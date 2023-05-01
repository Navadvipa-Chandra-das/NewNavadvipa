// ---------------------------------------------------------------------------

#ifndef VCL_NNFmStoryDataH
#define VCL_NNFmStoryDataH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.CheckLst.hpp>
//#include <Vcl.ComCtrls.hpp>
//#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include "VCL_NNPanel.h"
#include "VCL_NNActionList.h"
#include "VCL_NNDBMiracle.h"
#include "VCL_NNFlagBox.h"
#include "VCL_NNFmRes.h"
#include "VCL_NNRightsManager.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "VCL_NNLanguageManager.h"

// ---------------------------------------------------------------------------
class TfmvStoryData : public TfmvRes {
__published: // IDE-managed Components
  TNNVPanel *paB;
  TToolBar *ToolBar1;
  TToolButton *tbAllSelect;
  TToolButton *tbNoneSelect;
  TToolButton *tbInvertSelect;
  TCheckListBox *clData;
  TAction *aAllSelect;
  TAction *aNoneSelect;
  TAction *aInvertSelect;
  TToolButton *ToolButton1;
  TAction *aOK;
  TAction *aCancel;
  TToolButton *tbOK;
  TToolButton *ToolButton3;

  void __fastcall aAllSelectExecute(TObject *Sender);
  void __fastcall aNoneSelectExecute(TObject *Sender);
  void __fastcall aInvertSelectExecute(TObject *Sender);
  void __fastcall aOKExecute(TObject *Sender);
  void __fastcall aCancelExecute(TObject *Sender);

private: // User declarations
  using inherited = TfmvRes;
public: // User declarations
  __fastcall TfmvStoryData( TComponent* Owner );
};

// ---------------------------------------------------------------------------
extern PACKAGE TfmvStoryData *fmvStoryData;
// ---------------------------------------------------------------------------
#endif
