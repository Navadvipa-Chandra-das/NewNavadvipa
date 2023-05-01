// ---------------------------------------------------------------------------

#ifndef VCL_NNFmResH
#define VCL_NNFmResH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VCL_NNFlagBox.h"
#include "VCL_NNRightsManager.h"
#include "VCL_NNDisp.h"
#include "VCL_NNDBMiracle.h"
#include "VCL_NNActionList.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "VCL_NNCommon.h"
#include "VCL_NNLanguageManager.h"

// ---------------------------------------------------------------------------
class TfmvRes : public TForm {
__published: // IDE-managed Components
  TNNVFlagBox *fbRes;
  TNNVConfig *coRes;
  TNNVRight *rrRes;
  TNNVActionList *alRes;
  TAction *aActionListSetup;
  TAction *aRelease;
  TAction *aClearCase;
  TNNVLanguage *lnRes;
  TAction *aPrepareLanguage;

  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall FormDeactivate(TObject *Sender);
  void __fastcall coResLoad(TObject *Sender);
  void __fastcall coResSave(TObject *Sender);
  void __fastcall LabelClick(TObject *Sender);
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall SimpleKeyDownDialog( TObject *Sender, WORD &Key, TShiftState Shift );
  void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y);
  void __fastcall aActionListSetupExecute(TObject *Sender);
  void __fastcall aReleaseExecute(TObject *Sender);
  void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
  void __fastcall aClearCaseExecute(TObject *Sender);
  void __fastcall coResGetFiler( TObject *Sender, TNNVTextStream *&Filer );
  void __fastcall aPrepareLanguageExecute( TObject *Sender );
private: // User declarations
  using inherited = TForm;
  bool fDialogCloseOnDeactivate = false;
  bool fIsDestroy = false;
  TWinControl *FLastActive = nullptr;
  bool fHelpCapture;
  Controls::TCursor fOldCursor;
  bool fDialogMode;
  TWindowPlacement *FWindowPlace;
  NNV::TEnterKind FEnterKind = NNV::TEnterKind::Enter;
  bool FCanUserClose = true;
  bool  FIsQuickSearch = false;
  bool  FIsClearCase = false;

  void __fastcall SetDialogMode( bool Value );
  void __fastcall SetEnterKind( NNV::TEnterKind Value );
  inline void ClearWindowPlacement()
  {
    delete FWindowPlace;
    FWindowPlace = NULL;
  };
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
  virtual bool __fastcall SetFocusedControl( Controls::TWinControl* Control );
  virtual void __fastcall Notification( TComponent *AComponent
                                      , TOperation Operation );
  virtual void __fastcall Loaded();
  virtual void __fastcall RegisterForHistory();
  virtual void __fastcall StartHelp();
  virtual void __fastcall ToolButtonPrepare();
  void __fastcall ExecuteHelp();
  void __fastcall FixWhileEmbarcaderoBug();
public: // User declarations
  __fastcall TfmvRes( TComponent* Owner );
  NNV::TMultiResult MultiResult;
  virtual void __fastcall CorrectWindowPlace();
  void __fastcall ShowDialog( TComponent *SenderForm );
  void __fastcall CloseDialog( bool IsExecute );
  void __fastcall FillMultiResult( TNNVDBGrid *dg
                                 , TField *FieldNo
                                 , TField *FieldNote );
  void __fastcall MultiResultExecute( TNNVQuery *DSet
                                    , TField *FieldNo
                                    , TField *FieldNote
                                    , bool IsDublicate = false );
  __property bool DialogMode = { read = fDialogMode, write = SetDialogMode };
  __property bool DialogCloseOnDeactivate = { read = fDialogCloseOnDeactivate, write = fDialogCloseOnDeactivate };
  __property bool IsDestroy = { read = fIsDestroy };
  __property Variant ResultKind = { read = fResultKind };
  __property Variant ResultNo = { read = fResultNo };
  __property Variant ResultNote = { read = fResultNote };
  __property TDataSet *ResultDataSet = { read = fResultDataSet, write = fResultDataSet };
  __property bool IsMultiResult = { read = fIsMultiResult };
  __property TWinControl *LastActive = { read = FLastActive };
  __property NNV::TEnterKind EnterKind = { read = FEnterKind, write = SetEnterKind };
  __property bool CanUserClose = { read = FCanUserClose, write = FCanUserClose };
  __property bool  IsQuickSearch = { read = FIsQuickSearch, write = FIsQuickSearch };
  __property bool IsClearCase = { read = FIsClearCase };
};

// ---------------------------------------------------------------------------
extern PACKAGE TfmvRes *fmvRes;
// ---------------------------------------------------------------------------
#endif
