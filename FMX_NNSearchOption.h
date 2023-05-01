// ---------------------------------------------------------------------------

#ifndef FMX_NNSearchOptionH
#define FMX_NNSearchOptionH

#include "FMX_NNCommon.h"
#include <Data.DB.hpp>
#include <System.RegularExpressions.hpp>
#include <vector>
#include "FMX_NNCommon.h"

namespace NNF {

class PACKAGE TSearchOptions {
public:
  TSearchOptions();
  TSearchOptions( bool aCaseSensitive
                , bool aAnyEntry
                , bool aNotThis
                , bool aIsSoft
                , bool aIsMistake
                , bool aIsRegularExpression );
  TSearchOptions(const TSearchOptions& a);

  bool CaseSensitive       = false;
  bool AnyEntry            = true;
  bool NotThis             = false;
  bool IsSoft              = false;
  bool IsMistake           = false;
  bool IsRegularExpression = false;

  void __fastcall LoadFromFiler( TNNFTextStream *Filer );
  void __fastcall SaveToFiler( TNNFTextStream *Filer );
};

class PACKAGE TSearchDlgOptions {
public:
  TSearchOptions SearchOptions;
  bool Backward;
  bool StartIsBegin;
  bool IsAND;
  bool IsFilter;

  TSearchDlgOptions();
  TSearchDlgOptions( const TSearchOptions &aSearchOptions
                   , bool aBackward
                   , bool aStartIsBegin
                   , bool aIsAND
                   , bool aIsFilter );
  void __fastcall LoadFromFiler( TNNFTextStream *Filer );
  void __fastcall SaveToFiler( TNNFTextStream *Filer );
};

class PACKAGE TSearchValue {
private:
  String FStringValue;
  TRegEx *FRegEx = nullptr;
  String FStringHistory;
  TBoolExtended FBool;
  TPeriod FPeriod;
  TShortIntDiapazon FShortIntDiapazon;
  TIntDiapazon FIntDiapazon;
  TLongLongIntDiapazon FLongLongIntDiapazon;
  TDoubleDiapazon FDoubleDiapazon;
public:
  TSearchValue();
  TSearchValue( const TSearchValue &ASearch );
  ~TSearchValue();
  void __fastcall LoadFromFiler( TNNFTextStream *Filer );
  void __fastcall SaveToFiler( TNNFTextStream *Filer );
  __property String StringValue = { read = FStringValue, write = FStringValue };
  __property TRegEx *RegEx = { read = FRegEx, write = FRegEx };
  __property String StringHistory = { read = FStringHistory , write = FStringHistory };
  __property TBoolExtended Bool = { read = FBool, write = FBool };
  __property TPeriod Period = { read = FPeriod, write = FPeriod };
  __property TShortIntDiapazon ShortIntDiapazon = { read = FShortIntDiapazon, write = FShortIntDiapazon };
  __property TIntDiapazon IntDiapazon = { read = FIntDiapazon, write = FIntDiapazon };
  __property TLongLongIntDiapazon LongLongIntDiapazon = { read = FLongLongIntDiapazon, write = FLongLongIntDiapazon };
  __property TDoubleDiapazon DoubleDiapazon = { read = FDoubleDiapazon, write = FDoubleDiapazon };
};

class PACKAGE TSearchBox {
private:
  TField *FField = nullptr;
  String FFieldName;
  TFieldType FDataType;
  TSearchValue FSearchValue;
  bool FNeedSet = false;
public:
  TSearchBox();
  TSearchBox( const TSearchBox &ASearchBox );
  TSearchBox( TField *AField );
  void __fastcall LoadFromFiler( TNNFTextStream *Filer );
  void __fastcall SaveToFiler( TNNFTextStream *Filer );
  __property TField *Field = { read = FField, write = FField };
  __property String FieldName = { read = FFieldName, write = FFieldName };
  __property TFieldType DataType = { read = FDataType, write = FDataType };
  __property TSearchValue SearchValue = { read = FSearchValue, write = FSearchValue };
  __property bool NeedSet = { read = FNeedSet, write = FNeedSet };
};

class PACKAGE TMapSearch : public std::vector< TSearchBox > {
public:
  using inherited = std::vector< TSearchBox >;
  using TVectorSearch = std::vector< iterator >;

private:
  TSearchDlgOptions FSearchDlgOptions;
  TVectorSearch FVectorSearch;

public:
  TMapSearch();
  ~TMapSearch();
  TMapSearch( const TSearchDlgOptions &ASearchDlgOptions );
  void __fastcall LoadFromFiler( TNNFTextStream *Filer );
  void __fastcall SaveToFiler( TNNFTextStream *Filer );
  iterator __fastcall Find( TField *AField );
  iterator __fastcall FindLike( TField *AField );
  iterator __fastcall Add( TField *AField );
  void __fastcall AddVectorSearch( iterator AIterator, bool ANeedSet );
  __property TSearchDlgOptions SearchDlgOptions = { read = FSearchDlgOptions, write = FSearchDlgOptions };
  __property TVectorSearch VectorSearch = { read = FVectorSearch };
};

}

#endif

