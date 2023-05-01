// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef VCL_NNCommonH
#define VCL_NNCommonH

#include "VCL_NNCommon.h"
#include <Data.DB.hpp>
#include <Vcl.DBGrids.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <vector>
#include <map>
#include <set>

class TNNVTextStream;
PACKAGE enum TNNVStoreKind { skFile, skFiler, skDB };
using TNNVGetFiler = PACKAGE void __fastcall( __closure * ) ( System::TObject *Sender, TNNVTextStream *&Filer );

namespace NNV {

extern PACKAGE String __fastcall RemoveDiacritics( const String& S );
extern PACKAGE bool __fastcall PrabhupadaComareLess( const String& A, const String& B );
extern PACKAGE bool __fastcall PrabhupadaComareMore( const String& A, const String& B );

class PACKAGE TStringMap : public std::map< String, String >
{
private:
  using inherited = std::map< String, String >;
public:
  TStringMap();
  ~TStringMap();
};

class PACKAGE TStringSet : public std::set< String >
{
private:
  using inherited = std::set< String >;
public:
  TStringSet();
  ~TStringSet();
};

class PACKAGE TFilterSlovar
{
private:
  String FSanskrit;
  String FPerevod;
  String FSanskritWithoutDiakritik;
  String FPerevodWithoutDiakritik;
  bool FIsEmpty = true;
  bool FIsReset = true;
  void __fastcall SetSanskrit( const String &Value );
  void __fastcall SetPerevod( const String &Value );
public:
  TFilterSlovar();
  TFilterSlovar( const TFilterSlovar &A );
  TFilterSlovar( const String &ASanskrit
               , const String &APerevod );
  ~TFilterSlovar();
  TFilterSlovar& operator = ( const TFilterSlovar & a );

  void __fastcall LoadFromFiler( TNNVTextStream *Filer );
  void __fastcall SaveToFiler( TNNVTextStream *Filer );

  __property String Sanskrit = { read = FSanskrit, write = SetSanskrit };
  __property String Perevod = { read = FPerevod, write = SetPerevod };
  __property String SanskritWithoutDiakritik = { read = FSanskritWithoutDiakritik, write = FSanskritWithoutDiakritik };
  __property String PerevodWithoutDiakritik = { read = FPerevodWithoutDiakritik, write = FPerevodWithoutDiakritik };
  __property bool IsEmpty = { read = FIsEmpty, write = FIsEmpty };
  __property bool IsReset = { read = FIsReset, write = FIsReset };

  bool operator == ( const TFilterSlovar& F )
  {
    return ( Sanskrit == F.Sanskrit ) && ( Perevod == F.Perevod );
  }
  bool operator != ( const TFilterSlovar& F )
  {
    return ( ( Sanskrit != F.Sanskrit ) || ( Perevod != F.Perevod ) );
  }
  bool GetIsEmpty() const
  {
    return Sanskrit.IsEmpty() && Perevod.IsEmpty();
  }
  void Clear()
  {
    Sanskrit = L"";
    Perevod  = L"";
  }
};

class PACKAGE TPrabhupadaBukva
{
private:
  WideChar FBukva;
  int FVes;
public:
  TPrabhupadaBukva();
  ~TPrabhupadaBukva();
  __property WideChar Bukva = { read = FBukva, write = FBukva };
  __property int Ves = { read = FVes, write = FVes };
};

class PACKAGE TPrabhupadaBukvary : public std::map< WideChar, TPrabhupadaBukva >
{
private:
  using inherited = std::map< WideChar, TPrabhupadaBukva >;
public:
  TPrabhupadaBukvary();
  ~TPrabhupadaBukvary();
};

PACKAGE enum class TOrderBy : int
{
  SanskritVozrastanie
, SanskritUbyvanie
, PerevodVozrastanie
, PerevodUbyvanie
};

class PACKAGE TSanskritPerevod
{
private:
  int FID;
  String FSanskrit;
  String FPerevod;
  String FSanskritWithoutDiakritik;
  String FPerevodWithoutDiakritik;
public:
  // обходимся без конструктора копирования и оператора присваивания!
  // так он надежнее, быстрее работает
  TSanskritPerevod();
  ~TSanskritPerevod();

