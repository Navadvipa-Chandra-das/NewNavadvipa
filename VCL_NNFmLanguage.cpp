//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFmLanguage.h"
#include "VCL_NNDmNewNavadvipa.h"
#include "VCL_NNFmLanguages.h"
#include "VCL_NNFormAdmin.h"
#include <memory>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNActionList"
#pragma link "VCL_NNDateTimeDialog"
#pragma link "VCL_NNDialogExec"
#pragma link "VCL_NNFlagBox"
#pragma link "VCL_NNFmDB"
#pragma link "VCL_NNPageControl"
#pragma link "VCL_NNPanel"
#pragma link "VCL_NNRightsManager"
#pragma link "VCL_NNSplitter"
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNLanguageManager"
#pragma link "VCL_NNDialog"
#pragma resource "*.dfm"
TfmvLanguage *fmvLanguage;
//---------------------------------------------------------------------------
__fastcall TfmvLanguage::TfmvLanguage( TComponent* Owner )
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::FindID( long long int ALanguageID )
{
  long long int AKindID = dmvNewNavadvipa->EntityIDToKindID( ALanguageID );

  if ( dmvNewNavadvipa->quLanguageKindKindID->AsLargeInt != AKindID )
    dmvNewNavadvipa->quLanguageKind->CWLocate( "KindID", AKindID );

  dmvNewNavadvipa->quLanguage->FilterMap.EraseFilterSearch();

  if ( dmvNewNavadvipa->quLanguageEntityID->AsLargeInt != ALanguageID )
    dmvNewNavadvipa->quLanguage->CWLocate( "EntityID", ALanguageID );
}

