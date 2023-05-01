// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFmDB.h"
#include "VCL_NNDmNewNavadvipa.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNFlagBox"
#pragma link "VCL_NNFmRes"
#pragma link "VCL_NNRightsManager"
#pragma link "VCL_NNPanel"
#pragma link "VCL_NNPageControl"
#pragma link "VCL_NNActionList"
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNDateTimeDialog"
#pragma link "VCL_NNDialogExec"
#pragma link "VCL_NNLanguageManager"
#pragma resource "*.dfm"
TfmvDB *fmvDB;

// ---------------------------------------------------------------------------
__fastcall TfmvDB::TfmvDB( TComponent* Owner )
  : inherited( Owner )
{
}
// ---------------------------------------------------------------------------

void __fastcall TfmvDB::Loaded()
{
  inherited::Loaded();

  if ( NNV::DMExists( __classid( TdmvNewNavadvipa ), &dmvNewNavadvipa ) ) {
    tbrDB->Images     = dmvNewNavadvipa->ilDB;
    pcDB->Images      = dmvNewNavadvipa->ilDB;
    tbrDBTree->Images = dmvNewNavadvipa->ilDB;
    tbrSetup->Images  = dmvNewNavadvipa->ilDB;
    tbrStatus->Images = dmvNewNavadvipa->ilDB;
  }
}

void __fastcall TfmvDB::SetCurrentDBGrid( TNNVDBGrid *Value )
{
  if ( FCurrentDBGrid != Value ) {
    FCurrentDBGrid = Value;

    bool B = CurrentDBGrid != nullptr;
    aDBGridProperty->Enabled = B;
    if ( B ) {
      aDBCut->Enabled   = CurrentDBGrid->OnDBCut   != nullptr;
      aDBCopy->Enabled  = CurrentDBGrid->OnDBCopy  != nullptr;
      aDBPaste->Enabled = CurrentDBGrid->OnDBPaste != nullptr;
      aDBMerge->Enabled = CurrentDBGrid->OnDBMerge != nullptr;
    }
  }

  if ( CurrentDBGrid ) {
    CurrentDBGrid->Refresh();
    CurrentDBGrid->SetFieldSearchName();

    if ( CurrentDBGrid->DataSource )
      DataSource = CurrentDBGrid->DataSource;

    if ( CurrentDBGrid->DataSource->DataSet )
      DataSet = CurrentDBGrid->DataSource->DataSet;
  }
}

void __fastcall TfmvDB::SetCurrentDBTreeView( TNNVDBTreeView *Value )
{
  if ( FCurrentDBTreeView != Value )
    FCurrentDBTreeView = Value;

  if ( CurrentDBTreeView && CurrentDBTreeView->NodeAdmin && CurrentDBTreeView->NodeAdmin->DataSource ) {
    DataSet    = CurrentDBTreeView->NodeAdmin->DataSource->DataSet;
    DataSource = CurrentDBTreeView->NodeAdmin->DataSource;
  }
}

void __fastcall TfmvDB::aDBGridPropertyExecute( TObject *Sender )
{
  if ( CurrentDBGrid )
    CurrentDBGrid->ShowPropertyDialog();
}
// ---------------------------------------------------------------------------

void __fastcall TfmvDB::DBGridEnter( TObject *Sender )
{
  CurrentDBGrid = dynamic_cast< TNNVDBGrid* >( Sender );
}
// ---------------------------------------------------------------------------

void __fastcall TfmvDB::DBGridDblClick( TObject *Sender )
{
  CloseDialog( true );
}

void __fastcall TfmvDB::DBGridTitleClick( TColumn *Column )
{
  TCustomDBGrid *dg = Column->Grid;
  TDataSource *ds = dynamic_cast< TDataSource* >( dg->DataSource );

  if ( !ds )
    return;

  TNNVQuery *qu = dynamic_cast< TNNVQuery* >( ds->DataSet );

  if ( !qu )
    return;

  qu->OrderByColumn = Column;
}

void __fastcall TfmvDB::DBTreeViewEnter( TObject *Sender )
{
  CurrentDBTreeView = dynamic_cast< TNNVDBTreeView* >( Sender );
}
//---------------------------------------------------------------------------

TNNVQuery* __fastcall TfmvDB::GetQuery()
{
  return dynamic_cast< TNNVQuery* >( dsData->DataSet );
}