  __property String Sanskrit = { read = FSanskrit, write = FSanskrit };
  __property String Perevod = { read = FPerevod, write = FPerevod };
  __property String SanskritWithoutDiakritik = { read = FSanskritWithoutDiakritik, write = FSanskritWithoutDiakritik };
  __property String PerevodWithoutDiakritik = { read = FPerevodWithoutDiakritik, write = FPerevodWithoutDiakritik };
  __property int ID = { read = FID, write = FID };
};

class PACKAGE TPrabhupadaSlovarVector : public std::vector< TSanskritPerevod* >
{
private:
  using inherited = std::vector< TSanskritPerevod* >;
public:
  TPrabhupadaSlovarVector();
  ~TPrabhupadaSlovarVector();
};

class PACKAGE TPrabhupadaSearchVector : public std::vector< int >
{
private:
  using inherited = std::vector< int >;
  int FSearchCount = 0;
public:
  TPrabhupadaSearchVector();
  ~TPrabhupadaSearchVector();
  __property int SearchCount = { read = FSearchCount, write = FSearchCount };
};

class PACKAGE TPrabhupadaZakladka
{
private:
  int FRowNum;
  TFilterSlovar FFilterSlovar;
public:
  TPrabhupadaZakladka();
  TPrabhupadaZakladka( int ARowNum
                     , TFilterSlovar AFilterSlovar );
  ~TPrabhupadaZakladka();

  void __fastcall LoadFromFiler( TNNVTextStream *Filer );
  void __fastcall SaveToFiler( TNNVTextStream *Filer );

