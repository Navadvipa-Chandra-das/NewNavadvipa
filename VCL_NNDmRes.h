// ---------------------------------------------------------------------------

#ifndef VCL_NNDmResH
#define VCL_NNDmResH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "VCL_NNRightsManager.h"
#include "VCL_NNLanguageManager.h"
#include "VCL_NNDBMiracle.h"

// ---------------------------------------------------------------------------
class TdmvRes : public TDataModule {
__published: // IDE-managed Components
  TNNVConfig *coData;
  TNNVRight *rrData;
  TNNVLanguage *lnData;
  void __fastcall BoolGalkaGetText( TField *Sender, UnicodeString &Text, bool DisplayText );
  void __fastcall BoolPlusMinusGetText( TField *Sender, UnicodeString &Text, bool DisplayText );
  void __fastcall DataModuleCreate( TObject *Sender );
  void __fastcall DataModuleDestroy( TObject *Sender );
  void __fastcall NationalNumdecGetText( TField *Sender, UnicodeString &Text
                                       , bool DisplayText);
  void __fastcall ClearDateSetText( TField *Sender, const UnicodeString Text );
  void __fastcall coDataGetFiler( TObject *Sender, TNNVTextStream *&Filer );
  void __fastcall MemoStringGetText( TField *Sender, UnicodeString &Text, bool DisplayText );
private: // User declarations
  using inherited = TDataModule;
protected:
  virtual void __fastcall Loaded();
public: // User declarations
  __fastcall TdmvRes( TComponent* Owner );
};

// ---------------------------------------------------------------------------
extern PACKAGE TdmvRes *dmvRes;
// ---------------------------------------------------------------------------
#endif
