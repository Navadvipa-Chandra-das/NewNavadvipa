// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <fmx.h>
#pragma hdrstop

#include "FMX_NNDialog.h"

#pragma link "FMX_NNDialogExec"

#if (!__ANDROID__)
#pragma resource "*.res"
#endif

#pragma package(smart_init)
// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck( TNNFDialog * )
{
  new TNNFDialog( NULL );
}

// ---------------------------------------------------------------------------
__fastcall TNNFDialog::TNNFDialog( TComponent* Owner )
  : inherited( Owner )
{
}

// ---------------------------------------------------------------------------
namespace Fmx_nndialog
{
  void __fastcall PACKAGE Register()
  {
    TComponentClass classes[ 1 ] = { __classid(TNNFDialog ) };
    RegisterComponents( L"FMX New Navadvipa", classes, 0 );
  }
}
// ---------------------------------------------------------------------------
