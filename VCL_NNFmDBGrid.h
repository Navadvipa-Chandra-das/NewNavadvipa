// ---------------------------------------------------------------------------

#ifndef VCL_NNFmDBGridH
#define VCL_NNFmDBGridH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VCL_NNDBMiracle.h"
#include "VCL_NNFlagBox.h"
#include "VCL_NNFmRes.h"
#include "VCL_NNRightsManager.h"
#include "VCL_NNPanel.h"
#include <Vcl.CheckLst.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "VCL_NNActionList.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "VCL_NNLanguageManager.h"

// ---------------------------------------------------------------------------
class TfmvDBGrid : public TfmvRes {
__published: // IDE-managed Components
  TNNVPanel *paProperty;
  TEdit *edTitleCaption;
  TFontDialog *fdGrid;
  TCheckBox *cbConfirmDelete;
  TCheckBox *cbTitle;
  TCheckListBox *clGrid;
  TCheckBox *cbRowLines;
  TCheckBox *cbColLines;
  TCheckBox *cbIsFilteredColumn;
  TNNVPanel *paPropertyT;
  TRadioGroup *rgFontOwner;
  TNNVPanel *paFontColor;
  TNNVPanel *paColorFontT;
  TNNVPanel *paFont;
  TNNVPanel *paColor;
  TNNVPanel *paColorFont;
  TButton *buFont;
  TButton *buColor;
  TButton *buFontColor;
  TCheckBox *cbTabs;

  void __fastcall clGridClickCheck(TObject *Sender);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall clGridClick(TObject *Sender);
  void __fastcall edTitleCaptionChange(TObject *Sender);
  void __fastcall paFontDblClick(TObject *Sender);
  void __fastcall paColorDblClick(TObject *Sender);
  void __fastcall cbGridOption(TObject *Sender);
  void __fastcall buFontColorClick(TObject *Sender);
  void __fastcall cbIsFilteredColumnClick(TObject *Sender);

private: // User declarations
  using inherited = TfmvRes;
  TNNVDBGrid *fGrid;
  TColorDialog *fdColor;

  void __fastcall PrepareOptions(TNNVDBGrid *Grid);

public: // User declarations
  __fastcall TfmvDBGrid(TComponent* Owner);
  void __fastcall Execute(TNNVDBGrid *Grid);
  __property TNNVDBGrid *Grid = {read = fGrid};
};

// ---------------------------------------------------------------------------
extern PACKAGE TfmvDBGrid *fmvDBGrid;
// ---------------------------------------------------------------------------
#endif
