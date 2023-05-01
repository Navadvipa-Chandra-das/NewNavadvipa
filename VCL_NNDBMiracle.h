// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef VCL_NNDBMiracleH
#define VCL_NNDBMiracleH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Data.DB.hpp>
#include <set>
#include <map>
#include <vector>
#include "VCL_NNDisp.h"
#include "VCL_NNSearchOption.h"
#include "VCL_NNConst.h"
#include "VCL_NNDialog.h"
#include "NNNavHistory.h"
#include "Vcl.CheckLst.hpp"

namespace NNV {

using TSelectedFunction = PACKAGE bool __fastcall ( __closure * )();
extern PACKAGE void __fastcall MakeNodeActive( TTreeNode *Node );

using TNavTreeNode = PACKAGE void __fastcall( * ) ( TTreeNode* );
using TNavTree = PACKAGE NN::TNavHistory< TTreeNode*, TNavTreeNode >;

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

using TNNVTreeViewNewEditCancelEvent = PACKAGE void __fastcall( __closure * )( System::TObject *Sender, TTreeNode *Node, bool &IsDeleteNode );

class PACKAGE TNNVTreeView : public TTreeView
{
private:
  using inherited = TTreeView;
  bool fSearchReset;
  bool FSearchExecute;
  TStringList *FSearchHistory;
  bool FTextEmpty;
  TTVChangedEvent FOnCWEditCancel;
  TNNVTreeViewNewEditCancelEvent FOnCWNewEditCancel;
  TDBEdit *FEditKindID = nullptr;

  NNV::TSearchDlgOptions SearchDlgOptions;
  NNV::TNavTree fNavTree;
  void __fastcall SetSearchDialogOptions();
  void __fastcall SaveSearchDialogOptions();
  void __fastcall SetEditKindID( TDBEdit *Value );
  void __fastcall PrepareSearch( TObject *Sender );
  void __fastcall ExecuteSearch( TObject *Sender );

protected:
  bool FIsEditingNew;

  DYNAMIC void __fastcall Change( TTreeNode *Node );
  DYNAMIC void __fastcall KeyDown( Word &Key, TShiftState Shift );
  DYNAMIC void __fastcall Edit( const tagTVITEMW &Item );
  virtual void __fastcall DoCWEditCancel( TTreeNode *Node );
  virtual void __fastcall DoCWNewEditCancel( TTreeNode *Node, bool &IsDeleteNode );
  virtual void __fastcall CWDoEdit( TTreeNode *Node );

public:
  __fastcall TNNVTreeView( TComponent* Owner );
  __fastcall ~TNNVTreeView();
  TTreeNode* __fastcall NewChildAndEdit( TTreeNode *Node, const System::String S );
  void __fastcall ExecuteSearchDialog();
  void __fastcall SearchNext();

  void __fastcall ResetSearch()
  {
    fSearchReset = true;
  };
  void __fastcall SaveToFiler( TNNVTextStream *Filer );
  void __fastcall LoadFromFiler( TNNVTextStream *Filer );
  String __fastcall PathStr( bool IsRoot_ );
  __property bool IsEditingNew = { read = FIsEditingNew };
  __property NNV::TNavTree NavTree = { read = fNavTree };

__published:
  __property TTVChangedEvent OnCWEditCancel = { read = FOnCWEditCancel, write = FOnCWEditCancel };
  __property TNNVTreeViewNewEditCancelEvent OnCWNewEditCancel = { read = FOnCWNewEditCancel, write = FOnCWNewEditCancel };
  __property TDBEdit *EditKindID = { read = FEditKindID, write = SetEditKindID };
};

PACKAGE enum TNNVDragDropKind
{
  ddkMove
, ddkCustom
, ddkInherit
};

class PACKAGE TNNVNodeParams
{
public:
  String Text;
  int ImageIndex;
  int SelectedIndex;

  TNNVNodeParams();
  void __fastcall Clear();
};

class PACKAGE TNNVQuery;
class PACKAGE TNNVNodeAdmin;

class PACKAGE TNNVTreeNode : public TTreeNode
{
private:
  using inherited = TTreeNode;

public:
  __fastcall TNNVTreeNode( TTreeNodes *AOwner );

  TNNVNodeAdmin *NodeAdmin;
  long long int PK;
};

using TNNVGetNodeParams     = PACKAGE void __fastcall( __closure * )( System::TObject* Sender, TNNVNodeParams &NodeParams );
using TNNVSetNodeText       = PACKAGE void __fastcall( __closure * )( System::TObject* Sender, String &Text );
using TNNVMergeNodes        = PACKAGE void __fastcall( __closure * )( System::TObject* Sender, TTreeNode *Source, TTreeNode *Target );
using TNNVGetUserData       = PACKAGE void __fastcall( __closure * )( System::TObject* Sender, int UserData, long long int &Result, bool &Apply );
using TNNVSetUserData       = PACKAGE void __fastcall( __closure * )( System::TObject* Sender, int UserData, long long int Value );
using TNNVOnPasteNode       = PACKAGE void __fastcall( __closure * )( System::TObject* Sender, TTreeNode *TargetNode );
using TNNVOnNodeAdminChange = PACKAGE void __fastcall( __closure * )( System::TObject* Sender, TNNVNodeAdmin *NodeAdmin );

using TNNVNodeVector = PACKAGE std::vector< TNNVNodeAdmin* >;

namespace NNV {

using TNodeAdminPair = PACKAGE TDispPairTemplate< TNNVNodeAdmin*, TNotifyEvent >;

class PACKAGE TNodeAdmins : public TMapDispatcher< TNNVNodeAdmin*, TNodeAdminPair* >
{
private:
  using inherited = TMapDispatcher< TNNVNodeAdmin*, TNodeAdminPair* >;

public:
  iterator __fastcall Add( TNNVNodeAdmin* ANodeAdmin );
};

class PACKAGE TTreeBookmark
{
public:
  TTreeBookmark();
  TTreeBookmark( TNNVTreeNode *ANode, long long int ADetailPK );

