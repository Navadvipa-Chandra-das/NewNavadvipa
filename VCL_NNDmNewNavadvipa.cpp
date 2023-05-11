// ---------------------------------------------------------------------------

#pragma hdrstop

#include "VCL_NNDmNewNavadvipa.h"
#include "VCL_NNFmChangePassword.h"
#include "VCL_NNFmLogin.h"
#include "VCL_NNRightsIndex.h"
#include "VCL_NNColorIndex.h"
#include <memory>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
//#pragma classgroup "Vcl.Controls.TControl"
#pragma link "VCL_NNDmRes"
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNRightsManager"
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNLanguageManager"
#pragma resource "*.dfm"
TdmvNewNavadvipa *dmvNewNavadvipa;

namespace NNV
{

const long long int RootRightsKindID = 79;
const long long int RootColorKindID  = 72;
const long long int RootCommodKindID = 1;
const long long int RootRoleKindID   = 80;
const long long int RootLanguageKindID = 115;

}

// ---------------------------------------------------------------------------
__fastcall TdmvNewNavadvipa::TdmvNewNavadvipa( TComponent* Owner )
  : inherited( Owner )
{
}
// ---------------------------------------------------------------------------

__fastcall TdmvNewNavadvipa::TdmvNewNavadvipa( TComponent* Owner
                                             , NNV::TDoLogin AOnLogin )
  : inherited( Owner )
  , FOnLogin( AOnLogin )
{
}

void __fastcall TdmvNewNavadvipa::Loaded()
{
  inherited::Loaded();
#ifdef _WIN64
  PgDrLinkDB->VendorLib = L"C:\\PostgreSQL\\15\\bin\\libpq.dll";
#endif
}

void __fastcall TdmvNewNavadvipa::DBGridColor( TNNVDBGrid *dg, long long int AColorNo )
{
  TColor FonColor_, FontColor_;
  NNV::CycleColor( AColorNo, FonColor_, FontColor_ );

  dg->Canvas->Brush->Color = FonColor_;
  dg->Canvas->Font->Color  = FontColor_;
}

void __fastcall TdmvNewNavadvipa::coDataLoad( TObject *Sender )
{
  cdNN->CustomColors->Text = coData->Filer->ReadString();
  MapFiler.LoadFromFiler( coData->Filer );
  ColorVector.LoadFromFiler( coData->Filer );
  NNVConst::FonColorValueChange = coData->Filer->ReadColor();
  NNVConst::FontColorValueChange = coData->Filer->ReadColor();
  NNV::TMapQuery AMapQuery( this );
  AMapQuery.LoadFromFiler( coData->Filer );
}
// ---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::coDataSave( TObject *Sender )
{
  coData->Filer->WriteString( cdNN->CustomColors->Text );
  MapFiler.SaveToFiler( coData->Filer );
  ColorVector.SaveToFiler( coData->Filer );
  coData->Filer->WriteColor( NNVConst::FonColorValueChange );
  coData->Filer->WriteColor( NNVConst::FontColorValueChange );
  NNV::TMapQuery AMapQuery( this );
  AMapQuery.SaveToFiler( coData->Filer );
}
// ---------------------------------------------------------------------------

String __fastcall TdmvNewNavadvipa::GetUserName()
{
  return conDB->Params->UserName;
}

void __fastcall TdmvNewNavadvipa::ResetConfig( const String &AUser, TNNVQuery *AQuery )
{
  AQuery->ClearAll();
  AQuery->SQL->Text = "call &PRABHUPADA_SCHEMA\"ResetConfig\"( :AUser );";
  AQuery->PrepareStandartMacros();

  Variant AUser_ = AUser;
  AQuery->DeclareAndSetParam( "AUser", AUser_ );
  AQuery->ExecSQL();
}

void __fastcall TdmvNewNavadvipa::PrepareLanguageOwner( const String &AOwnerString )
{
  quDB->ClearAll();
  quDB->SQL->Text = "call &PRABHUPADA_SCHEMA\"InsertLanguageRow\"( :AKindID"
                                              ", :ALanguage"
                                              ", :ATranslate );";
  quDB->PrepareStandartMacros();
}

