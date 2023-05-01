// Nizhnyaya Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <fmx.h>
#pragma hdrstop

#include "FMX_NNStrUtil.h"
#include "FMX_NNConst.h"
#include "FMX_NNCommon.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace NNF {

TMistakeBox::TMistakeBox()
{
  // upper char
  CharMap.insert( std::make_pair( 'О', 'А' ) );
  CharMap.insert( std::make_pair( 'И', 'Е' ) );
  CharMap.insert( std::make_pair( 'С', 'З' ) );
  CharMap.insert( std::make_pair( 'Ю', 'У' ) );
  // меняем английское I на украинское І
  CharMap.insert( std::make_pair( 'I', 'І' ) );
  // меняем украинское Ї на украинское І
  CharMap.insert( std::make_pair( 'Ї', 'І' ) );
  CharMap.insert( std::make_pair( 'Ё', 'Е' ) );
  // lower char
  CharMap.insert( std::make_pair( 'о', 'а' ) );
  CharMap.insert( std::make_pair( 'и', 'е' ) );
  CharMap.insert( std::make_pair( 'с', 'з' ) );
  CharMap.insert( std::make_pair( 'ю', 'у' ) );
  // меняем английское i на украинское і
  CharMap.insert( std::make_pair( 'i', 'і' ) );
  // меняем украинское ї на украинское і
  CharMap.insert( std::make_pair( 'ї', 'і' ) );
  CharMap.insert( std::make_pair( 'ё', 'е' ) );

  // upper str
  StrUpper.insert( std::make_pair( "СС", "С" ) );
  StrUpper.insert( std::make_pair( "НН", "Н" ) );

  // lower str
  StrLower.insert( std::make_pair( "сс", "с" ) );
  StrLower.insert( std::make_pair( "нн", "н" ) );
}

TSerialBox::TSerialBox()
{
  CharMap.insert( std::make_pair( 'А', 'F' ) );
  CharMap.insert( std::make_pair( 'Б', '<' ) );
  CharMap.insert( std::make_pair( 'В', 'D' ) );
  CharMap.insert( std::make_pair( 'Г', 'U' ) );
  CharMap.insert( std::make_pair( 'Д', 'L' ) );
  CharMap.insert( std::make_pair( 'Е', 'T' ) );
  CharMap.insert( std::make_pair( 'Ё', '~' ) );
  CharMap.insert( std::make_pair( 'Ж', ':' ) );
  CharMap.insert( std::make_pair( 'З', 'P' ) );
  CharMap.insert( std::make_pair( 'И', 'B' ) );
  CharMap.insert( std::make_pair( 'Й', 'Q' ) );
  CharMap.insert( std::make_pair( 'К', 'R' ) );
  CharMap.insert( std::make_pair( 'Л', 'K' ) );
  CharMap.insert( std::make_pair( 'М', 'V' ) );
  CharMap.insert( std::make_pair( 'Н', 'Y' ) );
  CharMap.insert( std::make_pair( 'О', 'J' ) );
  CharMap.insert( std::make_pair( 'П', 'G' ) );
  CharMap.insert( std::make_pair( 'Р', 'H' ) );
  CharMap.insert( std::make_pair( 'С', 'C' ) );
  CharMap.insert( std::make_pair( 'Т', 'N' ) );
  CharMap.insert( std::make_pair( 'У', 'E' ) );
  CharMap.insert( std::make_pair( 'Ш', 'I' ) );
  CharMap.insert( std::make_pair( 'Щ', 'O' ) );
  CharMap.insert( std::make_pair( 'Х', '{' ) );
  CharMap.insert( std::make_pair( 'Ч', 'X' ) );
  CharMap.insert( std::make_pair( 'Ц', 'W' ) );
  CharMap.insert( std::make_pair( 'Ф', 'A' ) );
  CharMap.insert( std::make_pair( 'Ы', 'S' ) );
  CharMap.insert( std::make_pair( 'Ь', 'M' ) );
  CharMap.insert( std::make_pair( 'Ъ', '}' ) );
  CharMap.insert( std::make_pair( 'Э', '"' ) );
  CharMap.insert( std::make_pair( 'Ю', '>' ) );
  CharMap.insert( std::make_pair( 'Я', 'Z' ) );
  CharMap.insert( std::make_pair( 'а', 'F' ) );
  CharMap.insert( std::make_pair( 'б', ',' ) );
  CharMap.insert( std::make_pair( 'в', 'D' ) );
  CharMap.insert( std::make_pair( 'г', 'U' ) );
  CharMap.insert( std::make_pair( 'д', 'L' ) );
  CharMap.insert( std::make_pair( 'е', 'T' ) );
  CharMap.insert( std::make_pair( 'ё', '`' ) );
  CharMap.insert( std::make_pair( 'ж', ';' ) );
  CharMap.insert( std::make_pair( 'з', 'P' ) );
  CharMap.insert( std::make_pair( 'и', 'B' ) );
  CharMap.insert( std::make_pair( 'й', 'Q' ) );
  CharMap.insert( std::make_pair( 'к', 'R' ) );
  CharMap.insert( std::make_pair( 'л', 'K' ) );
  CharMap.insert( std::make_pair( 'м', 'V' ) );
  CharMap.insert( std::make_pair( 'н', 'Y' ) );
  CharMap.insert( std::make_pair( 'о', 'J' ) );
  CharMap.insert( std::make_pair( 'п', 'G' ) );
  CharMap.insert( std::make_pair( 'р', 'H' ) );
  CharMap.insert( std::make_pair( 'с', 'C' ) );
  CharMap.insert( std::make_pair( 'т', 'N' ) );
  CharMap.insert( std::make_pair( 'у', 'E' ) );
  CharMap.insert( std::make_pair( 'ш', 'I' ) );
  CharMap.insert( std::make_pair( 'щ', 'O' ) );
  CharMap.insert( std::make_pair( 'х', '[' ) );
  CharMap.insert( std::make_pair( 'ч', 'X' ) );
  CharMap.insert( std::make_pair( 'ц', 'W' ) );
  CharMap.insert( std::make_pair( 'ф', 'A' ) );
  CharMap.insert( std::make_pair( 'ы', 'S' ) );
  CharMap.insert( std::make_pair( 'ь', 'M' ) );
  CharMap.insert( std::make_pair( 'ъ', ']' ) );
  CharMap.insert( std::make_pair( 'э', '\'' ) );
  CharMap.insert( std::make_pair( 'ю', '.' ) );
  CharMap.insert( std::make_pair( 'я', 'Z' ) );

  // Украинский язык
  CharMap.insert( std::make_pair( 'І', 'S' ) );
  CharMap.insert( std::make_pair( 'Ї', '}' ) );
  CharMap.insert( std::make_pair( 'і', 'S' ) );
  CharMap.insert( std::make_pair( 'ї', ']' ) );
}

