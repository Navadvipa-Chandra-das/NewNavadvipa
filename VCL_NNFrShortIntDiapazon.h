//---------------------------------------------------------------------------

#ifndef VCL_NNFrShortIntDiapazonH
#define VCL_NNFrShortIntDiapazonH
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
class TfrvShortIntDiapazon : public TfrvDiapazon
{
__published:	// IDE-managed Components
  TAction *aApplyDiapazon;
  TNNVNumberEdit *neEnd;
  TNNVNumberEdit *neBegin;
  TToolButton *tbApplyDiapazon;
  void __fastcall aApplyDiapazonExecute(TObject *Sender);
private:	// User declarations
  using inherited = TfrvDiapazon;
  NNV::TShortIntDiapazon FShortIntDiapazon;
  void __fastcall SetShortIntDiapazon( NNV::TShortIntDiapazon Value );
protected:
  virtual void __fastcall SetOnBeginEndEnter( TNotifyEvent Value );
  virtual void __fastcall SyncDiapazonKind();
  virtual bool __fastcall GetIsEmpty();
  virtual void __fastcall SetIsEmpty( bool Value );
  virtual TWinControl* __fastcall GetBeginControl() { return neBegin; };
  virtual TWinControl* __fastcall GetEndControl() { return neEnd; };
public:		// User declarations
  __fastcall TfrvShortIntDiapazon(TComponent* Owner);
  __property NNV::TShortIntDiapazon ShortIntDiapazon = { read = FShortIntDiapazon, write = SetShortIntDiapazon };
};
//---------------------------------------------------------------------------
extern PACKAGE TfrvShortIntDiapazon *frvShortIntDiapazon;
//---------------------------------------------------------------------------
#endif
