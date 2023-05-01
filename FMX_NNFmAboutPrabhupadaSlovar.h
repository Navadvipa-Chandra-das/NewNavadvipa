//---------------------------------------------------------------------------

#ifndef FMX_NNFmAboutPrabhupadaSlovarH
#define FMX_NNFmAboutPrabhupadaSlovarH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "FMX_NNDBMiracle.h"
#include "FMX_NNFmRes.h"
#include <FMX.Layouts.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.ScrollBox.hpp>
#include "FMX_NNFlagBox.h"
#include "FMX_NNLanguageManager.h"
#include "FMX_NNRightsManager.h"
#include "FMX_NNActionList.h"
#include <FMX.ActnList.hpp>
#include <System.Actions.hpp>
//---------------------------------------------------------------------------
class TfmfAboutPrabhupadaSlovar : public TfmfRes
{
__published:	// IDE-managed Components
  TLayout *laB;
  TLayout *laC;
  TTabControl *tcPrabhupadaAbout;
  TTabItem *tiPrabhupadaPhoto;
  TTabItem *tiPrabhupadaLila;
  TTabItem *tiHelp;
  TTabItem *tiLetter;
  TButton *buClose;
  TImageControl *icPrabhupada;
  TMemo *mePrabhupadaLila;
  TMemo *meHelp;
  TMemo *meLetter;
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall coResDefault(TObject *Sender);
  void __fastcall buCloseClick(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
  using inherited = TfmfRes;
public:		// User declarations
  __fastcall TfmfAboutPrabhupadaSlovar(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmfAboutPrabhupadaSlovar *fmfAboutPrabhupadaSlovar;
//---------------------------------------------------------------------------
#endif
