//---------------------------------------------------------------------------

#ifndef FMX_NNFmLanguageH
#define FMX_NNFmLanguageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "FMX_NNDBMiracle.h"
#include "FMX_NNFlagBox.h"
#include "FMX_NNFmDB.h"
#include "FMX_NNLanguageManager.h"
#include "FMX_NNRightsManager.h"
#include <Data.Bind.Controls.hpp>
#include <Data.DB.hpp>
#include <Fmx.Bind.Navigator.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.ScrollBox.hpp>
#include <System.Rtti.hpp>
#include "FMX_NNActionList.h"
#include <FMX.ActnList.hpp>
#include <System.Actions.hpp>
#include <FMX.ListBox.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <Data.Bind.Grid.hpp>
#include <Fmx.Bind.DBEngExt.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <Fmx.Bind.Grid.hpp>
#include <System.Bindings.Outputs.hpp>
//---------------------------------------------------------------------------
class TfmfLanguage : public TfmfDB
{
__published:	// IDE-managed Components
  TPanel *paL;
  TGrid *grLanguageKind;
  TSplitter *splLanguageKind;
  TPanel *paC;
  TPanel *paCB;
  TSplitter *splTranslate;
  TPanel *Panel1;
  TGrid *grTranslate;
  TGrid *grLanguage;
  TGrid *grLanguages;
  TSplitter *splLanguages;
  TAction *aPrepareOwnerWords;
  TComboBox *cbLanguageOwner;
  TSpeedButton *SpeedButton1;
  TBindSourceDB *BindSourceDB1;
  TLinkGridToDataSource *LinkGridToDataSourceBindSourceDB1;
  TBindingsList *BindingsList1;
  TColumn *clLanguagesLanguagesID;
  TColumn *clLanguagesLanguagesStringID;
  TColumn *clLanguagesLanguages;
  void __fastcall coResLoad(TObject *Sender);
  void __fastcall coResSave(TObject *Sender);
  void __fastcall coResEndLoad(TObject *Sender);
  void __fastcall aPrepareOwnerWordsExecute(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
  using inherited = TfmfDB;
  TComponent *FLanguageOwner = nullptr;
  void __fastcall SetLanguageOwner( TComponent *Value );
  void __fastcall PrepareLanguageOwner();
public:		// User declarations
  __fastcall TfmfLanguage(TComponent* Owner);
  __property TComponent *LanguageOwner = { read = FLanguageOwner, write = SetLanguageOwner };
};
//---------------------------------------------------------------------------
extern PACKAGE TfmfLanguage *fmfLanguage;
//---------------------------------------------------------------------------
#endif
