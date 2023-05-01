// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef FMX_NNDialogExecH
#define FMX_NNDialogExecH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FMX.Forms.hpp>
// ---------------------------------------------------------------------------

using TNNFOnGetDlgForm = PACKAGE void __fastcall( __closure * )( System::TObject* Sender, TCommonCustomForm *&fm );

class PACKAGE TNNFDialogExec : public TComponent {
private:
  using inherited = TComponent;
  TNNFOnGetDlgForm fOnGetDialogForm;
  TNotifyEvent fOnPrepare;
  TNotifyEvent fOnUnPrepare;
  TNotifyEvent fOnExecute;

protected:
  virtual void __fastcall DoGetDialogForm( TCommonCustomForm *&fm );
  virtual void __fastcall DoPrepare(TObject *Sender);
  virtual void __fastcall DoUnPrepare(TObject *Sender);
  virtual void __fastcall DoExecute(TObject *Sender);
  __property TNNFOnGetDlgForm OnGetDialogForm = { read = fOnGetDialogForm, write = fOnGetDialogForm };
  __property TNotifyEvent OnPrepare = { read = fOnPrepare, write = fOnPrepare };
  __property TNotifyEvent OnUnPrepare = { read = fOnUnPrepare, write = fOnUnPrepare };
  __property TNotifyEvent OnExecute = { read = fOnExecute, write = fOnExecute };

public:
  __fastcall TNNFDialogExec(TComponent* Owner);
  void __fastcall Execute( TComponent *SenderForm );
  void __fastcall Execute( TRect R, TComponent *SenderForm );
  void __fastcall Execute( TControl *Control, TComponent *SenderForm );

__published:
};
// ---------------------------------------------------------------------------
#endif
