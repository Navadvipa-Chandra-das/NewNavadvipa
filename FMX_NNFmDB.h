//---------------------------------------------------------------------------

#ifndef FMX_NNFmDBH
#define FMX_NNFmDBH
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
#include <Data.Bind.Controls.hpp>
#include <Fmx.Bind.Navigator.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Edit.hpp>
#include <Data.DB.hpp>
#include "FMX_NNDBMiracle.h"
#include "FMX_NNActionList.h"
#include <FMX.ActnList.hpp>
#include <System.Actions.hpp>
#include <FMX.ListBox.hpp>
//---------------------------------------------------------------------------
class TfmfDB : public TfmfRes
{
__published:	// IDE-managed Components
  TPanel *paT;
  TPanel *paStatus;
  TPanel *paTL;
  TBindNavigator *BindNavigator1;
  TTabControl *tcDB;
  TTabItem *tiDB;
  TEdit *edDBStatus;
  TDataSource *dsData;
  TTabItem *tiSetup;
  TToolBar *ToolBar1;
  void __fastcall dsDataDataChange(TObject *Sender, TField *Field);
private:	// User declarations
  using inherited = TfmfRes;
  TDataSource *FDataSource = nullptr;
  void __fastcall SetDataSource( TDataSource *Value );
  TDataSet* __fastcall GetDataSet() { return dsData->DataSet; };
  void __fastcall SetDataSet( TDataSet *Value );
  TNNFQuery* __fastcall GetQuery();
public:		// User declarations
  __fastcall TfmfDB(TComponent* Owner);
  __property TDataSource *DataSource = { read = FDataSource, write = SetDataSource };
  __property TDataSet *DataSet = { read = GetDataSet, write = SetDataSet };
  __property TNNFQuery* *Query = { read = GetQuery };
};
//---------------------------------------------------------------------------
extern PACKAGE TfmfDB *fmfDB;
//---------------------------------------------------------------------------
#endif
