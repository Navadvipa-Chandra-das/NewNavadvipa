// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <vcl.h>
#pragma hdrstop
#include "VCL_NNStrUtil.h"
#include "VCL_NNConst.h"
#include "VCL_NNCommon.h"
#include <System.RegularExpressions.hpp>
#include <memory>
// ---------------------------------------------------------------------------
#pragma package(smart_init)

namespace NNV {

TMistakeBox::TMistakeBox() {
  // upper char
  CharMap.insert( std::make_pair( L'О', L'А' ) );
  CharMap.insert( std::make_pair( L'И', L'Е' ) );
  CharMap.insert( std::make_pair( L'С', L'З' ) );
  CharMap.insert( std::make_pair( L'Ю', L'У' ) );
  // меняем английское I на украинское І
  CharMap.insert( std::make_pair( L'I', L'І' ) );
  // меняем украинское Ї на украинское І
  CharMap.insert( std::make_pair( L'Ї', L'І' ) );
  CharMap.insert( std::make_pair( L'Ё', L'Е' ) );
  // lower char
  CharMap.insert( std::make_pair( L'о', L'а' ) );
  CharMap.insert( std::make_pair( L'и', L'е' ) );
  CharMap.insert( std::make_pair( L'с', L'з' ) );
  CharMap.insert( std::make_pair( L'ю', L'у' ) );
  // меняем английское i на украинское і
  CharMap.insert( std::make_pair( L'i', L'і' ) );
  // меняем украинское ї на украинское і
  CharMap.insert( std::make_pair( L'ї', L'і' ) );
  CharMap.insert( std::make_pair( L'ё', L'е' ) );
  // upper str
  StrUpper.insert( std::make_pair( "СС", "С" ) );
  StrUpper.insert( std::make_pair( "НН", "Н" ) );
  // lower str
  StrLower.insert( std::make_pair( "сс", "с" ) );
  StrLower.insert( std::make_pair( "нн", "н" ) );
}

TSerialBox::TSerialBox() {
  CharMap.insert( std::make_pair( L'А', L'F' ) );
  CharMap.insert( std::make_pair( L'Б', L'<' ) );
  CharMap.insert( std::make_pair( L'В', L'D' ) );
  CharMap.insert( std::make_pair( L'Г', L'U' ) );
  CharMap.insert( std::make_pair( L'Д', L'L' ) );
  CharMap.insert( std::make_pair( L'Е', L'T' ) );
  CharMap.insert( std::make_pair( L'Ё', L'~' ) );
  CharMap.insert( std::make_pair( L'Ж', L':' ) );
  CharMap.insert( std::make_pair( L'З', L'P' ) );
  CharMap.insert( std::make_pair( L'И', L'B' ) );
  CharMap.insert( std::make_pair( L'Й', L'Q' ) );
  CharMap.insert( std::make_pair( L'К', L'R' ) );
  CharMap.insert( std::make_pair( L'Л', L'K' ) );
  CharMap.insert( std::make_pair( L'М', L'V' ) );
  CharMap.insert( std::make_pair( L'Н', L'Y' ) );
  CharMap.insert( std::make_pair( L'О', L'J' ) );
  CharMap.insert( std::make_pair( L'П', L'G' ) );
  CharMap.insert( std::make_pair( L'Р', L'H' ) );
  CharMap.insert( std::make_pair( L'С', L'C' ) );
  CharMap.insert( std::make_pair( L'Т', L'N' ) );
  CharMap.insert( std::make_pair( L'У', L'E' ) );
  CharMap.insert( std::make_pair( L'Ш', L'I' ) );
  CharMap.insert( std::make_pair( L'Щ', L'O' ) );
  CharMap.insert( std::make_pair( L'Х', L'{' ) );
  CharMap.insert( std::make_pair( L'Ч', L'X' ) );
  CharMap.insert( std::make_pair( L'Ц', L'W' ) );
  CharMap.insert( std::make_pair( L'Ф', L'A' ) );
  CharMap.insert( std::make_pair( L'Ы', L'S' ) );
  CharMap.insert( std::make_pair( L'Ь', L'M' ) );
  CharMap.insert( std::make_pair( L'Ъ', L'}' ) );
  CharMap.insert( std::make_pair( L'Э', L'"' ) );
  CharMap.insert( std::make_pair( L'Ю', L'>' ) );
  CharMap.insert( std::make_pair( L'Я', L'Z' ) );
  CharMap.insert( std::make_pair( L'а', L'F' ) );
  CharMap.insert( std::make_pair( L'б', L',' ) );
  CharMap.insert( std::make_pair( L'в', L'D' ) );
  CharMap.insert( std::make_pair( L'г', L'U' ) );
  CharMap.insert( std::make_pair( L'д', L'L' ) );
  CharMap.insert( std::make_pair( L'е', L'T' ) );
  CharMap.insert( std::make_pair( L'ё', L'`' ) );
  CharMap.insert( std::make_pair( L'ж', L';' ) );
  CharMap.insert( std::make_pair( L'з', L'P' ) );
  CharMap.insert( std::make_pair( L'и', L'B' ) );
  CharMap.insert( std::make_pair( L'й', L'Q' ) );
  CharMap.insert( std::make_pair( L'к', L'R' ) );
  CharMap.insert( std::make_pair( L'л', L'K' ) );
  CharMap.insert( std::make_pair( L'м', L'V' ) );
  CharMap.insert( std::make_pair( L'н', L'Y' ) );
  CharMap.insert( std::make_pair( L'о', L'J' ) );
  CharMap.insert( std::make_pair( L'п', L'G' ) );
  CharMap.insert( std::make_pair( L'р', L'H' ) );
  CharMap.insert( std::make_pair( L'с', L'C' ) );
  CharMap.insert( std::make_pair( L'т', L'N' ) );
  CharMap.insert( std::make_pair( L'у', L'E' ) );
  CharMap.insert( std::make_pair( L'ш', L'I' ) );
  CharMap.insert( std::make_pair( L'щ', L'O' ) );
  CharMap.insert( std::make_pair( L'х', L'[' ) );
  CharMap.insert( std::make_pair( L'ч', L'X' ) );
  CharMap.insert( std::make_pair( L'ц', L'W' ) );
  CharMap.insert( std::make_pair( L'ф', L'A' ) );
  CharMap.insert( std::make_pair( L'ы', L'S' ) );
  CharMap.insert( std::make_pair( L'ь', L'M' ) );
  CharMap.insert( std::make_pair( L'ъ', L']' ) );
  CharMap.insert( std::make_pair( L'э', L'\'' ) );
  CharMap.insert( std::make_pair( L'ю', L'.' ) );
  CharMap.insert( std::make_pair( L'я', L'Z' ) );
  // Украинский язык
  CharMap.insert( std::make_pair( L'І', L'S' ) );
  CharMap.insert( std::make_pair( L'Ї', L'}' ) );
  CharMap.insert( std::make_pair( L'і', L'S' ) );
  CharMap.insert( std::make_pair( L'ї', L']' ) );
}

TWordBox::TWordBox() {
  CharMap.insert( std::make_pair( L'А', L'Ж' ) );
  CharMap.insert( std::make_pair( L'Б', L'З' ) );
  CharMap.insert( std::make_pair( L'В', L'И' ) );
  CharMap.insert( std::make_pair( L'Г', L'Й' ) );
  CharMap.insert( std::make_pair( L'Д', L'К' ) );
  CharMap.insert( std::make_pair( L'Е', L'Л' ) );
  CharMap.insert( std::make_pair( L'Ё', L'М' ) );
  CharMap.insert( std::make_pair( L'Ж', L'А' ) );
  CharMap.insert( std::make_pair( L'З', L'Б' ) );
  CharMap.insert( std::make_pair( L'И', L'В' ) );
  CharMap.insert( std::make_pair( L'Й', L'Г' ) );
  CharMap.insert( std::make_pair( L'К', L'Д' ) );
  CharMap.insert( std::make_pair( L'Л', L'Е' ) );
  CharMap.insert( std::make_pair( L'М', L'Ё' ) );
  CharMap.insert( std::make_pair( L'Н', L'Ч' ) );
  CharMap.insert( std::make_pair( L'О', L'Ц' ) );
  CharMap.insert( std::make_pair( L'П', L'Ф' ) );
  CharMap.insert( std::make_pair( L'Р', L'Ы' ) );
  CharMap.insert( std::make_pair( L'С', L'Ь' ) );
  CharMap.insert( std::make_pair( L'Т', L'Ъ' ) );
  CharMap.insert( std::make_pair( L'У', L'Э' ) );
  CharMap.insert( std::make_pair( L'Ш', L'Ю' ) );
  CharMap.insert( std::make_pair( L'Щ', L'Я' ) );
  CharMap.insert( std::make_pair( L'Х', L'Р' ) );
  CharMap.insert( std::make_pair( L'Ч', L'Н' ) );
  CharMap.insert( std::make_pair( L'Ц', L'О' ) );
  CharMap.insert( std::make_pair( L'Ф', L'П' ) );
  CharMap.insert( std::make_pair( L'Ы', L'Х' ) );
  CharMap.insert( std::make_pair( L'Ь', L'С' ) );
  CharMap.insert( std::make_pair( L'Ъ', L'Т' ) );
  CharMap.insert( std::make_pair( L'Э', L'У' ) );
  CharMap.insert( std::make_pair( L'Ю', L'Ш' ) );
  CharMap.insert( std::make_pair( L'Я', L'Щ' ) );
  CharMap.insert( std::make_pair( L'а', L'ж' ) );
  CharMap.insert( std::make_pair( L'б', L'з' ) );
  CharMap.insert( std::make_pair( L'в', L'и' ) );
  CharMap.insert( std::make_pair( L'г', L'й' ) );
  CharMap.insert( std::make_pair( L'д', L'к' ) );
  CharMap.insert( std::make_pair( L'е', L'л' ) );
  CharMap.insert( std::make_pair( L'ё', L'м' ) );
  CharMap.insert( std::make_pair( L'ж', L'а' ) );
  CharMap.insert( std::make_pair( L'з', L'б' ) );
  CharMap.insert( std::make_pair( L'и', L'в' ) );
  CharMap.insert( std::make_pair( L'й', L'г' ) );
  CharMap.insert( std::make_pair( L'к', L'д' ) );
  CharMap.insert( std::make_pair( L'л', L'е' ) );
  CharMap.insert( std::make_pair( L'м', L'ё' ) );
  CharMap.insert( std::make_pair( L'н', L'ч' ) );
  CharMap.insert( std::make_pair( L'о', L'ц' ) );
  CharMap.insert( std::make_pair( L'п', L'ф' ) );
  CharMap.insert( std::make_pair( L'р', L'ы' ) );
  CharMap.insert( std::make_pair( L'с', L'ь' ) );
  CharMap.insert( std::make_pair( L'т', L'ъ' ) );
  CharMap.insert( std::make_pair( L'у', L'э' ) );
  CharMap.insert( std::make_pair( L'ш', L'ю' ) );
  CharMap.insert( std::make_pair( L'щ', L'я' ) );
  CharMap.insert( std::make_pair( L'х', L'р' ) );
  CharMap.insert( std::make_pair( L'ч', L'н' ) );
  CharMap.insert( std::make_pair( L'ц', L'о' ) );
  CharMap.insert( std::make_pair( L'ф', L'п' ) );
  CharMap.insert( std::make_pair( L'ы', L'х' ) );
  CharMap.insert( std::make_pair( L'ь', L'с' ) );
  CharMap.insert( std::make_pair( L'ъ', L'т' ) );
  CharMap.insert( std::make_pair( L'э', L'у' ) );
  CharMap.insert( std::make_pair( L'ю', L'ш' ) );
  CharMap.insert( std::make_pair( L'я', L'щ' ) );
  // Украинский язык
  CharMap.insert( std::make_pair( L'І', L'Ї' ) );
  CharMap.insert( std::make_pair( L'Ї', L'І' ) );
  CharMap.insert( std::make_pair( L'і', L'ї' ) );
  CharMap.insert( std::make_pair( L'ї', L'і' ) );
  // Английский язык
  CharMap.insert( std::make_pair( L'a', L'i' ) );
  CharMap.insert( std::make_pair( L'b', L'j' ) );
  CharMap.insert( std::make_pair( L'c', L'a' ) );
  CharMap.insert( std::make_pair( L'd', L'b' ) );
  CharMap.insert( std::make_pair( L'e', L'k' ) );
  CharMap.insert( std::make_pair( L'f', L'l' ) );
  CharMap.insert( std::make_pair( L'g', L'm' ) );
  CharMap.insert( std::make_pair( L'h', L'n' ) );
  CharMap.insert( std::make_pair( L'i', L'c' ) );
  CharMap.insert( std::make_pair( L'j', L'd' ) );
  CharMap.insert( std::make_pair( L'k', L'e' ) );
  CharMap.insert( std::make_pair( L'l', L'f' ) );
  CharMap.insert( std::make_pair( L'm', L'g' ) );
  CharMap.insert( std::make_pair( L'n', L'h' ) );
  CharMap.insert( std::make_pair( L'o', L'u' ) );
  CharMap.insert( std::make_pair( L'p', L'v' ) );
  CharMap.insert( std::make_pair( L'q', L'w' ) );
  CharMap.insert( std::make_pair( L'r', L'x' ) );
  CharMap.insert( std::make_pair( L's', L'y' ) );
  CharMap.insert( std::make_pair( L't', L'z' ) );
  CharMap.insert( std::make_pair( L'u', L'o' ) );
  CharMap.insert( std::make_pair( L'v', L'p' ) );
  CharMap.insert( std::make_pair( L'w', L'q' ) );
  CharMap.insert( std::make_pair( L'x', L'r' ) );
  CharMap.insert( std::make_pair( L'y', L's' ) );
  CharMap.insert( std::make_pair( L'z', L't' ) );
  CharMap.insert( std::make_pair( L'A', L'I' ) );
  CharMap.insert( std::make_pair( L'B', L'J' ) );
  CharMap.insert( std::make_pair( L'C', L'A' ) );
  CharMap.insert( std::make_pair( L'D', L'B' ) );
  CharMap.insert( std::make_pair( L'E', L'K' ) );
  CharMap.insert( std::make_pair( L'F', L'L' ) );
  CharMap.insert( std::make_pair( L'G', L'M' ) );
  CharMap.insert( std::make_pair( L'H', L'N' ) );
  CharMap.insert( std::make_pair( L'I', L'C' ) );
  CharMap.insert( std::make_pair( L'J', L'D' ) );
  CharMap.insert( std::make_pair( L'K', L'E' ) );
  CharMap.insert( std::make_pair( L'L', L'F' ) );
  CharMap.insert( std::make_pair( L'M', L'G' ) );
  CharMap.insert( std::make_pair( L'N', L'H' ) );
  CharMap.insert( std::make_pair( L'O', L'U' ) );
  CharMap.insert( std::make_pair( L'P', L'V' ) );
  CharMap.insert( std::make_pair( L'Q', L'W' ) );
  CharMap.insert( std::make_pair( L'R', L'X' ) );
  CharMap.insert( std::make_pair( L'S', L'Y' ) );
  CharMap.insert( std::make_pair( L'T', L'Z' ) );
  CharMap.insert( std::make_pair( L'U', L'O' ) );
  CharMap.insert( std::make_pair( L'V', L'P' ) );
  CharMap.insert( std::make_pair( L'W', L'Q' ) );
  CharMap.insert( std::make_pair( L'X', L'R' ) );
  CharMap.insert( std::make_pair( L'Y', L'S' ) );
  CharMap.insert( std::make_pair( L'Z', L'T' ) );
  // Цифры
  CharMap.insert( std::make_pair( L'0', L'2' ) );
  CharMap.insert( std::make_pair( L'1', L'3' ) );
  CharMap.insert( std::make_pair( L'2', L'0' ) );
  CharMap.insert( std::make_pair( L'3', L'1' ) );
  CharMap.insert( std::make_pair( L'4', L'7' ) );
  CharMap.insert( std::make_pair( L'5', L'8' ) );
  CharMap.insert( std::make_pair( L'6', L'9' ) );
  CharMap.insert( std::make_pair( L'7', L'4' ) );
  CharMap.insert( std::make_pair( L'8', L'5' ) );
  CharMap.insert( std::make_pair( L'9', L'6' ) );
}

TMistakeBox MistakeBox;
TSerialBox SerialBox;
TWordBox WordBox;

const int H_STR = 11;

const char* MILLION_STR[ H_STR ][ wdFive + 1 ] = {
  {"тысяча", "тысячи", "тысяч" }, {"миллион", "миллиона", "миллионов" },
  {"миллиард", "миллиарда", "миллиардов" },
  {"триллион", "триллиона", "триллионов" },
  {"квадриллион", "квадриллиона", "квадриллионов" },
  {"квинтиллион", "квинтиллиона", "квинтиллионов" },
  {"секстиллион", "секстиллиона", "секстиллионов" },
  {"септиллион", "септиллиона", "септиллионов" },
  {"окталлион", "окталлиона", "окталлионов" },
  {"ноналлион", "ноналлиона", "ноналлионов" },
  {"дециллион", "дециллиона", "дециллионов" } };

const char* LIMON_STR[ 3 ] = {"-лион' ", "-лиона' ", "-лионов' " };
const char* ONE_GENDER[ 3 ] = {"один ", "одно ", "одна " };
const char* TWO_GENDER[ 3 ] = {"два ", "два ", "две " };
const char* SOTKA[ 9 ] = {
  "сто ", "двести ", "триста ", "четыреста ", "пятьсот ", "шестьсот ",
  "семьсот ", "восемьсот ", "девятьсот " };
const char* DESYATKA[ 10 ] = {
  "десять ", "одиннадцать ", "двенадцать ", "тринадцать ", "четырнадцать ",
  "пятнадцать ", "шестнадцать ", "семнадцать ", "восемнадцать ", "девятнадцать "
};
const char* DVADCATKA[ 8 ] = {
  "двадцать ", "тридцать ", "сорок ", "пятьдесят ", "шестьдесят ", "семьдесят ",
  "восемьдесят ", "девяносто " };
const char* EDINICA[ 7 ] = {
  "три ", "четыре ", "пять ", "шесть ", "семь ", "восемь ", "девять " };
const char* ZERO = "ноль ";
const char* MINUS = "минус ";

String __fastcall RemoveChar( String S, const String Chars ) {
  for ( int i = S.Length(); i > 0; i-- )
    if ( Chars.Pos( S[ i ] ) != 0 )
      S.Delete( i, 1 );
  return S;
}

String __fastcall GetToken( const String &S, int &Pos, const char &Delim ) {
  String Result;
  WideChar* I = S.c_str() + Pos;
  --I;
  while ( ( *I ) && ( *I != Delim ) )
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

int __fastcall CharCount( const String &S, WideChar C ) {
  int Result = 0, L = S.Length();
  for ( int i = 1; i <= L; ++i )
    if ( S[ i ] == C )
      Result++;
  return Result;
}

String __fastcall ReplaceStr( const String &S, const String Srch,
    const String Replace ) {
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
    }
    else
      Result = Result + Source;
  }
  while ( I > 0 );
  return Result;
}