  __property int RowNum = { read = FRowNum, write = FRowNum };
  __property TFilterSlovar FilterSlovar = { read = FFilterSlovar };
};

class PACKAGE TPrabhupadaZakladkaMap : public std::map< unsigned short, TPrabhupadaZakladka >
{
private:
  using inherited = std::map< unsigned short, TPrabhupadaZakladka >;
public:
  TPrabhupadaZakladkaMap();
  ~TPrabhupadaZakladkaMap();
  void __fastcall LoadFromFiler( TNNVTextStream *Filer );
  void __fastcall SaveToFiler( TNNVTextStream *Filer );
};

class PACKAGE TYazykInfo
{
private:
  int FID;
  String FYazyk;
  String FYazykSlovo;
  int FCurrentRow = 0;
  TFilterSlovar FFilterSlovar;
  TPrabhupadaZakladkaMap FPrabhupadaZakladkaMap;
public:
  TYazykInfo();
  TYazykInfo( const TYazykInfo &A );
  ~TYazykInfo();
  __property int ID = { read = FID, write = FID };
  __property String Yazyk = { read = FYazyk, write = FYazyk };
  __property String YazykSlovo = { read = FYazykSlovo, write = FYazykSlovo };
  __property TFilterSlovar FilterSlovar = { read = FFilterSlovar, write = FFilterSlovar };
  __property int CurrentRow = { read = FCurrentRow, write = FCurrentRow };
  __property TPrabhupadaZakladkaMap PrabhupadaZakladkaMap = { read = FPrabhupadaZakladkaMap };
};

class PACKAGE TYazykVector : public std::vector< TYazykInfo >
{
private:
  using inherited = std::vector< TYazykInfo >;
public:
  TYazykVector();
  ~TYazykVector();
  int __fastcall FindYazyk( const String &S );
  void __fastcall LoadFromFiler( TNNVTextStream *Filer );
  void __fastcall SaveToFiler( TNNVTextStream *Filer );
};

PACKAGE enum class TBoolExtended : int
{
  False
, True
, Empty
, NotEmpty
, Any
};

PACKAGE enum class TCheckStyleValue : int
{
  None
, Equal
, Greater
, GreaterOrEqual
, Less
, LessOrEqual
};

using TVectorCheckStyleValue = std::vector< TCheckStyleValue >;

PACKAGE enum class TCheckStyleSetKind : int
{
  None
, FullSet
, FullSetWithoutNone
, Greater
, Less
};

PACKAGE enum class TDiapazonKind : int
{
  Inner
, Outer
, HalfDiapazon
, Null
, NotNull
};

union TNumberUnion
{
public:
  short int ShortInt;
  int Int;
  long long int LongLongInt;
  double Double;
};

PACKAGE enum class TNumberKind : int
{
  ShortInt
, Int
, LongLongInt
, Double
};

PACKAGE enum TNDSKind
{
  nkWO_NDS   = 0
, nkWITH_NDS = 1
, nkONLY_NDS = 2
};

PACKAGE enum TSkilfulBool
{
  sbYes = 0
, sbNo  = 1
, sbAny = 2
};

PACKAGE enum class TEnterKind : int
{
  Enter
, Down
, Like
};

extern PACKAGE String __fastcall PrefixCheckStyleValue( TCheckStyleValue ACheckStyle );
extern PACKAGE String __fastcall PrefixFormatCheckStyleValue( TCheckStyleValue ACheckStyle );
extern PACKAGE bool __fastcall FormExists(TMetaClass* InstanceClass,
    void *Reference);
extern PACKAGE bool __fastcall FormExists(TCustomForm *fm);
extern PACKAGE void __fastcall FormCreate(TMetaClass* InstanceClass,
    void *Reference);
extern PACKAGE bool __fastcall DMExists(TMetaClass* InstanceClass,
    void *Reference);
extern PACKAGE bool __fastcall DMExists(TDataModule *fm);
extern PACKAGE void __fastcall DMCreate(TMetaClass* InstanceClass,
    void *Reference);
extern PACKAGE String __fastcall ComponentToKey( TComponent *AComponent
                                               , bool UseOwnerName );
extern PACKAGE String __fastcall UpdateStatusToStr(TUpdateStatus Value);
extern PACKAGE String __fastcall DataSetStateToStr(TDataSetState Value);
extern PACKAGE TDataModule* __fastcall StrToDataModule(const String AName);
extern PACKAGE TDataSet* __fastcall StrToDataSet(String &AText,
    TComponent *AOwner, bool RaiseExcept);
extern PACKAGE TRect __fastcall CalcRect(TRect ARect, TRect RC);
extern PACKAGE bool __fastcall IsLeapYear(int AYear);
extern PACKAGE TDateTime __fastcall PriorMonth(TDateTime D);
extern PACKAGE TDateTime __fastcall NextMonth(TDateTime D);
extern PACKAGE TDateTime __fastcall PriorYear(TDateTime D);
extern PACKAGE TDateTime __fastcall NextYear(TDateTime D);
// Precision :
// 1   - до целых
// 10  - до десятых
// 100 - до сотых
// ...
extern PACKAGE double __fastcall RoundEx(double X, int Precision);
extern PACKAGE double __fastcall AltRound(double X, int Precision);
extern PACKAGE TDateTime __fastcall TruncDate(const TDateTime &Value);
extern PACKAGE double __fastcall WizardNDS(double Summa_, bool IsNDS_,
    double Percent_, TNDSKind NeedNDS_, double PercentComok_ = 0,
    bool ForComok_ = false);
extern PACKAGE void __fastcall FormShow(TCustomForm *Form);
extern PACKAGE long double __fastcall Factorial(long double R);
extern PACKAGE void __fastcall OtherUserException();
extern PACKAGE void __fastcall SaveStrings( const String &AText, TStrings *SL, int Limit_ );
extern PACKAGE void __fastcall SaveComboBox( TComboBox *cb, int Limit_ );
extern PACKAGE void __fastcall SetFieldValue( TField *Field, const Variant &Value );
extern PACKAGE bool __fastcall CompareVariant( const Variant &V1, const Variant &V2 );
extern PACKAGE bool __fastcall IsEditModes(TDataSetState State_);
extern PACKAGE void __fastcall SetFieldField( TField *FSource, TField *FTarget );
extern PACKAGE void __fastcall ClearDateSetText( TField *Sender
                                               , const UnicodeString Text );
extern PACKAGE String VariantToStr(const Variant &Value);
extern PACKAGE String CriptPassword(String Password);
extern PACKAGE TControl* __fastcall ControlAtPos( TWinControl *Win, TPoint p );
extern PACKAGE bool __fastcall CompareBool( TBoolExtended Value, TField *Field );

class PACKAGE TCurrentOwner {
public:
  TCurrentOwner();

