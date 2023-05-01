// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <fmx.h>
#pragma hdrstop
#include "FMX_NNDBMiracle.h"
#include "FMX_NNStrUtil.h"
#include <FMX.DialogService.hpp>
//#include "FMX_NNFmSearch.h"
//#include "FMX_NNFrDiapazon.h"
//#include "FMX_NNFrDoubleDiapazon.h"
//#include "FMX_NNFrIntDiapazon.h"
//#include "FMX_NNFrLongLongIntDiapazon.h"
//#include "FMX_NNFrPeriod.h"
//#include "FMX_NNFrShortIntDiapazon.h"
#include <memory>
#include <algorithm>
//#include "FMX_NNFmStoryData.h"
//#include "FMX_NNFmRowInspector.h"
#include "FMX_NNFormAdmin.h"
//#include "FMX_NNDBComboBoxDateTime.h"
#include "FMX_NNCommon.h"

#if (!__ANDROID__)
#pragma resource "*.res"
#endif

#pragma package(smart_init)

namespace NNF {

const int tvID       = 0;
const int tvParentID = 1;
const int tvText     = 2;
const int tvActual   = 3;

const short InsertIsConfirm = 0;
const short InsertIsChild   = 1;
const short InsertIsNoChild = 2;
const short InsertIsCancel  = 3;

const long long int EmptyPK = 0;

const int SD_LEFTPOS = 4;
const int SD_SCROLLBAR_WIDTH = 20;
const int SD_LABEL_WIDTH = 200;
const int CW_LIMIT_HISTORY = 30;

TDSetBookmark::TDSetBookmark()
  : DataSet( nullptr )
{
}

TDSetBookmark::~TDSetBookmark()
{
}

TDSetBookmark::TDSetBookmark( const TDSetBookmark& a )
{
  DataSet = a.DataSet;
  UKey = a.UKey;
}

TDSetBookmark::TDSetBookmark(TNNFQuery *aDataSet) : DataSet(aDataSet)
{
  if ( DataSet )
    DataSet->GetUKey( UKey );
}

TDSetBookmark& TDSetBookmark:: operator = ( const TDSetBookmark & a )
{
  DataSet = a.DataSet;
  UKey = a.UKey;
  return *this;
}

void __fastcall TDSetBookmark::Execute()
{
  if ( DataSet )
    DataSet->GotoUKey( UKey );
}

TMapQuery::TMapQuery()
  : inherited()
{
}

TMapQuery::TMapQuery( TComponent *AOwner )
  : inherited()
{
  TNNFQuery *qu;
  int L = AOwner->ComponentCount;
  for ( int I = 0; I < L; ++I ) {
    qu = dynamic_cast< TNNFQuery* >( AOwner->Components[ I ] );
    if ( qu && qu->NeedSave )
      operator[]( qu->Name ) = qu;
  }
}

void __fastcall TMapQuery::PrepareStandartMacros()
{
  for ( iterator I = begin(); I != end(); ++I )
    (*I).second->PrepareStandartMacros();
}


TMapQuery::~TMapQuery()
{
}

void __fastcall TMapQuery::SaveToFiler( TNNFTextStream *Filer )
{
  for ( iterator I = begin(); I != end(); ++I )
    (*I).second->SaveToFiler( Filer );
}

void __fastcall TMapQuery::LoadFromFiler( TNNFTextStream *Filer )
{
  for ( iterator I = begin(); I != end(); ++I )
    (*I).second->LoadFromFiler( Filer );
}

TBufferIntBox::TBufferIntBox()
{
}

TBufferIntBox::~TBufferIntBox()
{
}

}

// ------------------------------------------------------
namespace NNF {
  const bool NoLockRecord = false;
  const bool LockRecord = true;
}

// ---------------------------------------------------------------------------
__fastcall TNNFQuery::TNNFQuery( TComponent* Owner )
  : inherited( Owner )
, FFilterMap( this )
{
  CachedUpdates  = false;
  Active         = false;
  FilteredEnable = true;
}

__fastcall TNNFQuery::~TNNFQuery()
{
}

void __fastcall TNNFQuery::PrepareStandartMacros()
{
  TFDMacro *M = FindMacro( NNFConst::PRABHUPADA_SCHEMA );

  if ( M ) {
    if ( Connection )
      M->AsRaw = Connection->Params->Values[ "PrabhupadaSchema" ];
    else
      M->AsRaw = NNFConst::PrabhupadaSchemaDefault;

  }
}

