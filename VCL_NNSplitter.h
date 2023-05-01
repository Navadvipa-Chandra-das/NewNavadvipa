// ---------------------------------------------------------------------------

#ifndef VCL_NNSplitterH
#define VCL_NNSplitterH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

// ---------------------------------------------------------------------------
class PACKAGE TNNVSplitter : public TSplitter {
private:
  using inherited = TSplitter;

protected:
public:
  __fastcall TNNVSplitter(TComponent* Owner);

__published:
  __property ResizeStyle = { default = rsUpdate};
};
// ---------------------------------------------------------------------------
#endif
