//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFmFormList.h"
#include <memory>
#include "VCL_NNDmNewNavadvipa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCL_NNActionList"
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNFlagBox"
#pragma link "VCL_NNRightsManager"
#pragma link "VCL_NNLanguageManager"
#pragma resource "*.dfm"
TfmvFormList *fmvFormList;
//---------------------------------------------------------------------------
__fastcall TfmvFormList::TfmvFormList( TComponent* Owner )
  : inherited( Owner )
, fClick( false )
{
}
//---------------------------------------------------------------------------

void __fastcall TfmvFormList::lbFormDblClick(TObject *Sender)
{
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------

TCustomForm* TfmvFormList::GetForm()
{
  TCustomForm *Result = nullptr;
  ShowModal();
  if ( ( ModalResult == mrOk ) && ( lbForm->ItemIndex != -1 ) )
    Result = dynamic_cast< TCustomForm* >( lbForm->Items->Objects[ lbForm->ItemIndex ] );
  return Result;
}

void __fastcall TfmvFormList::FormShow(TObject *Sender)
{
  TCustomForm *fActive = Screen->ActiveForm;
  TfmvRes *f;
  int i;
  fClick = false;
  std::unique_ptr< TStringList > sl( new TStringList );
  bool B;
  for ( i = 0; i < Screen->FormCount; i++ ) {
    f = dynamic_cast< TfmvRes* >( Screen->Forms[ i ] );
    B = f && ( ( !f->DialogMode ) && ( f->fbRes->ShowInWindowList ) );
    if ( Screen->Forms[ i ] != this && ( Screen->Forms[ i ]->Visible && B ) )
      sl->AddObject( Screen->Forms[ i ]->Caption, Screen->Forms[ i ] );
  }
  sl->Sort();
  lbForm->Items->Assign( sl.get() );
  for ( i = 0; i < lbForm->Items->Count; i++ )
    if ( fActive == lbForm->Items->Objects[ i ] ) {
      lbForm->ItemIndex = i;
      break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfmvFormList::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  switch ( Key  ) {
  case vkF10 :
    fClick = false;
    Key = 0;
    break;
  case vkF11 :
    if ( lbForm->ItemIndex == 0 ) lbForm->ItemIndex = lbForm->Items->Count - 1;
    else lbForm->ItemIndex = lbForm->ItemIndex - 1;
    fClick = true;
    Key = 0;
    break;
  case vkF12 :
    if ( lbForm->ItemIndex == lbForm->Items->Count - 1 ) lbForm->ItemIndex = 0;
    else lbForm->ItemIndex = lbForm->ItemIndex + 1;
    fClick = true;
    Key = 0;
    break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmvFormList::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  switch ( Key  ) {
    case vkShift :
      if ( fClick ) {
        ModalResult = mrOk;
        Key = 0;
      }
      break;
  }
}
//---------------------------------------------------------------------------

