// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFmDateTime.h"
#include "VCL_NNCommon.h"
#include "VCL_NNConst.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNFmRes"
#pragma link "VCL_NNActionList"
#pragma link "VCL_NNCalendar"
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNFlagBox"
#pragma link "VCL_NNFmRes"
#pragma link "VCL_NNPanel"
#pragma link "VCL_NNRightsManager"
#pragma link "VCL_NNLanguageManager"
#pragma resource "*.dfm"

TfmvDateTime *fmvDateTime;

namespace NNV {

const int fmDateHeight = 164;

}

//---------------------------------------------------------------------------
__fastcall TfmvDateTime::TfmvDateTime( TComponent* Owner )
  : inherited(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfmvDateTime::sbMonthPriorClick(TObject *Sender)
{
  Calendar->PrevMonth();
}

void __fastcall TfmvDateTime::sbMonthNextClick(TObject *Sender)
{
  Calendar->NextMonth();
}

void __fastcall TfmvDateTime::sbCurrentDateClick(TObject *Sender)
{
  TDateTime dt = Now();
  Calendar->CalendarDate = dt;
  if ( NeedTime )
    meTime->Text = FormatDateTime( NNVConst::LongTimeFormat, dt );
}

void __fastcall TfmvDateTime::edYearChange(TObject *Sender)
{
  if ( fClick )
    edYearExit( edYear );
}

void __fastcall TfmvDateTime::edYearExit(TObject *Sender)
{
  Calendar->Year = ( unsigned short )StrToInt( edYear->Text );
}

void __fastcall TfmvDateTime::CalendarDblClick(TObject *Sender)
{
  CloseDialog( true );
}

void __fastcall TfmvDateTime::CalendarChange(TObject *Sender)
{
  cbMonth->ItemIndex = Calendar->Month - 1;
  laLeap->Visible = NNV::IsLeapYear( Calendar->Year );
  edYear->Text = Calendar->Year;
}

void __fastcall TfmvDateTime::udYearClick(TObject *Sender, TUDBtnType Button)
{
  fClick = true;
  edYear->Text = StrToInt( edYear->Text ) - ( Button == Comctrls::btPrev ? 1: -1 );
  fClick = false;
}

void __fastcall TfmvDateTime::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  switch ( Key ) {
  case vkReturn :
    if ( cbMonth->DroppedDown )
      cbMonth->DroppedDown = false;
    else {
      if ( ActiveControl == edYear ) edYearExit( edYear );
      CloseDialog( true );
    }
    Key = 0;
    break;
  case vkEscape :
    if ( cbMonth->DroppedDown )
      cbMonth->DroppedDown = false;
    else
      CloseDialog( false );
    Key = 0;
    break;
  case vkPrior :
    if ( Shift.Contains( ssCtrl ) )
      Calendar->PrevYear();
    else
      sbMonthPrior->Click();
    Key = 0;
    break;
  case vkNext :
    if ( Shift.Contains( ssCtrl ) )
      Calendar->NextYear();
    else
      sbMonthNext->Click();
    Key = 0;
    break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmvDateTime::SetNeedTime( bool value )
{
  paTime->Visible = value;
  if ( value )
    ClientHeight = NNV::fmDateHeight;
  else
    ClientHeight = NNV::fmDateHeight - paTime->Height;
}

TDateTime __fastcall TfmvDateTime::GetDateTime()
{
  if ( NeedTime )
    return StrToDateTime( FormatDateTime( NNVConst::NlsDateFormatShort + NNVConst::Space, Calendar->CalendarDate ) + meTime->Text );
  else
    return Calendar->CalendarDate;
}

void __fastcall TfmvDateTime::SetDateTime( TDateTime value )
{
  Calendar->CalendarDate = value;
  if ( NeedTime )
    meTime->Text = FormatDateTime( NNVConst::LongTimeFormat, value );
}

void __fastcall TfmvDateTime::CloseValid()
{
  if ( NeedTime )
    FormatDateTime( NNVConst::LongTimeFormat, meTime->Text );
}

void __fastcall TfmvDateTime::sbCancelClick( TObject *Sender )
{
  CloseDialog( false );
}
//---------------------------------------------------------------------------

void __fastcall TfmvDateTime::cbMonthChange( TObject *Sender )
{
  Calendar->Month = (unsigned short)( cbMonth->ItemIndex + 1 );
}
//---------------------------------------------------------------------------

void __fastcall TfmvDateTime::FormCreate(TObject *Sender)
{
  inherited::FormCreate( Sender );
  for ( int i = 0; i < 12; ++i )
    cbMonth->Items->Add( FormatSettings.LongMonthNames[ i ] );
}
//---------------------------------------------------------------------------

