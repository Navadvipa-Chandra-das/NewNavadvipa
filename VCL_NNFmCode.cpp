//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFmCode.h"
#include "VCL_NNDmNewNavadvipa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNActionList"
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNFlagBox"
#pragma link "VCL_NNFmRes"
#pragma link "VCL_NNRightsManager"
#pragma link "VCL_NNLanguageManager"
#pragma resource "*.dfm"
TfmvCode *fmvCode;
//---------------------------------------------------------------------------
__fastcall TfmvCode::TfmvCode(TComponent* Owner)
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

void __fastcall TfmvCode::FormKeyDown( TObject *Sender, WORD &Key, TShiftState Shift )
{
  if ( Key == VK_ESCAPE || Key == VK_RETURN ) {
    CloseDialog( false );
    Key = 0;
  }
}
//---------------------------------------------------------------------------

