// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef VCL_NNComboBoxDateTimeH
#define VCL_NNComboBoxDateTimeH
//---------------------------------------------------------------------------
#include "VCL_NNComboBox.h"
#include "VCL_NNCommon.h"

class PACKAGE TNNVComboBoxDateTime : public TNNVComboBox
{
private:
  using inherited = TNNVComboBox;
  TDateTime FDateTime;
  String FFormatStr;
  bool FColorApply;
  TColor FSColor;
  TColor SFColor;
  bool FNeedTime;
  bool FIsUserCanChangeCheckStyle;
  NNV::TCheckStyleValue FCheckStyle = NNV::TCheckStyleValue::Equal;
  NNV::TVectorCheckStyleValue FVectorCheckStyleValue = { NNV::TCheckStyleValue::None
                                                       , NNV::TCheckStyleValue::Equal
                                                       , NNV::TCheckStyleValue::Greater
                                                       , NNV::TCheckStyleValue::GreaterOrEqual
                                                       , NNV::TCheckStyleValue::Less
                                                       , NNV::TCheckStyleValue::LessOrEqual };
  NNV::TCheckStyleSetKind FCheckStyleSetKind = NNV::TCheckStyleSetKind::FullSetWithoutNone;
  NNV::TVectorCheckStyleValue::iterator FCurrentIteratorCheckStyle;
  bool FIsEmpty = false;
  void __fastcall SetCheckStyleSetKind( NNV::TCheckStyleSetKind Value );
  void __fastcall SetCheckStyle( NNV::TCheckStyleValue Value );
  void __fastcall DoPrepare( TObject* Sender );
  void __fastcall DoExecuteDialog( TObject* Sender );
  void __fastcall SetDateTime( TDateTime Value );
  void __fastcall SetFormatStr( String Value );
  void __fastcall SetNeedTime( bool Value );
  MESSAGE void __fastcall CMExit( TCMExit &Message );
  void __fastcall TextToDateTime();
  TDateTime __fastcall InitialDateTime();
  void __fastcall SyncEditMaskAndFormatStr();
  String __fastcall PrefixCheckEdit();
  void __fastcall NextCheckStyleDateTime();
  bool __fastcall GetIsEmpty();
  __property NNV::TVectorCheckStyleValue VectorCheckStyleValue = { read = FVectorCheckStyleValue };
protected:
  virtual void __fastcall SetIsEmpty( bool Value );
  virtual void __fastcall ButtonClick( TComponent *SenderForm );
  DYNAMIC void __fastcall KeyDown( Word &Key, TShiftState Shift );
  DYNAMIC void __fastcall Change();
  virtual void __fastcall Loaded(void);
  //virtual void __fastcall CreateWnd(void);
  virtual bool __fastcall IsNull() { return false; };
public:
  __fastcall TNNVComboBoxDateTime( TComponent* Owner );
  __fastcall ~TNNVComboBoxDateTime();
  //virtual void __fastcall ClearDateTime();
  void __fastcall RestoreColor();
  bool __fastcall TextEmptyDate();
  void __fastcall TextRefresh();
  __property bool IsEmpty = { read = FIsEmpty, write = SetIsEmpty };
  __property TDateTime DateTime = { read = FDateTime, write = SetDateTime };
__published:
  __property String FormatStr = { read = FFormatStr, write = SetFormatStr, stored = false };
  __property bool NeedTime = { read = FNeedTime, write = SetNeedTime, default = true };
  __property EditMask = { stored = false };
  __property Text = { stored = false };
  __property bool IsUserCanChangeCheckStyle = { read = FIsUserCanChangeCheckStyle, write = FIsUserCanChangeCheckStyle, default = false };
  __property NNV::TCheckStyleValue CheckStyle = { read = FCheckStyle, write = SetCheckStyle, default = NNV::TCheckStyleValue::None };
  __property NNV::TCheckStyleSetKind CheckStyleSetKind = { read = FCheckStyleSetKind, write = SetCheckStyleSetKind, default = NNV::TCheckStyleSetKind::FullSet };
#pragma option push -w-inl
BEGIN_MESSAGE_MAP
  VCL_MESSAGE_HANDLER( CM_EXIT, TCMExit, CMExit );
END_MESSAGE_MAP(inherited);
#pragma option pop // -w-inl
};
//---------------------------------------------------------------------------
#endif