void __fastcall TdmvNewNavadvipa::UnPrepareLanguageOwner( TObject *Sender )
{
  quDB->ClearAll();
  quLanguage->CWRefresh();
}

void __fastcall TdmvNewNavadvipa::InsertLanguageRow( const String &ALanguage
                                                   , String &ATranslate
                                                   , bool &ATranslateSet )
{
  long long int AKindID = quLanguageKindKindID->AsLargeInt;
  quDB->DeclareAndSetParam( "AKindID", AKindID );
  quDB->DeclareAndSetParam( "ALanguage", ALanguage );
  quDB->DeclareAndSetParam( "ATranslate", ATranslate );
  quDB->ExecSQL();
}

void __fastcall TdmvNewNavadvipa::CreateNewUser( const String &AUser
                                               , const String &APassword
                                               , const String &ARole
                                               , bool IsSuperUser )
{
  quDB->ClearAll();
  quDB->SQL->Text = "call &PRABHUPADA_SCHEMA\"CreateUser\"( :AUser, :APassword, :ARole, :IsSuperUser );";
  quDB->PrepareStandartMacros();

  Variant AUser_ = AUser
        , APassword_ = NNV::CriptPassword( APassword );

  quDB->DeclareAndSetParam( "AUser", AUser_ );
  quDB->DeclareAndSetParam( "APassword", APassword_ );
  quDB->DeclareAndSetParam( "ARole", ARole );
  quDB->DeclareAndSetParam( "IsSuperUser", IsSuperUser );
  quDB->ExecSQL();
}

void __fastcall TdmvNewNavadvipa::SetNewUserPassword( const String &AUser
                                                          , const String &APassword )
{
  quDB->ClearAll();
  quDB->SQL->Text = "call &PRABHUPADA_SCHEMA\"SetNewUserPassword\"( :AUser, :APassword );";
  quDB->PrepareStandartMacros();

  Variant AUser_ = AUser
        , APassword_ = NNV::CriptPassword( APassword );

  quDB->DeclareAndSetParam( "AUser", AUser_ );
  quDB->DeclareAndSetParam( "APassword", APassword_ );
  quDB->ExecSQL();
}

void __fastcall TdmvNewNavadvipa::DeleteUser( const String &AUser )
{
  quDB->ClearAll();
  quDB->SQL->Text = "call &PRABHUPADA_SCHEMA\"DeleteUser\"( :AUser );";
  quDB->PrepareStandartMacros();

  Variant AUser_ = AUser;
  quDB->DeclareAndSetParam( "AUser", AUser_ );
  quDB->ExecSQL();
}

void __fastcall TdmvNewNavadvipa::SetUserRole( const String &AUser, const String &ARole, bool IsGrant )
{
  quDB->ClearAll();
  quDB->SQL->Text = "call &PRABHUPADA_SCHEMA\"SetUserRole\"( :AUser, :ARole, :IsGrant );";
  quDB->PrepareStandartMacros();

  quDB->DeclareAndSetParam( "AUser", AUser );
  quDB->DeclareAndSetParam( "ARole", ARole );
  quDB->DeclareAndSetParam( "IsGrant", IsGrant );

  quDB->ExecSQL();
}