void __fastcall TNNFQuery::DoSetVariableRecord()
{
  if ( FOnSetVariableRecord )
    FOnSetVariableRecord( this );
}

void __fastcall TNNFQuery::CWDeleteVariable( const String &VariableName ) {
  TFDParam *p = FindParam( VariableName );
  if ( p )
    Params->Delete( ( *p ).Index );
}

bool __fastcall TNNFQuery::CWSetVariable( const String &VariableName,
    const Variant &Value ) {
  TFDParam *p = FindParam( VariableName );
  bool B = p != nullptr;
  if ( B )
    p->Value = Value;
  return B;
}

TField* __fastcall TNNFQuery::CWFindField( const String &AFieldName, TADTField *AF )
{
  TField *F;
  TADTField *AAF;
  int I, FC;

  if ( AF ) {
    FC = AF->FieldCount;
    for ( I = 0; I < FC; ++I ) {
      F = AF->Fields->Fields[ I ];
      AAF = dynamic_cast< TADTField* >( F );
      if ( AAF ) {
        F = CWFindField( AFieldName, AAF );
        if ( F )
          return F;
      } else if ( F->FieldName == AFieldName )
        return F;
    }
  } else {
    for ( I = 0; I < FieldCount; ++I ) {
      F = Fields->Fields[ I ];
      AAF = dynamic_cast< TADTField* >( F );
      if ( AAF ) {
        F = CWFindField( AFieldName, AAF );
        if ( F )
          return F;
      } else if ( F->FieldName == AFieldName )
        return F;
    }
  }

  return F;
}

void __fastcall TNNFQuery::SaveToFiler( TNNFTextStream *Filer )
{
  Filer->WriteString( FieldSearchName );
  Filer->WriteBool( CachedUpdates );
  MapSearch.SaveToFiler( Filer );
}

void __fastcall TNNFQuery::LoadFromFiler( TNNFTextStream *Filer )
{
  FieldSearchName = Filer->ReadString();
  CachedUpdates = Filer->ReadBool();
  MapSearch.LoadFromFiler( Filer );
}

void __fastcall TNNFQuery::Post() {
  if ( MasterSource ) {
    if ( MasterSource->DataSet ) {
      TNNFQuery *mds = dynamic_cast < TNNFQuery* > ( MasterSource->DataSet );
      if ( mds ) {
        mds->CWCheckBrowseMode();
        if ( mds->CachedUpdates && !CachedUpdates )
          mds->CWApplyUpdates();
      }
    }
  }
  inherited::Post();
}

void __fastcall TNNFQuery::GetUKey( Variant &V, const String &UniqueFields_ ) {
  if ( UniqueFields_.IsEmpty() )
    V = Fields->Fields[ 0 ]->Value;
  else if ( UniqueFields_.Pos( ";" ) == 0 )
    V = FieldByName( UniqueFields_ )->Value;
  else {
    String S;
    char D = ';';
    int N = 1, L = NNF::CharCount( UniqueFields_, ';' ), Bounds[ 2 ];
    Bounds[ 0 ] = 0;
    Bounds[ 1 ] = L;
    V = VarArrayCreate( Bounds, 1, varVariant );
    for ( int i = 0; i <= L; ++i ) {
      S = NNF::GetToken( UniqueFields_, N, D );
      V.PutElement( FieldByName( S )->Value, i );
    }
  }
}

bool __fastcall TNNFQuery::GotoUKey( const Variant &V,
    const String &UniqueFields_ ) {
  if ( Bof && Eof )
    return false;
  if ( UniqueFields_.IsEmpty() )
    return Locate( Fields->Fields[ 0 ]->FieldName, V, TLocateOptions() );
  else
    return Locate( UniqueFields_, V, TLocateOptions() );
}

bool __fastcall TNNFQuery::GotoUKey( const Variant &V ) {
  return GotoUKey( V, CWUniqueFields );
}

void __fastcall TNNFQuery::GetUKey( Variant &V ) {
  GetUKey( V, CWUniqueFields );
}

void __fastcall TNNFQuery::SaveUKey() {
  GetUKey( fUKey );
}

bool __fastcall TNNFQuery::GotoUKey() {
  return GotoUKey( fUKey );
}

