// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNActionList.h"
#include "VCL_NNCommon.h"
#include "VCL_NNFmActionList.h"
#pragma resource "*.res"
#pragma package(smart_init)
// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNNVActionList *)
{
  new TNNVActionList( NULL );
}

// ---------------------------------------------------------------------------
__fastcall TNNVActionList::TNNVActionList( TComponent* Owner )
  : TActionList( Owner )
{
}

// ---------------------------------------------------------------------------
namespace Vcl_nnactionlist
{
  void __fastcall PACKAGE Register()
  {
    TComponentClass classes[1] = { __classid( TNNVActionList ) };
    RegisterComponents( L"VCL New Navadvipa", classes, 0 );
  }
}
// ---------------------------------------------------------------------------

void __fastcall TNNVActionList::SaveToFiler( TNNVTextStream *Filer )
{
  Filer->WriteInt( ActionCount );
  for ( int i = 0; i < ActionCount; ++i )
    Filer->WriteShortCut( Actions[ i ]->ShortCut );
}

void __fastcall TNNVActionList::LoadFromFiler( TNNVTextStream *Filer )
{
  int j = Filer->ReadInt();
  for ( int i = 0; i < j; ++i )
    Actions[ i ]->ShortCut = Filer->ReadShortCut();
}

void __fastcall TNNVActionList::ShowPropertyDialog()
{
  NNV::FormCreate( __classid( TfmvActionList ), &fmvActionList );
  fmvActionList->Execute( this );
}

