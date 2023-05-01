// ---------------------------------------------------------------------------
#include <fmx.h>
#pragma hdrstop

#include "FMX_NNActionList.h"
#include "FMX_NNCommon.h"
#include "FMX_NNFmActionList.h"

#if (!__ANDROID__)
#pragma resource "*.res"
#endif

#pragma package(smart_init)
// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNNFActionList *)
{
  new TNNFActionList( NULL );
}

// ---------------------------------------------------------------------------
__fastcall TNNFActionList::TNNFActionList( TComponent* Owner )
  : TActionList( Owner )
{
}

// ---------------------------------------------------------------------------
namespace Fmx_nnactionlist
{
  void __fastcall PACKAGE Register()
  {
    TComponentClass classes[1] = { __classid( TNNFActionList ) };
    RegisterComponents( L"FMX New Navadvipa", classes, 0 );
  }
}
// ---------------------------------------------------------------------------

void __fastcall TNNFActionList::SaveToFiler( TNNFTextStream *Filer )
{
  Filer->WriteInt( ActionCount );
  for ( int i = 0; i < ActionCount; ++i )
    Filer->WriteShortCut( Actions[ i ]->ShortCut );
}

void __fastcall TNNFActionList::LoadFromFiler( TNNFTextStream *Filer )
{
  int j = Filer->ReadInt();
  for ( int i = 0; i < j; ++i )
    Actions[ i ]->ShortCut = Filer->ReadShortCut();
}

void __fastcall TNNFActionList::ShowPropertyDialog()
{
  NNF::FormCreate( __classid( TfmfActionList ), &fmfActionList );
  fmfActionList->Execute( this );
}
