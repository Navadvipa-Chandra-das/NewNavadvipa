// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef VCL_NNFmDateTimeH
#define VCL_NNFmDateTimeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.ActnList.hpp>
#include "VCL_NNActionList.h"
#include "VCL_NNCalendar.h"
#include "VCL_NNDBMiracle.h"
#include "VCL_NNFlagBox.h"
#include "VCL_NNFmRes.h"
#include "VCL_NNPanel.h"
#include "VCL_NNRightsManager.h"
#include "VCL_NNLanguageManager.h"
//---------------------------------------------------------------------------
class PACKAGE TfmvDateTime : public TfmvRes
{
__published:	// IDE-managed Components
  TNNVPanel *paTop;
  TSpeedButton *sbMonthPrior;
  TSpeedButton *sbMonthNext;
  TSpeedButton *sbCurrentDate;
  TLabel *laLeap;
  TEdit *edYear;
  TUpDown *udYear;
  TNNVCalendar *Calendar;
  TNNVPanel *paBevel;
  TNNVPanel *paTime;
  TLabel *laTime;
  TMaskEdit *meTime;
  TSpeedButton *sbOk;
  TSpeedButton *sbCancel;
  TComboBox *cbMonth;
  void __fastcall sbMonthPriorClick(TObject *Sender);
  void __fastcall sbMonthNextClick(TObject *Sender);
  void __fastcall sbCurrentDateClick(TObject *Sender);
  void __fastcall edYearChange(TObject *Sender);
  void __fastcall edYearExit(TObject *Sender);
  void __fastcall CalendarDblClick(TObject *Sender);
  void __fastcall CalendarChange(TObject *Sender);
  void __fastcall udYearClick(TObject *Sender, TUDBtnType Button);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
    TShiftState Shift);
  void __fastcall sbCancelClick(TObject *Sender);
  void __fastcall cbMonthChange(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
  using inherited = TfmvRes;
  bool fClick;
  TDateTime __fastcall GetDateTime();
  void __fastcall SetDateTime( TDateTime value );
  void __fastcall SetNeedTime( bool value );
  bool __fastcall GetNeedTime() { return paTime->Visible; };
protected:
  virtual void __fastcall CloseValid();
public:		// User declarations
  __fastcall TfmvDateTime(TComponent* Owner);
  __property TDateTime DateTime = { read = GetDateTime, write = SetDateTime };
  __property bool NeedTime = { read = GetNeedTime, write = SetNeedTime };
};
//---------------------------------------------------------------------------
extern PACKAGE TfmvDateTime *fmvDateTime;
//---------------------------------------------------------------------------
#endif