void __fastcall TdmvNewNavadvipa::conDBBeforeConnect(TObject *Sender)
{
  PseudoPassword          = conDB->Params->Password;
  conDB->Params->Password = NNV::CriptPassword( conDB->Params->Password );
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::DataModuleCreate( TObject *Sender )
{
  DoLogin();
  // чтение из базы данных возможно только после соединени€ с ней!
  inherited::DataModuleCreate( Sender );

  NNV::TMapQuery AMapQuery( this );
  AMapQuery.PrepareStandartMacros();
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::DoLogin()
{
  if ( FOnLogin )
    FOnLogin( this, conDB );
}

void __fastcall TdmvNewNavadvipa::ChangePassword( TComponent *ASenderForm )
{
  fmvChangePassword = new TfmvChangePassword( Application );
  fmvChangePassword->ShowChangePassword( conDB->Params->UserName, ASenderForm );
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::SetIsDeletedUser( bool AIsDeleted )
{
  if ( quUsersIsDeleted->AsBoolean != AIsDeleted ) {
    quUsers->Edit();
    quUsersIsDeleted->AsBoolean = AIsDeleted;
    quUsers->Post();
  }
}

void __fastcall TdmvNewNavadvipa::SetNodeParamsCommodKind( TNNVNodeParams &NodeParams )
{
  NodeParams.Text = quCommodKindKind->DisplayText;

  if( quCommodKindActual->AsBoolean ) {
    NodeParams.ImageIndex    = (int)NNV::TImagesKind::imCommod;
    NodeParams.SelectedIndex = (int)NNV::TImagesKind::imCommod;
  } else {
    NodeParams.ImageIndex    = (int)NNV::TImagesKind::imCommodNA;
    NodeParams.SelectedIndex = (int)NNV::TImagesKind::imCommodNA;
  }
}

void __fastcall TdmvNewNavadvipa::SetNodeParamsRightsKind( TNNVNodeParams &NodeParams )
{
  NodeParams.Text = quRightsKindKind->DisplayText;

  if( quRightsKindActual->AsBoolean ) {
    NodeParams.ImageIndex    = (int)NNV::TImagesKind::imDocument;
    NodeParams.SelectedIndex = (int)NNV::TImagesKind::imDocument;
  } else {
    NodeParams.ImageIndex    = (int)NNV::TImagesKind::imDocumentNA;
    NodeParams.SelectedIndex = (int)NNV::TImagesKind::imDocumentNA;
  }
}

void __fastcall TdmvNewNavadvipa::SetNodeParamsRoleKind( TNNVNodeParams &NodeParams )
{
  NodeParams.Text = quRoleKindKind->DisplayText;

  if( quRoleKindActual->AsBoolean ) {
    NodeParams.ImageIndex    = (int)NNV::TImagesKind::imRoles;
    NodeParams.SelectedIndex = (int)NNV::TImagesKind::imRoles;
  } else {
    NodeParams.ImageIndex    = (int)NNV::TImagesKind::imContrAgentNA;
    NodeParams.SelectedIndex = (int)NNV::TImagesKind::imContrAgentNA;
  }
}

void __fastcall TdmvNewNavadvipa::SetNodeParamsLanguageKind( TNNVNodeParams &NodeParams )
{
  NodeParams.Text = quLanguageKindKind->DisplayText;

  if( quLanguageKindActual->AsBoolean ) {
    NodeParams.ImageIndex    = (int)NNV::TImagesKind::imFixedAssetsKind;
    NodeParams.SelectedIndex = (int)NNV::TImagesKind::imFixedAssetsKind;
  } else {
    NodeParams.ImageIndex    = (int)NNV::TImagesKind::imFixedAssetsKindNA;
    NodeParams.SelectedIndex = (int)NNV::TImagesKind::imFixedAssetsKindNA;
  }
}

void __fastcall TdmvNewNavadvipa::SetNodeParamsColorKind( TNNVNodeParams &NodeParams )
{
  NodeParams.Text = quColorKindKind->DisplayText;

  if( quColorKindActual->AsBoolean ) {
    NodeParams.ImageIndex    = (int)NNV::TImagesKind::imCashReason;
    NodeParams.SelectedIndex = (int)NNV::TImagesKind::imCashReason;
  } else {
    NodeParams.ImageIndex    = (int)NNV::TImagesKind::imCashReasonNA;
    NodeParams.SelectedIndex = (int)NNV::TImagesKind::imCashReasonNA;
  }
}

void __fastcall TdmvNewNavadvipa::quCommodNewRecord(TDataSet *DataSet)
{
  quCommodKindID->AsLargeInt = quCommodKindKindID->AsLargeInt;
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::dsCommodDataChange( TObject *Sender, TField *Field )
{
  if ( quCommodKindKindID->AsLargeInt != quCommodKindID->AsLargeInt && !quCommod->IsWorkFilter )
    quCommodKind->CWLocate( "KindID", quCommodKindID->AsLargeInt );
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::dsColorDataChange( TObject *Sender, TField *Field )

{
  if ( quColorKindKindID->AsLargeInt != quColorKindID->AsLargeInt && !quColor->IsWorkFilter )
    quColorKind->CWLocate( "KindID", quColorKindID->AsLargeInt );
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::quColorNewRecord( TDataSet *DataSet )
{
  quColorKindID->AsLargeInt = quColorKindKindID->AsLargeInt;
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::ColorIndexGenerate()
{
  quDB->ClearAll();
  quDB->SQL->Text = "call &PRABHUPADA_SCHEMA\"ColorIndexGenerate\"();";
  quDB->PrepareStandartMacros();
  quDB->ExecSQL();
  quColor->CWRefresh();
}

void __fastcall TdmvNewNavadvipa::RightsIndexGenerate()
{
  quDB->ClearAll();
  quDB->SQL->Text = "call &PRABHUPADA_SCHEMA\"RightsIndexGenerate\"();";
  quDB->PrepareStandartMacros();
  quDB->ExecSQL();
  quRights->CWRefresh();
}

void __fastcall TdmvNewNavadvipa::ColorVectorLoadFromDB()
{
  if ( coData->Connection && !coData->Connection->Connected )
    return;

  std::unique_ptr< TNNVQuery > qu( new TNNVQuery( this ) );
  std::unique_ptr< TFDTransaction> tr( new TFDTransaction( this ) );
  tr->Connection = coData->Connection;
  qu->Connection = coData->Connection;
  qu->Transaction = tr.get();

  qu->ClearAll();
  qu->SQL->Text = L"select max( a.\"VectorIndex\" ) from &PRABHUPADA_SCHEMA\"Color\" a;";
  qu->PrepareStandartMacros();
  qu->Active = true;
  std::size_t L = qu->Fields->Fields[ 0 ]->AsLargeInt;

  qu->ClearAll();
  qu->SQL->Text = L"select a.\"VectorIndex\", a.\"FontColor\", a.\"FonColor\" from &PRABHUPADA_SCHEMA\"Color\" a order by a.\"VectorIndex\";";
  qu->PrepareStandartMacros();
  qu->FetchOptions->Unidirectional = true;
  qu->FetchOptions->CursorKind = ckForwardOnly;
  qu->Active = true;

  TColor AColorFont, AColorFon;
  std::size_t I = 0;
  ColorVector.clear();
  ColorVector.reserve( L + 1 );
  while ( !qu->Eof ) {
    if ( I != qu->Fields->Fields[ 0 ]->AsLargeInt )
      throw Exception( L"ѕожалуйста, обновите индексы таблицы цветов!" );
    AColorFont = ( TColor )qu->Fields->Fields[ 1 ]->AsInteger;
    AColorFon  = ( TColor )qu->Fields->Fields[ 2 ]->AsInteger;
    ColorVector.push_back( NNV::TColorFonFont( AColorFont, AColorFon ) );
    qu->Next();
    ++I;
  }
  ColorVector.Size = I;
  qu->Active = false;
}

long long int __fastcall TdmvNewNavadvipa::EntityIDToKindID( long long int AEntityID )
{
  long long int R;
  quDB->ClearAll();
  quDB->SQL->Text = L"select &PRABHUPADA_SCHEMA\"EntityIDToKindID\"( :AEntityID );";
  quDB->PrepareStandartMacros();
  quDB->DeclareAndSetParam( "AEntityID", AEntityID );
  quDB->Active = true;
  R = quDB->Fields->Fields[ 0 ]->AsLargeInt;
  quDB->Active = false;
  return R;
}

void __fastcall TdmvNewNavadvipa::quColorCalcFields( TDataSet *DataSet )
{
  std::size_t I = quColorVectorIndex->AsLargeInt;
  if ( I < ColorVector.Size ) {
    quColorFonColorUser->AsInteger  = ColorVector[ I ].FonColor;
    quColorFontColorUser->AsInteger = ColorVector[ I ].FontColor;
  } else {
    quColorFonColorUser->AsInteger  = 0;
    quColorFontColorUser->AsInteger = 0;
  }
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::coDataDefault( TObject *Sender )
{
  ColorVectorLoadFromDB();
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::quRightsNewRecord( TDataSet *DataSet )
{
  quRightsKindID->AsLargeInt = quRightsKindKindID->AsLargeInt;
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::dsRoleDataChange(TObject *Sender, TField *Field)

{
  if ( quRoleKindKindID->AsLargeInt != quRoleKindID->AsLargeInt && !quRole->IsWorkFilter )
    quRoleKind->CWLocate( "KindID", quRoleKindID->AsLargeInt );
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::dsRightsDataChange(TObject *Sender, TField *Field)

{
  if ( quRightsKindKindID->AsLargeInt != quRightsKindID->AsLargeInt && !quRights->IsWorkFilter )
    quRightsKind->CWLocate( "KindID", quRightsKindID->AsLargeInt );
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::quRoleRightsNewRecord( TDataSet *DataSet )
{
  quRoleRightsRoleID->AsLargeInt = quRoleEntityID->AsLargeInt;
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::quRoleNewRecord(TDataSet *DataSet)
{
  quRoleKindID->AsLargeInt = quRoleKindKindID->AsLargeInt;
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::quUserRightsNewRecord( TDataSet *DataSet )
{
  quUserRightsUserID->AsLargeInt = quUsersUserID->AsLargeInt;
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::quUserRolesNewRecord( TDataSet *DataSet )
{
  quUserRolesUserID->AsLargeInt = quUsersUserID->AsLargeInt;
}
//---------------------------------------------------------------------------

long long int __fastcall TdmvNewNavadvipa::GetUserID( const String &AUserName )
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

void __fastcall TdmvNewNavadvipa::AfterLogon( long long int AUserID )
{
  quDB->ClearAll();
  quDB->SQL->Text = "call &PRABHUPADA_SCHEMA\"AfterLogon\"( :AUserID );";
  quDB->PrepareStandartMacros();
  quDB->DeclareAndSetParam( "AUserID", AUserID );
  quDB->ExecSQL();
}

void __fastcall TdmvNewNavadvipa::conDBAfterConnect(TObject *Sender)
{
  FUserID   = GetUserID( UserName );
  AfterLogon( UserID );
  rmDB->LoadRights();
  lmDB->LoadLanguages();
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::rrDataRight( TObject *Sender )
{
  NNV::TBoolVector &Rights = rmDB->Rights;

  quUsers->UpdateOptions->ReadOnly        = !Rights[ NNRights::UserEdit ];
  quUserRights->UpdateOptions->ReadOnly   = !Rights[ NNRights::UserEdit ];
  quUserRoles->UpdateOptions->ReadOnly    = !Rights[ NNRights::UserEdit ];
  quRights->UpdateOptions->ReadOnly       = !Rights[ NNRights::RightsEdit ];
  quCommod->UpdateOptions->ReadOnly       = !Rights[ NNRights::CommodEdit ];
  quColor->UpdateOptions->ReadOnly        = !Rights[ NNRights::ColorEdit ];
  quRole->UpdateOptions->ReadOnly         = !Rights[ NNRights::RoleEdit ];
  quRoleRights->UpdateOptions->ReadOnly   = !Rights[ NNRights::RoleEdit ];
  quLanguages->UpdateOptions->ReadOnly    = !Rights[ NNRights::LanguagesEdit ];
  quLanguageKind->UpdateOptions->ReadOnly = !Rights[ NNRights::LanguageStringEdit ];
  quLanguage->UpdateOptions->ReadOnly     = !Rights[ NNRights::LanguageStringEdit ];
  quTranslate->UpdateOptions->ReadOnly    = !Rights[ NNRights::LanguageStringEdit ];
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::dsLanguageDataChange( TObject *Sender, TField *Field )

{
  if ( quLanguageKindKindID->AsLargeInt != quLanguageKindID->AsLargeInt && !quLanguage->IsWorkFilter )
    quLanguageKind->CWLocate( "KindID", quLanguageKindID->AsLargeInt );
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::quLanguageNewRecord( TDataSet *DataSet )
{
  quLanguageKindID->AsLargeInt = quLanguageKindKindID->AsLargeInt;
}
//---------------------------------------------------------------------------

void __fastcall TdmvNewNavadvipa::quTranslateNewRecord( TDataSet *DataSet )
{
  quTranslateLanguageID->AsLargeInt = quLanguageEntityID->AsLargeInt;
  quTranslateTranslate->AsString = quLanguageOriginal->AsString;
}
//---------------------------------------------------------------------------