  TNNVTreeNode *Node;
  long long int DetailPK;

  void __fastcall Execute();
};

using TTreeBookmarks = PACKAGE TBookmarks< int, TTreeBookmark >;
using TMapLoadNodes = PACKAGE std::map< long long int, TNNVTreeNode* >;

}

class PACKAGE TNNVDBTreeView : public TNNVTreeView
{
private:
  using inherited = TNNVTreeView;
  TNNVNodeAdmin *FNodeAdmin = nullptr;

  NNV::TNodeAdmins *FNodeAdmins;

  TNNVNodeAdmin *FLoadAdmin = nullptr;
  TNNVNodeAdmin *FRefreshAdmin = nullptr;
  TDataSet *FLoadDataSet = nullptr;
  int FWork = 0;
  TDataSource *FDataSource;
  TTreeNode *fStartNode;
  TNNVDragDropKind FDragDropKind = ddkMove;

  TNNVOnPasteNode FOnPasteNode;
  TNNVOnNodeAdminChange FOnNodeAdminChange;
  bool FIsStartAdmin = false;
  int FActiveOrder = 0;

  NNV::TTreeBookmarks FTreeBookmarks;

  bool FIsRefresh = false;
  bool AdminRefreshWork;
  TNNVNodeVector fNodeVector;

  TField* FLoadDataSetFieldID;
  TField* FLoadDataSetFieldParentID;
  TField* FLoadDataSetFieldText;

