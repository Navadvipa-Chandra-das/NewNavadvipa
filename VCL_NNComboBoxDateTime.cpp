// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNComboBoxDateTime.h"
#include "VCL_NNCommon.h"
#include "VCL_NNConst.h"
#include "VCL_NNFmDateTime.h"
#include "VCL_NNFormAdmin.h"
#include "VCL_NNColor.h"

#pragma resource "*.res"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNNVComboBoxDateTime *)
{
    new TNNVComboBoxDateTime(NULL);
}
//---------------------------------------------------------------------------
__fastcall TNNVComboBoxDateTime::TNNVComboBoxDateTime(TComponent* Owner)
  : inherited( Owner )
  , FNeedTime( false )
  , FFormatStr( NNVConst::NlsDateFormatLong )
  , FColorApply( false )
  , FSColor( clWindow )
  , SFColor( clWindowText )
  , FIsUserCanChangeCheckStyle( true )
{
  NeedTime                  = true;
  IsUserCanChangeCheckStyle = false;
  CheckStyle                = NNV::TCheckStyleValue::None;
  CheckStyleSetKind         = NNV::TCheckStyleSetKind::FullSet;
  EditMask                  = NNVConst::EditMaskDateFormatLong;
  DateTime                  = InitialDateTime();
}

__fastcall TNNVComboBoxDateTime::~TNNVComboBoxDateTime()
{
  NNVFormList.Delete( fmvDateTime, this );
}

//---------------------------------------------------------------------------
namespace Vcl_nncomboboxdatetime
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TNNVComboBoxDateTime)};
        RegisterComponents( L"VCL New Navadvipa", classes, 0 );
    }
}
//---------------------------------------------------------------------------

void __fastcall TNNVComboBoxDateTime::SetCheckStyle( NNV::TCheckStyleValue Value )
{
  if ( FCheckStyle != Value ) {
    FCheckStyle = Value;

    SyncEditMaskAndFormatStr();
  }
}

void __fastcall TNNVComboBoxDateTime::SetCheckStyleSetKind( NNV::TCheckStyleSetKind Value )
{
  if ( FCheckStyleSetKind != Value ) {
    FCheckStyleSetKind = Value;

    VectorCheckStyleValue.clear();
    switch ( CheckStyleSetKind ) {
    case NNV::TCheckStyleSetKind::None :
      break;
    case NNV::TCheckStyleSetKind::FullSet :
      VectorCheckStyleValue.push_back( NNV::TCheckStyleValue::None           );
      VectorCheckStyleValue.push_back( NNV::TCheckStyleValue::Equal          );
      VectorCheckStyleValue.push_back( NNV::TCheckStyleValue::Greater        );
      VectorCheckStyleValue.push_back( NNV::TCheckStyleValue::GreaterOrEqual );
      VectorCheckStyleValue.push_back( NNV::TCheckStyleValue::Less           );
      VectorCheckStyleValue.push_back( NNV::TCheckStyleValue::LessOrEqual    );
      break;
    case NNV::TCheckStyleSetKind::FullSetWithoutNone :
      VectorCheckStyleValue.push_back( NNV::TCheckStyleValue::Equal          );
      VectorCheckStyleValue.push_back( NNV::TCheckStyleValue::Greater        );
      VectorCheckStyleValue.push_back( NNV::TCheckStyleValue::GreaterOrEqual );
      VectorCheckStyleValue.push_back( NNV::TCheckStyleValue::Less           );
      VectorCheckStyleValue.push_back( NNV::TCheckStyleValue::LessOrEqual    );
      break;
    case NNV::TCheckStyleSetKind::Greater :
      VectorCheckStyleValue.push_back( NNV::TCheckStyleValue::Greater        );
      VectorCheckStyleValue.push_back( NNV::TCheckStyleValue::GreaterOrEqual );
      break;
    case NNV::TCheckStyleSetKind::Less :
      VectorCheckStyleValue.push_back( NNV::TCheckStyleValue::Less           );
      VectorCheckStyleValue.push_back( NNV::TCheckStyleValue::LessOrEqual    );
      break;
    }

    FCurrentIteratorCheckStyle = VectorCheckStyleValue.begin();
    if ( CheckStyleSetKind == NNV::TCheckStyleSetKind::Greater ||
         CheckStyleSetKind == NNV::TCheckStyleSetKind::Less )
      ++FCurrentIteratorCheckStyle;
    CheckStyle = (*FCurrentIteratorCheckStyle);
  }
}

TDateTime __fastcall TNNVComboBoxDateTime::InitialDateTime()
{
  return NeedTime ? Now() : Date();
}

void __fastcall TNNVComboBoxDateTime::DoPrepare( TObject* Sender )
{
  fmvDateTime->DateTime = IsEmpty ? InitialDateTime() : DateTime;
}

void __fastcall TNNVComboBoxDateTime::DoExecuteDialog( TObject* Sender )
{
  if ( !ReadOnly )
    DateTime = fmvDateTime->DateTime;
}

