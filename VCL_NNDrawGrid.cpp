// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNDrawGrid.h"

#pragma resource "*.res"
#pragma package(smart_init)
// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNNVDrawGrid *) {
  new TNNVDrawGrid(NULL);
}

// ---------------------------------------------------------------------------
__fastcall TNNVDrawGrid::TNNVDrawGrid(TComponent* Owner) : inherited(Owner) {
}

// ---------------------------------------------------------------------------
namespace Vcl_nndrawgrid {
  void __fastcall PACKAGE Register() {
    TComponentClass classes[1] = {__classid(TNNVDrawGrid)};
    RegisterComponents(L"VCL New Navadvipa", classes, 0);
  }
}
// ---------------------------------------------------------------------------

int __fastcall TNNVDrawGrid::GetOptimalDefaultRowHeight() {
  int N = Canvas->TextHeight("Wg") + 3;
  if (Options.Contains(goHorzLine))
    N += GridLineWidth;
  return N;
}

void __fastcall TNNVDrawGrid::ColWidthsChanged() {
  inherited::ColWidthsChanged();
  DoCWColWidthsChanged();
}

void __fastcall TNNVDrawGrid::RowHeightsChanged() {
  inherited::RowHeightsChanged();
  DoCWRowHeightsChanged();
}
