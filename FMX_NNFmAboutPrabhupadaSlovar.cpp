//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "FMX_NNFmAboutPrabhupadaSlovar.h"
#include "FMX_NNFmPrabhupadaSlovar.h"
#include "FMX_NNConst.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FMX_NNDBMiracle"
#pragma link "FMX_NNFmRes"
#pragma link "FMX_NNFlagBox"
#pragma link "FMX_NNLanguageManager"
#pragma link "FMX_NNRightsManager"
#pragma link "FMX_NNActionList"
#pragma resource "*.fmx"
TfmfAboutPrabhupadaSlovar *fmfAboutPrabhupadaSlovar;
//---------------------------------------------------------------------------
__fastcall TfmfAboutPrabhupadaSlovar::TfmfAboutPrabhupadaSlovar(TComponent* Owner)
  : inherited( Owner )
{
  tcPrabhupadaAbout->Images = fmfPrabhupadaSlovar->ilPrabhupadaSlovar;
}

//---------------------------------------------------------------------------
void __fastcall TfmfAboutPrabhupadaSlovar::FormClose( TObject *Sender, TCloseAction &Action )
{
  Action = TCloseAction::caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfmfAboutPrabhupadaSlovar::coResDefault(TObject *Sender)
{
  Position = TFormPosition::ScreenCenter;
}
//---------------------------------------------------------------------------

void __fastcall TfmfAboutPrabhupadaSlovar::buCloseClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TfmfAboutPrabhupadaSlovar::FormCreate( TObject *Sender )
{
  inherited::FormCreate( Sender );
  icPrabhupada->LoadFromFile( NNFConst::PrabhupadaSlovarFiles + L"Prabhupada.jpg" );
  mePrabhupadaLila->Lines->LoadFromFile( NNFConst::PrabhupadaSlovarFiles + L"PrabhupadaLila.txt" );
  meHelp->Lines->LoadFromFile( NNFConst::PrabhupadaSlovarFiles + L"Help.txt" );
  meLetter->Lines->LoadFromFile( NNFConst::PrabhupadaSlovarFiles + L"Letter.txt" );
}
//---------------------------------------------------------------------------


