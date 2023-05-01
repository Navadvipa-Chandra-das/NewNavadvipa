                                            // ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFmStoryData.h"
#include "VCL_NNDmNewNavadvipa.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNPanel"
#pragma link "VCL_NNActionList"
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNFlagBox"
#pragma link "VCL_NNFmRes"
#pragma link "VCL_NNRightsManager"
#pragma link "VCL_NNLanguageManager"
#pragma resource "*.dfm"
TfmvStoryData *fmvStoryData;

// ---------------------------------------------------------------------------
__fastcall TfmvStoryData::TfmvStoryData( TComponent* Owner )
  : inherited( Owner )
{
}
// ---------------------------------------------------------------------------

void __fastcall TfmvStoryData::aAllSelectExecute( TObject *Sender )
{
  int L = clData->Items->Count;
  for ( int i = 0; i < L; ++i )
    clData->Checked[i] = true;
}
// ---------------------------------------------------------------------------

void __fastcall TfmvStoryData::aNoneSelectExecute( TObject *Sender )
{
  int L = clData->Items->Count;
  for ( int i = 0; i < L; ++i )
    clData->Checked[i] = false;
}
// ---------------------------------------------------------------------------

void __fastcall TfmvStoryData::aInvertSelectExecute( TObject *Sender )
{
  int L = clData->Items->Count;
  for ( int i = 0; i < L; ++i )
    clData->Checked[i] = !clData->Checked[i];
}
// ---------------------------------------------------------------------------

void __fastcall TfmvStoryData::aOKExecute(TObject *Sender)
{
  CloseDialog( true );
}
//---------------------------------------------------------------------------


void __fastcall TfmvStoryData::aCancelExecute(TObject *Sender)
{
  CloseDialog( false );
}
//---------------------------------------------------------------------------

