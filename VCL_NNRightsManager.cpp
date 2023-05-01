// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNConst.h"

#include "VCL_NNRightsManager.h"
#include "VCL_NNDBMiracle.h"
#include <memory>

#pragma resource "*.res"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNNVRightsManager *) {
  new TNNVRightsManager(NULL);
}

// ---------------------------------------------------------------------------
__fastcall TNNVRightsManager::TNNVRightsManager( TComponent* Owner )
  : inherited( Owner )
  , fConnection( NULL )
  , CompList( NULL )
  , fSuperUser( false )
{
  CompList = new NNV::TCompList();
}

__fastcall TNNVRightsManager::~TNNVRightsManager()
{
  delete CompList;
  CompList = NULL;
}

// ---------------------------------------------------------------------------
namespace Vcl_nnrightsmanager
{

void __fastcall PACKAGE Register()
{
  TComponentClass classes[ 2 ];
  classes[ 0 ] = __classid( TNNVRightsManager );
  classes[ 1 ] = __classid( TNNVRight );
  RegisterComponents( L"VCL New Navadvipa", classes, 1 );
}

}
// ---------------------------------------------------------------------------

void __fastcall TNNVRightsManager::Notification(TComponent *AComponent,
    TOperation Operation)
{
  inherited::Notification( AComponent, Operation );
  if ( Operation == opRemove ) {
    if ( AComponent == fConnection ) {
      fConnection = nullptr;
      return;
    }
    bool IsRunTime = !ComponentState.Contains( csDesigning );
    TNNVRight *o = dynamic_cast< TNNVRight* >( AComponent );
    if ( IsRunTime && o && CompList ) {
      NNV::TCompList::iterator i = CompList->find( o );
      if ( i != CompList->end() )
        CompList->erase(i);
    }
  }
}

void __fastcall TNNVRightsManager::AddComp( TNNVRight *aComp )
{
  if ( !CompList )
    return;

  aComp->FreeNotification( this );
  CompList->insert( aComp );
}

void __fastcall TNNVRightsManager::EraseComp(TNNVRight *aComp)
{
  if ( !CompList )
    return;

  NNV::TCompList::iterator i = CompList->find( aComp );
  if ( i != CompList->end() )
    CompList->erase(i);
}

void __fastcall TNNVRightsManager::RevokeAll()
{
  for ( NNV::TBoolVector::iterator i = Rights.begin(); i != Rights.end(); ++i )
    (*i) = false;
}

void __fastcall TNNVRightsManager::SetConnection( TFDConnection *Value )
{
  if ( fConnection != Value ) {
    fConnection = Value;
    if ( fConnection )
      fConnection->FreeNotification( this );
  }
}

void __fastcall TNNVRightsManager::LoadRights()
{
  if ( !(Connection && Connection->Connected) )
    return;

  std::unique_ptr< TNNVQuery > qu( new TNNVQuery(this));
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

void __fastcall TNNVRightsManager::RefreshRights( long long int AUserID )
{
  if ( !(Connection && Connection->Connected) )
    return;

  std::unique_ptr< TNNVQuery > qu( new TNNVQuery( this ) );
  qu->Connection = Connection;

  qu->SQL->Text = L"call &PRABHUPADA_SCHEMA\"LoadRightsUser\"( :AUserID );";
  qu->PrepareStandartMacros();
  qu->DeclareAndSetParam( "AUserID", AUserID );
  qu->ExecSQL();

  LoadRights();

  if ( !CompList )
    return;
  for ( NNV::TCompList::iterator i = CompList->begin(); i != CompList->end(); ++i )
    (*i)->Apply();
}

bool __fastcall  TNNVRightsManager::IsRight( int ARightIndex, NNV::TIsThrow AIsThrow )
{
  if ( SuperUser )
    return true;
  if ( ARightIndex < 0 || ARightIndex >= Rights.size() )
    throw Exception( NNVConst::SorryNoExistsRight );

  bool B = Rights[ ARightIndex ];

  if( !B ) {
    if ( AIsThrow == NNV::TIsThrow::Abort ) {
      Abort();
      return false;
    } else if ( AIsThrow == NNV::TIsThrow::Quiet ) {
      return false;
    } else if ( AIsThrow == NNV::TIsThrow::ThrowException ||
                AIsThrow == NNV::TIsThrow::ShowMessage ) {

      std::unique_ptr< TNNVQuery > qu( new TNNVQuery( this ) );
      qu->Connection = Connection;

      qu->SQL->Text = L"select &PRABHUPADA_SCHEMA\"RightIndexToName\"( :ARightIndex );";
      qu->PrepareStandartMacros();
      qu->DeclareAndSetParam( "ARightIndex", ARightIndex );
      qu->Active = true;

      String S = NNVConst::SorryNoRight + NNVConst::DoubleCommas + qu->Fields->Fields[ 0 ]->AsString + NNVConst::DoubleCommas;
      qu->Active = false;

      if ( AIsThrow == NNV::TIsThrow::ThrowException )
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

static inline void ValidCtrCheck(TNNVRight *)
{
  new TNNVRight( NULL );
}

// ---------------------------------------------------------------------------
__fastcall TNNVRight::TNNVRight( TComponent* Owner )
  : inherited( Owner )
{
}
// ---------------------------------------------------------------------------

void __fastcall TNNVRight::SetManager(TNNVRightsManager *Value)
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

void __fastcall TNNVRight::Notification( TComponent *AComponent,
    TOperation Operation )
{
  inherited::Notification( AComponent, Operation );
  if ( Operation == opRemove && AComponent == fManager )
    fManager = nullptr;
}