void __fastcall ReplaceChar( WideChar *c, const WideChar Srch,
    const WideChar Replace ) {
  while ( *c ) {
    if ( *c == Srch )
      * c = Replace;
    ++c;
  }
}

bool __fastcall Like( WideChar *t, WideChar *s ) {
  if ( !( *t ) )
    return true;
  WideChar *tt, *ss;
  while ( ( *t ) && ( *s ) ) {
    if ( ( *t ) == NNVConst::CharPercent ) {
      tt = ++t;
      ss = s;
      while ( ( *ss ) )
        if ( Like( tt, ss++ ) )
          return true;
      return false;
    }
    if ( ( ( *t ) != ( *s ) ) && ( ( *t ) != NNVConst::CharUnderline ) )
      return false;
    t++;
    s++;
  }
  if ( ( *s ) )
    return false;
  if ( !( *t ) )
    return true;
  do {
    if ( ( *t ) != NNVConst::CharPercent )
      return false;
  }
  while ( ( *( ++t ) ) );
  return true;
}

String __fastcall LikeStr( const String &S ) {
  String R( S );
  R = ReplaceStr( R, NNVConst::StrCharPercent, "%" );
  R = ReplaceStr( R, NNVConst::StrCharUnderline, "_" );
  return R;
}

void __fastcall MistakeStr( String &R, bool CaseInSensitive )
{
  TCharCharMap::iterator i;
  TStrStrMap::iterator j;

  for ( j = MistakeBox.StrUpper.begin(); j != MistakeBox.StrUpper.end(); ++j )
    R = ReplaceStr( R, ( *j ).first, ( *j ).second );

  if ( !CaseInSensitive )
    for ( j = MistakeBox.StrLower.begin(); j != MistakeBox.StrLower.end(); ++j )
      R = ReplaceStr( R, ( *j ).first, ( *j ).second );

  for ( WideChar * c = R.c_str(); *c; ++c ) {
    i = MistakeBox.CharMap.find( *c );
    if ( i != MistakeBox.CharMap.end() )
      * c = ( *i ).second;
  }
}

