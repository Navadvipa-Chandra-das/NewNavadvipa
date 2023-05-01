//---------------------------------------------------------------------------

#ifndef FMX_NNFmLoginH
#define FMX_NNFmLoginH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FMX.ActnList.hpp>
#include <System.Actions.hpp>
#include <FMX.Types.hpp>
#include "FMX_NNActionList.h"
#include "FMX_NNDBMiracle.h"
#include "FMX_NNFlagBox.h"
#include "FMX_NNFmRes.h"
#include "FMX_NNLanguageManager.h"
#include "FMX_NNRightsManager.h"
#include "FMX_NNFrLogin.h"
//---------------------------------------------------------------------------
class TfmfLogin : public TfmfRes
{
__published:	// IDE-managed Components
  TfrfLogin *frfLogin;
  void __fastcall coResLoad(TObject *Sender);
  void __fastcall coResSave(TObject *Sender);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
private:	// User declarations
  using inherited = TfmfRes;
protected:
  virtual void __fastcall Loaded();
public:		// User declarations
  __fastcall TfmfLogin( TComponent* Owner );
  void __fastcall ShowFormLogin( TFDConnection *AConnection );
};
//---------------------------------------------------------------------------
extern PACKAGE TfmfLogin *fmfLogin;
//---------------------------------------------------------------------------
#endif
