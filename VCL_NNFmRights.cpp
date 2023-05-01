//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop

#include "VCL_NNFmRights.h"
#include "VCL_NNDmNewNavadvipa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNActionList"
#pragma link "VCL_NNDateTimeDialog"
#pragma link "VCL_NNDialogExec"
#pragma link "VCL_NNFlagBox"
#pragma link "VCL_NNFmDB"
#pragma link "VCL_NNPageControl"
#pragma link "VCL_NNPanel"
#pragma link "VCL_NNRightsManager"
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNSplitter"
#pragma link "VCL_NNLanguageManager"
#pragma resource "*.dfm"
TfmvRights *fmvRights;

//---------------------------------------------------------------------------
__fastcall TfmvRights::TfmvRights( TComponent* Owner )
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

void __fastcall TfmvRights::FindID( long long int ARightID )
{
  long long int AKindID = dmvNewNavadvipa->EntityIDToKindID( ARightID );

  if ( dmvNewNavadvipa->quRightsKindKindID->AsLargeInt != AKindID )
    dmvNewNavadvipa->quRightsKind->CWLocate( "KindID", AKindID );

  dmvNewNavadvipa->quRights->FilterMap.EraseFilterSearch();

  if ( dmvNewNavadvipa->quRightsEntityID->AsLargeInt != ARightID )
    dmvNewNavadvipa->quRights->CWLocate( "EntityID", ARightID );
}

void __fastcall TfmvRights::naRightsKindFirstEnter( TObject *Sender )
{
  dmvNewNavadvipa->quRightsKind->CWOpen();
  dmvNewNavadvipa->quRights->CWOpen();
}
//---------------------------------------------------------------------------

void __fastcall TfmvRights::naRightsKindLastExit( TObject *Sender )
{
  dmvNewNavadvipa->quRights->CWClose();
  dmvNewNavadvipa->quRightsKind->CWClose();
}
//---------------------------------------------------------------------------

void __fastcall TfmvRights::naRightsKindEnter( TObject *Sender )
{
  DataSet = dmvNewNavadvipa->quRightsKind;
}
//---------------------------------------------------------------------------

void __fastcall TfmvRights::naRightsKindGetNodeParams( TObject *Sender, TNNVNodeParams &NodeParams )

{
  dmvNewNavadvipa->SetNodeParamsRightsKind( NodeParams );
}
//---------------------------------------------------------------------------

void __fastcall TfmvRights::naRightsKindLoadNodes( TObject *Sender )
{
  tvRights->LoadNodeAdmin( nullptr, naRightsKind, NNV::RootRightsKindID );
}
//---------------------------------------------------------------------------

void __fastcall TfmvRights::coResLoad( TObject *Sender )
{
  inherited::coResLoad( Sender );
  LoadNodeAdmins();
  LoadTrees();
  LoadGrids();
  tvRights->Width = coRes->Filer->ReadInt();
}
//---------------------------------------------------------------------------

void __fastcall TfmvRights::coResSave( TObject *Sender )
{
  inherited::coResSave( Sender );
  SaveNodeAdmins();
  SaveTrees();
  SaveGrids();
  coRes->Filer->WriteInt( tvRights->Width );
}
//---------------------------------------------------------------------------

void __fastcall TfmvRights::LoadNodeAdmins()
{
  naRightsKind->LoadFromFiler( coRes->Filer );
}

void __fastcall TfmvRights::SaveNodeAdmins()
{
  naRightsKind->SaveToFiler( coRes->Filer );
}

void __fastcall TfmvRights::LoadTrees()
{
  tvRights->LoadFromFiler( coRes->Filer );
}

void __fastcall TfmvRights::SaveTrees()
{
  tvRights->SaveToFiler( coRes->Filer );
}

void __fastcall TfmvRights::LoadGrids()
{
  dgRights->LoadFromFiler( coRes->Filer );
}

void __fastcall TfmvRights::SaveGrids()
{
  dgRights->SaveToFiler( coRes->Filer );
}

void __fastcall TfmvRights::dgRightsDBCut( TObject *Sender )
{
  dgRights->CWSelect( dmvNewNavadvipa->quRightsEntityID, &dmvNewNavadvipa->BufferIntBox, true );
}
//---------------------------------------------------------------------------

void __fastcall TfmvRights::dgRightsDBPaste( TObject *Sender )
{
  dmvNewNavadvipa->quRights->DBPaste( dmvNewNavadvipa->BufferIntBox, dmvNewNavadvipa->quDB, dmvNewNavadvipa->quRightsKindKindID );
}
//---------------------------------------------------------------------------

void __fastcall TfmvRights::dgRightsDrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
  if ( !State.Contains( gdFocused ) && !dgRights->IsCurrentSelected() ) {
    TField *f = dmvNewNavadvipa->quRightsKindID;
    if ( !f->IsNull )
      dmvNewNavadvipa->DBGridColor( dgRights, f->AsLargeInt );
  }
  dgRights->DefaultDrawColumnCell( Rect, DataCol, Column, State );
}

//---------------------------------------------------------------------------
void __fastcall TfmvRights::coResEndLoad( TObject *Sender )
{
  splRights->Left = tvRights->Left + tvRights->Width + 1;
}
//---------------------------------------------------------------------------

void __fastcall TfmvRights::FormCreate(TObject *Sender)
{
  inherited::FormCreate( Sender );

  tvRights->StartAdmin();
}
//---------------------------------------------------------------------------

void __fastcall TfmvRights::FormDestroy(TObject *Sender)
{
  inherited::FormDestroy( Sender );

  tvRights->FinishAdmin();
}
//---------------------------------------------------------------------------

void __fastcall TfmvRights::CloseValid()
{
  inherited::CloseValid();
  FillMultiResult( dgRights, dmvNewNavadvipa->quRightsEntityID, dmvNewNavadvipa->quRightsEntity );
}

