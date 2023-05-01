//---------------------------------------------------------------------------

#ifndef VCL_NNFmChangePasswordH
#define VCL_NNFmChangePasswordH
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
class TfmvChangePassword : public TfmvRes
{
__published:	// IDE-managed Components
  TEdit *edUser;
  TLabel *laUser;
  TEdit *edOldPassword;
  TLabel *laOldPassword;
  TEdit *edNewPassword;
  TLabel *laNewPassword;
  TLabel *laConfirmNewPassword;
  TEdit *edConfirmNewPassword;
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
  using inherited = TfmvRes;
  bool IsMyUserName;
public:		// User declarations
  __fastcall TfmvChangePassword( TComponent* Owner );
  void __fastcall ShowChangePassword( const String &AUser
                                    , TComponent *ASenderForm );
  bool __fastcall ChangePassword();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmvChangePassword *fmvChangePassword;
//---------------------------------------------------------------------------
#endif