TNumWordDiapazon __fastcall NumDiapazon( const char &C, bool B ) {
  if ( B )
    return wdFive;
  else
    switch ( C ) {
      case '1':
      return wdOne;
      case '2':
      case '3':
      case '4':
      return wdTwoFourth;
      default:
      return wdFive;
    }
}

void __fastcall BadCharError( char C ) {
  throw Exception( NNVConst::TheSymbol + String( C ) +
      NNVConst::IsInadmissibleInLine );
}

String __fastcall TroykaToStr( String &S, int P, TGender AGender,
    TNumWordDiapazon &ADiapazon ) {
  bool B = false;
  String Result;
  String T[ 3 ] = {"", "", "" };
  Result = "";
  switch ( S[ 1 ] ) {
    case '0':
    break; // ничего не делаем
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    Result = Result + SOTKA[ (unsigned char)( S[ 1 ] ) - 49 ];
    break;
    default:
    BadCharError( S[ 1 ] );
  }
  switch ( S[ 2 ] ) {
    case '0':
    break; // ничего не делаем
    case '1':
    if ( S[ 3 ] >= '0' && S[ 3 ] <= '9' )
      Result = Result + DESYATKA[ (unsigned char)( S[ 3 ] ) - 48 ];
    else
      BadCharError( S[ 3 ] );
    B = true;
    break;
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    Result = Result + DVADCATKA[ (unsigned char)( S[ 2 ] ) - 50 ];
    break;
    default:
    BadCharError( S[ 2 ] );
  }
  if ( !B )
    switch ( S[ 3 ] ) {
      case '0':
      break; // ничего не делаем
      case '1':
      switch ( P ) {
        case 0:
        Result = Result + ONE_GENDER[ AGender ];
        break;
        case 1:
        Result = Result + ONE_GENDER[ wgFemale ];
        break;
        default:
        Result = Result + ONE_GENDER[ wgMale ];
      }
      break;
      case '2':
      switch ( P ) {
        case 0:
        Result = Result + TWO_GENDER[ AGender ];
        break;
        case 1:
        Result = Result + TWO_GENDER[ wgFemale ];
        break;
        default:
        Result = Result + TWO_GENDER[ wgMale ];
      }
      break;
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      Result = Result + EDINICA[ (unsigned char)( S[ 3 ] ) - 51 ];
      break;
      default:
      BadCharError( S[ 3 ] );
    }
  if ( Result == "" )
    return Result;
  if ( P == 0 )
    ADiapazon = NumDiapazon( S[ 3 ], B );
  else if ( ( P >= 1 ) && ( P <= H_STR ) )
    Result = Result + MILLION_STR[ P - 1 ][ NumDiapazon( S[ 3 ], B ) ] + " ";
  else
    Result = Result + "''" + SToStr( IntToStr( P - 1 ), wgMale, T, false ) +
        LIMON_STR[ NumDiapazon( S[ 3 ], B ) ];
  return Result;
}

