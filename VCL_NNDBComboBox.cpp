// Wanderer library - author Oleg Zolotyh e-mail alejan@rambler.ru
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNDBComboBox.h"
#include "Vcl.DBCtrls.hpp"
#include "VCL_NNDBMiracle.h"

#pragma resource "*.res"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck( TNNVDBComboBox * )
{
    new TNNVDBComboBox( NULL );
}
//---------------------------------------------------------------------------

__fastcall TNNVDBComboBox::TNNVDBComboBox( TComponent* Owner )
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

namespace Vcl_nndbcombobox
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[ 1 ] = { __classid( TNNVDBComboBox ) };
        RegisterComponents( L"VCL New Navadvipa", classes, 0 );
    }
}
//---------------------------------------------------------------------------

void __fastcall TNNVDBComboBox::Notification( TComponent *AComponent, TOperation Operation )
{
  inherited::Notification( AComponent, Operation );
  if ( ( Operation == opRemove )  && ( AComponent == fDialog ) )
    fDialog = nullptr;
}

void __fastcall TNNVDBComboBox::SetDialog( TNNVDialog *Value )
{
  if ( fDialog != Value ) {
    fDialog = Value;
    if ( Value )
      Value->FreeNotification( this );
  }
}

void __fastcall TNNVDBComboBox::ButtonClick( TComponent *SenderForm )
{
  if ( Dialog )
    Dialog->Execute( CWRect, SenderForm );
  else
    DoExecute();
}

void __fastcall TNNVDBComboBox::KeyDown( Word &Key,  TShiftState Shift )
{
  if ( Key == vkDown && Shift == ( TShiftState() << ssAlt ) ) {
    ButtonClick( NNV::GetParentForm( this ) );
    Key = 0;
  } else
    inherited::KeyDown( Key, Shift );
}

TRect __fastcall TNNVDBComboBox::GetCWRect()
{
  return Bounds( ClientOrigin.x, ClientOrigin.y, Width, Height );
}

void __fastcall TNNVDBComboBox::DoExecute()
{
  if ( fOnExecute )
    fOnExecute( this );
}

void __fastcall TNNVDBComboBox::CMEnter( TCMEnter &Message )
{
  if ( DataSource && DataSource->DataSet && IsFiltered ) {
    TNNVQuery *qu = dynamic_cast< TNNVQuery* >( DataSource->DataSet );
    if ( qu )
      qu->FieldSearchName = DataField;
  }
  inherited::Dispatch( &Message );
}

