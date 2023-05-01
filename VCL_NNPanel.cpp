// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNPanel.h"
#pragma resource "*.res"
#pragma package(smart_init)
// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNNVPanel *) {
  new TNNVPanel(NULL);
}

// ---------------------------------------------------------------------------
__fastcall TNNVPanel::TNNVPanel( TComponent* Owner )
  : inherited(Owner)
{
  TControlStyle c = ControlStyle;
  c = c >> csSetCaption;
  ControlStyle = c;

  BevelInner = bvNone;
  BevelOuter = bvNone;
}

// ---------------------------------------------------------------------------
namespace Vcl_nnpanel {
  void __fastcall PACKAGE Register() {
    TComponentClass classes[1] = {__classid(TNNVPanel)};
    RegisterComponents(L"VCL New Navadvipa", classes, 0);
  }
}
// ---------------------------------------------------------------------------
