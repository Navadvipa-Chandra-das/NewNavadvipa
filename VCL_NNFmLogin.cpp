// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFmLogin.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNFlagBox"
#pragma link "VCL_NNFmRes"
#pragma link "VCL_NNRightsManager"
#pragma link "VCL_NNFrLogin"
#pragma link "VCL_NNActionList"
#pragma link "VCL_NNLanguageManager"
#pragma resource "*.dfm"
TfmvLogin *fmvLogin;

// ---------------------------------------------------------------------------
__fastcall TfmvLogin::TfmvLogin( TComponent* Owner )
  : inherited( Owner )
{
}
// ---------------------------------------------------------------------------

void __fastcall TfmvLogin::coResLoad( TObject *Sender )
{
  inherited::coResLoad( Sender );
  frvLogin->LoadFromFiler( coRes->Filer );
}
// ---------------------------------------------------------------------------

void __fastcall TfmvLogin::coResSave( TObject *Sender )
{
  inherited::coResSave( Sender );
  frvLogin->SaveToFiler( coRes->Filer );
}
// ---------------------------------------------------------------------------

void __fastcall TfmvLogin::FormKeyDown( TObject *Sender, WORD &Key, TShiftState Shift )
{
  frvLogin->FormKeyDown( Sender, Key, Shift );
}
// ---------------------------------------------------------------------------

void __fastcall TfmvLogin::ShowFormLogin( TFDConnection *AConnection )
{
  frvLogin->Connection = AConnection;

  if ( ShowModal() != mrOk ) {
    Application->Terminate();
    Application->ProcessMessages();
  }

  coRes->Enabled = AConnection->Connected;
}

