// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNDialog.h"
#pragma link "VCL_NNDialogExec"
#pragma resource "*.res"
#pragma package(smart_init)
// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNNVDialog *) {
  new TNNVDialog(NULL);
}

// ---------------------------------------------------------------------------
__fastcall TNNVDialog::TNNVDialog(TComponent* Owner) : inherited(Owner) {
}

// ---------------------------------------------------------------------------
namespace Vcl_nndialog {
  void __fastcall PACKAGE Register() {
    TComponentClass classes[1] = {__classid(TNNVDialog)};
    RegisterComponents(L"VCL New Navadvipa", classes, 0);
  }
}
// ---------------------------------------------------------------------------
