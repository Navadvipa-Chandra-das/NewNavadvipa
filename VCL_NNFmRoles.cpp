//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFmRoles.h"
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
#pragma link "VCL_NNSplitter"
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNLanguageManager"
#pragma resource "*.dfm"
TfmvRoles *fmvRoles;
//---------------------------------------------------------------------------
__fastcall TfmvRoles::TfmvRoles( TComponent* Owner )
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

void __fastcall TfmvRoles::FindID( long long int ARoleID )
{
  long long int AKindID = dmvNewNavadvipa->EntityIDToKindID( ARoleID );

  if ( dmvNewNavadvipa->quRoleKindKindID->AsLargeInt != AKindID )
    dmvNewNavadvipa->quRoleKind->CWLocate( "KindID", AKindID );

  dmvNewNavadvipa->quRole->FilterMap.EraseFilterSearch();

  if ( dmvNewNavadvipa->quRoleEntityID->AsLargeInt != ARoleID )
    dmvNewNavadvipa->quRole->CWLocate( "EntityID", ARoleID );
}

void __fastcall TfmvRoles::coResLoad( TObject *Sender )
{
  inherited::coResLoad( Sender );
  LoadNodeAdmins();
  LoadTrees();
  LoadGrids();
  tvRoles->Width = coRes->Filer->ReadInt();
}
//---------------------------------------------------------------------------

void __fastcall TfmvRoles::coResSave( TObject *Sender )
{
  inherited::coResSave( Sender );
  SaveNodeAdmins();
  SaveTrees();
  SaveGrids();
  coRes->Filer->WriteInt( tvRoles->Width );
}
//---------------------------------------------------------------------------

void __fastcall TfmvRoles::LoadNodeAdmins()
{
  naRoleKind->LoadFromFiler( coRes->Filer );
}

void __fastcall TfmvRoles::SaveNodeAdmins()
{
  naRoleKind->SaveToFiler( coRes->Filer );
}

void __fastcall TfmvRoles::LoadTrees()
{
  tvRoles->LoadFromFiler( coRes->Filer );
}

void __fastcall TfmvRoles::SaveTrees()
{
  tvRoles->SaveToFiler( coRes->Filer );
}

void __fastcall TfmvRoles::LoadGrids()
{
  dgRoles->LoadFromFiler( coRes->Filer );
}

void __fastcall TfmvRoles::SaveGrids()
{
  dgRoles->SaveToFiler( coRes->Filer );
}

void __fastcall TfmvRoles::coResEndLoad( TObject *Sender )
{
  splRoles->Left = tvRoles->Left + tvRoles->Width + 1;
}
//---------------------------------------------------------------------------

void __fastcall TfmvRoles::FormCreate( TObject *Sender )
{
  inherited::FormCreate( Sender );

  tvRoles->StartAdmin();
}
//---------------------------------------------------------------------------

void __fastcall TfmvRoles::FormDestroy( TObject *Sender )
{
  inherited::FormDestroy( Sender );

  tvRoles->FinishAdmin();
}
//---------------------------------------------------------------------------

void __fastcall TfmvRoles::dgRolesDBCut( TObject *Sender )
{
  dgRoles->CWSelect( dmvNewNavadvipa->quRoleEntityID, &dmvNewNavadvipa->BufferIntBox, true );
}
//---------------------------------------------------------------------------

void __fastcall TfmvRoles::dgRolesDBPaste( TObject *Sender )
{
  dmvNewNavadvipa->quRole->DBPaste( dmvNewNavadvipa->BufferIntBox, dmvNewNavadvipa->quDB, dmvNewNavadvipa->quRoleKindKindID );
}
//---------------------------------------------------------------------------

void __fastcall TfmvRoles::dgRolesDrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
  if ( !State.Contains( gdFocused ) && !dgRoles->IsCurrentSelected() ) {
    TField *f = dmvNewNavadvipa->quRoleKindID;
    if ( !f->IsNull )
      dmvNewNavadvipa->DBGridColor( dgRoles, f->AsLargeInt );
  }
  dgRoles->DefaultDrawColumnCell( Rect, DataCol, Column, State );
}
//---------------------------------------------------------------------------

void __fastcall TfmvRoles::naRoleKindFirstEnter( TObject *Sender )
{
  dmvNewNavadvipa->quRoleKind->CWOpen();
  dmvNewNavadvipa->quRole->CWOpen();
}
//---------------------------------------------------------------------------

void __fastcall TfmvRoles::naRoleKindLastExit( TObject *Sender )
{
  dmvNewNavadvipa->quRole->CWClose();
  dmvNewNavadvipa->quRoleKind->CWClose();
}
//---------------------------------------------------------------------------

void __fastcall TfmvRoles::naRoleKindEnter( TObject *Sender )
{
  DataSet = dmvNewNavadvipa->quRoleKind;
}
//---------------------------------------------------------------------------

void __fastcall TfmvRoles::naRoleKindGetNodeParams( TObject *Sender, TNNVNodeParams &NodeParams )
{
  dmvNewNavadvipa->SetNodeParamsRoleKind( NodeParams );
}
//---------------------------------------------------------------------------

void __fastcall TfmvRoles::naRoleKindLoadNodes( TObject *Sender )
{
  tvRoles->LoadNodeAdmin( nullptr, naRoleKind, NNV::RootRoleKindID );
}
//---------------------------------------------------------------------------

void __fastcall TfmvRoles::CloseValid()
{
  inherited::CloseValid();
  FillMultiResult( dgRoles, dmvNewNavadvipa->quRoleEntityID, dmvNewNavadvipa->quRoleEntity );
}

