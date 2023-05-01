//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFrShortIntDiapazon.h"
#include "VCL_NNDmNewNavadvipa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNFrDiapazon"
#pragma link "VCL_NNComboBox"
#pragma link "VCL_NNNumberEdit"
#pragma resource "*.dfm"
TfrvShortIntDiapazon *frvShortIntDiapazon;
//---------------------------------------------------------------------------
__fastcall TfrvShortIntDiapazon::TfrvShortIntDiapazon( TComponent* Owner )
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

void __fastcall TfrvShortIntDiapazon::SyncDiapazonKind()
{
  switch ( DiapazonKind ) {
  case NNV::TDiapazonKind::Inner :
    neBegin->CheckStyleSetKind         = NNV::TCheckStyleSetKind::Greater;
    neEnd->CheckStyleSetKind           = NNV::TCheckStyleSetKind::Less;

    neBegin->Enabled                   = true;
    neEnd->Enabled                     = true;

    aDiapazonKindInner->Checked        = true;
    aApplyDiapazon->ImageIndex         = aDiapazonKindInner->ImageIndex;
    break;
  case NNV::TDiapazonKind::Outer :
    neBegin->CheckStyleSetKind         = NNV::TCheckStyleSetKind::Less;
    neEnd->CheckStyleSetKind           = NNV::TCheckStyleSetKind::Greater;

    neBegin->Enabled                   = true;
    neEnd->Enabled                     = true;

    aDiapazonKindOuter->Checked        = true;
    aApplyDiapazon->ImageIndex         = aDiapazonKindOuter->ImageIndex;
    break;
  case NNV::TDiapazonKind::HalfDiapazon :
    neBegin->CheckStyleSetKind         = NNV::TCheckStyleSetKind::FullSetWithoutNone;

    neBegin->Enabled                   = true;
    neEnd->Enabled                     = false;

    aDiapazonKindHalfDiapazon->Checked = true;
    aApplyDiapazon->ImageIndex         = aDiapazonKindHalfDiapazon->ImageIndex;
    break;
  case NNV::TDiapazonKind::Null :
    neBegin->Enabled                   = false;
    neEnd->Enabled                     = false;

    aDiapazonKindNull->Checked         = true;
    aApplyDiapazon->ImageIndex         = aDiapazonKindNull->ImageIndex;
    break;
  case NNV::TDiapazonKind::NotNull :
    neBegin->Enabled                   = false;
    neEnd->Enabled                     = false;

    aDiapazonKindNotNull->Checked      = true;
    aApplyDiapazon->ImageIndex         = aDiapazonKindNotNull->ImageIndex;
    break;
  }
}

void __fastcall TfrvShortIntDiapazon::SetShortIntDiapazon( NNV::TShortIntDiapazon Value )
{
  if ( FShortIntDiapazon != Value ) {
    FShortIntDiapazon = Value;

    NNV::TNumberUnion N;
    neBegin->CheckStyle  = ShortIntDiapazon.BeginCheckStyle;
    N.ShortInt           = ShortIntDiapazon.Begin;
    neBegin->NumberUnion = N;
    neEnd->CheckStyle    = ShortIntDiapazon.EndCheckStyle;
    N.ShortInt           = ShortIntDiapazon.End;
    neEnd->NumberUnion   = N;
    DiapazonKind         = ShortIntDiapazon.DiapazonKind;

    aSetDiapazon->Execute();
  }
}

void __fastcall TfrvShortIntDiapazon::aApplyDiapazonExecute( TObject *Sender )
{
  NNV::TShortIntDiapazon D;

  D.BeginCheckStyle = neBegin->CheckStyle;
  D.Begin           = neBegin->NumberUnion.ShortInt;
  D.EndCheckStyle   = neEnd->CheckStyle;
  D.End             = neEnd->NumberUnion.ShortInt;
  D.DiapazonKind    = DiapazonKind;

  ShortIntDiapazon = D;
}
//---------------------------------------------------------------------------

bool __fastcall TfrvShortIntDiapazon::GetIsEmpty()
{
  return neBegin->IsEmpty && neEnd->IsEmpty;
}

void __fastcall TfrvShortIntDiapazon::SetIsEmpty( bool Value )
{
  neBegin->IsEmpty = true;
  neEnd->IsEmpty   = true;
}

void __fastcall TfrvShortIntDiapazon::SetOnBeginEndEnter( TNotifyEvent Value )
{
  neBegin->OnEnter = Value;
  neEnd->OnEnter   = Value;
}

