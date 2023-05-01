//---------------------------------------------------------------------------

#ifndef FMX_NNDmResH
#define FMX_NNDmResH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "FMX_NNDBMiracle.h"
#include "FMX_NNLanguageManager.h"
#include "FMX_NNRightsManager.h"
#include "FMX_NNConst.h"
#include "FMX_NNStrUtil.h"
//---------------------------------------------------------------------------
class TdmfRes : public TDataModule
{
__published:	// IDE-managed Components
  TNNFConfig *coData;
  TNNFRight *rrData;
  TNNFLanguage *lnData;
  void __fastcall DataModuleCreate(TObject *Sender);
  void __fastcall DataModuleDestroy(TObject *Sender);
  void __fastcall BoolGalkaGetText( TField *Sender, UnicodeString &Text, bool DisplayText );
  void __fastcall BoolPlusMinusGetText( TField *Sender, UnicodeString &Text, bool DisplayText );
  void __fastcall NationalNumdecGetText( TField *Sender, UnicodeString &Text
                                       , bool DisplayText);
  void __fastcall ClearDateSetText( TField *Sender, const UnicodeString Text );
  void __fastcall coDataGetFiler( TObject *Sender, TNNFTextStream *&Filer );
  void __fastcall MemoStringGetText( TField *Sender, UnicodeString &Text, bool DisplayText );
private:	// User declarations
  using inherited = TDataModule;
protected:
  virtual void __fastcall Loaded();
public:		// User declarations
  __fastcall TdmfRes(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmfRes *dmfRes;
//---------------------------------------------------------------------------
#endif
