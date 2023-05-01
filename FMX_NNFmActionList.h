//---------------------------------------------------------------------------

#ifndef FMX_NNFmActionListH
#define FMX_NNFmActionListH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "FMX_NNDBMiracle.h"
#include "FMX_NNFlagBox.h"
#include "FMX_NNFmRes.h"
#include "FMX_NNLanguageManager.h"
#include "FMX_NNRightsManager.h"
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.ScrollBox.hpp>
#include <System.Rtti.hpp>
#include "FMX_NNActionList.h"
#include <FMX.ActnList.hpp>
#include <System.Actions.hpp>
#include <vector>

namespace NNF {

using TActionVector = std::vector< TContainedAction* >;

}

//---------------------------------------------------------------------------
class TfmfActionList : public TfmfRes
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TButton *buSet;
  TEdit *edAction;
  TGrid *grAction;
  TColumn *clImage;
  TColumn *alShortCut;
  TColumn *clAction;
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
  void __fastcall buSetClick(TObject *Sender);
private:	// User declarations
  using inherited = TfmfRes;
  TBaseImageList *FActionImage = nullptr;
  NNF::TActionVector ActionVector;
  void __fastcall GetColor( TContainedAction *a
                          , TAlphaColor &FontColor
                          , TAlphaColor &FonColor );
public:		// User declarations
  __fastcall TfmfActionList(TComponent* Owner);
  void __fastcall Execute( TActionList *AList );
  __property TCustomImageList *ActionImage = { read = FActionImage };
};
//---------------------------------------------------------------------------
extern PACKAGE TfmfActionList *fmfActionList;
//---------------------------------------------------------------------------
#endif
