// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <fmx.h>
#pragma hdrstop

#include "FMX_NNFlagBox.h"
#include "FMX_NNFmRes.h"

#if (!__ANDROID__)
#pragma resource "*.res"
#endif

#pragma package(smart_init)
// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck( TNNFFlagBox* )
{
  new TNNFFlagBox( NULL );
}

// ---------------------------------------------------------------------------
__fastcall TNNFFlagBox::TNNFFlagBox( TComponent* Owner )
  : inherited( Owner )
{
}

// ---------------------------------------------------------------------------
namespace Fmx_nnflagbox
{
  void __fastcall PACKAGE Register()
  {
    TComponentClass classes[ 1 ] = { __classid( TNNFFlagBox ) };
    RegisterComponents( L"FMX New Navadvipa", classes, 0 );
  }
}
// ---------------------------------------------------------------------------

void __fastcall TNNFFlagBox::DoPrepare()
{
  TfmfRes *fm = dynamic_cast< TfmfRes* >( SenderForm );
  if ( fm )
    fm->DialogCloseOnDeactivate = false;

  if ( FOnPrepare )
    FOnPrepare( this );
}

void __fastcall TNNFFlagBox::DoUnPrepare()
{
  TfmfRes *fm = dynamic_cast< TfmfRes* >( SenderForm );
  if ( fm )
    fm->DialogCloseOnDeactivate = true;

  if ( FOnUnPrepare )
    FOnUnPrepare( this );
}

void __fastcall TNNFFlagBox::DoExecute()
{
  TfmfRes *fm = dynamic_cast< TfmfRes* >( SenderForm );
  try {
    if ( fm )
      fm->CanUserClose = false;

    if ( FOnExecute )
      FOnExecute( this );
  } __finally {
    if ( fm )
      fm->CanUserClose = true;
  }
};

void __fastcall TNNFFlagBox::DoSynchronization()
{
  if ( FOnSynchronization )
    FOnSynchronization( this );
}