void __fastcall TNNFQuery::CWRefresh() {
  if ( !Active )
    return;
  DisableControls();
  try {
    SaveUKey();
    SaveDlg();
    Refresh();

    GotoUKey();
  }
  __finally {
    EnableControls();
  }
}

void __fastcall TNNFQuery::CWRefreshWithoutTree()
{
//  AdminsSet->Enable = false;
//  try {
    CWRefresh();
//  }
//  __finally {
//    AdminsSet->Enable = true;
//  }
}

void __fastcall TNNFQuery::CWRefreshRecord() {
  if ( !Active )
    return;
  SaveDlg();
  RefreshRecord();
}

void _fastcall TNNFQuery::DoBeforeClose() {
  inherited::DoBeforeClose();
  SaveDlg();
}

void __fastcall TNNFQuery::SetFilteredEnable( bool Value )
{
  if ( FFilteredEnable != Value ) {
    FFilteredEnable = Value;
    if ( !FilteredEnable )
      MapSearch.SearchDlgOptions.IsFilter = false;
  }
}

void __fastcall TNNFQuery::SaveDlg()
{
  if ( CachedUpdates ) {
    CheckBrowseMode();
    if ( UpdatesPending ) {
      String S = NNFConst::ToKeepChanges + ( Note.IsEmpty() ? Name : Note );
      TDialogService::MessageDialog( S
                                   , TMsgDlgType::mtConfirmation
                                   , mbOKCancel, TMsgDlgBtn::mbOK
                                   , 0
                                   , SaveCachedUpdates );
    }
  }
}

void __fastcall TNNFQuery::SaveCachedUpdates( TObject* Sender, const TModalResult AResult )
{
  if ( AResult == mrOk ) {
    ApplyUpdates();
    CommitUpdates();
  } else {
    CancelUpdates();
  }
}

//void __fastcall TNNFQuery::SetOrderByColumn( TColumn *Value )
//{
//  if ( FOrderByColumn != Value ) {
//    FOrderByColumn = Value;
//
//    if ( OrderByColumn ) {
//      TNNFGridColumn *C = dynamic_cast< TNNFGridColumn* >( OrderByColumn );
//      bool B = false;
//      TFDMacro *M;
//      M = FindMacro( NNFConst::ORDER_BY );
//
//      if ( M ) {
//        bool SA = Active;
//        SaveUKey();
//        Active = false;
//        M->Value = C->OrderBy.IsEmpty() ? OrderByDefault : C->OrderBy;
//        Active = SA;
//        GotoUKey();
//      }
//    }
//  }
//}

void __fastcall TNNFQuery::ClearAll()
{
  Active = false;
  Params->Clear();
  SQL->Clear();
  AutoCalcFields = true;
  CachedUpdates = false;
  DetailFields = "";
  FieldSearchName = "";
  FilteredEnable = true;
  MasterSource = nullptr;
  MasterFields = "";
  Tag = 0;
  AfterCancel = nullptr;
  AfterClose = nullptr;
  AfterDelete = nullptr;
  AfterEdit = nullptr;
  AfterInsert = nullptr;
  AfterOpen = nullptr;
  AfterPost = nullptr;
  AfterScroll = nullptr;
  BeforeCancel = nullptr;
  BeforeClose = nullptr;
  BeforeDelete = nullptr;
  BeforeEdit = nullptr;
  BeforeInsert = nullptr;
  BeforeOpen = nullptr;
  BeforePost = nullptr;
  BeforeScroll = nullptr;
  OnDeleteError = nullptr;
  OnEditError = nullptr;
  if ( !FetchOptions->Unidirectional )
    OnFilterRecord = nullptr;
  OnNewRecord = nullptr;
  OnPostError = nullptr;
  for ( int i = FieldCount - 1; i >= 0; i-- )
    delete Fields->Fields[ i ];
}

void __fastcall TNNFQuery::CWApplyUpdates() {
  CWCheckBrowseMode();
  TNNFQuery *od = dynamic_cast < TNNFQuery* > ( MasterSource );
  if ( od )
    od->CWApplyUpdates();
  if ( CachedUpdates ) {
    DisableControls();
    try {
      ApplyUpdates();
      CommitUpdates();
      if ( Connection )
        Connection->Commit();
    }
    __finally {
      EnableControls();
    }
  }
}

