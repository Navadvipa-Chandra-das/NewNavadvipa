//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFmActionList.h"
#include "VCL_NNColor.h"
#include "VCL_NNColorIndex.h"
#include <algorithm>
#include <Vcl.ActnList.hpp>
#include "VCL_NNDmNewNavadvipa.h"
#include <memory>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNActionList"
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNDrawGrid"
#pragma link "VCL_NNFlagBox"
#pragma link "VCL_NNFmRes"
#pragma link "VCL_NNPanel"
#pragma link "VCL_NNRightsManager"
#pragma link "VCL_NNLanguageManager"
#pragma resource "*.dfm"
TfmvActionList *fmvActionList;

namespace NNV {

const int ShortCutWidth = 100;

}

//---------------------------------------------------------------------------
__fastcall TfmvActionList::TfmvActionList(TComponent* Owner)
  : inherited(Owner)
  , fActionImage( NULL )
  , ActionVector()
{
}
//---------------------------------------------------------------------------

void __fastcall TfmvActionList::Execute( TActionList *AList )
{
  if ( !AList )
    return;

  fActionImage = AList->Images;

  ActionVector.reserve( AList->ActionCount );
  ActionVector.clear();
  for ( int i = 0; i < AList->ActionCount; ++i )
    if ( !( !AList->Actions[ i ]->Visible || !AList->Actions[ i ]->Enabled ) )
      ActionVector.push_back( AList->Actions[ i ] );

    std::sort( ActionVector.begin(), ActionVector.end()
             , [] ( TContainedAction *a, TContainedAction *b )
               {
                 return a->Caption < b->Caption;
               }
             );

  dgAction->RowCount = ActionVector.size();

  ShowDialog( Owner );
}

void __fastcall TfmvActionList::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if ( Key == vkEscape ) {
    Key = 0;
    Close();
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmvActionList::buSetClick(TObject *Sender)
{
  unsigned int ARow = dgAction->Row;

  if ( ActionVector.size() <= ARow )
    return;

  ActionVector[ ARow ]->ShortCut = hkAction->HotKey;
  dgAction->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfmvActionList::dgActionDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
  int LA = ActionVector.size();

  if ( LA <= ARow )
    return;

  int L = Rect.Left + Rect.Height() + 2, R = Rect.Top + 2;

  TContainedAction *a = ActionVector[ ARow ];

  if ( !a )
    return;

  TColor FontColor, FonColor;

  GetColor( a, FontColor, FonColor );

  if ( ARow == dgAction->Row )
    dgAction->Canvas->Font->Style = dgAction->Canvas->Font->Style << fsUnderline;
  else
    dgAction->Canvas->Font->Style = dgAction->Canvas->Font->Style >> fsUnderline;

  dgAction->Canvas->Font->Color  = FontColor;
  dgAction->Canvas->Brush->Color = FonColor;

  switch ( ACol ) {
  case 0 :
    dgAction->Canvas->TextRect( Rect, L, R, a->Caption );
    if ( ActionImage != NULL ) {
      std::unique_ptr< TBitmap > bm( new TBitmap );
      ActionImage->GetBitmap( a->ImageIndex, bm.get() );
      dgAction->Canvas->Draw( Rect.Left, Rect.Top, bm.get() );
    }
    break;
  case 1 :
    dgAction->Canvas->TextRect( Rect, L, R, ShortCutToText( a->ShortCut ) );
    break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmvActionList::GetColor( TContainedAction *a
                                       , TColor &FontColor
                                       , TColor &FonColor )
{
  Word Key_;
  Classes::TShiftState Shift_;

  ShortCutToKey( a->ShortCut, Key_, Shift_ );

  if ( Key_ == 0 ) {
    FontColor  = dmvNewNavadvipa->ColorVector[ NNColor::EmptyHotKey ].FontColor;
    FonColor   = dmvNewNavadvipa->ColorVector[ NNColor::EmptyHotKey ].FonColor;
  } else if ( Shift_ == Classes::TShiftState() ) {
    FontColor  = dmvNewNavadvipa->ColorVector[ NNColor::HotKeyWithoutShift ].FontColor;
    FonColor   = dmvNewNavadvipa->ColorVector[ NNColor::HotKeyWithoutShift ].FonColor;
  } else {
    FontColor  = dmvNewNavadvipa->ColorVector[ NNColor::HotKey ].FontColor;
    FonColor   = dmvNewNavadvipa->ColorVector[ NNColor::HotKey ].FonColor;
  }
}

void __fastcall TfmvActionList::dgActionSelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
  int LA = ActionVector.size();

  if ( LA <= ARow )
    return;

  TColor FontColor, FonColor;

  GetColor( ActionVector[ ARow ], FontColor, FonColor );

  edAction->Font->Color = FontColor;
  edAction->Color       = FonColor;

  edAction->Text   = ActionVector[ ARow ]->Caption;
  hkAction->HotKey = ActionVector[ ARow ]->ShortCut;
}
//---------------------------------------------------------------------------

void __fastcall TfmvActionList::FormResize(TObject *Sender)
{
  dgAction->ColWidths[ 0 ] = dgAction->ClientWidth - NNV::ShortCutWidth - dgAction->GridLineWidth;
  dgAction->ColWidths[ 1 ] = NNV::ShortCutWidth;
}
//---------------------------------------------------------------------------

void __fastcall TfmvActionList::FormCreate(TObject *Sender)
{
  inherited::FormCreate( Sender );
  dgAction->OptimalDefaultRowHeight();
}
//---------------------------------------------------------------------------

