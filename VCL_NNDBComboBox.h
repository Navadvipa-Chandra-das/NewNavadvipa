// Wanderer library - author Oleg Zolotyh e-mail alejan@rambler.ru
#ifndef VCL_NNDBComboBoxH
#define VCL_NNDBComboBoxH
//---------------------------------------------------------------------------
#include <Vcl.DBCtrls.hpp>
#include "VCL_NNDialog.h"
//---------------------------------------------------------------------------
class PACKAGE TNNVDBComboBox : public TDBEdit
{
private:
  using inherited = TDBEdit;
  TNotifyEvent fOnExecute;
  TNNVDialog *fDialog;
  void __fastcall SetDialog( TNNVDialog *Value );
  TRect __fastcall GetCWRect();
  bool FIsFiltered = true;
  MESSAGE void __fastcall CMEnter( TCMEnter &Message );
protected:
  DYNAMIC void __fastcall KeyDown( Word &Key,  TShiftState Shift );
  virtual void __fastcall ButtonClick( TComponent *SenderForm );
  virtual void __fastcall Notification( TComponent *AComponent, TOperation Operation );
  virtual void __fastcall DoExecute();
public:
  __fastcall TNNVDBComboBox( TComponent* Owner );
  __property TRect CWRect = { read = GetCWRect };
__published:
  __property EditMask;
  __property TNotifyEvent OnExecute = { read = fOnExecute, write = fOnExecute };
  __property TNNVDialog* Dialog = { read = fDialog, write = SetDialog };
  __property bool IsFiltered = { read = FIsFiltered, write = FIsFiltered, default = true };
#pragma option push -w-inl
BEGIN_MESSAGE_MAP
  VCL_MESSAGE_HANDLER( CM_ENTER, TCMEnter, CMEnter );
END_MESSAGE_MAP(inherited);
#pragma option pop // -w-inl
};
//---------------------------------------------------------------------------
#endif

