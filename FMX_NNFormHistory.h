// ---------------------------------------------------------------------------

#ifndef FMX_NNFormHistoryH
#define FMX_NNFormHistoryH
// ---------------------------------------------------------------------------

#include "NNNavHistory.h"
#include "NNNavCycle.h"
#include "FMX_NNCommon.h"

namespace NNF {

using TFormActiveProc = PACKAGE void __fastcall ( * )( TCommonCustomForm* );

using TFormHistory = PACKAGE NN::TNavHistory< TCommonCustomForm*, TFormActiveProc >;
using TFormCycle   = PACKAGE NN::TNavCycle< TCommonCustomForm*, TFormActiveProc > ;

extern PACKAGE TFormHistory FormHistory;
extern PACKAGE TFormCycle FormCycle;

}

#endif
