// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFmRes.h"
#include "VCL_NNFormHistory.h"
#include "VCL_NNDmNewNavadvipa.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNFlagBox"
#pragma link "VCL_NNRightsManager"
#pragma link "VCL_NNActionList"
#pragma link "VCL_NNLanguageManager"
#pragma resource "*.dfm"

TfmvRes *fmvRes;

// ---------------------------------------------------------------------------
__fastcall TfmvRes::TfmvRes( TComponent* Owner )
  : inherited( Owner )
{
}

// ---------------------------------------------------------------------------
void __fastcall TfmvRes::FormCreate( TObject *Sender )
{
  rrRes->Apply();
  lnRes->Apply();
  coRes->Load();
  ToolButtonPrepare();

  // Устанавливаем всем полям даты и даты-времени (TimeStamp) EditMask
  NNV::FormLocaleFormat( this );
}

// ---------------------------------------------------------------------------
void __fastcall TfmvRes::FormDestroy( TObject *Sender )
{
  fIsDestroy = true;
  NNV::FormHistory.Remove( this );
  NNV::FormCycle.Remove( this );
  coRes->Save();
  if ( NNVConst::FormBack == this )
    NNVConst::FormBack = NULL;
  ClearWindowPlacement();
}

// ---------------------------------------------------------------------------
void __fastcall TfmvRes::FormClose( TObject *Sender, TCloseAction &Action )
{
  if ( fbRes->caFree || Application->Terminated )
    Action = caFree;
}

// ---------------------------------------------------------------------------
void __fastcall TfmvRes::FormDeactivate( TObject *Sender )
{
  if ( DialogMode && DialogCloseOnDeactivate )
    CloseDialog( false );
}

// ---------------------------------------------------------------------------
void __fastcall TfmvRes::coResLoad( TObject *Sender )
{
  FWindowPlace = new TWindowPlacement();

  coRes->Filer->ReadBinaryData( FWindowPlace );
  coRes->Filer->ReadFont( Font );
  AlphaBlendValue = coRes->Filer->ReadUnsignedChar();
  AlphaBlend = coRes->Filer->ReadBool();
  TransparentColorValue = coRes->Filer->ReadColor();
  TransparentColor = coRes->Filer->ReadBool();
  alRes->LoadFromFiler( coRes->Filer );
  EnterKind = ( NNV::TEnterKind )coRes->Filer->ReadInt();
}
// ---------------------------------------------------------------------------

void __fastcall TfmvRes::coResSave( TObject *Sender )
{
  TWindowPlacement Placement;
  Placement.length = sizeof( TWindowPlacement );
  GetWindowPlacement( Handle, &Placement );

  coRes->Filer->WriteBinaryData( &Placement, Placement.length );
  coRes->Filer->WriteFont( Font );
  coRes->Filer->WriteUnsignedChar( AlphaBlendValue );
  coRes->Filer->WriteBool( AlphaBlend );
  coRes->Filer->WriteColor( TransparentColorValue );
  coRes->Filer->WriteBool( TransparentColor );
  alRes->SaveToFiler( coRes->Filer );
  coRes->Filer->WriteInt( (int)EnterKind );
}
// ---------------------------------------------------------------------------

void __fastcall TfmvRes::FormActivate( TObject *Sender )
{
  fbRes->DoSynchronization();
  TNNVDBGrid *dg = dynamic_cast< TNNVDBGrid* >( ActiveControl );
  if ( dg )
    dg->SetFieldSearchName();
  else {
    dg = dynamic_cast< TNNVDBGrid* >( LastActive );
    if ( dg )
      dg->SetFieldSearchName();
  }
}
// ---------------------------------------------------------------------------

void __fastcall TfmvRes::LabelClick( TObject *Sender )
{
  TLabel *l = dynamic_cast< TLabel* >( Sender );
  if ( l->FocusControl && l->FocusControl->CanFocus() )
    l->FocusControl->SetFocus();
}
// ---------------------------------------------------------------------------

void __fastcall TfmvRes::SetDialogMode( bool Value )
{
  if ( fDialogMode != Value ) {
    fDialogMode = Value;

    SyncDialogInit();
    DialogCloseOnDeactivate = DialogMode;
    if ( DialogMode ) {
      DialogInit();
      fbRes->DoPrepare();
    } else
      fbRes->DoUnPrepare();
  }
}

void __fastcall TfmvRes::SetEnterKind( NNV::TEnterKind Value )
{
  if ( FEnterKind != Value ) {
    FEnterKind = Value;
    SyncEnterKind();
  }
}

void __fastcall TfmvRes::Activate(void)
{
  inherited::Activate();
  RegisterForHistory();
  if ( FWindowPlace ) {
    SetWindowPlacement( Handle, FWindowPlace );
    ClearWindowPlacement();
    if ( WindowState == wsMinimized )
      WindowState = wsNormal;
    CorrectWindowPlace();
  }
}

