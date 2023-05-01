// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFmDBGrid.h"
#include "VCL_NNDmNewNavadvipa.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNFlagBox"
#pragma link "VCL_NNFmRes"
#pragma link "VCL_NNRightsManager"
#pragma link "VCL_NNPanel"
#pragma link "VCL_NNActionList"
#pragma link "VCL_NNLanguageManager"
#pragma resource "*.dfm"
TfmvDBGrid *fmvDBGrid;

// ---------------------------------------------------------------------------
__fastcall TfmvDBGrid::TfmvDBGrid(TComponent* Owner)
  : inherited( Owner )
{
}
// ---------------------------------------------------------------------------

void __fastcall TfmvDBGrid::clGridClickCheck( TObject *Sender )
{
  ( ( TColumn* )( clGrid->Items->Objects[ clGrid->ItemIndex ] ) )->Visible = clGrid->Checked[ clGrid->ItemIndex ];
}
// ---------------------------------------------------------------------------

void __fastcall TfmvDBGrid::Execute( TNNVDBGrid *Grid )
{
  if ( !Grid )
    return;

  fGrid = Grid;

  PrepareOptions( Grid );

  TNNVQuery *od = dynamic_cast< TNNVQuery* >( Grid->DataSource->DataSet );
  if ( od )
    Caption = Caption + " " + od->Note;

  for ( int i = 0; i < Grid->Columns->Count; i++ ) {
    clGrid->Items->AddObject( Grid->Columns->Items[ i ]->Title->Caption, Grid->Columns->Items[ i ] );
    clGrid->Checked[ i ] = Grid->Columns->Items[ i ]->Visible;
  }

  if ( clGrid->Items->Count > 0 ) {
    clGrid->ItemIndex = 0;
    clGridClick( clGrid );
  }

  ShowDialog( Grid->Owner );
}

void __fastcall TfmvDBGrid::FormKeyDown( TObject *Sender, WORD &Key, TShiftState Shift)
{
  if ( Key == vkEscape ) {
    Key = 0;
    CloseDialog( false );
  }
}
// ---------------------------------------------------------------------------

void __fastcall TfmvDBGrid::FormCreate(TObject *Sender)
{
  fdColor = dmvNewNavadvipa->cdNN;
  inherited::FormCreate( Sender );
}
// ---------------------------------------------------------------------------

void __fastcall TfmvDBGrid::clGridClick( TObject *Sender )
{
  TNNVGridColumn* C = ( ( TNNVGridColumn* )( clGrid->Items->Objects[ clGrid->ItemIndex ] ) );
  edTitleCaption->Text = C->Title->Caption;
  paFont->ParentColor = false;
  switch ( rgFontOwner->ItemIndex ) {
  case 0:
    paFont->Font->Assign( fGrid->Font );
    paColor->Color      = fGrid->Color;
    paFont->Color       = fGrid->Color;
    paColorFont->Color  = fGrid->Font->Color;
    break;
  case 1:
    paFont->Font->Assign( C->Title->Font );
    paColor->Color      = C->Title->Color;
    paFont->Color       = C->Title->Color;
    paColorFont->Color  = C->Title->Font->Color;
    break;
  case 2:
    paFont->Font->Assign( C->Font );
    paColor->Color      = C->Color;
    paFont->Color       = C->Color;
    paColorFont->Color  = C->Font->Color;
    break;
  }

  cbIsFilteredColumn->Checked = C->IsFiltered;
}
// ---------------------------------------------------------------------------

void __fastcall TfmvDBGrid::edTitleCaptionChange(TObject *Sender)
{
  ( ( TColumn* )( clGrid->Items->Objects[ clGrid->ItemIndex ] ) )->Title->Caption =
      edTitleCaption->Text;
}
// ---------------------------------------------------------------------------

