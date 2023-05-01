// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef FMX_NNDBMiracleH
#define FMX_NNDBMiracleH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.hpp>
#include <FMX.TreeView.hpp>
#include <Data.DB.hpp>
#include <System.RegularExpressions.hpp>
#include <set>
#include <map>
#include <vector>
#include "FMX_NNDisp.h"
#include "FMX_NNSearchOption.h"
#include "FMX_NNConst.h"
#include "FMX_NNDialog.h"
#include "NNNavHistory.h"

namespace NNF {

using TSelectedFunction = PACKAGE bool __fastcall ( __closure * )();

extern PACKAGE const int tvID;
extern PACKAGE const int tvParentID;
extern PACKAGE const int tvText;
extern PACKAGE const int tvActual;

extern PACKAGE const short InsertIsConfirm;
extern PACKAGE const short InsertIsChild;
extern PACKAGE const short InsertIsNoChild;
extern PACKAGE const short InsertIsCancel;

extern PACKAGE const long long int EmptyPK;

}

PACKAGE enum TNNFDragDropKind
{
  ddkMove
, ddkCustom
, ddkInherit
};

class PACKAGE TNNFNodeParams
{
public:
  String Text;
  int ImageIndex;
  int SelectedIndex;

  TNNFNodeParams();
  void __fastcall Clear();
};

class PACKAGE TNNFQuery;

using TNNFGetNodeParams = PACKAGE void __fastcall( __closure * )( System::TObject* Sender, TNNFNodeParams &NodeParams );
using TNNFSetNodeText   = PACKAGE void __fastcall( __closure * )( System::TObject* Sender, String &Text );
using TNNFGetUserData   = PACKAGE void __fastcall( __closure * )( System::TObject* Sender, int UserData, long long int &Result, bool &Apply );
using TNNFSetUserData   = PACKAGE void __fastcall( __closure * )( System::TObject* Sender, int UserData, long long int Value );

namespace NNF {

extern PACKAGE const bool NoLockRecord;
extern PACKAGE const bool LockRecord;

}

class PACKAGE TNNFFilter
{
private:
  TField *FFieldFilter = nullptr;
  String FStrFilter;
  TRegEx *FRegEx = nullptr;
  bool FEnable = false;
  NNF::TSearchOptions FSearchOptions;
  TFilterRecordEvent FEventFilter;
public:

  TNNFFilter();
  ~TNNFFilter();
  TNNFFilter( bool aEnable
            , TField *aField
            , const String &S
            , const NNF::TSearchOptions &aSearchOptions );
  TNNFFilter( const TFilterRecordEvent &aEvent, bool aEnable );
  TNNFFilter& operator = ( const TNNFFilter & a );
  TNNFFilter& operator = ( TNNFFilter && a );
  void __fastcall FilterEvent( TDataSet *DataSet, bool &Accept );

  __property TField *FieldFilter = { read = FFieldFilter };
  __property String StrFilter = { read = FStrFilter };
  __property TRegEx *RegEx = { read = FRegEx };
  __property bool Enable = { read = FEnable, write = FEnable };
  __property TFilterRecordEvent EventFilter = { read = FEventFilter, write = FEventFilter };
  __property NNF::TSearchOptions SearchOptions = { read = FSearchOptions, write = FSearchOptions };
};

class PACKAGE TNNFFilterMap : public std::map< String, TNNFFilter > {
private:
  using inherited = std::map< String, TNNFFilter >;
  TNNFQuery *DataSet;
  int fCounter;

  void __fastcall FilterEvent( TDataSet *DataSet, bool &Accept );

public:
  TNNFFilterMap( TNNFQuery *DSet );
  void __fastcall RefreshFilter();
  void __fastcall EraseFilterSearch();
  bool __fastcall IsFilterSearchPresent();
};

class PACKAGE TNNFFieldUpdate {
public:
  bool Obligatory;
  TField *Field;

  TNNFFieldUpdate();
  TNNFFieldUpdate(TField *aField);
  TNNFFieldUpdate(bool aObligatory, TField *aField);
};

using TVectorOfField = PACKAGE std::map< TField*, TNNFFieldUpdate >;
using TSetOfField    = PACKAGE std::set< TField* >;

