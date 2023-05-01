//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFmRowInspector.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNActionList"
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNFlagBox"
#pragma link "VCL_NNFmRes"
#pragma link "VCL_NNRightsManager"
#pragma link "VCL_NNPanel"
#pragma link "VCL_NNLanguageManager"
#pragma resource "*.dfm"
TfmvRowInspector *fmvRowInspector;
//---------------------------------------------------------------------------
__fastcall TfmvRowInspector::TfmvRowInspector(TComponent* Owner)
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

void __fastcall TfmvRowInspector::buOKClick(TObject *Sender)
{
  CloseDialog( true );
}
//---------------------------------------------------------------------------

void __fastcall TfmvRowInspector::buClearClick(TObject *Sender)
{
  CloseDialog( false );
}
//---------------------------------------------------------------------------

void __fastcall TfmvRowInspector::SimpleKeyDownDialog( TObject *Sender, WORD &Key, TShiftState Shift )
{
  if ( Key == 0 )
    return;

  TNNVQuery *qu = Query;
  if ( qu ) {
    switch ( Key ) {
    case vkEscape :
      if ( qu->IsEditModes() ) {
        qu->Cancel();
        Key = 0;
      }
      break;
    case vkReturn :
      if ( qu->IsEditModes() ) {
        qu->Post();
        Key = 0;
      }
      break;
    }
  }

  if ( Key )
    inherited::SimpleKeyDownDialog( Sender, Key, Shift );
}
//---------------------------------------------------------------------------

TNNVQuery* __fastcall TfmvRowInspector::GetQuery()
{
  if ( dnRowInspector->DataSource )
    return dynamic_cast< TNNVQuery* >( dnRowInspector->DataSource->DataSet );
  else
    return nullptr;
}

