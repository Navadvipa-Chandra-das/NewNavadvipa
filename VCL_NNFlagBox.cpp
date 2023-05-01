// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFlagBox.h"
#include "VCL_NNFmRes.h"
#pragma resource "*.res"
#pragma package(smart_init)
// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck( TNNVFlagBox* )
{
  new TNNVFlagBox( NULL );
}

// ---------------------------------------------------------------------------
__fastcall TNNVFlagBox::TNNVFlagBox( TComponent* Owner )
  : inherited( Owner )
{
}

// ---------------------------------------------------------------------------
namespace Vcl_nnflagbox
{
  void __fastcall PACKAGE Register()
  {
    TComponentClass classes[ 1 ] = { __classid( TNNVFlagBox ) };
    RegisterComponents( L"VCL New Navadvipa", classes, 0 );
  }
}
// ---------------------------------------------------------------------------

void __fastcall TNNVFlagBox::DoPrepare()
{
  TfmvRes *fm = dynamic_cast< TfmvRes* >( SenderForm );
  if ( fm )
    fm->DialogCloseOnDeactivate = false;

  if ( FOnPrepare )
    FOnPrepare( this );
}

void __fastcall TNNVFlagBox::DoUnPrepare()
{
  TfmvRes *fm = dynamic_cast< TfmvRes* >( SenderForm );
  if ( fm )
    fm->DialogCloseOnDeactivate = true;

  if ( FOnUnPrepare )
    FOnUnPrepare( this );
}

void __fastcall TNNVFlagBox::DoExecute()
{
  TfmvRes *fm = dynamic_cast< TfmvRes* >( SenderForm );
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

void __fastcall TNNVFlagBox::DoSynchronization()
{
  if ( FOnSynchronization )
    FOnSynchronization( this );
}

