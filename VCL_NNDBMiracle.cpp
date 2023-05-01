// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <vcl.h>
#pragma hdrstop
#include "VCL_NNDBMiracle.h"
#include "VCL_NNStrUtil.h"
#include "VCL_NNFmSearch.h"
#include "VCL_NNFmDBGrid.h"
#include "VCL_NNFrDiapazon.h"
#include "VCL_NNFrDoubleDiapazon.h"
#include "VCL_NNFrIntDiapazon.h"
#include "VCL_NNFrLongLongIntDiapazon.h"
#include "VCL_NNFrPeriod.h"
#include "VCL_NNFrShortIntDiapazon.h"
#include <memory>
#include <algorithm>
#include "VCL_NNFmStoryData.h"
#include "VCL_NNFmRowInspector.h"
#include "VCL_NNFormAdmin.h"
#include "VCL_NNDBComboBoxDateTime.h"
#include "VCL_NNCommon.h"
#pragma resource "*.res"
#pragma package(smart_init)

namespace NNV {

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

TNodeAdmins::iterator __fastcall TNodeAdmins::Add( TNNVNodeAdmin* ANodeAdmin )
{
  iterator i = FindCache( ANodeAdmin );
  if ( i == end() ) {
    i = insert( std::make_pair( ANodeAdmin, new NNV::TNodeAdminPair ) ).first;
    ResetCache();
  }
  return i;
}

TTreeBookmark::TTreeBookmark()
  : Node( nullptr )
  , DetailPK( EmptyPK )
{
}

TTreeBookmark::TTreeBookmark( TNNVTreeNode *ANode, long long int ADetailPK )
  : Node( ANode )
  , DetailPK( ADetailPK )
{
}

void __fastcall TTreeBookmark::Execute()
{
  if ( Node->NodeAdmin ) {
    Node->Selected = true;
    Node->MakeVisible();
    if ( Node->NodeAdmin->DetailDataSet &&
         Node->NodeAdmin->DetailDataSet->Fields->Fields[ 0 ]->AsLargeInt != DetailPK )
      Node->NodeAdmin->DetailDataSet->Locate( Node->NodeAdmin->DetailDataSet->Fields->Fields[ 0 ]->FieldName, DetailPK, TLocateOptions() );
  }
}

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

TDSetBookmark::TDSetBookmark(TNNVQuery *aDataSet) : DataSet(aDataSet)
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
  TNNVQuery *qu;
  int L = AOwner->ComponentCount;
  for ( int I = 0; I < L; ++I ) {
    qu = dynamic_cast< TNNVQuery* >( AOwner->Components[ I ] );
    if ( qu && qu->NeedSave )
      operator[]( qu->Name ) = qu;
  }
}

TMapQuery::~TMapQuery()
{
}

void __fastcall TMapQuery::SaveToFiler( TNNVTextStream *Filer )
{
  for ( iterator I = begin(); I != end(); ++I )
    (*I).second->SaveToFiler( Filer );
}

void __fastcall TMapQuery::LoadFromFiler( TNNVTextStream *Filer )
{
  for ( iterator I = begin(); I != end(); ++I )
    (*I).second->LoadFromFiler( Filer );
}

void __fastcall TMapQuery::PrepareStandartMacros()
{
  for ( iterator I = begin(); I != end(); ++I )
    (*I).second->PrepareStandartMacros();
}

TBufferIntBox::TBufferIntBox()
{
}

TBufferIntBox::~TBufferIntBox()
{
}

}

// ---------------------------------------------------------------------------
namespace NNV
{
  void __fastcall MakeNodeActive( TTreeNode *Node )
  {
    if ( Node ) {
      Node->Selected = true;
      Node->MakeVisible();
    }
  }
}

__fastcall TNNVTreeView::TNNVTreeView( TComponent* Owner )
  : inherited( Owner )
, fSearchReset( false )
, FSearchExecute( false )
, fNavTree( NNVConst::MaxTreeHistory, NNV::MakeNodeActive )
, SearchDlgOptions()
{
  FSearchHistory = new TStringList();
}

__fastcall TNNVTreeView::~TNNVTreeView()
{
  delete FSearchHistory;
}

// ---------------------------------------------------------------------------
void __fastcall TNNVTreeView::Change( TTreeNode *Node )
{
  inherited::Change( Node );
  if ( Visible && Node )
    NavTree.Add( Node );
}

void __fastcall TNNVTreeView::DoCWEditCancel( TTreeNode *Node )
{
  if ( FOnCWEditCancel )
    FOnCWEditCancel( this, Node );
}

void __fastcall TNNVTreeView::DoCWNewEditCancel(TTreeNode *Node, bool &IsDeleteNode )
{
  if ( FOnCWNewEditCancel )
    FOnCWNewEditCancel( this, Node, IsDeleteNode );
}

void __fastcall TNNVTreeView::CWDoEdit(TTreeNode *Node)
{
}

void __fastcall TNNVTreeView::Edit( const tagTVITEMW &Item )
{
  TTreeNode *Node;
  if ( ( Item.state & TVIF_PARAM ) != 0 )
    Node = (TTreeNode*)(Item.lParam);
  else
    Node = Items->GetNode(Item.hItem);
  if ( Item.pszText == nullptr ) {
    if ( FIsEditingNew ) {
      bool IsDeleteNode = true;
      DoCWNewEditCancel( Node, IsDeleteNode );
      if ( IsDeleteNode )
        Node->Delete();
    }
    else
      DoCWEditCancel( Node );
  }
  else {
    inherited::Edit( Item );
    CWDoEdit( Node );
  }
  FIsEditingNew = false;
}

TTreeNode* __fastcall TNNVTreeView::NewChildAndEdit( TTreeNode *Node
                                                   , const System::String S )
{
  TTreeNode *R;

  SetFocus();

  R = Items->AddChild( Node, S );
  FIsEditingNew = true;

  if ( Node )
    Node->Expand( false );

  R->Selected = true;
  R->EditText();

  return R;
}

void __fastcall TNNVTreeView::ExecuteSearchDialog()
{
  fmvSearch = new TfmvSearch( this, false );

  fmvSearch->fbRes->OnPrepare = PrepareSearch;
  fmvSearch->fbRes->OnExecute = ExecuteSearch;

  fmvSearch->ShowDialog( Owner );
}

void __fastcall TNNVTreeView::PrepareSearch( TObject *Sender )
{
  TComboBox* cb;
  TLabel *la;

  fmvSearch->Caption = fmvSearch->Caption + NNVConst::OnTheTree;

  la          = new TLabel( fmvSearch );
  la->Caption = NNVConst::TheTextForSearch;
  la->Parent  = fmvSearch->sbSkip;
  la->Top     = 4;
  la->Left    = 4;

  cb          = new TComboBox( fmvSearch->sbSkip );
  cb->Top     = 4;
  cb->Left    = la->Left + la->Width + 4;
  cb->Width   = fmvSearch->sbSkip->Width - cb->Left - 4;
  cb->Parent  = fmvSearch->sbSkip;

  SetSearchDialogOptions();

  fmvSearch->rgOperation->Visible      = false;
  fmvSearch->rgFilterSearch->Enabled   = false;
  fmvSearch->rgFilterSearch->ItemIndex = 1;
}

void __fastcall TNNVTreeView::ExecuteSearch( TObject *Sender )
{
  FSearchExecute = true;
  SaveSearchDialogOptions();
  SearchNext();
  FSearchExecute = false;
}

void __fastcall TNNVTreeView::SetSearchDialogOptions()
{
  fmvSearch->SearchDlgOptions = SearchDlgOptions;
  dynamic_cast< TComboBox* >( fmvSearch->sbSkip->Components[0] )->Items->Assign( FSearchHistory );
  if ( ( !FTextEmpty ) && ( FSearchHistory->Count > 0 ) )
    dynamic_cast< TComboBox* >( fmvSearch->sbSkip->Components[ 0 ] )->Text = FSearchHistory->Strings[ 0 ];
}

void __fastcall TNNVTreeView::SaveSearchDialogOptions()
{
  int i;
  TComboBox *cb;
  SearchDlgOptions = fmvSearch->SearchDlgOptions;
  cb = dynamic_cast< TComboBox* >( fmvSearch->sbSkip->Components[0] );
  FTextEmpty = cb->Text.IsEmpty();
  NNV::SaveComboBox( cb, 30 );
  FSearchHistory->Text = cb->Items->Text;
}

void __fastcall TNNVTreeView::SetEditKindID( TDBEdit *Value )
{
  if ( FEditKindID != Value ) {
    FEditKindID = Value;

    if ( EditKindID )
      EditKindID->FreeNotification( this );
  }
}

void __fastcall TNNVTreeView::SearchNext()
{
  bool fGoStart = true;
  TTreeNode *TN;

  if ( FTextEmpty ) {
    Dialogs::MessageDlg( NNVConst::AttemptSearchEmpty, mtError, TMsgDlgButtons() << mbOK, 0 );
    return;
  }

  fSearchReset = false;
  if ( ( SearchDlgOptions.StartIsBegin ) && ( !SearchDlgOptions.Backward ) && ( FSearchExecute ) )
    TN = Items->GetFirstNode();
  else if ( SearchDlgOptions.Backward )
    TN = Selected->GetPrev();
  else
    TN = Selected->GetNext();

  String ST = FSearchHistory->Strings[ 0 ];
  TRegExOptions RO;
  RO = RO << roMultiLine;
  if ( !SearchDlgOptions.SearchOptions.CaseSensitive )
    RO = RO << roIgnoreCase;
  std::unique_ptr< TRegEx > RegEx( new TRegEx( ST, RO ) );

  while ( TN ) {
    if ( SearchDlgOptions.SearchOptions.IsRegularExpression ) {
      fGoStart = !RegEx->IsMatch( TN->Text );
      if ( SearchDlgOptions.SearchOptions.NotThis )
        fGoStart = !fGoStart;
    } else
      fGoStart = !NNV::Compare( ST, TN->Text, SearchDlgOptions.SearchOptions );
    if ( !fGoStart )
      break;
    Application->ProcessMessages();
    if ( fSearchReset )
      break;
    if ( SearchDlgOptions.Backward )
      TN = TN->GetPrev();
    else
      TN = TN->GetNext();
  }
  if ( fGoStart && !fSearchReset )
    Dialogs::MessageDlg( NNVConst::RecordNotFind, mtInformation, TMsgDlgButtons() << mbOK, 0 );
  if ( !fGoStart )
    TN->Selected = true;
}

void __fastcall TNNVTreeView::KeyDown( Word &Key, TShiftState Shift )
{
  switch ( Key ) {
  case 'F':
    if ( Shift == ( TShiftState() << ssAlt ) ) {
      ExecuteSearchDialog();
      Key = 0;
    }
    break;
  case 'R':
    if ( Shift == ( TShiftState() << ssAlt ) ) {
      ResetSearch();
      Key = 0;
    }
    break;
  case vkF3:
    if ( Shift == ( TShiftState() << ssAlt ) ) {
      SearchNext();
      Key = 0;
    }
  }
  if ( Key )
    inherited::KeyDown( Key, Shift );
}

void __fastcall TNNVTreeView::LoadFromFiler(TNNVTextStream *Filer)
{
  SearchDlgOptions.LoadFromFiler( Filer );
  FTextEmpty = Filer->ReadBool();
  FSearchHistory->Text = Filer->ReadString();
  Filer->ReadFont( Font );
}

void __fastcall TNNVTreeView::SaveToFiler( TNNVTextStream *Filer )
{
  SearchDlgOptions.SaveToFiler( Filer );
  Filer->WriteBool( FTextEmpty );
  Filer->WriteString( FSearchHistory->Text );
  Filer->WriteFont( Font );
}

String __fastcall TNNVTreeView::PathStr( bool IsRoot_ )
{
  bool F = true;
  String S;

  TTreeNode *TI = Selected;
  while ( TI ) {
    if ( !IsRoot_ && TI->Level == 0 && !F )
      break;
    else {
      if ( !F )
        S = NNVConst::NodeDelimeter + S;
      S = TI->Text + S;
      F = false;
    }
    TI = TI->Parent;
  }
  return S;
}

// ---------------------------------------------------------------------------
__fastcall TNNVNodeAdmin::TNNVNodeAdmin( TComponent * Owner )
  : inherited( Owner )
{
  FDetailDataSource = new TDataSource( this );
  DetailDataSource->OnDataChange = DetailDataChange;
  DragDropKind    = ddkMove;
}

// ---------------------------------------------------------------------------
__fastcall TNNVNodeAdmin::~TNNVNodeAdmin()
{
  if ( DataSet )
    DataSet->RemoveAdmin( this );
}

void __fastcall TNNVNodeAdmin::DetailDataChange( TObject *Sender, TField *Field )
{
  if ( Field == nullptr && StartDetailPK ) {
    DetailPK = DetailDataSet->Fields->Fields[ 0 ]->AsLargeInt;
  }
}

void __fastcall TNNVNodeAdmin::Loaded()
{
  inherited::Loaded();

  ActualOnly      = false;
  EndToEndViewing = false;
}

void __fastcall TNNVNodeAdmin::DoFirstEnter()
{
  if ( FOnFirstEnter )
    FOnFirstEnter( this );
}

void __fastcall TNNVNodeAdmin::DoEnter()
{
  if ( TreeView ) {
    if ( TreeView->EditKindID ) {
      if ( DataSource && DataSource->DataSet ) {
        TreeView->EditKindID->DataSource = DataSource;
        TreeView->EditKindID->DataField  = DataSource->DataSet->Fields->Fields[ NNV::tvID ]->FieldName;
      } else {
        TreeView->EditKindID->DataSource = nullptr;
        TreeView->EditKindID->DataField  = L"";
      }
    }
  }

  if ( FOnEnter )
    FOnEnter( this );
}

void __fastcall TNNVNodeAdmin::DoExit()
{
  if ( FOnExit )
    FOnExit( this );
}

void __fastcall TNNVNodeAdmin::DoLastExit()
{
  if ( FOnLastExit )
    FOnLastExit(this);
}

void __fastcall TNNVNodeAdmin::DoMergeNodes( TTreeNode *Source, TTreeNode *Target )
{
  if ( FOnMergeNodes )
    FOnMergeNodes( this, Source, Target );
}

void __fastcall TNNVNodeAdmin::DoGetBaseParent()
{
  if ( FOnGetBaseParent )
    FOnGetBaseParent( this );
}

void __fastcall TNNVNodeAdmin::DoInvertActual()
{
  if ( DataSet ) {
    TField *fa = DataSet->Fields->Fields[ NNV::tvActual ];
    DataSet->CWCheckEditMode();
    fa->AsBoolean = !fa->AsBoolean;
    DataSet->Post();
  }
}

void __fastcall TNNVNodeAdmin::PrepareMacroActualOnly( TNNVQuery *qu, bool NeedTreeViewReloadNodeAdmin )
{
  if ( qu ) {
    TFDMacro *m;
    m = qu->FindMacro( NNVConst::ACTUAL_ONLY );

    if ( m ) {
      bool SA = qu->Active;
      qu->SaveUKey();
      qu->Active = false;
      m->Value = ActualOnly ? NNVConst::ActualOnly : NNVConst::True;
      qu->Active = SA;
      qu->GotoUKey();

      if ( TreeView && NeedTreeViewReloadNodeAdmin )
        TreeView->CWReload( this );
    }
  }
}

void __fastcall TNNVNodeAdmin::SetActualOnly( bool Value )
{
  if ( FActualOnly != Value ) {
    FActualOnly = Value;

    if ( ActualOnlyNeed ) {
      TNNVQuery *quDataSet, *quDetailDataSet;
      quDataSet       = DataSet;
      quDetailDataSet = DetailDataSet;
      quDataSet->SaveUKey();
      quDetailDataSet->SaveUKey();

      PrepareMacroActualOnly( quDataSet,       true  );
      PrepareMacroActualOnly( quDetailDataSet, false );
    }
  }
}

