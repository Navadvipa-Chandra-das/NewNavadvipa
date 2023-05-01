// ---------------------------------------------------------------------------

#ifndef VCL_NNDrawGridH
#define VCL_NNDrawGridH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <Vcl.Controls.hpp>
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>

// ---------------------------------------------------------------------------
class PACKAGE TNNVDrawGrid : public TDrawGrid {
private:
  using inherited = TDrawGrid;
  TNotifyEvent fOnCWColWidthsChanged;
  TNotifyEvent fOnCWRowHeightsChanged;

protected:
  DYNAMIC void __fastcall ColWidthsChanged();
  DYNAMIC void __fastcall RowHeightsChanged();

  virtual void __fastcall DoCWColWidthsChanged()
  {
    if (fOnCWColWidthsChanged)
      fOnCWColWidthsChanged(this);
  };

  virtual void __fastcall DoCWRowHeightsChanged()
  {
    if ( fOnCWRowHeightsChanged )
      fOnCWRowHeightsChanged(this);
  };

public:
  __fastcall TNNVDrawGrid(TComponent* Owner);
  int __fastcall GetOptimalDefaultRowHeight();

  void __fastcall OptimalDefaultRowHeight() { DefaultRowHeight = GetOptimalDefaultRowHeight(); };

__published:
  __property OnResize;
  __property TNotifyEvent OnCWColWidthsChanged = { read = fOnCWColWidthsChanged, write = fOnCWColWidthsChanged };
  __property TNotifyEvent OnCWRowHeightsChanged = { read = fOnCWRowHeightsChanged, write = fOnCWRowHeightsChanged };
};
// ---------------------------------------------------------------------------
#endif