void __fastcall TfmvRes::DialogInit()
{
  fResultKind.Clear();
  fResultNo.Clear();
  fResultNote.Clear();

  fIsMultiResult = false;
  MultiResult.clear();
}

bool __fastcall TfmvRes::SetFocusedControl( Controls::TWinControl* Control )
{
  bool B = inherited::SetFocusedControl( Control );
  if ( B && !IsQuickSearch ) {
    FLastActive = Control;
    LastActive->FreeNotification( this );
  }
  return B;
}

void __fastcall TfmvRes::Notification( TComponent *AComponent, TOperation Operation )
{
  inherited::Notification( AComponent, Operation );
  if ( Operation == opRemove ) {
    if ( AComponent == LastActive )
      FLastActive = nullptr;
  }
}

void __fastcall TfmvRes::Loaded()
{
  inherited::Loaded();

  //OldCreateOrder = false;
  if ( NNV::DMExists( __classid( TdmvNewNavadvipa ), &dmvNewNavadvipa ) )
    FixWhileEmbarcaderoBug();
  // Это нужно из-зп глюка Embarcadero! В Инспекторе Объектов не видна coResGetFiler!
  coRes->OnGetFiler = coResGetFiler;
}

void __fastcall TfmvRes::FixWhileEmbarcaderoBug()
{
  coRes->Connection = dmvNewNavadvipa->conDB;
  rrRes->Manager    = dmvNewNavadvipa->rmDB;
  lnRes->Manager    = dmvNewNavadvipa->lmDB;
  alRes->Images     = dmvNewNavadvipa->ilDB;
}

void __fastcall TfmvRes::RegisterForHistory()
{
  if ( !DialogMode ) {
    NNVConst::FormBack = this;
    NNV::FormHistory.Add( this );
    NNV::FormCycle.Add( this );
  }
}

void __fastcall TfmvRes::StartHelp()
{
  if ( fHelpCapture )
    return;

  fHelpCapture = true;
  fOldCursor = Screen->Cursor;
  Screen->Cursor = crHelp;

  SetCapture( Handle );
}

void __fastcall TfmvRes::ToolButtonPrepare()
{
  TToolButton *bt;
  TAction *a;

  int N = ComponentCount;

  for ( int i = 0; i < N; ++i ) {
    bt = dynamic_cast< TToolButton* >( Components[ i ] );
    if ( bt ) {
      a = dynamic_cast< TAction* >( bt->Action );
      if ( a )
        bt->HelpContext = a->HelpContext;
    }
  }
}

void __fastcall TfmvRes::CorrectWindowPlace()
{
  TPoint P = ClientOrigin;
  if ( P.x + NNVConst::CriticalFormPlaceDelta > Screen->Width || P.x +
      NNVConst::CriticalFormPlaceMinus < 0 )
    Left = (Screen->Width - Width) / 2;
  if ( P.y + NNVConst::CriticalFormPlaceDelta > Screen->Height || P.y -
      NNVConst::CriticalFormPlaceMinus < 0 )
    Top = (Screen->Height - Height) / 2;
}

void __fastcall TfmvRes::ShowDialog( TComponent *SenderForm )
{
  fbRes->SenderForm = SenderForm;

  if ( DialogMode )
    DialogMode = false;
  DialogMode = true;

  NNV::FormShow( this );
}

void __fastcall TfmvRes::CloseDialog( bool IsExecute )
{
  if ( DialogMode ) {
    if ( IsExecute ) {
      CloseValid();
      fbRes->DoExecute();
    }
    CloseAlways();
    DialogMode = false;
  }
  Close();
}

void __fastcall TfmvRes::FillMultiResult( TNNVDBGrid *dg
                                        , TField *FieldNo
                                        , TField *FieldNote )
{
  if ( IsClearCase ) {
    fResultNo.Clear();
    fResultNote.Clear();
    fIsMultiResult = false;
  } else {
    TDataSet *DSet = dg->DataSource->DataSet;
    int N = dg->SelectedRows->Count;
    fResultNo = FieldNo->AsFloat;
    fResultNote = FieldNote->DisplayText;
    if ( N > 1 ) {
      TBookmark bm = DSet->Bookmark;
      DSet->DisableControls();
      try {
        for ( int i = 0; i < N; ++i ) {
          DSet->Bookmark = dg->SelectedRows->Items[ i ];
          MultiResult.push_back( NNV::TMultiResultElement( FieldNo->AsFloat
                                                         , FieldNote->DisplayText ) );
        }
        DSet->Bookmark = bm;
      } __finally {
        DSet->EnableControls();
      }
      fIsMultiResult = true;
    } else
      fIsMultiResult = false;
  }
}

