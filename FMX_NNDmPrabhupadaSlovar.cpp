//---------------------------------------------------------------------------

#pragma hdrstop

#include "FMX_NNDmPrabhupadaSlovar.h"
#include "FMX_NNFmLogin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "FMX.Controls.TControl"
#pragma link "FMX_NNDBMiracle"
#pragma link "FMX_NNDmRes"
#pragma link "FMX_NNLanguageManager"
#pragma link "FMX_NNRightsManager"
#pragma resource "*.dfm"
TdmfPrabhupadaSlovar *dmfPrabhupadaSlovar;

const String SuperUserName = L"Navadvipa Chandra das";

//---------------------------------------------------------------------------
__fastcall TdmfPrabhupadaSlovar::TdmfPrabhupadaSlovar(TComponent* Owner)
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

void __fastcall TdmfPrabhupadaSlovar::DoLogin( TObject* Sender, TFDConnection *AConnection )
{
  AConnection->Params->UserName                     = SuperUserName;
  AConnection->Params->Database                     = L"NewNavadvipa";
  AConnection->Params->Values[ "Server" ]           = L"127.0.0.1";
  AConnection->Params->Values[ "Port" ]             = 5432;
  AConnection->Params->Values[ "PrabhupadaSchema" ] = L"\"NewNavadvipa\".";

  fmfLogin = new TfmfLogin( Application );
  fmfLogin->ShowFormLogin( AConnection );
}