void __fastcall TNNVNodeAdmin::SetEndToEndViewing( bool Value )
{
  if ( FEndToEndViewing != Value ) {
    FEndToEndViewing = Value;

    if ( !DataSet || !DetailDataSource || !DetailDataSource->DataSet || !EndToEndViewingNeed )
      return;

    TNNVQuery *qu = DetailDataSet;

    if ( !qu )
      return;

    TFDMacro *m = qu->FindMacro( NNVConst::END_TO_END_VIEWING );

    if ( !m )
      return;

    bool SA = qu->Active;
    qu->SaveUKey();
    qu->Active = false;
    m->Value = EndToEndViewing ? NNVConst::True : NNVConst::EndToEndViewing;

    if ( EndToEndViewing ) {
      qu->MasterSource = nullptr;
    } else {
      qu->MasterSource = DataSource;
    }

    qu->Active = SA;
    qu->GotoUKey();
  }
}

void __fastcall TNNVNodeAdmin::DoPrint()
{
  if ( FOnPrint )
    FOnPrint( this );
}

TNNVQuery* __fastcall TNNVNodeAdmin::GetDetailDataSet()
{
  return dynamic_cast< TNNVQuery* >( DetailDataSource->DataSet );
}

void __fastcall TNNVNodeAdmin::SetDetailDataSet( TNNVQuery* Value )
{
  DetailDataSource->DataSet = Value;
}

TNNVQuery* __fastcall TNNVNodeAdmin::GetDataSet()
{
  if ( !DataSource || !DataSource->DataSet )
    return nullptr;

  TNNVQuery *qu = dynamic_cast< TNNVQuery* >( DataSource->DataSet );

  return qu;
}

void __fastcall TNNVNodeAdmin::SetDataSource( TDataSource *Value )
{
  if ( FDataSource != Value ) {
    FDataSource = Value;

    TNNVQuery *qu = nullptr;

    if ( DataSource ) {
      qu = dynamic_cast< TNNVQuery* >( DataSource->DataSet );
      DataSource->FreeNotification( this );
    }

    if ( qu ) {
      qu->RemoveAdmin( this );
      qu->AdminsSet->insert( this );
    }
  }
}

void __fastcall TNNVNodeAdmin::Notification( TComponent *AComponent, TOperation Operation )
{
  inherited::Notification( AComponent, Operation );
  if ( Operation == opRemove ) {
    if ( AComponent == DataSource )
      FDataSource = nullptr;
    else if ( AComponent == TreeView )
      FTreeView = nullptr;
  }
}

void __fastcall TNNVNodeAdmin::DoLoadNodes()
{
  if ( TreeView == nullptr )
    throw Exception( Name + String( L"->TreeView == nullptr" ) );

  bool B = TreeView->IsRefresh &&
         ( TreeView->RefreshAdmin == TreeView->NodeAdmin ) &&
         ( TreeView->Selected != nullptr );
  long long int SavePK;

  if ( B ) {
    SavePK = ( ( TNNVTreeNode* )( TreeView->Selected ) )->PK;
    SaveDetailPK();
  }

  CurrentNode = nullptr;
  StartDetailPK = false;

  if ( FOnLoadNodes )
    FOnLoadNodes( this );

  if ( B ) {
    if ( TreeView->RefreshAdmin->LocateNode )
      TreeView->RefreshAdmin->LocateNode->Selected = true;

    TDataSet *DSet = DataSet;
    if ( DSet )
      DSet->Locate( DSet->Fields->Fields[ NNV::tvID ]->FieldName, SavePK, TLocateOptions() );

    RestoreDetailPK();
  }
  if ( DetailPK == NNV::EmptyPK )
    StartDetailPK = true;
}

void __fastcall TNNVNodeAdmin::SaveDetailPK()
{
  if ( DetailDataSet )
    DetailPK = DetailDataSet->Fields->Fields[ 0 ]->AsLargeInt;
}

void __fastcall TNNVNodeAdmin::RestoreDetailPK()
{
  if ( DetailDataSet && DetailDataSet->Fields->Fields[ 0 ]->AsLargeInt != DetailPK ) {
    DetailDataSet->Locate( DetailDataSet->Fields->Fields[ 0 ]->FieldName
                         , DetailPK
                         , TLocateOptions() );
    StartDetailPK = true;
  }
}

void __fastcall TNNVNodeAdmin::SetTreeView( TNNVDBTreeView *Value )
{
  if ( FTreeView != Value ) {
    FTreeView = Value;

    bool IsRunTime = !ComponentState.Contains( csDesigning );
    if ( TreeView ) {
      TreeView->FreeNotification( this );

      if ( IsRunTime && TreeView->NodeAdmins )
        TreeView->NodeAdmins->erase( this );

      if ( IsRunTime ) {
        NNV::TNodeAdmins::iterator i = TreeView->NodeAdmins->Add( this );
        (*i).second->OnFirstEnter = FirstEnter;
        (*i).second->OnEnter = Enter;
        (*i).second->OnExit = Exit;
        (*i).second->OnLastExit = LastExit;
      }
    }
  }
}

void __fastcall TNNVNodeAdmin::PrepareDataSet()
{
  if ( DataSet ) {
    DataSet->AdminsSet->Enable = false;
    try {
      DataSet->CWOpen();
    } __finally {
      DataSet->AdminsSet->Enable = true;
    }
  }
}

void __fastcall TNNVNodeAdmin::UnPrepareDataSet()
{
  if ( DataSet )
    DataSet->CWClose();
}

void __fastcall TNNVNodeAdmin::DoGetNodeParams(TNNVNodeParams &NodeParams)
{
  if ( FOnGetNodeParams )
    FOnGetNodeParams( this, NodeParams );
  else
    NodeParams.Text = DataSet->Fields->Fields[ NNV::tvText ]->DisplayText;
}

void __fastcall TNNVNodeAdmin::DoSetNodeText( String S )
{
  if ( FOnSetNodeText )
    FOnSetNodeText( this, S );
  else
    DataSet->Fields->Fields[ NNV::tvText ]->AsString = S;
}

void __fastcall TNNVNodeAdmin::DoGetUserData( int UserData, long long int &Result
                                            , bool &Apply )
{
  Apply = false;
  Result = 0;
  if ( FOnGetUserData )
    FOnGetUserData( this, UserData, Result, Apply );
}

void __fastcall TNNVNodeAdmin::DoSetUserData(int UserData, long long int Value)
{
  if ( FOnSetUserData )
    FOnSetUserData( this, UserData, Value );
}

void __fastcall TNNVNodeAdmin::SetDragDropKind( TNNVDragDropKind Value )
{
  if ( FDragDropKind != Value ) {
    FDragDropKind = Value;

    if ( TreeView && ( TreeView->NodeAdmin == this ) )
      TreeView->DragDropKind = DragDropKind;
  }
}

void __fastcall TNNVNodeAdmin::FirstEnter(TObject *Sender)
{
  PrepareDataSet();
  DoFirstEnter();
}

void __fastcall TNNVNodeAdmin::Enter(TObject *Sender)
{
  DoEnter();
}

void __fastcall TNNVNodeAdmin::Exit(TObject *Sender)
{
  DoExit();
}

void __fastcall TNNVNodeAdmin::LastExit(TObject *Sender)
{
  DoLastExit();
  UnPrepareDataSet();
}

void __fastcall TNNVNodeAdmin::LoadFromFiler( TNNVTextStream *Filer )
{
  ActualOnly      = Filer->ReadBool();
  EndToEndViewing = Filer->ReadBool();
  ActivePK        = Filer->ReadLongLongInt();
  DetailPK        = Filer->ReadLongLongInt();
}

void __fastcall TNNVNodeAdmin::SaveToFiler( TNNVTextStream *Filer )
{
  Filer->WriteBool( ActualOnly );
  Filer->WriteBool( EndToEndViewing );
  Filer->WriteLongLongInt( ActivePK );
  Filer->WriteLongLongInt( DetailPK );
}

__fastcall TNNVDBTreeView::TNNVDBTreeView( TComponent* Owner )
  : inherited( Owner )
{
  HideSelection             = false;
  SortType                  = Vcl::Comctrls::stText;
  FDataSource               = new TDataSource( this );
  FNodeAdmins               = new NNV::TNodeAdmins();
  FDataSource->OnDataChange = DataChange;
}

__fastcall TNNVDBTreeView::~TNNVDBTreeView()
{
  delete FNodeAdmins;
  delete FDataSource;

  FDataSource = nullptr;
  FNodeAdmins = nullptr;
}

void __fastcall TNNVDBTreeView::SetDataSet( TDataSet *Value )
{
  FDataSource->DataSet = Value;
}

void __fastcall TNNVDBTreeView::RefreshBugUpdate()
{
  Items->BeginUpdate();
  Items->EndUpdate();
}

void __fastcall TNNVDBTreeView::StartAdmin()
{
  if ( IsStartAdmin )
    return;
  if ( Work )
    return;

  FTreeBookmarks.clear();
  NavTree.Clear();
  FIsRefresh = false;
  FWork++;
  Items->BeginUpdate();
  try {
    FinishAdmin();
    NodeVector.clear();
    TNNVNodeVector::size_type N = NodeAdmins->size();
    if ( N == 0 )
      throw Exception( "NodeAdmins->size() == 0" );
    NodeVector.reserve( N );
    NodeVector.insert( NodeVector.begin(), N, nullptr );
    for ( NNV::TNodeAdmins::iterator i = NodeAdmins->begin(); i != NodeAdmins->end(); ++i )
      NodeVector[(*i).first->LoadOrder] = (*i).first;
    for ( TNNVNodeVector::iterator i = NodeVector.begin(); i != NodeVector.end(); ++i )
      if ( (*i)->Enabled )
        (*i)->DoLoadNodes();
    AlphaSort();
  } __finally {
    FWork--;
    Items->EndUpdate();
  }
  FIsStartAdmin = true;
  PowderTree();
}

void __fastcall TNNVDBTreeView::PowderTree()
{
  NodeAdminSelect( NodeVector[ ActiveOrder ] );
}

void __fastcall TNNVDBTreeView::NodeAdminSelect( TNNVNodeAdmin *ANodeAdmin )
{
  if ( !ANodeAdmin )
    return;

  if ( Selected && (ANodeAdmin == ((TNNVTreeNode*)(Selected))->NodeAdmin) &&
       ( ANodeAdmin->ActivePK == ((TNNVTreeNode*)(Selected))->PK ) )
    return;
  TTreeNode *TI = ANodeAdmin->LocateNode, *T = nullptr;
  while ( TI ) {
    if ( ANodeAdmin == ((TNNVTreeNode*)(TI))->NodeAdmin )
      if ( !T )
        T = TI;
    if ( T && (ANodeAdmin->ActivePK == ((TNNVTreeNode*)(TI))->PK) ) {
      T = TI;
      break;
    }
    if ( T && (ANodeAdmin != ((TNNVTreeNode*)(TI))->NodeAdmin) )
      break;
    TI = TI->GetNext();
  }
  if ( T ) {
    T->Selected = true;
    T->MakeVisible();
    ANodeAdmin->RestoreDetailPK();
  } else
    NodeAdmin = ANodeAdmin;
}

void __fastcall TNNVDBTreeView::FinishAdmin()
{
  if ( !IsStartAdmin )
    return;

  FIsStartAdmin = false;

  Items->BeginUpdate();
  FWork++;
  try {
    Items->Clear();
  } __finally {
    Items->EndUpdate();
    FWork--;
  }
  NodeAdmins->ResetAll();
  NodeAdmin = nullptr;
}

TTreeNode* __fastcall TNNVDBTreeView::FindNode()
{
  if ( ( !IsStartAdmin ) || DataSource->DataSet->ControlsDisabled() || Work != 0 ||
      DataSource->DataSet->IsEmpty() )
    return nullptr;
  TTreeNode *TI = FindNodePK( NodeAdmin, DataSource->DataSet->Fields->Fields[ NNV::tvID ]->AsLargeInt );
  if ( TI ) {
    NodeAdmin->CurrentNode = ((TNNVTreeNode*)(TI));
    NodeAdmin->ActivePK    = ((TNNVTreeNode*)(TI))->PK;
  }
  return TI;
}

TDataSet* __fastcall TNNVDBTreeView::GetDataSet()
{
  return DataSource->DataSet;
}

TTreeNode* __fastcall TNNVDBTreeView::FindNodePK( TNNVNodeAdmin *ANodeAdmin, long long int PK )
{
  TTreeNode *TI = ANodeAdmin->LocateNode;
  while ( TI ) {
    if ( (ANodeAdmin == ((TNNVTreeNode*)(TI))->NodeAdmin) && ( PK == ((TNNVTreeNode*)(TI))->PK) )
      return TI;
    TI = TI->GetNext();
  }
  return TI;
}

void __fastcall TNNVDBTreeView::DataChange( TObject *Sender, TField *Field )
{
  if ( !IsStartAdmin )
    return;

  switch ( DataSource->DataSet->State ) {
  case dsBrowse: {
      TTreeNode *TN = FindNode();
      if (TN) {
        TN->Selected = true;
        TN->MakeVisible();
      }
    } break;
  case dsEdit:
  case dsInsert:
    UpdateData( DataSource );
  default:
    break;
  }
}

void __fastcall TNNVDBTreeView::UpdateData( TObject *Sender )
{
  if ( !IsStartAdmin )
    return;

  if ( Work != 0 )
    return;

  TTreeNode *TN = Selected;
  if ( TN ) {
    TNNVNodeParams NodeParams;
    if ( !( ( ( TNNVTreeNode* )( Selected ) )->NodeAdmin == NodeAdmin &&
            ( ( TNNVTreeNode* )( Selected ) )->PK == DataSource->DataSet->Fields->Fields[ NNV::tvID ]->AsLargeInt ) )
      TN = FindNode();

    if ( TN ) {
      NodeAdmin->DoGetNodeParams( NodeParams );
      TN->Text = NodeParams.Text;
      TN->ImageIndex = NodeParams.ImageIndex;
      if ( NodeParams.SelectedIndex == -1 )
        TN->SelectedIndex = NodeParams.ImageIndex;
      else
        TN->SelectedIndex = NodeParams.SelectedIndex;
    }
  }
}

void __fastcall TNNVDBTreeView::Change( TTreeNode *Node )
{
  if ( ( Work == 0 ) && ( IsStartAdmin ) && Node ) {
    FWork++;
    try {
      if ( ( ( TNNVTreeNode* )( Node ) )->NodeAdmin ) {
        if ( DataSource->DataSet && NNV::IsEditModes( DataSource->DataSet->State ) )
          DataSource->DataSet->Post();
        NodeAdmin = ( ( TNNVTreeNode* )( Node ) )->NodeAdmin;
        if ( !Locate( ( ( TNNVTreeNode* )( Node ) ) ) )
          throw Exception( NNVConst::NodeNotUnerstand );
      }
      else
        NodeAdmin = nullptr;
    }
    __finally {
      FWork--;
    }
  }
  inherited::Change( Node );
}

bool __fastcall TNNVDBTreeView::GetKeyEnabled()
{
  return NodeAdmin && NodeAdmin->KeyEnabled;
}

