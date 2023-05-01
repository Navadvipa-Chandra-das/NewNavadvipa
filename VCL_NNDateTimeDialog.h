//---------------------------------------------------------------------------

#ifndef VCL_NNDateTimeDialogH
#define VCL_NNDateTimeDialogH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "VCL_NNDialogExec.h"
//---------------------------------------------------------------------------

class PACKAGE TNNVDateTimeDialog : public TNNVDialogExec
{
private:
  using inherited = TNNVDialogExec;
  TDateTime FDateTime;
  bool FNeedTime;
  void __fastcall SetNeedTime( bool Value );
  void __fastcall SetDateTime( TDateTime Value );
protected:
  virtual void __fastcall DoGetDialogForm( TCustomForm *&fm );
  virtual void __fastcall DoPrepare( TObject *Sender );
  virtual void __fastcall DoExecute( TObject *Sender );
public:
  __fastcall TNNVDateTimeDialog( TComponent* Owner );
  __fastcall ~TNNVDateTimeDialog();
  __property TDateTime DateTime = { read = FDateTime, write = SetDateTime };
__published:
  __property bool NeedTime = { read = FNeedTime, write = SetNeedTime, default = false };
  __property OnPrepare;
  __property OnUnPrepare;
  __property OnExecute;
};
//---------------------------------------------------------------------------
#endif
