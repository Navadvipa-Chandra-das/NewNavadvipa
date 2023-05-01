// ---------------------------------------------------------------------------

#pragma hdrstop

#include "VCL_NNDmRes.h"
#include "VCL_NNConst.h"
#include "VCL_NNStrUtil.h"
#include "VCL_NNDmNewNavadvipa.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "Vcl.Controls.TControl"
#pragma link "VCL_NNDBMiracle"
#pragma link "VCL_NNRightsManager"
#pragma link "VCL_NNLanguageManager"
#pragma link "VCL_NNDBMiracle"
#pragma resource "*.dfm"
TdmvRes *dmvRes;

// ---------------------------------------------------------------------------
__fastcall TdmvRes::TdmvRes( TComponent* Owner )
  : inherited( Owner )
{
}
// ---------------------------------------------------------------------------

void __fastcall TdmvRes::Loaded()
{
  inherited::Loaded();

  //OldCreateOrder     = false;
  if ( NNV::DMExists( __classid( TdmvNewNavadvipa ), &dmvNewNavadvipa ) ) {
    coData->Connection = dmvNewNavadvipa->conDB;
    rrData->Manager    = dmvNewNavadvipa->rmDB;
    lnData->Manager    = dmvNewNavadvipa->lmDB;
  }
  // Это нужно из-зп глюка Embarcadero! В Инспекторе Объектов не видна coResGetFiler!
  coData->OnGetFiler = coDataGetFiler;
}

void __fastcall TdmvRes::BoolGalkaGetText( TField *Sender, UnicodeString &Text, bool DisplayText )
{
  if ( Sender->AsBoolean )
    Text = NNVConst::S_Galka;
  else
    Text = NNVConst::S_GalkaEmpty;
}

// ---------------------------------------------------------------------------
void __fastcall TdmvRes::BoolPlusMinusGetText( TField *Sender, UnicodeString &Text, bool DisplayText )
{
  if ( Sender->AsBoolean )
    Text = L"+";
  else
    Text = L"-";
}
// ---------------------------------------------------------------------------

void __fastcall TdmvRes::DataModuleCreate( TObject *Sender )
{
  if ( Application->Terminated )
    return;
  // rrData->Manager = dmData->rmData;
  // coData->OracleSession = dmData->osData;
  coData->Load();
  rrData->Apply();
  lnData->Apply();

  // if ( this != dmData ) {
  // NNV::TEnterpriseManager::const_iterator ie = dmData->EnterpriseManager->FindEnterprise( dmData->EnterpriseManager->EnterpriseDefault );
  // dmData->DataModuleLocaleFormat( this, ie );
  // }
  // Устанавливаем всем полям даты и даты-времени (TimeStamp) EditMask
  NNV::DataModuleLocaleFormat( this );
}
// ---------------------------------------------------------------------------

void __fastcall TdmvRes::DataModuleDestroy( TObject *Sender )
{
  coData->Save();
}
// ---------------------------------------------------------------------------

void __fastcall TdmvRes::NationalNumdecGetText( TField *Sender, UnicodeString &Text
                                              , bool DisplayText )
{
  if ( DisplayText )
    Text = NNV::FloatFormat( Sender->AsFloat, NNVConst::NationalNumdec );
  else
    Text = Sender->AsString;
}
// ---------------------------------------------------------------------------

void __fastcall TdmvRes::ClearDateSetText( TField *Sender, const UnicodeString Text )
{
  NNV::ClearDateSetText( Sender, Text );
}
// ---------------------------------------------------------------------------

void __fastcall TdmvRes::coDataGetFiler( TObject *Sender, TNNVTextStream *&Filer )
{
  Filer = dmvNewNavadvipa->MapFiler.Filer[ coData->RegistryKey() ];
}
//---------------------------------------------------------------------------

void __fastcall TdmvRes::MemoStringGetText( TField *Sender, UnicodeString &Text, bool DisplayText )
{
  Text = Sender->AsString;
}
//---------------------------------------------------------------------------

