// ---------------------------------------------------------------------------

#ifndef VCL_NNNumberToWordsH
#define VCL_NNNumberToWordsH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "VCL_NNStrUtil.h"
// ---------------------------------------------------------------------------

PACKAGE enum TCopyicaKind
{
  ckWord
, ckNumber
};

class PACKAGE TNNVNumberToWords : public TComponent {
  using inherited = TComponent;
  String fText;
  String fRubl1;
  String fRubl24;
  String fRubl5;
  String fCopyica1;
  String fCopyica24;
  String fCopyica5;
  String fValue;
  TNotifyEvent fOnChange;

  NNV::TGender fRublGender = NNV::wgMale;
  NNV::TGender fCopyicaGender = NNV::wgFemale;

  int fLenCopyica = 2;
  bool fNeedCopyica = true;
  TCopyicaKind fCopyicaKind = ckNumber;
  bool FNeedFirstUpper = true;

  void __fastcall SetValue(String Value);
  bool __fastcall IsDRubl1();
  bool __fastcall IsDRubl24();
  bool __fastcall IsDRubl5();
  bool __fastcall IsDCopyica1();
  bool __fastcall IsDCopyica24();
  bool __fastcall IsDCopyica5();
  void __fastcall GenText();
  inline void __fastcall RefreshText() {
    GenText();
    DoChange();
  };
  void __fastcall SetRubl1(String Value);
  void __fastcall SetRubl24(String Value);
  void __fastcall SetRubl5(String Value);
  void __fastcall SetCopyica1(String Value);
  void __fastcall SetCopyica24(String Value);
  void __fastcall SetCopyica5(String Value);
  void __fastcall SetRublGender(NNV::TGender Value);
  void __fastcall SetCopyicaGender(NNV::TGender Value);
  void __fastcall SetLenCopyica(int Value);
  void __fastcall SetNeedCopyica(bool Value);
  void __fastcall SetCopyicaKind(TCopyicaKind Value);
protected:
  virtual void __fastcall DoChange();
public:
  __fastcall TNNVNumberToWords( TComponent* Owner );
__published:
  __property String Text = {read = fText};
__published:
  __property String Rubl1 = { read = fRubl1, write = SetRubl1, stored = IsDRubl1 };
  __property String Rubl24 = { read = fRubl24, write = SetRubl24, stored = IsDRubl24 };
  __property String Rubl5 = { read = fRubl5, write = SetRubl5, stored = IsDRubl5 };
  __property String Copyica1 = { read = fCopyica1, write = SetCopyica1, stored = IsDCopyica1 };
  __property String Copyica24 = { read = fCopyica24, write = SetCopyica24, stored = IsDCopyica24 };
  __property String Copyica5 = { read = fCopyica5, write = SetCopyica5, stored = IsDCopyica5 };
  __property String Value = { read = fValue, write = SetValue };
  __property NNV::TGender RublGender = { read = fRublGender, write = SetRublGender, default = NNV::wgMale };
  __property NNV::TGender CopyicaGender = { read = fCopyicaGender, write = SetCopyicaGender, default = NNV::wgFemale };
  __property int LenCopyica = { read = fLenCopyica, write = SetLenCopyica, default = 2 };
  __property bool NeedCopyica = { read = fNeedCopyica, write = SetNeedCopyica, default = true };
  __property TCopyicaKind CopyicaKind = { read = fCopyicaKind, write = SetCopyicaKind, default = ckNumber };
  __property TNotifyEvent OnChange = { read = fOnChange, write = fOnChange };
  __property bool NeedFirstUpper = { read = FNeedFirstUpper, write = FNeedFirstUpper, default = true };
};
// ---------------------------------------------------------------------------
#endif
