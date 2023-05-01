//---------------------------------------------------------------------------

#ifndef VCL_NNFrPeriodH
#define VCL_NNFrPeriodH
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
#include "VCL_NNComboBoxDateTime.h"
#include <Vcl.Mask.hpp>
//---------------------------------------------------------------------------
class TfrvPeriod : public TfrvDiapazon
{
__published:	// IDE-managed Components
  TNNVComboBoxDateTime *cbdBegin;
  TNNVComboBoxDateTime *cbdEnd;
  TAction *aApplyDiapazon;
  TToolButton *tbApplyDiapazon;
  void __fastcall aApplyDiapazonExecute(TObject *Sender);
private:	// User declarations
  using inherited = TfrvDiapazon;
  NNV::TPeriod FPeriod;
  bool FNeedTime = false;
  void __fastcall SetNeedTime( bool Value );
  void __fastcall SetPeriod( NNV::TPeriod Value );
protected:
  virtual void __fastcall SetOnBeginEndEnter( TNotifyEvent Value );
  virtual void __fastcall SyncDiapazonKind();
  virtual bool __fastcall GetIsEmpty();
  virtual void __fastcall SetIsEmpty( bool Value );
  virtual TWinControl* __fastcall GetBeginControl() { return cbdBegin; };
  virtual TWinControl* __fastcall GetEndControl() { return cbdEnd; };
public:		// User declarations
  __fastcall TfrvPeriod( TComponent* Owner );
  __property NNV::TPeriod Period = { read = FPeriod, write = SetPeriod };
  __property bool NeedTime = { read = FNeedTime, write = SetNeedTime };
};
//---------------------------------------------------------------------------
extern PACKAGE TfrvPeriod *frvPeriod;
//---------------------------------------------------------------------------
#endif