String __fastcall SToStr( String S, TGender AGender, String A[ 3 ],
    bool FirstUpper ) {
  int I, N;
  TNumWordDiapazon ADiapazon;
  String Result, m;
  bool IsMinus = false;
  if ( !S.IsEmpty() && S[ 1 ] == '-' ) {
    S.Delete( 1, 1 );
    IsMinus = true;
  }
  Result = "";
  ADiapazon = wdFive;
  N = S.Length();
  if ( ( N % 3 ) != 0 ) {
    S = String::StringOfChar( '0', 3 - ( N % 3 ) ) + S;
    N = S.Length();
  }
  for ( I = ( N / 3 ); I > 0; I-- ) {
    m = S.SubString( N - I * 3 + 1, 3 );
    Result = Result + TroykaToStr( m, I - 1, AGender, ADiapazon );
  }
  if ( Result == "" )
    Result = ZERO;
  Result = Result + A[ ADiapazon ];
  if ( FirstUpper )
    Result = UpperCase( Result[ 1 ] ) + Result.SubString( 2, MaxInt );
  if ( IsMinus )
    Result = MINUS + Result;
  return Result;
}

bool __fastcall Compare( String sub_str
                       , String s
                       , TSearchOptions &Options )
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
    sub_str = sub_str + NNVConst::StrCharPercent;
    sub_str = NNVConst::StrCharPercent + sub_str;
  }

  if ( sub_str.IsEmpty() )
    result = true;
  else
    result = Like( sub_str.c_str(), s.c_str() );

  return Options.NotThis ? !result : result;
}