  void __fastcall CWInsertNode( short Action );
  TTreeNode* __fastcall AddNodes( const NNV::TMapLoadNodes &MapLoadNodes );
  void __fastcall DataChange( TObject *Sender, TField *Field );
  void __fastcall UpdateData( TObject *Sender );
  TTreeNode* __fastcall FindNode();
  TDataSet* __fastcall GetDataSet();
  void __fastcall SetDataSet( TDataSet *Value );
  bool __fastcall Locate( TNNVTreeNode *Node );
  void __fastcall SetNodeAdmin( TNNVNodeAdmin *Value );
  void __fastcall SetLoadAdmin( TNNVNodeAdmin *Value );
  void __fastcall CWMoveNode( TTreeNode *TargetNode );
  void __fastcall NewPosNode( TTreeNode *TargetNode );
  void __fastcall GetNewLocateNode();
  void __fastcall PowderTree();
  bool __fastcall GetKeyEnabled();
  void __fastcall RefreshBugUpdate();
  void __fastcall DeleteNodeForRefresh( TNNVTreeNode *TN );
  void __fastcall SetLoadDataSet( TDataSet *Value );
  long long int __fastcall TreeSortInfo( long long int &Oldpk
                                , long long int &Newpk
                                , const String &Table
                                , const String &Fieldpk );
  void __fastcall TreeSort( long long int Oldsortno
                          , long long int Newsortno
                          , const String &Table
                          , const String &Fieldpk
                          , long long int Parentno );
  void __fastcall SetNewParentID( long long int NewParentID, TTreeNode *TargetNode );
  __property TNNVNodeAdmin *LoadAdmin = { read = FLoadAdmin, write = SetLoadAdmin };
  __property TField* LoadDataSetFieldID = { read = FLoadDataSetFieldID };
  __property TField* LoadDataSetFieldParentID = { read = FLoadDataSetFieldParentID };
  __property TField* LoadDataSetFieldText = { read = FLoadDataSetFieldText };
  __property TDataSet *LoadDataSet = {read = FLoadDataSet, write = SetLoadDataSet };

protected:
  virtual void __fastcall Notification( TComponent *AComponent, TOperation Operation );
  DYNAMIC void __fastcall DoStartDrag( Controls::TDragObject* &DragObject );
  DYNAMIC void __fastcall DragOver( System::TObject* Source, int X, int Y
                                  , TDragState State, bool &Accept );
  DYNAMIC void __fastcall Change( TTreeNode *Node );
  DYNAMIC void __fastcall KeyDown( Word &Key, TShiftState Shift );
  DYNAMIC void __fastcall DoEnter();
  virtual TTreeNode* __fastcall CreateNode();
  virtual void __fastcall DoCWNewEditCancel( TTreeNode *Node
                                           , bool &IsDeleteNode );
  virtual void __fastcall CWDoEdit( TTreeNode *Node );
  virtual void __fastcall DoPasteNode( TTreeNode *TargetNode );
  virtual void __fastcall DoNodeAdminChange( TNNVNodeAdmin *ANodeAdmin );

public:
  __fastcall TNNVDBTreeView( TComponent* Owner );
  virtual __fastcall ~TNNVDBTreeView();
  void __fastcall CWNodeCompare( TObject *Sender, TTreeNode *Node1
                               , TTreeNode *Node2, int Data, int &Compare );
  DYNAMIC void __fastcall DragDrop( System::TObject* Source, int X, int Y );
  TTreeNode* __fastcall FindNodePK( TNNVNodeAdmin *ANodeAdmin, long long int PK );
  void __fastcall CutNode();
  void __fastcall PasteNode( TTreeNode *TargetNode );
  void __fastcall CWMergeNodes( TTreeNode *TargetNode );
  void __fastcall DeleteNode();
  bool __fastcall CancelNewNode();
  void __fastcall LoadNodeAdmin( TNNVTreeNode *Node
                               , TNNVNodeAdmin *aNodeAdmin
                               , long long int ARootID );
  void __fastcall CWDeleteAllChild( TTreeNode *Node );
  void __fastcall StartAdmin();
  void __fastcall FinishAdmin();
  void __fastcall NodeAdminSelect( TNNVNodeAdmin *ANodeAdmin );
  void __fastcall CWRefresh();
  void __fastcall CWRefreshAdmin();
  void __fastcall CWReload( TNNVNodeAdmin *ANodeAdmin );
  void __fastcall SaveToFiler( TNNVTextStream *Filer );
  void __fastcall LoadFromFiler( TNNVTextStream *Filer );
  __property int Work = { read = FWork };
  __property TNNVNodeAdmin *RefreshAdmin = { read = FRefreshAdmin, write = FRefreshAdmin };
  __property TDataSource* DataSource = { read = FDataSource };
  __property bool IsRefresh = { read = FIsRefresh };
  __property TTreeNode *StartNode = { read = fStartNode };
  __property TDataSet* DataSet = { read = GetDataSet, write = SetDataSet };
  __property TNNVNodeAdmin *NodeAdmin = { read = FNodeAdmin, write = SetNodeAdmin };
  __property NNV::TNodeAdmins *NodeAdmins = { read = FNodeAdmins };
  __property bool KeyEnabled = { read = GetKeyEnabled };
  __property bool IsStartAdmin = { read = FIsStartAdmin };
  __property TNNVNodeVector NodeVector = { read = fNodeVector };

__published:
  __property HideSelection = { default = false };
  __property SortType = { default = Vcl::Comctrls::stText };
  __property TNNVDragDropKind DragDropKind = { read = FDragDropKind, write = FDragDropKind, default = ddkMove };
  __property TNNVOnPasteNode OnPasteNode = { read = FOnPasteNode, write = FOnPasteNode };
  __property TNNVOnNodeAdminChange OnNodeAdminChange = { read = FOnNodeAdminChange, write = FOnNodeAdminChange };
  __property int ActiveOrder = { read = FActiveOrder, write = FActiveOrder, default = 0 };
};
// ---------------------------------------------------------------------------

namespace NNV {

extern PACKAGE const bool NoLockRecord;
extern PACKAGE const bool LockRecord;

class PACKAGE TSetNodeAdmins : public std::set<TNNVNodeAdmin*>
{
private:
  using inherited = std::set< TNNVNodeAdmin* >;

public:
  bool Enable;

  TSetNodeAdmins();
  void __fastcall Refresh();
  bool __fastcall DeletePK( long long int PK );
};

}

class PACKAGE TNNVFilter
{
private:
  TField *FFieldFilter = nullptr;
  String FStrFilter;
  TRegEx *FRegEx = nullptr;
  bool FEnable = false;
  NNV::TSearchOptions FSearchOptions;
  TFilterRecordEvent FEventFilter;
public:

  TNNVFilter();
  ~TNNVFilter();
  TNNVFilter( bool aEnable
            , TField *aField
            , const String &S
            , const NNV::TSearchOptions &aSearchOptions );
  TNNVFilter( const TFilterRecordEvent &aEvent, bool aEnable );
  TNNVFilter& operator = ( const TNNVFilter & a );
  TNNVFilter& operator = ( TNNVFilter && a );
  void __fastcall FilterEvent( TDataSet *DataSet, bool &Accept );

  __property TField *FieldFilter = { read = FFieldFilter };
  __property String StrFilter = { read = FStrFilter };
  __property TRegEx *RegEx = { read = FRegEx };
  __property bool Enable = { read = FEnable, write = FEnable };
  __property TFilterRecordEvent EventFilter = { read = FEventFilter, write = FEventFilter };
  __property NNV::TSearchOptions SearchOptions = { read = FSearchOptions, write = FSearchOptions };
};

class PACKAGE TNNVFilterMap : public std::map< String, TNNVFilter > {
private:
  using inherited = std::map< String, TNNVFilter >;
  TNNVQuery *DataSet;
  int fCounter;

  void __fastcall FilterEvent( TDataSet *DataSet, bool &Accept );

public:
  TNNVFilterMap( TNNVQuery *DSet );
  void __fastcall RefreshFilter();
  void __fastcall EraseFilterSearch();
  bool __fastcall IsFilterSearchPresent();
};

class PACKAGE TNNVFieldUpdate {
public:
  bool Obligatory;
  TField *Field;

