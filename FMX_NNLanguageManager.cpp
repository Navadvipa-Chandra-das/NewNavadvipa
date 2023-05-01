// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <fmx.h>
#pragma hdrstop

#include "FMX_NNConst.h"

#include "FMX_NNLanguageManager.h"
#include "FMX_NNDBMiracle.h"
#include <memory>
#include "FMX_NNCommon.h"

#if (!__ANDROID__)
#pragma resource "*.res"
#endif

#pragma package(smart_init)

// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNNFLanguageManager *) {
  new TNNFLanguageManager(NULL);
}

namespace NNF {

const int FieldIndexLanguageStringID = 2;
const int FieldIndexTranslate        = 4;

TLanguage::TLanguage()
{
}

TLanguage::~TLanguage()
{
}

}

// ---------------------------------------------------------------------------
__fastcall TNNFLanguageManager::TNNFLanguageManager( TComponent* Owner )
  : inherited( Owner )
{
  LanguageSet = new NNF::TLanguageSet();
  PrepareLanguageExcludeStringSet();
}

__fastcall TNNFLanguageManager::~TNNFLanguageManager()
{
  delete LanguageSet;
  LanguageSet = nullptr;
}

void __fastcall TNNFLanguageManager::PrepareLanguageExcludeStringSet()
{
  LanguageExcludeStringSet.insert( L"TComponentName" );
  PairExcludeStringSet.insert( L"TAction.Category" );
}

void __fastcall TNNFLanguageManager::PrepareStrings( TStrings *AStrings )
{
  for ( NNF::TLanguageVector::iterator I = LanguageVector.begin(); I != LanguageVector.end(); ++ I )
    AStrings->Add( (*I).Language );
}

int __fastcall TNNFLanguageManager::LanguageIDToItemIndex( long long int ALanguageID )
{
  for ( NNF::TLanguageVector::iterator I = LanguageVector.begin(); I != LanguageVector.end(); ++ I )
    if ( (*I).LanguageID == ALanguageID )
      return I - LanguageVector.begin();
  return -1;
}

void __fastcall TNNFLanguageManager::Notification(TComponent *AComponent,
    TOperation Operation)
{
  inherited::Notification( AComponent, Operation );
  if ( Operation == opRemove ) {
    if ( AComponent == fConnection ) {
      fConnection = nullptr;
      return;
    }
    bool IsRunTime = !ComponentState.Contains( csDesigning );
    TNNFLanguage *o = dynamic_cast< TNNFLanguage* >( AComponent );
    if ( IsRunTime && o && LanguageSet ) {
      NNF::TLanguageSet::iterator i = LanguageSet->find( o );
      if ( i != LanguageSet->end() )
        LanguageSet->erase(i);
    }
  }
}

void __fastcall TNNFLanguageManager::AddComp( TNNFLanguage *aComp )
{
  if ( !LanguageSet )
    return;

  aComp->FreeNotification( this );
  LanguageSet->insert( aComp );
}

void __fastcall TNNFLanguageManager::EraseComp( TNNFLanguage *aComp )
{
  if ( !LanguageSet )
    return;

  NNF::TLanguageSet::iterator i = LanguageSet->find( aComp );
  if ( i != LanguageSet->end() )
    LanguageSet->erase(i);
}

void __fastcall TNNFLanguageManager::SetConnection( TFDConnection *Value )
{
  if ( fConnection != Value ) {
    fConnection = Value;
    if ( fConnection )
      fConnection->FreeNotification( this );
  }
}

void __fastcall TNNFLanguageManager::LoadLanguages()
{
  if ( !(Connection && Connection->Connected) )
    return;

  std::unique_ptr< TNNFQuery > qu( new TNNFQuery( this ) );
  qu->Connection = Connection;

  qu->ClearAll();
  qu->SQL->Text = L"select a.\"LanguagesID\","
    "\"LanguagesStringID\","
    "\"Languages\" from &PRABHUPADA_SCHEMA\"Languages\" a order by a.\"Languages\";";
  qu->PrepareStandartMacros();
  qu->Active = true;

  NNF::TLanguage ALanguage;
  LanguageVector.clear();
  int I = 0;
  while ( !qu->Eof ) {
    ALanguage.ItemIndex        = I++;
    ALanguage.LanguageID       = qu->Fields->Fields[ 0 ]->AsLargeInt;
    ALanguage.LanguageStringID = qu->Fields->Fields[ 1 ]->AsString;
    ALanguage.Language         = qu->Fields->Fields[ 2 ]->AsString;
    LanguageVector.push_back( ALanguage );
    qu->Next();
  }
  qu->Active = false;
}

void __fastcall TNNFLanguageManager::SetCurrentLanguageID( long long int Value )
{
  if ( FCurrentLanguageID != Value ) {
    FCurrentLanguageID = Value;

    if ( !( Connection && Connection->Connected ) )
      return;

    if ( !LanguageSet )
      return;

    for ( NNF::TLanguageSet::iterator i = LanguageSet->begin(); i != LanguageSet->end(); ++i )
      (*i)->Apply();
  }
}