void __fastcall TfmvDBGrid::paFontDblClick(TObject *Sender)
{
  fdGrid->Font->Assign( paFont->Font );
  bool SB = DialogCloseOnDeactivate;
  DialogCloseOnDeactivate = false;
  try {
    if ( fdGrid->Execute() ) {
      paFont->Font->Assign( fdGrid->Font );
      switch ( rgFontOwner->ItemIndex ) {
      case 0:
        fGrid->Font->Assign( fdGrid->Font );
        break;
      case 1:
        ( ( TColumn* )( clGrid->Items->Objects[ clGrid->ItemIndex ] ) )->Title->Font->Assign( fdGrid->Font );
        break;
      case 2:
        ( ( TColumn* )( clGrid->Items->Objects[ clGrid->ItemIndex ] ) )->Font->Assign( fdGrid->Font );
        break;
      }
    }
  } __finally {
    DialogCloseOnDeactivate = SB;
  }
}
// ---------------------------------------------------------------------------

void __fastcall TfmvDBGrid::paColorDblClick(TObject *Sender)
{
  fdColor->Color = paColor->Color;
  bool SB = DialogCloseOnDeactivate;
  DialogCloseOnDeactivate = false;
  try {
    if ( fdColor->Execute() ) {
      paColor->Color = fdColor->Color;
      paFont->Color  = fdColor->Color;
      switch ( rgFontOwner->ItemIndex ) {
      case 0:
        fGrid->Color = fdColor->Color;
        break;
      case 1:
        ( ( TColumn* )( clGrid->Items->Objects[ clGrid->ItemIndex ] ) )->Title->Color = fdColor->Color;
        break;
      case 2:
        ( ( TColumn* )( clGrid->Items->Objects[ clGrid->ItemIndex ] ) )->Color = fdColor->Color;
        break;
      }
    }
  } __finally {
    DialogCloseOnDeactivate = SB;
  }
}
// ---------------------------------------------------------------------------

void __fastcall TfmvDBGrid::PrepareOptions( TNNVDBGrid *Grid )
{
  cbTitle->Checked         = Grid->Options.Contains( dgTitles );
  cbConfirmDelete->Checked = Grid->Options.Contains( dgConfirmDelete );
  cbTabs->Checked          = Grid->Options.Contains( dgTabs );
  cbRowLines->Checked      = Grid->Options.Contains( dgRowLines );
  cbColLines->Checked      = Grid->Options.Contains( dgColLines );
}

void __fastcall TfmvDBGrid::cbGridOption( TObject *Sender )
{
  TCheckBox *cb = dynamic_cast< TCheckBox* >( Sender );
  TDBGridOptions Opt = Grid->Options;
  if ( cb->Checked )
    Opt = Opt << ( TDBGridOption )cb->Tag;
  else
    Opt = Opt >> ( TDBGridOption )cb->Tag;
  Grid->Options = Opt;
  Grid->Refresh();
}
// ---------------------------------------------------------------------------

void __fastcall TfmvDBGrid::buFontColorClick( TObject *Sender )
{
  int ii = rgFontOwner->ItemIndex;

  switch ( ii ) {
  case 0:
    fdColor->Color = fGrid->Font->Color;
    break;
  case 1:
    fdColor->Color = ( ( TColumn* )( clGrid->Items->Objects[ clGrid->ItemIndex ] ) )->Title->Font->Color;
    break;
  case 2:
    fdColor->Color = ( ( TColumn* )( clGrid->Items->Objects[ clGrid->ItemIndex ] ) )->Font->Color;
    break;
  }

  bool SB = DialogCloseOnDeactivate;
  DialogCloseOnDeactivate = false;
  try {
    if ( fdColor->Execute() ) {
      switch ( ii ) {
      case 0:
        fGrid->Font->Color = fdColor->Color;
        break;
      case 1:
        ( ( TColumn* )( clGrid->Items->Objects[ clGrid->ItemIndex ] ) )->Title->Font->Color = fdColor->Color;
        break;
      case 2:
        ( ( TColumn* )( clGrid->Items->Objects[ clGrid->ItemIndex ] ) )->Font->Color = fdColor->Color;
        break;
      }
    }
  } __finally {
    DialogCloseOnDeactivate = SB;
  }
}
// ---------------------------------------------------------------------------

void __fastcall TfmvDBGrid::cbIsFilteredColumnClick( TObject *Sender )
{
  ( ( TNNVGridColumn* )( clGrid->Items->Objects[ clGrid->ItemIndex ] ) )->IsFiltered = cbIsFilteredColumn->Checked;
}
// ---------------------------------------------------------------------------

