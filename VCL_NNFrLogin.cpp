// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFrLogin.h"
#include "VCL_NNCommon.h"
#include "VCL_NNConst.h"
#include "VCL_NNDmNewNavadvipa.h"
#include "VCL_NNDBMiracle.h"
#include <memory>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrvLogin *frvLogin;

// ---------------------------------------------------------------------------
__fastcall TfrvLogin::TfrvLogin(TComponent* Owner)
  : inherited( Owner )
  , fReadSuccess( false )
  , fConnection( nullptr )
{
}
// ---------------------------------------------------------------------------

void __fastcall TfrvLogin::LabelClick( TObject *Sender )
{
  TLabel *l = dynamic_cast< TLabel* >( Sender );
  if ( l->FocusControl && l->FocusControl->CanFocus() )
    l->FocusControl->SetFocus();
}
// ---------------------------------------------------------------------------

void __fastcall TfrvLogin::LoadFromFiler( TNNVTextStream *Filer )
{
  cbUser->Text        = Filer->ReadString();
  cbUser->Items->Text = Filer->ReadString();
  edDatabase->Text    = Filer->ReadString();
  edServer->Text      = Filer->ReadString();
  edPort->Text        = Filer->ReadString();
  edSchema->Text      = Filer->ReadString();

  fReadSuccess = true;
}

void __fastcall TfrvLogin::SaveToFiler( TNNVTextStream *Filer )
{
  Filer->WriteString( cbUser->Text) ;
  Filer->WriteString( cbUser->Items->Text );
  Filer->WriteString( edDatabase->Text );
  Filer->WriteString( edServer->Text );
  Filer->WriteString( edPort->Text );
  Filer->WriteString( edSchema->Text );
}

void __fastcall TfrvLogin::ConnectionToControls()
{
  cbUser->Text = Connection->Params->UserName;
  edDatabase->Text = Connection->Params->Database;
  edServer->Text = Connection->Params->Values[ "Server" ];

  String aPort = Connection->Params->Values[ "Port" ];
  if ( !aPort.IsEmpty() )
    edPort->Text = aPort;

  edSchema->Text = Connection->Params->Values[ "PrabhupadaSchema" ];
}

bool __fastcall TfrvLogin::Login()
{
  Connection->Params->UserName                     = this->cbUser->Text;
  Connection->Params->Password                     = this->edPassword->Text;
  Connection->Params->Database                     = edDatabase->Text;
  Connection->Params->Values[ "Server" ]           = edServer->Text;
  Connection->Params->Values[ "Port" ]             = edPort->Text;
  Connection->Params->Values[ "PrabhupadaSchema" ] = edSchema->Text;

  if ( Connection->Connected ) {
    Connection->Connected = false;
    Connection->Connected = true;
  } else
    Connection->Connected = true;

  if ( Connection->Connected ) {
    NNV::SaveComboBox( cbUser, NNVConst::MaxStoryComboBox );

    if ( chbResetConfig->Checked ) {
      std::unique_ptr< TNNVQuery > qu( new TNNVQuery( this ) );
      qu->Connection = Connection;
      dmvNewNavadvipa->ResetConfig( Connection->Params->UserName, qu.get() );
    }
  }

  return Connection->Connected;
}

void __fastcall TfrvLogin::FormKeyDown( TObject *Sender, WORD &Key, TShiftState Shift )
{
  TForm *f = dynamic_cast< TForm* >( Owner );

  if ( f == nullptr )
    return;

  switch ( Key ) {
  case vkReturn:
    if ( Login() ) {
      f->ModalResult = mrOk;
      Key = 0;
    }
    break;
  case vkEscape:
    f->ModalResult = mrCancel;
    Key = 0;
    break;
  }
}

void __fastcall TfrvLogin::SetConnection( TFDConnection *AConnection )
{
  if ( fConnection != AConnection ) {

    fConnection = AConnection;

    if ( !ReadSuccess )
      ConnectionToControls();
  }
}

