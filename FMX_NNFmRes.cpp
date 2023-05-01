//---------------------------------------------------------------------------
#include <fmx.h>

#pragma hdrstop

#include "FMX_NNFmRes.h"
#include "FMX_NNFormHistory.h"
#include "FMX_NNDmNewNavadvipa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FMX_NNDBMiracle"
#pragma link "FMX_NNFlagBox"
#pragma link "FMX_NNLanguageManager"
#pragma link "FMX_NNRightsManager"
#pragma link "FMX_NNActionList"
#pragma resource "*.fmx"
TfmfRes *fmfRes;
//---------------------------------------------------------------------------
__fastcall TfmfRes::TfmfRes(TComponent* Owner)
  : inherited( Owner  )
{
}

//---------------------------------------------------------------------------
void __fastcall TfmfRes::FormCreate(TObject *Sender)
{
  rrRes->Apply();
  lnRes->Apply();
  coRes->Load();
  //ToolButtonPrepare();

  // Устанавливаем всем полям даты и даты-времени (TimeStamp) EditMask
  NNF::FormLocaleFormat( this );
}
//---------------------------------------------------------------------------

void __fastcall TfmfRes::FormDestroy(TObject *Sender)
{
  fIsDestroy = true;
  NNF::FormHistory.Remove( this );
  NNF::FormCycle.Remove( this );
  coRes->Save();
  if ( NNFConst::FormBack == this )
    NNFConst::FormBack = NULL;
  //ClearWindowPlacement();
}
//---------------------------------------------------------------------------

void __fastcall TfmfRes::coResLoad(TObject *param_0)
{
  Left   = coRes->Filer->ReadInt();
  Top    = coRes->Filer->ReadInt();
  Width  = coRes->Filer->ReadInt();
  Height = coRes->Filer->ReadInt();
}
//---------------------------------------------------------------------------

void __fastcall TfmfRes::coResSave(TObject *param_0)
{
  coRes->Filer->WriteInt( Left );
  coRes->Filer->WriteInt( Top );
  coRes->Filer->WriteInt( Width );
  coRes->Filer->WriteInt( Height );
}
//---------------------------------------------------------------------------

void __fastcall TfmfRes::ShowDialog( TComponent *SenderForm )
{
  fbRes->SenderForm = SenderForm;

  if ( DialogMode )
    DialogMode = false;
  DialogMode = true;

  NNF::FormShow( this );
}

void __fastcall TfmfRes::CloseDialog( bool IsExecute )
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

void __fastcall TfmfRes::FillMultiResult( TGrid *dg
                                        , TField *FieldNo
                                        , TField *FieldNote )
{
  if ( IsClearCase ) {
    fResultNo.Clear();
    fResultNote.Clear();
    fIsMultiResult = false;
  } else {
//    TDataSet *DSet = dg->DataSource->DataSet;
//    int N = dg->SelectedRows->Count;
//    fResultNo = FieldNo->AsFloat;
//    fResultNote = FieldNote->DisplayText;
//    if ( N > 1 ) {
//      TBookmark bm = DSet->Bookmark;
//      DSet->DisableControls();
//      try {
//        for ( int i = 0; i < N; ++i ) {
//          DSet->Bookmark = dg->SelectedRows->Items[ i ];
//          MultiResult.push_back( NNF::TMultiResultElement( FieldNo->AsFloat
//                                                         , FieldNote->DisplayText ) );
//        }
//        DSet->Bookmark = bm;
//      } __finally {
//        DSet->EnableControls();
//      }
//      fIsMultiResult = true;
//    } else
//      fIsMultiResult = false;
  }
}

//void __fastcall TfmfRes::MultiResultExecute( TNNFQuery *DSet
//                                           , TField *FieldNo
//                                           , TField *FieldNote
//                                           , bool IsDublicate )
//{
//  if ( IsMultiResult ) {
//    bool B;
//    DSet->DisableControls();
//    if ( NNF::IsEditModes( DSet->State ) )
//      DSet->Cancel();
//    try {
//      for ( NNF::TMultiResult::const_iterator i = MultiResult.begin(); i != MultiResult.end(); ++i ) {
//        if ( IsDublicate )
//          B = true;
//        else
//          B = !DSet->Locate( FieldNo->FieldName, (*i).PK, TLocateOptions() );
//        if ( B ) {
//          DSet->Append();
//          FieldNo->Value = (*i).PK;
//          FieldNote->Value = (*i).Note;
//          DSet->Post();
//        }
//      }
//    } __finally {
//      DSet->EnableControls();
//    }
//  } else {
//    DSet->CWCheckEditMode();
//    NNF::SetFieldValue( FieldNo, ResultNo );
//    NNF::SetFieldValue( FieldNote, ResultNote );
//  }
//}

