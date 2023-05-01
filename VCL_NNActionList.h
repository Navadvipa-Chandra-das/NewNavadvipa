// ---------------------------------------------------------------------------
#ifndef VCL_NNActionListH
#define VCL_NNActionListH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <Vcl.Controls.hpp>
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ActnList.hpp>
#include "VCL_NNCommon.h"

// ---------------------------------------------------------------------------
class PACKAGE TNNVActionList : public TActionList {
private:
protected:
public:
  __fastcall TNNVActionList( TComponent* Owner );
  void __fastcall ShowPropertyDialog();
  void __fastcall SaveToFiler( TNNVTextStream *Filer );
  void __fastcall LoadFromFiler( TNNVTextStream *Filer );
__published:
};
// ---------------------------------------------------------------------------
#endif
