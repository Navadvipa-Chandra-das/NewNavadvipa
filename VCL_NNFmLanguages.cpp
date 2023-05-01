//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFmLanguages.h"
#include "VCL_NNDmNewNavadvipa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNActionList"
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNDateTimeDialog"
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNDialogExec"
#pragma link "VCL_NNFlagBox"
#pragma link "VCL_NNFmDB"
#pragma link "VCL_NNLanguageManager"
#pragma link "VCL_NNPageControl"
#pragma link "VCL_NNPanel"
#pragma link "VCL_NNRightsManager"
#pragma resource "*.dfm"
TfmvLanguages *fmvLanguages;
//---------------------------------------------------------------------------
__fastcall TfmvLanguages::TfmvLanguages( TComponent* Owner )
  : inherited( Owner )
{
}

//---------------------------------------------------------------------------
void __fastcall TfmvLanguages::coResLoad( TObject *Sender )
{
  inherited::coResLoad( Sender );
  dgLanguages->LoadFromFiler( coRes->Filer );
}

//---------------------------------------------------------------------------
void __fastcall TfmvLanguages::coResSave( TObject *Sender )
{
  inherited::coResSave( Sender );
  dgLanguages->SaveToFiler( coRes->Filer );
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguages::FindID( long long int ALanguagesID )
{
  dmvNewNavadvipa->quLanguages->FilterMap.EraseFilterSearch();

  if ( dmvNewNavadvipa->quLanguagesLanguagesID->AsLargeInt != ALanguagesID )
    dmvNewNavadvipa->quLanguages->CWLocate( "LanguagesID", ALanguagesID );
}

void __fastcall TfmvLanguages::CloseValid()
{
  inherited::CloseValid();
  FillMultiResult( dgLanguages, dmvNewNavadvipa->quLanguagesLanguagesID, dmvNewNavadvipa->quLanguagesLanguages );
}

void __fastcall TfmvLanguages::FormCreate( TObject *Sender )
{
  dmvNewNavadvipa->quLanguages->CWOpen();
  inherited::FormCreate( Sender );
}
//---------------------------------------------------------------------------

void __fastcall TfmvLanguages::FormDestroy( TObject *Sender )
{
  inherited::FormDestroy( Sender );
  dmvNewNavadvipa->quLanguages->CWClose();
}
//---------------------------------------------------------------------------