TWordBox::TWordBox()
{
  CharMap.insert( std::make_pair( 'А', 'Ж' ) );
  CharMap.insert( std::make_pair( 'Б', 'З' ) );
  CharMap.insert( std::make_pair( 'В', 'И' ) );
  CharMap.insert( std::make_pair( 'Г', 'Й' ) );
  CharMap.insert( std::make_pair( 'Д', 'К' ) );
  CharMap.insert( std::make_pair( 'Е', 'Л' ) );
  CharMap.insert( std::make_pair( 'Ё', 'М' ) );
  CharMap.insert( std::make_pair( 'Ж', 'А' ) );
  CharMap.insert( std::make_pair( 'З', 'Б' ) );
  CharMap.insert( std::make_pair( 'И', 'В' ) );
  CharMap.insert( std::make_pair( 'Й', 'Г' ) );
  CharMap.insert( std::make_pair( 'К', 'Д' ) );
  CharMap.insert( std::make_pair( 'Л', 'Е' ) );
  CharMap.insert( std::make_pair( 'М', 'Ё' ) );
  CharMap.insert( std::make_pair( 'Н', 'Ч' ) );
  CharMap.insert( std::make_pair( 'О', 'Ц' ) );
  CharMap.insert( std::make_pair( 'П', 'Ф' ) );
  CharMap.insert( std::make_pair( 'Р', 'Ы' ) );
  CharMap.insert( std::make_pair( 'С', 'Ь' ) );
  CharMap.insert( std::make_pair( 'Т', 'Ъ' ) );
  CharMap.insert( std::make_pair( 'У', 'Э' ) );
  CharMap.insert( std::make_pair( 'Ш', 'Ю' ) );
  CharMap.insert( std::make_pair( 'Щ', 'Я' ) );
  CharMap.insert( std::make_pair( 'Х', 'Р' ) );
  CharMap.insert( std::make_pair( 'Ч', 'Н' ) );
  CharMap.insert( std::make_pair( 'Ц', 'О' ) );
  CharMap.insert( std::make_pair( 'Ф', 'П' ) );
  CharMap.insert( std::make_pair( 'Ы', 'Х' ) );
  CharMap.insert( std::make_pair( 'Ь', 'С' ) );
  CharMap.insert( std::make_pair( 'Ъ', 'Т' ) );
  CharMap.insert( std::make_pair( 'Э', 'У' ) );
  CharMap.insert( std::make_pair( 'Ю', 'Ш' ) );
  CharMap.insert( std::make_pair( 'Я', 'Щ' ) );
  CharMap.insert( std::make_pair( 'а', 'Ж' ) );
  CharMap.insert( std::make_pair( 'б', 'З' ) );
  CharMap.insert( std::make_pair( 'в', 'И' ) );
  CharMap.insert( std::make_pair( 'г', 'Й' ) );
  CharMap.insert( std::make_pair( 'д', 'К' ) );
  CharMap.insert( std::make_pair( 'е', 'Л' ) );
  CharMap.insert( std::make_pair( 'ё', 'М' ) );
  CharMap.insert( std::make_pair( 'ж', 'А' ) );
  CharMap.insert( std::make_pair( 'з', 'Б' ) );
  CharMap.insert( std::make_pair( 'и', 'В' ) );
  CharMap.insert( std::make_pair( 'й', 'Г' ) );
  CharMap.insert( std::make_pair( 'к', 'Д' ) );
  CharMap.insert( std::make_pair( 'л', 'Е' ) );
  CharMap.insert( std::make_pair( 'м', 'Ё' ) );
  CharMap.insert( std::make_pair( 'н', 'Ч' ) );
  CharMap.insert( std::make_pair( 'о', 'Ц' ) );
  CharMap.insert( std::make_pair( 'п', 'Ф' ) );
  CharMap.insert( std::make_pair( 'р', 'Ы' ) );
  CharMap.insert( std::make_pair( 'с', 'Ь' ) );
  CharMap.insert( std::make_pair( 'т', 'Ъ' ) );
  CharMap.insert( std::make_pair( 'у', 'Э' ) );
  CharMap.insert( std::make_pair( 'ш', 'Ю' ) );
  CharMap.insert( std::make_pair( 'щ', 'Я' ) );
  CharMap.insert( std::make_pair( 'х', 'Р' ) );
  CharMap.insert( std::make_pair( 'ч', 'Н' ) );
  CharMap.insert( std::make_pair( 'ц', 'О' ) );
  CharMap.insert( std::make_pair( 'ф', 'П' ) );
  CharMap.insert( std::make_pair( 'ы', 'Х' ) );
  CharMap.insert( std::make_pair( 'ь', 'С' ) );
  CharMap.insert( std::make_pair( 'ъ', 'Т' ) );
  CharMap.insert( std::make_pair( 'э', 'У' ) );
  CharMap.insert( std::make_pair( 'ю', 'Ш' ) );
  CharMap.insert( std::make_pair( 'я', 'Щ' ) );
  // Украинский язык
  CharMap.insert( std::make_pair( 'І', 'ї' ) );
  CharMap.insert( std::make_pair( 'Ї', 'і' ) );
  CharMap.insert( std::make_pair( 'і', 'Ї' ) );
  CharMap.insert( std::make_pair( 'ї', 'І' ) );
  // Английский язык
  CharMap.insert( std::make_pair( 'a', 'I' ) );
  CharMap.insert( std::make_pair( 'b', 'J' ) );
  CharMap.insert( std::make_pair( 'c', 'A' ) );
  CharMap.insert( std::make_pair( 'd', 'B' ) );
  CharMap.insert( std::make_pair( 'e', 'K' ) );
  CharMap.insert( std::make_pair( 'f', 'L' ) );
  CharMap.insert( std::make_pair( 'g', 'M' ) );
  CharMap.insert( std::make_pair( 'h', 'N' ) );
  CharMap.insert( std::make_pair( 'i', 'C' ) );
  CharMap.insert( std::make_pair( 'j', 'D' ) );
  CharMap.insert( std::make_pair( 'k', 'E' ) );
  CharMap.insert( std::make_pair( 'l', 'F' ) );
  CharMap.insert( std::make_pair( 'm', 'G' ) );
  CharMap.insert( std::make_pair( 'n', 'H' ) );
  CharMap.insert( std::make_pair( 'o', 'U' ) );
  CharMap.insert( std::make_pair( 'p', 'V' ) );
  CharMap.insert( std::make_pair( 'q', 'W' ) );
  CharMap.insert( std::make_pair( 'r', 'X' ) );
  CharMap.insert( std::make_pair( 's', 'Y' ) );
  CharMap.insert( std::make_pair( 't', 'Z' ) );
  CharMap.insert( std::make_pair( 'u', 'O' ) );
  CharMap.insert( std::make_pair( 'v', 'P' ) );
  CharMap.insert( std::make_pair( 'w', 'Q' ) );
  CharMap.insert( std::make_pair( 'x', 'R' ) );
  CharMap.insert( std::make_pair( 'y', 'S' ) );
  CharMap.insert( std::make_pair( 'z', 'T' ) );
  CharMap.insert( std::make_pair( 'A', 'I' ) );
  CharMap.insert( std::make_pair( 'B', 'J' ) );
  CharMap.insert( std::make_pair( 'C', 'A' ) );
  CharMap.insert( std::make_pair( 'D', 'B' ) );
  CharMap.insert( std::make_pair( 'E', 'K' ) );
  CharMap.insert( std::make_pair( 'F', 'L' ) );
  CharMap.insert( std::make_pair( 'G', 'M' ) );
  CharMap.insert( std::make_pair( 'H', 'N' ) );
  CharMap.insert( std::make_pair( 'I', 'C' ) );
  CharMap.insert( std::make_pair( 'J', 'D' ) );
  CharMap.insert( std::make_pair( 'K', 'E' ) );
  CharMap.insert( std::make_pair( 'L', 'F' ) );
  CharMap.insert( std::make_pair( 'M', 'G' ) );
  CharMap.insert( std::make_pair( 'N', 'H' ) );
  CharMap.insert( std::make_pair( 'O', 'U' ) );
  CharMap.insert( std::make_pair( 'P', 'V' ) );
  CharMap.insert( std::make_pair( 'Q', 'W' ) );
  CharMap.insert( std::make_pair( 'R', 'X' ) );
  CharMap.insert( std::make_pair( 'S', 'Y' ) );
  CharMap.insert( std::make_pair( 'T', 'Z' ) );
  CharMap.insert( std::make_pair( 'U', 'O' ) );
  CharMap.insert( std::make_pair( 'V', 'P' ) );
  CharMap.insert( std::make_pair( 'W', 'Q' ) );
  CharMap.insert( std::make_pair( 'X', 'R' ) );
  CharMap.insert( std::make_pair( 'Y', 'S' ) );
  CharMap.insert( std::make_pair( 'Z', 'T' ) );
  // Цифры
  CharMap.insert( std::make_pair( '0', '2' ) );
  CharMap.insert( std::make_pair( '1', '3' ) );
  CharMap.insert( std::make_pair( '2', '0' ) );
  CharMap.insert( std::make_pair( '3', '1' ) );
  CharMap.insert( std::make_pair( '4', '7' ) );
  CharMap.insert( std::make_pair( '5', '8' ) );
  CharMap.insert( std::make_pair( '6', '9' ) );
  CharMap.insert( std::make_pair( '7', '4' ) );
  CharMap.insert( std::make_pair( '8', '5' ) );
  CharMap.insert( std::make_pair( '9', '6' ) );
}