void __fastcall TNNVDBTreeView::KeyDown( Word &Key, TShiftState Shift )
{
  TTreeNode *TN;
  if ( !KeyEnabled ) {
    inherited::KeyDown( Key, Shift );
    if ( !Key )
      return;
  }
  switch ( Key ) {
  case vkInsert:
    if ( !KeyEnabled )
      break;
    if ( Shift == ( TShiftState() << ssCtrl ) ) {
      CWInsertNode( NNV::InsertIsChild );
      Key = 0;
    } else if ( Shift == ( TShiftState() << ssAlt ) ) {
      CWInsertNode( NNV::InsertIsNoChild );
      Key = 0;
    } else if ( Shift == TShiftState() ) {
      CWInsertNode( NNV::InsertIsConfirm );
      Key = 0;
    }
    break;
  case vkF2:
    if ( !KeyEnabled )
      break;
    Selected->EditText();
    Key = 0;
    break;
  case vkEscape:
    if ( !KeyEnabled )
      break;
    if ( ReadOnly && CancelNewNode() )
      Key = 0;
    break;
  case vkDelete:
    if ( !KeyEnabled )
      break;
    if ( Shift == ( TShiftState() << ssCtrl ) ) {
      DeleteNode();
      Key = 0;
    }
    break;
  case vkF5:
    if ( !KeyEnabled )
      break;
    if ( ( Shift == ( TShiftState() << ssShift ) ) &&
         ( NodeAdmin && ( NodeAdmin->DragDropKind == ddkMove ) ) ) {
      CutNode();
      TN = fStartNode->Parent;
      if ( TN )
        TN = TN->Parent;
      PasteNode( TN );
      Key = 0;
    }
    break;
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    if ( Shift.Contains( ssCtrl ) ) {
      if ( Shift.Contains( ssShift ) ) {
        long long int S;
        if ( Selected &&
             ((TNNVTreeNode*)(Selected))->NodeAdmin &&
             ((TNNVTreeNode*)(Selected))->NodeAdmin->DetailDataSource )
          S = ( (TNNVTreeNode*)(Selected) )->NodeAdmin->DetailDataSource->DataSet->Fields->Fields[ 0 ]->AsLargeInt;
        FTreeBookmarks[ Key ] = NNV::TTreeBookmark( ((TNNVTreeNode*)(Selected)), S );
      } else {
        FTreeBookmarks.GoTo( Key );
      }
    }
    Key = 0;
  }
  if ( Key )
    inherited::KeyDown( Key, Shift );
}

void __fastcall TNNVDBTreeView::DoEnter()
{
  inherited::DoEnter();
  DoNodeAdminChange( NodeAdmin );
}

void __fastcall TNNVDBTreeView::CutNode()
{
  fStartNode = Selected;
}

void __fastcall TNNVDBTreeView::PasteNode( TTreeNode *TargetNode )
{
  switch ( DragDropKind ) {
  case ddkMove:
    CWMoveNode( TargetNode );
    break;
//  case ddkSort:
//    NewPosNode( TargetNode );
//    break;
  case ddkCustom:
    DoPasteNode( TargetNode );
    break;
  case ddkInherit:
    break;
  }
}

void __fastcall TNNVDBTreeView::CWMoveNode( TTreeNode *TargetNode )
{
  if ( TargetNode ) {
    if (TargetNode->HasAsParent(fStartNode) || (TargetNode == fStartNode) ||
        (!((TNNVTreeNode*)(TargetNode))->NodeAdmin) ||
        (((TNNVTreeNode*)(TargetNode))->NodeAdmin != ((TNNVTreeNode*)(fStartNode))->NodeAdmin ) )
      throw Exception( NNVConst::NodeImpossibleMove + fStartNode->Text + NNVConst::ToNode + TargetNode->Text + '!');

    if ( Dialogs::MessageDlg( NNVConst::MoveNode + fStartNode->Text + NNVConst::ToNodeSample + TargetNode->Text + '?', mtConfirmation,
         (TMsgDlgButtons() << mbYes << mbNo ), 0 ) == mrYes ) {
      FWork++;
      try {
        if ( !Locate( ((TNNVTreeNode*)(StartNode)) ) )
          throw Exception( NNVConst::NotUnderstandStartNode );
      } __finally {
        FWork--;
      }
      SetNewParentID( ((TNNVTreeNode*)(TargetNode))->PK, TargetNode );
    }
  } else {
    SetNewParentID( NodeAdmin->BaseParent, TargetNode );
  }
}

void __fastcall TNNVDBTreeView::SetNewParentID( long long int NewParentID, TTreeNode *TargetNode )
{
  DataSource->DataSet->Edit();
  DataSource->DataSet->Fields->Fields[ NNV::tvParentID ]->AsLargeInt = NewParentID;
  DataSource->DataSet->Post();

  fStartNode->MoveTo( TargetNode, naAddChild );
  if ( fStartNode == NodeAdmin->LocateNode )
    GetNewLocateNode();
}

long long int __fastcall TNNVDBTreeView::TreeSortInfo( long long int &Oldpk, long long int &Newpk, const String &Table, const String &Fieldpk )
{
  long long int R = 0;
  return R;
}

void __fastcall TNNVDBTreeView::TreeSort( long long int Oldsortno
                                        , long long int Newsortno
                                        , const String &Table
                                        , const String &Fieldpk
                                        , long long int Parentno)
{
}

void __fastcall TNNVDBTreeView::GetNewLocateNode()
{
  TTreeNode *TI = Items->GetFirstNode();
  while ( TI ) {
    if ( ((TNNVTreeNode*)(TI))->NodeAdmin == NodeAdmin ) {
      NodeAdmin->LocateNode = TI;
      break;
    }
    TI = TI->GetNext();
  }
}

void __fastcall TNNVDBTreeView::DeleteNode()
{
  if ( Work != 0 )
    return;

  TTreeNode *TN = Selected, *PN;
  bool B;
  PN = TN->Parent;
  B = false;
  if ( !( (!PN) && (NodeAdmins->size() == 1 ) &&
       ( NodeAdmin->BaseParent != NNV::EmptyPK) ) )
    if ( (!PN) ||
         ( (!((TNNVTreeNode*)(PN))->NodeAdmin) ||
           (!((TNNVTreeNode*)(TN))->NodeAdmin) ) ||
           ( ((TNNVTreeNode*)(PN))->NodeAdmin != ((TNNVTreeNode*)(TN))->NodeAdmin ) ||
           ( ((TNNVTreeNode*)(Selected))->PK == NNV::EmptyPK ) )
      B = true;
  if ( B ) {
    Dialogs::MessageDlg(NNVConst::TheNode + Selected->Text + NNVConst::DeleteImpossible, mtInformation, (TMsgDlgButtons() << mbOK), 0 );
    return;
  }
  if ( Dialogs::MessageDlg(NNVConst::ToDeleteNode + Selected->Text + " ?", mtConfirmation, (TMsgDlgButtons() << mbYes << mbNo), 0) == mrYes ) {
    FWork++;
    try {
      DataSource->DataSet->Delete();
    } __finally {
      FWork--;
    }
    if ( Selected )
      Locate( ((TNNVTreeNode*)(Selected)) );
    RefreshBugUpdate();
  }
}

int __stdcall CWCompareNodeAlpha( TNNVTreeNode *Node1, TNNVTreeNode *Node2, int Reverse )
{
  int R = AnsiStrIComp( Node1->Text.c_str(), Node2->Text.c_str() );
  if ( Reverse != 0 )
    R = -R;
  return R;
}

void __fastcall TNNVDBTreeView::SetLoadDataSet( TDataSet *Value )
{
  if ( FLoadDataSet != Value ) {
    FLoadDataSet = Value;

    if ( LoadDataSet != nullptr )  {
      FLoadDataSetFieldID       = LoadDataSet->Fields->Fields[ NNV::tvID ];
      FLoadDataSetFieldParentID = LoadDataSet->Fields->Fields[ NNV::tvParentID ];
      FLoadDataSetFieldText     = LoadDataSet->Fields->Fields[ NNV::tvText ];
    } else {
      FLoadDataSetFieldID       = nullptr;
      FLoadDataSetFieldParentID = nullptr;
      FLoadDataSetFieldText     = nullptr;
    }
  }
}

void __fastcall TNNVDBTreeView::LoadNodeAdmin( TNNVTreeNode *Node
                                             , TNNVNodeAdmin *aNodeAdmin
                                             , long long int ARootID )
{
  TBookmark B;
  NavTree.Clear();
  AdminRefreshWork = true;
  FWork++;
  NNV::TMapLoadNodes aMapLoadNodesStart;
  try {
    LoadAdmin = aNodeAdmin;
    try {
      Items->BeginUpdate();
      try {
        B = LoadDataSet->Bookmark;
        LoadDataSet->DisableControls();
        try {
          aMapLoadNodesStart[ ARootID ] = Node;
          LoadAdmin->LocateNode = AddNodes( aMapLoadNodesStart );
          LoadAdmin->DoGetBaseParent();
          LoadDataSet->Bookmark = B;
        } __finally {
          LoadDataSet->EnableControls();
        }
      } __finally {
        Items->EndUpdate();
      }
    } __finally {
      LoadAdmin->CurrentNode = (TNNVTreeNode*)LoadAdmin->LocateNode;
      LoadAdmin = nullptr;
    }
  } __finally {
    FWork--;
  }
}

TTreeNode* __fastcall TNNVDBTreeView::AddNodes( const NNV::TMapLoadNodes &MapLoadNodes )
{
  TTreeNode *TN = nullptr, *TC = nullptr;
  TNNVTreeNode *TCNNV = nullptr;
  TNNVNodeParams NodeParams;
  TTreeNode *result = nullptr;

  long long int KindID = NNV::EmptyPK;
  NNV::TMapLoadNodes aMapLoadNodes;

  for ( NNV::TMapLoadNodes::const_iterator i = MapLoadNodes.begin(); i != MapLoadNodes.end(); ++i ) {
    KindID = (*i).first;
    TN     = (*i).second;

    aMapLoadNodes.clear();
    LoadDataSet->Locate( LoadDataSetFieldID->FieldName, KindID, TLocateOptions() );

    NodeParams.Clear();
    LoadAdmin->DoGetNodeParams( NodeParams );

    if ( IsRefresh && AdminRefreshWork && LoadAdmin->LocateNode ) {
      AdminRefreshWork = false;

      if ( !TN )
        TC = Items->Insert( LoadAdmin->LocateNode, NodeParams.Text ); // Это всегда корневая веточка LoadAdmin

      DeleteNodeForRefresh( (TNNVTreeNode*)( LoadAdmin->LocateNode ) );

      if ( !TC )
        TC = Items->AddChild( TN, NodeParams.Text );
    } else
      TC = Items->AddChild( TN, NodeParams.Text );

    if ( !result )
      result = TC;

    TC->ImageIndex = NodeParams.ImageIndex;

    if ( NodeParams.SelectedIndex == NNV::EmptyPK )
      TC->SelectedIndex = NodeParams.ImageIndex;
    else
      TC->SelectedIndex = NodeParams.SelectedIndex;

    TCNNV = static_cast< TNNVTreeNode* >( TC );
    TCNNV->NodeAdmin = LoadAdmin;
    TCNNV->PK        = LoadDataSetFieldID->AsLargeInt;

    LoadDataSet->First();
    while ( !LoadDataSet->Eof ) {
      if ( LoadDataSetFieldParentID->AsLargeInt == KindID )
        aMapLoadNodes[ LoadDataSetFieldID->AsLargeInt ] = TCNNV;
      LoadDataSet->MoveBy( 1 );
    }

    if ( !aMapLoadNodes.empty() )
      AddNodes( aMapLoadNodes );
  }

  return result;
}

void __fastcall TNNVDBTreeView::DeleteNodeForRefresh( TNNVTreeNode *TN )
{
  TNNVTreeNode *TE;
  while ( TN && TN->NodeAdmin == LoadAdmin ) {
    TE = ( TNNVTreeNode* )( TN->getNextSibling() );
    NavTree.Remove( TN );
    TN->Delete();
    if ( !TE )
      break;
    else
      TN = TE;
  }
}

void __fastcall TNNVDBTreeView::CWMergeNodes( TTreeNode *TargetNode )
{
  if ( ((TNNVTreeNode*)(fStartNode))->NodeAdmin != ((TNNVTreeNode*)(TargetNode))->NodeAdmin )
    throw Exception(NNVConst::TheMergeNodeImpossible + fStartNode->Text + NNVConst::TheAnd + TargetNode->Text);

  ((TNNVTreeNode*)(TargetNode))->NodeAdmin->DoMergeNodes( fStartNode, TargetNode );
}

void __fastcall TNNVDBTreeView::CWInsertNode( short Action )
{
  if ( Work != 0 )
    return;

  long long int N = 0;
  TTreeNode *TN = nullptr;
  FWork++;
  try {
    if ( !Selected ) {
      if ( NodeAdmins->size() == 1 ) {
        NodeAdmin = (*NodeAdmins->begin()).first;
        if ( NodeAdmin->BaseParent != NNV::EmptyPK )
          Action = NNV::InsertIsNoChild;
        else
          return;
      }
      else
        return;
    }

    if ( Selected && !((TNNVTreeNode*)(Selected))->NodeAdmin )
      throw Exception(NNVConst::InsertImpossible);

    if ( Action == NNV::InsertIsConfirm )
      switch (Dialogs::MessageDlg(NNVConst::ToMakeLevel + Selected->Text + '?',
          mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0)) {
      case mrYes:
        Action = NNV::InsertIsChild;
        break;
      case mrNo:
        Action = NNV::InsertIsNoChild;
        break;
      case mrCancel:
        Action = NNV::InsertIsCancel;
      }

    if ( Action == NNV::InsertIsCancel )
      return;

    switch ( Action ) {
    case NNV::InsertIsChild:
      TN = Selected;
      N = DataSource->DataSet->Fields->Fields[ NNV::tvID ]->AsLargeInt;
      break;
    case NNV::InsertIsNoChild:
      if ( Selected && Selected->Parent ) {
        TN = Selected->Parent;
        N = ((TNNVTreeNode*)(Selected->Parent))->PK;
      } else if ( NodeAdmin->BaseParent != NNV::EmptyPK ) {
        TN = nullptr;
        N = NodeAdmin->BaseParent;
      } else
        throw Exception( NNVConst::InsertImpossible );
    }

    if ( ReadOnly )
      TN = Items->AddChild( TN, NNVConst::TheNewNodeText );
    else
      TN = NewChildAndEdit( TN, NNVConst::TheNewNodeText );

    TN->Selected = true;
    DataSource->DataSet->Insert();
    DataSource->DataSet->Fields->Fields[ NNV::tvParentID ]->AsLargeInt = N;

    ((TNNVTreeNode*)(TN))->NodeAdmin = NodeAdmin;
    // К сожалению тут мы присваиваем ноль, так как тодлько при методе Post() появляется новый ID
    ((TNNVTreeNode*)(TN))->PK        = DataSource->DataSet->Fields->Fields[ NNV::tvID ]->AsLargeInt;
  } __finally {
    FWork--;
  }
  RefreshBugUpdate();
}

void __fastcall TNNVDBTreeView::CWRefresh()
{
  if ( !IsStartAdmin )
    return;

  CWRefreshAdmin();
}

void __fastcall TNNVDBTreeView::CWRefreshAdmin()
{
  Items->BeginUpdate();
  try {
    FWork++;
    try {
      FinishAdmin();
      for (NNV::TNodeAdmins::iterator i = NodeAdmins->begin();
      i != NodeAdmins->end(); ++i)
        if ((*i).first->DataSet)
          (*i).first->DataSet->CWRefresh();
    } __finally {
      FWork--;
    }
    StartAdmin();
  } __finally {
    Items->EndUpdate();
  }

  if ( Selected )
    Selected->MakeVisible();
}

