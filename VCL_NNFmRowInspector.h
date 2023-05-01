//---------------------------------------------------------------------------

#ifndef VCL_NNFmRowInspectorH
#define VCL_NNFmRowInspectorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VCL_NNActionList.h"
#include "VCL_NNDBMiracle.h"
#include "VCL_NNFlagBox.h"
#include "VCL_NNFmRes.h"
#include "VCL_NNRightsManager.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "VCL_NNPanel.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.DBCtrls.hpp>
#include "VCL_NNLanguageManager.h"
//---------------------------------------------------------------------------
class TfmvRowInspector : public TfmvRes
{
__published:	// IDE-managed Components
  TScrollBox *sbSkip;
  TNNVPanel *paB;
  TButton *buOK;
  TButton *buClear;
  TDBNavigator *dnRowInspector;
  void __fastcall buOKClick(TObject *Sender);
  void __fastcall buClearClick(TObject *Sender);
  void __fastcall SimpleKeyDownDialog( TObject *Sender, WORD &Key, TShiftState Shift );
private:	// User declarations
  using inherited = TfmvRes;
  TNNVQuery* __fastcall GetQuery();
public:		// User declarations
  __fastcall TfmvRowInspector(TComponent* Owner);
  __property TNNVQuery* Query = { read = GetQuery };
};
//---------------------------------------------------------------------------
extern PACKAGE TfmvRowInspector *fmvRowInspector;
//---------------------------------------------------------------------------
#endif