TMistakeBox MistakeBox;
TSerialBox  SerialBox;
TWordBox  WordBox;

const int H_STR = 11;
const char* MILLION_STR[ H_STR ][ wdFive + 1 ] =
    {
      { "тысяча",      "тысячи",       "тысяч"         },
      { "миллион",     "миллиона",     "миллионов"     },
      { "миллиард",    "миллиарда",    "миллиардов"    },
      { "триллион",    "триллиона",    "триллионов"    },
      { "квадриллион", "квадриллиона", "квадриллионов" },
      { "квинтиллион", "квинтиллиона", "квинтиллионов" },
      { "секстиллион", "секстиллиона", "секстиллионов" },
      { "септиллион",  "септиллиона",  "септиллионов"  },
      { "окталлион",   "окталлиона",   "окталлионов"   },
      { "ноналлион",   "ноналлиона",   "ноналлионов"   },
      { "дециллион",   "дециллиона",   "дециллионов"   }
    };
const char* LIMON_STR[ 3 ] =
    {
      "-лион' ", "-лиона' ", "-лионов' "
    };
const char* ONE_GENDER[ 3 ] =
    {
      "один ", "одно ", "одна "
    };
const char* TWO_GENDER[ 3 ] =
    {
      "два ", "два " , "две "
    };
