//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "FMX_NNFmLanguage.h"
#include "FMX_NNDmNewNavadvipa.h"
#include <memory>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FMX_NNDBMiracle"
#pragma link "FMX_NNFlagBox"
#pragma link "FMX_NNFmDB"
#pragma link "FMX_NNLanguageManager"
#pragma link "FMX_NNRightsManager"
#pragma link "FMX_NNActionList"
#pragma resource "*.fmx"
TfmfLanguage *fmfLanguage;
//---------------------------------------------------------------------------
__fastcall TfmfLanguage::TfmfLanguage(TComponent* Owner)
  : TfmfDB(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TfmfLanguage::coResLoad(TObject *Sender)
{
  inherited::coResLoad( Sender );

  grLanguages->Height = coRes->Filer->ReadInt();
  paL->Width = coRes->Filer->ReadInt();
  paCB->Height = coRes->Filer->ReadInt();

  PrepareLanguageOwner();
}
//---------------------------------------------------------------------------

void __fastcall TfmfLanguage::coResSave(TObject *Sender)
{
  inherited::coResSave( Sender );
  coRes->Filer->WriteInt( grLanguages->Height );
  coRes->Filer->WriteInt( paL->Width );
  coRes->Filer->WriteInt( paCB->Height );
}
//---------------------------------------------------------------------------

void __fastcall TfmfLanguage::coResEndLoad(TObject *Sender)
{
  splLanguages->Position->Y = grLanguages->Position->Y + grLanguages->Size->Height + 1;
  splLanguageKind->Position->X = paL->Position->X + paL->Size->Width + 1;
  splTranslate->Position->Y = paCB->Position->Y - 1;
}
//---------------------------------------------------------------------------

void __fastcall TfmfLanguage::PrepareLanguageOwner()
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

void __fastcall TfmfLanguage::aPrepareOwnerWordsExecute( TObject *Sender )
{
  if ( dmfNewNavadvipa->lmDB->CurrentLanguageID == NNFConst::MainLanguageID )
    dmfNewNavadvipa->lmDB->PrepareOwnerWords( LanguageOwner
                                            , dmfNewNavadvipa->InsertLanguageRow
                                            , dmfNewNavadvipa->PrepareLanguageOwner
                                            , dmfNewNavadvipa->UnPrepareLanguageOwner );
  else
    ShowMessage( L"Пожалуйста, сделайте текущим основной язык программы!" );
}
//---------------------------------------------------------------------------

void __fastcall TfmfLanguage::SetLanguageOwner( TComponent *Value )
{
  if ( FLanguageOwner != Value ) {
    FLanguageOwner = Value;
    cbLanguageOwner->ItemIndex = cbLanguageOwner->Items->IndexOfObject( LanguageOwner );
  }
}

void __fastcall TfmfLanguage::FormCreate( TObject *Sender )
{
  inherited::FormCreate( Sender );

  dmfNewNavadvipa->quLanguages->CWOpen();
  dmfNewNavadvipa->quLanguageKind->CWOpen();
  dmfNewNavadvipa->quLanguage->CWOpen();
  dmfNewNavadvipa->quTranslate->CWOpen();

}
//---------------------------------------------------------------------------

void __fastcall TfmfLanguage::FormDestroy( TObject *Sender )
{
  dmfNewNavadvipa->quLanguages->CWClose();
  dmfNewNavadvipa->quLanguageKind->CWClose();
  dmfNewNavadvipa->quLanguage->CWClose();
  dmfNewNavadvipa->quTranslate->CWClose();

  inherited::FormDestroy( Sender );
}
//---------------------------------------------------------------------------



