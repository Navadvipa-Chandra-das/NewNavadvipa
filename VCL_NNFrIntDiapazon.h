//---------------------------------------------------------------------------

#ifndef VCL_NNFrIntDiapazonH
#define VCL_NNFrIntDiapazonH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VCL_NNFrDiapazon.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ToolWin.hpp>
#include "VCL_NNComboBox.h"
#include "VCL_NNNumberEdit.h"
#include <Vcl.Mask.hpp>
//---------------------------------------------------------------------------
class TfrvIntDiapazon : public TfrvDiapazon
{
__published:	// IDE-managed Components
  TAction *aApplyDiapazon;
  TNNVNumberEdit *neBegin;
  TNNVNumberEdit *neEnd;
  TToolButton *tbApplyDiapazon;
  void __fastcall aApplyDiapazonExecute(TObject *Sender);
private:	// User declarations
  using inherited = TfrvDiapazon;
  NNV::TIntDiapazon FIntDiapazon;
  void __fastcall SetIntDiapazon( NNV::TIntDiapazon Value );
protected:
  virtual void __fastcall SetOnBeginEndEnter( TNotifyEvent Value );
  virtual void __fastcall SyncDiapazonKind();
  virtual bool __fastcall GetIsEmpty();
  virtual void __fastcall SetIsEmpty( bool Value );
  virtual TWinControl* __fastcall GetBeginControl() { return neBegin; };
  virtual TWinControl* __fastcall GetEndControl() { return neEnd; };
public:		// User declarations
  __fastcall TfrvIntDiapazon(TComponent* Owner);
  __property NNV::TIntDiapazon IntDiapazon = { read = FIntDiapazon, write = SetIntDiapazon };
};
//---------------------------------------------------------------------------
extern PACKAGE TfrvIntDiapazon *frvIntDiapazon;
//---------------------------------------------------------------------------
#endif