bool __fastcall TNNFQuery::CheckFields(TVectorOfField &VField ) {
  bool result = true;
  TVectorOfField::iterator i;
  Variant VQ, VF;
  int T;
  for ( i = VField.begin(); i != VField.end(); ++i ) {
    T = ( *i ).first->DataType;
    if ( T == ftBlob )
      continue;
    VF = ( *i ).first->OldValue;
    VQ = ( *i ).second.Field->Value;
    if ( VF.IsNull() ) {
      if ( !VQ.IsNull() ) {
        result = false;
        break;
      }
    }
    else {
      if ( VQ.IsNull() ) {
        result = false;
        break;
      }
      else if ( VQ != VF ) {
        result = false;
        break;
      }
    }
  }
  if ( !result )
    NNFConst::FieldUserChange = ( *i ).first->DisplayLabel;
  return result;
}

bool __fastcall TNNFQuery::CheckFieldsModify( TSetOfField &VField ) {
  bool B = false;
  int T;
  for ( TSetOfField::iterator i = VField.begin(); i != VField.end(); ++i ) {
    T = ( *i )->DataType;
    if ( T == ftBlob ) {
      if ( ( ( TBlobField* )( *i ) )->Modified ) {
        B = true;
        break;
      }
    }
    else {
      if ( ( *i )->Value != ( *i )->OldValue ) {
        B = true;
        break;
      }
    }
  }
  return B;
}

void __fastcall TNNFQuery::SetNewRecord( TVectorOfField &VField ) {
  int T;
  for ( TVectorOfField::iterator i = VField.begin(); i != VField.end(); ++i )
  {
    T = ( *i ).first->DataType;
    if ( ( *i ).second.Field->IsNull )
      ( *i ).first->Clear();
    else if ( T == ftBlob )
      ( ( TBlobField* )( *i ).first )->Assign
          ( ( ( TBlobField* )( *i ).second.Field ) );
    else
      ( *i ).first->Value = ( *i ).second.Field->Value;
  }
}

long long int __fastcall TNNFQuery::GetNewID( String SQ, TNNFQuery *Query )
{
  long long int result;
  // Query->ClearAll();
  Query->SQL->Text = "select " + SQ + ".nextval res from dual";
  Query->Execute();
  result = Query->Fields->Fields[ 0 ]->AsLargeInt;
  Query->Close();
  return result;
}

void __fastcall TNNFQuery::CWCheckEditMode()
{
  if ( !IsEditModes() )
    Edit();
}

void __fastcall TNNFQuery::CWCheckBrowseMode()
{
  if ( IsEditModes() )
    Post();
}

// ---------------------------------------------------
TNNFFilter::TNNFFilter()
{
}

TNNFFilter::~TNNFFilter()
{
  if ( FRegEx ) {
    delete FRegEx;
    FRegEx = nullptr;
  }
}

TNNFFilter::TNNFFilter( bool aEnable
                      , TField *aField
                      , const String &S
                      , const NNF::TSearchOptions &aSearchOptions )
  : FEnable( aEnable )
  , FFieldFilter( aField )
  , FStrFilter( S )
  , FSearchOptions( aSearchOptions )
{
  TRegExOptions RO;
  RO = RO << roMultiLine;
  if ( !SearchOptions.CaseSensitive )
    RO = RO << roIgnoreCase;
  if ( SearchOptions.IsRegularExpression )
    FRegEx = new TRegEx( S, RO );
}

TNNFFilter::TNNFFilter( const TFilterRecordEvent &aEvent
                      , bool aEnable )
  : FEventFilter( aEvent )
  , FEnable( aEnable )
{
}

TNNFFilter& TNNFFilter:: operator = ( const TNNFFilter & a )
{
  FFieldFilter   = a.FFieldFilter;
  FStrFilter     = a.FStrFilter;
  FRegEx         = a.FRegEx;
  FEnable        = a.FEnable;
  FSearchOptions = a.FSearchOptions;
  FEventFilter   = a.FEventFilter;

  return *this;
}

TNNFFilter& TNNFFilter:: operator = ( TNNFFilter && a )
{
  FFieldFilter   = a.FFieldFilter;
  FStrFilter     = a.FStrFilter;
  FRegEx         = a.FRegEx;
  FEnable        = a.FEnable;
  FSearchOptions = a.FSearchOptions;
  FEventFilter   = a.FEventFilter;

  a.FRegEx       = nullptr;
  a.FEventFilter = nullptr;
  a.FFieldFilter = nullptr;

  return *this;
}

