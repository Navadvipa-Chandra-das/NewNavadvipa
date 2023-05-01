//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "FMX_NNFrLogin.h"
#include "FMX_NNConst.h"
#include "FMX_NNDBMiracle.h"
#include <memory>
#include "FMX_NNDmNewNavadvipa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrfLogin *frfLogin;
//---------------------------------------------------------------------------
__fastcall TfrfLogin::TfrfLogin(TComponent* Owner)
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

void __fastcall TfrfLogin::LabelClick( TObject *Sender )
{
  TLabel *l = dynamic_cast< TLabel* >( Sender );
  if ( l->FocusControl && l->FocusControl->CanFocus )
    l->FocusControl->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrfLogin::LoadFromFiler( TNNFTextStream *Filer )
{
  cbUser->Items->Text = Filer->ReadString();
  cbUser->Text        = Filer->ReadString();
  edDatabase->Text    = Filer->ReadString();
  edServer->Text      = Filer->ReadString();
  edPort->Text        = Filer->ReadString();
  edSchema->Text      = Filer->ReadString();

  fReadSuccess = true;
}

void __fastcall TfrfLogin::SaveToFiler( TNNFTextStream *Filer )
{
  Filer->WriteString( cbUser->Items->Text );
  Filer->WriteString( cbUser->Text ) ;
  Filer->WriteString( edDatabase->Text );
  Filer->WriteString( edServer->Text );
  Filer->WriteString( edPort->Text );
  Filer->WriteString( edSchema->Text );
}

void __fastcall TfrfLogin::ConnectionToControls()
{
  cbUser->Text = Connection->Params->UserName;
  edDatabase->Text = Connection->Params->Database;
  edServer->Text = Connection->Params->Values[ "Server" ];

  String aPort = Connection->Params->Values[ "Port" ];
  if ( !aPort.IsEmpty() )
    edPort->Text = aPort;

  edSchema->Text = Connection->Params->Values[ "PrabhupadaSchema" ];
}

bool __fastcall TfrfLogin::Login()
{
  Connection->Params->UserName                     = this->cbUser->Text;
  Connection->Params->Password                     = this->edPassword->Text;
  Connection->Params->Database                     = edDatabase->Text;
  Connection->Params->Values[ "Server" ]           = edServer->Text;
  Connection->Params->Values[ "Port" ]             = edPort->Text;
  String PrabhupadaSchema                          = edSchema->Text;
  Connection->Params->Values[ "PrabhupadaSchema" ] = PrabhupadaSchema;

  if ( PrabhupadaSchema.IsEmpty() ) {
    Connection->DriverName = L"SQLite_PrabhupadaSlovar";
    Connection->Params->Database = NNFConst::PrabhupadaSlovarFiles + Connection->Params->Database;
  } else
    Connection->DriverName = L"PostgreSQL_NewNavadvipa";

  if ( Connection->Connected ) {
    Connection->Connected = false;
    Connection->Connected = true;
  } else
    Connection->Connected = true;

  if ( Connection->Connected ) {
    NNF::SaveComboBox( cbUser, NNFConst::MaxStoryComboBox );

    if ( chbResetConfig->IsChecked ) {
      std::unique_ptr< TNNFQuery > qu( new TNNFQuery( this ) );
      qu->Connection = Connection;
      dmfNewNavadvipa->ResetConfig( Connection->Params->UserName, qu.get() );
    }
  }

  return Connection->Connected;
}

void __fastcall TfrfLogin::FormKeyDown( TObject *Sender, WORD &Key, TShiftState Shift )
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

void __fastcall TfrfLogin::SetConnection( TFDConnection *AConnection )
{
  if ( fConnection != AConnection ) {

    fConnection = AConnection;

    if ( !ReadSuccess )
      ConnectionToControls();
  }
}

