//---------------------------------------------------------------------------
#pragma hdrstop

#include "FMX_NNDmNewNavadvipa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "FMX.Controls.TControl"
#pragma link "FMX_NNDmRes"
#pragma link "FMX_NNLanguageManager"
#pragma link "FMX_NNRightsManager"
#pragma link "FMX_NNDBMiracle"
#pragma resource "*.dfm"
TdmfNewNavadvipa *dmfNewNavadvipa;
//---------------------------------------------------------------------------
__fastcall TdmfNewNavadvipa::TdmfNewNavadvipa( TComponent* Owner )
  : inherited( Owner )
{
}

__fastcall TdmfNewNavadvipa::TdmfNewNavadvipa( TComponent* Owner
                                             , NNF::TDoLogin AOnLogin )
  : inherited( Owner )
  , FOnLogin( AOnLogin )
{
}

void __fastcall TdmfNewNavadvipa::Loaded()
{
  inherited::Loaded();
#ifdef _WIN64
  PgDrLinkDB->VendorLib = L"C:\\PostgreSQL\\15\\bin\\libpq.dll";
#endif

#ifdef _WIN64
  SQLiteDrLinkDB->VendorLib = NNFConst::PrabhupadaSlovarFiles + L"sqlite3.dll";
#elif _WIN32
  SQLiteDrLinkDB->VendorLib = NNFConst::PrabhupadaSlovarFiles + L"sqlite3.dll";
#elif _PLAT_ANDROID
  SQLiteDrLinkDB->VendorLib = NNFConst::PrabhupadaSlovarFiles + L"sqlite3.dll";
#elif _PLAT_IOS32
  SQLiteDrLinkDB->VendorLib = NNFConst::PrabhupadaSlovarFiles + L"sqlite3.dll";
#elif _PLAT_IOS64
  SQLiteDrLinkDB->VendorLib = NNFConst::PrabhupadaSlovarFiles + L"sqlite3.dll";
#elif _PLAT_LINUX64
  SQLiteDrLinkDB->VendorLib = NNFConst::PrabhupadaSlovarFiles + L"sqlite3.dll";
#endif
}

//---------------------------------------------------------------------------
void __fastcall TdmfNewNavadvipa::coDataLoad(TObject *Sender)
{
  MapFiler.LoadFromFiler( coData->Filer );
  ColorVector.LoadFromFiler( coData->Filer );
}
//---------------------------------------------------------------------------

void __fastcall TdmfNewNavadvipa::coDataSave(TObject *Sender)
{
  MapFiler.SaveToFiler( coData->Filer );
  ColorVector.SaveToFiler( coData->Filer );
}
//---------------------------------------------------------------------------

void __fastcall TdmfNewNavadvipa::ResetConfig( const String &AUser, TNNFQuery *AQuery )
{
  AQuery->ClearAll();
  AQuery->SQL->Text = "call &PRABHUPADA_SCHEMA\"ResetConfig\"( :AUser );";
  AQuery->PrepareStandartMacros();

  Variant AUser_ = AUser;
  AQuery->DeclareAndSetParam( "AUser", AUser_ );
  AQuery->ExecSQL();
}

void __fastcall TdmfNewNavadvipa::CreateNewUser( const String &AUser
                                               , const String &APassword
                                               , const String &ARole
                                               , bool IsSuperUser )
{
  quDB->ClearAll();
  quDB->SQL->Text = "call &PRABHUPADA_SCHEMA\"CreateUser\"( :AUser, :APassword, :ARole, :IsSuperUser );";
  quDB->PrepareStandartMacros();

  Variant AUser_ = AUser
        , APassword_ = NNF::CriptPassword( APassword );

  quDB->DeclareAndSetParam( "AUser", AUser_ );
  quDB->DeclareAndSetParam( "APassword", APassword_ );
  quDB->DeclareAndSetParam( "ARole", ARole );
  quDB->DeclareAndSetParam( "IsSuperUser", IsSuperUser );
  quDB->ExecSQL();
}

void __fastcall TdmfNewNavadvipa::InsertLanguageRow( const String &ALanguage
                                                   , String &ATranslate
                                                   , bool &ATranslateSet )
{
  long long int AKindID = quLanguageKindKindID->AsLargeInt;
  quDB->DeclareAndSetParam( "AKindID", AKindID );
  quDB->DeclareAndSetParam( "ALanguage", ALanguage );
  quDB->DeclareAndSetParam( "ATranslate", ATranslate );
  quDB->ExecSQL();
}

void __fastcall TdmfNewNavadvipa::PrepareLanguageOwner( const String &AOwnerString )
{
  quDB->ClearAll();
  quDB->SQL->Text = "call &PRABHUPADA_SCHEMA\"InsertLanguageRow\"( :AKindID"
                                              ", :ALanguage"
                                              ", :ATranslate );";
  quDB->PrepareStandartMacros();
}

void __fastcall TdmfNewNavadvipa::UnPrepareLanguageOwner( TObject *Sender )
{
  quDB->ClearAll();
  quLanguage->CWRefresh();
}

void __fastcall TdmfNewNavadvipa::conDBBeforeConnect(TObject *Sender)
{
  PseudoPassword          = conDB->Params->Password;
  conDB->Params->Password = NNF::CriptPassword( conDB->Params->Password );
}
//---------------------------------------------------------------------------

void __fastcall TdmfNewNavadvipa::conDBAfterConnect( TObject *Sender )
{
  if ( conDB->DriverName[ 1 ] == 'P' /*PostgreSQL*/ ) {
    FUserID   = GetUserID( UserName );
    AfterLogon( UserID );
    rmDB->LoadRights();
  }
  lmDB->LoadLanguages();
}
//---------------------------------------------------------------------------

long long int __fastcall TdmfNewNavadvipa::GetUserID( const String &AUserName )
{
  long long int R;
  quDB->ClearAll();
  quDB->SQL->Text = L"select &PRABHUPADA_SCHEMA\"GetUserID\"( :AUserName );";
  quDB->PrepareStandartMacros();
  quDB->DeclareAndSetParam( "AUserName", AUserName );
  quDB->Active = true;
  R = quDB->Fields->Fields[ 0 ]->AsLargeInt;
  quDB->Active = false;
  return R;
}

void __fastcall TdmfNewNavadvipa::AfterLogon( long long int AUserID )
{
  quDB->ClearAll();
  quDB->SQL->Text = "call &PRABHUPADA_SCHEMA\"AfterLogon\"( :AUserID );";
  quDB->PrepareStandartMacros();
  quDB->DeclareAndSetParam( "AUserID", AUserID );
  quDB->ExecSQL();
}

String __fastcall TdmfNewNavadvipa::GetUserName()
{
  return conDB->Params->UserName;
}

void __fastcall TdmfNewNavadvipa::DoLogin()
{
  if ( FOnLogin )
    FOnLogin( this, conDB );
}

void __fastcall TdmfNewNavadvipa::DataModuleCreate(TObject *Sender)
{
  DoLogin();
  // чтение из базы данных возможно только после соединения с ней!
  inherited::DataModuleCreate( Sender );

  NNF::TMapQuery AMapQuery( this );
  AMapQuery.PrepareStandartMacros();
}
//---------------------------------------------------------------------------

