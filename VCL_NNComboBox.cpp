// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNComboBox.h"
#include "VCL_NNCommon.h"

#pragma resource "*.res"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNNVComboBox *)
{
    new TNNVComboBox( NULL );
}
//---------------------------------------------------------------------------
__fastcall TNNVComboBox::TNNVComboBox(TComponent* Owner)
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------
namespace Vcl_nncombobox
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[ 1 ] = { __classid( TNNVComboBox ) };
        RegisterComponents( L"VCL New Navadvipa", classes, 0 );
    }
}
//---------------------------------------------------------------------------

void __fastcall TNNVComboBox::Notification(TComponent *AComponent, TOperation Operation)
{
  inherited::Notification( AComponent, Operation );
  if ( ( Operation == opRemove )  && ( AComponent == fDialog ) )
    fDialog = NULL;
}

void __fastcall TNNVComboBox::SetDialog( TNNVDialog *Value )
{
  if ( fDialog != Value ) {
    fDialog = Value;
    if ( Value )
      Value->FreeNotification( this );
  }
}

void __fastcall TNNVComboBox::ButtonClick( TComponent *SenderForm )
{
  if ( Dialog )
    Dialog->Execute( CWRect, SenderForm );
  else
    DoExecute();
}

void __fastcall TNNVComboBox::KeyDown(Word &Key,  TShiftState Shift)
{
  if ( Key == vkDown && Shift == ( TShiftState() << ssAlt ) ) {
    ButtonClick( NNV::GetParentForm( this ) );
    Key = 0;
  } else
    inherited::KeyDown( Key, Shift );
}

TRect __fastcall TNNVComboBox::GetCWRect()
{
  return Bounds( ClientOrigin.x, ClientOrigin.y, Width, Height );
}

void __fastcall TNNVComboBox::DoExecute()
{
  if ( fOnExecute )
    fOnExecute( this );
}

