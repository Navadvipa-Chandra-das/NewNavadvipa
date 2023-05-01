//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFrDoubleDiapazon.h"
#include "VCL_NNDmNewNavadvipa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNFrDiapazon"
#pragma link "VCL_NNComboBox"
#pragma link "VCL_NNNumberEdit"
#pragma resource "*.dfm"
TfrvDoubleDiapazon *frvDoubleDiapazon;
//---------------------------------------------------------------------------
__fastcall TfrvDoubleDiapazon::TfrvDoubleDiapazon(TComponent* Owner)
  : TfrvDiapazon(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrvDoubleDiapazon::SyncDiapazonKind()
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

void __fastcall TfrvDoubleDiapazon::SetDoubleDiapazon( NNV::TDoubleDiapazon Value )
{
  if ( FDoubleDiapazon != Value ) {
    FDoubleDiapazon = Value;

    NNV::TNumberUnion N;
    neBegin->CheckStyle  = DoubleDiapazon.BeginCheckStyle;
    N.Double             = DoubleDiapazon.Begin;
    neBegin->NumberUnion = N;
    neEnd->CheckStyle    = DoubleDiapazon.EndCheckStyle;
    N.Double             = DoubleDiapazon.End;
    neEnd->NumberUnion   = N;
    DiapazonKind         = DoubleDiapazon.DiapazonKind;

    aSetDiapazon->Execute();
  }
}

void __fastcall TfrvDoubleDiapazon::aApplyDiapazonExecute( TObject *Sender )
{
  NNV::TDoubleDiapazon DD;

  DD.BeginCheckStyle = neBegin->CheckStyle;
  DD.Begin           = neBegin->NumberUnion.Double;
  DD.EndCheckStyle   = neEnd->CheckStyle;
  DD.End             = neEnd->NumberUnion.Double;
  DD.DiapazonKind    = DiapazonKind;

  DoubleDiapazon = DD;
}
//---------------------------------------------------------------------------

bool __fastcall TfrvDoubleDiapazon::GetIsEmpty()
{
  return neBegin->IsEmpty && neEnd->IsEmpty;
}

void __fastcall TfrvDoubleDiapazon::SetIsEmpty( bool Value )
{
  neBegin->IsEmpty = true;
  neEnd->IsEmpty   = true;
}

void __fastcall TfrvDoubleDiapazon::SetOnBeginEndEnter( TNotifyEvent Value )
{
  neBegin->OnEnter = Value;
  neEnd->OnEnter   = Value;
}

