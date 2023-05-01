//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFrIntDiapazon.h"
#include "VCL_NNDmNewNavadvipa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNFrDiapazon"
#pragma link "VCL_NNComboBox"
#pragma link "VCL_NNNumberEdit"
#pragma resource "*.dfm"
TfrvIntDiapazon *frvIntDiapazon;
//---------------------------------------------------------------------------
__fastcall TfrvIntDiapazon::TfrvIntDiapazon( TComponent* Owner )
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

void __fastcall TfrvIntDiapazon::SyncDiapazonKind()
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

void __fastcall TfrvIntDiapazon::SetIntDiapazon( NNV::TIntDiapazon Value )
{
  if ( FIntDiapazon != Value ) {
    FIntDiapazon = Value;

    NNV::TNumberUnion N;
    neBegin->CheckStyle  = IntDiapazon.BeginCheckStyle;
    N.Int                = IntDiapazon.Begin;
    neBegin->NumberUnion = N;
    neEnd->CheckStyle    = IntDiapazon.EndCheckStyle;
    N.Int                = IntDiapazon.End;
    neEnd->NumberUnion   = N;
    DiapazonKind         = IntDiapazon.DiapazonKind;

    aSetDiapazon->Execute();
  }
}

void __fastcall TfrvIntDiapazon::aApplyDiapazonExecute(TObject *Sender)
{
  NNV::TIntDiapazon ID;

  ID.BeginCheckStyle = neBegin->CheckStyle;
  ID.Begin           = neBegin->NumberUnion.Int;
  ID.EndCheckStyle   = neEnd->CheckStyle;
  ID.End             = neEnd->NumberUnion.Int;
  ID.DiapazonKind    = DiapazonKind;

  IntDiapazon = ID;
}
//---------------------------------------------------------------------------

bool __fastcall TfrvIntDiapazon::GetIsEmpty()
{
  return neBegin->IsEmpty && neEnd->IsEmpty;
}

void __fastcall TfrvIntDiapazon::SetIsEmpty( bool Value )
{
  neBegin->IsEmpty = true;
  neEnd->IsEmpty   = true;
}

void __fastcall TfrvIntDiapazon::SetOnBeginEndEnter( TNotifyEvent Value )
{
  neBegin->OnEnter = Value;
  neEnd->OnEnter   = Value;
}

