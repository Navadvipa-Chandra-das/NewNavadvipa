//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFmLock.h"
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
TfmvLock *fmvLock;
//---------------------------------------------------------------------------
__fastcall TfmvLock::TfmvLock( TComponent* Owner )
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

void __fastcall TfmvLock::FormShow()
{
  LastActivForm         = Screen->ActiveForm;

  aPrepareLock->Execute();
  FCanClose = false;

  edUser->Text = dmvNewNavadvipa->UserName;

  Show();

  for ( int i = 0; i < Screen->FormCount; i++ ) {
    if ( Screen->Forms[ i ] != this ) {
      FFormList.insert( std::make_pair( Screen->Forms[ i ], Screen->Forms[ i ]->Visible ) );
      Screen->Forms[ i ]->Hide();
      Screen->Forms[ i ]->Update();
    }
  }
}

void __fastcall TfmvLock::FormCreate( TObject *Sender )
{
  inherited::FormCreate( Sender );
  Caption = Application->Title + String( " - блокировка" );
}
//---------------------------------------------------------------------------

void __fastcall TfmvLock::buUnLockClick( TObject *Sender )
{
  if ( edPassword->Text != dmvNewNavadvipa->PseudoPassword ) {
      Hide();
      ShowMessage( NNVConst::Sorry + String( L"пароль введен не верно!" ) );
      Show();
  } else {
    for ( NNV::TControlMap::iterator i = FFormList.begin(); i != FFormList.end(); i++ )
      (*i).first->Visible = (*i).second;

      aPrepareUnLock->Execute();
      FCanClose = true;

    if ( LastActivForm && LastActivForm->Visible )
      LastActivForm->SetFocus();

    Close();
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmvLock::FormCloseQuery( TObject *Sender, bool &CanClose )
{
  CanClose = FCanClose;
}
//---------------------------------------------------------------------------