namespace NNF {

class PACKAGE TBufferIntBox
{
private:
  bool FIsCut = false;
  TNNFQuery* FLabel = nullptr;
  std::vector< long long int > FVectorID;
public:
  TBufferIntBox();
  ~TBufferIntBox();
  __property bool IsCut = { read = FIsCut, write = FIsCut };
  __property TNNFQuery* Label = { read = FLabel, write = FLabel };
  __property std::vector< long long int > VectorID = { read = FVectorID };
};

}

class PACKAGE TNNFQuery : public TFDQuery
{
private:
  using inherited = TFDQuery;
  Variant fUKey;
  String FFieldSearchName;
  String fNote;
  String fCWUniqueFields;
  bool FFilteredEnable = false;
  TNotifyEvent FOnSetVariableRecord;
  TNNFFilterMap FFilterMap;
  int FOpenCounter = 0;
  bool FIsWorkFilter = false;
  long long int FDeleteNodePK = NNF::EmptyPK;

  String FOrderByDefault;
  String FPasteProcedure;
  String FMergeProcedure;

  //TColumn* FOrderByColumn = nullptr;
  NNF::TMapSearch FMapSearch;
  bool FNeedSave = true;

  void __fastcall SetFilteredEnable( bool Value );
  void __fastcall SaveDlg();
  //void __fastcall SetOrderByColumn( TColumn *Value );
  String __fastcall DefaultPasteProcedure();
  bool __fastcall StoredPasteProcedure();
  String __fastcall DefaultMergeProcedure();
  bool __fastcall StoredMergeProcedure();
  TField* __fastcall GetFieldSearch();
  void __fastcall SaveCachedUpdates( TObject* Sender, const TModalResult AResult );

protected:
  virtual void __fastcall Loaded();
  virtual void __fastcall DoBeforeDelete();
  virtual void __fastcall DoAfterDelete();
  virtual void __fastcall DoAfterOpen();
  virtual void __fastcall DoBeforeClose();
  virtual void __fastcall DoSetVariableRecord();
  virtual void __fastcall SetName( const TComponentName Value );
public:
  __fastcall TNNFQuery( TComponent* Owner );
  __fastcall ~TNNFQuery();
  inline void __fastcall ClearVectorSearch() { MapSearch.VectorSearch.clear(); };
  void __fastcall DBPaste( NNF::TBufferIntBox &ABufferIntBox, TNNFQuery *QU, TField *F );
  void __fastcall DBMerge( NNF::TBufferIntBox &ABufferIntBox, TNNFQuery *QU, TField *F );
  virtual void __fastcall Post();
  bool __fastcall GotoUKey( const Variant &V, const String &UniqueFields_ );
  bool __fastcall GotoUKey( const Variant &V );
  void __fastcall GetUKey( Variant &V, const String &UniqueFields_ );
  void __fastcall GetUKey( Variant &V);
  void __fastcall SaveUKey();
  bool __fastcall GotoUKey();
  void __fastcall CWRefresh();
  void __fastcall CWRefreshWithoutTree();
  void __fastcall CWRefreshRecord();
  bool __fastcall CWLocate( const String KeyFields, const System::Variant &KeyValues );
  void __fastcall ClearAll();
  void __fastcall CWApplyUpdates();
  void __fastcall DeclareAndSetParam( const String &AParam, Variant Value );
  bool __fastcall CheckFields( TVectorOfField &VField );
  bool __fastcall CheckFieldsModify( TSetOfField &VField );
  void __fastcall SetNewRecord( TVectorOfField &VField );
  long long int __fastcall GetNewID( String SQ, TNNFQuery *Query );
  void __fastcall CWCheckBrowseMode();
  void __fastcall CWCheckEditMode();
  void __fastcall CWOpen();
  void __fastcall CWOpenIf(bool Condition);
  void __fastcall CWOpenIfClose();
  void __fastcall CWClose();
  void __fastcall CWCloseAlways();
  void __fastcall CWReopen();
  void __fastcall CWActiveReopen();
  void __fastcall CWReconnectReopen( bool NeedClose_ );
  bool __fastcall IsEditModes();
  void __fastcall CalcFieldFilterPresent();
  void __fastcall CWDeleteVariable( const String &VariableName );
  bool __fastcall CWSetVariable( const String &VariableName
                               , const Variant &Value );
  TField* __fastcall CWFindField( const String &AFieldName, TADTField *AF = nullptr );
  void __fastcall SaveToFiler( TNNFTextStream *Filer );
  void __fastcall LoadFromFiler( TNNFTextStream *Filer );
  void __fastcall PrepareStandartMacros();
  __property int OpenCounter = { read = FOpenCounter };
  __property TNNFFilterMap FilterMap = { read = FFilterMap };
  __property bool IsWorkFilter = { read = FIsWorkFilter, write = FIsWorkFilter };
  __property long long int DeleteNodePK = { read = FDeleteNodePK };
  //__property TColumn* OrderByColumn = { read = FOrderByColumn, write = SetOrderByColumn };
  __property TField* FieldSearch = { read = GetFieldSearch };
  __property NNF::TMapSearch MapSearch = { read = FMapSearch };
__published:
  __property String OrderByDefault = { read = FOrderByDefault, write = FOrderByDefault };
  __property String FieldSearchName = { read = FFieldSearchName, write = FFieldSearchName };
  __property bool FilteredEnable = { read = FFilteredEnable, write = SetFilteredEnable, default = true };
  __property String Note = { read = fNote, write = fNote };
  __property TNotifyEvent OnSetVariableRecord = { read = FOnSetVariableRecord, write = FOnSetVariableRecord };
  __property String CWUniqueFields = { read = fCWUniqueFields, write = fCWUniqueFields };
  __property String PasteProcedure = { read = FPasteProcedure, write = FPasteProcedure, stored = StoredPasteProcedure };
  __property String MergeProcedure = { read = FMergeProcedure, write = FMergeProcedure, stored = StoredMergeProcedure };
  __property bool NeedSave = { read = FNeedSave, write = FNeedSave, default = true };
};