const char* SOTKA[ 9 ] =
    {
      "сто ", "двести ", "триста ", "четыреста ", "пятьсот ", "шестьсот ", "семьсот ", "восемьсот ", "девятьсот "
    };
const char* DESYATKA[ 10 ] =
    {
      "десять ",     "одиннадцать ", "двенадцать ", "тринадцать ",   "четырнадцать ",
      "пятнадцать ", "шестнадцать ", "семнадцать ", "восемнадцать ", "девятнадцать "
    };
const char* DVADCATKA[ 8 ] =
    {
      "двадцать ",   "тридцать ",  "сорок ",       "пятьдесят ",
      "шестьдесят ", "семьдесят ", "восемьдесят ", "девяносто "
    };
const char* EDINICA[ 7 ] =
     { "три ",  "четыре ", "пять ", "шесть ", "семь ", "восемь ", "девять " };

const char* ZERO = "ноль ";
const char* MINUS = "минус ";

String __fastcall RemoveChar( String S, const String Chars )
{
  for( int i = S.Length(); i > 0; i-- )
    if ( Chars.Pos( S[ i ] ) != 0 )
      S.Delete( i, 1 );
  return S;
}

String __fastcall GetToken( const String &S, int &Pos, const char &Delim )
{
  String Result;
  WideChar* I = S.c_str() + Pos;
  --I;
  while ( (*I) && ( *I != Delim ) )
    ++I;
  int N = I - S.c_str();
  N -= Pos;
  Result = S.SubString( Pos, ++N );
  if ( *I == Delim )
    ++I;
  Pos = I - S.c_str();
  ++Pos;
  return Result;
}

