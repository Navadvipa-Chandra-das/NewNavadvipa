//---------------------------------------------------------------------------

#ifndef VCL_NNFmRightsH
#define VCL_NNFmRightsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VCL_NNActionList.h"
#include "VCL_NNDBMiracle.h"
#include "VCL_NNDateTimeDialog.h"
#include "VCL_NNDialogExec.h"
#include "VCL_NNFlagBox.h"
#include "VCL_NNFmDB.h"
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
#include "VCL_NNSplitter.h"
#include "VCL_NNDBMiracle.h"
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include "VCL_NNLanguageManager.h"
//---------------------------------------------------------------------------
class TfmvRights : public TfmvDB
{
__published:	// IDE-managed Components
  TNNVDBTreeView *tvRights;
  TNNVSplitter *splRights;
  TNNVNodeAdmin *naRightsKind;
  TNNVDBGrid *dgRights;
  void __fastcall naRightsKindFirstEnter( TObject *Sender );
  void __fastcall naRightsKindLastExit( TObject *Sender );
  void __fastcall naRightsKindEnter( TObject *Sender );
  void __fastcall naRightsKindGetNodeParams( TObject *Sender, TNNVNodeParams &NodeParams );
  void __fastcall naRightsKindLoadNodes( TObject *Sender );
  void __fastcall coResLoad( TObject *Sender );
  void __fastcall coResSave( TObject *Sender );
  void __fastcall dgRightsDBCut( TObject *Sender );
  void __fastcall dgRightsDBPaste( TObject *Sender );
  void __fastcall dgRightsDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
  void __fastcall coResEndLoad( TObject *Sender );
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
  using inherited = TfmvDB;
  void __fastcall LoadNodeAdmins();
  void __fastcall LoadTrees();
  void __fastcall LoadGrids();
  void __fastcall SaveNodeAdmins();
  void __fastcall SaveTrees();
  void __fastcall SaveGrids();
protected:
  virtual void __fastcall CloseValid();
public:		// User declarations
  __fastcall TfmvRights( TComponent* Owner );
  void __fastcall FindID( long long int ARightID );
};
//---------------------------------------------------------------------------
extern PACKAGE TfmvRights *fmvRights;
//---------------------------------------------------------------------------
#endif