void __fastcall TNNVDBTreeView::CWReload( TNNVNodeAdmin *ANodeAdmin )
{
  if ( !ANodeAdmin )
    return;
  if ( !ANodeAdmin->LocateNode )
    return;
  if ( ( ( TNNVTreeNode* )( ANodeAdmin->LocateNode ) )->PK == NNV::EmptyPK )
    return;

  Items->BeginUpdate();
  try {
    FIsRefresh = true;
    RefreshAdmin = ANodeAdmin;
    try {
      ANodeAdmin->DoLoadNodes();
    } __finally {
      RefreshAdmin = nullptr;
    }
    FIsRefresh = false;
    if ( ANodeAdmin->LocateNode )
      ANodeAdmin->LocateNode->AlphaSort();
  } __finally {
    Items->EndUpdate();
  }

  RefreshBugUpdate();
  Refresh();

  if ( Selected )
    Selected->MakeVisible();
}

bool __fastcall TNNVDBTreeView::CancelNewNode()
{
  if ( FIsEditingNew ) {
    Selected->EndEdit( true );
    return true;
  } else {
    if ( !DataSource->DataSet )
      return false;
    if ( NNV::IsEditModes( DataSource->DataSet->State ) ) {
      int N = ( Selected->AbsoluteIndex - 1 );
      FWork++;
      try {
        DataSource->DataSet->Cancel();
        Selected->Delete();
      } __finally {
        FWork--;
      }
      Items->Item[ N < 0 ? 0 : N ]->Selected = true;
      return true;
    }
  }
  return false;
}

void __fastcall TNNVDBTreeView::DoCWNewEditCancel( TTreeNode *Node
                                                 , bool &IsDeleteNode )
{
  DataSource->DataSet->Cancel();
  inherited::DoCWNewEditCancel( Node, IsDeleteNode );
}

void __fastcall TNNVDBTreeView::CWDoEdit( TTreeNode *Node )
{
  TDataSet *ADataSet = DataSource->DataSet;

  ++FWork;
  try {
    if ( !NNV::IsEditModes( ADataSet->State ) )
      ADataSet->Edit();
  } __finally {
    --FWork;
  }

  NodeAdmin->DoSetNodeText( Node->Text );

  if ( NNV::IsEditModes( ADataSet->State ) )
    ADataSet->Post();
  ( ( TNNVTreeNode* )( Node ) )->PK = ADataSet->Fields->Fields[ NNV::tvID ]->AsLargeInt;

  inherited::CWDoEdit( Node );
  RefreshBugUpdate();
}

void __fastcall TNNVDBTreeView::DoPasteNode( TTreeNode *TargetNode )
{
  if ( FOnPasteNode )
    FOnPasteNode( this, TargetNode );
}

void __fastcall TNNVDBTreeView::DoNodeAdminChange( TNNVNodeAdmin *ANodeAdmin )
{
  if ( FOnNodeAdminChange && ANodeAdmin )
    FOnNodeAdminChange( this, ANodeAdmin );
}

void __fastcall TNNVDBTreeView::DoStartDrag( Controls::TDragObject* &DragObject )
{
  if ( DragDropKind == ddkInherit ) {
    CutNode();

    inherited::DoStartDrag( DragObject );
    return;
  }
  CutNode();
}

void __fastcall TNNVDBTreeView::DragOver( System::TObject* Source, int X, int Y
                                        , TDragState State, bool &Accept )
{
  if ( DragDropKind == ddkInherit ) {
    inherited::DragOver( Source, X, Y, State, Accept );
    return;
  }
  if ( Source != this ) {
    Accept = false;
    return;
  }
  Accept = GetHitTestInfoAt( X, Y ).Contains( htOnItem );
}

void __fastcall TNNVDBTreeView::DragDrop( System::TObject* Source, int X, int Y )
{
  if ( DragDropKind == ddkInherit )
    inherited::DragDrop( Source, X, Y );
  else
    PasteNode( DropTarget );
}

void __fastcall TNNVDBTreeView::CWDeleteAllChild( TTreeNode *Node )
{
  TTreeNode *CN = Node->getFirstChild();
  while ( CN ) {
    delete CN;
    CN = Node->getFirstChild();
  }
}

bool __fastcall TNNVDBTreeView::Locate( TNNVTreeNode *Node )
{
  if ( !Node )
    return false;

  if ( Node->PK == NNV::EmptyPK )
    return true;

  TDataSet *DS = Node->NodeAdmin->DataSet;
  if ( DS ) {
    if ( NodeAdmin )
      NodeAdmin->CurrentNode = ( (TNNVTreeNode*)(Selected) );
    bool B = false;
    if ( DS->Fields->Fields[ NNV::tvID ]->AsLargeInt == Node->PK )
      B = true;
    if ( !B )
      B = DS->Locate( DS->Fields->Fields[ NNV::tvID ]->FieldName
                    , Node->PK
                    , TLocateOptions() );
    if ( B && NodeAdmin )
      NodeAdmin->ActivePK = DS->Fields->Fields[ NNV::tvID ]->AsLargeInt;
    return B;
  }
  return false;
}

void __fastcall TNNVDBTreeView::SetNodeAdmin( TNNVNodeAdmin *Value )
{
  if ( FNodeAdmin != Value ) {
    FNodeAdmin = Value;

    if ( NodeAdmin ) {
      NodeAdmins->MakeCurrent( NodeAdmin );

      ActiveOrder  = NodeAdmin->LoadOrder;
      ReadOnly     = NodeAdmin->ReadOnly;
      DragDropKind = NodeAdmin->DragDropKind;
      HelpType     = NodeAdmin->HelpType;
      HelpContext  = NodeAdmin->HelpContext;
      HelpKeyword  = NodeAdmin->HelpKeyword;
    } else
      NodeAdmins->Reset();

    DataSource->DataSet = ( NodeAdmin ? NodeAdmin->DataSet : nullptr );
    DoNodeAdminChange( NodeAdmin );
  }
}

void __fastcall TNNVDBTreeView::SetLoadAdmin( TNNVNodeAdmin *Value )
{
  if ( FLoadAdmin != Value ) {
    if ( LoadAdmin )
      LoadAdmin->UnPrepareDataSet();

    FLoadAdmin = Value;

    if ( LoadAdmin )
      LoadAdmin->PrepareDataSet();

    LoadDataSet = ( LoadAdmin ? LoadAdmin->DataSet : nullptr );
  }
}

void __fastcall TNNVDBTreeView::LoadFromFiler( TNNVTextStream *Filer )
{
  inherited::LoadFromFiler( Filer );
  ActiveOrder = Filer->ReadInt();
}

void __fastcall TNNVDBTreeView::SaveToFiler( TNNVTextStream *Filer )
{
  inherited::SaveToFiler( Filer );
  Filer->WriteInt( ActiveOrder );
}

TTreeNode* __fastcall TNNVDBTreeView::CreateNode()
{
  return new TNNVTreeNode( Items );
}

// ------------------------------------------------------
namespace NNV {
  const bool NoLockRecord = false;
  const bool LockRecord = true;
}

// ---------------------------------------------------------------------------
__fastcall TNNVQuery::TNNVQuery( TComponent* Owner )
  : inherited( Owner )
, FFilterMap( this )
{
  CachedUpdates  = false;
  Active         = false;
  FAdminsSet     = new NNV::TSetNodeAdmins();
  FilteredEnable = true;
}

__fastcall TNNVQuery::~TNNVQuery()
{
  delete FAdminsSet;
}

void __fastcall TNNVQuery::DoSetVariableRecord()
{
  if ( FOnSetVariableRecord )
    FOnSetVariableRecord( this );
}

void __fastcall TNNVQuery::RemoveAdmin(TNNVNodeAdmin *aNodeAdmin)
{
  if ( aNodeAdmin && AdminsSet ) {
    NNV::TSetNodeAdmins::iterator i = AdminsSet->find( aNodeAdmin );
    if ( i != AdminsSet->end() )
      AdminsSet->erase(i);
  }
}

void __fastcall TNNVQuery::CWDeleteVariable( const String &VariableName ) {
  TFDParam *p = FindParam( VariableName );
  if ( p )
    Params->Delete( ( *p ).Index );
}

bool __fastcall TNNVQuery::CWSetVariable( const String &VariableName,
    const Variant &Value ) {
  TFDParam *p = FindParam( VariableName );
  bool B = p != nullptr;
  if ( B )
    p->Value = Value;
  return B;
}

TField* __fastcall TNNVQuery::CWFindField( const String &AFieldName, TADTField *AF )
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

void __fastcall TNNVQuery::SaveToFiler( TNNVTextStream *Filer )
{
  Filer->WriteString( FieldSearchName );
  Filer->WriteBool( CachedUpdates );
  MapSearch.SaveToFiler( Filer );
}

void __fastcall TNNVQuery::LoadFromFiler( TNNVTextStream *Filer )
{
  FieldSearchName = Filer->ReadString();
  CachedUpdates = Filer->ReadBool();
  MapSearch.LoadFromFiler( Filer );
}

void __fastcall TNNVQuery::Post() {
  if ( MasterSource ) {
    if ( MasterSource->DataSet ) {
      TNNVQuery *mds = dynamic_cast < TNNVQuery* > ( MasterSource->DataSet );
      if ( mds ) {
        mds->CWCheckBrowseMode();
        if ( mds->CachedUpdates && !CachedUpdates )
          mds->CWApplyUpdates();
      }
    }
  }
  inherited::Post();
}

void __fastcall TNNVQuery::GetUKey( Variant &V, const String &UniqueFields_ ) {
  if ( UniqueFields_.IsEmpty() )
    V = Fields->Fields[ 0 ]->Value;
  else if ( UniqueFields_.Pos( ";" ) == 0 )
    V = FieldByName( UniqueFields_ )->Value;
  else {
    String S;
    char D = ';';
    int N = 1, L = NNV::CharCount( UniqueFields_, ';' ), Bounds[ 2 ];
    Bounds[ 0 ] = 0;
    Bounds[ 1 ] = L;
    V = VarArrayCreate( Bounds, 1, varVariant );
    for ( int i = 0; i <= L; ++i ) {
      S = NNV::GetToken( UniqueFields_, N, D );
      V.PutElement( FieldByName( S )->Value, i );
    }
  }
}

bool __fastcall TNNVQuery::GotoUKey( const Variant &V,
    const String &UniqueFields_ ) {
  if ( Bof && Eof )
    return false;
  if ( UniqueFields_.IsEmpty() )
    return Locate( Fields->Fields[ 0 ]->FieldName, V, TLocateOptions() );
  else
    return Locate( UniqueFields_, V, TLocateOptions() );
}

bool __fastcall TNNVQuery::GotoUKey( const Variant &V ) {
  return GotoUKey( V, CWUniqueFields );
}

void __fastcall TNNVQuery::GetUKey( Variant &V ) {
  GetUKey( V, CWUniqueFields );
}

void __fastcall TNNVQuery::SaveUKey() {
  GetUKey( fUKey );
}

bool __fastcall TNNVQuery::GotoUKey() {
  return GotoUKey( fUKey );
}

void __fastcall TNNVQuery::CWRefresh() {
  if ( !Active )
    return;
  DisableControls();
  try {
    SaveUKey();
    SaveDlg();
    Refresh();

    if ( Active )
      AdminsSet->Refresh();

    GotoUKey();
  }
  __finally {
    EnableControls();
  }
}

void __fastcall TNNVQuery::CWRefreshWithoutTree()
{
  AdminsSet->Enable = false;
  try {
    CWRefresh();
  }
  __finally {
    AdminsSet->Enable = true;
  }
}

void __fastcall TNNVQuery::CWRefreshRecord() {
  if ( !Active )
    return;
  SaveDlg();
  RefreshRecord();
}

void _fastcall TNNVQuery::DoBeforeClose() {
  inherited::DoBeforeClose();
  SaveDlg();
}

void __fastcall TNNVQuery::SetFilteredEnable( bool Value )
{
  if ( FFilteredEnable != Value ) {
    FFilteredEnable = Value;
    if ( !FilteredEnable )
      MapSearch.SearchDlgOptions.IsFilter = false;
  }
}

void __fastcall TNNVQuery::SaveDlg()
{
  if ( CachedUpdates ) {
    CheckBrowseMode();
    if ( UpdatesPending ) {
      unsigned int N = ( Application->Terminated ? MB_SYSTEMMODAL : 0 );
      String S = NNVConst::ToKeepChanges + ( Note.IsEmpty() ? Name : Note );
      if ( Application->MessageBox( S.c_str(), Application->Title.c_str(),
          MB_YESNO + MB_ICONQUESTION + N ) == IDYES ) {
        ApplyUpdates();
        CommitUpdates();
      }
      else
        CancelUpdates();
    }
  }
}

void __fastcall TNNVQuery::SetOrderByColumn( TColumn *Value )
{
  if ( FOrderByColumn != Value ) {
    FOrderByColumn = Value;

    if ( OrderByColumn ) {
      TNNVGridColumn *C = dynamic_cast< TNNVGridColumn* >( OrderByColumn );
      bool B = false;
      TFDMacro *M;
      M = FindMacro( NNVConst::ORDER_BY );

      if ( M ) {
        bool SA = Active;
        SaveUKey();
        Active = false;
        M->Value = C->OrderBy.IsEmpty() ? OrderByDefault : C->OrderBy;
        Active = SA;
        GotoUKey();
      }
    }
  }
}

void __fastcall TNNVQuery::ClearAll()
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