  TNNVFieldUpdate();
  TNNVFieldUpdate(TField *aField);
  TNNVFieldUpdate(bool aObligatory, TField *aField);
};

using TVectorOfField = PACKAGE std::map< TField*, TNNVFieldUpdate >;
using TSetOfField = PACKAGE std::set< TField* >;

namespace NNV {

class PACKAGE TBufferIntBox
{
private:
  bool FIsCut = false;
  TNNVQuery* FLabel = nullptr;
  std::vector< long long int > FVectorID;
public:
  TBufferIntBox();
  ~TBufferIntBox();
  __property bool IsCut = { read = FIsCut, write = FIsCut };
  __property TNNVQuery* Label = { read = FLabel, write = FLabel };
  __property std::vector< long long int > VectorID = { read = FVectorID };
};

}

class PACKAGE TNNVQuery : public TFDQuery
{
private:
  using inherited = TFDQuery;
  Variant fUKey;
  String FFieldSearchName;
  String fNote;
  String fCWUniqueFields;
  bool FFilteredEnable = false;
  TNotifyEvent FOnSetVariableRecord;
  TNNVFilterMap FFilterMap;
  int FOpenCounter = 0;
  bool FIsWorkFilter = false;
  long long int FDeleteNodePK = NNV::EmptyPK;

  NNV::TSetNodeAdmins *FAdminsSet;

  String FOrderByDefault;
  String FPasteProcedure;
  String FMergeProcedure;

  TColumn* FOrderByColumn = nullptr;
  NNV::TMapSearch FMapSearch;
  bool FNeedSave = true;

  void __fastcall SetFilteredEnable( bool Value );
  void __fastcall SaveDlg();
  void __fastcall SetOrderByColumn( TColumn *Value );
  String __fastcall DefaultPasteProcedure();
  bool __fastcall StoredPasteProcedure();
  String __fastcall DefaultMergeProcedure();
  bool __fastcall StoredMergeProcedure();
  TField* __fastcall GetFieldSearch();

protected:
  //virtual void __fastcall Loaded();
  virtual void __fastcall DoBeforeDelete();
  virtual void __fastcall DoAfterDelete();
  virtual void __fastcall DoAfterOpen();
  virtual void __fastcall DoBeforeClose();
  virtual void __fastcall DoSetVariableRecord();
  virtual void __fastcall SetName( const TComponentName Value );
public:
  __fastcall TNNVQuery( TComponent* Owner );
  __fastcall ~TNNVQuery();
  void __fastcall PrepareStandartMacros();
  inline void __fastcall ClearVectorSearch() { MapSearch.VectorSearch.clear(); };
  void __fastcall DBPaste( NNV::TBufferIntBox &ABufferIntBox, TNNVQuery *QU, TField *F );
  void __fastcall DBMerge( NNV::TBufferIntBox &ABufferIntBox, TNNVQuery *QU, TField *F );
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
  long long int __fastcall GetNewID( String SQ, TNNVQuery *Query );
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
  void __fastcall RemoveAdmin( TNNVNodeAdmin *aNodeAdmin );
  void __fastcall CalcFieldFilterPresent();
  void __fastcall CWDeleteVariable( const String &VariableName );
  bool __fastcall CWSetVariable( const String &VariableName
                               , const Variant &Value );
  TField* __fastcall CWFindField( const String &AFieldName, TADTField *AF = nullptr );
  void __fastcall SaveToFiler( TNNVTextStream *Filer );
  void __fastcall LoadFromFiler( TNNVTextStream *Filer );
  __property int OpenCounter = { read = FOpenCounter };
  __property TNNVFilterMap FilterMap = { read = FFilterMap };
  __property bool IsWorkFilter = { read = FIsWorkFilter, write = FIsWorkFilter };
  __property long long int DeleteNodePK = { read = FDeleteNodePK };
  __property NNV::TSetNodeAdmins *AdminsSet = { read = FAdminsSet };
  __property TColumn* OrderByColumn = { read = FOrderByColumn, write = SetOrderByColumn };
  __property TField* FieldSearch = { read = GetFieldSearch };
  __property NNV::TMapSearch MapSearch = { read = FMapSearch };
__published:
  __property String FieldSearchName = { read = FFieldSearchName, write = FFieldSearchName };
  __property String OrderByDefault = { read = FOrderByDefault, write = FOrderByDefault };
  __property bool FilteredEnable = { read = FFilteredEnable, write = SetFilteredEnable, default = true };
  __property String Note = { read = fNote, write = fNote };
  __property TNotifyEvent OnSetVariableRecord = { read = FOnSetVariableRecord, write = FOnSetVariableRecord };
  __property String CWUniqueFields = { read = fCWUniqueFields, write = fCWUniqueFields };
  __property String PasteProcedure = { read = FPasteProcedure, write = FPasteProcedure, stored = StoredPasteProcedure };
  __property String MergeProcedure = { read = FMergeProcedure, write = FMergeProcedure, stored = StoredMergeProcedure };
  __property bool NeedSave = { read = FNeedSave, write = FNeedSave, default = true };
};

namespace NNV {

class PACKAGE TDSetBookmark {
public:
  TNNVQuery *DataSet;
  Variant UKey;