void __fastcall TNNFFilter::FilterEvent( TDataSet *DataSet, bool &Accept )
{
  if ( EventFilter )
     EventFilter( DataSet, Accept );
}

TNNFFilterMap::TNNFFilterMap( TNNFQuery *DSet )
  : DataSet( DSet )
{
  if ( !DataSet->ComponentState.Contains( csDesigning ) )
    DataSet->OnFilterRecord = FilterEvent;
}

void __fastcall TNNFFilterMap::FilterEvent( TDataSet *DataSet, bool &Accept ) {
  int N = this->size();
  for ( iterator i = this->begin(); i != this->end(); ++i ) {
    if ( ( *i ).second.Enable ) {
      ( *i ).second.FilterEvent( DataSet, Accept );
      if ( !Accept )
        break;
    }
  }
}

void __fastcall TNNFFilterMap::RefreshFilter()
{
  if ( !DataSet )
    return;
  bool B = false;

  for ( iterator i = begin(); i != end(); ++i )
    if ( ( *i ).second.Enable ) {
      B = true;
      break;
    }
  DataSet->DisableControls();
  try {
    if ( B ) {
      if ( DataSet->Filtered )
        DataSet->Filtered = false;
      DataSet->Filtered = true;
    }
    else
      DataSet->Filtered = false;
  } __finally {
    DataSet->EnableControls();
  }
}

void __fastcall TNNFFilterMap::EraseFilterSearch()
{
  bool B = false;

  for ( iterator i = begin(); i != end(); ) {
    if ( (*i).first == NNFConst::DBSearchDialogFilterKey ) {
      i = erase( i );
      B = true;
      break;
    }
    ++i;
  }

  if ( B )
    RefreshFilter();
}

bool __fastcall TNNFFilterMap::IsFilterSearchPresent()
{
  return find( NNFConst::DBSearchDialogFilterKey ) != end();
}

void __fastcall TNNFQuery::CWOpen()
{
  ++FOpenCounter;
  Open();
}

void __fastcall TNNFQuery::CWOpenIf( bool Condition )
{
  ++FOpenCounter;
  if ( Condition )
    Open();
}

void __fastcall TNNFQuery::CWOpenIfClose()
{
  if ( !Active )
    CWOpen();
}

void __fastcall TNNFQuery::CWClose()
{
  if ( --FOpenCounter <= 0 )
    Close();
}

void __fastcall TNNFQuery::CWCloseAlways()
{
  FOpenCounter = 0;
  Close();
}

bool __fastcall TNNFQuery::IsEditModes()
{
  return State == dsEdit || State == dsInsert || State == dsSetKey;
}

bool __fastcall TNNFQuery::CWLocate( const String KeyFields
                                   , const System::Variant &KeyValues )
{
  return Locate( KeyFields, KeyValues, TLocateOptions() );
};

void __fastcall TNNFQuery::CWReopen()
{
  DisableControls();
  try {
    Close();
    Open();
  } __finally {
    EnableControls();
  }
}

void __fastcall TNNFQuery::CWActiveReopen()
{
  if ( Active ) {
    DisableControls();
    try {
      Close();
      Open();
    } __finally {
      EnableControls();
    }
  }
}

void __fastcall TNNFQuery::CWReconnectReopen(bool NeedClose_ )
{
  if ( Active && !NeedClose_ )
    return;

  if ( OpenCounter > 0 ) {
    DisableControls();
    try {
      if ( NeedClose_ )
        Close();
      Open();
    } __finally {
      EnableControls();
    }
  } else
    Close();
}

void __fastcall TNNFQuery::Loaded()
{
  inherited::Loaded();
  TFDMacro *M = FindMacro( NNFConst::ORDER_BY );
  if ( M )
    M->Value = OrderByDefault;
}

void __fastcall TNNFQuery::DoBeforeDelete()
{
  inherited::DoBeforeDelete();
  FDeleteNodePK = Fields->Fields[ NNF::tvID ]->AsLargeInt;
}

void __fastcall TNNFQuery::DoAfterDelete()
{
  inherited::DoAfterDelete();
}

void __fastcall TNNFQuery::DoAfterOpen()
{
  inherited::DoAfterOpen();
}