void __fastcall TNNVQuery::CWApplyUpdates() {
  CWCheckBrowseMode();
  TNNVQuery *od = dynamic_cast < TNNVQuery* > ( MasterSource );
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

bool __fastcall TNNVQuery::CheckFields(TVectorOfField &VField ) {
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
    NNVConst::FieldUserChange = ( *i ).first->DisplayLabel;
  return result;
}

bool __fastcall TNNVQuery::CheckFieldsModify( TSetOfField &VField ) {
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

void __fastcall TNNVQuery::SetNewRecord( TVectorOfField &VField ) {
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

long long int __fastcall TNNVQuery::GetNewID( String SQ, TNNVQuery *Query )
{
  long long int result;
  // Query->ClearAll();
  Query->SQL->Text = "select " + SQ + ".nextval res from dual";
  Query->Execute();
  result = Query->Fields->Fields[ 0 ]->AsLargeInt;
  Query->Close();
  return result;
}

void __fastcall TNNVQuery::CWCheckEditMode()
{
  if ( !IsEditModes() )
    Edit();
}

void __fastcall TNNVQuery::CWCheckBrowseMode()
{
  if ( IsEditModes() )
    Post();
}

namespace NNV
{

TSetNodeAdmins::TSetNodeAdmins()
  : inherited()
  , Enable( true )
{
}

void __fastcall TSetNodeAdmins::Refresh()
{
  if ( !Enable )
    return;

  for ( const_iterator i = begin(); i != end(); ++i )
    if ( ( *i )->TreeView && ( *i )->TreeView->IsStartAdmin )
      ( *i )->TreeView->CWReload( *i );
}

bool __fastcall TSetNodeAdmins::DeletePK( long long int PK )
{
  if ( !Enable )
    return false;

  bool B = false;
  for ( const_iterator i = begin(); i != end(); ++i )
    if ( ( *i )->TreeView && ( *i )->TreeView->IsStartAdmin ) {
      TTreeNode *TI = ( *i )->TreeView->FindNodePK( *i, PK );
      if ( TI ) {
        B = B || TI->HasChildren;
        if ( TI->HasChildren )
          ( *i )->TreeView->NavTree.Clear();
        if ( TI->Selected )
          ( *i )->TreeView->Items->Item[ TI->AbsoluteIndex < 1 ? 0 :
            TI->AbsoluteIndex - 1 ]->Selected = true;
        ( *i )->TreeView->NavTree.Remove( TI );
        TI->Delete();
      }
    }
  return B;
}

}

// ---------------------------------------------------
TNNVFilter::TNNVFilter()
{
}

TNNVFilter::~TNNVFilter()
{
  if ( FRegEx ) {
    delete FRegEx;
    FRegEx = nullptr;
  }
}

TNNVFilter::TNNVFilter( bool aEnable
                      , TField *aField
                      , const String &S
                      , const NNV::TSearchOptions &aSearchOptions )
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

TNNVFilter::TNNVFilter( const TFilterRecordEvent &aEvent
                      , bool aEnable )
  : FEventFilter( aEvent )
  , FEnable( aEnable )
{
}

TNNVFilter& TNNVFilter:: operator = ( const TNNVFilter & a )
{
  FFieldFilter   = a.FFieldFilter;
  FStrFilter     = a.FStrFilter;
  FRegEx         = a.FRegEx;
  FEnable        = a.FEnable;
  FSearchOptions = a.FSearchOptions;
  FEventFilter   = a.FEventFilter;

  return *this;
}

TNNVFilter& TNNVFilter:: operator = ( TNNVFilter && a )
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

void __fastcall TNNVFilter::FilterEvent( TDataSet *DataSet, bool &Accept )
{
  if ( EventFilter )
     EventFilter( DataSet, Accept );
}

TNNVFilterMap::TNNVFilterMap( TNNVQuery *DSet )
  : DataSet( DSet )
{
  if ( !DataSet->ComponentState.Contains( csDesigning ) )
    DataSet->OnFilterRecord = FilterEvent;
}

void __fastcall TNNVFilterMap::FilterEvent( TDataSet *DataSet, bool &Accept ) {
  int N = this->size();
  for ( iterator i = this->begin(); i != this->end(); ++i ) {
    if ( ( *i ).second.Enable ) {
      ( *i ).second.FilterEvent( DataSet, Accept );
      if ( !Accept )
        break;
    }
  }
}

void __fastcall TNNVFilterMap::RefreshFilter()
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

void __fastcall TNNVFilterMap::EraseFilterSearch()
{
  bool B = false;

  for ( iterator i = begin(); i != end(); ) {
    if ( (*i).first == NNVConst::DBSearchDialogFilterKey ) {
      i = erase( i );
      B = true;
      break;
    }
    ++i;
  }

  if ( B )
    RefreshFilter();
}

bool __fastcall TNNVFilterMap::IsFilterSearchPresent()
{
  return find( NNVConst::DBSearchDialogFilterKey ) != end();
}

void __fastcall TNNVQuery::CWOpen()
{
  ++FOpenCounter;
  Open();
}

void __fastcall TNNVQuery::CWOpenIf( bool Condition )
{
  ++FOpenCounter;
  if ( Condition )
    Open();
}

void __fastcall TNNVQuery::CWOpenIfClose()
{
  if ( !Active )
    CWOpen();
}

void __fastcall TNNVQuery::CWClose()
{
  if ( --FOpenCounter <= 0 )
    Close();
}

void __fastcall TNNVQuery::CWCloseAlways()
{
  FOpenCounter = 0;
  Close();
}

bool __fastcall TNNVQuery::IsEditModes()
{
  return State == dsEdit || State == dsInsert || State == dsSetKey;
}

bool __fastcall TNNVQuery::CWLocate( const String KeyFields
                                   , const System::Variant &KeyValues )
{
  return Locate( KeyFields, KeyValues, TLocateOptions() );
};

void __fastcall TNNVQuery::CWReopen()
{
  DisableControls();
  try {
    Close();
    Open();
  } __finally {
    EnableControls();
  }
}

void __fastcall TNNVQuery::CWActiveReopen()
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

void __fastcall TNNVQuery::CWReconnectReopen(bool NeedClose_ )
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

void __fastcall TNNVQuery::DoBeforeDelete()
{
  inherited::DoBeforeDelete();
  FDeleteNodePK = Fields->Fields[ NNV::tvID ]->AsLargeInt;
}

void __fastcall TNNVQuery::DoAfterDelete()
{
  inherited::DoAfterDelete();
  if ( AdminsSet->DeletePK( DeleteNodePK ) )
    CWRefreshWithoutTree();
}

void __fastcall TNNVQuery::DoAfterOpen()
{
  inherited::DoAfterOpen();
  AdminsSet->Refresh();
}

void __fastcall TNNVQuery::DeclareAndSetParam( const String &AParam, Variant Value )
{
  TFDParam *P = ParamByName( AParam );
  P->Value = Value;
}

void __fastcall TNNVQuery::SetName( const TComponentName Value )
{
  inherited::SetName( Value );
  FPasteProcedure = DefaultPasteProcedure();
  FMergeProcedure = DefaultMergeProcedure();
}

String __fastcall TNNVQuery::DefaultPasteProcedure()
{
  String R( L"\"Paste" );
  R += Name.SubString( 3, Name.Length() - 2 );
  R += L"\"";
  return R;
}

bool __fastcall TNNVQuery::StoredPasteProcedure()
{
  return FPasteProcedure != DefaultPasteProcedure();
}

String __fastcall TNNVQuery::DefaultMergeProcedure()
{
  String R( L"\"Merge" );
  R += Name.SubString( 3, Name.Length() - 2 );
  R += L"\"";
  return R;
}

bool __fastcall TNNVQuery::StoredMergeProcedure()
{
  return FMergeProcedure != DefaultMergeProcedure();
}

TField* __fastcall TNNVQuery::GetFieldSearch()
{
  return FieldSearchName.IsEmpty() ? nullptr : CWFindField( FieldSearchName );
}

void __fastcall TNNVQuery::PrepareStandartMacros()
{
  TFDMacro *M = FindMacro( NNVConst::PRABHUPADA_SCHEMA );

  if ( M ) {
    if ( Connection )
      M->AsRaw = Connection->Params->Values[ "PrabhupadaSchema" ];
    else
      M->AsRaw = NNVConst::PrabhupadaSchemaDefault;

  }
}

void __fastcall TNNVQuery::DBPaste( NNV::TBufferIntBox &ABufferIntBox, TNNVQuery *QU, TField *F )
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

void __fastcall TNNVQuery::DBMerge( NNV::TBufferIntBox &ABufferIntBox, TNNVQuery *QU, TField *F )
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

__fastcall TNNVTreeNode::TNNVTreeNode( TTreeNodes *AOwner )
  : inherited( AOwner )
  , NodeAdmin( nullptr )
  , PK( NNV::EmptyPK )
{
}

TNNVNodeParams::TNNVNodeParams()
  : ImageIndex( -1 )
  , SelectedIndex( -1 )
{
}

void __fastcall TNNVNodeParams::Clear()
{
  Text = "";
  ImageIndex = -1;
  SelectedIndex = -1;
}

TNNVFieldUpdate::TNNVFieldUpdate()
  : Obligatory( false )
  , Field( nullptr )
{
}

TNNVFieldUpdate::TNNVFieldUpdate( TField *aField )
  : Obligatory( false )
  , Field( aField )
{
}

TNNVFieldUpdate::TNNVFieldUpdate( bool aObligatory
                                , TField *aField )
  : Obligatory( aObligatory )
  , Field( aField )
{
}

void __fastcall TNNVDBTreeView::Notification( TComponent *AComponent, TOperation Operation )
{
  inherited::Notification( AComponent, Operation );
  if ( Operation == opRemove ) {
    if ( AComponent == EditKindID )
      EditKindID = nullptr;
    else if ( NodeAdmins ) {
      if ( !ComponentState.Contains( csDesigning ) ) {
        TNNVNodeAdmin *na = dynamic_cast<TNNVNodeAdmin*>(AComponent);
        if ( na != nullptr ) {
          NNV::TNodeAdmins::iterator i = NodeAdmins->FindCache( na );
          if ( i != NodeAdmins->end() ) {
            if ( (*i).first == NodeAdmin )
              NodeAdmin = nullptr;
            NodeAdmins->erase( i );
            NodeAdmins->ResetCache();
          }
        }
      }
    }
  }
}

__fastcall TNNVGridColumn::TNNVGridColumn( TCollection *Collection )
  : inherited( Collection )
  , fIsFiltered( true )
{
  Color       = clWindow;
  Font->Color = clWindowText;
}

void __fastcall TNNVGridColumn::SetDialog( TNNVDialog *Value )
{
  if ( FDialog != Value ) {
    FDialog = Value;
    if ( Dialog )
      Dialog->FreeNotification( Grid );
  }
}

__fastcall TNNVDBGrid::TNNVDBGrid( TComponent* Owner )
  : inherited( Owner )
  , fAutoFieldSearch( true )
  , fForceFocusRect( true )
{
}

void __fastcall TNNVDBGrid::ColEnter()
{
  inherited::ColEnter();
  SetFieldSearchName();
}

void __fastcall TNNVDBGrid::SelectRows( NNV::TSelectedFunction ASelectedFunction )
{
  if (!( Options.Contains( dgMultiSelect) && DataLink->Active ) )
    return;

  TDataSet *DSet = DataSource->DataSet;
  TBookmark B = DSet->Bookmark;
  DSet->DisableControls();
  try {
    SelectedRows->Clear();
    DSet->First();
    while ( !DSet->Eof ) {
      if ( ASelectedFunction() )
        SelectedRows->CurrentRowSelected = true;
      DSet->MoveBy(1);
    }
  } __finally {
    DSet->Bookmark = B;
    DSet->EnableControls();
  }
}

void __fastcall TNNVDBGrid::Notification( TComponent *AComponent, TOperation Operation )
{
  inherited::Notification( AComponent, Operation );
  if ( Operation == opRemove && !ComponentState.Contains( csDestroying ) ) {
    TNNVGridColumn *cl;
    for ( int i = 0; i < Columns->Count; ++i ) {
      cl = dynamic_cast< TNNVGridColumn* >( Columns->Items[ i ] );
      if ( cl->Dialog == AComponent )
        cl->FDialog = nullptr;
    }
  }
}

void __fastcall TNNVDBGrid::SetFieldSearchName()
{
  if ( AutoFieldSearch && DataSource && DataSource->DataSet &&
      ( SelectedIndex != -1 ) ) {
    TNNVGridColumn *c = (TNNVGridColumn*)( Columns->Items[ SelectedIndex ] );
    TNNVQuery *qu = dynamic_cast< TNNVQuery* >( DataSource->DataSet );

    if ( qu && c->IsFiltered )
      qu->FieldSearchName = SelectedField->FieldName;
  }
}

void __fastcall TNNVDBGrid::ClearAll()
{
  DataSource        = nullptr;
  Tag               = 0;
  OnCellClick       = nullptr;
  OnColEnter        = nullptr;
  OnColExit         = nullptr;
  OnColumnMoved     = nullptr;
  OnDblClick        = nullptr;
  OnDragDrop        = nullptr;
  OnDragOver        = nullptr;
  OnDrawColumnCell  = nullptr;
  OnDrawDataCell    = nullptr;
  OnEditButtonClick = nullptr;
  OnEndDrag         = nullptr;
  OnEnter           = nullptr;
  OnExit            = nullptr;
  OnKeyDown         = nullptr;
  OnKeyPress        = nullptr;
  OnKeyUp           = nullptr;
  OnStartDrag       = nullptr;
  OnTitleClick      = nullptr;
}

TColumn* __fastcall TNNVDBGrid::FieldNameToColumn( const String &S )
{
  TColumn* result = NULL;
  for ( int i = 0; i < Columns->Count; ++i )
    if ( Columns->Items[ i ]->FieldName == S ) {
      result = Columns->Items[ i ];
      break;
    }
  return result;
}

void __fastcall TNNVDBGrid::LoadFromFiler( TNNVTextStream *Filer)
{
  TColumn *C;
  std::unique_ptr< TFont > afc( new TFont() ), aft( new TFont() );

  int CWidth, CIndex;
  bool CVisible;
  String CPickList, CTitleCaption;
  TColor CColor, CTitleColor;

  Filer->ReadFont( Font );
  Color = Filer->ReadColor();

  TDBGridOptions Opt = Options;
  if ( Filer->ReadBool() )
    Opt = Opt << dgTitles;
  else
    Opt = Opt >> dgTitles;
  if ( Filer->ReadBool() )
    Opt = Opt << dgConfirmDelete;
  else
    Opt = Opt >> dgConfirmDelete;
  if ( Filer->ReadBool() )
    Opt = Opt << dgRowLines;
  else
    Opt = Opt >> dgRowLines;
  if ( Filer->ReadBool() )
    Opt = Opt << dgColLines;
  else
    Opt = Opt >> dgColLines;
  if ( Filer->ReadBool() )
    Opt = Opt << dgTabs;
  else
    Opt = Opt >> dgTabs;

  Options = Opt;

  int N = Filer->ReadInt();
  for ( int i = 0; i < N; ++i )
  {
    C = FieldNameToColumn( Filer->ReadString() );

    CWidth = Filer->ReadInt();
    CIndex = Filer->ReadInt();
    CVisible = Filer->ReadBool();
    CPickList = Filer->ReadString();

    CTitleCaption = Filer->ReadString();
    CColor = Filer->ReadColor();
    CTitleColor = Filer->ReadColor();
    Filer->ReadFont( afc.get() );
    Filer->ReadFont( aft.get() );

    if ( C ) {
      C->Width          = CWidth;
      C->Index          = CIndex;
      C->Visible        = CVisible;
      C->PickList->Text = CPickList;
      C->Title->Caption = CTitleCaption;
      C->Color          = CColor;
      C->Title->Color   = CTitleColor;

      C->Font->Assign( afc.get() );
      C->Title->Font->Assign( aft.get() );
    }
  }
}

void __fastcall TNNVDBGrid::SaveToFiler( TNNVTextStream *Filer )
{
  Filer->WriteFont( Font );
  Filer->WriteColor( Color );

  Filer->WriteBool( Options.Contains( dgTitles ) );
  Filer->WriteBool( Options.Contains( dgConfirmDelete ) );
  Filer->WriteBool( Options.Contains( dgRowLines ) );
  Filer->WriteBool( Options.Contains( dgColLines ) );
  Filer->WriteBool( Options.Contains( dgTabs ) );

  int N = Columns->Count;
  Filer->WriteInt( N );
  TColumn *C;
  for ( int i = 0; i < N; ++i ) {
    C = Columns->Items[ i ];
    Filer->WriteString( C->FieldName );
    Filer->WriteInt( C->Width );
    Filer->WriteInt( C->Index );
    Filer->WriteBool( C->Visible );
    Filer->WriteString( C->PickList->Text );
    Filer->WriteString( C->Title->Caption );
    Filer->WriteColor( C->Color );
    Filer->WriteColor( C->Title->Color );
    Filer->WriteFont( C->Font );
    Filer->WriteFont( C->Title->Font );
  }
}

void __fastcall TNNVDBGrid::CWSelect( TField *AFieldPK
                                    , NNV::TBufferIntBox *ABufferIntBox
                                    , bool AIsCut )
{
  if ( !DataSource || !DataSource->DataSet || !AFieldPK  )
    return;

  TNNVQuery *qu = dynamic_cast< TNNVQuery* >( DataSource->DataSet );

  TBookmark B = qu->Bookmark;

  ABufferIntBox->IsCut = AIsCut;
  ABufferIntBox->Label = qu;

  int L = SelectedRows->Count;
  qu->DisableControls();
  try {
    ABufferIntBox->VectorID.clear();
    ABufferIntBox->VectorID.reserve( L );
    for ( int i = 0; i < L; ++i ) {
      qu->Bookmark = SelectedRows->Items[ i ];
      ABufferIntBox->VectorID.push_back( AFieldPK->AsLargeInt );
    }
    qu->Bookmark = B;
  } __finally {
    qu->EnableControls();
  }
}

void __fastcall TNNVDBGrid::KeyDown( Word &Key, TShiftState Shift )
{
  switch ( Key ) {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    if ( Shift.Contains( ssCtrl ) ) {
      if ( Shift.Contains( ssShift ) ) {
        if ( DataSource && DataSource->DataSet )
          fDSetBookmarks[ Key ] =
              NNV::TDSetBookmark( dynamic_cast< TNNVQuery* >( DataSource->DataSet ) );
      }
      else
        fDSetBookmarks.GoTo( Key );
      Key = 0;
    }
    break;
  }
  if ( Key )
    inherited::KeyDown( Key, Shift );
}

TDBGridColumns* __fastcall TNNVDBGrid::CreateColumns()
{
  return new TDBGridColumns( this, __classid( TNNVGridColumn ) );
}

void __fastcall TNNVDBGrid::CWCheckSelect()
{
  if ( SelectedRows->Count == 0 )
    throw Exception( L"Не выбраны строки в таблице " + Name );
}

TColumn* __fastcall TNNVDBGrid::CWFindColumn( TField *Field_ )
{
  TColumn *c;
  int N = Columns->Count;
  for ( int i = 0; i < N; ++i ) {
    c = Columns->Items[ i ];
    if ( c->Field == Field_ )
      return c;
  }
  return nullptr;
}

void __fastcall TNNVDBGrid::DrawColumnCell( const Types::TRect &Rect
                                          , int DataCol
                                          , TColumn* Column
                                          , Grids::TGridDrawState State )
{
  inherited::DrawColumnCell( Rect, DataCol, Column, State );

  if ( State.Contains( gdFocused ) ) {
    TPoint P;
    P = ClientToScreen( Point( Rect.Left, Rect.Top ) );
    fCWRect = Bounds( P.x, P.y, Rect.Right - Rect.Left, Rect.Bottom - Rect.Top );
  }
}

bool __fastcall TNNVDBGrid::IsCurrentSelected()
{
  int Index;
  return Options.Contains(dgMultiSelect)
      && DataLink->Active && SelectedRows->Find
      (DataLink->DataSource->DataSet->Bookmark, Index);
}

void __fastcall TNNVDBGrid::CWSelectAll()
{
  if (!(Options.Contains(dgMultiSelect) && DataLink->Active))
    return;
  TDataSet *DSet = DataSource->DataSet;
  TBookmark B = DSet->Bookmark;
  DSet->DisableControls();
  try {
    SelectedRows->Clear();
    DSet->First();
    while (!DSet->Eof) {
      SelectedRows->CurrentRowSelected = true;
      DSet->MoveBy(1);
    }
  } __finally {
    DSet->Bookmark = B;
    DSet->EnableControls();
  }
}

void __fastcall TNNVDBGrid::CWFieldResize( TField *f, int WidthAdd )
{
  TColumn *c = CWFindColumn(f);
  if ( c )
    c->Width = ClientWidth - WidthAdd - 20;
}

void __fastcall TNNVDBGrid::SetComboItems( TCustomCombo *cc, TField *f )
{
  TColumn *cl = CWFindColumn( f );
  if ( cl )
    cc->Items->Assign( cl->PickList );
}

int __fastcall TNNVDBGrid::GetVisibleCount()
{
  TColumn *c;
  int R = 0, N = Columns->Count;
  for ( int i = 0; i < N; ++i ) {
    c = Columns->Items[ i ];
    if ( c->Visible )
      ++R;
  }
  return R;
}

void __fastcall TNNVDBGrid::ShowPropertyDialog()
{
  NNV::FormCreate( __classid( TfmvDBGrid ), &fmvDBGrid );
  fmvDBGrid->Execute( this );
}

void __fastcall TNNVDBGrid::DoDBCut()
{
  if ( FOnDBCut )
    FOnDBCut( this );
}

void __fastcall TNNVDBGrid::DoDBCopy()
{
  if ( FOnDBCopy )
    FOnDBCopy( this );
}

void __fastcall TNNVDBGrid::DoDBPaste()
{
  if ( FOnDBPaste )
    FOnDBPaste( this );
}

void __fastcall TNNVDBGrid::DoDBMerge()
{
  if ( FOnDBMerge )
    FOnDBMerge( this );
}

void __fastcall TNNVDBGrid::DBCut()
{
  DoDBCut();
}

void __fastcall TNNVDBGrid::DBCopy()
{
  DoDBCopy();
}

void __fastcall TNNVDBGrid::DBPaste()
{
  DoDBPaste();
}

void __fastcall TNNVDBGrid::DBMerge()
{
  DoDBMerge();
}

TNNVQuery* __fastcall TNNVDBGrid::GetQuery()
{
  if ( DataSource && DataSource->DataSet ) {
    TNNVQuery *qu = dynamic_cast< TNNVQuery* >( DataSource->DataSet );
    return qu;
  } else
    return nullptr;
}

__fastcall TNNVDBSearchDialog::TNNVDBSearchDialog( TComponent* Owner )
  : inherited( Owner )
, FLimitHistory( NNV::CW_LIMIT_HISTORY )
{
}

__fastcall TNNVDBSearchDialog::~TNNVDBSearchDialog()
{
}

void __fastcall TNNVDBSearchDialog::Notification( TComponent *AComponent
                                                , TOperation Operation )
{
  inherited::Notification( AComponent, Operation );
  if ( Operation == opRemove ) {
    if ( AComponent == DataSource )
      fDataSource = nullptr;
    else if ( AComponent == QuickScrollBox )
      FQuickScrollBox = nullptr;
  }
}

void __fastcall TNNVDBSearchDialog::SetDataSource(TDataSource *Value)
{
  if ( fDataSource != Value ) {
    fDataSource = Value;
    if ( DataSource )
      DataSource->FreeNotification( this );
  }
}

void __fastcall TNNVDBSearchDialog::SetOptions( TField *AFieldSearch, TScrollBox *AScrollBox )
{
  TNNVQuery *qu = Query;
  if ( !qu )
    return;
  bool AIsQuick = AScrollBox == QuickScrollBox;

  if ( !AIsQuick )
    fmvSearch->SearchDlgOptions = qu->MapSearch.SearchDlgOptions;

  if ( AFieldSearch ) {
    TWinControl *CTR, *AC;

    int L = AScrollBox->ComponentCount;
    for ( int I = 0; I < L; ++I ) {
      CTR = dynamic_cast< TWinControl* >( AScrollBox->Components[ I ] );
      if ( CTR && CTR->Tag == NativeInt( AFieldSearch ) ) {
        TfrvDiapazon *fr = dynamic_cast< TfrvDiapazon* >( CTR );
        AC = fr ? fr->BeginControl : CTR;
        TCustomForm *fm = dynamic_cast< TCustomForm* >( AScrollBox->Owner );
        if ( AIsQuick )
          AC->SetFocus();
        else {
          fm->ActiveControl = AC;
          AScrollBox->VertScrollBar->Position = 0;
          AScrollBox->VertScrollBar->Position = CTR->Top - 2;
        }
        break;
      }
    }
  }
}

void __fastcall TNNVDBSearchDialog::PrepareSkip( bool AIsQuick )
{
  TNNVQuery *qu = Query;
  if ( !qu )
    return;

  TControl *cn;
  TComboBox *cb;
  TComponent *CPN;
  NNV::TMapSearch::iterator J;
  TField *F;
  String S;
  TfrvPeriod *frPeriod;
  TfrvShortIntDiapazon *frShortIntDiapazon;
  TfrvIntDiapazon *frIntDiapazon;
  TfrvLongLongIntDiapazon *frLongLongIntDiapazon;
  TfrvDoubleDiapazon *frDoubleDiapazon;

  TScrollBox *SB = AIsQuick ? QuickScrollBox : fmvSearch->sbSkip;

  TRegExOptions RO;
  RO = RO << roMultiLine;
  if ( !qu->MapSearch.SearchDlgOptions.SearchOptions.CaseSensitive )
    RO = RO << roIgnoreCase;

  int L = SB->ComponentCount;
  if ( !AIsQuick ) {
    qu->MapSearch.VectorSearch.clear();
    qu->MapSearch.VectorSearch.reserve( L );
  }

  for ( int I = 0; I < L; ++I ) {
    CPN = SB->Components[ I ];
    cn = dynamic_cast< TControl* >( CPN );
    if ( !cn )
      continue;
    // В тэге хранится поле!
    F = (TField*)cn->Tag;
    assert( F != nullptr );

    J = qu->MapSearch.Find( F );
    assert( J != qu->MapSearch.end() );

    cb = dynamic_cast< TComboBox* >( cn );
    if ( cb ) {
      if ( cb->Style == csDropDownList ) {
        (*J).NeedSet = cb->ItemIndex != (int)NNV::TBoolExtended::Any;
        (*J).SearchValue.Bool         = (NNV::TBoolExtended)cb->ItemIndex;
        qu->MapSearch.AddVectorSearch( J, (*J).NeedSet );
      } else {
        S = cb->Text;
        (*J).NeedSet = !S.IsEmpty();
        (*J).SearchValue.StringValue = S;
        if ( (*J).SearchValue.RegEx ) {
          delete (*J).SearchValue.RegEx;
          (*J).SearchValue.RegEx = nullptr;
        }
        if ( qu->MapSearch.SearchDlgOptions.SearchOptions.IsRegularExpression )
          (*J).SearchValue.RegEx = new TRegEx( S, RO );
        NNV::SaveComboBox( cb, LimitHistory );
        qu->MapSearch.AddVectorSearch( J, (*J).NeedSet );
        (*J).SearchValue.StringHistory = cb->Items->Text;
      }
    } else {
      frPeriod = dynamic_cast< TfrvPeriod* >( CPN );
      if ( frPeriod ) {
        frPeriod->aApplyDiapazon->Execute();
        (*J).NeedSet            = !frPeriod->IsEmpty;
        (*J).SearchValue.Period =  frPeriod->Period;
        qu->MapSearch.AddVectorSearch( J, (*J).NeedSet );
      } else {
        frShortIntDiapazon = dynamic_cast< TfrvShortIntDiapazon* >( CPN );
        if ( frShortIntDiapazon ) {
          frShortIntDiapazon->aApplyDiapazon->Execute();
          (*J).NeedSet                      = !frShortIntDiapazon->IsEmpty;
          (*J).SearchValue.ShortIntDiapazon =  frShortIntDiapazon->ShortIntDiapazon;
          qu->MapSearch.AddVectorSearch( J, (*J).NeedSet );
        } else {
          frIntDiapazon = dynamic_cast< TfrvIntDiapazon* >( CPN );
          if ( frIntDiapazon ) {
            frIntDiapazon->aApplyDiapazon->Execute();
            (*J).NeedSet                 = !frIntDiapazon->IsEmpty;
            (*J).SearchValue.IntDiapazon =  frIntDiapazon->IntDiapazon;
            qu->MapSearch.AddVectorSearch( J, (*J).NeedSet );
          } else {
            frLongLongIntDiapazon = dynamic_cast< TfrvLongLongIntDiapazon* >( CPN );
            if ( frLongLongIntDiapazon ) {
              frLongLongIntDiapazon->aApplyDiapazon->Execute();
              (*J).NeedSet                         = !frLongLongIntDiapazon->IsEmpty;
              (*J).SearchValue.LongLongIntDiapazon =  frLongLongIntDiapazon->LongLongIntDiapazon;
              qu->MapSearch.AddVectorSearch( J, (*J).NeedSet );
            } else {
              frDoubleDiapazon = dynamic_cast< TfrvDoubleDiapazon* >( CPN );
              if ( frDoubleDiapazon ) {
                frDoubleDiapazon->aApplyDiapazon->Execute();
                (*J).NeedSet                    = !frDoubleDiapazon->IsEmpty;
                (*J).SearchValue.DoubleDiapazon =  frDoubleDiapazon->DoubleDiapazon;
                qu->MapSearch.AddVectorSearch( J, (*J).NeedSet );
              }
            }
          }
        }
      }
    }
  }
}

void __fastcall TNNVDBSearchDialog::SaveOptions()
{
  if ( IsSaveOptions )
    return;

  TNNVQuery *qu = Query;
  qu->MapSearch.SearchDlgOptions      = fmvSearch->SearchDlgOptions;

  IsSaveOptions = true;
}

bool __fastcall TNNVDBSearchDialog::CheckActive()
{
  if ( !Query )
    return false;
  if ( !Query->Active )
    return false;
  Query->CheckBrowseMode();
  return true;
}

void __fastcall TNNVDBSearchDialog::SearchSkipNext()
{
  TNNVQuery *qu = Query;

  TNNVFilterMap::iterator ID = qu->FilterMap.find( NNVConst::DBSearchDialogFilterKey );
  if ( ID != qu->FilterMap.end() ) {
    qu->FilterMap.erase( NNVConst::DBSearchDialogFilterKey );
    qu->FilterMap.RefreshFilter();
  }

  if ( qu->MapSearch.VectorSearch.size() == 0 ) {
    Dialogs::MessageDlg( NNVConst::AttemptSearchEmpty, mtError, TMsgDlgButtons() << mbOK, 0 );
    return;
  }

  int TrueSearch;

  FGoStart = true;
  FReset = false;

  TBookmark AStartBookmark = qu->Bookmark;
  qu->DisableControls();
  try {
    if ( qu->MapSearch.SearchDlgOptions.StartIsBegin && !qu->MapSearch.SearchDlgOptions.Backward && IsExecute )
      qu->First();

    if ( !IsExecute ) {
      if ( qu->MapSearch.SearchDlgOptions.Backward )
        qu->MoveBy( -1 );
      else
        qu->MoveBy( 1 );
    }

    while ( !( qu->MapSearch.SearchDlgOptions.Backward ? qu->Bof : qu->Eof ) ) {
      TrueSearch = 0;

      for ( NNV::TMapSearch::TVectorSearch::iterator i = qu->MapSearch.VectorSearch.begin(); i != qu->MapSearch.VectorSearch.end(); ++i ) {

        if ( CompareRecord( qu, i ) ) {
          ++TrueSearch;
          if ( !qu->MapSearch.SearchDlgOptions.IsAND )
            break;
        }
      }
      if ( ( TrueSearch == qu->MapSearch.VectorSearch.size() ) ||
           ( ( TrueSearch == 1 ) && !qu->MapSearch.SearchDlgOptions.IsAND ) ) {
        FGoStart = false;
        break;
      }

      Application->ProcessMessages();

      if ( FReset )
        break;
      if ( qu->MapSearch.SearchDlgOptions.Backward )
        qu->MoveBy( -1 );
      else
        qu->MoveBy( 1 );
    }

    if ( FGoStart ) {
      qu->Bookmark = AStartBookmark;
      if ( !FReset)
        Dialogs::MessageDlg( NNVConst::RecordNotFind, mtInformation, TMsgDlgButtons() << mbOK, 0 );
    }
  } __finally {
    qu->EnableControls();
  }
}

void __fastcall TNNVDBSearchDialog::DialogFilter( TDataSet* ADataSet, bool &Accept )
{
  TNNVQuery *qu = dynamic_cast< TNNVQuery* >( ADataSet );
  if ( !qu )
    return;

  int TrueSearch = 0;

  for ( NNV::TMapSearch::TVectorSearch::iterator i = qu->MapSearch.VectorSearch.begin(); i != qu->MapSearch.VectorSearch.end(); ++i ) {
    if ( CompareRecord( qu, i ) ) {
      ++TrueSearch;
      if ( !qu->MapSearch.SearchDlgOptions.IsAND )
        break;
    }
  }

  if ( ( TrueSearch == qu->MapSearch.VectorSearch.size() ) ||
       ( ( TrueSearch == 1 ) && !qu->MapSearch.SearchDlgOptions.IsAND ) )
    Accept = true;
  else
    Accept = false;
}

void __fastcall TNNVDBSearchDialog::SearchSkipFilter()
{
  TNNVQuery *qu = Query;

  if ( qu->MapSearch.VectorSearch.size() == 0 )
    qu->FilterMap.erase( NNVConst::DBSearchDialogFilterKey );
  else
    qu->FilterMap[ NNVConst::DBSearchDialogFilterKey ] = TNNVFilter( DialogFilter, true );

  qu->FilterMap.RefreshFilter();
}

bool __fastcall TNNVDBSearchDialog::CompareRecord( TNNVQuery *qu, NNV::TMapSearch::TVectorSearch::iterator i )
{
  bool B = false;

  switch ( (*(*i)).Field->DataType ) {
  case ftBoolean :
    B = NNV::CompareBool( (*(*i)).SearchValue.Bool, (*(*i)).Field );
    break;
  case ftFloat :
    B = (*(*i)).SearchValue.DoubleDiapazon.Check( (*(*i)).Field );
    break;
  case ftSmallint :
    B = (*(*i)).SearchValue.ShortIntDiapazon.Check( (*(*i)).Field );
    break;
  case ftInteger :
    B = (*(*i)).SearchValue.IntDiapazon.Check( (*(*i)).Field );
    break;
  case ftLargeint :
    B = (*(*i)).SearchValue.LongLongIntDiapazon.Check( (*(*i)).Field );
    break;
  case ftWideString :
    if ( qu->MapSearch.SearchDlgOptions.SearchOptions.IsRegularExpression ) {
      B = (*(*i)).SearchValue.RegEx->IsMatch( (*(*i)).Field->DisplayText );
      if ( qu->MapSearch.SearchDlgOptions.SearchOptions.NotThis )
        B = !B;
    } else
      B = NNV::Compare( (*(*i)).SearchValue.StringValue, (*(*i)).Field->DisplayText, qu->MapSearch.SearchDlgOptions.SearchOptions );
    break;
  case ftDate :
  case ftDateTime :
  case ftTimeStamp :
    B = (*(*i)).SearchValue.Period.Check( (*(*i)).Field );
    break;
  default :
    if ( qu->MapSearch.SearchDlgOptions.SearchOptions.IsRegularExpression ) {
      B = (*(*i)).SearchValue.RegEx->IsMatch( (*(*i)).Field->DisplayText );
      if ( qu->MapSearch.SearchDlgOptions.SearchOptions.NotThis )
        B = !B;
    } else
      B = NNV::Compare( (*(*i)).SearchValue.StringValue, (*(*i)).Field->DisplayText, qu->MapSearch.SearchDlgOptions.SearchOptions );
    break;
  }

  return B;
}

void __fastcall TNNVDBSearchDialog::ResetSearch()
{
  FReset = true;
}

TNNVQuery* __fastcall TNNVDBSearchDialog::GetQuery()
{
  if ( DataSource )
    return dynamic_cast< TNNVQuery* >( DataSource->DataSet );
  else
    return nullptr;
}

void __fastcall TNNVDBSearchDialog::Execute( TComponent *SenderForm )
{
  if ( !CheckActive() )
    return;
  fmvSearch = new TfmvSearch( this );

  fmvSearch->rgFilterSearch->Enabled = Query->FilteredEnable;
  fmvSearch->fbRes->OnPrepare        = PrepareSearch;
  fmvSearch->fbRes->OnExecute        = ExecuteSearch;
  fmvSearch->fbRes->OnUnPrepare      = UnPrepareSearch;

  IsSaveOptions = false;

  fmvSearch->ShowDialog( SenderForm );
}

void __fastcall TNNVDBSearchDialog::ExecuteQuick()
{
  if ( !CheckActive() )
    return;
  ForPrepareSearch( QuickScrollBox );
}

void __fastcall TNNVDBSearchDialog::SetQuickScrollBox( TScrollBox *Value )
{
  if ( FQuickScrollBox != Value ) {
    FQuickScrollBox = Value;
    if ( QuickScrollBox )
      QuickScrollBox->FreeNotification( this );
  }
}

void __fastcall TNNVDBSearchDialog::ForPrepareSearch( TScrollBox *AScrollBox )
{
  TNNVQuery *qu = Query;

  if ( !qu )
    return;

  TField *AFieldSearch = qu->FieldSearch;
  if ( AFieldSearch == nullptr )
    return;

  bool AIsQuick = AScrollBox == QuickScrollBox;
  int I, TopSkip = 0, NS = 0;
  // выкрутасы с SBW нужны только потому, что fmvSearch->sbSkip не успевает вовремя поменять свою ширину по свойству Align == alClient
  int SBW = AIsQuick ? AScrollBox->Width : AScrollBox->Parent->Width;
  int AWidthComboBox = SBW - 2 * NNV::SD_LEFTPOS - NNV::SD_LABEL_WIDTH - NNV::SD_SCROLLBAR_WIDTH;

  if ( AIsQuick ) {
    NNV::ClearScrollBox( AScrollBox );
    NewLabelCombo( TopSkip, AFieldSearch, NS, AWidthComboBox, AScrollBox, L"" );
  } else {
    TField *F;
    int FC = qu->FieldCount;
    for ( I = 0; I < FC; ++I ) {
      F = qu->Fields->Fields[ I ];
      if ( ( !UseHide ) && ( !F->Visible ) )
        continue;
      NewLabelCombo( TopSkip, F, NS, AWidthComboBox, AScrollBox, L"" );
    }
  }
  SetOptions( AFieldSearch, AScrollBox );
}

void __fastcall TNNVDBSearchDialog::PrepareSearch( TObject *Sender )
{
  ForPrepareSearch( fmvSearch->sbSkip );
}

void __fastcall TNNVDBSearchDialog::ExecuteSearch( TObject *Sender )
{
  TNNVQuery *qu = Query;
  bool AIsQuick = Sender == nullptr;

  IsExecute = true;
  if ( !AIsQuick )
    SaveOptions();
  PrepareSkip( AIsQuick );

  if ( qu->MapSearch.SearchDlgOptions.IsFilter )
    SearchFilter();
  else
    SearchNext();

  DoExecute();
  IsExecute = false;
}

void __fastcall TNNVDBSearchDialog::UnPrepareSearch( TObject *Sender )
{
  SaveOptions();
}

void __fastcall TNNVDBSearchDialog::PrepareBoolComboBox( TComboBox *cb )
{
  cb->Style = csDropDownList;

  cb->Items->Add( L"Ложь" );
  cb->Items->Add( L"Истина" );
  cb->Items->Add( L"Пусто" );
  cb->Items->Add( L"Не пусто" );
  cb->Items->Add( L"Любое" );

  cb->ItemIndex = (int)NNV::TBoolExtended::Any;
}

void __fastcall TNNVDBSearchDialog::NewLabelCombo( int &TopSkip
                                                 , TField *ASearchField
                                                 , int &NS
                                                 , const int AWidthComboBox
                                                 , TScrollBox *AScrollBox
                                                 , const String &APrefixLabel )
{
  TNNVQuery *qu = Query;
  int I, FC;
  TADTField *F;
  TEdit *la;
  TWinControl *TempControl = nullptr;
  TfrvPeriod *fr;
  TComboBox *cb = nullptr;
  bool IsBool = false;

  la           = new TEdit( AScrollBox->Owner );
  NNV::SetNameToComponent( la, NS );
  la->Text     = APrefixLabel + ASearchField->DisplayLabel;
  la->ReadOnly = true;
  la->TabStop  = false;
  la->Parent   = AScrollBox;
  la->Top      = TopSkip;
  la->Left     = NNV::SD_LEFTPOS;
  la->Width    = NNV::SD_LABEL_WIDTH;

  TField *SearchField;
  switch ( ASearchField->DataType ) {
  case ftBoolean :
    cb          = new TComboBox( AScrollBox );
    TempControl = cb;
    IsBool      = true;
    break;
  case ftFloat :
    TempControl = new TfrvDoubleDiapazon( AScrollBox );
    break;
  case ftSmallint :
    TempControl = new TfrvShortIntDiapazon( AScrollBox );
    break;
  case ftInteger :
    TempControl = new TfrvIntDiapazon( AScrollBox );
    break;
  case ftLargeint :
    TempControl = new TfrvLongLongIntDiapazon( AScrollBox );
    break;
  case ftWideString :
    cb          = new TComboBox( AScrollBox );
    TempControl = cb;
    break;
  case ftDate :
    fr          = new TfrvPeriod( AScrollBox );
    TempControl = fr;
    fr->NeedTime = false;
    break;
  case ftDateTime :
  case ftTimeStamp :
    TempControl = new TfrvPeriod( AScrollBox );
    break;
  case ftADT :
    F = dynamic_cast< TADTField* >( ASearchField );
    FC = F->FieldCount;
    for ( I = 0; I < FC; ++I ) {
      //++NS;
      SearchField = F->Fields->Fields[ I ];
      NewLabelCombo( TopSkip
                   , SearchField
                   , NS
                   , AWidthComboBox
                   , AScrollBox
                   , F->DisplayLabel + L"." );
    }
    break;
  default :
    cb = new TComboBox( AScrollBox );
    TempControl = cb;
    break;
  }

  if ( TempControl ) {
    NNV::SetNameToComponent( TempControl, ASearchField, NS );
    TempControl->Tag     = NativeInt( ASearchField );
    TempControl->Parent  = AScrollBox;
    TempControl->Top     = TopSkip;
    TempControl->Left    = la->Left + la->Width + NNV::SD_LEFTPOS;

    TopSkip += std::max( TempControl->Height, la->Height ) + 2;
  }

  if ( cb ) {
    if ( IsBool )
      PrepareBoolComboBox( cb );
    else {
      cb->Text = L"";
      cb->Width   = AWidthComboBox;
      cb->Anchors = cb->Anchors << akRight;
    }
  }

  if ( TempControl ) {
    NNV::TMapSearch::iterator I = qu->MapSearch.FindLike( ASearchField );
    if ( I != qu->MapSearch.end() ) {
      (*I).Field = ASearchField;
      SetSearchValueToControl( TempControl, I );
    } else
      qu->MapSearch.Add( ASearchField );
  }
}

void __fastcall TNNVDBSearchDialog::SetSearchValueToControl( TControl *TempControl, NNV::TMapSearch::iterator I )
{
  TComboBox *cb;
  TfrvPeriod *frPeriod;
  TfrvShortIntDiapazon *frShortIntDiapazon;
  TfrvIntDiapazon *frIntDiapazon;
  TfrvLongLongIntDiapazon *frLongLongIntDiapazon;
  TfrvDoubleDiapazon *frDoubleDiapazon;

  switch ( (*I).Field->DataType ) {
  case ftBoolean :
    cb = dynamic_cast< TComboBox* >( TempControl );
    if ( (*I).NeedSet )
      cb->ItemIndex = (int)(*I).SearchValue.Bool;
    break;
  case ftFloat :
    frDoubleDiapazon = dynamic_cast< TfrvDoubleDiapazon* >( TempControl );
    if ( (*I).NeedSet )
      frDoubleDiapazon->DoubleDiapazon = (*I).SearchValue.DoubleDiapazon;
    break;
  case ftSmallint :
    frShortIntDiapazon = dynamic_cast< TfrvShortIntDiapazon* >( TempControl );
    if ( (*I).NeedSet )
      frShortIntDiapazon->ShortIntDiapazon = (*I).SearchValue.ShortIntDiapazon;
    break;
  case ftInteger :
    frIntDiapazon = dynamic_cast< TfrvIntDiapazon* >( TempControl );
    if ( (*I).NeedSet )
      frIntDiapazon->IntDiapazon = (*I).SearchValue.IntDiapazon;
    break;
  case ftLargeint :
    frLongLongIntDiapazon = dynamic_cast< TfrvLongLongIntDiapazon* >( TempControl );
    if ( (*I).NeedSet )
      frLongLongIntDiapazon->LongLongIntDiapazon = (*I).SearchValue.LongLongIntDiapazon;
    break;
  case ftWideString :
    cb = dynamic_cast< TComboBox* >( TempControl );
    if ( (*I).NeedSet )
      cb->Text = (*I).SearchValue.StringValue;
    cb->Items->Text = (*I).SearchValue.StringHistory;
    break;
  case ftDate :
  case ftDateTime :
  case ftTimeStamp :
    frPeriod = dynamic_cast< TfrvPeriod* >( TempControl );
    if ( (*I).NeedSet )
      frPeriod->Period = (*I).SearchValue.Period;
    break;
  default :
    cb = dynamic_cast< TComboBox* >( TempControl );
    if ( (*I).NeedSet )
      cb->Text        = (*I).SearchValue.StringValue;
    cb->Items->Text = (*I).SearchValue.StringHistory;
    break;
  }
}

void __fastcall TNNVDBSearchDialog::SearchNext()
{
  if ( !CheckActive() )
    return;
  if ( FWorking )
    return;

  FWorking = true;
  try {
    SearchSkipNext();
  } __finally {
    FWorking = false;
  }
}

void __fastcall TNNVDBSearchDialog::SearchFilter()
{
  if ( !CheckActive() )
    return;
  if ( FWorking )
    return;

  FWorking = true;
  try {
    SearchSkipFilter();
  } __finally {
    FWorking = false;
  }
}

void __fastcall TNNVDBSearchDialog::LoadFromFiler( TNNVTextStream *Filer )
{
  LimitHistory = Filer->ReadInt();
  UseHide      = Filer->ReadBool();
}

void __fastcall TNNVDBSearchDialog::SaveToFiler( TNNVTextStream *Filer )
{
  Filer->WriteInt( LimitHistory );
  Filer->WriteBool( UseHide );
}

void __fastcall TNNVDBSearchDialog::DoExecute()
{
  if ( FOnExecute )
    FOnExecute( this );
}

bool __fastcall TNNVDBSearchDialog::IsFilterPresent()
{
  TNNVQuery *qu = Query;

  if ( !qu )
    return false;

  if ( !qu->MapSearch.SearchDlgOptions.IsFilter )
    return false;

  if ( qu->MapSearch.VectorSearch.size() == 0 )
    return false;

  return qu->FilterMap.IsFilterSearchPresent();
}

// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
static inline void ValidCtrCheck( TNNVDBSearchDialog * )
{
  new TNNVTreeView( nullptr );
  new TNNVNodeAdmin( nullptr );
  new TNNVDBTreeView( nullptr );
  new TNNVQuery( nullptr );
  new TNNVDBGrid( nullptr );
  new TNNVDBSearchDialog( nullptr );
  new TNNVStoryData( nullptr );
  new TNNVConfig( nullptr );
}

namespace NNV {

TStoryInfo::TStoryInfo()
  : Value()
{
}

TStoryInfo::TStoryInfo( const Variant &aValue )
  : Value( aValue )
{
}

}

__fastcall TNNVStoryData::TNNVStoryData(TComponent* Owner)
  : inherited( Owner )
{
}
// ---------------------------------------------------------------------------

void __fastcall TNNVStoryData::Execute( TForm *ASenderForm
                                      , TNNVQuery *AQuery
                                      , TDBGrid *ADBGrid )
{
  if ( !AQuery )
    return;

  BookmarkList = nullptr;

  if ( ADBGrid != nullptr && ADBGrid->SelectedRows->Count > 0 )
    BookmarkList = ADBGrid->SelectedRows;

  if ( BookmarkList == nullptr && AQuery->Eof )
    return;

  fmvStoryData = new TfmvStoryData( this );

  Query = AQuery;

  FillFieldList();

  fmvStoryData->fbRes->OnExecute  = SetStoryData;

  fmvStoryData->ShowDialog( ASenderForm );
}

void __fastcall TNNVStoryData::SetStoryData( TObject *Sender )
{
  if ( !Query )
    return;

  SaveSetting();

  TCheckListBox *cl = fmvStoryData->clData;

  Query->DisableControls();
  try {
    if ( BookmarkList != nullptr && BookmarkList->Count > 0 ) {
      TBookmark BS = Query->Bookmark;
      int blc = BookmarkList->Count;

      for ( int i = 0; i < blc; ++i ) {
        Query->Bookmark = BookmarkList->Items[ i ];
        SetFieldsValue( cl, Query );
      }

      Query->Bookmark = BS;
    } else
      SetFieldsValue( cl, Query );
  } __finally {
    Query->EnableControls();
  }
}

void __fastcall TNNVStoryData::FillFieldList()
{
  bool B = SettingQuery == Query;

  if ( !B )
    SettingSet.clear();

  TCheckListBox *cl = fmvStoryData->clData;

  TField *f;

  cl->Clear();

  int fc = Query->FieldCount, j;
  for ( int i = 0; i < fc; ++i ) {
    f = Query->Fields->Fields[ i ];
    if ( FieldValid( f ) ) {
      j = cl->Items->AddObject( f->DisplayLabel, f );
      if ( B && SettingSet.find( f ) != SettingSet.end() )
        cl->Checked[ j ] = true;
    }
  }
}

void __fastcall TNNVStoryData::RememberData( TNNVQuery *AQuery )
{
  TField *f;

  StoryMap.clear();

  int fc = AQuery->FieldCount;
  for ( int i = 0; i < fc; ++i ) {
    f = AQuery->Fields->Fields[ i ];
    if ( FieldValid( f ) )
      StoryMap[ f ] = NNV::TStoryInfo( f->Value );
  }
}

void __fastcall TNNVStoryData::SetFieldsValue( TCheckListBox *cl, TNNVQuery *od )
{
  TField *f;
  int N = cl->Count;
  NNV::TStoryMap::iterator im;

  od->CWCheckEditMode();
  for ( int j = 0; j < N; ++j ) {
    f = ( TField* )cl->Items->Objects[ j ];
    if ( FieldValid( f ) ) {
      if ( cl->Checked[ j ] ) {
        im = StoryMap.find( f );
        if ( im != StoryMap.end() ) {
          NNV::SetFieldValue( (*im).first, (*im).second.Value );
        }
      }
    }
  }
  od->CWApplyUpdates();
}

void __fastcall TNNVStoryData::SaveSetting()
{
  SettingQuery = Query;
  SettingSet.clear();

  TField *f; // TFieldType

  TCheckListBox *cl = fmvStoryData->clData;
  int N = cl->Count;

  for ( int i = 0; i < N; ++i ) {
    f = (TField*)cl->Items->Objects[ i ];
    if ( FieldValid( f ) && cl->Checked[ i ] )
      SettingSet.insert( f );
  }
}

bool __fastcall TNNVStoryData::FieldValid( TField *f )
{
  NNV::TSettingSet::iterator ie = ExcludeSet.find( f );

  if ( ie != ExcludeSet.end() )
    return false;

  NNV::TRightFieldMap::iterator ir = RightFieldMap.find( f );

  if ( ir != RightFieldMap.end() )
    return (*ir).second;
  else
    return true;
}

void __fastcall TNNVStoryData::ExecuteRowInspector( TForm *ASenderForm
                                                  , TDataSource *ADataSource )
{
  if ( !ADataSource )
    return;

  NNVFormList.New( __classid( TfmvRowInspector ), &fmvRowInspector, this );

  fmvRowInspector->fbRes->OnExecute = RowInspectorExecute;

  DataSource = ADataSource;
  fmvRowInspector->dnRowInspector->DataSource = DataSource;
  PrepareScrollBox( fmvRowInspector->sbSkip );
  fmvRowInspector->ShowDialog( ASenderForm );
}

void __fastcall TNNVStoryData::PrepareScrollBox( TScrollBox *AScrollBox )
{
  TNNVQuery *qu = Query;

  if ( !qu )
    return;

  TField *AFieldSearch = qu->FieldSearch;
  int I, TopSkip = 0, NS = 0;
  // выкрутасы с SBW нужны только потому, что fmvSearch->sbSkip не успевает вовремя поменять свою ширину по свойству Align == alClient
  int SBW = AScrollBox->Parent->Width;
  int AWidthComboBox = SBW - 2 * NNV::SD_LEFTPOS - NNV::SD_LABEL_WIDTH - NNV::SD_SCROLLBAR_WIDTH;

  NNV::ClearScrollBox( AScrollBox );
  TField *F;
  int FC = qu->FieldCount;
  for ( I = 0; I < FC; ++I ) {
    F = qu->Fields->Fields[ I ];
    if ( !UseHide && !F->Visible )
      continue;
    NewLabelCombo( TopSkip, F, NS, AWidthComboBox, AScrollBox, L"", L"" );
  }
  SetOptions( AFieldSearch, AScrollBox );
}

void __fastcall TNNVStoryData::NewLabelCombo( int &TopSkip
                                            , TField *ASearchField
                                            , int &NS
                                            , const int AWidthComboBox
                                            , TScrollBox *AScrollBox
                                            , const String &APrefixLabel
                                            , const String &APrefixField )
{
  TNNVQuery *qu = Query;
  int I, FC;
  TADTField *F;
  TEdit *la;
  TWinControl *TempControl = nullptr;
  TNNVDBComboBoxDateTime *cbd = nullptr;
  TDBEdit *de = nullptr;
  TDBCheckBox *cb = nullptr;
  String S;
  bool ANeedRightAnchors = false;

  la           = new TEdit( AScrollBox->Owner );
  NNV::SetNameToComponent( la, NS );
  la->Text     = APrefixLabel + ASearchField->DisplayLabel;
  la->ReadOnly = true;
  la->TabStop  = false;
  la->Parent   = AScrollBox;
  la->Top      = TopSkip;
  la->Left     = NNV::SD_LEFTPOS;
  la->Width    = NNV::SD_LABEL_WIDTH;

  TField *SearchField;
  switch ( ASearchField->DataType ) {
  case ftBoolean :
    cb             = new TDBCheckBox( AScrollBox );
    cb->Caption    = ASearchField->DisplayLabel;
    cb->DataSource = DataSource;
    cb->DataField  = APrefixField + ASearchField->FieldName;
    TempControl = cb;
    break;
  case ftFloat :
  case ftSmallint :
  case ftInteger :
  case ftLargeint :
    de             = new TDBEdit( AScrollBox );
    TempControl    = de;
    de->Width = de->Width * 2;
    break;
  case ftWideString :
    de             = new TDBEdit( AScrollBox );
    TempControl    = de;
    ANeedRightAnchors = true;
    break;
  case ftDate :
    cbd             = new TNNVDBComboBoxDateTime( AScrollBox );
    TempControl     = cbd;
    cbd->DataSource = DataSource;
    cbd->DataField  = APrefixField + ASearchField->FieldName;
    cbd->NeedTime   = false;
    break;
  case ftDateTime :
  case ftTimeStamp :
    cbd             = new TNNVDBComboBoxDateTime( AScrollBox );
    TempControl     = cbd;
    cbd->DataSource = DataSource;
    cbd->DataField  = APrefixField + ASearchField->FieldName;
    cbd->NeedTime = true;
    break;
  case ftADT :
    F = dynamic_cast< TADTField* >( ASearchField );
    FC = F->FieldCount;
    for ( I = 0; I < FC; ++I ) {
      //++NS;
      SearchField = F->Fields->Fields[ I ];
      NewLabelCombo( TopSkip
                   , SearchField
                   , NS
                   , AWidthComboBox
                   , AScrollBox
                   , F->DisplayLabel + L"."
                   , F->FieldName + L"." );
    }
    break;
  default :
    de                = new TDBEdit( AScrollBox );
    TempControl       = de;
    ANeedRightAnchors = true;
    break;
  }

  if ( TempControl ) {
    NNV::SetNameToComponent( TempControl, ASearchField, NS );
    TempControl->Tag     = NativeInt( ASearchField );
    TempControl->Parent  = AScrollBox;
    TempControl->Top     = TopSkip;
    TempControl->Left    = la->Left + la->Width + NNV::SD_LEFTPOS;

    TopSkip += std::max( TempControl->Height, la->Height ) + 2;
  }

  if ( TempControl && !( cbd || cb ) && ANeedRightAnchors ) {
    TempControl->Width   = AWidthComboBox;
    TempControl->Anchors = TempControl->Anchors << akRight;
  }

  if ( de ) {
    de->DataSource = DataSource;
    de->DataField  = APrefixField + ASearchField->FieldName;
  }
}

void __fastcall TNNVStoryData::SetOptions( TField *AFieldSearch, TScrollBox *AScrollBox )
{
  TNNVQuery *qu = Query;
  if ( !qu )
    return;

  if ( AFieldSearch ) {
    TWinControl *CTR, *AC;

    int L = AScrollBox->ComponentCount;
    for ( int I = 0; I < L; ++I ) {
      CTR = dynamic_cast< TWinControl* >( AScrollBox->Components[ I ] );
      if ( CTR && CTR->Tag == NativeInt( AFieldSearch ) ) {
        TfrvDiapazon *fr = dynamic_cast< TfrvDiapazon* >( CTR );
        AC = fr ? fr->BeginControl : CTR;

        TCustomForm *fm = dynamic_cast< TCustomForm* >( AScrollBox->Owner );
        fm->ActiveControl = AC;
        AScrollBox->VertScrollBar->Position = 0;
        AScrollBox->VertScrollBar->Position = CTR->Top - 2;
        break;
      }
    }
  }
}

void __fastcall TNNVStoryData::SetDataSource( TDataSource *Value )
{
  if ( FDataSource != Value ) {
    FDataSource = Value;
    if ( DataSource ) {
      Query = dynamic_cast< TNNVQuery* >( DataSource->DataSet );
    }
  }
}

void __fastcall TNNVStoryData::RowInspectorExecute( TObject *Sender )
{
  Query->CWCheckBrowseMode();
}

TNNVConfig::TNNVConfig( TComponent* Owner )
  : inherited( Owner )
  , fVersion( char() )
  , fTableUserReg( NNVConst::TableUserReg )
  , fFieldUserRegKey( NNVConst::FieldUserRegKey )
  , fFieldUserData( NNVConst::FieldUserData )
{
}

bool __fastcall TNNVConfig::StoredTableUserReg()
{
  return fTableUserReg != NNVConst::TableUserReg;
}

bool __fastcall TNNVConfig::StoredFieldUserRegKey()
{
  return fFieldUserRegKey != NNVConst::FieldUserRegKey;
}

bool __fastcall TNNVConfig::StoredFieldUserData()
{
  return fFieldUserData != NNVConst::FieldUserData;
}

void __fastcall TNNVConfig::Notification( TComponent *AComponent, TOperation Operation )
{
  inherited::Notification( AComponent, Operation );
  if ( ( Operation == opRemove ) && ( AComponent == Connection ) )
    fConnection = nullptr;
}

void __fastcall TNNVConfig::Load()
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

void __fastcall TNNVConfig::Save()
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

void __fastcall TNNVConfig::DoLoad()
{
  DoBeginLoad();
  try {
    if ( FOnLoad )
      FOnLoad(this);
  } __finally {
    DoEndLoad();
  }
}

void __fastcall TNNVConfig::DoDefault()
{
  DoBeginLoad();
  try {
    if ( FOnDefault )
      FOnDefault( this );
  } __finally {
    DoEndLoad();
  }
}

void __fastcall TNNVConfig::DoSave()
{
  DoBeginSave();
  try {
    if ( FOnSave )
      FOnSave( this );
  } __finally {
    DoEndSave();
  }
}

void __fastcall TNNVConfig::LoadFilerFromUserEvent()
{
  bool B = true;
  Filer->Position = 0;
  if ( Version == Filer->ReadChar() ) {
    DoLoad();
    if ( Version != Filer->ReadChar() )
      throw Exception( L"Ошибка чтения потока TNNVConfig" );
    else
      B = false;
  }
  if ( B )
    DoDefault();
}

void __fastcall TNNVConfig::SaveFilerFromUserEvent()
{
  Filer->Position = 0;
  Filer->WriteChar( Version );
  DoSave();
  Filer->WriteChar( Version );
  Filer->Size = Filer->Position;
}

void __fastcall TNNVConfig::PrepareFilerFromFile()
{
  String fn = RegistryKey();
  if ( !FileExists( fn ) ) {
    DoDefault();
    return;
  }

  std::unique_ptr< TFileStream >fs( new TFileStream( fn, fmOpenRead ) );
  fFiler = new TNNVTextStream( fs.get() );
  try {
    LoadFilerFromUserEvent();
  } __finally {
    delete fFiler;
    fFiler = nullptr;
  }
}

void __fastcall TNNVConfig::PrepareFilerFromDB()
{
  fFiler = new TNNVTextStream( nullptr );

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

void __fastcall TNNVConfig::PrepareFilerFromUserEvent()
{
  if ( Filer )
    throw Exception( L"Не определён fFiler" );

  DoGetFiler();
  if ( Filer && ( Filer->Size != 0 ) )
    LoadFilerFromUserEvent();
  else
    DoDefault();
}

void __fastcall TNNVConfig::SaveToFile()
{
  String fn = RegistryKey();
  if ( !FileExists( fn ) ) {
    NativeUInt H = FileCreate( fn );
    FileClose( H );
  }
  TFileStream* fs = new TFileStream( fn, fmOpenWrite );
  fFiler = new TNNVTextStream( fs );
  try {
    SaveFilerFromUserEvent();
  } __finally {
    delete fFiler;
    fFiler = nullptr;
    if ( fs )
      delete fs;
  }
}

void __fastcall TNNVConfig::SaveToFiler()
{
  fFiler = nullptr;
  DoGetFiler();
  if ( Filer )
    SaveFilerFromUserEvent();
}

void __fastcall TNNVConfig::SetConnection(TFDConnection *value)
{
  if ( Connection != value ) {
    fConnection = value;
    if ( value )
      value->FreeNotification( this );
  }
}

void __fastcall TNNVConfig::PrepareQuerySQL( TNNVQuery *quReg, const String &UserRegKey )
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

void __fastcall TNNVConfig::SaveToDB()
{
  if ( !IsConnection() )
    return;

  String RK = RegistryKey();
  fFiler = new TNNVTextStream( nullptr );
  try {
    SaveFilerFromUserEvent();
    std::unique_ptr< TNNVQuery > quReg( new TNNVQuery( this ) );
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

bool __fastcall TNNVConfig::LoadFromDB()
{
  if ( !IsConnection() )
    return false;

  bool B = false;
  std::unique_ptr< TNNVQuery > quReg( new TNNVQuery( this ) );
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

String __fastcall TNNVConfig::RegistryKey()
{
  String S;

  if ( StaticRegistryKey.IsEmpty() ) {
    S = NNV::ComponentToKey( Owner, UseOwnerNameInRegistryKey );
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

bool __fastcall TNNVConfig::IsConnection()
{
  if ( Connection == nullptr )
    return false;
  else
    return Connection->Connected;
}

namespace Vcl_nndbmiracle
{

void __fastcall PACKAGE Register()
{
  TComponentClass classes[ 8 ];

  classes[ 0 ] = __classid( TNNVTreeView );
  classes[ 1 ] = __classid( TNNVNodeAdmin );
  classes[ 2 ] = __classid( TNNVDBTreeView );
  classes[ 3 ] = __classid( TNNVQuery );
  classes[ 4 ] = __classid( TNNVDBGrid );
  classes[ 5 ] = __classid( TNNVDBSearchDialog );
  classes[ 6 ] = __classid( TNNVStoryData );
  classes[ 7 ] = __classid( TNNVConfig );

  RegisterComponents( L"VCL New Navadvipa", classes, 7 );
}

}

