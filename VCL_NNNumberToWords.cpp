// ---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "VCL_NNNumberToWords.h"
#pragma resource "*.res"
#pragma package(smart_init)

const char* CW_DEFAULT_RUBL1 = "рубль";
const char* CW_DEFAULT_RUBL24 = "рубля";
const char* CW_DEFAULT_RUBL5 = "рублей";
const char* CW_DEFAULT_COPYICA1 = "копейка";
const char* CW_DEFAULT_COPYICA24 = "копейки";
const char* CW_DEFAULT_COPYICA5 = "копеек";

// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNNVNumberToWords *) {
  new TNNVNumberToWords(NULL);
}

// ---------------------------------------------------------------------------
__fastcall TNNVNumberToWords::TNNVNumberToWords( TComponent* Owner )
    : inherited( Owner )
{
  fRubl1 = CW_DEFAULT_RUBL1;
  fRubl24 = CW_DEFAULT_RUBL24;
  fRubl5 = CW_DEFAULT_RUBL5;
  fCopyica1 = CW_DEFAULT_COPYICA1;
  fCopyica24 = CW_DEFAULT_COPYICA24;
  fCopyica5 = CW_DEFAULT_COPYICA5;
}

bool __fastcall TNNVNumberToWords::IsDRubl1()
{
  return Rubl1 != CW_DEFAULT_RUBL1;
}

bool __fastcall TNNVNumberToWords::IsDRubl24()
{
  return Rubl24 != CW_DEFAULT_RUBL24;
}

bool __fastcall TNNVNumberToWords::IsDRubl5()
{
  return Rubl5 != CW_DEFAULT_RUBL5;
}

bool __fastcall TNNVNumberToWords::IsDCopyica1()
{
  return Copyica1 != CW_DEFAULT_COPYICA1;
}

bool __fastcall TNNVNumberToWords::IsDCopyica24()
{
  return Copyica24 != CW_DEFAULT_COPYICA24;
}

bool __fastcall TNNVNumberToWords::IsDCopyica5()
{
  return Copyica5 != CW_DEFAULT_COPYICA5;
}

void __fastcall TNNVNumberToWords::SetValue( String Value )
{
  if (Value != fValue) {
    fValue = NNV::RemoveChar(Value, FormatSettings.ThousandSeparator);
    fValue = NNV::RoundString(fValue, LenCopyica);
    GenText();
  }
}

void __fastcall TNNVNumberToWords::GenText()
{
  int N;
  String SN, S;
  bool B;
  NNV::TNumWordDiapazon D;
  String T[3];
  SN = Value;
  N = 1;
  T[0] = Rubl1;
  T[1] = Rubl24;
  T[2] = Rubl5;
  fText = NNV::SToStr( NNV::GetToken( SN
                                    , N
                                    , FormatSettings.DecimalSeparator )
                     , RublGender
                     , T
                     , NeedFirstUpper );
  if ((NeedCopyica) || (N < SN.Length() + 1)) {
    S = NNV::GetToken(SN, N, FormatSettings.DecimalSeparator);
    S = S + String::StringOfChar('0', LenCopyica - S.Length());
    T[0] = Copyica1;
    T[1] = Copyica24;
    T[2] = Copyica5;
    switch (CopyicaKind) {
    case ckWord:
      fText = fText + ' ' + NNV::SToStr( S, CopyicaGender, T, false );
      break;
    default:
      N = S.Length();
      B = N > 1 ? S[ N - 1 ] == '1' : false;
      D = NNV::NumDiapazon(S[N], B);
      fText = fText + ' ' + S;
      switch ( D ) {
      case NNV::wdOne:
        S = Copyica1;
        break;
      case NNV::wdTwoFourth:
        S = Copyica24;
        break;
      default:
        S = Copyica5;
      }
      fText = fText + ' ' + S;
    }
  }
  DoChange();
}

void __fastcall TNNVNumberToWords::DoChange()
{
  if ( fOnChange )
    fOnChange( this );
};

void __fastcall TNNVNumberToWords::SetRubl1( String Value )
{
  if ( Rubl1 != Value ) {
    fRubl1 = Value;
    RefreshText();
  }
}

void __fastcall TNNVNumberToWords::SetRubl24( String Value )
{
  if ( Rubl24 != Value ) {
    fRubl24 = Value;
    RefreshText();
  }
}

void __fastcall TNNVNumberToWords::SetRubl5( String Value )
{
  if ( Rubl5 != Value ) {
    fRubl5 = Value;
    RefreshText();
  }
}

void __fastcall TNNVNumberToWords::SetCopyica1( String Value )
{
  if ( Copyica1 != Value ) {
    fCopyica1 = Value;
    RefreshText();
  }
}

void __fastcall TNNVNumberToWords::SetCopyica24( String Value )
{
  if ( Copyica24 != Value ) {
    fCopyica24 = Value;
    RefreshText();
  }
}

void __fastcall TNNVNumberToWords::SetCopyica5( String Value )
{
  if ( Copyica5 != Value ) {
    fCopyica5 = Value;
    RefreshText();
  }
}

void __fastcall TNNVNumberToWords::SetRublGender( NNV::TGender Value )
{
  if ( RublGender != Value ) {
    fRublGender = Value;
    RefreshText();
  }
}

void __fastcall TNNVNumberToWords::SetCopyicaGender( NNV::TGender Value )
{
  if ( CopyicaGender != Value ) {
    fCopyicaGender = Value;
    RefreshText();
  }
}

void __fastcall TNNVNumberToWords::SetLenCopyica( int Value )
{
  if ( LenCopyica != Value ) {
    fLenCopyica = Value;
    RefreshText();
  }
}

void __fastcall TNNVNumberToWords::SetNeedCopyica( bool Value )
{
  if ( NeedCopyica != Value ) {
    fNeedCopyica = Value;
    RefreshText();
  }
}

void __fastcall TNNVNumberToWords::SetCopyicaKind( TCopyicaKind Value )
{
  if ( CopyicaKind != Value ) {
    fCopyicaKind = Value;
    RefreshText();
  }
}

// ---------------------------------------------------------------------------
namespace Vcl_nnnumbertowords
{
  void __fastcall PACKAGE Register()
  {
    TComponentClass classes[ 1 ] = { __classid( TNNVNumberToWords ) };
    RegisterComponents( L"VCL New Navadvipa", classes, 0 );
  }
}
// ---------------------------------------------------------------------------
