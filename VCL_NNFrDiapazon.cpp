//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFrDiapazon.h"
#include "VCL_NNDmNewNavadvipa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNComboBox"
#pragma link "VCL_NNComboBoxDateTime"
#pragma resource "*.dfm"
TfrvDiapazon *frvDiapazon;
//---------------------------------------------------------------------------
__fastcall TfrvDiapazon::TfrvDiapazon( TComponent* Owner )
  : inherited( Owner )
{
  DiapazonKind = NNV::TDiapazonKind::Inner;
}
//---------------------------------------------------------------------------

void __fastcall TfrvDiapazon::SetDiapazonKind( NNV::TDiapazonKind Value )
{
  if ( FDiapazonKind != Value ) {
    FDiapazonKind = Value;

    SyncDiapazonKind();
  }
}

void __fastcall TfrvDiapazon::aDiapazonKindInnerExecute( TObject *Sender )
{
  DiapazonKind = NNV::TDiapazonKind::Inner;
}
//---------------------------------------------------------------------------

void __fastcall TfrvDiapazon::aDiapazonKindOuterExecute( TObject *Sender )
{
  DiapazonKind = NNV::TDiapazonKind::Outer;
}
//---------------------------------------------------------------------------

void __fastcall TfrvDiapazon::aDiapazonKindHalfDiapazonExecute( TObject *Sender )
{
  DiapazonKind = NNV::TDiapazonKind::HalfDiapazon;
}
//---------------------------------------------------------------------------

void __fastcall TfrvDiapazon::aDiapazonKindNullExecute( TObject *Sender )
{
  DiapazonKind = NNV::TDiapazonKind::Null;
}
//---------------------------------------------------------------------------

void __fastcall TfrvDiapazon::aDiapazonKindNotNullExecute( TObject *Sender )
{
  DiapazonKind = NNV::TDiapazonKind::NotNull;
}
//---------------------------------------------------------------------------

void __fastcall TfrvDiapazon::Loaded()
{
  inherited::Loaded();

  IsEmpty             = true;
  alDiapazon->Images  = dmvNewNavadvipa->ilDB;
  tbrDiapazon->Images = dmvNewNavadvipa->ilDB;
}

void __fastcall TfrvDiapazon::aClearDiapazonExecute( TObject *Sender )
{
  IsEmpty = true;
}
//---------------------------------------------------------------------------