  TDSetBookmark();
  ~TDSetBookmark();
  TDSetBookmark( const TDSetBookmark& a );
  TDSetBookmark( TNNVQuery *aDataSet );
  TDSetBookmark& operator = ( const TDSetBookmark &a );
  void __fastcall Execute( );
};

using TDSetBookmarks = PACKAGE TBookmarks < int, TDSetBookmark >;

class PACKAGE TMapQuery : public std::map< String, TNNVQuery* > {
private:
  using inherited = std::map< String, TNNVQuery* >;
public:
  TMapQuery();
  TMapQuery( TComponent *AOwner );
  ~TMapQuery();
  void __fastcall SaveToFiler( TNNVTextStream *Filer );
  void __fastcall LoadFromFiler( TNNVTextStream *Filer );
  void __fastcall PrepareStandartMacros();
};

}

class PACKAGE TNNVNodeAdmin : public TComponent {
private:
  using inherited = TComponent;
  friend class TNNVDBTreeView;
  TNotifyEvent FOnLoadNodes;
  TNNVGetNodeParams FOnGetNodeParams;
  TNNVSetNodeText FOnSetNodeText;
  TNNVMergeNodes FOnMergeNodes;
  TNotifyEvent FOnFirstEnter;
  TNotifyEvent FOnEnter;
  TNotifyEvent FOnExit;
  TNotifyEvent FOnLastExit;
  TNotifyEvent FOnGetBaseParent;
  TNotifyEvent FOnPrint;
  TNNVGetUserData FOnGetUserData;
  TNNVSetUserData FOnSetUserData;
  TTreeNode *FLocateNode = nullptr;
  TNNVTreeNode *FCurrentNode = nullptr;
  String fTableName;
  String fCaption;
  int FImageIndex = -1;
  // FBaseParent - значение поля PARENTNO для дерева если TNNVNodeAdmin не имеет одного корня
  long long int FBaseParent = NNV::EmptyPK;
  bool FReadOnly = false;
  bool FKeyEnabled = true;
  bool FMoveEnabled = true;
  bool FReloadEnabled = true;
  bool FActualOnly = true;
  bool FActualOnlyNeed = false;
  bool FEndToEndViewing = true;
  bool FEndToEndViewingNeed = false;

  Classes::THelpType FHelpType = htContext;
  Classes::THelpContext FHelpContext = 0;

  String fHelpKeyword;
  TNNVDragDropKind FDragDropKind = ddkCustom;
  TNNVDBTreeView *FTreeView = nullptr;
  int FLoadOrder = 1;
  long long int FActivePK = NNV::EmptyPK;
  long long int FDetailPK = NNV::EmptyPK;
  TDataSource *FDetailDataSource;
  TDataSource *FDataSource = nullptr;
  bool FEnabled = true;
  bool FStartDetailPK = false;