int __fastcall CharCount( const String &S, WideChar C )
{
  int Result = 0, L = S.Length();
  for( int i = 1; i <= L; ++i )
    if ( S[ i ] == C )
      Result++;
  return Result;
}

String __fastcall ReplaceStr( const String &S, const String Srch, const String Replace )
{
  int I, N;
  String Source, Result;

  Source = S;
  N = Srch.Length();
  Result = "";
  do {
    I = Source.Pos( Srch );
    if ( I > 0 ) {
      Result = Result + Source.SubString( 1, I - 1 ) + Replace;
      Source = Source.SubString( I + N, MaxInt );
    } else
      Result = Result + Source;
  } while ( I > 0 );
  return Result;
}

void __fastcall ReplaceChar( WideChar *c, const WideChar Srch, const WideChar Replace )
{
  while( *c ) {
    if ( *c == Srch )
      *c = Replace;
    ++c;
  }
}

template < class CharType >
bool __fastcall Like( CharType *t, CharType *s )
{
  if ( !(*t) ) return true;
  CharType *tt, *ss;
  while ( (*t) && (*s) ) {
    if ( (*t) == NNFConst::CharPercent ) {
      tt = ++t;
      ss = s;
      while ( (*ss) ) if ( Like( tt, ss++ ) ) return true;
      return false;
    }
    if ( ( (*t) != (*s) ) && ( (*t) != NNFConst::CharUnderline ) ) return false;
    t++;
    s++;
  }
  if ( (*s) ) return false;
  if ( !(*t) ) return true;
  do {
    if ( (*t) != NNFConst::CharPercent ) return false;
  } while ( (*(++t)) );
  return true;
}

String __fastcall LikeStr( const String &S )
{
  String R( S );

  R = NNF::ReplaceStr( R, NNFConst::StrCharPercent,   "%" );
  R = NNF::ReplaceStr( R, NNFConst::StrCharUnderline, "_" );

  return R;
}

void __fastcall MistakeStr( String &R, bool CaseInSensitive )
{
  NNF::TCharCharMap::iterator i;
  NNF::TStrStrMap::iterator j;
  for ( j = NNF::MistakeBox.StrUpper.begin(); j != NNF::MistakeBox.StrUpper.end(); ++j )
    R = ReplaceStr( R, (*j).first, (*j).second );
  if ( !CaseInSensitive )
    for ( j = NNF::MistakeBox.StrLower.begin(); j != NNF::MistakeBox.StrLower.end(); ++j )
      R = ReplaceStr( R, (*j).first, (*j).second );
  for ( WideChar *c = R.c_str(); *c; ++c ) {
    i = NNF::MistakeBox.CharMap.find( *c );
    if ( i != NNF::MistakeBox.CharMap.end() )
      *c = (*i).second;
  }
}

TNumWordDiapazon __fastcall NumDiapazon( const char &C, bool B )
{
  if ( B )
    return wdFive;
  else
    switch ( C ) {
      case '1' :
        return wdOne;
      case '2' : case '3' : case '4' :
        return wdTwoFourth;
      default :
        return wdFive;
    }
}

void __fastcall BadCharError( char C )
{
  throw Exception( NNFConst::TheSymbol + String( C ) + NNFConst::IsInadmissibleInLine );
}

