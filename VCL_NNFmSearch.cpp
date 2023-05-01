// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFmSearch.h"
#include <Data.DB.hpp>
#include "VCL_NNFrDiapazon.h"
#include "VCL_NNDmNewNavadvipa.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNActionList"
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNFlagBox"
#pragma link "VCL_NNFmRes"
#pragma link "VCL_NNRightsManager"
#pragma link "VCL_NNLanguageManager"
#pragma resource "*.dfm"

TfmvSearch *fmvSearch;

// ---------------------------------------------------------------------------
__fastcall TfmvSearch::TfmvSearch(TComponent* Owner)
  : inherited( Owner )
{
  FUseTag = true;
}

__fastcall TfmvSearch::TfmvSearch( TComponent* Owner, bool tag )
  : inherited( Owner )
{
  FUseTag = tag;

  if ( !FUseTag ) {
    BorderStyle               = bsToolWindow;
    rgFilterSearch->ItemIndex = 1;
  }
}

void __fastcall TfmvSearch::rgDirectionClick( TObject *Sender )
{
  rgStartPoint->Enabled = ( rgDirection->ItemIndex != 1 );
}
// ---------------------------------------------------------------------------

void __fastcall TfmvSearch::buClearClick( TObject *Sender )
{
  TComboBox *cb;
  TfrvDiapazon *frD;

  for ( int I = 0; I < sbSkip->ComponentCount; ++I ) {
    cb = dynamic_cast< TComboBox* >( sbSkip->Components[ I ] );
    if ( cb ) {
      if ( cb->Style == csDropDownList )
        cb->ItemIndex = (int)NNV::TBoolExtended::Any;
      else
        cb->Text = L"";
    } else {
      frD = dynamic_cast< TfrvDiapazon* >( sbSkip->Components[ I ] );
      if ( frD ) {
        frD->IsEmpty = true;
      }
    }
  }
}
// ---------------------------------------------------------------------------

NNV::TSearchDlgOptions __fastcall TfmvSearch::GetSearchDlgOptions()
{
  return NNV::TSearchDlgOptions( NNV::TSearchOptions( ckCaseSensitive->Checked
                                                    , ckAnyEntry->Checked
                                                    , ckNotThis->Checked
                                                    , ckIsSoft->Checked
                                                    , ckIsMistake->Checked
                                                    , ckRegularExpression->Checked )
                               , rgDirection->ItemIndex == 1
                               , rgStartPoint->ItemIndex == 0
                               , rgOperation->ItemIndex == 0
                               , rgFilterSearch->ItemIndex == 0 );
}

void __fastcall TfmvSearch::SetSearchDlgOptions( const NNV::TSearchDlgOptions &Value )
{
  ckCaseSensitive->Checked     = Value.SearchOptions.CaseSensitive;
  ckAnyEntry->Checked          = Value.SearchOptions.AnyEntry;
  ckNotThis->Checked           = Value.SearchOptions.NotThis;
  ckIsSoft->Checked            = Value.SearchOptions.IsSoft;
  ckIsMistake->Checked         = Value.SearchOptions.IsMistake;
  ckRegularExpression->Checked = Value.SearchOptions.IsRegularExpression;
  rgDirection->ItemIndex       = Value.Backward     ? 1 : 0;
  rgStartPoint->ItemIndex      = Value.StartIsBegin ? 0 : 1;
  rgOperation->ItemIndex       = Value.IsAND        ? 0 : 1;
  rgFilterSearch->ItemIndex    = Value.IsFilter     ? 0 : 1;
}

void __fastcall TfmvSearch::ckIsSoftClick( TObject *Sender )
{
  ckCaseSensitive->Enabled = !ckIsSoft->Checked;
}
// ---------------------------------------------------------------------------

void __fastcall TfmvSearch::ckRegularExpressionClick( TObject *Sender )
{
  bool B = !ckRegularExpression->Checked;

  ckIsSoft->Enabled        = B;
  ckIsMistake->Enabled     = B;
  ckAnyEntry->Enabled      = B;
}
//---------------------------------------------------------------------------

void __fastcall TfmvSearch::buOKClick( TObject *Sender )
{
  // Для того, чтобы поля ввода данных периодов в потере фокуса примеляли введенные в них данные поиска!
  buOK->SetFocus();
  CloseDialog( true );
}
//---------------------------------------------------------------------------

void __fastcall TfmvSearch::buCancelClick( TObject *Sender )
{
  CloseDialog( false );
}
//---------------------------------------------------------------------------

void __fastcall TfmvSearch::rgFilterSearchClick( TObject *Sender )
{
  bool B = rgFilterSearch->ItemIndex == 1;

  rgDirection->Enabled  = B;
  rgStartPoint->Enabled = B;
}
//---------------------------------------------------------------------------

void __fastcall TfmvSearch::FormCreate(TObject *Sender)
{
  inherited::FormCreate( Sender );

  rgFilterSearchClick( rgFilterSearch );
}
//---------------------------------------------------------------------------

