// Wanderer library - author Oleg Zolotyh e-mail alejan@rambler.ru
#ifndef VCL_NNComboBoxH
#define VCL_NNComboBoxH
//---------------------------------------------------------------------------
#include <Vcl.Mask.hpp>
#include "VCL_NNDialog.h"
//---------------------------------------------------------------------------
class PACKAGE TNNVComboBox : public TMaskEdit
{
private:
  using inherited = TMaskEdit;
  TNotifyEvent fOnExecute;
  TNNVDialog *fDialog;
  void __fastcall SetDialog( TNNVDialog *Value );
  TRect __fastcall GetCWRect();
protected:
  DYNAMIC void __fastcall KeyDown(Word &Key,  TShiftState Shift);
  virtual void __fastcall ButtonClick( TComponent *SenderForm );
  virtual void __fastcall Notification(TComponent *AComponent, TOperation Operation);
  virtual void __fastcall DoExecute();
public:
  __fastcall TNNVComboBox( TComponent* Owner );
  __property TRect CWRect = { read = GetCWRect };
__published:
  __property EditMask;
  __property TNotifyEvent OnExecute = { read = fOnExecute, write = fOnExecute };
  __property TNNVDialog* Dialog = { read = fDialog, write = SetDialog };
};
//---------------------------------------------------------------------------
#endif

