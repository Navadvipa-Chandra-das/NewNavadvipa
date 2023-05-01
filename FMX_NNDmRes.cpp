//---------------------------------------------------------------------------

#pragma hdrstop

#include "FMX_NNDmRes.h"
#include "FMX_NNDmNewNavadvipa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "FMX.Controls.TControl"
#pragma link "FMX_NNDBMiracle"
#pragma link "FMX_NNLanguageManager"
#pragma link "FMX_NNRightsManager"
#pragma resource "*.dfm"
TdmfRes *dmfRes;
//---------------------------------------------------------------------------
__fastcall TdmfRes::TdmfRes(TComponent* Owner)
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

void __fastcall TdmfRes::DataModuleCreate(TObject *Sender)
{
  if ( Application->Terminated )
    return;
  // rrData->Manager = dmData->rmData;
  // coData->OracleSession = dmData->osData;
  coData->Load();
  rrData->Apply();
  lnData->Apply();

  // if ( this != dmData ) {
  // NNF::TEnterpriseManager::const_iterator ie = dmData->EnterpriseManager->FindEnterprise( dmData->EnterpriseManager->EnterpriseDefault );
  // dmData->DataModuleLocaleFormat( this, ie );
  // }
  // Устанавливаем всем полям даты и даты-времени (TimeStamp) EditMask
  NNF::DataModuleLocaleFormat( this );
}
//---------------------------------------------------------------------------

void __fastcall TdmfRes::DataModuleDestroy(TObject *Sender)
{
  coData->Save();
}
//---------------------------------------------------------------------------

void __fastcall TdmfRes::Loaded()
{
  inherited::Loaded();

  // OldCreateOrder     = false;
  if ( NNF::DMExists( __classid( TdmfNewNavadvipa ), &dmfNewNavadvipa ) ) {
    coData->Connection = dmfNewNavadvipa->conDB;
    rrData->Manager    = dmfNewNavadvipa->rmDB;
    lnData->Manager    = dmfNewNavadvipa->lmDB;
  }
  // Это нужно из-зп глюка Embarcadero! В Инспекторе Объектов не видна coResGetFiler!
  coData->OnGetFiler = coDataGetFiler;
}

void __fastcall TdmfRes::BoolGalkaGetText( TField *Sender, UnicodeString &Text, bool DisplayText )
{
  if ( Sender->AsBoolean )
    Text = NNFConst::S_Galka;
  else
    Text = NNFConst::S_GalkaEmpty;
}
// ---------------------------------------------------------------------------

void __fastcall TdmfRes::BoolPlusMinusGetText( TField *Sender, UnicodeString &Text, bool DisplayText )
{
  if ( Sender->AsBoolean )
    Text = L"+";
  else
    Text = L"-";
}
// ---------------------------------------------------------------------------

void __fastcall TdmfRes::NationalNumdecGetText( TField *Sender, UnicodeString &Text
                                              , bool DisplayText )
{
  if ( DisplayText )
    Text = NNF::FloatFormat( Sender->AsFloat, NNFConst::NationalNumdec );
  else
    Text = Sender->AsString;
}
// ---------------------------------------------------------------------------

void __fastcall TdmfRes::ClearDateSetText( TField *Sender, const UnicodeString Text )
{
  NNF::ClearDateSetText( Sender, Text );
}
// ---------------------------------------------------------------------------

void __fastcall TdmfRes::coDataGetFiler( TObject *Sender, TNNFTextStream *&Filer )
{
  Filer = dmfNewNavadvipa->MapFiler.Filer[ coData->RegistryKey() ];
}
//---------------------------------------------------------------------------

void __fastcall TdmfRes::MemoStringGetText( TField *Sender, UnicodeString &Text, bool DisplayText )
{
  Text = Sender->AsString;
}
//---------------------------------------------------------------------------