String __fastcall TroykaToStr( String &S
                             , int P
                             , TGender AGender
                             , TNumWordDiapazon &ADiapazon )
{
  bool B = false;
  String Result;
  String T[3] = { "", "", "" };

 Result = "";
  switch ( S[1] ) {
    case '0' : break; // ничего не делаем
    case '1' : case '2' : case '3' : case '4' : case '5' :
    case '6' : case '7' : case '8' : case '9' :
      Result = Result + SOTKA[ (unsigned char)( S[ 1 ] ) - 49 ];
      break;
    default : BadCharError( S[1] );
  }
  switch ( S[2] ) {
    case '0' : break; // ничего не делаем
    case '1' :
      if ( S[3] >= '0' && S[3] <= '9' )
        Result = Result + DESYATKA[ (unsigned char)( S[ 3 ] ) - 48 ];
      else BadCharError( S[3] );
      B = true;
      break;
    case '2' : case '3' : case '4' : case '5' : case '6' : case '7' :
    case '8' : case '9' :
      Result = Result + DVADCATKA[ (unsigned char)( S[ 2 ] ) - 50 ];
      break;
    default :
      BadCharError( S[2] );
  }
  if ( ! B )
    switch ( S[3] ) {
      case '0' : break; // ничего не делаем
      case '1' :
        switch ( P ) {
          case 0 :
            Result = Result + ONE_GENDER[ AGender ];
            break;
          case 1 :
            Result = Result + ONE_GENDER[ wgFemale ];
            break;
          default : Result = Result + ONE_GENDER[ wgMale ];
        }
        break;
      case '2' :
        switch ( P ) {
          case 0 :
            Result = Result + TWO_GENDER[ AGender ];
            break;
          case 1 :
            Result = Result + TWO_GENDER[ wgFemale ];
            break;
          default : Result = Result + TWO_GENDER[ wgMale ];
        }
        break;
      case '3' : case '4' : case '5' : case '6' :
      case '7' : case '8' : case '9' :
        Result = Result + EDINICA[ (unsigned char)( S[ 3 ] ) - 51 ];
        break;
      default :
        BadCharError( S[3] );
    }
  if ( Result == "" ) return Result;
  if ( P == 0 )
    ADiapazon  = NumDiapazon( S[ 3 ], B );
  else if ( ( P >= 1 ) && ( P <= H_STR ) )
    Result = Result + MILLION_STR[ P - 1 ][ NumDiapazon( S[ 3 ], B ) ] + " ";
  else
    Result = Result + "''" + SToStr( IntToStr( P - 1 ), wgMale, T, false ) +
             LIMON_STR[ NumDiapazon( S[ 3 ], B ) ];
  return Result;
}

String __fastcall SToStr( String S
                        , TGender AGender
                        , String A[3]
                        , bool FirstUpper )
{
  int I, N;
  TNumWordDiapazon ADiapazon ;
  String Result, m;
  bool IsMinus = false;

  if ( !S.IsEmpty() && S[ 1 ] == '-' ) {
    S.Delete( 1, 1 );
    IsMinus = true;
  }
  Result = "";
  ADiapazon  = wdFive;
  N = S.Length();
  if ( ( N % 3 ) != 0 ) {
    S = String::StringOfChar('0', 3 - ( N % 3 ) ) + S;
    N = S.Length();
  }
  for ( I = ( N / 3 ); I > 0; I-- ) {
    m = S.SubString( N - I * 3 + 1, 3 );
    Result = Result +
      TroykaToStr( m, I - 1, AGender, ADiapazon );
  }
  if ( Result == "" ) Result = ZERO;
  Result = Result + A[ ADiapazon ];
  if ( FirstUpper ) Result = UpperCase( Result[1] ) + Result.SubString( 2, MaxInt );
  if ( IsMinus ) Result = MINUS + Result;
  return Result;
}

bool __fastcall Compare( String sub_str, String s
                       , NNF::TSearchOptions &Options )
{
  bool result;
  bool CaseInSensitive = Options.IsSoft || !Options.CaseSensitive;
  if ( CaseInSensitive ) {
    s       = UpperCase( s );
    sub_str = UpperCase( sub_str );
  }
  if ( Options.IsSoft ) {
    s       = RemoveChar( s, " \"'" );
    sub_str = RemoveChar( sub_str, " \"'" );
  }
  if ( Options.IsMistake ) {
    MistakeStr( s, CaseInSensitive );
    MistakeStr( sub_str, CaseInSensitive );
  }
  if ( Options.AnyEntry ) {
    sub_str = sub_str + NNFConst::StrCharPercent;
    sub_str = NNFConst::StrCharPercent + sub_str;
  }
  if ( !(*sub_str.c_str()) ) result = true;
  else result = NNF::Like( sub_str.c_str(), s.c_str() );
  return Options.NotThis ? !result : result;
}

String __fastcall TrimBChar( const String S, WideChar C )
{
  int i = 1, L = S.Length();

  while ( ( i <= L ) && ( S[ i ] == C ) ) i++;
  return S.SubString( i, MaxInt);
}