void __fastcall TNNFLanguageManager::SetMainLanguageID( long long int Value )
{
  if ( FCurrentLanguageID != Value ) {
    FCurrentLanguageID = Value;

    if ( !( Connection && Connection->Connected ) )
      return;

    if ( !LanguageSet )
      return;

    for ( NNF::TLanguageSet::iterator i = LanguageSet->begin(); i != LanguageSet->end(); ++i )
      (*i)->FirstApplyWork = true;
  }
}

void __fastcall TNNFLanguageManager::PrepareOwnerWordsRecursive( TComponent *AOwner
                                   , NNF::TDoInsertLanguageRow ADoInsertLanguageRow
                                   , String &AOwnerClassNamePrefix
                                   , bool &AFirstMinusOne )
{
  TRttiType *ARttiType;
  TRttiProperty *ARttiProperty;
  DynamicArray< TRttiProperty* > AArrayRttiProperty;
  TRttiContext *ARttiContext = new TRttiContext();
  int L = AOwner->ComponentCount, M;
  TRttiType *APropertyType;
  TComponent *AChild;
  TValue SV;
  String S, /*OCS = AOwner->ClassName(),*/ PTCN, AChildClassName, ALanguageStringID;
  NNF::TStringSet AStringSet;
  bool ATranslateSet;

  AOwnerClassNamePrefix += AOwner->ClassName() + L".";
  String LocalOwnerClassNamePrefix;
  for ( int I = -1; I < L; ++I ) {
    if ( I == -1 ) {
      if ( AFirstMinusOne ) {
        AChild = AOwner;
        AFirstMinusOne = false;
      } else
        break;
    } else
      AChild = AOwner->Components[ I ];
    AChildClassName = AChild->ClassName();
    if ( I >= 0 ) {
      LocalOwnerClassNamePrefix = AOwnerClassNamePrefix;
      PrepareOwnerWordsRecursive( AChild, ADoInsertLanguageRow, LocalOwnerClassNamePrefix, AFirstMinusOne );
    }
    ARttiType = ARttiContext->GetType( AChild->ClassType() );
    AArrayRttiProperty = ARttiType->GetProperties();
    M = AArrayRttiProperty.Length;
    AStringSet.clear();
    for ( int J = 0; J < M; ++J ) {
      ARttiProperty = AArrayRttiProperty[ J ];
      APropertyType = ARttiProperty->PropertyType;
      PTCN = APropertyType->ClassName();
      if ( PTCN == L"TRttiStringType" ) {
        if ( LanguageExcludeStringSet.find( APropertyType->Name ) == LanguageExcludeStringSet.end() &&
             PairExcludeStringSet.find( AChildClassName + L"." + ARttiProperty->Name ) == PairExcludeStringSet.end() &&
             ARttiProperty->Name != "DataField" && !ARttiProperty->Name.IsEmpty() ) {
          SV = ARttiProperty->GetValue( AChild );
          S = SV.AsString();
          if ( !S.IsEmpty() ) {
            ALanguageStringID = AOwnerClassNamePrefix + AChild->Name + L"." + ARttiProperty->Name;
            if ( AStringSet.find( ALanguageStringID ) == AStringSet.end() ) {
              AStringSet.insert( ALanguageStringID );
              if ( ADoInsertLanguageRow ) {
                ATranslateSet = false;
                ADoInsertLanguageRow( ALanguageStringID, S, ATranslateSet );
                if ( ATranslateSet ) {
                  SV = S;
                  ARttiProperty->SetValue( AChild, SV );
                }
              }
            }
          }
        }
      }
    }
  }
}

void __fastcall TNNFLanguageManager::PrepareOwnerWords( TComponent *AOwner
                                   , NNF::TDoInsertLanguageRow ADoInsertLanguageRow
                                   , NNF::TDoPrepareOwner ADoPrepareOwner
                                   , TNotifyEvent ADoUnPrepareOwner )
{
  if ( ADoPrepareOwner )
    ADoPrepareOwner( AOwner->ClassName() );

  String AOwnerClassNamePrefix;
  bool AFirstMinusOne = true;
  PrepareOwnerWordsRecursive( AOwner, ADoInsertLanguageRow, AOwnerClassNamePrefix, AFirstMinusOne );

  if ( ADoUnPrepareOwner )
    ADoUnPrepareOwner( AOwner );
}

