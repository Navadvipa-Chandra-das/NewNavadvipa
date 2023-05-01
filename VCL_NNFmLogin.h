// ---------------------------------------------------------------------------

#ifndef VCL_NNFmLoginH
#define VCL_NNFmLoginH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <FireDAC.Comp.Client.hpp>
#include "VCL_NNDBMiracle.h"
#include "VCL_NNFlagBox.h"
#include "VCL_NNFmRes.h"
#include "VCL_NNRightsManager.h"
#include "VCL_NNFrLogin.h"
#include "VCL_NNActionList.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "VCL_NNLanguageManager.h"

// ---------------------------------------------------------------------------
class TfmvLogin : public TfmvRes {
__published: // IDE-managed Components
  TfrvLogin *frvLogin;

  void __fastcall coResLoad(TObject *Sender);
  void __fastcall coResSave(TObject *Sender);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private: // User declarations
  using inherited = TfmvRes;

public: // User declarations
  __fastcall TfmvLogin(TComponent* Owner);
  void __fastcall ShowFormLogin( TFDConnection *AConnection );
};

// ---------------------------------------------------------------------------
extern PACKAGE TfmvLogin *fmvLogin;
// ---------------------------------------------------------------------------
#endif