void __fastcall TfmfRes::FormClose( TObject *Sender, TCloseAction &Action )
{
  if ( fbRes->caFree || Application->Terminated )
    Action = TCloseAction::caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfmfRes::SetDialogMode( bool Value )
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

void __fastcall TfmfRes::SetEnterKind( NNF::TEnterKind Value )
{
  if ( FEnterKind != Value ) {
    FEnterKind = Value;
    SyncEnterKind();
  }
}

void __fastcall TfmfRes::Activate(void)
{
  inherited::Activate();
  RegisterForHistory();
//  if ( FWindowPlace ) {
//    SetWindowPlacement( Handle, FWindowPlace );
//    ClearWindowPlacement();
//    if ( WindowState == wsMinimized )
//      WindowState = wsNormal;
//    CorrectWindowPlace();
//  }
}

void __fastcall TfmfRes::DialogInit()
{
  fResultKind.Clear();
  fResultNo.Clear();
  fResultNote.Clear();

  fIsMultiResult = false;
  MultiResult.clear();
}

//bool __fastcall TfmfRes::SetFocusedControl( TControl* Control )
//{
//  bool B = inherited::SetFocusedControl( Control );
//  if ( B && !IsQuickSearch ) {
//    FLastActive = Control;
//    LastActive->FreeNotification( this );
//  }
//  return B;
//}

void __fastcall TfmfRes::Notification( TComponent *AComponent, TOperation Operation )
{
  inherited::Notification( AComponent, Operation );
  if ( Operation == opRemove ) {
    if ( AComponent == LastActive )
      FLastActive = nullptr;
  }
}

void __fastcall TfmfRes::Loaded()
{
  inherited::Loaded();

  if ( NNF::DMExists( __classid( TdmfNewNavadvipa ), &dmfNewNavadvipa ) ) {
    FixWhileEmbarcaderoBug();
    alRes->Images = dmfNewNavadvipa->ilDB;
    coRes->Connection = dmfNewNavadvipa->conDB;
  }
  // Это нужно из-зп глюка Embarcadero! В Инспекторе Объектов не видна coResGetFiler!
  coRes->OnGetFiler = coResGetFiler;
}

void __fastcall TfmfRes::FixWhileEmbarcaderoBug()
{
  coRes->Connection = dmfNewNavadvipa->conDB;
  rrRes->Manager    = dmfNewNavadvipa->rmDB;
  lnRes->Manager    = dmfNewNavadvipa->lmDB;
  alRes->Images     = dmfNewNavadvipa->ilDB;
}

void __fastcall TfmfRes::RegisterForHistory()
{
  if ( !DialogMode ) {
    NNFConst::FormBack = this;
    NNF::FormHistory.Add( this );
    NNF::FormCycle.Add( this );
  }
}

//void __fastcall TfmfRes::StartHelp()
//{
//  if ( fHelpCapture )
//    return;
//
//  fHelpCapture = true;
//  fOldCursor = Cursor;
//  Cursor = crHelp;
//
//  SetCapture( Handle );
//}

void __fastcall TfmfRes::ToolButtonPrepare()
{
//  TToolButton *bt;
//  TAction *a;
//
//  int N = ComponentCount;
//
//  for ( int i = 0; i < N; ++i ) {
//    bt = dynamic_cast< TToolButton* >( Components[ i ] );
//    if ( bt ) {
//      a = dynamic_cast< TAction* >( bt->Action );
//      if ( a )
//        bt->HelpContext = a->HelpContext;
//    }
//  }
}

void __fastcall TfmfRes::CorrectWindowPlace()
{
  TPoint P = TPoint( Left, Top );
  if ( P.x + NNFConst::CriticalFormPlaceDelta > Screen->Width || P.x +
      NNFConst::CriticalFormPlaceMinus < 0 )
    Left = (Screen->Width - Width) / 2;
  if ( P.y + NNFConst::CriticalFormPlaceDelta > Screen->Height || P.y -
      NNFConst::CriticalFormPlaceMinus < 0 )
    Top = (Screen->Height - Height) / 2;
}

void __fastcall TfmfRes::coResGetFiler( TObject *Sender, TNNFTextStream *&Filer )
{
  Filer = dmfNewNavadvipa->MapFiler.Filer[ coRes->RegistryKey() ];
}
//---------------------------------------------------------------------------