String __fastcall TrimEChar( const String S, WideChar C )
{
  int i = S.Length();

  while ( ( i > 0 ) && ( S[ i ] == C ) )
    i--;
  return S.SubString( 1, i );
}

bool __fastcall IsStringEmpty( const String &S )
{
  if ( S.IsEmpty() )
    return true;
  else {
    int L = S.Length();
    for ( int i = 0; i < L; ++i )
      if ( S[ i ] != ' ' || S[ i ] != '\t' )
        return false;
  }
  return true;
}

String __fastcall FormatFloat( String S )
{
  String R, result;
  int N, i;
  if ( S.IsEmpty() || S == "-" ) return "0";
  bool B = S[ 1 ] == '-';
  if ( B ) S = S.SubString( 2, S.Length() - 1 );
  N = S.Pos( FormatSettings.DecimalSeparator );
  i = ( N == 0 ? S.Length() - 2 : N - 3 );
  while ( i > -3 ) {
    result = String( FormatSettings.ThousandSeparator ) +
      S.SubString( ( i <= 0 ? 1 : i ), ( i <= 0 ? 2 + i : 3 ) ) + result;
    i -= 3;
  }
  if ( N ) result = result + String( FormatSettings.DecimalSeparator ) +
    S.SubString( N + 1, S.Length() - N );
  result = TrimBChar( result, FormatSettings.ThousandSeparator );
  if ( result[ 1 ] == FormatSettings.DecimalSeparator )
    result = String( '0' ) + result;
  if ( B ) result = "-" + result;
  return result;
}

String __fastcall RoundString( String S, int D )
{
  String i, d;
  int N = S.Pos( FormatSettings.DecimalSeparator ), L = S.Length();
  int Start = ( N == 0 ? L + D + 1 : N + D + 1 ), B, St;
  if ( D == -1 ) Start++;
  if ( ( Start <= L ) && ( Start > 0 ) ) {
    bool b = false;
    B = ( S[ Start ] > '4' ? 1 : 0 );
    do {
      if ( Start == 1 ) {
        S = String( '0' ) + S;
        if ( N ) N++;
        Start = 2;
        b = true;
      }
      St = Start - 1;
      if ( St < 1 ) break;
      if ( B == 1 ) {
        switch ( S[ St ] ) {
          case '0' : S[ St ] = '1'; B = 0; break;
          case '1' : S[ St ] = '2'; B = 0; break;
          case '2' : S[ St ] = '3'; B = 0; break;
          case '3' : S[ St ] = '4'; B = 0; break;
          case '4' : S[ St ] = '5'; B = 0; break;
          case '5' : S[ St ] = '6'; B = 0; break;
          case '6' : S[ St ] = '7'; B = 0; break;
          case '7' : S[ St ] = '8'; B = 0; break;
          case '8' : S[ St ] = '9'; B = 0; break;
          case '9' : S[ St ] = '0'; B = 1;
        }
      }
      if ( b ) break;
      Start--;
    } while ( B );
  }
  if ( N ) {
    i = S.SubString( 1, N - 1 );
    d = S.SubString( N + 1, L );
  } else i = S;
  int iL = i.Length();
  if ( iL == 0 ) {
    i = '0';
    iL = 1;
  }
  if ( D > 0 ) d = RPad( d, D, '0' );
  else
    if ( iL + D >= 0 ) {
      if ( ( iL == -D + 1 ) && i[ 1 ] == '0' ) i = '0';
      else for( int x = iL + D + 1; x <= iL; ++x ) i[ x ] = '0';
    } else i = '0';
  if ( D > 0 ) return i + String( FormatSettings.DecimalSeparator ) + d;
  return i;
}

String __fastcall RPad( const String &S, int L, char C )
{
  String R = S;
  int N = R.Length();
  R.SetLength( L );
  while ( ++N <= L ) R[ N ] = C;
  return R;
}

String __fastcall LPad( const String &S, int L, char C )
{
  String R;
  int N = S.Length();
  int K = L - N;

  if ( K > 0 ) {
    R.SetLength( K );
    N = 0;
    while ( ++N <= K )
      R[ N ] = C;
    R += S;
  } else
    R = S;

  return R;
}

String __fastcall FormatFloatDec( String S, int D )
{
  return NNF::FormatFloat( RoundString( S, D ) );
}

String __fastcall FormatStr( int Numdec )
{
  String S( NNFConst::FLOAT_FORMAT );
  if ( Numdec > 0 ) {
    S += NNFConst::Point;
    S += String::StringOfChar( '0', Numdec );
  }
  return S;
}

