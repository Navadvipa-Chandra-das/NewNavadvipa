//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFrPeriod.h"
#include "VCL_NNDmNewNavadvipa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNFrDiapazon"
#pragma link "VCL_NNComboBox"
#pragma link "VCL_NNComboBoxDateTime"
#pragma resource "*.dfm"
TfrvPeriod *frvPeriod;
//---------------------------------------------------------------------------
__fastcall TfrvPeriod::TfrvPeriod( TComponent* Owner )
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

void __fastcall TfrvPeriod::SyncDiapazonKind()
{
  switch ( DiapazonKind ) {
  case NNV::TDiapazonKind::Inner :
    cbdBegin->CheckStyleSetKind        = NNV::TCheckStyleSetKind::Greater;
    cbdEnd->CheckStyleSetKind          = NNV::TCheckStyleSetKind::Less;

    cbdBegin->Enabled                  = true;
    cbdEnd->Enabled                    = true;

    aDiapazonKindInner->Checked        = true;
    aApplyDiapazon->ImageIndex         = aDiapazonKindInner->ImageIndex;
    break;
  case NNV::TDiapazonKind::Outer :
    cbdBegin->CheckStyleSetKind        = NNV::TCheckStyleSetKind::Less;
    cbdEnd->CheckStyleSetKind          = NNV::TCheckStyleSetKind::Greater;

    cbdBegin->Enabled                  = true;
    cbdEnd->Enabled                    = true;

    aDiapazonKindOuter->Checked        = true;
    aApplyDiapazon->ImageIndex         = aDiapazonKindOuter->ImageIndex;
    break;
  case NNV::TDiapazonKind::HalfDiapazon :
    cbdBegin->CheckStyleSetKind        = NNV::TCheckStyleSetKind::FullSetWithoutNone;

    cbdBegin->Enabled                  = true;
    cbdEnd->Enabled                    = false;

    aDiapazonKindHalfDiapazon->Checked = true;
    aApplyDiapazon->ImageIndex         = aDiapazonKindHalfDiapazon->ImageIndex;
    break;
  case NNV::TDiapazonKind::Null :
    cbdBegin->Enabled                  = false;
    cbdEnd->Enabled                    = false;

    aDiapazonKindNull->Checked         = true;
    aApplyDiapazon->ImageIndex         = aDiapazonKindNull->ImageIndex;
    break;
  case NNV::TDiapazonKind::NotNull :
    cbdBegin->Enabled                  = false;
    cbdEnd->Enabled                    = false;

    aDiapazonKindNotNull->Checked      = true;
    aApplyDiapazon->ImageIndex         = aDiapazonKindNotNull->ImageIndex;
    break;
  }
}

void __fastcall TfrvPeriod::SetPeriod( NNV::TPeriod Value )
{
  if ( FPeriod != Value ) {
    FPeriod = Value;

    cbdBegin->CheckStyle = Period.BeginCheckStyle;
    cbdBegin->DateTime   = Period.Begin;
    cbdEnd->CheckStyle   = Period.EndCheckStyle;
    cbdEnd->DateTime     = Period.End;
    DiapazonKind         = Period.DiapazonKind;

    aSetDiapazon->Execute();
  }
}

void __fastcall TfrvPeriod::aApplyDiapazonExecute( TObject *Sender )
{
  NNV::TPeriod P;

  P.BeginCheckStyle = cbdBegin->CheckStyle;
  P.Begin           = cbdBegin->DateTime;
  P.EndCheckStyle   = cbdEnd->CheckStyle;
  P.End             = cbdEnd->DateTime;
  P.DiapazonKind    = DiapazonKind;

  Period = P;
}
//---------------------------------------------------------------------------

void __fastcall TfrvPeriod::SetNeedTime( bool Value )
{
  if ( FNeedTime != Value ) {
    FNeedTime = Value;

    cbdBegin->NeedTime = NeedTime;
    cbdEnd->NeedTime   = NeedTime;
  }
}

bool __fastcall TfrvPeriod::GetIsEmpty()
{
  return cbdBegin->IsEmpty && cbdEnd->IsEmpty;
}

void __fastcall TfrvPeriod::SetIsEmpty( bool Value )
{
  cbdBegin->IsEmpty = true;
  cbdEnd->IsEmpty   = true;
}

void __fastcall TfrvPeriod::SetOnBeginEndEnter( TNotifyEvent Value )
{
  cbdBegin->OnEnter = Value;
  cbdEnd->OnEnter   = Value;
}

