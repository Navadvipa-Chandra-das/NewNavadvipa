//---------------------------------------------------------------------------

#ifndef FMX_NNNumberToWordsH
#define FMX_NNNumberToWordsH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "FMX_NNStrUtil.h"
//---------------------------------------------------------------------------

PACKAGE enum TCopyicaKind { ckWord, ckNumber };

class PACKAGE TNNFNumberToWords : public TComponent
{
private:
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
  NNF::TGender fRublGender;
  NNF::TGender fCopyicaGender;
  int fLenCopyica;
  bool fNeedCopyica;
  TCopyicaKind fCopyicaKind;
  void __fastcall SetValue( String Value );
  bool __fastcall IsDRubl1();
  bool __fastcall IsDRubl24();
  bool __fastcall IsDRubl5();
  bool __fastcall IsDCopyica1();
  bool __fastcall IsDCopyica24();
  bool __fastcall IsDCopyica5();
  void __fastcall GenText();
  inline void __fastcall RefreshText() { GenText(); Change(); };
  void __fastcall SetRubl1( String value );
  void __fastcall SetRubl24( String value );
  void __fastcall SetRubl5( String value );
  void __fastcall SetCopyica1( String value );
  void __fastcall SetCopyica24( String value );
  void __fastcall SetCopyica5( String value );
  void __fastcall SetRublGender( NNF::TGender value );
  void __fastcall SetCopyicaGender( NNF::TGender value );
  void __fastcall SetLenCopyica( int value );
  void __fastcall SetNeedCopyica( bool value );
  void __fastcall SetCopyicaKind( TCopyicaKind value );
protected:
  virtual void __fastcall Change() { if ( fOnChange ) fOnChange( this ); };
public:
  __fastcall TNNFNumberToWords( TComponent* Owner );
  __property String Text = { read = fText };
__published:
  __property String Rubl1 = { read = fRubl1, write = SetRubl1, stored = IsDRubl1 };
  __property String Rubl24 = { read = fRubl24, write = SetRubl24, stored = IsDRubl24 };
  __property String Rubl5 = { read = fRubl5, write = SetRubl5, stored = IsDRubl5 };
  __property String Copyica1 = { read = fCopyica1, write = SetCopyica1, stored = IsDCopyica1 };
  __property String Copyica24 = { read = fCopyica24, write = SetCopyica24, stored = IsDCopyica24 };
  __property String Copyica5 = { read = fCopyica5, write = SetCopyica5, stored = IsDCopyica5 };
  __property String Value = { read = fValue, write = SetValue };
  __property NNF::TGender RublGender = { read = fRublGender, write = SetRublGender, default = NNF::wgFemale };
  __property NNF::TGender CopyicaGender = { read = fCopyicaGender, write = SetCopyicaGender, default = NNF::wgFemale };
  __property int LenCopyica = { read = fLenCopyica, write = SetLenCopyica, default = 2 };
  __property bool NeedCopyica = { read = fNeedCopyica, write = SetNeedCopyica, default = true };
  __property TCopyicaKind CopyicaKind = { read = fCopyicaKind, write = SetCopyicaKind, default = ckNumber };
  __property TNotifyEvent OnChange = { read = fOnChange, write = fOnChange };
};
//---------------------------------------------------------------------------
#endif