  double PK;
  double Level;
};

PACKAGE enum TTriggerMode
{
  AfterDelete
, AfterUpdate
, AfterInsert
, AfterAnother
};

template < class TValue >
class PACKAGE TDiapazon
{
private:
  TCheckStyleValue FBeginCheckStyle = TCheckStyleValue::GreaterOrEqual;
  TDiapazonKind FDiapazonKind = TDiapazonKind::Inner;
  TValue FBegin = TValue();
  TCheckStyleValue FEndCheckStyle = TCheckStyleValue::LessOrEqual;;
  TValue FEnd = TValue();
public:
  TDiapazon();
  TDiapazon( TCheckStyleValue ABeginCheckStyle
           , TValue ABegin
           , TCheckStyleValue AEndCheckStyle
           , TValue AEnd );
  bool Check( TValue Value );
  bool Check( TField *Field );
  bool operator != ( const TDiapazon< TValue > &P ) const;
  __property TCheckStyleValue BeginCheckStyle = { read = FBeginCheckStyle, write = FBeginCheckStyle };
  __property TDiapazonKind DiapazonKind = { read = FDiapazonKind, write = FDiapazonKind };
  __property TValue Begin = { read = FBegin, write = FBegin };
  __property TCheckStyleValue EndCheckStyle = { read = FEndCheckStyle, write = FEndCheckStyle };
  __property TValue End = { read = FEnd, write = FEnd };
};

template < class TValue >
TDiapazon< TValue >::TDiapazon()
{
  TValue D = TValue();

  FBegin = D - 1;
  FEnd   = D;
}

template < class TValue >
TDiapazon< TValue >::TDiapazon(  TCheckStyleValue ABeginCheckStyle
                              , TValue ABegin
                              , TCheckStyleValue AEndCheckStyle
                              , TValue AEnd )
: FBeginCheckStyle( ABeginCheckStyle )
, FBegin( ABegin )
, FEndCheckStyle( AEndCheckStyle )
, FEnd( AEnd )
{
}

template < class TValue >
bool TDiapazon< TValue >:: operator != ( const TDiapazon< TValue > &P ) const
{
  return BeginCheckStyle != P.BeginCheckStyle
      || Begin           != P.Begin
      || EndCheckStyle   != P.EndCheckStyle
      || End             != P.End;
}

template < class TValue >
bool TDiapazon< TValue >::Check( TValue Value )
{
  TValue N = TValue();
  bool B = false;

  switch ( (int)DiapazonKind ) {
  case (int)TDiapazonKind::Inner :
  case (int)TDiapazonKind::Outer :
  case (int)TDiapazonKind::HalfDiapazon :

    switch ( (int)BeginCheckStyle ) {
    case (int)TCheckStyleValue::None :
      B = Value >= Begin;
      break;
    case (int)TCheckStyleValue::Equal :
      B = Value == Begin;
      break;
    case (int)TCheckStyleValue::Greater :
      B = Value > Begin;
      break;
    case (int)TCheckStyleValue::GreaterOrEqual :
      B = Value >= Begin;
      break;
    case (int)TCheckStyleValue::Less :
      B = Value < Begin;
      break;
    case (int)TCheckStyleValue::LessOrEqual :
      B = Value <= Begin;
    }

    if ( (int)DiapazonKind == (int)TDiapazonKind::HalfDiapazon )
      return B;

    switch ( (int)EndCheckStyle ) {
    case (int)TCheckStyleValue::None :
      B = Value >= End;
      break;
    case (int)TCheckStyleValue::Equal :
      B = Value == End;
      break;
    case (int)TCheckStyleValue::Greater :
      B = B && Value > End;
      break;
    case (int)TCheckStyleValue::GreaterOrEqual :
      B = B && Value >= End;
      break;
    case (int)TCheckStyleValue::Less :
      B = B && Value < End;
      break;
    case (int)TCheckStyleValue::LessOrEqual :
      B = B && Value <= End;
    }

    return B;
  case (int)TDiapazonKind::Null :
    return Value == N;
  case (int)TDiapazonKind::NotNull :
    return Value != N;
  }

  return B;
}

template < class TValue >
bool TDiapazon< TValue >::Check( TField *Field )
{
  if ( !Field )
    return false;

  bool FieldIsNull = Field->IsNull;

  if ( DiapazonKind == TDiapazonKind::Null )
    return FieldIsNull;

  if ( DiapazonKind == TDiapazonKind::NotNull )
    return !FieldIsNull;

  if ( FieldIsNull )
    return false;

  TValue Value = Field->Value;
  bool B = false;

  switch ( (int)DiapazonKind ) {
  case (int)TDiapazonKind::Inner :
  case (int)TDiapazonKind::Outer :
  case (int)TDiapazonKind::HalfDiapazon :

    switch ( (int)BeginCheckStyle ) {
    case (int)TCheckStyleValue::None :
      B = Value >= Begin;
      break;
    case (int)TCheckStyleValue::Equal :
      B = Value == Begin;
      break;
    case (int)TCheckStyleValue::Greater :
      B = Value > Begin;
      break;
    case (int)TCheckStyleValue::GreaterOrEqual :
      B = Value >= Begin;
      break;
    case (int)TCheckStyleValue::Less :
      B = Value < Begin;
      break;
    case (int)TCheckStyleValue::LessOrEqual :
      B = Value <= Begin;
    }

    if ( (int)DiapazonKind == (int)TDiapazonKind::HalfDiapazon )
      return B;

    switch ( (int)EndCheckStyle ) {
    case (int)TCheckStyleValue::None :
      B = Value <= End;
      break;
    case (int)TCheckStyleValue::Equal :
      B = Value == End;
      break;
    case (int)TCheckStyleValue::Greater :
      B = B && Value > End;
      break;
    case (int)TCheckStyleValue::GreaterOrEqual :
      B = B && Value >= End;
      break;
    case (int)TCheckStyleValue::Less :
      B = B && Value < End;
      break;
    case (int)TCheckStyleValue::LessOrEqual :
      B = B && Value <= End;
    }

    return B;
  case (int)TDiapazonKind::Null :
    return Field->IsNull;
  case (int)TDiapazonKind::NotNull :
    return !Field->IsNull;
  }

  return B;
}

using TPeriod = PACKAGE TDiapazon< TDateTime >;
using TShortIntDiapazon = PACKAGE TDiapazon< short int >;
using TIntDiapazon = PACKAGE TDiapazon< int >;
using TLongLongIntDiapazon = PACKAGE TDiapazon< long long int >;
using TDoubleDiapazon = PACKAGE TDiapazon< double >;

extern PACKAGE int pow2(int p);

using TStringPair = PACKAGE std::pair<String, String>;
extern PACKAGE int __fastcall BoolToInt(bool Value);
extern PACKAGE void __fastcall SetColumnStory(TColumn *cl, const String &S,
    TCustomCombo *cc = NULL);
extern PACKAGE void __fastcall SetComboStory(const String &S,
    TCustomCombo *cc);
extern PACKAGE double __fastcall ConvertPrice(double Price, double FromCurs,
    double FromCoef, double ToCurs, double ToCoef);
extern PACKAGE void __fastcall FormListShow();
extern PACKAGE void __fastcall FormLocaleFormat( TCustomForm *fm );
extern PACKAGE void __fastcall DataModuleLocaleFormat( TDataModule *dm );
extern PACKAGE void __fastcall SyncLocaleFormat( /*double EnterpriseNo_*/ );
extern PACKAGE void __fastcall ClearScrollBox( TScrollBox *AScrollBox );
extern PACKAGE TCustomForm* __fastcall GetParentForm( TWinControl *Control );
extern PACKAGE void __fastcall SetNameToComponent( TComponent *AComponent, int &ANumber );
extern PACKAGE void __fastcall SetNameToComponent( TComponent *AComponent, TField *ASearchField, int &ANumber );

class PACKAGE TCursorMagic {
public:
  TCursor OldCursor;

