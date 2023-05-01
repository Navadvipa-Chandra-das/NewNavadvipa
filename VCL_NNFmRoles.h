//---------------------------------------------------------------------------

#ifndef VCL_NNFmRolesH
#define VCL_NNFmRolesH
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
class TfmvRoles : public TfmvDB
{
__published:	// IDE-managed Components
  TNNVDBTreeView *tvRoles;
  TNNVSplitter *splRoles;
  TNNVNodeAdmin *naRoleKind;
  TNNVDBGrid *dgRoles;
  void __fastcall coResLoad( TObject *Sender );
  void __fastcall coResSave( TObject *Sender );
  void __fastcall coResEndLoad( TObject *Sender );
  void __fastcall FormCreate( TObject *Sender );
  void __fastcall FormDestroy( TObject *Sender );
  void __fastcall dgRolesDBCut( TObject *Sender );
  void __fastcall dgRolesDBPaste( TObject *Sender );
  void __fastcall dgRolesDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
  void __fastcall naRoleKindFirstEnter( TObject *Sender );
  void __fastcall naRoleKindLastExit( TObject *Sender );
  void __fastcall naRoleKindEnter( TObject *Sender );
  void __fastcall naRoleKindGetNodeParams( TObject *Sender, TNNVNodeParams &NodeParams );
  void __fastcall naRoleKindLoadNodes( TObject *Sender );

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
  __fastcall TfmvRoles( TComponent* Owner );
  void __fastcall FindID( long long int ARoleID );
};
//---------------------------------------------------------------------------
extern PACKAGE TfmvRoles *fmvRoles;
//---------------------------------------------------------------------------
#endif