  void __fastcall DetailDataChange( TObject *Sender, TField *Field );
  void __fastcall SetActualOnly( bool Value );
  void __fastcall SetEndToEndViewing( bool Value );
  TNNVQuery* __fastcall GetDataSet();
  TNNVQuery* __fastcall GetDetailQuery();
  void __fastcall SetDataSource( TDataSource *Value );
  void __fastcall SaveDetailUKey();
  void __fastcall RestoreDetailUKey();
  void __fastcall SetDragDropKind( TNNVDragDropKind Value );
  void __fastcall SetTreeView( TNNVDBTreeView *Value );
  TNNVQuery* __fastcall GetDetailDataSet();
  void __fastcall SetDetailDataSet( TNNVQuery* Value );
  void __fastcall PrepareMacroActualOnly( TNNVQuery *qu, bool NeedTreeViewReloadNodeAdmin );
protected:
  virtual void __fastcall Notification( TComponent *AComponent
                                      , TOperation Operation );
  virtual void __fastcall Loaded();
  __property TDataSource *DetailDataSource = { read = FDetailDataSource };
  __property bool StartDetailPK = { read = FStartDetailPK, write = FStartDetailPK };
public:
  __fastcall TNNVNodeAdmin(TComponent* Owner);
  __fastcall ~TNNVNodeAdmin();
  void __fastcall PrepareDataSet();
  void __fastcall UnPrepareDataSet();
  virtual void __fastcall DoGetNodeParams( TNNVNodeParams &NodeParams );
  virtual void __fastcall DoSetNodeText(String S);
  virtual void __fastcall DoFirstEnter();
  virtual void __fastcall DoEnter();
  virtual void __fastcall DoExit();
  virtual void __fastcall DoLastExit();
  virtual void __fastcall DoLoadNodes();
  virtual void __fastcall DoMergeNodes(TTreeNode *Source, TTreeNode *Target);
  virtual void __fastcall DoGetBaseParent();
  void __fastcall DoInvertActual();
  virtual void __fastcall DoPrint();
  virtual void __fastcall DoGetUserData( int UserData, long long int &Result, bool &Apply );
  virtual void __fastcall DoSetUserData( int UserData, long long int Value );
  void __fastcall SaveDetailPK();
  void __fastcall RestoreDetailPK();
  // восстанавливаем позицию подчиненных таблиц
  void __fastcall FirstEnter( TObject *Sender );
  void __fastcall Enter( TObject *Sender );
  void __fastcall Exit( TObject *Sender );
  void __fastcall LastExit( TObject *Sender );
  void __fastcall LoadFromFiler( TNNVTextStream *Filer );
  void __fastcall SaveToFiler( TNNVTextStream *Filer );
  __property TTreeNode *LocateNode = { read = FLocateNode, write = FLocateNode };
  __property TNNVTreeNode *CurrentNode = { read = FCurrentNode, write = FCurrentNode };
  __property long long int BaseParent = { read = FBaseParent, write = FBaseParent };
  __property long long int ActivePK = { read = FActivePK, write = FActivePK };
  __property long long int DetailPK = { read = FDetailPK, write = FDetailPK };
  __property bool ActualOnly = { read = FActualOnly, write = SetActualOnly };
  __property bool EndToEndViewing = { read = FEndToEndViewing, write = SetEndToEndViewing };
  __property TNNVQuery *DataSet = { read = GetDataSet };
  __property TNNVQuery *DetailQuery = { read = GetDetailQuery };

__published:
  __property TNotifyEvent OnLoadNodes = { read = FOnLoadNodes, write = FOnLoadNodes };
  __property TNNVGetNodeParams OnGetNodeParams = { read = FOnGetNodeParams, write = FOnGetNodeParams };
  __property TNNVSetNodeText OnSetNodeText = { read = FOnSetNodeText, write = FOnSetNodeText };
  __property TNNVMergeNodes OnMergeNodes = { read = FOnMergeNodes, write = FOnMergeNodes };
  __property TNotifyEvent OnFirstEnter = { read = FOnFirstEnter, write = FOnFirstEnter };
  __property TNotifyEvent OnEnter = {read = FOnEnter, write = FOnEnter};
  __property TNotifyEvent OnExit = {read = FOnExit, write = FOnExit};
  __property TNotifyEvent OnLastExit = { read = FOnLastExit, write = FOnLastExit };
  __property TNotifyEvent OnGetBaseParent = { read = FOnGetBaseParent, write = FOnGetBaseParent };
  __property TNotifyEvent OnPrint = { read = FOnPrint, write = FOnPrint };
  __property TNNVGetUserData OnGetUserData = { read = FOnGetUserData, write = FOnGetUserData };
  __property TNNVSetUserData OnSetUserData = { read = FOnSetUserData, write = FOnSetUserData };
  __property bool ReadOnly = { read = FReadOnly, write = FReadOnly, default = false };
  __property TNNVDragDropKind DragDropKind = { read = FDragDropKind, write = SetDragDropKind, default = ddkMove };
  __property String TableName = { read = fTableName, write = fTableName };
  __property String Caption = { read = fCaption, write = fCaption };
  __property int ImageIndex = { read = FImageIndex, write = FImageIndex, default = -1 };
  __property bool KeyEnabled = { read = FKeyEnabled, write = FKeyEnabled, default = true };
  __property bool MoveEnabled = { read = FMoveEnabled, write = FMoveEnabled, default = true };
  __property bool ReloadEnabled = { read = FReloadEnabled, write = FReloadEnabled, default = true };
  __property bool ActualOnlyNeed = { read = FActualOnlyNeed, write = FActualOnlyNeed, default = false };
  __property bool EndToEndViewingNeed = { read = FEndToEndViewingNeed, write = FEndToEndViewingNeed, default = false };
  __property TNNVDBTreeView *TreeView = { read = FTreeView, write = SetTreeView };
  __property int LoadOrder = {read = FLoadOrder, write = FLoadOrder, default = 1 };
  __property TDataSet* DetailDataSet = { read = GetDetailDataSet, write = SetDetailDataSet };
  __property TDataSource *DataSource = { read = FDataSource, write = SetDataSource };
  __property Classes::THelpType HelpType = { read = FHelpType, write = FHelpType, default = htContext };
  __property Classes::THelpContext HelpContext = { read = FHelpContext, write = FHelpContext, default = 0 };
  __property String HelpKeyword = { read = fHelpKeyword, write = fHelpKeyword };
  __property bool Enabled = { read = FEnabled, write = FEnabled, default = true };
};

class PACKAGE TNNVDBGrid;

class PACKAGE TNNVGridColumn : public TColumn
{
private:
  using inherited = TColumn;
  friend class TNNVDBGrid;
  bool fIsFiltered;
  TNNVDialog *FDialog = nullptr;
  String FOrderBy;
  void __fastcall SetDialog( TNNVDialog *Value );

__published:
  __fastcall TNNVGridColumn(TCollection *Collection);
  __property bool IsFiltered = { read = fIsFiltered, write = fIsFiltered, default = true };
  __property TNNVDialog* Dialog = { read = FDialog, write = SetDialog };
  __property Color = { default = clWindow };
  __property String OrderBy = { read = FOrderBy,write = FOrderBy };
};

class PACKAGE TNNVDBGrid : public TDBGrid {
private:
  using inherited = TDBGrid;
  bool fAutoFieldSearch;
  bool fForceFocusRect;

  TNotifyEvent FOnDBCut   = nullptr;
  TNotifyEvent FOnDBCopy  = nullptr;
  TNotifyEvent FOnDBPaste = nullptr;
  TNotifyEvent FOnDBMerge = nullptr;

  NNV::TDSetBookmarks fDSetBookmarks;

  TRect fCWRect;

  int __fastcall GetVisibleCount();
  TNNVQuery* __fastcall GetQuery();

protected:
  virtual void __fastcall DoDBCut();
  virtual void __fastcall DoDBCopy();
  virtual void __fastcall DoDBPaste();
  virtual void __fastcall DoDBMerge();

