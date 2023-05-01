// Nizhnyaya Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef FMX_NNStrUtilH
#define FMX_NNStrUtilH

#include "FMX_NNSearchOption.h"
#include "FMX_NNConst.h"
#include <map>
#include <set>

//---------------------------------------------------------------------------

namespace NNF {

using TCharCharMap = std::map< WideChar, WideChar >;
using TStrStrMap   = std::map< String,   String >;

class TMistakeBox
{
public:
  TMistakeBox();
  TCharCharMap CharMap;
  TStrStrMap StrUpper;
  TStrStrMap StrLower;
};

class TSerialBox
{
public:
  TSerialBox();
  TCharCharMap CharMap;
};

class TWordBox
{
public:
  TWordBox();
  TCharCharMap CharMap;
};

PACKAGE enum TGender { wgMale,wgAvg,wgFemale };
PACKAGE enum TNumWordDiapazon { wdOne, wdTwoFourth, wdFive };

using TCharSet = PACKAGE std::set< WideChar >;

// Удаляет из S символы Chars
extern PACKAGE String __fastcall RemoveChar( String S, const String Chars );
extern PACKAGE String  __fastcall SToStr( String S, TGender AGender, String A[3], bool FirstUpper );
extern PACKAGE String __fastcall GetToken( const String &S, int &Pos, const char &Delim );
extern PACKAGE int __fastcall CharCount( const String &S, WideChar C );
extern PACKAGE String __fastcall ReplaceStr( const String &S, const String Srch, const String Replace );
extern PACKAGE void __fastcall ReplaceChar( WideChar *c, const WideChar Srch, const WideChar Replace );
extern PACKAGE String __fastcall LikeStr( const String &S );
extern PACKAGE void __fastcall MistakeStr( String &R, bool CaseInSensitive );
extern PACKAGE TNumWordDiapazon __fastcall NumDiapazon( const char &C, bool B );
extern PACKAGE bool __fastcall Compare( String sub_str, String s
                                      , NNF::TSearchOptions &Options );
extern PACKAGE String __fastcall TrimBChar( const String S, WideChar C );
extern PACKAGE String __fastcall TrimEChar( const String S, WideChar C );
extern PACKAGE bool __fastcall IsStringEmpty( const String &S );
extern PACKAGE String __fastcall FormatFloat( String S );
extern PACKAGE String __fastcall FormatStr( int Numdec );
extern PACKAGE String __fastcall SampleFormatStr( int Numdec );
extern PACKAGE String __fastcall FloatFormat( double Value, int Numdec );
extern PACKAGE String __fastcall SampleFloatFormat( double Value, int Numdec );
extern PACKAGE String __fastcall RoundString( String S, int D );
extern PACKAGE String __fastcall FormatFloatDec( String S, int D );
extern PACKAGE String __fastcall RPad( const String &S, int L, char C = ' ' );
extern PACKAGE String __fastcall LPad( const String &S, int L, char C = ' ' );
extern PACKAGE String __fastcall VariableToken( char *&P );
extern PACKAGE bool __fastcall IsMask( NNFConst::char_mask mask, const AnsiString &P );
extern PACKAGE bool __fastcall IsSerial( const String &P );
extern PACKAGE String __fastcall ConvertSerial( const String &S );
extern PACKAGE String __fastcall ConvertWord( const String &S );
extern PACKAGE int __fastcall MinimumLength( int Value, int Normal, int NotValidMinimum );

// Сравнивает маску t со строкой s
template < class CharType >
extern PACKAGE bool __fastcall Like( CharType *t, CharType *s );
extern PACKAGE bool ArtfulName( const String &Name_ );
extern PACKAGE bool __fastcall CompareAccept( String Template, String Accept );
extern PACKAGE String __fastcall PropertyNumField( const String &FieldName_
                                                 , const String &PropertyNum_
                                                 , const String &Prefix_ );

}

#endif

