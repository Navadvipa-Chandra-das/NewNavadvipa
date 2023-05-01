// ---------------------------------------------------------------------------

#ifndef VCL_NNFmDBH
#define VCL_NNFmDBH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VCL_NNFlagBox.h"
#include "VCL_NNFmRes.h"
#include "VCL_NNRightsManager.h"
#include "VCL_NNPanel.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.DBCtrls.hpp>
#include "VCL_NNPageControl.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include "VCL_NNActionList.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Data.DB.hpp>
#include "VCL_NNDBMiracle.h"
#include <Vcl.Menus.hpp>
#include "VCL_NNDateTimeDialog.h"
#include "VCL_NNDialogExec.h"
#include <Vcl.Mask.hpp>
#include "VCL_NNLanguageManager.h"

// ---------------------------------------------------------------------------
class TfmvDB : public TfmvRes {
__published: // IDE-managed Components
  TNNVPanel *paT;
  TNNVPageControl *pcDB;
  TTabSheet *tsDB;
  TNNVPanel *paTL;
  TToolBar *tbrDB;
  TDBNavigator *dbngDB;
  TAction *aDBGridProperty;
  TToolBar *tbrDBTree;
  TAction *aDBCut;
  TAction *aDBCopy;
  TAction *aDBPaste;
  TAction *aDBMerge;
  TAction *aDBCachedUpdates;
  TDataSource *dsData;
  TAction *aDBAutoEdit;
  TToolButton *tbDBAutoEdit;
  TAction *aRemeberRow;
  TAction *aStoreData;
  TToolButton *tbDBCut;
  TToolButton *tbDBCopy;
  TToolButton *tbDBPaste;
  TToolButton *tbDBMerge;
  TToolButton *tbDBCachedUpdates;
  TToolButton *tbRemeberRow;
  TToolButton *tbStoreData;
  TAction *aTVNodeAdminReload;
  TToolButton *tbTVNodeAdminReload;
  TTabSheet *tsSetup;
  TToolBar *tbrSetup;
  TToolButton *tbActionListSetup;
  TAction *aDBTreeViewReload;
  TToolButton *tbDBTreeViewReload;
  TAction *aDBTreeViewNodeActualInvert;
  TToolButton *tbDBTreeNodeActualInvert;
  TAction *aDBTreeViewActualOnly;
  TToolButton *tbDBTreeViewActualOnly;
  TAction *aTVNodeAdminPrint;
  TAction *aDBTreeViewEndToEndViewing;
  TToolButton *tbDBTreeViewEndToEndViewing;
  TComboBox *cbEnterKind;
  TMainMenu *mmDB;
  TMenuItem *miDB;
  TMenuItem *miDBProperty;
  TAction *aAutoMergeMainMenu;
  TToolButton *tbDBGridProperty;
  TMenuItem *miDBAutoEdit;
  TMenuItem *miDBCut;
  TMenuItem *miDBCopy;
  TMenuItem *miDBPaste;
  TMenuItem *miDBMerge;
  TMenuItem *miDBCachedUpdates;
  TMenuItem *miRemeberRow;
  TMenuItem *miStoreData;
  TMenuItem *miTVNodeAdminReload;
  TMenuItem *miDBTreeViewReload;
  TMenuItem *miDBTreeViewNodeActualInvert;
  TMenuItem *miDBTreeViewActualOnly;
  TMenuItem *miDBTreeViewEndToEndViewing;
  TMenuItem *miActionListSetup;
  TMenuItem *miDBGridProperty;
  TMenuItem *miAutoMergeMainMenu;
  TToolButton *tbAutoMergeMainMenu;
  TAction *aDBSearch;
  TAction *aDBSearchNext;
  TAction *aDBSearchReset;
  TToolButton *tbDBSearch;
  TToolButton *tbDBSearchNext;
  TToolButton *tbDBSearchReset;
  TMenuItem *miDBSearch;
  TMenuItem *miDBSearchNext;
  TMenuItem *miDBSearchReset;
  TMenuItem *miSearchEdit;
  TNNVDBSearchDialog *sdDB;
  TNNVPanel *paStatus;
  TEdit *edDBStatus;
  TAction *aEraseFilterSearch;
  TAction *aDBTreeNodePrev;
  TAction *aDBTreeNodeNext;
  TToolButton *tbDBTreeNodePrev;
  TToolButton *tbDBTreeNodeNext;
  TToolButton *tbRelease;
  TNNVDateTimeDialog *ddDB;
  TMenuItem *miRelease;
  TDBEdit *deKindID;
  TPopupMenu *pmDBGrid;
  TMenuItem *mipDBCut;
  TMenuItem *mipDBCopy;
  TMenuItem *mipDBPaste;
  TMenuItem *mipDBMerge;
  TMenuItem *mipDBGridSeparator;
  TMenuItem *mipDBAutoEdit;
  TMenuItem *mipDBCachedUpdates;
  TMenuItem *mipRemeberRow;
  TMenuItem *mipStoreData;
  TAction *aDBSelectAll;
  TToolButton *tbDBSelectAll;
  TMenuItem *mipDBSelectAll;
  TMenuItem *miDBSelectAll;
  TMenuItem *mipDBGridProperty;
  TToolButton *tbClearCase;
  TMenuItem *miClearCase;
  TPopupMenu *pmDBTreeView;
  TMenuItem *mitDBCut;
  TMenuItem *mitDBPaste;
  TScrollBox *sbQuickSearch;
  TAction *aDBQuickSearch;
  TToolBar *tbrStatus;
  TToolButton *tbEraseFilterSearch;
  TToolButton *tbDBQuickSearch;
  TAction *aDBSearchVectorClear;
  TToolButton *tbDBSearchVectorClear;
  TMenuItem *miEraseFilterSearch;
  TAction *aRowInspector;
  TToolButton *tbRowInspector;
  TMenuItem *mipRowInspector;
  TMenuItem *miRowInspector;
  TToolButton *tbPrepareLanguage;
  TMenuItem *miPrepareLanguage;
  void __fastcall DBGridEnter( TObject *Sender );
  void __fastcall DBGridDblClick( TObject *Sender );
  void __fastcall DBGridTitleClick( TColumn *Column );
  void __fastcall DBTreeViewEnter( TObject *Sender );
  void __fastcall aDBGridPropertyExecute( TObject *Sender );
  void __fastcall aDBCutExecute( TObject *Sender );
  void __fastcall aDBCopyExecute( TObject *Sender );
  void __fastcall aDBPasteExecute( TObject *Sender );
  void __fastcall aDBMergeExecute( TObject *Sender );
  void __fastcall aDBCachedUpdatesExecute( TObject *Sender );
  void __fastcall aDBAutoEditExecute( TObject *Sender );
  void __fastcall aRemeberRowExecute( TObject *Sender );
  void __fastcall aStoreDataExecute( TObject *Sender );
  void __fastcall aTVNodeAdminReloadExecute( TObject *Sender );
  void __fastcall aDBTreeViewReloadExecute( TObject *Sender );
  void __fastcall aDBTreeViewNodeActualInvertExecute( TObject *Sender );
  void __fastcall aDBTreeViewActualOnlyExecute( TObject *Sender );
  void __fastcall DBTreeViewNodeAdminChange( TObject *Sender, TNNVNodeAdmin *NodeAdmin );
  void __fastcall aTVNodeAdminPrintExecute( TObject *Sender );
  void __fastcall aDBTreeViewEndToEndViewingExecute( TObject *Sender );
  void __fastcall cbEnterKindChange( TObject *Sender );
  void __fastcall DBGridKeyDown( TObject *Sender, WORD &Key, TShiftState Shift );
  void __fastcall KeyDownDialog( TObject *Sender, WORD &Key, TShiftState Shift );
  void __fastcall DBGridEditButtonClick( TObject *Sender );
  void __fastcall coResLoad( TObject *Sender );
  void __fastcall coResSave( TObject *Sender );
  void __fastcall FormCreate( TObject *Sender );
  void __fastcall aAutoMergeMainMenuExecute( TObject *Sender );
  void __fastcall aDBSearchExecute( TObject *Sender );
  void __fastcall aDBSearchNextExecute( TObject *Sender );
  void __fastcall aDBSearchResetExecute( TObject *Sender );
  void __fastcall aEraseFilterSearchExecute( TObject *Sender );
  void __fastcall aDBTreeNodePrevExecute( TObject *Sender );
  void __fastcall aDBTreeNodeNextExecute( TObject *Sender );
  void __fastcall aDBTreeNodePrevUpdate( TObject *Sender );
  void __fastcall aDBTreeNodeNextUpdate( TObject *Sender );
  void __fastcall ddDBPrepare( TObject *Sender );
  void __fastcall ddDBExecute( TObject *Sender );
  void __fastcall dsDataDataChange( TObject *Sender, TField *Field );
  void __fastcall aDBSelectAllExecute( TObject *Sender );
  void __fastcall aDBQuickSearchExecute( TObject *Sender );
  void __fastcall FormKeyDown( TObject *Sender, WORD &Key, TShiftState Shift );
  void __fastcall sbQuickSearchExit( TObject *Sender );
  void __fastcall aDBSearchVectorClearExecute(TObject *Sender);
  void __fastcall sdDBExecute( TObject *Sender );
  void __fastcall sbQuickSearchEnter(TObject *Sender);
  void __fastcall aRowInspectorExecute(TObject *Sender);
private: // User declarations
  using inherited = TfmvRes;
  TNNVDBGrid *FCurrentDBGrid = nullptr;
  TNNVDBTreeView *FCurrentDBTreeView = nullptr;
  TDataSource *FDataSource = nullptr;
  bool FDBGridEditButtonClickOK;
  void __fastcall SetDataSource( TDataSource *Value );
  TDataSet* __fastcall GetDataSet() { return dsData->DataSet; };
  void __fastcall SetDataSet( TDataSet *Value );
  TNNVQuery* __fastcall GetQuery();
  void __fastcall SetCurrentDBGrid( TNNVDBGrid *Value );
  void __fastcall SetCurrentDBTreeView( TNNVDBTreeView *Value );
  void __fastcall SyncCachedUpdates();
  void __fastcall SyncFilterSearch();
  void __fastcall SyncProperty();
protected:
  virtual void __fastcall Loaded();
  virtual void __fastcall SyncEnterKind();
  virtual void __fastcall SyncDialogInit();
public: // User declarations
  __fastcall TfmvDB( TComponent* Owner );
  void __fastcall QuickSearchKeyDown( TObject *Sender, WORD &Key, TShiftState Shift );
  __property TDataSource *DataSource = { read = FDataSource, write = SetDataSource };
  __property TDataSet *DataSet = { read = GetDataSet, write = SetDataSet };
  __property TNNVQuery* *Query = { read = GetQuery };
  __property TNNVDBGrid *CurrentDBGrid = { read = FCurrentDBGrid, write = SetCurrentDBGrid };
  __property TNNVDBTreeView *CurrentDBTreeView = { read = FCurrentDBTreeView, write = SetCurrentDBTreeView };
};

// ---------------------------------------------------------------------------
extern PACKAGE TfmvDB *fmvDB;
// ---------------------------------------------------------------------------
#endif