  DYNAMIC void __fastcall ColEnter();
  DYNAMIC void __fastcall KeyDown( Word &Key, TShiftState Shift );
  DYNAMIC TDBGridColumns* __fastcall CreateColumns();
  DYNAMIC void __fastcall DrawColumnCell( const Types::TRect &Rect
                                        , int DataCol
                                        , TColumn* Column
                                        , Grids::TGridDrawState State );
  virtual void __fastcall Notification( TComponent *AComponent, TOperation Operation );

public:
  __fastcall TNNVDBGrid( TComponent* Owner );
  void __fastcall DBCut();
  void __fastcall DBCopy();
  void __fastcall DBPaste();
  void __fastcall DBMerge();
  void __fastcall ClearAll();
  void __fastcall SaveToFiler( TNNVTextStream *Filer );
  void __fastcall LoadFromFiler( TNNVTextStream *Filer );
  void __fastcall CWSelect( TField *AFieldPK
                          , NNV::TBufferIntBox *ABufferIntBox
                          , bool AIsCut );
  void __fastcall CWCheckSelect();
  void __fastcall SetFieldSearchName();
  TColumn* __fastcall CWFindColumn( TField *Field_ );
  TColumn* __fastcall FieldNameToColumn( const String &S );
  bool __fastcall IsCurrentSelected();
  void __fastcall CWSelectAll();
  void __fastcall CWFieldResize( TField *f, int WidthAdd );
  void __fastcall SetComboItems( TCustomCombo *cc, TField *f );
  void __fastcall ShowPropertyDialog();
  void __fastcall SelectRows( NNV::TSelectedFunction ASelectedFunction );
  __property TRect CWRect = {read = fCWRect};
  __property TNNVQuery* Query = { read = GetQuery };

__published:
  __property bool AutoFieldSearch = { read = fAutoFieldSearch, write = fAutoFieldSearch, default = true };
  __property bool ForceFocusRect = { read = fForceFocusRect, write = fForceFocusRect, default = true };
  __property int VisibleCount = { read = GetVisibleCount };
  __property TNotifyEvent OnDBCut = { read = FOnDBCut, write = FOnDBCut };
  __property TNotifyEvent OnDBCopy = { read = FOnDBCopy, write = FOnDBCopy };
  __property TNotifyEvent OnDBPaste = { read = FOnDBPaste, write = FOnDBPaste };
  __property TNotifyEvent OnDBMerge = { read = FOnDBMerge, write = FOnDBMerge };

  __property OnResize;
};

class PACKAGE TNNVDBSearchDialog : public TComponent
{
private:
  using inherited = TComponent;
  TDataSource *fDataSource;
  bool FGoStart;
  bool FReset;
  bool FWorking;
  bool FIsExecute = false;
  bool fUseHide = true;
  int FLimitHistory;
  TNotifyEvent FOnExecute;
  bool FIsSaveOptions = false;
  TScrollBox *FQuickScrollBox = nullptr;

  void __fastcall SetQuickScrollBox( TScrollBox *Value );
  void __fastcall SetOptions( TField *AFieldSearch, TScrollBox *AScrollBox );
  void __fastcall SaveOptions();
  void __fastcall PrepareSkip( bool AIsQuick );
  bool __fastcall CheckActive();
  void __fastcall SearchSkipNext();
  void __fastcall SearchSkipFilter();
  TNNVQuery* __fastcall GetQuery();
  void __fastcall NewLabelCombo( int &TopSkip
                               , TField *ASearchField
                               , int &NS
                               , const int AWidthComboBox
                               , TScrollBox *AScrollBox
                               , const String &APrefixLabel );
  void __fastcall SetDataSource(TDataSource *Value);
  void __fastcall PrepareBoolComboBox( TComboBox *cb );
  void __fastcall ForPrepareSearch( TScrollBox *AScrollBox );
  void __fastcall PrepareSearch( TObject *Sender );
  void __fastcall UnPrepareSearch( TObject *Sender );
  bool __fastcall CompareRecord( TNNVQuery *qu, NNV::TMapSearch::TVectorSearch::iterator i );
  void __fastcall SetSearchValueToControl( TControl *TempControl, NNV::TMapSearch::iterator I );
  void __fastcall DialogFilter( TDataSet* ADataSet, bool &Accept );
protected:
  virtual void __fastcall Notification( TComponent *AComponent, TOperation Operation );
  __property bool IsSaveOptions = { read = FIsSaveOptions, write = FIsSaveOptions };
public:
  __fastcall TNNVDBSearchDialog( TComponent* Owner );
  __fastcall ~TNNVDBSearchDialog();
  virtual void __fastcall DoExecute();
  void __fastcall ResetSearch();
  void __fastcall SearchNext();
  void __fastcall SearchFilter();
  void __fastcall Execute( TComponent *SenderForm );
  void __fastcall ExecuteQuick();
  void __fastcall ExecuteSearch( TObject *Sender );
  void __fastcall LoadFromFiler( TNNVTextStream *Filer );
  void __fastcall SaveToFiler( TNNVTextStream *Filer );
  bool __fastcall IsFilterPresent();
  __property TNNVQuery* Query = { read = GetQuery };
  __property bool IsExecute = { read = FIsExecute, write = FIsExecute };

__published:
  __property TDataSource *DataSource = { read = fDataSource, write = SetDataSource };
  __property int LimitHistory = { read = FLimitHistory, write = FLimitHistory, default = 30 };
  __property bool UseHide = { read = fUseHide, write = fUseHide, default = true };
  __property TScrollBox QuickScrollBox = { read = FQuickScrollBox, write = SetQuickScrollBox };
  __property TNotifyEvent OnExecute = { read = FOnExecute, write = FOnExecute };
};

namespace NNV {

class PACKAGE TStoryInfo {
public:
  Variant Value;

