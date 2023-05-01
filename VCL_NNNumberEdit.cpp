// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNNumberEdit.h"
#include "VCL_NNCommon.h"
#include "VCL_NNConst.h"
#include "VCL_NNFormAdmin.h"
#include "VCL_NNColor.h"
#include "VCL_NNStrUtil.h"

#pragma resource "*.res"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNNVNumberEdit *)
{
    new TNNVNumberEdit(NULL);
}
//---------------------------------------------------------------------------
__fastcall TNNVNumberEdit::TNNVNumberEdit(TComponent* Owner)
  : inherited( Owner )
  , FColorApply( false )
  , FSColor( clWindow )
  , FSFColor( clWindowText )
  , FIsUserCanChangeCheckStyle( true )
{
  NumberKind                = NNV::TNumberKind::Double;
  IsUserCanChangeCheckStyle = false;
  CheckStyle                = NNV::TCheckStyleValue::None;
  CheckStyleSetKind         = NNV::TCheckStyleSetKind::FullSet;
  NumberUnion.Double        = 0;
}

//__fastcall TNNVNumberEdit::~TNNVNumberEdit()
//{
//  NNVFormList.Delete( fmvDateTime, this );
//}

//---------------------------------------------------------------------------
namespace Vcl_nnnumberedit
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TNNVNumberEdit)};
        RegisterComponents( L"VCL New Navadvipa", classes, 0 );
    }
}
//---------------------------------------------------------------------------

void __fastcall TNNVNumberEdit::SetCheckStyle( NNV::TCheckStyleValue Value )
{
  if ( FCheckStyle != Value ) {
    FCheckStyle = Value;

    SyncEditMask();
  }
}

void __fastcall TNNVNumberEdit::SetCheckStyleSetKind( NNV::TCheckStyleSetKind Value )
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

//void __fastcall TNNVNumberEdit::DoPrepare( TObject* Sender )
//{
//  fmvDateTime->DateTime = DateTime == NNVConst::EmptyDateTime ? InitialDateTime() : DateTime;
//}
//
//void __fastcall TNNVNumberEdit::DoExecuteDialog( TObject* Sender )
//{
//  if ( !ReadOnly )
//    DateTime = fmvDateTime->DateTime;
//}

void __fastcall TNNVNumberEdit::KeyDown( Word &Key, Classes::TShiftState Shift )
{
  switch ( Key ) {
  case vkUp :
    if ( IsUserCanChangeCheckStyle && Shift == TShiftState() << ssAlt )
      NextCheckStyle();
    break;
  case vkReturn :
    TextToNumberUnion();
    break;
  default :
    inherited::KeyDown( Key, Shift );
  }
}

void __fastcall TNNVNumberEdit::NextCheckStyle()
{
  if ( VectorCheckStyleValue.empty() )
    return;

  ++FCurrentIteratorCheckStyle;
  if ( FCurrentIteratorCheckStyle == VectorCheckStyleValue.end() )
    FCurrentIteratorCheckStyle = VectorCheckStyleValue.begin();
  CheckStyle = (*FCurrentIteratorCheckStyle);
}

bool __fastcall TNNVNumberEdit::IsTextEmpty()
{
  String S = Text.Trim();
  return S.IsEmpty();
}

//void __fastcall TNNVNumberEdit::ButtonClick( TComponent *SenderForm )
//{
//  NNVFormList.New( __classid( TfmvDateTime ), &fmvDateTime, this );
//
//  fmvDateTime->BoundsRect         = NNV::CalcRect( CWRect, fmvDateTime->BoundsRect );
//  fmvDateTime->NeedTime           = NeedTime;
//
//  fmvDateTime->fbRes->OnPrepare   = DoPrepare;
//  fmvDateTime->fbRes->OnUnPrepare = NULL;
//  fmvDateTime->fbRes->OnExecute   = DoExecuteDialog;
//
//  fmvDateTime->ShowDialog( SenderForm );
//}

void __fastcall TNNVNumberEdit::SetNumberUnion( NNV::TNumberUnion Value )
{
  bool B;
  switch ( NumberKind ) {
  case NNV::TNumberKind::ShortInt :
    B = FNumberUnion.ShortInt != Value.ShortInt;
    break;
  case NNV::TNumberKind::Int :
    B = FNumberUnion.Int != Value.Int;
    break;
  case NNV::TNumberKind::LongLongInt :
    B = FNumberUnion.LongLongInt != Value.LongLongInt;
    break;
  case NNV::TNumberKind::Double :
    B = FNumberUnion.Double != Value.Double;
    break;
  }

  if ( B ) {
    FNumberUnion = Value;
    FIsEmpty     = false;

    DoExecute();
  }

  TextRefresh();
}

