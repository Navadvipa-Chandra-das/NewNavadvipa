//---------------------------------------------------------------------------

#ifndef VCL_NNFmLockH
#define VCL_NNFmLockH
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
class TfmvLock : public TfmvRes
{
__published:	// IDE-managed Components
  TLabel *laUser;
  TEdit *edUser;
  TEdit *edPassword;
  TLabel *laPassword;
  TButton *buUnLock;
  TAction *aPrepareLock;
  TAction *aPrepareUnLock;
  void __fastcall FormCreate( TObject *Sender );
  void __fastcall buUnLockClick( TObject *Sender );
  void __fastcall FormCloseQuery( TObject *Sender, bool &CanClose );
private:	// User declarations
  using inherited = TfmvRes;
  NNV::TControlMap FFormList;
  bool FCanClose = false;
  TForm *LastActivForm = nullptr;
public:		// User declarations
  __fastcall TfmvLock( TComponent* Owner );
  void __fastcall FormShow();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmvLock *fmvLock;
//---------------------------------------------------------------------------
#endif
