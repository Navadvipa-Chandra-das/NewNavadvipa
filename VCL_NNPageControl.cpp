// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNPageControl.h"
#pragma resource "*.res"
#pragma package(smart_init)
// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNNVPageControl *) {
  new TNNVPageControl(NULL);
}

// ---------------------------------------------------------------------------
__fastcall TNNVPageControl::TNNVPageControl(TComponent* Owner)
    : TPageControl(Owner) {
}

// ---------------------------------------------------------------------------
namespace Vcl_nnpagecontrol {
  void __fastcall PACKAGE Register() {
    TComponentClass classes[1] = {__classid(TNNVPageControl)};
    RegisterComponents(L"VCL New Navadvipa", classes, 0);
  }
}
// ---------------------------------------------------------------------------

void __fastcall TNNVPageControl::LoadFromFiler(TNNVTextStream *Filer) {
  ActivePage = Pages[Filer->ReadInt()];
}

void __fastcall TNNVPageControl::SaveToFiler(TNNVTextStream *Filer) {
  Filer->WriteInt(ActivePage->PageIndex);
}
