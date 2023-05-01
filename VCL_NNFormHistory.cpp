// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFormHistory.h"
#include "VCL_NNConst.h"

// ---------------------------------------------------------------------------

#pragma package(smart_init)

namespace NNV {

TFormHistory FormHistory( NNVConst::MaxFormHistory, FormShow );
TFormCycle FormCycle( FormShow );

}
