// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <fmx.h>
#pragma hdrstop

#include "FMX_NNDialogExec.h"
#include "FMX_NNConst.h"
#include "FMX_NNCommon.h"
#include "FMX_NNFmRes.h"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TNNFDialogExec::TNNFDialogExec( TComponent* Owner )
  : inherited( Owner )
{
}

void __fastcall TNNFDialogExec::DoGetDialogForm( TCommonCustomForm *&fm )
{
  if ( fOnGetDialogForm )
    fOnGetDialogForm( this, fm );
}

void __fastcall TNNFDialogExec::DoPrepare( TObject *Sender )
{
  if ( fOnPrepare )
    fOnPrepare( Sender );
}

void __fastcall TNNFDialogExec::DoUnPrepare( TObject *Sender )
{
  if ( fOnUnPrepare )
    fOnUnPrepare( Sender );
}

void __fastcall TNNFDialogExec::DoExecute( TObject *Sender )
{
  if ( fOnExecute )
    fOnExecute( Sender );
}

void __fastcall TNNFDialogExec::Execute( TComponent *SenderForm )
{
  TCommonCustomForm *cf;
  TfmfRes *fm;
  DoGetDialogForm( cf );
  fm = dynamic_cast< TfmfRes* >( cf );
  if ( !fm )
    return;

  fm->fbRes->OnPrepare   = DoPrepare;
  fm->fbRes->OnUnPrepare = DoUnPrepare;
  fm->fbRes->OnExecute   = DoExecute;

  fm->ShowDialog( SenderForm );
}

void __fastcall TNNFDialogExec::Execute( TRect R, TComponent *SenderForm )
{
  TCommonCustomForm *cf;
  TfmfRes *fm;
  DoGetDialogForm( cf );
  fm = dynamic_cast< TfmfRes* >( cf );
  if ( !fm )
    return;

  TRect BR = NNF::CalcRect( R, TRect( TPoint( fm->Left, fm->Top ), fm->Width, fm->Height ) );
  fm->Left = BR.Location.X;
  fm->Top  = BR.Location.Y;

  fm->fbRes->OnPrepare   = DoPrepare;
  fm->fbRes->OnUnPrepare = DoUnPrepare;
  fm->fbRes->OnExecute   = DoExecute;

  fm->ShowDialog( SenderForm );
}

void __fastcall TNNFDialogExec::Execute( TControl *Control, TComponent *SenderForm )
{
  TPoint P = TPoint( Control->Position->X, Control->Position->Y );
  Execute( Bounds( P.x, P.y, Control->Width, Control->Height ), SenderForm );
}