void __fastcall TNNFQuery::DeclareAndSetParam( const String &AParam, Variant Value )
{
  TFDParam *P = ParamByName( AParam );
  P->Value = Value;
}

void __fastcall TNNFQuery::SetName( const TComponentName Value )
{
  inherited::SetName( Value );
  FPasteProcedure = DefaultPasteProcedure();
  FMergeProcedure = DefaultMergeProcedure();
}

String __fastcall TNNFQuery::DefaultPasteProcedure()
{
  String R( L"\"Paste" );
  R += Name.SubString( 3, Name.Length() - 2 );
  R += L"\"";
  return R;
}

bool __fastcall TNNFQuery::StoredPasteProcedure()
{
  return FPasteProcedure != DefaultPasteProcedure();
}

String __fastcall TNNFQuery::DefaultMergeProcedure()
{
  String R( L"\"Merge" );
  R += Name.SubString( 3, Name.Length() - 2 );
  R += L"\"";
  return R;
}

bool __fastcall TNNFQuery::StoredMergeProcedure()
{
  return FMergeProcedure != DefaultMergeProcedure();
}

TField* __fastcall TNNFQuery::GetFieldSearch()
{
  return FieldSearchName.IsEmpty() ? nullptr : CWFindField( FieldSearchName );
}

void __fastcall TNNFQuery::DBPaste( NNF::TBufferIntBox &ABufferIntBox, TNNFQuery *QU, TField *F )
{
  if ( ABufferIntBox.Label != this )
    return;

  QU->ClearAll();
  QU->SQL->Text = L"call " + PasteProcedure + "( :ANewID, :AVectorID, :IsCut );";

  QU->DeclareAndSetParam( "ANewID", F->AsLargeInt );
  QU->DeclareAndSetParam( "IsCut", ABufferIntBox.IsCut );

  TFDParam *P = QU->ParamByName( "AVectorID" );

  int L = ABufferIntBox.VectorID.size();

  // К большому сожалению передача параметров-массивов в хранимую процедуру PostgreSQL не работает! Надеемся, что Эмбаркадеро это скоро исправит!
  for ( int I = 0; I != L; ++I ) {
    //P->AsLargeInts[ I ] = BufferIntBox.VectorID[ I ];
    P->AsLargeInt = ABufferIntBox.VectorID[ I ];
    QU->ExecSQL();
  }

  CWRefresh();
}

void __fastcall TNNFQuery::DBMerge( NNF::TBufferIntBox &ABufferIntBox, TNNFQuery *QU, TField *F )
{
  if ( ABufferIntBox.Label != this )
    return;

  QU->ClearAll();
  QU->SQL->Text = L"call " + MergeProcedure + "( :ANewID, :AVectorID );";

  QU->DeclareAndSetParam( "ANewID", F->AsLargeInt );

  TFDParam *P = QU->ParamByName( "AVectorID" );

  int L = ABufferIntBox.VectorID.size();

  // К большому сожалению передача параметров-массивов в хранимую процедуру PostgreSQL не работает! Надеемся, что Эмбаркадеро это скоро исправит!
  for ( int I = 0; I != L; ++I ) {
    //P->AsLargeInts[ I ] = BufferIntBox.VectorID[ I ];
    P->AsLargeInt = ABufferIntBox.VectorID[ I ];
    QU->ExecSQL();
  }

  CWRefresh();
}

TNNFNodeParams::TNNFNodeParams()
  : ImageIndex( -1 )
  , SelectedIndex( -1 )
{
}

void __fastcall TNNFNodeParams::Clear()
{
  Text = "";
  ImageIndex = -1;
  SelectedIndex = -1;
}

TNNFFieldUpdate::TNNFFieldUpdate()
  : Obligatory( false )
  , Field( nullptr )
{
}

TNNFFieldUpdate::TNNFFieldUpdate( TField *aField )
  : Obligatory( false )
  , Field( aField )
{
}

TNNFFieldUpdate::TNNFFieldUpdate( bool aObligatory
                                , TField *aField )
  : Obligatory( aObligatory )
  , Field( aField )
{
}

namespace NNF {

TStoryInfo::TStoryInfo()
  : Value()
{
}

TStoryInfo::TStoryInfo( const Variant &aValue )
  : Value( aValue )
{
}

}