void __fastcall TfmvDB::SetDataSource( TDataSource *Value )
{
  if ( FDataSource != Value ) {
    FDataSource = Value;

    bool B = DataSource->AutoEdit;
    aDBAutoEdit->Checked   = B;
    tbDBAutoEdit->Down     = B;
    miDBAutoEdit->Checked  = B;
    mipDBAutoEdit->Checked = B;
  }
}

void __fastcall TfmvDB::SetDataSet( TDataSet *Value )
{
  if ( dsData->DataSet != Value ) {
    dsData->DataSet = Value;

    NNV::ClearScrollBox( sbQuickSearch );
    SyncFilterSearch();
    SyncCachedUpdates();
    aDBSearchVectorClear->Enabled = Value != nullptr;
  }
}

void __fastcall TfmvDB::aDBCutExecute( TObject *Sender )
{
  TWinControl *C = ActiveControl;
  if ( CurrentDBGrid && CurrentDBGrid == C )
    CurrentDBGrid->DBCut();
  else if ( CurrentDBTreeView && CurrentDBTreeView == C )
    CurrentDBTreeView->CutNode();
}

void __fastcall TfmvDB::aDBCopyExecute( TObject *Sender )
{
  if ( CurrentDBGrid )
    CurrentDBGrid->DBCopy();
}

void __fastcall TfmvDB::aDBPasteExecute( TObject *Sender )
{
  TWinControl *C = ActiveControl;
  if ( CurrentDBGrid && CurrentDBGrid == C )
    CurrentDBGrid->DBPaste();
  else if ( CurrentDBTreeView && CurrentDBTreeView == C )
    CurrentDBTreeView->PasteNode( CurrentDBTreeView->Selected );
}

void __fastcall TfmvDB::aDBMergeExecute( TObject *Sender )
{
  if ( CurrentDBGrid )
    CurrentDBGrid->DBMerge();
}

void __fastcall TfmvDB::aDBCachedUpdatesExecute( TObject *Sender )
{
  TNNVQuery *qu = Query;
  if ( qu )
    qu->CachedUpdates = !qu->CachedUpdates;
  SyncCachedUpdates();
}

void __fastcall TfmvDB::SyncFilterSearch()
{
  aEraseFilterSearch->ImageIndex = sdDB->IsFilterPresent() ? (int)NNV::TImagesKind::imRedLamp : (int)NNV::TImagesKind::imGreenLamp;
}

void __fastcall TfmvDB::SyncCachedUpdates()
{
  TNNVQuery *qu = Query;
  aDBCachedUpdates->Enabled = qu != nullptr;
  if ( qu ) {
    aDBCachedUpdates->Checked   = qu->CachedUpdates;
    tbDBCachedUpdates->Down     = qu->CachedUpdates;
    miDBCachedUpdates->Checked  = qu->CachedUpdates;
    mipDBCachedUpdates->Checked = qu->CachedUpdates;
  }
}

void __fastcall TfmvDB::aDBAutoEditExecute( TObject *Sender )
{
  if ( DataSource )
    DataSource->AutoEdit = !DataSource->AutoEdit;
}

