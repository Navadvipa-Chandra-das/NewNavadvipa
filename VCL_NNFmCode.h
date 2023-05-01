//---------------------------------------------------------------------------

#ifndef VCL_NNFmCodeH
#define VCL_NNFmCodeH
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
#include "VCL_NNLanguageManager.h"
//---------------------------------------------------------------------------
class TfmvCode : public TfmvRes
{
__published:	// IDE-managed Components
  TMemo *meCode;
  void __fastcall FormKeyDown( TObject *Sender, WORD &Key, TShiftState Shift );
private:	// User declarations
  using inherited = TfmvRes;
public:		// User declarations
  __fastcall TfmvCode( TComponent* Owner );
};
//---------------------------------------------------------------------------
extern PACKAGE TfmvCode *fmvCode;
//---------------------------------------------------------------------------
#endif