TNNFConfig::TNNFConfig( TComponent* Owner )
  : inherited( Owner )
  , fVersion( char() )
  , fTableUserReg( NNFConst::TableUserReg )
  , fFieldUserRegKey( NNFConst::FieldUserRegKey )
  , fFieldUserData( NNFConst::FieldUserData )
{
}

bool __fastcall TNNFConfig::StoredTableUserReg()
{
  return fTableUserReg != NNFConst::TableUserReg;
}

bool __fastcall TNNFConfig::StoredFieldUserRegKey()
{
  return fFieldUserRegKey != NNFConst::FieldUserRegKey;
}

bool __fastcall TNNFConfig::StoredFieldUserData()
{
  return fFieldUserData != NNFConst::FieldUserData;
}

void __fastcall TNNFConfig::Notification( TComponent *AComponent, TOperation Operation )
{
  inherited::Notification( AComponent, Operation );
  if ( ( Operation == opRemove ) && ( AComponent == Connection ) )
    fConnection = nullptr;
}

void __fastcall TNNFConfig::Load()
{
  if ( !Enabled )
    return;

  switch ( StoreKind ) {
  case skFile:
    PrepareFilerFromFile();
    break;
  case skFiler:
    PrepareFilerFromUserEvent();
    break;
  case skDB:
    PrepareFilerFromDB();
  }
}

void __fastcall TNNFConfig::Save()
{
  if ( !Enabled )
    return;

  switch ( StoreKind ) {
  case skFile:
    SaveToFile();
    break;
  case skFiler:
    SaveToFiler();
    break;
  case skDB:
    SaveToDB();
  }
}

void __fastcall TNNFConfig::DoLoad()
{
  DoBeginLoad();
  try {
    if ( FOnLoad )
      FOnLoad(this);
  } __finally {
    DoEndLoad();
  }
}

void __fastcall TNNFConfig::DoDefault()
{
  DoBeginLoad();
  try {
    if ( FOnDefault )
      FOnDefault( this );
  } __finally {
    DoEndLoad();
  }
}

void __fastcall TNNFConfig::DoSave()
{
  DoBeginSave();
  try {
    if ( FOnSave )
      FOnSave( this );
  } __finally {
    DoEndSave();
  }
}

void __fastcall TNNFConfig::LoadFilerFromUserEvent()
{
  bool B = true;
  Filer->Position = 0;
  if ( Version == Filer->ReadChar() ) {
    DoLoad();
    if ( Version != Filer->ReadChar() )
      throw Exception( L"Ошибка чтения потока TNNFConfig" );
    else
      B = false;
  }
  if ( B )
    DoDefault();
}

void __fastcall TNNFConfig::SaveFilerFromUserEvent()
{
  Filer->Position = 0;
  Filer->WriteChar( Version );
  DoSave();
  Filer->WriteChar( Version );
  Filer->Size = Filer->Position;
}

void __fastcall TNNFConfig::PrepareFilerFromFile()
{
  String fn = RegistryKey();
  if ( !FileExists( fn ) ) {
    DoDefault();
    return;
  }

  std::unique_ptr< TFileStream >fs( new TFileStream( fn, fmOpenRead ) );
  fFiler = new TNNFTextStream( fs.get() );
  try {
    LoadFilerFromUserEvent();
  } __finally {
    delete fFiler;
    fFiler = nullptr;
  }
}

void __fastcall TNNFConfig::PrepareFilerFromDB()
{
  fFiler = new TNNFTextStream( nullptr );

  try {
    if ( LoadFromDB() )
      LoadFilerFromUserEvent();
    else
      DoDefault();
  } __finally {
    delete fFiler;
    fFiler = nullptr;
  }
}

void __fastcall TNNFConfig::PrepareFilerFromUserEvent()
{
  if ( Filer )
    throw Exception( L"Не определён fFiler" );

  DoGetFiler();
  if ( Filer && ( Filer->Size != 0 ) )
    LoadFilerFromUserEvent();
  else
    DoDefault();
}

void __fastcall TNNFConfig::SaveToFile()
{
  String fn = RegistryKey();
  if ( !FileExists( fn ) ) {
    NativeUInt H = FileCreate( fn );
    FileClose( H );
  }
  TFileStream* fs = new TFileStream( fn, fmOpenWrite );
  fFiler = new TNNFTextStream( fs );
  try {
    SaveFilerFromUserEvent();
  } __finally {
    delete fFiler;
    fFiler = nullptr;
    if ( fs )
      delete fs;
  }
}