void __fastcall TfmvDB::aRemeberRowExecute( TObject *Sender )
{
  dmvNewNavadvipa->sdDB->RememberData( Query );
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aStoreDataExecute( TObject *Sender )
{
  dmvNewNavadvipa->sdDB->Execute( this
                                , Query
                                , CurrentDBGrid );
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aTVNodeAdminReloadExecute( TObject *Sender )
{
  if ( CurrentDBTreeView )
    CurrentDBTreeView->CWReload( CurrentDBTreeView->NodeAdmin );
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aDBTreeViewReloadExecute( TObject *Sender )
{
  if ( CurrentDBTreeView )
    CurrentDBTreeView->CWRefresh();
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aDBTreeViewNodeActualInvertExecute( TObject *Sender )
{
  if ( CurrentDBTreeView )
    CurrentDBTreeView->NodeAdmin->DoInvertActual();
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aDBTreeViewActualOnlyExecute( TObject *Sender )
{
  if ( CurrentDBTreeView && CurrentDBTreeView->NodeAdmin ) {

    CurrentDBTreeView->NodeAdmin->ActualOnly = !CurrentDBTreeView->NodeAdmin->ActualOnly;
    aDBTreeViewActualOnly->Checked = CurrentDBTreeView->NodeAdmin->ActualOnly;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::DBTreeViewNodeAdminChange( TObject *Sender, TNNVNodeAdmin *NodeAdmin )
{
  aTVNodeAdminReload->Enabled          = NodeAdmin->ReloadEnabled;
  aDBTreeViewNodeActualInvert->Enabled = NodeAdmin->ActualOnlyNeed;
  aDBTreeViewActualOnly->Enabled       = aDBTreeViewNodeActualInvert->Enabled;
  aDBTreeViewActualOnly->Checked       = NodeAdmin->ActualOnly;
  aDBTreeViewEndToEndViewing->Enabled  = NodeAdmin->EndToEndViewingNeed;
  aDBTreeViewEndToEndViewing->Checked  = NodeAdmin->EndToEndViewing;
  aTVNodeAdminPrint->Enabled           = NodeAdmin->OnPrint != nullptr;
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aTVNodeAdminPrintExecute( TObject *Sender )
{
  if ( CurrentDBTreeView && CurrentDBTreeView->NodeAdmin )
    CurrentDBTreeView->NodeAdmin->DoPrint();
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aDBTreeViewEndToEndViewingExecute( TObject *Sender )
{
  if ( CurrentDBTreeView && CurrentDBTreeView->NodeAdmin ) {

    CurrentDBTreeView->NodeAdmin->EndToEndViewing = !CurrentDBTreeView->NodeAdmin->EndToEndViewing;
    aDBTreeViewEndToEndViewing->Checked = CurrentDBTreeView->NodeAdmin->EndToEndViewing;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::SyncEnterKind()
{
  cbEnterKind->ItemIndex = (int)EnterKind;
}

void __fastcall TfmvDB::SyncDialogInit()
{
  aClearCase->Enabled = DialogMode;
}

void __fastcall TfmvDB::cbEnterKindChange( TObject *Sender )
{
  EnterKind = ( NNV::TEnterKind )cbEnterKind->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::DBGridKeyDown( TObject *Sender, WORD &Key, TShiftState Shift )
{
  if ( Key == vkSpace ) {
    if ( !Query->UpdateOptions->ReadOnly ) {
      TField *f = CurrentDBGrid->SelectedField;
      if ( f->DataType == ftBoolean ) {
        Query->CWCheckEditMode();
        f->AsBoolean = !f->AsBoolean;
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::DBGridEditButtonClick( TObject *Sender )
{
  TField *f = CurrentDBGrid->SelectedField;
  TRect R = CurrentDBGrid->CWRect;

  FDBGridEditButtonClickOK = false;
  if ( f->DataType == ftDate || f->DataType == ftTimeStamp ) {
    ddDB->NeedTime = f->DataType == ftTimeStamp;
    ddDB->Execute( R, this );
    FDBGridEditButtonClickOK = true;
  } else {
    TNNVGridColumn *cl = (TNNVGridColumn*)( CurrentDBGrid->Columns->Items[ CurrentDBGrid->SelectedIndex ] );
    if ( cl && cl->Dialog ) {
      cl->Dialog->Execute( R, this );;
      FDBGridEditButtonClickOK = true;
    }
  }
}

void __fastcall TfmvDB::coResLoad( TObject *Sender )
{
  inherited::coResLoad( Sender );
  pcDB->LoadFromFiler( coRes->Filer );
  mmDB->AutoMerge = coRes->Filer->ReadBool();
  sdDB->LoadFromFiler( coRes->Filer );
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::coResSave( TObject *Sender )
{
  inherited::coResSave( Sender );
  pcDB->SaveToFiler( coRes->Filer );
  coRes->Filer->WriteBool( mmDB->AutoMerge );
  sdDB->SaveToFiler( coRes->Filer );
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::FormCreate( TObject *Sender )
{
  inherited::FormCreate( Sender );
  SyncProperty();
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::SyncProperty()
{
  SyncEnterKind();
}
//---------------------------------------------------------------------------


void __fastcall TfmvDB::aAutoMergeMainMenuExecute( TObject *Sender )
{
  mmDB->AutoMerge = !mmDB->AutoMerge;
  aAutoMergeMainMenu->Checked  = mmDB->AutoMerge;
  miAutoMergeMainMenu->Checked = mmDB->AutoMerge;
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aDBSearchExecute( TObject *Sender )
{
  sdDB->Execute( this );
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aDBSearchNextExecute( TObject *Sender )
{
  sdDB->SearchNext();
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aDBSearchResetExecute( TObject *Sender )
{
  sdDB->ResetSearch();
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aEraseFilterSearchExecute( TObject *Sender )
{
  TNNVQuery *qu = Query;
  if ( qu ) {
    qu->FilterMap.EraseFilterSearch();
    sdDB->DoExecute();
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aDBTreeNodePrevExecute( TObject *Sender )
{
  if ( CurrentDBTreeView )
    CurrentDBTreeView->NavTree.Prev();
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aDBTreeNodeNextExecute( TObject *Sender )
{
  if ( CurrentDBTreeView )
    CurrentDBTreeView->NavTree.Next();
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aDBTreeNodePrevUpdate(TObject *Sender)
{
  if ( CurrentDBTreeView )
    aDBTreeNodePrev->Enabled = !CurrentDBTreeView->NavTree.Bof();
  else
    aDBTreeNodePrev->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aDBTreeNodeNextUpdate(TObject *Sender)
{
  if ( CurrentDBTreeView )
    aDBTreeNodeNext->Enabled = !CurrentDBTreeView->NavTree.Eof();
  else
    aDBTreeNodeNext->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::ddDBPrepare( TObject *Sender )
{
  TField *f = CurrentDBGrid->SelectedField;
  if ( f->IsNull )
    ddDB->DateTime = Now();
  else
    ddDB->DateTime = f->AsDateTime;
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::ddDBExecute( TObject *Sender )
{
  Query->CWCheckEditMode();
  TField *f = CurrentDBGrid->SelectedField;
  if ( !f->ReadOnly )
    f->AsDateTime = ddDB->DateTime;
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::dsDataDataChange( TObject *Sender, TField *Field )
{
  TDataSet *ds = DataSet;
  if ( ds ) {
    edDBStatus->Text = NNV::DataSetStateToStr( dsData->State ) + NNVConst::Space +
                       String( ds->RecNo ) + NNVConst::AltDelimeter +
                       String( ds->RecordCount );
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aDBSelectAllExecute( TObject *Sender )
{
  if ( CurrentDBGrid )
    CurrentDBGrid->CWSelectAll();
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::KeyDownDialog( TObject *Sender, WORD &Key, TShiftState Shift )
{
  QuickSearchKeyDown( Sender, Key, Shift );

  if ( Key == 0 )
    return;

  if ( EnterKind == NNV::TEnterKind::Down && Key == vkReturn )
    Key = vkDown;

  switch ( Key ) {
  case vkEscape :
    if ( DataSet != NULL && NNV::IsEditModes( DataSet->State ) ) DataSet->Cancel();
    else {
      TCustomCombo *cc = dynamic_cast< TCustomCombo* >( ActiveControl );
      if ( cc && cc->DroppedDown )
        cc->DroppedDown = false;
      else
        CloseDialog( false );
    }
    Key = 0;
    break;
  case vkReturn :
    if ( EnterKind == NNV::TEnterKind::Like || Shift.Contains( ssShift ) ) {
      if ( NNV::IsEditModes( DataSet->State ) )
        DataSet->Post();
      else {
        TCustomCombo *cc = dynamic_cast< TCustomCombo* >( ActiveControl );
        if ( cc && cc->DroppedDown )
          cc->DroppedDown = false;
        else
          CloseDialog( true );
      }
      Key = 0;
    }
    break;
  }

  if ( Key )
    FormKeyDown( Sender, Key, Shift );
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aDBQuickSearchExecute(TObject *Sender)
{
  IsQuickSearch = true;
  sdDB->ExecuteQuick();
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::QuickSearchKeyDown( TObject *Sender, WORD &Key, TShiftState Shift )
{
  switch ( Key ) {
  case vkReturn :
    if ( IsQuickSearch ) {
      sdDB->ExecuteSearch( nullptr );
      Key = 0;
    }
    break;
  case vkEscape :
    if ( IsQuickSearch && LastActive ) {
      LastActive->SetFocus();
      Key = 0;
    }
    break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::FormKeyDown( TObject *Sender, WORD &Key, TShiftState Shift )
{
  QuickSearchKeyDown( Sender, Key, Shift );
  if ( Key )
    inherited::FormKeyDown( Sender, Key, Shift );
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aDBSearchVectorClearExecute(TObject *Sender)
{
  sdDB->Query->ClearVectorSearch();
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::sdDBExecute( TObject *Sender )
{
  SyncFilterSearch();
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::sbQuickSearchEnter(TObject *Sender)
{
  IsQuickSearch = true;
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::sbQuickSearchExit( TObject *Sender )
{
  IsQuickSearch = false;
}
//---------------------------------------------------------------------------

void __fastcall TfmvDB::aRowInspectorExecute( TObject *Sender )
{
  dmvNewNavadvipa->sdDB->ExecuteRowInspector( this, DataSource );
}
//---------------------------------------------------------------------------