void __fastcall TNNFLanguageManager::PrepareLanguageOwner( const String &AOwnerString )
{
  long long int AKindID;

  Query = new TNNFQuery( this );
  Query->Connection = Connection;
  Query->FetchOptions->Unidirectional = true;
  Query->FetchOptions->CursorKind = ckForwardOnly;

  Query->SQL->Text = L"select\n"
                     "  a.\"KindID\"\n"
                     "from \n"
                     "  &PRABHUPADA_SCHEMA\"LanguageKind\" a\n"
                     "where\n"
                     "    a.\"Kind\" = :AOwnerString;";

  Query->PrepareStandartMacros();
  Query->DeclareAndSetParam( "AOwnerString", AOwnerString );
  Query->Active = true;

  if ( Query->Eof )
    return;

  AKindID = Query->Fields->Fields[ 0 ]->AsLargeInt;

  Query->ClearAll();
  if ( CurrentLanguageID == NNFConst::MainLanguageID )
    Query->SQL->Text = L"select\n"
                        "  a.\"EntityID\"\n"
                        ", a.\"KindID\"\n"
                        ", a.\"Entity\"\n"
                        ", a.\"Actual\"\n"
                        ", a.\"Original\" as \"Translate\"\n"
                        "from \n"
                        "  &PRABHUPADA_SCHEMA\"Language\" a\n"
                        "where\n"
                        "    a.\"KindID\" = :AKindID;";
  else {
    Query->SQL->Text = L"select\n"
                        "  a.\"EntityID\"\n"
                        ", a.\"KindID\"\n"
                        ", a.\"Entity\"\n"
                        ", a.\"Actual\"\n"
                        ", b.\"Translate\"\n"
                        "from \n"
                        "  &PRABHUPADA_SCHEMA\"Language\" a\n"
                        ", &PRABHUPADA_SCHEMA\"Translate\" b\n"
                        "where\n"
                        "    a.\"KindID\" = :AKindID\n"
                        "and b.\"LanguageID\" = a.\"EntityID\"\n"
                        "and b.\"LanguagesID\" = :LanguagesID;";
    Query->DeclareAndSetParam( "LanguagesID", CurrentLanguageID );
  }
  Query->PrepareStandartMacros();
  Query->DeclareAndSetParam( "AKindID", AKindID );
  Query->Active = true;

  while ( !Query->Eof ) {
    LanguageMap[ Query->Fields->Fields[ NNF::FieldIndexLanguageStringID ]->AsString ] = Query->Fields->Fields[ NNF::FieldIndexTranslate ]->AsString;
    Query->Next();
  }
}

void __fastcall TNNFLanguageManager::UnPrepareLanguageOwner( TObject *Sender )
{
  delete Query;
  Query = nullptr;
}

void __fastcall TNNFLanguageManager::SetLanguageRow( const String &ALanguage
                                                   , String &ATranslate
                                                   , bool &ATranslateSet )
{
  NNF::TStringMap::iterator I = LanguageMap.find( ALanguage );
  if ( I != LanguageMap.end() ) {
    ATranslate = (*I).second;
    ATranslateSet = true;
  }
}

// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNNFLanguage *)
{
  new TNNFLanguage( NULL );
}

// ---------------------------------------------------------------------------
__fastcall TNNFLanguage::TNNFLanguage( TComponent* Owner )
  : inherited( Owner )
{
}
// ---------------------------------------------------------------------------

void __fastcall TNNFLanguage::SetManager( TNNFLanguageManager *Value )
{
  if ( fManager != Value ) {
    bool IsRunTime = !ComponentState.Contains( csDesigning );
    if ( IsRunTime && fManager )
      fManager->EraseComp( this );
    fManager = Value;
    if ( fManager ) {
      if ( IsRunTime )
        fManager->AddComp( this );
      fManager->FreeNotification( this );
    }
  }
}

void __fastcall TNNFLanguage::Notification( TComponent *AComponent,
    TOperation Operation )
{
  inherited::Notification( AComponent, Operation );
  if ( Operation == opRemove && AComponent == fManager )
    fManager = nullptr;
}

void __fastcall TNNFLanguage::DoLanguage()
{
  if ( Manager )
    Manager->PrepareOwnerWords( Owner
                              , Manager->SetLanguageRow
                              , Manager->PrepareLanguageOwner
                              , Manager->UnPrepareLanguageOwner );
  if ( fOnLanguage )
    fOnLanguage( this );
}

void __fastcall TNNFLanguage::Apply()
{
  if ( !Manager )
    return;

  if ( Manager->CurrentLanguageID == 0 )
    return;

  if ( FirstApplyWork ) {
    if ( Manager->CurrentLanguageID != NNFConst::MainLanguageID )
      DoLanguage();
    FirstApplyWork = false;
  } else
    DoLanguage();
}

namespace Fmx_nnlanguagemanager
{

void __fastcall PACKAGE Register()
{
  TComponentClass classes[ 2 ];
  classes[ 0 ] = __classid( TNNFLanguageManager );
  classes[ 1 ] = __classid( TNNFLanguage );
  RegisterComponents( L"FMX New Navadvipa", classes, 1 );
}

}
// ---------------------------------------------------------------------------

