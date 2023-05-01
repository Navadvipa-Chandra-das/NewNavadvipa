// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNCalendar.h"
#pragma resource "*.res"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
namespace Vcl_nncalendar {
  void __fastcall PACKAGE Register() {
    TComponentClass classes[1] = {__classid(TNNVCalendar)};
    RegisterComponents(L"VCL New Navadvipa", classes, 0);
  }
}

// ---------------------------------------------------------------------------
__fastcall TNNVCalendar::TNNVCalendar(TComponent *AOwner) : inherited(AOwner) {
  FUseCurrentDate = true;
  FixedCols = 0;
  FixedRows = 1;
  ColCount = 7;
  RowCount = 7;
  StartOfWeek = 1;
  ScrollBars = ssNone;
  FDate = Date();
  (Options >> goRangeSelect) << goDrawFocusSelected;
  UpdateCalendar();
}

void __fastcall TNNVCalendar::Change() {
  if (FOnChange)
    FOnChange(this);
}

void __fastcall TNNVCalendar::Click() {
  String TheCellText;

  TheCellText = CellText[Col][Row];
  if (!TheCellText.IsEmpty())
    Day = (unsigned short)TheCellText.ToInt();
}

/* Don't have any leap year code available.  Seemed like a straigthforward
 translation, but should be checked.
 */
bool __fastcall TNNVCalendar::IsLeapYear(int AYear) {
  return ((AYear % 4) == 0) && (((AYear % 100) != 0) || ((AYear % 400) == 0));
};

