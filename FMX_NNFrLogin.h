//---------------------------------------------------------------------------

#ifndef FMX_NNFrLoginH
#define FMX_NNFrLoginH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.ListBox.hpp>
#include <FireDAC.Comp.Client.hpp>
#include "FMX_NNCommon.h"
#include <FMX.Edit.hpp>
#include <FMX.ComboEdit.hpp>
//---------------------------------------------------------------------------
class TfrfLogin : public TFrame
{
__published:	// IDE-managed Components
  TImageControl *imLogin;
  TLabel *laUser;
  TLabel *laPassword;
  TLabel *laDatabase;
  TLabel *laServer;
  TLabel *laPort;
  TLabel *laSchema;
  TEdit *edPassword;
  TEdit *edDatabase;
  TEdit *edServer;
  TEdit *edPort;
  TEdit *edSchema;
  TCheckBox *chbResetConfig;
  TComboEdit *cbUser;
  void __fastcall LabelClick(TObject *Sender);
private:	// User declarations
  using inherited = TFrame;
  bool fReadSuccess;
  TFDConnection *fConnection;

  void __fastcall SetConnection( TFDConnection *AConnection );

public:		// User declarations
  __fastcall TfrfLogin(TComponent* Owner);
  void __fastcall LoadFromFiler( TNNFTextStream *Filer );
  void __fastcall SaveToFiler( TNNFTextStream *Filer );
  void __fastcall ConnectionToControls();
  bool __fastcall Login();
  void __fastcall FormKeyDown( TObject *Sender, WORD &Key, TShiftState Shift );
  __property bool ReadSuccess = { read = fReadSuccess };
  __property TFDConnection *Connection = { read = fConnection, write = SetConnection };
};
//---------------------------------------------------------------------------
extern PACKAGE TfrfLogin *frfLogin;
//---------------------------------------------------------------------------
#endif
