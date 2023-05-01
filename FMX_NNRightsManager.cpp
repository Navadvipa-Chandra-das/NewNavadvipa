// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <fmx.h>
#pragma hdrstop

#include "FMX_NNConst.h"

#include "FMX_NNRightsManager.h"
#include "FMX_NNDBMiracle.h"
#include <memory>

#if (!__ANDROID__)
#pragma resource "*.res"
#endif

#pragma package(smart_init)

// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNNFRightsManager *) {
  new TNNFRightsManager(NULL);
}

// ---------------------------------------------------------------------------
__fastcall TNNFRightsManager::TNNFRightsManager( TComponent* Owner )
  : inherited( Owner )
  , fConnection( NULL )
  , CompList( NULL )
  , fSuperUser( false )
{
  CompList = new NNF::TCompList();
}

__fastcall TNNFRightsManager::~TNNFRightsManager()
{
  delete CompList;
  CompList = nullptr;
}

// ---------------------------------------------------------------------------
namespace Fmx_nnrightsmanager
{

void __fastcall PACKAGE Register()
{
  TComponentClass classes[ 2 ];
  classes[ 0 ] = __classid( TNNFRightsManager );
  classes[ 1 ] = __classid( TNNFRight );
  RegisterComponents( L"FMX New Navadvipa", classes, 1 );
}

}
// ---------------------------------------------------------------------------

void __fastcall TNNFRightsManager::Notification(TComponent *AComponent,
    TOperation Operation)
{
  inherited::Notification( AComponent, Operation );
  if ( Operation == opRemove ) {
    if ( AComponent == fConnection ) {
      fConnection = nullptr;
      return;
    }
    bool IsRunTime = !ComponentState.Contains( csDesigning );
    TNNFRight *o = dynamic_cast< TNNFRight* >( AComponent );
    if ( IsRunTime && o && CompList ) {
      NNF::TCompList::iterator i = CompList->find( o );
      if ( i != CompList->end() )
        CompList->erase(i);
    }
  }
}

void __fastcall TNNFRightsManager::AddComp( TNNFRight *aComp )
{
  if ( !CompList )
    return;

  aComp->FreeNotification( this );
  CompList->insert( aComp );
}

void __fastcall TNNFRightsManager::EraseComp(TNNFRight *aComp)
{
  if ( !CompList )
    return;

  NNF::TCompList::iterator i = CompList->find( aComp );
  if ( i != CompList->end() )
    CompList->erase(i);
}

void __fastcall TNNFRightsManager::RevokeAll()
{
  for ( NNF::TBoolVector::iterator i = Rights.begin(); i != Rights.end(); ++i )
    (*i) = false;
}

void __fastcall TNNFRightsManager::SetConnection( TFDConnection *Value )
{
  if ( fConnection != Value ) {
    fConnection = Value;
    if ( fConnection )
      fConnection->FreeNotification( this );
  }
}

void __fastcall TNNFRightsManager::LoadRights()
{
  if ( !(Connection && Connection->Connected) )
    return;

  std::unique_ptr< TNNFQuery > qu( new TNNFQuery(this));
  qu->Connection = Connection;

  qu->SQL->Text = L"select max( a.\"RightIndex\" ) from \"RightsUser\" a;";
  qu->Active = true;
  std::size_t L = qu->Fields->Fields[ 0 ]->AsLargeInt + 1;

  qu->ClearAll();
  qu->SQL->Text = L"select a.\"RightIndex\", a.\"Value\" from \"RightsUser\" a order by a.\"RightIndex\";";
  qu->Active = true;

  TColor AColorFont, AColorFon;
  std::size_t I = 0;
  Rights.clear();
  Rights.reserve( L );
  while ( !qu->Eof ) {
    if ( I != qu->Fields->Fields[ 0 ]->AsLargeInt )
      throw Exception( L"Пожалуйста, обновите индексы таблицы прав!" );
    Rights.push_back( qu->Fields->Fields[ 1 ]->AsBoolean );
    qu->Next();
    ++I;
  }
  qu->Active = false;
}

void __fastcall TNNFRightsManager::RefreshRights( long long int AUserID )
{
  if ( !(Connection && Connection->Connected) )
    return;

  std::unique_ptr< TNNFQuery > qu( new TNNFQuery( this ) );
  qu->Connection = Connection;

  qu->SQL->Text = L"call \"LoadRightsUser\"( :AUserID );";
  qu->DeclareAndSetParam( "AUserID", AUserID );
  qu->ExecSQL();

  LoadRights();

  if ( !CompList )
    return;
  for ( NNF::TCompList::iterator i = CompList->begin(); i != CompList->end(); ++i )
    (*i)->Apply();
}

bool __fastcall  TNNFRightsManager::IsRight( int ARightIndex, NNF::TIsThrow AIsThrow )
{
  if ( SuperUser )
    return true;
  if ( ARightIndex < 0 || ARightIndex >= Rights.size() )
    throw Exception( NNFConst::SorryNoExistsRight );

  bool B = Rights[ ARightIndex ];

  if( !B ) {
    if ( AIsThrow == NNF::TIsThrow::Abort ) {
      Abort();
      return false;
    } else if ( AIsThrow == NNF::TIsThrow::Quiet ) {
      return false;
    } else if ( AIsThrow == NNF::TIsThrow::ThrowException ||
                AIsThrow == NNF::TIsThrow::ShowMessage ) {

      std::unique_ptr< TNNFQuery > qu( new TNNFQuery( this ) );
      qu->Connection = Connection;

      qu->SQL->Text = L"select \"RightIndexToName\"( :ARightIndex );";
      qu->DeclareAndSetParam( "ARightIndex", ARightIndex );
      qu->Active = true;

      String S = NNFConst::SorryNoRight + NNFConst::DoubleCommas + qu->Fields->Fields[ 0 ]->AsString + NNFConst::DoubleCommas;
      qu->Active = false;

      if ( AIsThrow == NNF::TIsThrow::ThrowException )
        throw Exception( S );
      else
        Dialogs::ShowMessage( S );

      return false;
    }
  }
  return B;
}

// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNNFRight *)
{
  new TNNFRight( NULL );
}

// ---------------------------------------------------------------------------
__fastcall TNNFRight::TNNFRight( TComponent* Owner )
  : inherited( Owner )
{
}
// ---------------------------------------------------------------------------

void __fastcall TNNFRight::SetManager(TNNFRightsManager *Value)
{
  if ( fManager != Value ) {
    bool IsRunTime = !ComponentState.Contains( csDesigning );
    if ( IsRunTime && fManager )
      fManager->EraseComp( this );
    fManager = Value;
    if ( fManager ) {
      if ( IsRunTime )
        fManager->AddComp(this);
      fManager->FreeNotification( this );
    }
  }
}

void __fastcall TNNFRight::Notification( TComponent *AComponent,
    TOperation Operation )
{
  inherited::Notification( AComponent, Operation );
  if ( Operation == opRemove && AComponent == fManager )
    fManager = nullptr;
}