void __fastcall TNNVNumberEdit::TextRefresh()
{
  if ( IsEmpty )
    Text = "";
  else
    switch ( NumberKind ) {
    case NNV::TNumberKind::ShortInt :
      Text = IntToStr( NumberUnion.ShortInt );
      break;
    case NNV::TNumberKind::Int :
      Text = IntToStr( NumberUnion.Int );
      break;
    case NNV::TNumberKind::LongLongInt :
      Text = IntToStr( NumberUnion.LongLongInt );
      break;
    case NNV::TNumberKind::Double :
      Text = FloatToStr( NumberUnion.Double );
      break;
    }

  RestoreColor();
}

void __fastcall TNNVNumberEdit::RestoreColor()
{
  Color       = FSColor;
  Font->Color = FSFColor;

  FColorApply  = false;
}

void __fastcall TNNVNumberEdit::SetNumberKind( NNV::TNumberKind Value )
{
  if ( FNumberKind != Value ) {
    FNumberKind = Value;

    SyncEditMask();
  }
}

void __fastcall TNNVNumberEdit::SyncEditMask()
{
  String P = NNV::PrefixCheckStyleValue( CheckStyle );

  switch ( NumberKind ) {
  case NNV::TNumberKind::ShortInt :
    EditMask = P + NNVConst::EditMaskNumberKindShortInt;
    break;
  case NNV::TNumberKind::Int :
    EditMask = P + NNVConst::EditMaskNumberKindInt;
    break;

  case NNV::TNumberKind::LongLongInt :
    EditMask = P + NNVConst::EditMaskNumberKindLongLongInt;
    break;
  case NNV::TNumberKind::Double :
    EditMask = P + NNVConst::EditMaskNumberKindDouble;
    break;
  }

  TextRefresh();
}

void __fastcall TNNVNumberEdit::ClearNumberUnion()
{
  NNV::TNumberUnion N;
  switch ( NumberKind ) {
  case NNV::TNumberKind::ShortInt :
    N.ShortInt = 0;
    break;
  case NNV::TNumberKind::Int :
    N.Int = 0;
    break;
  case NNV::TNumberKind::LongLongInt :
    N.LongLongInt = 0;
    break;
  case NNV::TNumberKind::Double :
    N.Double = 0;
    break;
  }
  NumberUnion = N;
}

void __fastcall TNNVNumberEdit::SetIsEmpty( bool Value )
{
  FIsEmpty = Value;
  TextRefresh();
}

void __fastcall TNNVNumberEdit::TextToNumberUnion()
{
  if ( IsTextEmpty() )
    IsEmpty = true;
  else {
    String NS = NNV::RemoveChar( Text, L" " );
    NNV::TNumberUnion NU;
    switch ( NumberKind ) {
    case NNV::TNumberKind::ShortInt :
      NU.ShortInt = StrToInt( NS );
      break;
    case NNV::TNumberKind::Int :
      NU.Int = StrToInt( NS );
      break;
    case NNV::TNumberKind::LongLongInt :
      NU.LongLongInt = StrToInt64( NS );
      break;
    case NNV::TNumberKind::Double :
      NU.Double = NS.ToDouble();
      break;
    }
    NumberUnion = NU;
  }
}

void __fastcall TNNVNumberEdit::CMExit(TCMExit &Message)
{
  if ( IsMasked && ( !ComponentState.Contains( csDesigning ) ) ) {
    int Pos = SelStart;
    try {
      TextToNumberUnion();
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

void __fastcall TNNVNumberEdit::Change()
{
  inherited::Change();
  if ( !FColorApply &&
       !ComponentState.Contains( csLoading ) &&
       !ComponentState.Contains( csDesigning ) ) {

    FColorApply = true;

    FSColor     = Color;
    FSFColor    = Font->Color;

    Color       = NNVConst::FonColorValueChange;
    Font->Color = NNVConst::FontColorValueChange;
  }
}

void __fastcall TNNVNumberEdit::Loaded(void)
{
  inherited::Loaded();
  FSColor  = Color;
  FSFColor = Font->Color;
}

//void __fastcall TNNVNumberEdit::CreateWnd(void)
//{
//  inherited::CreateWnd();
//  //ButtonKind = bkCalendar;
//}

