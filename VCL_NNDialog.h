// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef VCL_NNDialogH
#define VCL_NNDialogH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <Vcl.Controls.hpp>
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
#include "VCL_NNDialogExec.h"

// ---------------------------------------------------------------------------
class PACKAGE TNNVDialog : public TNNVDialogExec {
private:
  using inherited = TNNVDialogExec;

protected:
public:
  __fastcall TNNVDialog(TComponent* Owner);

__published:
  __property OnGetDialogForm;
  __property OnPrepare;
  __property OnUnPrepare;
  __property OnExecute;
};
// ---------------------------------------------------------------------------
#endif