void __fastcall TNNFConfig::SaveToFiler()
{
  fFiler = nullptr;
  DoGetFiler();
  if ( Filer )
    SaveFilerFromUserEvent();
}

void __fastcall TNNFConfig::SetConnection(TFDConnection *value)
{
  if ( Connection != value ) {
    fConnection = value;
    if ( value )
      value->FreeNotification( this );
  }
}

void __fastcall TNNFConfig::PrepareQuerySQL( TNNFQuery *quReg, const String &UserRegKey )
{
  quReg->SQL->Text = "select " + FieldUserRegKey + "," + FieldUserData +
                    " from &PRABHUPADA_SCHEMA" + TableUserReg +
                    " where " + FieldUserRegKey + " = :UserRegKey_";
  quReg->Params->Items[ 0 ]->DataType = ftString;
  quReg->Params->Items[ 0 ]->AsString = UserRegKey;
  quReg->UpdateOptions->AutoCommitUpdates = true;
  quReg->PrepareStandartMacros();
  quReg->Open();
}

void __fastcall TNNFConfig::SaveToDB()
{
  if ( !IsConnection() )
    return;

  String RK = RegistryKey();
  fFiler = new TNNFTextStream( nullptr );
  try {
    SaveFilerFromUserEvent();
    std::unique_ptr< TNNFQuery > quReg( new TNNFQuery( this ) );
    std::unique_ptr< TFDTransaction > trReg( new TFDTransaction( this ) );
    quReg->Connection = Connection;
    trReg->Connection = Connection;
    quReg->Transaction = trReg.get();
    PrepareQuerySQL( quReg.get(), RK );
    if ( quReg->RecordCount == 0 ) {
      quReg->Insert();
      quReg->Fields->Fields[ 0 ]->AsString = RK;
    }
    else
      quReg->Edit();
    TBlobField *bf = ( ( TBlobField* )( quReg->Fields->Fields[ 1 ] ) );
    bf->LoadFromStream( Filer );
    quReg->Post();
  } __finally {
    delete fFiler;
    fFiler = nullptr;
  }
}

bool __fastcall TNNFConfig::LoadFromDB()
{
  if ( !IsConnection() )
    return false;

  bool B = false;
  std::unique_ptr< TNNFQuery > quReg( new TNNFQuery( this ) );
  std::unique_ptr< TFDTransaction > trReg( new TFDTransaction( this ) );
  quReg->Connection = Connection;
  trReg->Connection = Connection;
  quReg->Transaction = trReg.get();
  String RK = RegistryKey();
  PrepareQuerySQL( quReg.get(), RK );
  if ( quReg->RecordCount == 1 ) {
    TBlobField *bf = ( ( TBlobField* )( quReg->Fields->Fields[ 1 ] ) );
    bf->SaveToStream( Filer );
    B = true;
  }
  return B;
}

String __fastcall TNNFConfig::RegistryKey()
{
  String S;

  if ( StaticRegistryKey.IsEmpty() ) {
    S = NNF::ComponentToKey( Owner, UseOwnerNameInRegistryKey );
  } else
    S = StaticRegistryKey;

  String AUserName;
  if ( Connection != nullptr )
    AUserName = Connection->Params->UserName;

  if ( StaticUserName.IsEmpty() ) {
    if ( !AUserName.IsEmpty() )
      S = AUserName + L"-" + S;
  } else {
    S = StaticUserName + L"-" + S;
  }

  if ( !PrefixRegistryKey.IsEmpty() )
    S = PrefixRegistryKey + S;

  return S;
}

bool __fastcall TNNFConfig::IsConnection()
{
  if ( Connection == nullptr )
    return false;
  else
    return Connection->Connected;
}

// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
static inline void ValidCtrCheck( TNNFQuery * )
{
  new TNNFQuery( nullptr );
  new TNNFConfig( nullptr );
}

namespace Fmx_nndbmiracle {

void __fastcall PACKAGE Register()
{
  TComponentClass classes[ 2 ];

  classes[ 0 ] = __classid( TNNFQuery );
  classes[ 1 ] = __classid( TNNFConfig );

  RegisterComponents( L"FMX New Navadvipa", classes, 1 );
}

}