unsigned short __fastcall TNNVCalendar::DaysPerMonth(int AYear, int AMonth) {
  unsigned short result;
  const unsigned short DaysInMonth[12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  result = DaysInMonth[AMonth - 1];
  if ((AMonth == 2) && IsLeapYear(AYear))
    ++result; // leap-year Feb is special

  return result;
};

int __fastcall TNNVCalendar::DaysThisMonth() {
  return DaysPerMonth(Year, Month);
};

void __fastcall TNNVCalendar::DrawCell(int ACol, int ARow, const TRect &ARect,
    TGridDrawState /* AState */) {
  const String TheText = CellText[ACol][ARow];
  Canvas->TextRect(ARect, ARect.Left + (ARect.Right - ARect.Left -
      Canvas->TextWidth(TheText)) / 2,
      ARect.Top + (ARect.Bottom - ARect.Top - Canvas->TextHeight(TheText)) / 2,
      TheText);
};

String __fastcall TNNVCalendar::GetCellText(int ACol, int ARow) {
  int DayNum;
  String result;

  if (!ARow)
      // day names at tops of columns
      //
        result = FormatSettings.ShortDayNames[(StartOfWeek + ACol) % 7];
  else {
    DayNum = FMonthOffset + ACol + (ARow - 1) * 7;
    if ((DayNum < 1) || (DayNum > DaysThisMonth()))
      result = "";
    else
      result = IntToStr(DayNum);
  }

  return result;
};

bool __fastcall TNNVCalendar::SelectCell(int ACol, int ARow) {
  bool result;

  if ((!FUpdating && FReadOnly) || CellText[ACol][ARow].IsEmpty())
    result = false;
  else
    result = inherited::SelectCell(ACol, ARow);

  return result;
};

void __fastcall TNNVCalendar::SetCalendarDate(TDateTime Value) {
  FDate = Value;
  UpdateCalendar();
  Change();
};

bool __fastcall TNNVCalendar::StoreCalendarDate() {
  return !FUseCurrentDate;
};

unsigned short __fastcall TNNVCalendar::GetDateElement(int Index) {
  unsigned short AYear, AMonth, ADay, result;

  DecodeDate(FDate, AYear, AMonth, ADay);
  switch (Index) {
  case 1:
    result = AYear;
    break;

  case 2:
    result = AMonth;
    break;

  case 3:
    result = ADay;
    break;

  default:
    result = -1;
  };

  return result;
};

// #pragma warn -sig
void __fastcall TNNVCalendar::SetDateElement(int Index, unsigned short Value) {
  unsigned short AYear, AMonth, ADay;
  bool Update = false;

  if (Value > 0) {
    DecodeDate(FDate, AYear, AMonth, ADay);
    switch (Index) {
    case 1:
      if (AYear != Value) {
        AYear = Value;
        Update = true;
      }
      break;

    case 2:
      if ((Value <= 12) && (Value != AMonth)) {
        AMonth = Value;
        Update = true;
      }
      break;

    case 3:
      if ((Value <= DaysThisMonth()) && (Value != ADay)) {
        ADay = Value;
        Update = true;
      }
      break;
    }
    if (Update) {
      FDate = EncodeDate(AYear, AMonth, ADay);
      FUseCurrentDate = false;
      UpdateCalendar();
      Change();
    }
  };
};

void __fastcall TNNVCalendar::SetStartOfWeek(TDayOfWeek Value) {
  if ( ( Value > 7 ) || ( Value < 1 ) ) {
    FStartOfWeek = 1; // bad value sets to 1 (Sunday)
  } else {
    if ( Value != FStartOfWeek ) {
      FStartOfWeek = Value;
      UpdateCalendar( );
    }
  }
};

void __fastcall TNNVCalendar::SetUseCurrentDate( bool Value ) {
  if ( Value != FUseCurrentDate ) {
    FUseCurrentDate = Value;
    if ( Value ) {
      FDate = Date( ); // use the current date, then
      UpdateCalendar( );
    };
  };
};

// Given a value of 1 or -1, moves to Next or Prev month accordingly.
//
void __fastcall TNNVCalendar::ChangeMonth( int Delta )
{
  unsigned short AYear, AMonth, ADay, CurDay;
  TDateTime NewDate;

  DecodeDate( FDate, AYear, AMonth, ADay );
  CurDay = ADay;
  if (Delta > 0)
    ADay = DaysPerMonth( AYear, AMonth );
  else
    ADay = 1;

  NewDate = EncodeDate( AYear, AMonth, ADay );
  NewDate = NewDate + Delta;
  DecodeDate( NewDate, AYear, AMonth, ADay );
  if (DaysPerMonth( AYear, AMonth) > CurDay )
    ADay = CurDay;
  else
    ADay = DaysPerMonth( AYear, AMonth );

  CalendarDate = EncodeDate( AYear, AMonth, ADay );
};
// #pragma warn .sig

void __fastcall TNNVCalendar::PrevMonth()
{
  ChangeMonth( -1 );
}

void __fastcall TNNVCalendar::NextMonth()
{
  ChangeMonth( 1 );
}

void __fastcall TNNVCalendar::NextYear( )
{
  if ( IsLeapYear( Year ) && ( Month == 2 ) && ( Day == 29 ) )
    Day = 28;
  ++Year;
}

void __fastcall TNNVCalendar::PrevYear( )
{
  if ( IsLeapYear( Year ) && ( Month == 2 ) && ( Day == 29 ) )
    Day = 28;
  --Year;
}

void __fastcall TNNVCalendar::UpdateCalendar( )
{
  unsigned short AYear, AMonth, ADay;
  TDateTime FirstDate;

  FUpdating = True;
  DecodeDate( FDate, AYear, AMonth, ADay );
  FirstDate = EncodeDate( AYear, AMonth, 1 );

  // Day of week for 1st of month.
  //
  FMonthOffset = 2 - ( ( DayOfWeek( FirstDate ) - StartOfWeek + 7 ) % 7 );
  if ( FMonthOffset == 2 )
    FMonthOffset = -5;

  MoveColRow( ( ADay - FMonthOffset ) % 7, ( ADay - FMonthOffset ) / 7 + 1,
      False, False );
  Invalidate( );

  FUpdating = False;
};

void __fastcall TNNVCalendar::WMSize( TWMSize &Message )
{
  int GridLines;

  GridLines        = 6 * GridLineWidth;
  DefaultColWidth  = ( Message.Width  - GridLines ) / 7;
  DefaultRowHeight = ( Message.Height - GridLines ) / 7;

  inherited::Dispatch( &Message );
}

