//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop

#include "VCL_NNDateTimeDialog.h"
#include "VCL_NNFmDateTime.h"
#include "VCL_NNConst.h"
#include "VCL_NNFormAdmin.h"

#pragma link "VCL_NNDialogExec"
#pragma resource "*.res"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck( TNNVDateTimeDialog * )
{
  new TNNVDateTimeDialog( NULL );
}
//---------------------------------------------------------------------------

__fastcall TNNVDateTimeDialog::TNNVDateTimeDialog( TComponent* Owner )
  : inherited( Owner )
  , FNeedTime( false )
{
  DateTime = NeedTime ? Now() : Date();
}
//---------------------------------------------------------------------------

__fastcall TNNVDateTimeDialog::~TNNVDateTimeDialog()
{
  NNVFormList.Delete( fmvDateTime, this );
}

namespace Vcl_nndatetimedialog
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[ 1 ] = { __classid( TNNVDateTimeDialog ) };
     RegisterComponents( L"VCL New Navadvipa", classes, 0 );
  }
}
//---------------------------------------------------------------------------

void __fastcall TNNVDateTimeDialog::DoGetDialogForm( TCustomForm *&fm )
{
  NNVFormList.New( __classid( TfmvDateTime ), &fmvDateTime, this );
  fmvDateTime->NeedTime = NeedTime;
  fm = fmvDateTime;
}

void __fastcall TNNVDateTimeDialog::DoPrepare( TObject *Sender )
{
  inherited::DoPrepare( Sender );
  fmvDateTime->DateTime = DateTime;
}

void __fastcall TNNVDateTimeDialog::DoExecute( TObject *Sender )
{
  DateTime = fmvDateTime->DateTime;
  inherited::DoExecute( Sender );
}

void __fastcall TNNVDateTimeDialog::SetNeedTime( bool Value )
{
  if ( FNeedTime != Value ) {
    FNeedTime = Value;
    if ( !Value )
      DateTime = NNV::TruncDate( DateTime );
  }
}

void __fastcall TNNVDateTimeDialog::SetDateTime( TDateTime Value )
{
  if ( FDateTime != Value ) {
    if ( NeedTime )
      FDateTime = Value;
    else
      FDateTime = NNV::TruncDate( Value );
  }
}

