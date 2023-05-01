//---------------------------------------------------------------------------
#ifndef VCL_NNFmActionListH
#define VCL_NNFmActionListH
//---------------------------------------------------------------------------
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <System.Classes.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Mask.hpp>
#include "VCL_NNActionList.h"
#include "VCL_NNDBMiracle.h"
#include "VCL_NNDrawGrid.h"
#include "VCL_NNFlagBox.h"
#include "VCL_NNFmRes.h"
#include "VCL_NNPanel.h"
#include "VCL_NNRightsManager.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include "VCL_NNLanguageManager.h"
#include <vector>
//---------------------------------------------------------------------------
namespace NNV {

using TActionVector = std::vector< TContainedAction* >;

}

class TfmvActionList : public TfmvRes
{
__published:	// IDE-managed Components
  TNNVPanel *paAction;
  THotKey *hkAction;
  TButton *buSet;
  TNNVDrawGrid *dgAction;
  TEdit *edAction;
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
    TShiftState Shift);
  void __fastcall buSetClick(TObject *Sender);
  void __fastcall dgActionDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
  void __fastcall dgActionSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
  using inherited = TfmvRes;
  TCustomImageList *fActionImage;
  NNV::TActionVector ActionVector;
  void __fastcall GetColor( TContainedAction *a
                          , TColor &FontColor
                          , TColor &FonColor );
public:		// User declarations
  __fastcall TfmvActionList(TComponent* Owner);
  void __fastcall Execute( TActionList *AList );
  __property TCustomImageList *ActionImage = { read = fActionImage };
};
//---------------------------------------------------------------------------
extern PACKAGE TfmvActionList *fmvActionList;
//---------------------------------------------------------------------------
#endif