String __fastcall SampleFormatStr( int Numdec )
{
  String S( NNFConst::SAMPLE_FLOAT_FORMAT );
  if ( Numdec > 0 ) {
    S += NNFConst::Point;
    S += String::StringOfChar( '0', Numdec );
  }
  return S;
}

String __fastcall FloatFormat( double Value, int Numdec )
{
  if ( Numdec > 0 ) {
    String S( NNFConst::FLOAT_FORMAT );
    S += '.';
    S += String::StringOfChar( '0', Numdec );
    return ::FormatFloat( S, Value );
  } else {
    Value = AltRound( Value, Numdec );
    return ::FormatFloat( NNFConst::FLOAT_FORMAT, Value );
  }
}

String __fastcall SampleFloatFormat( double Value, int Numdec )
{
  if ( Numdec > 0 ) {
    String S( NNFConst::SAMPLE_FLOAT_FORMAT );
    S += '.';
    S += String::StringOfChar( '0', Numdec );
    return ::FormatFloat( S, Value );
  } else {
    Value = AltRound( Value, Numdec );
    return ::FormatFloat( NNFConst::SAMPLE_FLOAT_FORMAT, Value );
  }
}

String __fastcall VariableToken( char *&P )
{
  String S;
  while ( *P ) {
    if ( *P == ':' ) {
      char *c;
      c = ++P;
      while ( true ) {
        if ( isspace( *P ) || *P == ':' || !*P ) {
          S.SetLength( P - c );
          memmove( S.c_str(), c, P - c );
          return S;
        }
        ++P;
      }
    }
    ++P;
  }
  return S;
}

bool __fastcall IsMask( NNFConst::char_mask mask, const AnsiString &P )
{
  return NNFConst::char_o.scan_is( mask, P.c_str(), P.c_str() + P.Length() );
}

bool __fastcall IsSerial( const String &P )
{
  for ( WideChar *c = P.c_str(); *c; ++c )
    if ( NNFConst::SerialValidChars.Pos( *c ) == 0 )
      return false;
  return true;
}

String __fastcall ConvertSerial( const String &S )
{
  String R( S.UpperCase() );

  TCharCharMap::const_iterator is;
  int L = S.Length();

  for ( int i = 1; i <= L; ++i ) {
    is = SerialBox.CharMap.find( S[ i ] );
    if ( is != SerialBox.CharMap.end() )
      R[ i ] = (*is).second;
  }

  R = RemoveChar( R, "#№" );

  return R;
}

String __fastcall ConvertWord( const String &S )
{
  String R( S.UpperCase() );

  TCharCharMap::const_iterator is;
  int L = S.Length();

  for ( int i = 1; i <= L; ++i ) {
    is = WordBox.CharMap.find( S[ i ] );
    if ( is != WordBox.CharMap.end() )
      R[ i ] = (*is).second;
  }

  return R;
}

int __fastcall MinimumLength( int Value, int Normal, int NotValidMinimum )
{
  if ( Value <= NotValidMinimum )
    return Normal;
  else
    return Value;
}

bool ArtfulName( const String &Name_ )
{
  bool R, E;

  int N = 1, L = Name_.Length() + 1;
  String S;

  while ( N != L ) {
    S = NNF::GetToken( Name_, N, ',' ).Trim();
    R = false;
    E = false;
    for ( WideChar *c = S.c_str(); *c != '\0'; ++c ) {
      if ( SerialBox.CharMap.find( *c ) != SerialBox.CharMap.end() )
        R = true;

      for ( TCharCharMap::iterator i = SerialBox.CharMap.begin(); i != SerialBox.CharMap.end(); ++i )
        if ( (*i).second == *c && std::isalpha( *c ) ) {
          E = true;
          break;
        }

      if ( R && E )
        return true;
    }
  }

  return false;
}

bool __fastcall CompareAccept( String Template, String Accept )
{
  if ( Template == Accept )
    return true;
  String S;
  int N = 1, L = Template.Length() + 1;
  S = NNF::GetToken( Template, N, ';' );
  S = ";" + S + ";";
  if ( Accept.Pos( S ) == 0 )
    return false;
  while ( N != L ) {
    S = NNF::GetToken( Template, N, ';' );
    S = ";" + S + ";";
    if ( Accept.Pos( S ) == 0 )
      return false;
  }
  return true;
}

String __fastcall PropertyNumField( const String &FieldName_
                                  , const String &PropertyNum_
                                  , const String &Prefix_ )
{
  String S = NNF::RemoveChar( FieldName_, "1234567890" );
  S = NNF::ReplaceStr( S, Prefix_ + NNFConst::Point, Prefix_ + PropertyNum_ + NNFConst::Point );
  return S;
}

}

