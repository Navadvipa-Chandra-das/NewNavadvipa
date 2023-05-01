//---------------------------------------------------------------------------
#ifndef VCL_NNFmFormListH
#define VCL_NNFmFormListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "VCL_NNFmRes.h"
#include "VCL_NNActionList.h"
#include "VCL_NNDBMiracle.h"
#include "VCL_NNFlagBox.h"
#include "VCL_NNRightsManager.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "VCL_NNLanguageManager.h"
//---------------------------------------------------------------------------
class TfmvFormList : public TfmvRes
{
__published:	// IDE-managed Components
  TListBox *lbForm;
  TButton *buOK;
  TButton *buCancel;
  void __fastcall lbFormDblClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
    TShiftState Shift);
  void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
    TShiftState Shift);
private:	// User declarations
  using inherited = TfmvRes;
  bool fClick;
public:		// User declarations
  __fastcall TfmvFormList(TComponent* Owner);
  TCustomForm* GetForm();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmvFormList *fmvFormList;
//---------------------------------------------------------------------------
#endif
