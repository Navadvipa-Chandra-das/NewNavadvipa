// ---------------------------------------------------------------------------

#ifndef VCL_NNFrLoginH
#define VCL_NNFrLoginH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "VCL_NNCommon.h"
#include "VCL_NNDBMiracle.h"
#include <FireDAC.Comp.Client.hpp>

// ---------------------------------------------------------------------------
class TfrvLogin : public TFrame
{
__published: // IDE-managed Components
  TLabel *laUser;
  TLabel *laPassword;
  TLabel *laDatabase;
  TLabel *laServer;
  TLabel *laPort;
  TComboBox *cbUser;
  TEdit *edPassword;
  TEdit *edDatabase;
  TEdit *edServer;
  TEdit *edPort;
  TImage *imLogin;
  TCheckBox *chbResetConfig;
  TLabel *laSchema;
  TEdit *edSchema;

  void __fastcall LabelClick( TObject *Sender );

private: // User declarations
  using inherited = TFrame;
  bool fReadSuccess;
  TFDConnection *fConnection;

  void __fastcall SetConnection( TFDConnection *AConnection );

public: // User declarations
  __fastcall TfrvLogin( TComponent* Owner );
  void __fastcall LoadFromFiler( TNNVTextStream *Filer );
  void __fastcall SaveToFiler( TNNVTextStream *Filer );
  void __fastcall ConnectionToControls();
  bool __fastcall Login();
  void __fastcall FormKeyDown( TObject *Sender, WORD &Key, TShiftState Shift );
  __property bool ReadSuccess = { read = fReadSuccess };
  __property TFDConnection *Connection = { read = fConnection, write = SetConnection };
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrvLogin *frvLogin;
// ---------------------------------------------------------------------------
#endif
