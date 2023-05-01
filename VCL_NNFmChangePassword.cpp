//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFmChangePassword.h"
#include "VCL_NNDmNewNavadvipa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNActionList"
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNFlagBox"
#pragma link "VCL_NNFmRes"
#pragma link "VCL_NNRightsManager"
#pragma link "VCL_NNLanguageManager"
#pragma resource "*.dfm"
TfmvChangePassword *fmvChangePassword;
//---------------------------------------------------------------------------
__fastcall TfmvChangePassword::TfmvChangePassword( TComponent* Owner )
  : inherited( Owner )
  , IsMyUserName( false )
{
}
//---------------------------------------------------------------------------

void __fastcall TfmvChangePassword::ShowChangePassword( const String &AUser
                                                      , TComponent *ASenderForm )
{
  edUser->Text = AUser;
  IsMyUserName = dmvNewNavadvipa->conDB->Params->UserName == AUser;

  edUser->ReadOnly       = IsMyUserName;
  edOldPassword->Enabled = IsMyUserName;

  if ( IsMyUserName )
    ActiveControl = edOldPassword;
  else
    ActiveControl = edNewPassword;


  ShowDialog( ASenderForm );
}

bool __fastcall TfmvChangePassword::ChangePassword()
{
  if ( IsMyUserName ) {
    if ( dmvNewNavadvipa->conDB->Params->Password != NNV::CriptPassword( edOldPassword->Text ) ) {
      ShowMessage( L"Неверен старый пароль!" );
      return false;
    }
  }

  if ( edNewPassword->Text != edConfirmNewPassword->Text ) {
    ShowMessage( L"Пароль не подтверждён!" );
    return false;
  }

  if ( edNewPassword->Text.IsEmpty() ) {
    ShowMessage( L"Пустой пароль не допустим!" );
    return false;
  }

  dmvNewNavadvipa->SetNewUserPassword( edUser->Text, edNewPassword->Text );
  return true;
}

void __fastcall TfmvChangePassword::FormKeyDown( TObject *Sender, WORD &Key, TShiftState Shift )
{
  switch ( Key ) {
  case vkReturn:
    if ( ChangePassword() ) {
      CloseDialog( true );
      Key = 0;
    }
    break;
  case vkEscape:
    CloseDialog( false );
    Key = 0;
    break;
  }

  if ( Key != 0 )
    inherited::FormKeyDown( Sender, Key, Shift );
}
//---------------------------------------------------------------------------


