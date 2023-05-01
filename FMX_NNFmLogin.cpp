//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "FMX_NNFmLogin.h"
#include "FMX_NNDmNewNavadvipa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FMX_NNActionList"
#pragma link "FMX_NNDBMiracle"
#pragma link "FMX_NNFlagBox"
#pragma link "FMX_NNFmRes"
#pragma link "FMX_NNLanguageManager"
#pragma link "FMX_NNRightsManager"
#pragma link "FMX_NNFrLogin"
#pragma resource "*.fmx"
TfmfLogin *fmfLogin;
//---------------------------------------------------------------------------
__fastcall TfmfLogin::TfmfLogin( TComponent* Owner )
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

void __fastcall TfmfLogin::Loaded()
{
  inherited::Loaded();

  coRes->StaticRegistryKey = NNFConst::PrabhupadaSlovarFiles + coRes->StaticRegistryKey;
}

void __fastcall TfmfLogin::coResLoad( TObject *Sender )
{
  inherited::coResLoad( Sender );
  frfLogin->LoadFromFiler( coRes->Filer );
}
//---------------------------------------------------------------------------

void __fastcall TfmfLogin::coResSave( TObject *Sender )
{
  inherited::coResSave( Sender );
  frfLogin->SaveToFiler( coRes->Filer );
}
//---------------------------------------------------------------------------

void __fastcall TfmfLogin::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
  frfLogin->FormKeyDown( Sender, Key, Shift );
}
//---------------------------------------------------------------------------

void __fastcall TfmfLogin::ShowFormLogin( TFDConnection *AConnection )
{
  frfLogin->Connection = AConnection;

  if ( ShowModal() != mrOk ) {
    Application->Terminate();
    Application->ProcessMessages();
  }

  coRes->Enabled = AConnection->Connected;
}

