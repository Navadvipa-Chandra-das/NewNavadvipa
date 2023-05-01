// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNDBToolButton.h"
#pragma resource "*.res"
#pragma package(smart_init)
// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNNVDBToolButton *) {
  new TNNVDBToolButton(NULL);
}

// ---------------------------------------------------------------------------
__fastcall TNNVDBToolButton::TNNVDBToolButton(TComponent* Owner)
  : inherited( Owner )
  , fWork( false )
  , fCheckImageIndex( -1 )
  , fUnCheckImageIndex( -1 )
  , fAllowDown( true )
  , fAllowUp(true)
{
  Style                   = tbsCheck;
  FDataLink               = new TFieldDataLink();
  FDataLink->Control      = this;
  FDataLink->OnDataChange = DataChange;
}

// ---------------------------------------------------------------------------
namespace Vcl_nndbtoolbutton {
  void __fastcall PACKAGE Register() {
    TComponentClass classes[1] = {__classid(TNNVDBToolButton)};
    RegisterComponents(L"VCL New Navadvipa", classes, 0);
  }
}
// ---------------------------------------------------------------------------

void __fastcall TNNVDBToolButton::Notification( TComponent* AComponent
                                              , TOperation Operation )
{
  inherited::Notification( AComponent, Operation );
  if ( Operation == opRemove && FDataLink && AComponent == DataSource )
    DataSource = NULL;
}

TDataSource* __fastcall TNNVDBToolButton::GetDataSource()
{
  if ( FDataLink )
    return FDataLink->DataSource;
  else
    return nullptr;
}

void __fastcall TNNVDBToolButton::SetDataSource( TDataSource* Value )
{
  if ( !( FDataLink->DataSourceFixed && ( ComponentState.Contains( csLoading ) ) ) )
    FDataLink->DataSource = Value;
  if ( Value )
    Value->FreeNotification( this );
}

void __fastcall TNNVDBToolButton::DataChange( TObject *Sender )
{
  if ( FDataLink->Field && !fWork ) {
    if ( FDataLink->Field->Value == 1 ) {
      Down = true;
      ImageIndex = CheckImageIndex;
    } else {
      Down = false;
      ImageIndex = UnCheckImageIndex;
    }
  }
}

void __fastcall TNNVDBToolButton::Click()
{
  if (FDataLink->Field->ReadOnly) {
    Down = FDataLink->Field->AsBoolean == true;
    Abort();
  } else {
    fWork = true;
    try {
      FDataLink->Edit();
      if ( Down ) {
        if ( AllowDown )
          FDataLink->Field->Value = 1;
      } else {
        if ( AllowUp )
          FDataLink->Field->Value = 0;
      }
      FDataLink->Modified();
    } __finally {
      fWork = false;
    }
  }
  if ( Parent && Parent->CanFocus() )
    Parent->SetFocus();
  inherited::Click();
}

void __fastcall TNNVDBToolButton::SetDataField(const String Value)
{
  FDataLink->FieldName = Value;
}

void __fastcall TNNVDBToolButton::Loaded(void)
{
  inherited::Loaded();
  CheckImageIndex = ImageIndex;
  if ( UnCheckImageIndex == -1 )
    UnCheckImageIndex = ImageIndex;
}

bool __fastcall TNNVDBToolButton::StoreUnCheckImageIndex()
{
  if ( UnCheckImageIndex == -1 || UnCheckImageIndex == CheckImageIndex )
    return false;
  else
    return true;
}