void __fastcall TfmvLanguage::coResLoad( TObject *Sender )
{
  inherited::coResLoad( Sender );
  LoadNodeAdmins();
  LoadTrees();
  LoadGrids();
  tvLanguage->Width = coRes->Filer->ReadInt();
  paLanguageB->Height = coRes->Filer->ReadInt();
  paLanguageBB->Height = coRes->Filer->ReadInt();
  dmeSlovo->Width = coRes->Filer->ReadInt();
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::coResSave( TObject *Sender )
{
  inherited::coResSave( Sender );
  SaveNodeAdmins();
  SaveTrees();
  SaveGrids();
  coRes->Filer->WriteInt( tvLanguage->Width );
  coRes->Filer->WriteInt( paLanguageB->Height );
  coRes->Filer->WriteInt( paLanguageBB->Height );
  coRes->Filer->WriteInt( dmeSlovo->Width );
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::LoadNodeAdmins()
{
  naLanguageKind->LoadFromFiler( coRes->Filer );
}

void __fastcall TfmvLanguage::SaveNodeAdmins()
{
  naLanguageKind->SaveToFiler( coRes->Filer );
}

void __fastcall TfmvLanguage::LoadTrees()
{
  tvLanguage->LoadFromFiler( coRes->Filer );
}

void __fastcall TfmvLanguage::SaveTrees()
{
  tvLanguage->SaveToFiler( coRes->Filer );
}

void __fastcall TfmvLanguage::LoadGrids()
{
  dgLanguage->LoadFromFiler( coRes->Filer );
  dgTranslate->LoadFromFiler( coRes->Filer );
}

void __fastcall TfmvLanguage::SaveGrids()
{
  dgLanguage->SaveToFiler( coRes->Filer );
  dgTranslate->SaveToFiler( coRes->Filer );
}

void __fastcall TfmvLanguage::coResEndLoad( TObject *Sender )
{
  splLanguage->Left = tvLanguage->Left + tvLanguage->Width + 1;
  splLanguageB->Top = paLanguageB->Top - 1;
  splLanguageBB->Top = paLanguageBB->Top - 1;
  splSlovo->Left = dmeSlovo->Left + dmeSlovo->Width + 1;
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::FormCreate( TObject *Sender )
{
  inherited::FormCreate( Sender );

  tvLanguage->StartAdmin();
  PrepareLanguageOwner();
  SetOnGetDialogFormsBecauseBug();
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::SetOnGetDialogFormsBecauseBug()
{
  DLanguages->OnGetDialogForm  = DLanguagesGetDialogForm;
}

void __fastcall TfmvLanguage::FormDestroy( TObject *Sender )
{
  inherited::FormDestroy( Sender );

  tvLanguage->FinishAdmin();
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::SetLanguageOwner( TComponent *Value )
{
  if ( FLanguageOwner != Value ) {
    FLanguageOwner = Value;
    cbLanguageOwner->ItemIndex = cbLanguageOwner->Items->IndexOfObject( LanguageOwner );
  }
}

void __fastcall TfmvLanguage::PrepareLanguageOwner()
{
  std::unique_ptr< TStringList > sl( new TStringList );
  String CN;
  int i;
  for ( i = 0; i < Screen->FormCount; i++ ) {
    CN = Screen->Forms[ i ]->ClassName();
    if ( sl->IndexOf( CN ) == -1 )
      sl->AddObject( CN, Screen->Forms[ i ] );
  }
  for ( i = 0; i < Screen->DataModuleCount; i++ ) {
    CN = Screen->DataModules[ i ]->ClassName();
    if ( sl->IndexOf( CN ) == -1 )
      sl->AddObject( CN, Screen->DataModules[ i ] );
  }
  sl->Sort();

  cbLanguageOwner->Items->Assign( sl.get() );
}

void __fastcall TfmvLanguage::dgLanguageDBCut( TObject *Sender )
{
  dgLanguage->CWSelect( dmvNewNavadvipa->quLanguageEntityID, &dmvNewNavadvipa->BufferIntBox, true );
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::dgLanguageDBPaste( TObject *Sender )
{
  dmvNewNavadvipa->quLanguage->DBPaste( dmvNewNavadvipa->BufferIntBox, dmvNewNavadvipa->quDB, dmvNewNavadvipa->quLanguageKindKindID );
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::dgLanguageDrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
  if ( !State.Contains( gdFocused ) && !dgLanguage->IsCurrentSelected() ) {
    TField *f = dmvNewNavadvipa->quLanguageKindID;
    if ( !f->IsNull )
      dmvNewNavadvipa->DBGridColor( dgLanguage, f->AsLargeInt );
  }
  dgLanguage->DefaultDrawColumnCell( Rect, DataCol, Column, State );
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::naLanguageKindFirstEnter( TObject *Sender )
{
  dmvNewNavadvipa->quLanguageKind->CWOpen();
  dmvNewNavadvipa->quLanguage->CWOpen();
  dmvNewNavadvipa->quTranslate->CWOpen();
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::naLanguageKindLastExit( TObject *Sender )
{
  dmvNewNavadvipa->quLanguage->CWClose();
  dmvNewNavadvipa->quLanguageKind->CWClose();
  dmvNewNavadvipa->quTranslate->CWClose();
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::naLanguageKindEnter( TObject *Sender )
{
  DataSet = dmvNewNavadvipa->quLanguageKind;
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::naLanguageKindGetNodeParams( TObject *Sender, TNNVNodeParams &NodeParams )
{
  dmvNewNavadvipa->SetNodeParamsLanguageKind( NodeParams );
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::naLanguageKindLoadNodes( TObject *Sender )
{
  tvLanguage->LoadNodeAdmin( nullptr, naLanguageKind, NNV::RootLanguageKindID );
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::CloseValid()
{
  inherited::CloseValid();
  FillMultiResult( dgLanguage, dmvNewNavadvipa->quLanguageEntityID, dmvNewNavadvipa->quLanguageEntity );
}

void __fastcall TfmvLanguage::dgTranslateDBCut( TObject *Sender )
{
  dgTranslate->CWSelect( dmvNewNavadvipa->quTranslateTranslateID, &dmvNewNavadvipa->BufferIntBox, true );
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::dgTranslateDBCopy( TObject *Sender )
{
  dgTranslate->CWSelect( dmvNewNavadvipa->quTranslateTranslateID, &dmvNewNavadvipa->BufferIntBox, false );
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::dgTranslateDBPaste( TObject *Sender )
{
  dmvNewNavadvipa->quTranslate->DBPaste( dmvNewNavadvipa->BufferIntBox, dmvNewNavadvipa->quDB, dmvNewNavadvipa->quLanguageEntityID );
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::aPrepareOwnerWordsExecute( TObject *Sender )
{
  if ( dmvNewNavadvipa->lmDB->CurrentLanguageID == NNVConst::MainLanguageID )
    dmvNewNavadvipa->lmDB->PrepareOwnerWords( LanguageOwner
                                            , dmvNewNavadvipa->InsertLanguageRow
                                            , dmvNewNavadvipa->PrepareLanguageOwner
                                            , dmvNewNavadvipa->UnPrepareLanguageOwner );
  else
    ShowMessage( L"Пожалуйста, сделайте текущим основной язык программы!" );
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::cbLanguageOwnerChange( TObject *Sender )
{
  LanguageOwner = dynamic_cast< TComponent* >( cbLanguageOwner->Items->Objects[ cbLanguageOwner->ItemIndex ] );
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::aSelectNonLatinicaExecute( TObject *Sender )
{
  dgLanguage->SelectRows( IsNonLatinica );
}
//---------------------------------------------------------------------------

bool __fastcall TfmvLanguage::IsNonLatinica()
{
  String S = dmvNewNavadvipa->quLanguageOriginal->AsString;
  int L = S.Length();

  for ( int i = 1; i <= L; ++i )
    if ( S[ i ] > 123 )
      return false;

  return true;
}

void __fastcall TfmvLanguage::DLanguagesGetDialogForm( TObject *Sender, TCustomForm *&fm )
{
  NNVFormList.New( __classid( TfmvLanguages ), &fmvLanguages, this );
  fm = fmvLanguages;
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::DLanguagesPrepare( TObject *Sender )
{
  fmvLanguages->FindID( dmvNewNavadvipa->quTranslateLanguagesID->AsLargeInt );
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguage::DLanguagesExecute( TObject *Sender )
{
  fmvLanguages->MultiResultExecute( dmvNewNavadvipa->quTranslate
                                  , dmvNewNavadvipa->quTranslateLanguagesID
                                  , dmvNewNavadvipa->quTranslateLanguages );
}
//---------------------------------------------------------------------------

