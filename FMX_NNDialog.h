// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef FMX_NNDialogH
#define FMX_NNDialogH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FMX.Forms.hpp>
#include "FMX_NNDialogExec.h"

// ---------------------------------------------------------------------------
class PACKAGE TNNFDialog : public TNNFDialogExec
{
private:
  using inherited = TNNFDialogExec;
protected:
public:
  __fastcall TNNFDialog( TComponent* Owner );
__published:
  __property OnGetDialogForm;
  __property OnPrepare;
  __property OnUnPrepare;
  __property OnExecute;
};
// ---------------------------------------------------------------------------
#endif
