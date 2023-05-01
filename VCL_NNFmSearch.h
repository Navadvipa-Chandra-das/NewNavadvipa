// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef VCL_NNFmSearchH
#define VCL_NNFmSearchH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "VCL_NNSearchOption.h"
#include "VCL_NNActionList.h"
#include "VCL_NNDBMiracle.h"
#include "VCL_NNFlagBox.h"
#include "VCL_NNFmRes.h"
#include "VCL_NNRightsManager.h"
#include "VCL_NNCommon.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ComCtrls.hpp>
#include "VCL_NNLanguageManager.h"
// ---------------------------------------------------------------------------

class PACKAGE TfmvSearch : public TfmvRes {
__published: // IDE-managed Components
  TPanel *paBottom;
  TRadioGroup *rgDirection;
  TRadioGroup *rgStartPoint;
  TRadioGroup *rgOperation;
  TButton *buOK;
  TButton *buCancel;
  TButton *buClear;
  TRadioGroup *rgFilterSearch;
  TGroupBox *gbChechSettings;
  TCheckBox *ckCaseSensitive;
  TCheckBox *ckIsSoft;
  TCheckBox *ckIsMistake;
  TCheckBox *ckAnyEntry;
  TCheckBox *ckNotThis;
  TCheckBox *ckRegularExpression;
  TPageControl *pcSearch;
  TTabSheet *tsSearch;
  TTabSheet *tsHelpLetter;
  TScrollBox *sbSkip;
  TMemo *meHelpLetter;
  void __fastcall rgDirectionClick( TObject *Sender );
  void __fastcall buClearClick( TObject *Sender );
  void __fastcall ckIsSoftClick( TObject *Sender );
  void __fastcall ckRegularExpressionClick( TObject *Sender );
  void __fastcall buOKClick( TObject *Sender );
  void __fastcall buCancelClick( TObject *Sender );
  void __fastcall rgFilterSearchClick( TObject *Sender );
  void __fastcall FormCreate( TObject *Sender );
private: // User declarations
  using inherited = TfmvRes;
  bool FUseTag = true;
  NNV::TMapSearch *FMapSearch;
  String FActiveControlName;
  NNV::TSearchDlgOptions __fastcall GetSearchDlgOptions();
  void __fastcall SetSearchDlgOptions( const NNV::TSearchDlgOptions &Value );
protected:

public: // User declarations
  __fastcall TfmvSearch( TComponent* Owner );
  __fastcall TfmvSearch( TComponent* Owner, bool tag );
  __property NNV::TSearchDlgOptions SearchDlgOptions = { read = GetSearchDlgOptions, write = SetSearchDlgOptions };
  __property NNV::TMapSearch *MapSearch = { read = FMapSearch };
  __property String ActiveControlName = { read = FActiveControlName };
};

// ---------------------------------------------------------------------------
extern PACKAGE TfmvSearch *fmvSearch;
// ---------------------------------------------------------------------------
#endif
