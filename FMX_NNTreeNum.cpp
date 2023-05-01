//---------------------------------------------------------------------------
#include <fmx.h>
#pragma hdrstop

#include "FMX_NNTreeNum.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
static inline void ValidCtrCheck( TNNFTreeNum * )
{
  new TNNFTreeNum( NULL );
}
//---------------------------------------------------------------------------
__fastcall TNNFTreeNum::TNNFTreeNum(TComponent* Owner)
  : TComponent(Owner)
{
}
//---------------------------------------------------------------------------
namespace Nntreenum
{

void __fastcall PACKAGE Register()
{
  TComponentClass classes[ 1 ] = { __classid( TNNFTreeNum ) };
  RegisterComponents( L"FMX New Navadvipa", classes, 0 );
}

}
//---------------------------------------------------------------------------
