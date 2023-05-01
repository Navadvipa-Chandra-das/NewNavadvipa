// ---------------------------------------------------------------------------

#ifndef VCL_NNFormHistoryH
#define VCL_NNFormHistoryH
// ---------------------------------------------------------------------------

#include "NNNavHistory.h"
#include "NNNavCycle.h"
#include "VCL_NNCommon.h"

namespace NNV {

  using TFormActiveProc = PACKAGE void __fastcall ( * )( TCustomForm* );
  using TFormHistory = PACKAGE NN::TNavHistory< TCustomForm*, TFormActiveProc >;
  using TFormCycle = PACKAGE NN::TNavCycle< TCustomForm*, TFormActiveProc >;

  extern PACKAGE TFormHistory FormHistory;
  extern PACKAGE TFormCycle FormCycle;

}

#endif
