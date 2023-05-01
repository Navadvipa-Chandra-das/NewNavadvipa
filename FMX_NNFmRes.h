//---------------------------------------------------------------------------

#ifndef FMX_NNFmResH
#define FMX_NNFmResH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Types.hpp>
#include "FMX_NNDBMiracle.h"
#include "FMX_NNFlagBox.h"
#include "FMX_NNCommon.h"
#include "FMX_NNDisp.h"
#include <FMX.ActnList.hpp>
#include <FMX.Grid.hpp>
#include <System.Actions.hpp>
#include "FMX_NNLanguageManager.h"
#include "FMX_NNRightsManager.h"
#include "FMX_NNActionList.h"
//---------------------------------------------------------------------------
class TfmfRes : public TForm
{
__published:	// IDE-managed Components
  TNNFConfig *coRes;
  TNNFFlagBox *fbRes;
  TNNFRight *rrRes;
  TNNFLanguage *lnRes;
  TNNFActionList *alRes;
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall coResLoad(TObject *param_0);
  void __fastcall coResSave(TObject *param_0);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall coResGetFiler( TObject *Sender, TNNFTextStream *&Filer );
private:	// User declarations
  using inherited = TForm;
  bool fDialogCloseOnDeactivate = false;
  bool fIsDestroy = false;
  TControl *FLastActive = nullptr;
  bool fHelpCapture;
  TCursor fOldCursor;
  bool fDialogMode;
  //TWindowPlacement *FWindowPlace;
  NNF::TEnterKind FEnterKind = NNF::TEnterKind::Enter;
  bool FCanUserClose = true;
  bool  FIsQuickSearch = false;
  bool  FIsClearCase = false;
  void __fastcall SetLang( String Value );
  void __fastcall SetDialogMode( bool Value );
  void __fastcall SetEnterKind( NNF::TEnterKind Value );
//  inline void ClearWindowPlacement()
//  {
//    delete FWindowPlace;
//    FWindowPlace = NULL;
//  };
protected:
  Variant fResultKind;
  Variant fResultNo;
  Variant fResultNote;
  TDataSet *fResultDataSet;
  bool fIsMultiResult;
  virtual void __fastcall SyncEnterKind() {};
  DYNAMIC void __fastcall Activate(void);
  virtual void __fastcall SyncDialogInit() {};
  virtual void __fastcall DialogInit();
  virtual void __fastcall CloseValid() {};
  virtual void __fastcall CloseAlways() {};
  //virtual bool __fastcall SetFocusedControl( TControl* Control );
  virtual void __fastcall Notification( TComponent *AComponent
                                      , TOperation Operation );
  virtual void __fastcall Loaded();
  virtual void __fastcall RegisterForHistory();
  //virtual void __fastcall StartHelp();
  virtual void __fastcall ToolButtonPrepare();
  void __fastcall ExecuteHelp();
  void __fastcall FixWhileEmbarcaderoBug();
public:		// User declarations
  __fastcall TfmfRes( TComponent* Owner );
  NNF::TMultiResult MultiResult;
  virtual void __fastcall CorrectWindowPlace();
  void __fastcall ShowDialog( TComponent *SenderForm );
  void __fastcall CloseDialog( bool IsExecute );
  void __fastcall FillMultiResult( TGrid *dg
                                 , TField *FieldNo
                                 , TField *FieldNote );
//  void __fastcall MultiResultExecute( TNNFQuery *DSet
//                                    , TField *FieldNo
//                                    , TField *FieldNote
//                                    , bool IsDublicate = false );
  __property bool DialogMode = { read = fDialogMode, write = SetDialogMode };
  __property bool DialogCloseOnDeactivate = { read = fDialogCloseOnDeactivate, write = fDialogCloseOnDeactivate };
  __property bool IsDestroy = { read = fIsDestroy };
  __property Variant ResultKind = { read = fResultKind };
  __property Variant ResultNo = { read = fResultNo };
  __property Variant ResultNote = { read = fResultNote };
  __property TDataSet *ResultDataSet = { read = fResultDataSet, write = fResultDataSet };
  __property bool IsMultiResult = { read = fIsMultiResult };
  __property TControl *LastActive = { read = FLastActive };
  __property NNF::TEnterKind EnterKind = { read = FEnterKind, write = SetEnterKind };
  __property bool CanUserClose = { read = FCanUserClose, write = FCanUserClose };
  __property bool  IsQuickSearch = { read = FIsQuickSearch, write = FIsQuickSearch };
  __property bool IsClearCase = { read = FIsClearCase };
};
//---------------------------------------------------------------------------
extern PACKAGE TfmfRes *fmfRes;
//---------------------------------------------------------------------------
#endif