class PACKAGE TNNFConfig : public TComponent {
private:
  using inherited = TComponent;
  TNotifyEvent FOnLoad;
  TNotifyEvent FOnSave;
  TNotifyEvent FOnDefault;
  TNotifyEvent FOnBeginLoad;
  TNotifyEvent FOnEndLoad;
  TNotifyEvent FOnBeginSave;
  TNotifyEvent FOnEndSave;
  TNNFGetFiler FOnGetFiler;
  char fVersion;
  TNNFStoreKind fStoreKind = skDB;
  TNNFTextStream *fFiler = nullptr;
  TFDConnection *fConnection = nullptr;
  bool fEnabled = true;
  String fTableUserReg;
  String fFieldUserRegKey;
  String fFieldUserData;
  String FStaticRegistryKey;
  String FStaticUserName;
  String FPrefixRegistryKey;
  bool FUseUserNameInRegistryKey = true;
  bool FUseOwnerNameInRegistryKey = true;

  bool __fastcall StoredTableUserReg();
  bool __fastcall StoredFieldUserRegKey();
  bool __fastcall StoredFieldUserData();
  void __fastcall PrepareQuerySQL( TNNFQuery *quReg, const String &UserRegKey );
  bool __fastcall LoadFromFiler();
  bool __fastcall LoadFromDB();
  void __fastcall PrepareFilerFromFile();
  void __fastcall PrepareFilerFromUserEvent();
  void __fastcall PrepareFilerFromDB();
  void __fastcall LoadFilerFromUserEvent();
  void __fastcall SaveFilerFromUserEvent();
  void __fastcall LoadFile();
  void __fastcall LoadFiler();
  void __fastcall SaveToFile();
  void __fastcall SaveToFiler();
  void __fastcall SaveToDB();
  void __fastcall SetConnection( TFDConnection *value );
  bool __fastcall IsConnection();

protected:
  virtual void __fastcall Notification( TComponent *AComponent, TOperation Operation );
  virtual void __fastcall DoLoad();
  virtual void __fastcall DoSave();
  virtual void __fastcall DoDefault();

  virtual void __fastcall DoBeginLoad()
  {
    if ( FOnBeginLoad )
      FOnBeginLoad( this );
  };

  virtual void __fastcall DoEndLoad()
  {
    if ( FOnEndLoad )
      FOnEndLoad( this );
  };

  virtual void __fastcall DoBeginSave()
  {
    if ( FOnBeginSave )
      FOnBeginSave( this );
  };

  virtual void __fastcall DoEndSave()
  {
    if ( FOnEndSave )
      FOnEndSave( this );
  };

