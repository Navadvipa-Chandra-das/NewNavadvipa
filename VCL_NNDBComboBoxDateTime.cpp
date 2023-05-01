// Wanderer library - author Oleg Zolotyh e-mail alejan@rambler.ru
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNDBComboBoxDateTime.h"
#include "VCL_NNCommon.h"

#pragma resource "*.res"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck( TNNVDBComboBoxDateTime * )
{
    new TNNVDBComboBoxDateTime( NULL );
}
//---------------------------------------------------------------------------

__fastcall TNNVDBComboBoxDateTime::TNNVDBComboBoxDateTime( TComponent* Owner )
  : inherited( Owner )
, fWork( false )
, fWorkUpdateData( false )
{
  FDataLink = new TFieldDataLink();
  FDataLink->Control = this;
  FDataLink->OnDataChange = DataChange;
}

__fastcall TNNVDBComboBoxDateTime::~TNNVDBComboBoxDateTime()
{
  delete FDataLink;
  FDataLink = nullptr;
}

//---------------------------------------------------------------------------
namespace Vcl_nndbcomboboxdatetime
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[ 1 ] = { __classid( TNNVDBComboBoxDateTime ) };
        RegisterComponents( L"VCL New Navadvipa", classes, 0 );
    }
}
//---------------------------------------------------------------------------

TDataSource* __fastcall TNNVDBComboBoxDateTime::GetDataSource()
{
  if ( FDataLink )
    return FDataLink->DataSource;
  else
    return nullptr;
}

void __fastcall TNNVDBComboBoxDateTime::SetDataSource( TDataSource* Value )
{
  if ( !( FDataLink->DataSourceFixed && ( ComponentState.Contains( csLoading ) ) ) )
    FDataLink->DataSource = Value;
  if ( Value )
    Value->FreeNotification( this );
}

String __fastcall TNNVDBComboBoxDateTime::GetDataField()
{
  if ( FDataLink )
    return FDataLink->FieldName;
  else
    return "";
};

bool __fastcall TNNVDBComboBoxDateTime::GetReadOnly()
{
  if ( FDataLink )
    return FDataLink->ReadOnly;
  else
    return true;
};

void __fastcall TNNVDBComboBoxDateTime::SetReadOnly( bool Value )
{
  if ( FDataLink )
    FDataLink->ReadOnly = Value;
}

TField* __fastcall TNNVDBComboBoxDateTime::GetField()
{
  if ( FDataLink )
    return FDataLink->Field;
  else
    return nullptr;
};

void __fastcall TNNVDBComboBoxDateTime::SetDataField( const String Value )
{
  FDataLink->FieldName = Value;
}

void __fastcall TNNVDBComboBoxDateTime::Notification( TComponent* AComponent
                                                    , TOperation Operation )
{
  inherited::Notification( AComponent, Operation );
  if ( Operation == opRemove && FDataLink && AComponent == DataSource )
    DataSource = NULL;
}

void __fastcall TNNVDBComboBoxDateTime::ForUpdateData( TObject *Sender )
{
  if ( fWork )
    return;
  if ( FDataLink && FDataLink->Field ) {
    fWorkUpdateData = true;
    FDataLink->Edit();
    FDataLink->Field->AsDateTime = DateTime;
    fWorkUpdateData = false;
  }
}
void __fastcall TNNVDBComboBoxDateTime::DataChange( TObject *Sender )
{
  if ( fWorkUpdateData )
    return;
  if ( FDataLink->Field ) {
    fWork = true;
    DateTime = FDataLink->Field->AsDateTime;
    fWork = false;
  }
}

void __fastcall TNNVDBComboBoxDateTime::DoExecute()
{
  inherited::DoExecute();
  ForUpdateData( this );
}

void __fastcall TNNVDBComboBoxDateTime::SetIsEmpty( bool Value )
{
  inherited::SetIsEmpty( Value );
  if ( FDataLink->Field && !FDataLink->Field->IsNull ) {
    FDataLink->Edit();
    FDataLink->Field->Clear();
  }
}

bool __fastcall TNNVDBComboBoxDateTime::IsNull()
{
  TField *F = Field;
  if ( F )
    return F->IsNull;
  else
    return true;
}

