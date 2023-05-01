//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "FMX_NNFmDB.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FMX_NNDBMiracle"
#pragma link "FMX_NNFlagBox"
#pragma link "FMX_NNFmRes"
#pragma link "FMX_NNLanguageManager"
#pragma link "FMX_NNRightsManager"
#pragma link "FMX_NNActionList"
#pragma resource "*.fmx"
TfmfDB *fmfDB;
//---------------------------------------------------------------------------
__fastcall TfmfDB::TfmfDB(TComponent* Owner)
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

void __fastcall TfmfDB::dsDataDataChange(TObject *Sender, TField *Field)
{
  TDataSet *ds = DataSet;
  if ( ds ) {
    edDBStatus->Text = NNF::DataSetStateToStr( dsData->State ) + NNFConst::Space +
                       String( ds->RecNo ) + NNFConst::AltDelimeter +
                       String( ds->RecordCount );
  }
}
//---------------------------------------------------------------------------

