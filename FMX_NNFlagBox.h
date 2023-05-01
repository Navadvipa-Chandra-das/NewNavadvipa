// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef FMX_NNFlagBoxH
#define FMX_NNFlagBoxH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <FMX.Controls.hpp>
#include <System.Classes.hpp>
#include <FMX.Forms.hpp>
#include <Data.DB.hpp>
#include "FMX_NNConst.h"
// ---------------------------------------------------------------------------

class PACKAGE TNNFFlagBox : public TComponent {
private:
  using inherited = TComponent;
  TNotifyEvent FOnPrepare;
  TNotifyEvent FOnUnPrepare;
  TNotifyEvent FOnExecute;
  TNotifyEvent FOnSynchronization;
  bool FcaFree            = true;
  bool FShowInWindowList  = false;
  TField *FFieldNo        = nullptr;
  TField *FFieldName      = nullptr;
  TComponent *FSenderForm = nullptr;

protected:
public:
  __fastcall TNNFFlagBox( TComponent* Owner );
  virtual void __fastcall DoPrepare();
  virtual void __fastcall DoUnPrepare();
  virtual void __fastcall DoExecute();
  virtual void __fastcall DoSynchronization();
  __property TNotifyEvent OnPrepare = { read = FOnPrepare, write = FOnPrepare };
  __property TNotifyEvent OnUnPrepare = { read = FOnUnPrepare, write = FOnUnPrepare };
  __property TNotifyEvent OnExecute = { read = FOnExecute, write = FOnExecute };
  __property TField *FieldNo = { read = FFieldNo, write = FFieldNo };
  __property TField *FieldName = { read = FFieldName, write = FFieldName };
  __property TComponent *SenderForm = { read = FSenderForm, write = FSenderForm };

__published:
  __property bool caFree = { read = FcaFree, write = FcaFree, default = true };
  __property TNotifyEvent OnSynchronization = { read = FOnSynchronization, write = FOnSynchronization };
  __property bool ShowInWindowList = { read = FShowInWindowList, write = FShowInWindowList, default = false };
};
// ---------------------------------------------------------------------------

#endif
