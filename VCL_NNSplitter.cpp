// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNSplitter.h"
#pragma resource "*.res"
#pragma package(smart_init)
// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNNVSplitter *)
{
  new TNNVSplitter(NULL);
}

// ---------------------------------------------------------------------------
__fastcall TNNVSplitter::TNNVSplitter(TComponent* Owner) : inherited(Owner)
{
  ResizeStyle = rsUpdate;
}

// ---------------------------------------------------------------------------
namespace Vcl_nnsplitter {
  void __fastcall PACKAGE Register()
  {
    TComponentClass classes[1] = {__classid(TNNVSplitter)};
    RegisterComponents(L"VCL New Navadvipa", classes, 0);
  }
}
// ---------------------------------------------------------------------------
