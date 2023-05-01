//---------------------------------------------------------------------------

#ifndef VCL_NNFmLanguageH
#define VCL_NNFmLanguageH
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
#include "VCL_NNDialog.h"
//---------------------------------------------------------------------------
class TfmvLanguage : public TfmvDB
{
__published:	// IDE-managed Components
  TNNVDBTreeView *tvLanguage;
  TNNVSplitter *splLanguage;
  TNNVNodeAdmin *naLanguageKind;
  TNNVPanel *paLanguage;
  TNNVDBGrid *dgLanguage;
  TNNVPanel *paLanguageB;
  TNNVPanel *paLanguageBB;
  TNNVDBGrid *dgTranslate;
  TNNVSplitter *splLanguageBB;
  TNNVSplitter *splLanguageB;
  TDBMemo *dmeSlovo;
  TDBMemo *dmePerevod;
  TNNVSplitter *splSlovo;
  TAction *aPrepareOwnerWords;
  TComboBox *cbLanguageOwner;
  TToolButton *tbPrepareOwnerWords;
  TAction *aSelectNonLatinica;
  TToolButton *tbSelectNonLatinica;
  TMenuItem *miPrepareOwnerWords;
  TMenuItem *miSelectNonLatinica;
  TNNVDialog *DLanguages;
  void __fastcall coResLoad( TObject *Sender );
  void __fastcall coResSave( TObject *Sender );
  void __fastcall coResEndLoad( TObject *Sender );
  void __fastcall FormCreate( TObject *Sender );
  void __fastcall FormDestroy( TObject *Sender );
  void __fastcall dgLanguageDBCut( TObject *Sender );
  void __fastcall dgLanguageDBPaste( TObject *Sender );
  void __fastcall dgLanguageDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
  void __fastcall naLanguageKindFirstEnter( TObject *Sender );
  void __fastcall naLanguageKindLastExit( TObject *Sender );
  void __fastcall naLanguageKindEnter( TObject *Sender );
  void __fastcall naLanguageKindGetNodeParams( TObject *Sender, TNNVNodeParams &NodeParams );
  void __fastcall naLanguageKindLoadNodes( TObject *Sender );
  void __fastcall dgTranslateDBCut( TObject *Sender );
  void __fastcall dgTranslateDBCopy( TObject *Sender );
  void __fastcall dgTranslateDBPaste( TObject *Sender );
  void __fastcall aPrepareOwnerWordsExecute( TObject *Sender );
  void __fastcall cbLanguageOwnerChange( TObject *Sender );
  void __fastcall aSelectNonLatinicaExecute( TObject *Sender );
  void __fastcall DLanguagesGetDialogForm( TObject *Sender, TCustomForm *&fm );
  void __fastcall DLanguagesPrepare( TObject *Sender );
  void __fastcall DLanguagesExecute( TObject *Sender );
private:	// User declarations
  using inherited = TfmvDB;
  TComponent *FLanguageOwner = nullptr;
  void __fastcall SetLanguageOwner( TComponent *Value );
  void __fastcall LoadNodeAdmins();
  void __fastcall LoadTrees();
  void __fastcall LoadGrids();
  void __fastcall SaveNodeAdmins();
  void __fastcall SaveTrees();
  void __fastcall SaveGrids();
  void __fastcall PrepareLanguageOwner();
  bool __fastcall IsNonLatinica();
  void __fastcall SetOnGetDialogFormsBecauseBug();
protected:
  virtual void __fastcall CloseValid();
public:		// User declarations
  __fastcall TfmvLanguage( TComponent* Owner );
  void __fastcall FindID( long long int ALanguageID );
  __property TComponent *LanguageOwner = { read = FLanguageOwner, write = SetLanguageOwner };
};
//---------------------------------------------------------------------------
extern PACKAGE TfmvLanguage *fmvLanguage;
//---------------------------------------------------------------------------
#endif
