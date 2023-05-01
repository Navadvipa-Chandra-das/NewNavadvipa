// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef VCL_NNPanelH
#define VCL_NNPanelH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

// ---------------------------------------------------------------------------
class PACKAGE TNNVPanel : public TPanel {
private:
  using inherited = TPanel;

protected:
public:
  __fastcall TNNVPanel(TComponent* Owner);

__published:
  __property BevelInner = { default = bvNone};
  __property BevelOuter = { default = bvNone};
};
// ---------------------------------------------------------------------------
#endif
