// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <fmx.h>

#pragma hdrstop
#include "FMX_NNCommon.h"
#include "FMX_NNStrUtil.h"
#include "FMX_NNConst.h"
//#include "FMX_NNFmFormList.h"
#include "FMX_NNDBMiracle.h"
#include <memory>
#include <algorithm>
// ---------------------------------------------------------------------------
#pragma package(smart_init)

namespace NNF {

const int RussianIndex = 4;
TPrabhupadaBukvary PrabhupadaBukvary;

String __fastcall RemoveDiacritics( const String& S )
{
  String R;

  int L = S.Length();
  for ( int i = 1; i <= L; ++i )
    R += PrabhupadaBukvary[ S[ i ] ].Bukva;
  return R;
}

bool __fastcall PrabhupadaComareLess( const String& A, const String& B )
{
  int AL = A.Length(),
      BL = B.Length();

  int L = std::min( AL, BL );

  int AV, BV;
  for ( int i = 1; i <= L; ++i ) {
    AV = PrabhupadaBukvary[ A[ i ] ].Ves;
    BV = PrabhupadaBukvary[ B[ i ] ].Ves;
    if ( AV == BV ) {
      continue;
    } else if ( AV > BV ) {
      return false;
    } else if ( AV < BV ) {
      return true;
    }
  }

  if ( AL < BL )
    return true;

  return false;
}

bool __fastcall PrabhupadaComareMore( const String& A, const String& B )
{
  int AL = A.Length(),
      BL = B.Length();

  int L = std::min( AL, BL );

  int AV, BV;
  for ( int i = 1; i <= L; ++i ) {
    AV = PrabhupadaBukvary[ A[ i ] ].Ves;
    BV = PrabhupadaBukvary[ B[ i ] ].Ves;
    if ( AV == BV ) {
      continue;
    } else if ( AV < BV ) {
      return false;
    } else if ( AV > BV ) {
      return true;
    }
  }

  if ( AL > BL )
    return true;

  return false;
}

TStringMap::TStringMap()
  : inherited()
{
}

TStringMap::~TStringMap()
{
}

TStringSet::TStringSet()
  : inherited()
{
}

TStringSet::~TStringSet()
{
}

TFilterSlovar::TFilterSlovar()
{
}

TFilterSlovar::TFilterSlovar( const TFilterSlovar &A )
  : FSanskrit( A.Sanskrit )
  , FPerevod( A.Perevod )
  , FSanskritWithoutDiakritik( A.SanskritWithoutDiakritik )
  , FPerevodWithoutDiakritik( A.PerevodWithoutDiakritik )
{
}

TFilterSlovar::TFilterSlovar( const String &ASanskrit
                            , const String &APerevod )
  : FSanskrit( ASanskrit )
  , FPerevod( APerevod )
{
  SanskritWithoutDiakritik = RemoveDiacritics( Sanskrit );
  PerevodWithoutDiakritik  = RemoveDiacritics( Perevod );
}

TFilterSlovar::~TFilterSlovar()
{
}

TFilterSlovar& TFilterSlovar::operator = ( const TFilterSlovar &a )
{
  Sanskrit = a.FSanskrit;
  Perevod  = a.FPerevod;
  // нет нужды сравнивать служебные поля FSanskritWithoutDiakritik, FPerevodWithoutDiakritik и другие
  return *this;
}

void __fastcall TFilterSlovar::SetSanskrit( const String &Value )
{
  if ( FSanskrit != Value ) {
    FSanskrit = Value;
    SanskritWithoutDiakritik = RemoveDiacritics( Sanskrit );
  }
}

void __fastcall TFilterSlovar::SetPerevod( const String &Value )
{
  if ( FPerevod != Value ) {
    FPerevod = Value;
    PerevodWithoutDiakritik = RemoveDiacritics( Perevod );
  }
}

void __fastcall TFilterSlovar::LoadFromFiler( TNNFTextStream *Filer )
{
  Sanskrit                 = Filer->ReadString();
  Perevod                  = Filer->ReadString();
  // нет нужды запоминать служебные свойства, так как они заполняются автоматически
  // SanskritWithoutDiakritik
  // PerevodWithoutDiakritik
  IsEmpty                  = Filer->ReadBool();
  IsReset                  = true;
}

void __fastcall TFilterSlovar::SaveToFiler( TNNFTextStream *Filer )
{
  Filer->WriteString( Sanskrit );
  Filer->WriteString( Perevod );
  Filer->WriteBool( IsEmpty );
}

TPrabhupadaBukva::TPrabhupadaBukva()
{
}

TPrabhupadaBukva::~TPrabhupadaBukva()
{
}

TPrabhupadaBukvary::TPrabhupadaBukvary()
  : inherited()
{
}

TPrabhupadaBukvary::~TPrabhupadaBukvary()
{
}

TYazykInfo::TYazykInfo()
{
}

TYazykInfo::TYazykInfo( const TYazykInfo &A )
  : FID( A.FID )
  , FYazyk( A.FYazyk )
  , FYazykSlovo( A.FYazykSlovo )
  , FLang( A.FLang )
  , FCurrentRow( A.FCurrentRow )
  , FFilterSlovar( A.FFilterSlovar )
  , FPrabhupadaZakladkaMap( A.FPrabhupadaZakladkaMap )
{
}

TYazykInfo::~TYazykInfo()
{
}

TYazykVector::TYazykVector()
  : inherited()
{
}

TYazykVector::~TYazykVector()
{
}

TPrabhupadaSlovarVector::TPrabhupadaSlovarVector()
  : inherited()
{
}

TPrabhupadaSlovarVector::~TPrabhupadaSlovarVector()
{
  for ( TPrabhupadaSlovarVector::iterator I = begin(); I != end(); ++I )
    delete *I;
}

TSanskritPerevod::TSanskritPerevod()
{
}

TSanskritPerevod::~TSanskritPerevod()
{
}

TPrabhupadaZakladka::TPrabhupadaZakladka()
{
}

TPrabhupadaZakladka::TPrabhupadaZakladka( int ARowNum
                                        , TFilterSlovar AFilterSlovar )
  : FRowNum( ARowNum )
  , FFilterSlovar( AFilterSlovar )
{
}


TPrabhupadaZakladka::~TPrabhupadaZakladka()
{
}

void __fastcall TPrabhupadaZakladka::LoadFromFiler( TNNFTextStream *Filer )
{
  RowNum = Filer->ReadInt();
  FilterSlovar.LoadFromFiler( Filer );
}

void __fastcall TPrabhupadaZakladka::SaveToFiler( TNNFTextStream *Filer )
{
  Filer->WriteInt( RowNum );
  FilterSlovar.SaveToFiler( Filer );
}

TPrabhupadaZakladkaMap::TPrabhupadaZakladkaMap()
  : inherited()
{
}

TPrabhupadaZakladkaMap::~TPrabhupadaZakladkaMap()
{
}

void __fastcall TPrabhupadaZakladkaMap::LoadFromFiler( TNNFTextStream *Filer )
{
  TPrabhupadaZakladka PZ;
  unsigned short I;
  std::size_t L = Filer->ReadSizeType();
  clear();
  for ( std::size_t i = 0; i < L; ++i ) {
    I = Filer->ReadUnsignedShort();
    PZ.LoadFromFiler( Filer );
    operator[]( I ) = PZ;
  }
}

void __fastcall TPrabhupadaZakladkaMap::SaveToFiler( TNNFTextStream *Filer )
{
  Filer->WriteSizeType( size() );
  for ( iterator I = begin(); I != end(); ++I ) {
    Filer->WriteUnsignedShort( (*I).first );
    (*I).second.SaveToFiler( Filer );
  }
}

int __fastcall TYazykVector::FindYazyk( const String &S )
{
  std::size_t L = size(), I = 0;
  for( ; I < L; ++I )
    if ( operator[]( I ).Yazyk == S )
      return I;
  return -1;
}

int __fastcall TYazykVector::FindLang( const String &S )
{
  std::size_t L = size(), I = 0;
  for( ; I < L; ++I )
    if ( operator[]( I ).Lang == S )
      return I;
  return -1;
}

void __fastcall TYazykVector::LoadFromFiler( TNNFTextStream *Filer )
{
  for ( iterator I = begin(); I != end(); ++I ) {
    (*I).CurrentRow = Filer->ReadInt();
    (*I).FilterSlovar.LoadFromFiler( Filer );
    (*I).PrabhupadaZakladkaMap.LoadFromFiler( Filer );
  }
}

void __fastcall TYazykVector::SaveToFiler( TNNFTextStream *Filer )
{
  for ( iterator I = begin(); I != end(); ++I ) {
    Filer->WriteInt( (*I).CurrentRow );
    (*I).FilterSlovar.SaveToFiler( Filer );
    (*I).PrabhupadaZakladkaMap.SaveToFiler( Filer );
  }
}

const unsigned short DAYS_IN_MONTH[ 12 ] = {
  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

String __fastcall PrefixCheckStyleValue( TCheckStyleValue ACheckStyle )
{
  String R;
  switch ( ACheckStyle ) {
  case TCheckStyleValue::None :
    R = L"";
    break;
  case TCheckStyleValue::Equal :
    R = L"\\=\\ ";
    break;
  case TCheckStyleValue::Greater :
    R = L"\\>\\ ";
    break;
  case TCheckStyleValue::GreaterOrEqual :
    R = L"\\>\\=\\ ";
    break;
  case TCheckStyleValue::Less :
    R = L"\\<\\ ";
    break;
  case TCheckStyleValue::LessOrEqual :
    R = L"\\<\\=\\ ";
    break;
  }
  return R;
}

String __fastcall PrefixFormatCheckStyleValue( TCheckStyleValue ACheckStyle )
{
  String R;
  switch ( ACheckStyle ) {
  case TCheckStyleValue::None :
    R = L"";
    break;
  case TCheckStyleValue::Equal :
    R = L"= ";
    break;
  case TCheckStyleValue::Greater :
    R = L"> ";
    break;
  case TCheckStyleValue::GreaterOrEqual :
    R = L">= ";
    break;
  case TCheckStyleValue::Less :
    R = L"< ";
    break;
  case TCheckStyleValue::LessOrEqual :
    R = L"<= ";
    break;
  }
  return R;
}

bool __fastcall FormExists( TMetaClass* InstanceClass, void *Reference ) {
  int N = Screen->FormCount;
  for ( int i = 0; i < N; ++i )
    if ( Screen->Forms[ i ]->InheritsFrom( InstanceClass ) &&
        ( ( *( TComponent * * )( Reference ) ) == Screen->Forms[ i ] ) )
      return true;
  return false;
}

bool __fastcall FormExists( TCommonCustomForm *fm ) {
  int N = Screen->FormCount;
  for ( int i = 0; i < N; ++i )
    if ( Screen->Forms[ i ] == fm )
      return true;
  return false;
}

void __fastcall FormCreate( TMetaClass* InstanceClass, void *Reference ) {
  if ( !FormExists( InstanceClass, Reference ) ) {
    NNF::TCursorMagic cm( crHourGlass );
    Application->CreateForm( InstanceClass, Reference );
  }
}

bool __fastcall DMExists( TMetaClass* InstanceClass, void *Reference ) {
  int N = Screen->DataModuleCount;
  for ( int i = 0; i < N; ++i )
    if ( Screen->DataModules[ i ]->InheritsFrom( InstanceClass ) &&
        ( ( *( TComponent * * )( Reference ) ) == Screen->DataModules[ i ] ) )
      return true;
  return false;
}

bool __fastcall DMExists( TDataModule *dm ) {
  int N = Screen->DataModuleCount;
  for ( int i = 0; i < N; ++i )
    if ( Screen->DataModules[ i ] == dm )
      return true;
  return false;
}

void __fastcall DMCreate( TMetaClass* InstanceClass, void *Reference ) {
  if ( !DMExists( InstanceClass, Reference ) ) {
    NNF::TCursorMagic cm( crHourGlass );
    Application->CreateForm( InstanceClass, Reference );
  }
}

String __fastcall ComponentToKey( TComponent *AComponent
                                , bool UseOwnerName )
{
  String Result, S;
  int i = 0;
  while ( AComponent != nullptr && AComponent != Application ) {
    S = AComponent->ClassName();
    if ( UseOwnerName )
      S += L"." + AComponent->Name;
    if ( i > 0 )
      S += L"-";
    Result = S + Result;
    AComponent = AComponent->Owner;
    ++i;
  }
  if ( !Application->Name.IsEmpty( ) )
    Result = Application->Name + L"-" + Result;
  Result += L".ini";
  return Result;
}

String __fastcall UpdateStatusToStr( TUpdateStatus Value ) {
  String Result;
  switch ( Value ) {
    case usUnmodified:
    Result = NNFConst::RecordNotChanged;
    break;
    case usModified:
    Result = NNFConst::RecordChanged;
    break;
    case usInserted:
    Result = NNFConst::RecordInserted;
    break;
    case usDeleted:
    Result = NNFConst::RecordDeleted;
    break;
  }
  return Result;
}

String __fastcall DataSetStateToStr( TDataSetState Value ) {
  String Result;
  switch ( Value ) {
    case dsInactive:
    Result = NNFConst::DataSetNotActive;
    break;
    case dsBrowse:
    Result = NNFConst::DataSetBrowse;
    break;
    case dsEdit:
    Result = NNFConst::DataSetEdit;
    break;
    case dsInsert:
    Result = NNFConst::DataSetInsert;
    break;
    case dsSetKey:
    Result = NNFConst::DataSetSetKey;
    break;
    case dsCalcFields:
    Result = NNFConst::DataSetCalcFields;
    break;
    case dsFilter:
    Result = NNFConst::DataSetFilter;
    break;
    case dsNewValue:
    Result = NNFConst::DataSetNewValue;
    break;
    case dsOldValue:
    Result = NNFConst::DataSetOldValue;
    break;
    case dsCurValue:
    Result = NNFConst::DataSetCurValue;
    break;
    case dsBlockRead:
    Result = NNFConst::DataSetBlockRead;
    break;
    case dsInternalCalc:
    Result = NNFConst::DataSetInternalCalc;
    break;
    case dsOpening:
    Result = NNFConst::DataSetOpening;
  }
  return Result;
}

TDataModule* __fastcall StrToDataModule( const String AName ) {
  for ( int i = 0; i < Screen->DataModuleCount; ++i )
    if ( CompareText( Screen->DataModules[ i ]->Name, AName ) == 0 )
      return Screen->DataModules[ i ];
  return NULL;
}

TDataSet* __fastcall StrToDataSet( String &AText, TComponent *AOwner,
    bool RaiseExcept ) {
  int N;
  TComponent *O;
  String S;
  TDataSet* Result;
  N = 1;
  S = NNF::GetToken( AText, N, '.' );
  Result = NULL;
  if ( N <= AText.Length( ) ) {
    O = StrToDataModule( S );
    if ( !O ) {
      if ( RaiseExcept )
        throw Exception( NNFConst::NotFindDataModule + S );
      else
        return Result;
    }
    S = GetToken( AText, N, '.' );
  }
  else
    O = AOwner;
  Result = dynamic_cast < TDataSet* > ( O->FindComponent( S ) );
  if ( Result && RaiseExcept )
    throw Exception( NNFConst::NotFindDataSet + S );
  return Result;
}

TRect __fastcall CalcRect( TRect ARect, TRect RC ) {
  int W, H;
  W = RC.Right - RC.Left + 1;
  H = RC.Bottom - RC.Top + 1;
  if ( ARect.Left + 1 + W > Screen->Width )
    RC.Left = Screen->Width - W - 1;
  else
    RC.Left = ARect.Left + 1;
  if ( RC.Left < 0 )
    RC.Left = 0;
  if ( ARect.Bottom + 1 + H > Screen->Height )
    RC.Top = ARect.Top - 1 - H;
  else
    RC.Top = ARect.Bottom + 1;
  if ( RC.Top < 0 )
    RC.Top = 0;
  RC.Right = RC.Left + W - 1;
  RC.Bottom = RC.Top + H - 1;
  return RC;
}

bool __fastcall IsLeapYear( int AYear ) {
  return ( ( AYear % 4 == 0 ) && ( ( AYear % 100 != 0 ) ||
      ( AYear % 400 == 0 ) ) );
}

unsigned short __fastcall DaysPerMonth( int AYear, int AMonth ) {
  unsigned short result;
  result = DAYS_IN_MONTH[ AMonth - 1 ];
  if ( ( AMonth == 2 ) && IsLeapYear( AYear ) )
    ++result; // leap-year Feb is special
  return result;
};

TDateTime __fastcall ChangeMonth( TDateTime D, int Delta ) {
  unsigned short AYear, AMonth, ADay, CurDay;
  TDateTime NewDate;
  DecodeDate( D, AYear, AMonth, ADay );
  CurDay = ADay;
  if ( Delta > 0 )
    ADay = DaysPerMonth( AYear, AMonth );
  else
    ADay = 1;
  NewDate = EncodeDate( AYear, AMonth, ADay );
  NewDate = NewDate + Delta;
  DecodeDate( NewDate, AYear, AMonth, ADay );
  if ( DaysPerMonth( AYear, AMonth ) > CurDay )
    ADay = CurDay;
  else
    ADay = DaysPerMonth( AYear, AMonth );
  return EncodeDate( AYear, AMonth, ADay );
};

TDateTime __fastcall PriorMonth( TDateTime D ) {
  return ChangeMonth( D, -1 );
}

TDateTime __fastcall NextMonth( TDateTime D ) {
  return ChangeMonth( D, 1 );
}

TDateTime __fastcall PriorYear( TDateTime D ) {
  unsigned short AYear, AMonth, ADay;
  DecodeDate( D, AYear, AMonth, ADay );
  if ( IsLeapYear( AYear ) && ( AMonth == 2 ) && ( ADay == 29 ) )
    ADay = 28;
  --AYear;
  return EncodeDate( AYear, AMonth, ADay );
}

TDateTime __fastcall NextYear( TDateTime D ) {
  unsigned short AYear, AMonth, ADay;
  DecodeDate( D, AYear, AMonth, ADay );
  if ( IsLeapYear( AYear ) && ( AMonth == 2 ) && ( ADay == 29 ) )
    ADay = 28;
  ++AYear;
  return EncodeDate( AYear, AMonth, ADay );
}

double __fastcall RoundEx( double X, int Precision ) {
  double IntX, ScaledFractPart, Temp;
  ScaledFractPart = modf( X, &IntX );
  ScaledFractPart = ScaledFractPart * Precision;
  Temp = modf( ScaledFractPart, &ScaledFractPart );
  if ( Temp >= 0.5 )
    ScaledFractPart = ScaledFractPart + 1;
  else if ( Temp <= -0.5 )
    ScaledFractPart = ScaledFractPart - 1;
  return IntX + ScaledFractPart / Precision;
}

double __fastcall AltRound( double X, int Precision ) {
  double div = 1.0;
  if ( Precision > 0 )
    while ( Precision-- )
      div *= 10.0;
  else
    while ( Precision++ )
      div /= 10.0;
  return floor( X * div + 0.5 ) / div;
}

TDateTime __fastcall TruncDate( const TDateTime &Value ) {
  Word Year, Month, Day;
  DecodeDate( Value, Year, Month, Day );
  return EncodeDate( Year, Month, Day );
}

double __fastcall WizardNDS( double Summa_, bool IsNDS_, double Percent_,
    TNDSKind NeedNDS_, double PercentComok_, bool ForComok_ ) {
  if ( Summa_ == 0 )
    return 0;
  double SWithoutComokAll, SComokAll;
  if ( PercentComok_ != 0 ) {
    if ( IsNDS_ == nkWO_NDS ) {
      SWithoutComokAll = Summa_;
      SComokAll = PercentComok_ * SWithoutComokAll / 100;
    }
    else {
      SComokAll = PercentComok_ * Summa_ / ( 100 + PercentComok_ );
      SWithoutComokAll = Summa_ - SComokAll;
    }
    if ( ForComok_ ) {
      Summa_ = SComokAll;
    }
    else {
      if ( NeedNDS_ == nkWO_NDS )
        return SWithoutComokAll;
      else
        throw Exception( "Непонятный тип преобразования NDS" );
    }
  }

  if ( Percent_ == 0 )
    return Summa_;
  if ( !IsNDS_ ) {
    if ( NeedNDS_ == nkWO_NDS )
      return Summa_;
    else if ( NeedNDS_ == nkWITH_NDS )
      return ( 100 + Percent_ ) * Summa_ / 100;
    else
      return Percent_ * Summa_ / 100;
  }
  else {
    if ( NeedNDS_ == nkWO_NDS )
      return 100 * Summa_ / ( 100 + Percent_ );
    else if ( NeedNDS_ == nkWITH_NDS )
      return Summa_;
    else
      return Percent_ * Summa_ / ( 100 + Percent_ );
  }
}

void __fastcall FormShow( TCommonCustomForm *Form ) {
  if ( Form->WindowState == TWindowState::wsMinimized )
    Form->WindowState = TWindowState::wsNormal;
  Form->Show( );
}

long double __fastcall LocalFactorial( long double R ) {
  if ( R == 0 )
    return 1;
  return R * Factorial( R - 1 );
}

long double __fastcall Factorial( long double R ) {
  long double i;
  modfl( R, &i );
  return LocalFactorial( i );
}

int pow2( int p ) {
  if ( p < 0 )
    return 0;
  if ( p == 0 )
    return 1;
  int rez = 1;
  for ( int i = 0; i < p; ++i )
    rez *= 2;
  return rez;
}

TCurrentOwner::TCurrentOwner( )
  : PK( -1 )
  , Level( 0 )
{
}

void __fastcall SetFieldValue( TField *Field, const Variant &Value ) {
  if ( Value.IsEmpty( ) )
    Field->Clear( );
  else
    Field->Value = Value;
}

bool __fastcall CompareVariant( const Variant &V1, const Variant &V2 ) {
  if ( V1.IsEmpty( ) ) {
    return V2.IsEmpty( );
  }
  else if ( V1.IsNull( ) ) {
    return V2.IsNull( );
  }
  else {
    if ( V2.IsEmpty( ) || V2.IsNull( ) )
      return false;
    else
      return V1 == V2;
  }
}

bool __fastcall IsEditModes( TDataSetState State_ ) {
  return State_ == dsEdit || State_ == dsInsert || State_ == dsSetKey;
}

void __fastcall SetFieldField( TField *FSource, TField *FTarget ) {
  if ( !FSource->IsNull )
    FTarget->Value = FSource->Value;
}

void __fastcall ClearDateSetText( TField *Sender, const UnicodeString Text )
{
  if ( Text == NNFConst::StrEmptyDateLong ||
       Text == NNFConst::StrEmptyDateShort )
    Sender->Clear();
  else {
    String S( Text );
    S.Unique();
    ReplaceChar( S.c_str(), ' ', '0' );
    Sender->AsString = S;
  }
}

String VariantToStr( const Variant &Value ) {
  if ( Value.IsEmpty( ) || Value.IsNull( ) )
    return "";
  else
    return Value;
}

String CriptPassword( String Password ) {
  if ( Password.IsEmpty( ) )
    return Password;
  return String( "S" ) + ConvertWord( Password ) + String( "L" );
}

TControl* __fastcall ControlAtPos( TControl *Win, TPoint p )
{
  int i;
  TControl *c;
  TControl *wc;
  TPoint p1;
  int N = Win->ChildrenCount;
  for ( i = N - 1; i >= 0; --i ) {
    c =  dynamic_cast< TControl* >( Win->Children->Items[ i ] );
    if ( c && c->Visible && PtInRect( c->BoundsRect, p ) ) {
      wc = c;
      if ( wc && wc->ChildrenCount > 0 ) {
        p1 = p;
        p1.x -= wc->Position->X;
        p1.y -= wc->Position->Y;
        c = NNF::ControlAtPos( wc, p1 );
        if ( c )
          return c;
      } else
        return c;
    }
  }
  if ( Win->Visible && PtInRect( Rect( 0, 0, Win->Width, Win->Height), p ) )
    return Win;
  else
    return nullptr;
}

bool __fastcall CompareBool( TBoolExtended Value, TField *Field )
{
  switch ( Value ) {
  case TBoolExtended::False :
    return Field->AsBoolean == false;
  case TBoolExtended::True :
    return Field->AsBoolean == true;
  case TBoolExtended::Empty :
    return Field->IsNull;
  case TBoolExtended::NotEmpty :
    return !Field->IsNull;
  case TBoolExtended::Any :
    return true;
  }
}

int __fastcall BoolToInt( bool Value ) {
  if ( Value )
    return 1;
  else
    return 0;
}

//void __fastcall SetColumnStory( TColumn *cl, const String &S, TCustomCombo *cc )
//{
//  if ( NNF::IsStringEmpty( S ) )
//    return;
//
//  TStrings *sl = cl->PickList;
//  int I = sl->IndexOf( S );
//
//  if ( I != -1 )
//    sl->Move( I, 0 );
//  else
//    sl->Insert( 0, S );
//
//  if ( sl->Count > NNFConst::limit_pick_list )
//    sl->Delete( sl->Count - 1 );
//
//  if ( cc )
//    cc->Items->Assign( sl );
//}

void __fastcall SetComboStory( const String &S
                             , TCustomComboEdit *cc )
{
  if ( NNF::IsStringEmpty( S ) ) return;
  std::auto_ptr< TStringList > sl( new TStringList() );
  sl->Assign( cc->Items );
  int I = sl->IndexOf( S );
  if ( I != -1 )
    sl->Move( I, 0 );
  else
    sl->Insert( 0, S );
  if ( sl->Count > NNFConst::limit_pick_list )
    sl->Delete( sl->Count - 1 );
  if ( cc )
    cc->Items->Assign( sl.get() );
}

TCursorMagic::TCursorMagic( TCursor NewCursor_ )
  : OldCursor( Screen->ActiveForm->Cursor )
{
  Screen->ActiveForm->Cursor = NewCursor_;
}

TCursorMagic::~TCursorMagic()
{
  Screen->ActiveForm->Cursor = OldCursor;
}

void __fastcall OtherUserException( ) {
  throw Exception( String( NNFConst::OtherUserChangeRecord ) +
      NNFConst::FieldUserChange );
}

void __fastcall SaveStrings( const String &AText, TStrings *SL, int Limit_ )
{
  if ( AText.IsEmpty( ) )
    return;

  int i = SL->IndexOf( AText );

  if ( i != -1 )
    SL->Move( i, 0 );
  else
    SL->Insert( 0, AText );

  if ( SL->Count > Limit_ )
    SL->Delete( SL->Count - 1 );
}

void __fastcall SaveComboBox( TComboBox *cb, int Limit_ )
{
  if ( cb->Data.AsString().IsEmpty() ) return;
  int i = cb->ItemIndex;
  if ( i == -1 )
    i = cb->Items->IndexOf( cb->Data.AsString() );
  if ( i != -1 )
    cb->Items->Move( i, 0 );
  else
    cb->Items->Insert( 0, cb->Data.AsString() );
  if ( cb->Items->Count > Limit_ )
    cb->Items->Delete( cb->Items->Count - 1 );
  cb->ItemIndex = 0;
}

void __fastcall SaveComboBox( TComboEdit *cb, int Limit_ )
{
  if ( cb->Text.IsEmpty() ) return;
  int i = cb->ItemIndex;
  if ( i == -1 )
    i = cb->Items->IndexOf( cb->Text );
  if ( i != -1 )
    cb->Items->Move( i, 0 );
  else
    cb->Items->Insert( 0, cb->Text );
  if ( cb->Items->Count > Limit_ )
    cb->Items->Delete( cb->Items->Count - 1 );
  cb->ItemIndex = 0;
}

double __fastcall ConvertPrice( double Price, double FromCurs, double FromCoef,
    double ToCurs, double ToCoef ) {
  // Формула такова:
  // R = ( Price * FromCurs / FromCoef ) / ( ToCurs / ToCoef );
  double R = Price * FromCurs;
  R /= FromCoef;
  R *= ToCoef;
  R /= ToCurs;
  return R;
}


void __fastcall FormListShow()
{
//  FormCreate( __classid( TfmvFormList ), &fmvFormList );
//  TCommonCustomForm *f = fmvFormList->GetForm();
//  if( f )
//    FormShow( f );
}

void __fastcall FormLocaleFormat( TCommonCustomForm *fm )
{
  TField *f;

  int N = fm->ComponentCount, i;

  NNFConst::LocaleFormatRun = true;
  try {
    for( i = 0; i < N; ++i ) {
      f = dynamic_cast< TDateField* >( fm->Components[ i ] );
      if ( f ) {
        f->EditMask = NNFConst::EditMaskDateFormatShort;
      } else {
        f = dynamic_cast< TSQLTimeStampField* >( fm->Components[ i ] );
        if ( f ) {
          f->EditMask = NNFConst::EditMaskDateFormatLong;
        }
      }
    }
  } __finally {
    NNFConst::LocaleFormatRun = false;
  }
}

void __fastcall DataModuleLocaleFormat( TDataModule *dm )
{
  TField *f;

  int N = dm->ComponentCount, i;

  NNFConst::LocaleFormatRun = true;
  try {
    for( i = 0; i < N; ++i ) {
      f = dynamic_cast< TDateField* >( dm->Components[ i ] );
      if ( f ) {
        f->EditMask      = NNFConst::EditMaskDateFormatShort;
      } else {
        f = dynamic_cast< TSQLTimeStampField* >( dm->Components[ i ] );
        if ( f ) {
          f->EditMask      = NNFConst::EditMaskDateFormatLong;
        }
      }
    }
  } __finally {
    NNFConst::LocaleFormatRun = false;
  }
}

void __fastcall SyncLocaleFormat( /*double EnterpriseNo_*/ )
{
  //cw::TEnterpriseManager::const_iterator ie = EnterpriseManager->FindEnterprise( EnterpriseNo_ );

  int N = Screen->DataModuleCount, i;

  for( i = 0; i < N; ++i )
    DataModuleLocaleFormat( Screen->DataModules[ i ] );

  N = Screen->FormCount;

  for( i = 0; i < N; ++i )
    FormLocaleFormat( Screen->Forms[ i ] );
}

void __fastcall ClearScrollBox( TScrollBox *AScrollBox )
{
  int L = AScrollBox->ControlsCount;
  for ( int I = L - 1; I >= 0; --I )
    delete AScrollBox->Controls->Items[ I ];
}

void __fastcall SetNameToComponent( TComponent *AComponent, int &ANumber )
{
  if ( !AComponent )
    return;

  String S = AComponent->Name;
  if ( S.IsEmpty() )
    S = AComponent->ClassName();

  AComponent->Name = S + IntToStr( ++ANumber );
}

void __fastcall SetNameToComponent( TComponent *AComponent, TField *ASearchField, int &ANumber )
{
  if ( !AComponent )
    return;

  String S = AComponent->Name;
  if ( S.IsEmpty() )
    S = AComponent->ClassName();

  String FN = ASearchField->Name;
  if ( FN.IsEmpty() )
    FN = IntToStr( ++ANumber );

  AComponent->Name = S + FN;
}

}

__fastcall TNNFTextStream::TNNFTextStream( TStream *AStream )
  : inherited()
  , fIsDeleteStream( false )
{
  if ( AStream == nullptr ) {
    fStream = new TMemoryStream;
    fIsDeleteStream = true;
  } else
    fStream = AStream;
}

_fastcall TNNFTextStream::~TNNFTextStream()
{
  if ( fIsDeleteStream )
    delete fStream;
}

bool __fastcall TNNFTextStream::ReadBool()
{
  bool R;
  Read( &R, sizeof( R ) );
  return R;
}

char __fastcall TNNFTextStream::ReadChar()
{
  char R;
  Read( &R, sizeof( R ) );
  return R;
}

unsigned char __fastcall TNNFTextStream::ReadUnsignedChar()
{
  unsigned char R;
  Read( &R, sizeof( R ) );
  return R;
}

int __fastcall TNNFTextStream::ReadInt()
{
  int R;
  Read( &R, sizeof( R ) );
  return R;
}

short int __fastcall TNNFTextStream::ReadShortInt()
{
  short int R;
  Read( &R, sizeof( R ) );
  return R;
}

unsigned short int __fastcall TNNFTextStream::ReadUnsignedShortInt()
{
  short int R;
  Read( &R, sizeof( R ) );
  return R;
}

std::size_t __fastcall TNNFTextStream::ReadSizeType()
{
  std::size_t R;
  Read( &R, sizeof( R ) );
  return R;
}

NativeInt __fastcall TNNFTextStream::ReadNativeInt()
{
  NativeInt R;
  Read( &R, sizeof( R ) );
  return R;
}

unsigned int __fastcall TNNFTextStream::ReadUnsignedInt()
{
  unsigned int R;
  Read( &R, sizeof( R ) );
  return R;
}

TDateTime __fastcall TNNFTextStream::ReadDateTime()
{
  TDateTime R;
  Read( &R, sizeof( R ) );
  return R;
}

short int __fastcall TNNFTextStream::ReadShort()
{
  short int R;
  Read( &R, sizeof( R ) );
  return R;
}

unsigned short int __fastcall TNNFTextStream::ReadUnsignedShort()
{
  unsigned short int R;
  Read( &R, sizeof( R ) );
  return R;
}

long int __fastcall TNNFTextStream::ReadLongInt()
{
  long int R;
  Read( &R, sizeof( R ) );
  return R;
}

long long int __fastcall TNNFTextStream::ReadLongLongInt()
{
  long long int R;
  Read( &R, sizeof( R ) );
  return R;
}

unsigned long int __fastcall TNNFTextStream::ReadUnsignedLongInt()
{
  unsigned long int R;
  Read( &R, sizeof( R ) );
  return R;
}

unsigned long long int __fastcall TNNFTextStream::ReadUnsignedLongLongInt()
{
  unsigned long long int R;
  Read( &R, sizeof( R ) );
  return R;
}

float __fastcall TNNFTextStream::ReadFloat()
{
  float R;
  Read( &R, sizeof( R ) );
  return R;
}

double __fastcall TNNFTextStream::ReadDouble()
{
  double R;
  Read( &R, sizeof( R ) );
  return R;
}

long double __fastcall TNNFTextStream::ReadLongDouble()
{
  long double R;
  Read( &R, sizeof( R ) );
  return R;
}

TAlphaColor __fastcall TNNFTextStream::ReadColor()
{
  TAlphaColor R;
  Read( &R, sizeof( R ) );
  return R;
}

TTextAlign __fastcall TNNFTextStream::ReadTextAlign()
{
  TTextAlign R;
  Read( &R, sizeof( R ) );
  return R;
}

TTextTrimming __fastcall TNNFTextStream::ReadTextTrimming()
{
  TTextTrimming R;
  Read( &R, sizeof( R ) );
  return R;
}

String __fastcall TNNFTextStream::ReadString()
{
  UTF8String S;
  String R;
  int BufSize;
  Read( &BufSize, sizeof( BufSize ) );
  S.SetLength( BufSize );
  Read( S.c_str(), BufSize );
  R = String( S );
  return R;
}

void __fastcall TNNFTextStream::WriteString( const String &Value )
{
  UTF8String S( Value );
  int R = S.Length();
  Write( &R, sizeof( R ) );
  Write( S.c_str(), R );
}

bool __fastcall TNNFTextStream::ReadStringLine( String &S )
{
  long long int SP = Position;

  UTF8String R;
  NativeInt BufSize = 0, MinusOffset = 0;

  char C;
  while ( !IsEof() ) {
    Read( &C, sizeof( C ) );
    if ( C == '\r' ) {
      ++MinusOffset;
      if ( !IsEof() ) {
        Read( &C, sizeof( C ) );
        if ( C == '\n' ) {
          ++MinusOffset;
          break;
        } else {
          ++BufSize;
          MinusOffset = 0;
        }
      }
    }
    ++BufSize;
  }

  if ( BufSize > 0 ) {
    Seek( SP, soBeginning );
    R.SetLength( BufSize );
    Read( R.c_str(), BufSize );
    Seek( MinusOffset, soCurrent );
    S = String( R );
    return true;
  } else {
    S = L"";
    return false;
  }
}

AnsiString __fastcall TNNFTextStream::ReadAnsiString()
{
  AnsiString R;
  int BufSize;
  Read( &BufSize, sizeof( BufSize ) );
  R.SetLength( BufSize );
  Read( R.c_str(), BufSize );
  return R;
}

void __fastcall TNNFTextStream::WriteAnsiString( const AnsiString &Value )
{
  int R = Value.Length();
  Write( &R, sizeof( R ) );
  Write( Value.c_str(), R );
}

void __fastcall TNNFTextStream::ReadBinaryData( void *Buffer )
{
  int BufSize;
  Read( &BufSize, sizeof( BufSize ) );
  Read( Buffer, BufSize );
}

void __fastcall TNNFTextStream::ReadFiler( TNNFTextStream *filer )
{
  ( ( TMemoryStream* )filer->Stream )->SetSize( ReadInt() );
  Read( ( ( TMemoryStream* )filer->Stream )->Memory, filer->Stream->Size );
}

void __fastcall TNNFTextStream::WriteFiler( TNNFTextStream *filer )
{
  WriteInt( filer->Stream->Size );
  filer->Position = 0;
  Write( ( ( TMemoryStream* )filer->Stream )->Memory, filer->Stream->Size );
}

void __fastcall TNNFTextStream::ReadFont( TFont* AFont )
{
  std::unique_ptr< TFont > f( new TFont() );
  f->Family = ReadString();
  f->Size = ReadInt();
  TFontStyles RS;
  Read( &RS, sizeof( RS ) );
  f->Style = RS;
  TFontStyleExt RSE;
  Read( &RSE, sizeof( RSE ) );
  f->StyleExt = RSE;
  AFont->Assign( f.get() );
}

void __fastcall TNNFTextStream::WriteFont( TFont* AFont )
{
  WriteString( AFont->Family );
  WriteInt( AFont->Size );
  TFontStyles RS = AFont->Style;
  Write( &RS, sizeof( RS ) );
  TFontStyleExt RSE = AFont->StyleExt;
  Write( &RSE, sizeof( RSE ) );
}

void __fastcall TNNFTextStream::ReadFontColorForState( TFontColorForState* A )
{
  std::unique_ptr< TTextSettings > ts( new TTextSettings( A->Owner ) );
  std::unique_ptr< TFontColorForState > f( new TFontColorForState( ts.get() ) );

  f->Active  = ReadColor();
  f->Focused = ReadColor();
  f->Hot     = ReadColor();
  f->Normal  = ReadColor();
  f->Pressed = ReadColor();

  A->Assign( f.get() );
}

void __fastcall TNNFTextStream::WriteFontColorForState( TFontColorForState* A )
{
  WriteColor( A->Active  );
  WriteColor( A->Focused );
  WriteColor( A->Hot     );
  WriteColor( A->Normal  );
  WriteColor( A->Pressed );
}

void __fastcall TNNFTextStream::ReadTextSettings( TTextSettings* ATextSettings )
{
  ReadFont( ATextSettings->Font );
  ATextSettings->FontColor = ReadColor();
  ReadFontColorForState( ATextSettings->FontColorForState );
  ATextSettings->IsAdjustChanged = ReadBool();
  ATextSettings->HorzAlign = ReadTextAlign();
  ATextSettings->IsAdjustChanged = ReadBool();
  ATextSettings->IsChanged = ReadBool();
  ATextSettings->Trimming = ReadTextTrimming();
  ATextSettings->VertAlign = ReadTextAlign();
  ATextSettings->WordWrap = ReadBool();
}

void __fastcall TNNFTextStream::WriteTextSettings( TTextSettings* ATextSettings )
{
  WriteFont( ATextSettings->Font );
  WriteColor( ATextSettings->FontColor );
  WriteFontColorForState( ATextSettings->FontColorForState );
  WriteBool( ATextSettings->IsAdjustChanged );
  WriteTextAlign( ATextSettings->HorzAlign );
  WriteBool( ATextSettings->IsAdjustChanged );
  WriteBool( ATextSettings->IsChanged );
  WriteTextTrimming( ATextSettings->Trimming );
  WriteTextAlign( ATextSettings->VertAlign );
  WriteBool( ATextSettings->WordWrap );
}

TShortCut __fastcall TNNFTextStream::ReadShortCut()
{
  TShortCut R;
  Read( &R, sizeof( R ) );
  return R;
}

void __fastcall TNNFTextStream::ResetVersion()
{
  if ( Size == 0 )
    return;
  long long int P = Position;
  unsigned char R;
  Read( &R, sizeof( R ) );
  Position = 0;
  ++R;
  Write( &R, sizeof( R ) );
  Position = P;
}

Variant __fastcall TNNFTextStream::ReadDoubleVariant()
{
  bool IsNull;
  Variant V;
  Read( &IsNull, sizeof( IsNull ) );
  if ( IsNull )
    V.Clear();
  else {
    double R;
    Read( &R, sizeof( R ) );
    V = R;
  }
  return V;
}

void __fastcall TNNFTextStream::WriteDoubleVariant( const Variant &R )
{
  bool IsNull = R.IsNull();
  WriteBool( IsNull );
  if ( !IsNull ) {
    double D = R;
    WriteDouble( D );
  }
}

Variant __fastcall TNNFTextStream::ReadDateTimeVariant()
{
  bool IsNull;
  Variant V;
  Read( &IsNull, sizeof( IsNull ) );
  if ( IsNull )
    V.Clear();
  else {
    TDateTime R;
    Read( &R, sizeof( R ) );
    V = R;
  }
  return V;
}

void __fastcall TNNFTextStream::WriteDateTimeVariant( const Variant &R )
{
  bool IsNull = R.IsNull();
  WriteBool( IsNull );
  if ( !IsNull ) {
    TDateTime D = R;
    WriteDateTime( D );
  }
}

Variant __fastcall TNNFTextStream::ReadStringVariant()
{
  bool IsNull;
  Variant V;
  Read( &IsNull, sizeof( IsNull ) );
  if ( IsNull )
    V.Clear();
  else {
    String S = ReadString();
    V = S;
  }
  return V;
}

void __fastcall TNNFTextStream::WriteStringVariant( const Variant &R )
{
  bool IsNull = R.IsNull();
  WriteBool( IsNull );
  if ( !IsNull ) {
    String S = R;
    WriteString( S );
  }
}

NNF::TBoolExtended __fastcall TNNFTextStream::ReadBoolExtended()
{
  NNF::TBoolExtended R;
  Read( &R, sizeof( R ) );
  return R;
}

NNF::TPeriod __fastcall TNNFTextStream::ReadPeriod()
{
  NNF::TPeriod R;
  Read( &R, sizeof( R ) );
  return R;
}

NNF::TShortIntDiapazon __fastcall TNNFTextStream::ReadShortIntDiapazon()
{
  NNF::TShortIntDiapazon R;
  Read( &R, sizeof( R ) );
  return R;
}

NNF::TIntDiapazon __fastcall TNNFTextStream::ReadIntDiapazon()
{
  NNF::TIntDiapazon R;
  Read( &R, sizeof( R ) );
  return R;
}

NNF::TLongLongIntDiapazon __fastcall TNNFTextStream::ReadLongLongIntDiapazon()
{
  NNF::TLongLongIntDiapazon R;
  Read( &R, sizeof( R ) );
  return R;
}

NNF::TDoubleDiapazon __fastcall TNNFTextStream::ReadDoubleDiapazon()
{
  NNF::TDoubleDiapazon R;
  Read( &R, sizeof( R ) );
  return R;
}

namespace NNF {

TMapFiler::TMapFiler()
  : inherited()
{
}

TMapFiler::~TMapFiler()
{
  for ( iterator i = begin(); i != end(); ++i )
    delete ( *i ).second;
}

TNNFTextStream* __fastcall TMapFiler::GetFiler( const String &AKeyRegistry )
{
  iterator i = find( AKeyRegistry );
  if ( i == end() ) {
    TNNFTextStream* Filer = new TNNFTextStream( nullptr );
    ( *this )[ AKeyRegistry ] = Filer;
    return Filer;
  } else
    return ( *i ).second;
}

void __fastcall TMapFiler::SaveToFiler( TNNFTextStream *Filer )
{
  Filer->WriteSizeType( size() );
  for ( iterator i = begin(); i != end(); ++i ) {
    Filer->WriteString( ( *i ).first );
    Filer->WriteFiler( ( *i ).second );
  }
}

void __fastcall TMapFiler::LoadFromFiler( TNNFTextStream *Filer )
{
  String AKeyRegistry;
  TNNFTextStream *F;
  std::size_t MapSize = Filer->ReadSizeType();
  for ( std::size_t i = 0; i < MapSize; ++i ) {
    AKeyRegistry = Filer->ReadString();
    F = new TNNFTextStream( nullptr );
    Filer->ReadFiler( F );
    ( *this )[ AKeyRegistry ] = F;
  }
}

}

