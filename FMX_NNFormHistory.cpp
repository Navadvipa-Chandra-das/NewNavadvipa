// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "FMX_NNFormHistory.h"
#include "FMX_NNConst.h"

// ---------------------------------------------------------------------------

#pragma package(smart_init)

namespace NNF {

TFormHistory FormHistory( NNFConst::MaxFormHistory, FormShow );
TFormCycle FormCycle( FormShow );

}
