//---------------------------------------------------------------------------

#ifndef VCL_NNFrDiapazonH
#define VCL_NNFrDiapazonH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VCL_NNComboBox.h"
#include "VCL_NNComboBoxDateTime.h"
#include <Vcl.Mask.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Menus.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
//---------------------------------------------------------------------------
class TfrvDiapazon : public TFrame
{
__published:	// IDE-managed Components
  TToolBar *tbrDiapazon;
  TPopupMenu *pmDiapazonKind;
  TActionList *alDiapazon;
  TAction *aDiapazonKindInner;
  TAction *aDiapazonKindOuter;
  TAction *aDiapazonKindHalfDiapazon;
  TMenuItem *mipDiapazonKindInner;
  TMenuItem *mipDiapazonKindOuter;
  TMenuItem *mipDiapazonKindHalhDiapazon;
  TAction *aSetDiapazon;
  TAction *aDiapazonKindNull;
  TAction *aDiapazonKindNotNull;
  TMenuItem *mipDiapazonNull;
  TMenuItem *mipDiapazonNotNull;
  TAction *aClearDiapazon;
  TMenuItem *mipClearDiapazon;
  TMenuItem *mipSeparatorClear;
  void __fastcall aDiapazonKindInnerExecute( TObject *Sender );
  void __fastcall aDiapazonKindOuterExecute( TObject *Sender );
  void __fastcall aDiapazonKindHalfDiapazonExecute( TObject *Sender );
  void __fastcall aDiapazonKindNullExecute(TObject *Sender);
  void __fastcall aDiapazonKindNotNullExecute(TObject *Sender);
  void __fastcall aClearDiapazonExecute(TObject *Sender);
private:	// User declarations
  using inherited = TFrame;
  NNV::TDiapazonKind FDiapazonKind = NNV::TDiapazonKind::Outer;
  void __fastcall SetDiapazonKind( NNV::TDiapazonKind Value );
protected:
  virtual void __fastcall SetOnBeginEndEnter( TNotifyEvent Value ) {};
  virtual void __fastcall SyncDiapazonKind() {};
  virtual bool __fastcall GetIsEmpty() { return false; };
  virtual void __fastcall SetIsEmpty( bool Value ) {};
  virtual void __fastcall Loaded();
  virtual TWinControl* __fastcall GetBeginControl() { return nullptr; };
  virtual TWinControl* __fastcall GetEndControl() { return nullptr; };
public:		// User declarations
  __fastcall TfrvDiapazon( TComponent* Owner );
  __property NNV::TDiapazonKind DiapazonKind = { read = FDiapazonKind, write = SetDiapazonKind, default = NNV::TDiapazonKind::Inner };
  __property bool IsEmpty = { read = GetIsEmpty, write = SetIsEmpty };
  __property TNotifyEvent OnBeginEndEnter = { write = SetOnBeginEndEnter };
  __property TWinControl* BeginControl = { read = GetBeginControl };
  __property TWinControl* EndControl = { read = GetEndControl };
};
//---------------------------------------------------------------------------
extern PACKAGE TfrvDiapazon *frvDiapazon;
//---------------------------------------------------------------------------
#endif
