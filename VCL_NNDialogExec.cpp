// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNDialogExec.h"
#include "VCL_NNConst.h"
#include "VCL_NNCommon.h"
#include "VCL_NNFmRes.h"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TNNVDialogExec::TNNVDialogExec( TComponent* Owner )
  : inherited(Owner)
{
}

void __fastcall TNNVDialogExec::DoGetDialogForm( TCustomForm *&fm )
{
  if ( fOnGetDialogForm )
    fOnGetDialogForm( this, fm );
}

void __fastcall TNNVDialogExec::DoPrepare(TObject *Sender)
{
  if ( fOnPrepare )
    fOnPrepare( Sender );
}

void __fastcall TNNVDialogExec::DoUnPrepare(TObject *Sender)
{
  if ( fOnUnPrepare )
    fOnUnPrepare( Sender );
}

void __fastcall TNNVDialogExec::DoExecute(TObject *Sender)
{
  if ( fOnExecute )
    fOnExecute( Sender );
}

void __fastcall TNNVDialogExec::Execute( TComponent *SenderForm )
{
  TCustomForm *cf;
  TfmvRes *fm;
  DoGetDialogForm( cf );
  fm = dynamic_cast< TfmvRes* >( cf );
  if ( !fm )
    return;

  fm->fbRes->OnPrepare   = DoPrepare;
  fm->fbRes->OnUnPrepare = DoUnPrepare;
  fm->fbRes->OnExecute   = DoExecute;

  fm->ShowDialog( SenderForm );
}

void __fastcall TNNVDialogExec::Execute( TRect R, TComponent *SenderForm )
{
  TCustomForm *cf;
  TfmvRes *fm;
  DoGetDialogForm( cf );
  fm = dynamic_cast< TfmvRes* >( cf );
  if ( !fm )
    return;

  fm->BoundsRect = NNV::CalcRect( R, fm->BoundsRect );

  fm->fbRes->OnPrepare   = DoPrepare;
  fm->fbRes->OnUnPrepare = DoUnPrepare;
  fm->fbRes->OnExecute   = DoExecute;

  fm->ShowDialog( SenderForm );
}

void __fastcall TNNVDialogExec::Execute( TControl *Control, TComponent *SenderForm )
{
  TPoint P = Control->ClientOrigin;
  Execute( Bounds( P.x, P.y, Control->Width, Control->Height ), SenderForm );
}