void __fastcall TfmvRes::MultiResultExecute( TNNVQuery *DSet
                                           , TField *FieldNo
                                           , TField *FieldNote
                                           , bool IsDublicate )
{
  if ( IsMultiResult ) {
    bool B;
    DSet->DisableControls();
    if ( NNV::IsEditModes( DSet->State ) )
      DSet->Cancel();
    try {
      for ( NNV::TMultiResult::const_iterator i = MultiResult.begin(); i != MultiResult.end(); ++i ) {
        if ( IsDublicate )
          B = true;
        else
          B = !DSet->Locate( FieldNo->FieldName, (*i).PK, TLocateOptions() );
        if ( B ) {
          DSet->Append();
          FieldNo->Value = (*i).PK;
          FieldNote->Value = (*i).Note;
          DSet->Post();
        }
      }
    } __finally {
      DSet->EnableControls();
    }
  } else {
    DSet->CWCheckEditMode();
    NNV::SetFieldValue( FieldNo, ResultNo );
    NNV::SetFieldValue( FieldNote, ResultNote );
  }
}

void __fastcall TfmvRes::ExecuteHelp()
{
  THelpContext HK;

  TWinControl *c = ActiveControl;
  if ( c ) {
    do {
      HK = c->HelpContext;
      c = c->Parent;
    } while ( ( ( HK == 0 ) || ( HK % 10 != 0 ) ) && ( c != NULL ) );
  } else
    HK = HelpContext;
  if ( HK != 0 ) {
    if ( HK % 10 == 0 )
      Application->HelpContext( HK );
    else
      Application->HelpCommand( HELP_CONTEXTPOPUP, HK );
  }
}

void __fastcall TfmvRes::FormKeyDown( TObject *Sender, WORD &Key, TShiftState Shift )
{
  if ( Key == vkF1 ) {
    if ( Shift == ( Classes::TShiftState() << ssAlt ) )
      StartHelp();
    else if ( Shift == ( Classes::TShiftState() << ssAlt << ssShift ) )
      ExecuteHelp();
    Key = 0;
  }
}
// ---------------------------------------------------------------------------

void __fastcall TfmvRes::SimpleKeyDownDialog( TObject *Sender, WORD &Key, TShiftState Shift )
{
  if ( Key == 0 )
    return;

  TCustomCombo *cc;
  switch ( Key ) {
  case vkEscape :
    cc = dynamic_cast< TCustomCombo* >( ActiveControl );
    if ( cc && cc->DroppedDown )
      cc->DroppedDown = false;
    else
      CloseDialog( false );
    Key = 0;
    break;
  case vkReturn :
    if ( EnterKind == NNV::TEnterKind::Like || Shift.Contains( ssShift ) ) {
      cc = dynamic_cast< TCustomCombo* >( ActiveControl );
      if ( cc && cc->DroppedDown )
        cc->DroppedDown = false;
      else
        CloseDialog( true );
      Key = 0;
    }
    break;
  }

  if ( Key )
    FormKeyDown( Sender, Key, Shift );
}
//---------------------------------------------------------------------------

void __fastcall TfmvRes::FormMouseDown( TObject *Sender, TMouseButton Button
                                      , TShiftState Shift, int X, int Y )
{
  if ( fHelpCapture ) {
    fHelpCapture = false;
    Screen->Cursor = fOldCursor;

    THelpContext HK;
    TControl *c = NNV::ControlAtPos( this, Point( X, Y ) );
    if ( c ) {
      do {
        HK = c->HelpContext;
        c = c->Parent;
      }
      while ( HK == 0 && c != NULL );
    } else
      HK = HelpContext;
    if ( HK != 0 ) {
      if ( HK % 10 == 0 )
        Application->HelpContext( HK );
      else
        Application->HelpCommand( HELP_CONTEXTPOPUP, HK );
    }
  }
}
// ---------------------------------------------------------------------------

void __fastcall TfmvRes::aActionListSetupExecute( TObject *Sender )
{
  alRes->ShowPropertyDialog();
}
//---------------------------------------------------------------------------

void __fastcall TfmvRes::aReleaseExecute( TObject *Sender )
{
  Release();
}
//---------------------------------------------------------------------------

void __fastcall TfmvRes::FormCloseQuery( TObject *Sender, bool &CanClose )
{
  CanClose = CanUserClose;
}
//---------------------------------------------------------------------------

void __fastcall TfmvRes::aClearCaseExecute(TObject *Sender)
{
  FIsClearCase = true;
  try {
    CloseDialog( true );
  } __finally {
    FIsClearCase = false;
  }
}

void __fastcall TfmvRes::coResGetFiler( TObject *Sender, TNNVTextStream *&Filer )
{
  Filer = dmvNewNavadvipa->MapFiler.Filer[ coRes->RegistryKey() ];
}
//---------------------------------------------------------------------------

void __fastcall TfmvRes::aPrepareLanguageExecute( TObject *Sender )
{
  dmvNewNavadvipa->lmDB->PrepareLanguage( this );
}
//---------------------------------------------------------------------------