  TCursorMagic(TCursor NewCursor_);
  ~TCursorMagic();
};

}

class PACKAGE TNNVTextStream : public TStream {
private:
  using inherited = TStream;
  TStream *fStream;
  bool fIsDeleteStream;

protected:
public:
  __fastcall TNNVTextStream(TStream *AStream);
  __fastcall ~TNNVTextStream();

  virtual int __fastcall Read( void *Buffer, int Count )
  {
    return Stream->Read( Buffer, Count );
  };

  virtual int __fastcall Write( const void *Buffer, int Count )
  {
    return Stream->Write( Buffer, Count );
  };

  virtual __int64 __fastcall Seek( const __int64 Offset, TSeekOrigin Origin )
  {
    return Stream->Seek( Offset, Origin );
  }; /* overload */

  inline bool __fastcall IsEof()
  {
    return ( Position == Size );
  };

  bool __fastcall ReadBool();

  inline void __fastcall WriteBool( bool Value )
  {
    Write( &Value, sizeof( Value ) );
  };
  char __fastcall ReadChar();

  inline void __fastcall WriteChar( char Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  unsigned char __fastcall ReadUnsignedChar();

  inline void __fastcall WriteUnsignedChar( unsigned char Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  int __fastcall ReadInt();

  inline void __fastcall WriteInt( int Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  short int __fastcall ReadShortInt();

  inline void __fastcall WriteShortInt( short int Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  unsigned short int __fastcall ReadUnsignedShortInt();

  inline void __fastcall WriteUnsignedShortInt( unsigned short int Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  std::size_t __fastcall ReadSizeType();

  inline void __fastcall WriteSizeType( std::size_t Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  NativeInt __fastcall ReadNativeInt();

  inline void __fastcall WriteNativeInt( NativeInt Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  unsigned int __fastcall ReadUnsignedInt();

  inline void __fastcall WriteUnsignedInt( unsigned int Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  TDateTime __fastcall ReadDateTime();

  inline void __fastcall WriteDateTime(TDateTime Value)
  {
    Write( &Value, sizeof( Value ) );
  };

  short int __fastcall ReadShort();

  inline void __fastcall WriteShort( short int Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  unsigned short int __fastcall ReadUnsignedShort();

  inline void __fastcall WriteUnsignedShort( unsigned short int Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  long int __fastcall ReadLongInt();

  inline void __fastcall WriteLongInt( long int Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  long long int __fastcall ReadLongLongInt();

  inline void __fastcall WriteLongLongInt( long long int Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  unsigned long int __fastcall ReadUnsignedLongInt();

  inline void __fastcall WriteLongInt( unsigned long int Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  unsigned long long int __fastcall ReadUnsignedLongLongInt();

  inline void __fastcall WriteLongLongInt( unsigned long long int Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  float __fastcall ReadFloat();

  inline void __fastcall WriteFloat( float Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  double __fastcall ReadDouble();

  inline void __fastcall WriteDouble( double Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  long double __fastcall ReadLongDouble();

  inline void __fastcall WriteLongDouble( long double Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  TColor __fastcall ReadColor();

  inline void __fastcall WriteColor( TColor Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  String __fastcall ReadString();
  void __fastcall WriteString( const String &Value );
  bool __fastcall ReadStringLine( String &S );
  AnsiString __fastcall ReadAnsiString();
  void __fastcall WriteAnsiString( const AnsiString &Value );
  void __fastcall ReadBinaryData( void *Buffer );
  inline void __fastcall WriteBinaryData( void *Buffer, int BufSize )
  {
    Write( &BufSize, sizeof( BufSize ) );
    Write( Buffer, BufSize );
  };
  void __fastcall ReadFiler( TNNVTextStream *filer );
  void __fastcall WriteFiler( TNNVTextStream *filer );
  void __fastcall ReadFont( TFont* AFont );
  void __fastcall WriteFont( TFont* AFont );
  TShortCut __fastcall ReadShortCut();

  inline void __fastcall WriteShortCut( TShortCut Value )
  {
    Write( &Value, sizeof( Value ) );
  };
  void __fastcall ResetVersion();
  // обработка разных типов полей для работы с базами данных
  Variant __fastcall ReadDoubleVariant();
  void __fastcall WriteDoubleVariant( const Variant &Value );
  Variant __fastcall ReadDateTimeVariant();
  void __fastcall WriteDateTimeVariant( const Variant &Value );
  Variant __fastcall ReadStringVariant();
  void __fastcall WriteStringVariant( const Variant &Value );
  NNV::TBoolExtended __fastcall ReadBoolExtended();
  inline void __fastcall WriteBoolExtended( NNV::TBoolExtended Value )
  {
    Write( &Value, sizeof( Value ) );
  };
  NNV::TPeriod __fastcall ReadPeriod();
  inline void __fastcall WritePeriod( NNV::TPeriod Value )
  {
    Write( &Value, sizeof( Value ) );
  };
  NNV::TShortIntDiapazon __fastcall ReadShortIntDiapazon();
  inline void __fastcall WriteShortIntDiapazon( NNV::TShortIntDiapazon Value )
  {
    Write( &Value, sizeof( Value ) );
  };
  NNV::TIntDiapazon __fastcall ReadIntDiapazon();
  inline void __fastcall WriteIntDiapazon( NNV::TIntDiapazon Value )
  {
    Write( &Value, sizeof( Value ) );
  };
  NNV::TLongLongIntDiapazon __fastcall ReadLongLongIntDiapazon();
  inline void __fastcall WriteLongLongIntDiapazon( NNV::TLongLongIntDiapazon Value )
  {
    Write( &Value, sizeof( Value ) );
  };
  NNV::TDoubleDiapazon __fastcall ReadDoubleDiapazon();
  inline void __fastcall WriteDoubleDiapazon( NNV::TDoubleDiapazon Value )
  {
    Write( &Value, sizeof( Value ) );
  };

  __property TStream* Stream = { read = fStream };
};

namespace NNV {

class TMapFiler : public std::map< String, TNNVTextStream* > {
private:
  using inherited = std::map< String, TNNVTextStream* >;
  TNNVTextStream* __fastcall GetFiler( const String &AKeyRegistry );
public:
  TMapFiler();
  ~TMapFiler();
  void __fastcall SaveToFiler( TNNVTextStream *Filer );
  void __fastcall LoadFromFiler( TNNVTextStream *Filer );
  __property TNNVTextStream* Filer[ const String &AKeyRegistry ] = { read = GetFiler };
};

}

#endif

