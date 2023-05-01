// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef VCL_NNPageControlH
#define VCL_NNPageControlH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <Vcl.Controls.hpp>
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include "VCL_NNCommon.h"

// ---------------------------------------------------------------------------
class PACKAGE TNNVPageControl : public TPageControl {
private:
protected:
public:
  __fastcall TNNVPageControl(TComponent* Owner);
  void __fastcall SaveToFiler(TNNVTextStream *Filer);
  void __fastcall LoadFromFiler(TNNVTextStream *Filer);

__published:
};
// ---------------------------------------------------------------------------
#endif