String __fastcall TrimBChar( const String S, WideChar C ) {
  int i = 1, L = S.Length();
  while ( ( i <= L ) && ( S[ i ] == C ) )
    i++;
  return S.SubString( i, MaxInt );
}

String __fastcall TrimEChar( const String S, WideChar C ) {
  int i = S.Length();
  while ( ( i > 0 ) && ( S[ i ] == C ) )
    i--;
  return S.SubString( 1, i );
}

bool __fastcall IsStringEmpty( const String &S ) {
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

String __fastcall FormatFloat( String S ) {
  String R, result;
  int N, i;
  if ( S.IsEmpty() || S == "-" )
    return "0";
  bool B = S[ 1 ] == '-';
  if ( B )
    S = S.SubString( 2, S.Length() - 1 );
  N = S.Pos( FormatSettings.DecimalSeparator );
  i = ( N == 0 ? S.Length() - 2 : N - 3 );
  while ( i > -3 ) {
    result = String( FormatSettings.ThousandSeparator ) +
        S.SubString( ( i <= 0 ? 1 : i ), ( i <= 0 ? 2 + i : 3 ) ) + result;
    i -= 3;
  }
  if ( N )
    result = result + String( FormatSettings.DecimalSeparator ) +
        S.SubString( N + 1, S.Length() - N );
  result = TrimBChar( result, FormatSettings.ThousandSeparator );
  if ( result[ 1 ] == FormatSettings.DecimalSeparator )
    result = String( '0' ) + result;
  if ( B )
    result = "-" + result;
  return result;
}

String __fastcall RoundString( String S, int D ) {
  String i, d;
  int N = S.Pos( FormatSettings.DecimalSeparator ), L = S.Length();
  int Start = ( N == 0 ? L + D + 1 : N + D + 1 ), B, St;
  if ( D == -1 )
    Start++;
  if ( ( Start <= L ) && ( Start > 0 ) ) {
    bool b = false;
    B = ( S[ Start ] > '4' ? 1 : 0 );
    do {
      if ( Start == 1 ) {
        S = String( '0' ) + S;
        if ( N )
          N++;
        Start = 2;
        b = true;
      }
      St = Start - 1;
      if ( St < 1 )
        break;
      if ( B == 1 ) {
        switch ( S[ St ] ) {
          case '0':
          S[ St ] = '1';
          B = 0;
          break;
          case '1':
          S[ St ] = '2';
          B = 0;
          break;
          case '2':
          S[ St ] = '3';
          B = 0;
          break;
          case '3':
          S[ St ] = '4';
          B = 0;
          break;
          case '4':
          S[ St ] = '5';
          B = 0;
          break;
          case '5':
          S[ St ] = '6';
          B = 0;
          break;
          case '6':
          S[ St ] = '7';
          B = 0;
          break;
          case '7':
          S[ St ] = '8';
          B = 0;
          break;
          case '8':
          S[ St ] = '9';
          B = 0;
          break;
          case '9':
          S[ St ] = '0';
          B = 1;
        }
      }
      if ( b )
        break;
      Start--;
    }
    while ( B );
  }
  if ( N ) {
    i = S.SubString( 1, N - 1 );
    d = S.SubString( N + 1, L );
  }
  else
    i = S;
  int iL = i.Length();
  if ( iL == 0 ) {
    i = '0';
    iL = 1;
  }
  if ( D > 0 )
    d = RPad( d, D, '0' );
  else if ( iL + D >= 0 ) {
    if ( ( iL == -D + 1 ) && i[ 1 ] == '0' )
      i = '0';
    else
      for ( int x = iL + D + 1; x <= iL; ++x )
        i[ x ] = '0';
  }
  else
    i = '0';
  if ( D > 0 )
    return i + String( FormatSettings.DecimalSeparator ) + d;
  return i;
}

String __fastcall RPad( const String &S, int L, char C ) {
  String R = S;
  int N = R.Length();
  R.SetLength( L );
  while ( ++N <= L )
    R[ N ] = C;
  return R;
}

String __fastcall LPad( const String &S, int L, char C ) {
  String R;
  int N = S.Length();
  int K = L - N;
  if ( K > 0 ) {
    R.SetLength( K );
    N = 0;
    while ( ++N <= K )
      R[ N ] = C;
    R += S;
  }
  else
    R = S;
  return R;
}

String __fastcall FormatFloatDec( String S, int D ) {
  return FormatFloat( RoundString( S, D ) );
}

String __fastcall FormatStr( int Numdec ) {
  String S( NNVConst::FLOAT_FORMAT );
  if ( Numdec > 0 ) {
    S += NNVConst::Point;
    S += String::StringOfChar( '0', Numdec );
  }
  return S;
}

String __fastcall SampleFormatStr( int Numdec ) {
  String S( NNVConst::SAMPLE_FLOAT_FORMAT );
  if ( Numdec > 0 ) {
    S += NNVConst::Point;
    S += String::StringOfChar( '0', Numdec );
  }
  return S;
}

String __fastcall FloatFormat( double Value, int Numdec ) {
  if ( Numdec > 0 ) {
    String S( NNVConst::FLOAT_FORMAT );
    S += '.';
    S += String::StringOfChar( '0', Numdec );
    return ::FormatFloat( S, Value );
  }
  else {
    Value = AltRound( Value, Numdec );
    return ::FormatFloat( NNVConst::FLOAT_FORMAT, Value );
  }
}

String __fastcall SampleFloatFormat( double Value, int Numdec ) {
  if ( Numdec > 0 ) {
    String S( NNVConst::SAMPLE_FLOAT_FORMAT );
    S += '.';
    S += String::StringOfChar( '0', Numdec );
    return ::FormatFloat( S, Value );
  }
  else {
    Value = AltRound( Value, Numdec );
    return ::FormatFloat( NNVConst::SAMPLE_FLOAT_FORMAT, Value );
  }
}

String __fastcall VariableToken( char *&P ) {
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

bool __fastcall IsMask( NNVConst::char_mask mask, const AnsiString &P ) {
  return NNVConst::char_o.scan_is( mask, P.c_str(), P.c_str() + P.Length() );
}

bool __fastcall IsSerial( const String &P ) {
  for ( WideChar * c = P.c_str(); *c; ++c )
    if ( NNVConst::SerialValidChars.Pos( *c ) == 0 )
      return false;
  return true;
}

String __fastcall ConvertSerial( const String &S ) {
  String R( S.UpperCase() );
  TCharCharMap::const_iterator is;
  int L = S.Length();
  for ( int i = 1; i <= L; ++i ) {
    is = SerialBox.CharMap.find( S[ i ] );
    if ( is != SerialBox.CharMap.end() )
      R[ i ] = ( *is ).second;
  }
  R = RemoveChar( R, "#№" );
  return R;
}

String __fastcall ConvertWord( const String &S )
{
  String R( S );
  TCharCharMap::const_iterator is;

  int L = R.Length();
  for ( int i = 1; i <= L; ++i ) {
    is = WordBox.CharMap.find( R[ i ] );
    if ( is != WordBox.CharMap.end() )
      R[ i ] = ( *is ).second;
  }
  return R;
}

int __fastcall MinimumLength( int Value, int Normal, int NotValidMinimum ) {
  if ( Value <= NotValidMinimum )
    return Normal;
  else
    return Value;
}

bool ArtfulName( const String &Name_ ) {
  bool R, E;
  int N = 1, L = Name_.Length() + 1;
  String S;
  while ( N != L ) {
    S = GetToken( Name_, N, ',' ).Trim();
    R = false;
    E = false;
    for ( WideChar * c = S.c_str(); *c != '\0'; ++c ) {
      if ( SerialBox.CharMap.find( *c ) != SerialBox.CharMap.end() )
        R = true;
      for ( TCharCharMap::iterator i = SerialBox.CharMap.begin();
      i != SerialBox.CharMap.end(); ++i )
        if ( ( *i ).second == *c && std::isalpha( *c ) ) {
          E = true;
          break;
        }
      if ( R && E )
        return true;
    }
  }
  return false;
}

bool __fastcall CompareAccept( String Template, String Accept ) {
  if ( Template == Accept )
    return true;
  String S;
  int N = 1, L = Template.Length() + 1;
  S = GetToken( Template, N, ';' );
  S = ";" + S + ";";
  if ( Accept.Pos( S ) == 0 )
    return false;
  while ( N != L ) {
    S = GetToken( Template, N, ';' );
    S = ";" + S + ";";
    if ( Accept.Pos( S ) == 0 )
      return false;
  }
  return true;
}

String __fastcall PropertyNumField( const String &FieldName_,
    const String &PropertyNum_, const String &Prefix_ ) {
  String S = RemoveChar( FieldName_, "1234567890" );
  S = ReplaceStr( S, Prefix_ + NNVConst::Point,
      Prefix_ + PropertyNum_ + NNVConst::Point );
  return S;
}

}

