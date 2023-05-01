// ---------------------------------------------------------------------------
#ifndef FMX_NNActionListH
#define FMX_NNActionListH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <FMX.Controls.hpp>
#include <System.Classes.hpp>
#include <FMX.Forms.hpp>
#include <FMX.ActnList.hpp>
#include "FMX_NNCommon.h"

// ---------------------------------------------------------------------------
class PACKAGE TNNFActionList : public TActionList {
private:
protected:
public:
  __fastcall TNNFActionList( TComponent* Owner );
  void __fastcall ShowPropertyDialog();
  void __fastcall SaveToFiler( TNNFTextStream *Filer );
  void __fastcall LoadFromFiler( TNNFTextStream *Filer );
__published:
};
// ---------------------------------------------------------------------------
#endif
