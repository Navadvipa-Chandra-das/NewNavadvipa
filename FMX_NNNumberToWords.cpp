//---------------------------------------------------------------------------
#include <fmx.h>

#pragma hdrstop

#include "FMX_NNNumberToWords.h"
#if (!__ANDROID__)
#pragma resource "*.res"
#endif
#pragma package(smart_init)

const char* CW_DEFAULT_RUBL1     = "рубль";
const char* CW_DEFAULT_RUBL24    = "рубля";
const char* CW_DEFAULT_RUBL5     = "рублей";
const char* CW_DEFAULT_COPYICA1  = "копейка";
const char* CW_DEFAULT_COPYICA24 = "копейки";
const char* CW_DEFAULT_COPYICA5  = "копеек";

//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck( TNNFNumberToWords * )
{
  new TNNFNumberToWords(NULL);
}
//---------------------------------------------------------------------------
__fastcall TNNFNumberToWords::TNNFNumberToWords( TComponent* Owner )
    : inherited( Owner )
{
  fRubl1         = CW_DEFAULT_RUBL1;
  fRubl24        = CW_DEFAULT_RUBL24;
  fRubl5         = CW_DEFAULT_RUBL5;
  fCopyica1      = CW_DEFAULT_COPYICA1;
  fCopyica24     = CW_DEFAULT_COPYICA24;
  fCopyica5      = CW_DEFAULT_COPYICA5;
  fRublGender    = NNF::wgFemale;
  fCopyicaGender = NNF::wgFemale;
  fLenCopyica    = 2;
  fNeedCopyica   = True;
  fCopyicaKind   = ckNumber;
}
bool __fastcall TNNFNumberToWords::IsDRubl1()
{
  return Rubl1 != CW_DEFAULT_RUBL1;
}
bool __fastcall TNNFNumberToWords::IsDRubl24()
{
  return Rubl24 != CW_DEFAULT_RUBL24;
}
bool __fastcall TNNFNumberToWords::IsDRubl5()
{
  return Rubl5 != CW_DEFAULT_RUBL5;
}
bool __fastcall TNNFNumberToWords::IsDCopyica1()
{
  return Copyica1 != CW_DEFAULT_COPYICA1;
}
bool __fastcall TNNFNumberToWords::IsDCopyica24()
{
  return Copyica24 != CW_DEFAULT_COPYICA24;
}
bool __fastcall TNNFNumberToWords::IsDCopyica5()
{
  return Copyica5 != CW_DEFAULT_COPYICA5;
}
void __fastcall TNNFNumberToWords::SetValue( String Value )
{
  if ( Value != fValue ) {
    fValue = NNF::RemoveChar( Value, FormatSettings.ThousandSeparator );
    fValue = NNF::RoundString( fValue, LenCopyica );
    GenText();
  }
}
void __fastcall TNNFNumberToWords::GenText()
{
  int N;
  String SN, S;
  bool B;
  NNF::TNumWordDiapazon D;
  String T[3];
  SN = Value;
  N = 1;
  T[0] = Rubl1;
  T[1] = Rubl24;
  T[2] = Rubl5;
  fText = NNF::SToStr( NNF::GetToken( SN, N, FormatSettings.DecimalSeparator ), RublGender, T, true );
  if ( ( NeedCopyica ) || ( N < SN.Length() + 1 ) ) {
    S = NNF::GetToken( SN, N, FormatSettings.DecimalSeparator );
    S = S + String::StringOfChar('0', LenCopyica - S.Length() );
    T[0] = Copyica1;
    T[1] = Copyica24;
    T[2] = Copyica5;
    switch ( CopyicaKind ) {
      case ckWord :
        fText = fText + ' ' + NNF::SToStr( S, CopyicaGender, T, false );
        break;
      default :
        N = S.Length();
        if ( N > 1 ) B = ( S[N-1] == '1' );
        else B = false;
        D = NNF::NumDiapazon( S[ N ], B );
        fText = fText + ' ' + S;
        switch ( D ) {
          case NNF::wdOne : S = Copyica1; break;
          case NNF::wdTwoFourth : S = Copyica24; break;
          default : S = Copyica5;
        }
        fText = fText + ' ' + S;
    }
  }
  Change();
}
void __fastcall TNNFNumberToWords::SetRubl1( String value )
{
  if ( Rubl1 != value ) {
    fRubl1 = value;
    RefreshText();
  }
}
void __fastcall TNNFNumberToWords::SetRubl24( String value )
{
  if ( Rubl24 != value ) {
    fRubl24 = value;
    RefreshText();
  }
}
void __fastcall TNNFNumberToWords::SetRubl5( String value )
{
  if ( Rubl5 != value ) {
    fRubl5 = value;
    RefreshText();
  }
}
void __fastcall TNNFNumberToWords::SetCopyica1( String value )
{
  if ( Copyica1 != value ) {
    fCopyica1 = value;
    RefreshText();
  }
}
void __fastcall TNNFNumberToWords::SetCopyica24( String value )
{
  if ( Copyica24 != value ) {
    fCopyica24 = value;
    RefreshText();
  }
}
void __fastcall TNNFNumberToWords::SetCopyica5( String value )
{
  if ( Copyica5 != value ) {
    fCopyica5 = value;
    RefreshText();
  }
}
void __fastcall TNNFNumberToWords::SetRublGender( NNF::TGender value )
{
  if ( RublGender != value ) {
    fRublGender = value;
    RefreshText();
  }
}
void __fastcall TNNFNumberToWords::SetCopyicaGender( NNF::TGender value )
{
  if ( CopyicaGender != value ) {
    fCopyicaGender = value;
    RefreshText();
  }
}
void __fastcall TNNFNumberToWords::SetLenCopyica( int value )
{
  if ( LenCopyica != value ) {
    fLenCopyica = value;
    RefreshText();
  }
}
void __fastcall TNNFNumberToWords::SetNeedCopyica( bool value )
{
  if ( NeedCopyica != value ) {
    fNeedCopyica = value;
    RefreshText();
  }
}
void __fastcall TNNFNumberToWords::SetCopyicaKind( TCopyicaKind value )
{
  if ( CopyicaKind != value ) {
    fCopyicaKind = value;
    RefreshText();
  }
}
//---------------------------------------------------------------------------
namespace Fmx_nnnumbertowords
{

void __fastcall PACKAGE Register()
{
  TComponentClass classes[ 1 ] = { __classid( TNNFNumberToWords ) };
  RegisterComponents( L"FMX New Navadvipa", classes, 0 );
}

}
//---------------------------------------------------------------------------
