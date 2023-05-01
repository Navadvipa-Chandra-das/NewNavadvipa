//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "FMX_NNFmActionList.h"
#include "FMX_NNColor.h"
#include "FMX_NNColorIndex.h"
#include "FMX_NNDmNewNavadvipa.h"
#include <algorithm>
#include <memory>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FMX_NNDBMiracle"
#pragma link "FMX_NNFlagBox"
#pragma link "FMX_NNFmRes"
#pragma link "FMX_NNLanguageManager"
#pragma link "FMX_NNRightsManager"
#pragma link "FMX_NNActionList"
#pragma resource "*.fmx"
TfmfActionList *fmfActionList;

namespace NNF {

const int ShortCutWidth = 100;

}

//---------------------------------------------------------------------------
__fastcall TfmfActionList::TfmfActionList(TComponent* Owner)
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

void __fastcall TfmfActionList::Execute( TActionList *AList )
{
  if ( !AList )
    return;

  FActionImage = AList->Images;

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

  //dgAction->RowCount = ActionVector.size();

  ShowDialog( Owner );
}

void __fastcall TfmfActionList::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
  if ( Key == vkEscape ) {
    Key = 0;
    Close();
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmfActionList::buSetClick(TObject *Sender)
{
  //unsigned int ARow = dgAction->Row;

  //if ( ActionVector.size() <= ARow )
  //  return;

  //ActionVector[ ARow ]->ShortCut = hkAction->HotKey;
  //dgAction->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfmfActionList::GetColor( TContainedAction *a
                                        , TAlphaColor &FontColor
                                        , TAlphaColor &FonColor )
{
  Word Key_;
  TShiftState Shift_;

  //ShortCutToKey( a->ShortCut, Key_, Shift_ );

  if ( Key_ == 0 ) {
    FontColor  = dmfNewNavadvipa->ColorVector[ NNColor::EmptyHotKey ].FontColor;
    FonColor   = dmfNewNavadvipa->ColorVector[ NNColor::EmptyHotKey ].FonColor;
  } else if ( Shift_ == Classes::TShiftState() ) {
    FontColor  = dmfNewNavadvipa->ColorVector[ NNColor::HotKeyWithoutShift ].FontColor;
    FonColor   = dmfNewNavadvipa->ColorVector[ NNColor::HotKeyWithoutShift ].FonColor;
  } else {
    FontColor  = dmfNewNavadvipa->ColorVector[ NNColor::HotKey ].FontColor;
    FonColor   = dmfNewNavadvipa->ColorVector[ NNColor::HotKey ].FonColor;
  }
}