  virtual void __fastcall DoGetFiler()
  {
    if ( FOnGetFiler )
      FOnGetFiler( this, fFiler );
  };

public:
  __fastcall TNNFConfig( TComponent* Owner );
  __property TNNFTextStream *Filer = { read = fFiler };
  String __fastcall RegistryKey();
  void __fastcall Load();
  void __fastcall Save();

__published:
  __property TNNFStoreKind StoreKind = { read = fStoreKind, write = fStoreKind, default = skDB };
  __property char Version = { read = fVersion, write = fVersion, default = char() };
  __property bool Enabled = { read = fEnabled, write = fEnabled, default = true };
  __property TNotifyEvent OnLoad = { read = FOnLoad, write = FOnLoad };
  __property TNotifyEvent OnSave = { read = FOnSave, write = FOnSave };
  __property TNotifyEvent OnDefault = { read = FOnDefault, write = FOnDefault };
  __property TNotifyEvent OnBeginLoad = { read = FOnBeginLoad, write = FOnBeginLoad };
  __property TNotifyEvent OnEndLoad = { read = FOnEndLoad, write = FOnEndLoad };
  __property TNotifyEvent OnBeginSave = { read = FOnBeginSave, write = FOnBeginSave };
  __property TNotifyEvent OnEndSave = { read = FOnEndSave, write = FOnEndSave };
  __property TNNFGetFiler OnGetFiler = { read = FOnGetFiler, write = FOnGetFiler };
  __property TFDConnection *Connection = { read = fConnection, write = SetConnection };
  __property String TableUserReg = { read = fTableUserReg, write = fTableUserReg, stored = StoredTableUserReg };
  __property String FieldUserRegKey = { read = fFieldUserRegKey, write = fFieldUserRegKey, stored = StoredFieldUserRegKey };
  __property String FieldUserData = { read = fFieldUserData, write = fFieldUserData, stored = StoredFieldUserData };
  __property String StaticRegistryKey = { read = FStaticRegistryKey, write = FStaticRegistryKey };
  __property String StaticUserName = { read = FStaticUserName, write = FStaticUserName };
  __property String PrefixRegistryKey = { read = FPrefixRegistryKey, write = FPrefixRegistryKey };
  __property bool UseUserNameInRegistryKey = { read = FUseUserNameInRegistryKey, write = FUseUserNameInRegistryKey, default = true };
  __property bool UseOwnerNameInRegistryKey = { read = FUseOwnerNameInRegistryKey, write = FUseOwnerNameInRegistryKey, default = true };
};

namespace NNF {

class PACKAGE TDSetBookmark {
public:
  TNNFQuery *DataSet;
  Variant UKey;

  TDSetBookmark();
  ~TDSetBookmark();
  TDSetBookmark( const TDSetBookmark& a );
  TDSetBookmark( TNNFQuery *aDataSet );
  TDSetBookmark& operator = ( const TDSetBookmark &a );
  void __fastcall Execute( );
};

using TDSetBookmarks = PACKAGE TBookmarks < int, TDSetBookmark >;

class PACKAGE TMapQuery : public std::map< String, TNNFQuery* > {
private:
  using inherited = std::map< String, TNNFQuery* >;
public:
  TMapQuery();
  TMapQuery( TComponent *AOwner );
  ~TMapQuery();
  void __fastcall SaveToFiler( TNNFTextStream *Filer );
  void __fastcall LoadFromFiler( TNNFTextStream *Filer );
  void __fastcall PrepareStandartMacros();
};

}

namespace NNF {

class PACKAGE TStoryInfo {
public:
  Variant Value;

  TStoryInfo();
  TStoryInfo( const Variant &aValue );
};

using TStoryMap      = PACKAGE std::map< TField*, TStoryInfo >;
using TSettingSet    = PACKAGE std::set< TField* >;
using TRightFieldMap = PACKAGE std::map< TField*, bool >;

using TDoInsertLanguageRow = PACKAGE void __fastcall( __closure * )( const String &ALanguageStringID, String &ATranslate, bool &ATranslateSet );
using TDoPrepareOwner      = PACKAGE void __fastcall( __closure * )( const String &AOwnerString );
using TDoLogin             = PACKAGE void __fastcall( __closure * )( System::TObject* Sender, TFDConnection *AConnection );

}

#endif

