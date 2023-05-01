//---------------------------------------------------------------------------

#ifndef VCL_NNFmLanguagesH
#define VCL_NNFmLanguagesH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VCL_NNActionList.h"
#include "VCL_NNDateTimeDialog.h"
#include "VCL_NNDBMiracle.h"
#include "VCL_NNDialogExec.h"
#include "VCL_NNFlagBox.h"
#include "VCL_NNFmDB.h"
#include "VCL_NNLanguageManager.h"
#include "VCL_NNPageControl.h"
#include "VCL_NNPanel.h"
#include "VCL_NNRightsManager.h"
#include <Data.DB.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TfmvLanguages : public TfmvDB
{
__published:	// IDE-managed Components
  TNNVDBGrid *dgLanguages;
  void __fastcall coResLoad( TObject *Sender );
  void __fastcall coResSave( TObject *Sender );
  void __fastcall FormCreate( TObject *Sender );
  void __fastcall FormDestroy( TObject *Sender );
private:	// User declarations
  using inherited = TfmvDB;
protected:
  virtual void __fastcall CloseValid();
public:		// User declarations
  __fastcall TfmvLanguages( TComponent* Owner );
  void __fastcall FindID( long long int ALanguagesID );
};
//---------------------------------------------------------------------------
extern PACKAGE TfmvLanguages *fmvLanguages;
//---------------------------------------------------------------------------
#endif