void __fastcall TNNVComboBoxDateTime::KeyDown( Word &Key, Classes::TShiftState Shift )
{
  switch ( Key ) {
  case vkUp :
    if ( IsUserCanChangeCheckStyle && Shift == TShiftState() << ssAlt )
      NextCheckStyleDateTime();
    break;
  case vkReturn :
    TextToDateTime();
    break;
  default :
    inherited::KeyDown( Key, Shift );
  }
}

void __fastcall TNNVComboBoxDateTime::NextCheckStyleDateTime()
{
  if ( VectorCheckStyleValue.empty() )
    return;

  ++FCurrentIteratorCheckStyle;
  if ( FCurrentIteratorCheckStyle == VectorCheckStyleValue.end() )
    FCurrentIteratorCheckStyle = VectorCheckStyleValue.begin();
  CheckStyle = (*FCurrentIteratorCheckStyle);
}

bool __fastcall TNNVComboBoxDateTime::TextEmptyDate()
{
  String PF = NNV::PrefixFormatCheckStyleValue( CheckStyle )
       , S = NeedTime ? NNVConst::StrEmptyDateLong : NNVConst::StrEmptyDateShort;
  return Text == PF + S;
}

void __fastcall TNNVComboBoxDateTime::ButtonClick( TComponent *SenderForm )
{
  NNVFormList.New( __classid( TfmvDateTime ), &fmvDateTime, this );

  fmvDateTime->BoundsRect         = NNV::CalcRect( CWRect, fmvDateTime->BoundsRect );
  fmvDateTime->NeedTime           = NeedTime;

  fmvDateTime->fbRes->OnPrepare   = DoPrepare;
  fmvDateTime->fbRes->OnUnPrepare = NULL;
  fmvDateTime->fbRes->OnExecute   = DoExecuteDialog;

  fmvDateTime->ShowDialog( SenderForm );
}

void __fastcall TNNVComboBoxDateTime::SetDateTime( TDateTime Value )
{
  if ( FDateTime != Value ) {
    FDateTime = Value;
    FIsEmpty  = false;

    DoExecute();
  }
  TextRefresh();
}

void __fastcall TNNVComboBoxDateTime::TextRefresh()
{
  if ( IsEmpty )
    Text = "";
  else
    Text = FormatDateTime( FormatStr, DateTime );

  RestoreColor();
}

void __fastcall TNNVComboBoxDateTime::RestoreColor()
{
  Color       = FSColor;
  Font->Color = SFColor;

  FColorApply  = false;
}

void __fastcall TNNVComboBoxDateTime::SetFormatStr( String Value )
{
  if ( FFormatStr != Value ) {
    FFormatStr = Value;

    TextRefresh();
  }
}

void __fastcall TNNVComboBoxDateTime::SetNeedTime( bool Value )
{
  if ( FNeedTime != Value ) {
    FNeedTime = Value;

    SyncEditMaskAndFormatStr();
  }
}

void __fastcall TNNVComboBoxDateTime::SyncEditMaskAndFormatStr()
{
  String P = NNV::PrefixCheckStyleValue( CheckStyle );
  String PF = NNV::PrefixFormatCheckStyleValue( CheckStyle );

  if ( NeedTime ) {
    EditMask  = P  + NNVConst::EditMaskDateFormatLong;
    FormatStr = PF + NNVConst::NlsDateFormatLong;
  } else {
    EditMask  = P  + NNVConst::EditMaskDateFormatShort;
    FormatStr = PF + NNVConst::NlsDateFormatShort;
  }

  TextRefresh();
}

bool __fastcall TNNVComboBoxDateTime::GetIsEmpty()
{
  return FIsEmpty || IsNull();
}

void __fastcall TNNVComboBoxDateTime::SetIsEmpty( bool Value )
{
  FIsEmpty = Value;
  TextRefresh();
}

void __fastcall TNNVComboBoxDateTime::TextToDateTime()
{
  if ( TextEmptyDate() )
    IsEmpty = true;
  else
    DateTime = StrToDateTime( Text );
}

void __fastcall TNNVComboBoxDateTime::CMExit( TCMExit &Message )
{
  if ( IsMasked && ( !ComponentState.Contains( csDesigning ) ) ) {
    int Pos = SelStart;
    try {
      TextToDateTime();
      inherited::Dispatch( &Message );
    } catch ( EConvertError &er ) {
      MaskState = MaskState << msReEnter;
      SetFocus();
      SetCursor( Pos );
      String S = "Неверная дата: " + Text;
      ShowMessage( S );
    }
  }
}

void __fastcall TNNVComboBoxDateTime::Change()
{
  inherited::Change();
  if ( !FColorApply &&
       !ComponentState.Contains( csLoading ) &&
       !ComponentState.Contains( csDesigning ) ) {

    FColorApply = true;

    FSColor     = Color;
    SFColor     = Font->Color;

    Color       = NNVConst::FonColorValueChange;
    Font->Color = NNVConst::FontColorValueChange;
  }
}

void __fastcall TNNVComboBoxDateTime::Loaded(void)
{
  inherited::Loaded();
  FSColor  = Color;
  SFColor = Font->Color;
}

//void __fastcall TNNVComboBoxDateTime::CreateWnd(void)
//{
//  inherited::CreateWnd();
//  //ButtonKind = bkCalendar;
//}

