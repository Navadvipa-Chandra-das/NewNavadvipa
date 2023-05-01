//---------------------------------------------------------------------------

#ifndef FMX_NNDmPrabhupadaSlovarH
#define FMX_NNDmPrabhupadaSlovarH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "FMX_NNDBMiracle.h"
#include "FMX_NNDmRes.h"
#include "FMX_NNLanguageManager.h"
#include "FMX_NNRightsManager.h"
//---------------------------------------------------------------------------
class TdmfPrabhupadaSlovar : public TdmfRes
{
__published:	// IDE-managed Components
private:	// User declarations
  using inherited = TdmfRes;
public:		// User declarations
  __fastcall TdmfPrabhupadaSlovar( TComponent* Owner );
  void __fastcall DoLogin( TObject* Sender, TFDConnection *AConnection );
};
//---------------------------------------------------------------------------
extern PACKAGE TdmfPrabhupadaSlovar *dmfPrabhupadaSlovar;
extern PACKAGE const String SuperUserName;
//---------------------------------------------------------------------------
#endif
