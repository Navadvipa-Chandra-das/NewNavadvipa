// ---------------------------------------------------------------------------
#include <fmx.h>
#pragma hdrstop

#include "FMX_NNSearchOption.h"

#pragma package(smart_init)

namespace NNF {

TSearchOptions::TSearchOptions()
{
}

TSearchOptions::TSearchOptions( bool aCaseSensitive
                              , bool aAnyEntry
                              , bool aNotThis
                              , bool aIsSoft
                              , bool aIsMistake
                              , bool aIsRegularExpression )
  : CaseSensitive( aCaseSensitive )
  , AnyEntry( aAnyEntry )
  , NotThis( aNotThis )
  , IsSoft( aIsSoft )
  , IsMistake( aIsMistake )
  , IsRegularExpression( aIsRegularExpression )
{
}

TSearchOptions::TSearchOptions( const TSearchOptions& a )
  : CaseSensitive( a.CaseSensitive )
  , AnyEntry( a.AnyEntry )
  , NotThis( a.NotThis )
  , IsSoft( a.IsSoft )
  , IsMistake( a.IsMistake )
  , IsRegularExpression( a.IsRegularExpression )
{
}

void __fastcall TSearchOptions::LoadFromFiler( TNNFTextStream *Filer )
{
  CaseSensitive       = Filer->ReadBool();
  AnyEntry            = Filer->ReadBool();
  NotThis             = Filer->ReadBool();
  IsSoft              = Filer->ReadBool();
  IsMistake           = Filer->ReadBool();
  IsRegularExpression = Filer->ReadBool();
}

void __fastcall TSearchOptions::SaveToFiler( TNNFTextStream *Filer )
{
  Filer->WriteBool( CaseSensitive );
  Filer->WriteBool( AnyEntry );
  Filer->WriteBool( NotThis );
  Filer->WriteBool( IsSoft );
  Filer->WriteBool( IsMistake );
  Filer->WriteBool( IsRegularExpression );
}

TSearchDlgOptions::TSearchDlgOptions()
  : Backward( false )
  , StartIsBegin( true )
  , IsAND( true )
  , IsFilter( true )
{
}

TSearchDlgOptions::TSearchDlgOptions( const TSearchOptions &aSearchOptions
                                    , bool aBackward
                                    , bool aStartIsBegin
                                    , bool aIsAND
                                    , bool aIsFilter )
  : SearchOptions( aSearchOptions )
  , Backward( aBackward )
  , StartIsBegin( aStartIsBegin )
  , IsAND( aIsAND )
  , IsFilter( aIsFilter )
{
}

void __fastcall TSearchDlgOptions::LoadFromFiler( TNNFTextStream *Filer )
{
  SearchOptions.LoadFromFiler( Filer );
  Backward     = Filer->ReadBool();
  StartIsBegin = Filer->ReadBool();
  IsAND        = Filer->ReadBool();
  IsFilter     = Filer->ReadBool();
}

void __fastcall TSearchDlgOptions::SaveToFiler( TNNFTextStream *Filer )
{
  SearchOptions.SaveToFiler( Filer );
  Filer->WriteBool( Backward );
  Filer->WriteBool( StartIsBegin );
  Filer->WriteBool( IsAND );
  Filer->WriteBool( IsFilter );
}

TSearchValue::TSearchValue()
{
}

TSearchValue::TSearchValue( const TSearchValue &ASearchValue )
  : FStringValue(         ASearchValue.StringValue         )
  , FStringHistory(       ASearchValue.StringHistory       )
  , FRegEx(               ASearchValue.RegEx               )
  , FBool(                ASearchValue.Bool                )
  , FPeriod(              ASearchValue.Period              )
  , FShortIntDiapazon(    ASearchValue.ShortIntDiapazon    )
  , FIntDiapazon(         ASearchValue.IntDiapazon         )
  , FLongLongIntDiapazon( ASearchValue.LongLongIntDiapazon )
  , FDoubleDiapazon(      ASearchValue.DoubleDiapazon      )
{
}

TSearchValue::~TSearchValue()
{
  if ( RegEx ) {
    delete RegEx;
    RegEx = nullptr;
  }
}

void __fastcall TSearchValue::LoadFromFiler( TNNFTextStream *Filer )
{
  StringValue         = Filer->ReadString();
  StringHistory       = Filer->ReadString();
  Bool                = Filer->ReadBoolExtended();
  Period              = Filer->ReadPeriod();
  ShortIntDiapazon    = Filer->ReadShortIntDiapazon();
  IntDiapazon         = Filer->ReadIntDiapazon();
  LongLongIntDiapazon = Filer->ReadLongLongIntDiapazon();
  DoubleDiapazon      = Filer->ReadDoubleDiapazon();
}

void __fastcall TSearchValue::SaveToFiler( TNNFTextStream *Filer )
{
  Filer->WriteString(              StringValue );
  Filer->WriteString(              StringHistory );
  Filer->WriteBoolExtended(        Bool );
  Filer->WritePeriod(              Period );
  Filer->WriteShortIntDiapazon(    ShortIntDiapazon );
  Filer->WriteIntDiapazon(         IntDiapazon );
  Filer->WriteLongLongIntDiapazon( LongLongIntDiapazon );
  Filer->WriteDoubleDiapazon(      DoubleDiapazon );
}

TSearchBox::TSearchBox()
{
}

TSearchBox::TSearchBox( const TSearchBox &ASearchBox )
  : FField( ASearchBox.Field )
  , FFieldName( ASearchBox.FieldName )
  , FDataType( ASearchBox.DataType )
  , FSearchValue( ASearchBox.SearchValue )
  , FNeedSet( ASearchBox.NeedSet )
{
}

TSearchBox::TSearchBox( TField *AField )
  : FField( AField )
{
  assert( AField != nullptr );
  FieldName = AField->FieldName;
  DataType  = AField->DataType;
}

void __fastcall TSearchBox::LoadFromFiler( TNNFTextStream *Filer )
{
  NeedSet   = Filer->ReadBool();
  FieldName = Filer->ReadString();
  DataType  = (TFieldType)Filer->ReadUnsignedChar();
  SearchValue.LoadFromFiler( Filer );
}

void __fastcall TSearchBox::SaveToFiler( TNNFTextStream *Filer )
{
  Filer->WriteBool( NeedSet );
  Filer->WriteString( FieldName );
  Filer->WriteUnsignedChar( DataType );
  SearchValue.SaveToFiler( Filer );
}

TMapSearch::TMapSearch()
  : inherited()
{
}

TMapSearch::~TMapSearch()
{
}

TMapSearch::TMapSearch( const TSearchDlgOptions &ASearchDlgOptions )
  : inherited()
  , FSearchDlgOptions( ASearchDlgOptions )
{
}

void __fastcall TMapSearch::LoadFromFiler( TNNFTextStream *Filer )
{
  TSearchBox SB;
  SearchDlgOptions.LoadFromFiler( Filer );
  std::size_t L = Filer->ReadSizeType();
  for ( std::size_t i = 0; i < L; ++i )
  {
    SB.LoadFromFiler( Filer );
    push_back( SB );
  }
}

void __fastcall TMapSearch::SaveToFiler( TNNFTextStream *Filer )
{
  SearchDlgOptions.SaveToFiler( Filer );
  std::size_t L = size();
  Filer->WriteSizeType( L );
  for ( std::size_t i = 0; i < L; ++i )
  {
    (*this)[ i ].SaveToFiler( Filer );
  }
}

TMapSearch::iterator __fastcall TMapSearch::Find( TField *AField )
{
  iterator R = end();
  for( iterator i = begin(); i != end(); ++i ) {
    if ( ( *i ).Field == AField ) {
      R = i;
      break;
    }
  }
  return R;
}

TMapSearch::iterator __fastcall TMapSearch::FindLike( TField *AField )
{
  iterator R = end();
  for( iterator i = begin(); i != end(); ++i ) {
    if ( ( *i ).FieldName == AField->FieldName && ( *i ).DataType == AField->DataType ) {
      R = i;
      break;
    }
  }
  return R;
}

TMapSearch::iterator __fastcall TMapSearch::Add( TField *AField )
{
  iterator R = end();
  bool B = false;
  for( iterator i = begin(); i != end(); ++i ) {
    if ( ( *i ).Field == AField ) {
      R = i;
      B = true;
      break;
    }
  }
  if ( !B ) {
    TSearchBox SB( AField );
    push_back( SB );
    R = end();
    --R;
  }
  return R;
}

void __fastcall TMapSearch::AddVectorSearch( iterator AIterator, bool ANeedSet )
{
  TVectorSearch::iterator R = std::find( VectorSearch.begin(), VectorSearch.end(), AIterator );
  if ( R == VectorSearch.end() ) {
    if ( ANeedSet )
      VectorSearch.push_back( AIterator );
  } else {
    if ( !ANeedSet )
      VectorSearch.erase( R );
  }
}

}

