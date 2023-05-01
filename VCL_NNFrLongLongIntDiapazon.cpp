//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFrLongLongIntDiapazon.h"
#include "VCL_NNDmNewNavadvipa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNFrDiapazon"
#pragma link "VCL_NNComboBox"
#pragma link "VCL_NNNumberEdit"
#pragma resource "*.dfm"
TfrvLongLongIntDiapazon *frvLongLongIntDiapazon;
//---------------------------------------------------------------------------
__fastcall TfrvLongLongIntDiapazon::TfrvLongLongIntDiapazon( TComponent* Owner )
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

void __fastcall TfrvLongLongIntDiapazon::SyncDiapazonKind()
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

void __fastcall TfrvLongLongIntDiapazon::SetLongLongIntDiapazon( NNV::TLongLongIntDiapazon Value )
{
  if ( FLongLongIntDiapazon != Value ) {
    FLongLongIntDiapazon = Value;

    NNV::TNumberUnion N;
    neBegin->CheckStyle  = LongLongIntDiapazon.BeginCheckStyle;
    N.LongLongInt        = LongLongIntDiapazon.Begin;
    neBegin->NumberUnion = N;
    neEnd->CheckStyle    = LongLongIntDiapazon.EndCheckStyle;
    N.LongLongInt        = LongLongIntDiapazon.End;
    neEnd->NumberUnion   = N;
    DiapazonKind         = LongLongIntDiapazon.DiapazonKind;

    aSetDiapazon->Execute();
  }
}

void __fastcall TfrvLongLongIntDiapazon::aApplyDiapazonExecute(TObject *Sender)
{
  NNV::TLongLongIntDiapazon D;

  D.BeginCheckStyle = neBegin->CheckStyle;
  D.Begin           = neBegin->NumberUnion.LongLongInt;
  D.EndCheckStyle   = neEnd->CheckStyle;
  D.End             = neEnd->NumberUnion.LongLongInt;
  D.DiapazonKind    = DiapazonKind;

  LongLongIntDiapazon = D;
}
//---------------------------------------------------------------------------

bool __fastcall TfrvLongLongIntDiapazon::GetIsEmpty()
{
  return neBegin->IsEmpty && neEnd->IsEmpty;
}

void __fastcall TfrvLongLongIntDiapazon::SetIsEmpty( bool Value )
{
  neBegin->IsEmpty = true;
  neEnd->IsEmpty   = true;
}

void __fastcall TfrvLongLongIntDiapazon::SetOnBeginEndEnter( TNotifyEvent Value )
{
  neBegin->OnEnter = Value;
  neEnd->OnEnter   = Value;
}