  TStoryInfo();
  TStoryInfo( const Variant &aValue );
};

using TStoryMap = PACKAGE std::map< TField*, TStoryInfo >;
using TSettingSet = PACKAGE std::set< TField* >;
using TRightFieldMap = PACKAGE std::map< TField*, bool >;

using TDoInsertLanguageRow = PACKAGE void __fastcall( __closure * )( const String &ALanguageStringID, String &ATranslate, bool &ATranslateSet );
using TDoPrepareOwner      = PACKAGE void __fastcall( __closure * )( const String &AOwnerString );

}

class PACKAGE TNNVStoryData : public TComponent {
private:
  using inherited = TComponent;
  NNV::TStoryMap StoryMap;
  TNNVQuery* FQuery = nullptr;
  TNNVQuery* FSettingQuery = nullptr;
  NNV::TSettingSet SettingSet;
  TBookmarkList *BookmarkList;
  bool fUseHide = false;
  TDataSource *FDataSource;
  void __fastcall FillFieldList();
  void __fastcall SetStoryData( TObject *Sender );
  void __fastcall SaveSetting();
  bool __fastcall FieldValid( TField *f );
  void __fastcall SetFieldsValue( TCheckListBox *cl, TNNVQuery *qu );
  void __fastcall RowInspectorExecute( TObject *Sender );
  void __fastcall PrepareScrollBox( TScrollBox *AScrollBox );
  void __fastcall NewLabelCombo( int &TopSkip
                               , TField *ASearchField
                               , int &NS
                               , const int AWidthComboBox
                               , TScrollBox *AScrollBox
                               , const String &APrefixLabel
                               , const String &APrefixField );
  void __fastcall SetOptions( TField *AFieldSearch, TScrollBox *AScrollBox );
  void __fastcall SetDataSource( TDataSource *Value );
protected:
  __property TNNVQuery* Query = { read = FQuery, write = FQuery };
  __property TNNVQuery* SettingQuery = { read = FSettingQuery, write = FSettingQuery };
  __property TDataSource *DataSource = { read = FDataSource, write = SetDataSource };
public:
  __fastcall TNNVStoryData( TComponent* Owner );
  NNV::TRightFieldMap RightFieldMap;
  NNV::TSettingSet ExcludeSet;
  void __fastcall RememberData( TNNVQuery *AQuery );
  void __fastcall Execute( TForm *ASenderForm
                         , TNNVQuery *AQuery
                         , TDBGrid *ADBGrid );
  void __fastcall ExecuteRowInspector( TForm *ASenderForm
                                     , TDataSource *ADataSource );
__published:
  __property bool UseHide = { read = fUseHide, write = fUseHide, default = false };
};

class PACKAGE TNNVConfig : public TComponent {
private:
  using inherited = TComponent;
  TNotifyEvent FOnLoad;
  TNotifyEvent FOnSave;
  TNotifyEvent FOnDefault;
  TNotifyEvent FOnBeginLoad;
  TNotifyEvent FOnEndLoad;
  TNotifyEvent FOnBeginSave;
  TNotifyEvent FOnEndSave;
  TNNVGetFiler FOnGetFiler;
  char fVersion;
  TNNVStoreKind fStoreKind = skDB;
  TNNVTextStream *fFiler = nullptr;
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
  void __fastcall PrepareQuerySQL( TNNVQuery *quReg, const String &UserRegKey );
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
  __fastcall TNNVConfig( TComponent* Owner );
  __property TNNVTextStream *Filer = { read = fFiler };
  String __fastcall RegistryKey();
  void __fastcall Load();
  void __fastcall Save();

__published:
  __property TNNVStoreKind StoreKind = { read = fStoreKind, write = fStoreKind, default = skDB };
  __property char Version = { read = fVersion, write = fVersion, default = char() };
  __property bool Enabled = { read = fEnabled, write = fEnabled, default = true };
  __property TNotifyEvent OnLoad = { read = FOnLoad, write = FOnLoad };
  __property TNotifyEvent OnSave = { read = FOnSave, write = FOnSave };
  __property TNotifyEvent OnDefault = { read = FOnDefault, write = FOnDefault };
  __property TNotifyEvent OnBeginLoad = { read = FOnBeginLoad, write = FOnBeginLoad };
  __property TNotifyEvent OnEndLoad = { read = FOnEndLoad, write = FOnEndLoad };
  __property TNotifyEvent OnBeginSave = { read = FOnBeginSave, write = FOnBeginSave };
  __property TNotifyEvent OnEndSave = { read = FOnEndSave, write = FOnEndSave };
  __property TNNVGetFiler OnGetFiler = { read = FOnGetFiler, write = FOnGetFiler };
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

namespace NNV
{

using TDoLogin = PACKAGE void __fastcall( __closure * )( System::TObject* Sender, TFDConnection *AConnection );

}

#endif

