// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef VCL_NNDialogExecH
#define VCL_NNDialogExecH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <Vcl.Controls.hpp>
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
// ---------------------------------------------------------------------------

using TNNVOnGetDlgForm = PACKAGE void __fastcall( __closure * )( System::TObject* Sender, TCustomForm *&fm );

class PACKAGE TNNVDialogExec : public TComponent {
private:
  using inherited = TComponent;
  TNNVOnGetDlgForm fOnGetDialogForm;
  TNotifyEvent fOnPrepare;
  TNotifyEvent fOnUnPrepare;
  TNotifyEvent fOnExecute;

protected:
  virtual void __fastcall DoGetDialogForm( TCustomForm *&fm );
  virtual void __fastcall DoPrepare(TObject *Sender);
  virtual void __fastcall DoUnPrepare(TObject *Sender);
  virtual void __fastcall DoExecute(TObject *Sender);
  __property TNNVOnGetDlgForm OnGetDialogForm = { read = fOnGetDialogForm, write = fOnGetDialogForm };
  __property TNotifyEvent OnPrepare = { read = fOnPrepare, write = fOnPrepare };
  __property TNotifyEvent OnUnPrepare = { read = fOnUnPrepare, write = fOnUnPrepare };
  __property TNotifyEvent OnExecute = { read = fOnExecute, write = fOnExecute };

public:
  __fastcall TNNVDialogExec(TComponent* Owner);
  void __fastcall Execute( TComponent *SenderForm );
  void __fastcall Execute( TRect R, TComponent *SenderForm );
  void __fastcall Execute( TControl *Control, TComponent *SenderForm );

__published:
};
// ---------------------------------------------------------------------------
#endif
