//---------------------------------------------------------------------------
#include <fmx.h>

#pragma hdrstop

#include <memory>
#include <algorithm>
#include <memory>
#include <FMX.DialogService.hpp>
#include "FMX_NNFmPrabhupadaSlovar.h"
#include "FMX_NNDmPrabhupadaSlovar.h"
#include <System.RegularExpressions.hpp>
#include "FMX_NNFmAboutPrabhupadaSlovar.h"
#include "FMX_NNConst.h"
#include "FMX_NNDmNewNavadvipa.h"
#include "FMX_NNFmLanguage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FMX_NNDBMiracle"
#pragma link "FMX_NNFlagBox"
#pragma link "FMX_NNLanguageManager"
#pragma link "FMX_NNRightsManager"
#pragma link "FMX_NNActionList"
#pragma resource "*.fmx"

TfmfPrabhupadaSlovar *fmfPrabhupadaSlovar;
//---------------------------------------------------------------------------

__fastcall TfmfPrabhupadaSlovar::TfmfPrabhupadaSlovar( TComponent* Owner )
  : inherited( Owner )
{
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::Loaded()
{
  inherited::Loaded();

  coRes->PrefixRegistryKey = NNFConst::PrabhupadaSlovarFiles;

  sbSearch->Text           = L"";
  sbDelete->Text           = L"";
  sbInsert->Text           = L"";
  sbRemoveDuplicates->Text = L"";
  sbAbout->Text            = L"";
}

void __fastcall TfmfPrabhupadaSlovar::FormCreate( TObject *Sender )
{
  dmfNewNavadvipa = new TdmfNewNavadvipa( this, dmfPrabhupadaSlovar->DoLogin );

  if ( Application->Terminated )
    return;

  NNF::TMapQuery AMapQuery( this );
  AMapQuery.PrepareStandartMacros();

  PreparePrabhupadaBukvary();
  PrepareYazykAndMaxID();

  OrderBy       = NNF::TOrderBy::SanskritVozrastanie;
  YazykIndex    = NNF::RussianIndex;
  CaseSensitive = false;

  PrepareLanguages();

  inherited::FormCreate( Sender );

  SetFilterStart = true;
  FilterSlovar   = FilterSlovar;

}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::PrepareLanguages()
{
  dmfNewNavadvipa->lmDB->PrepareStrings( cbLanguage->Items );
  dmfNewNavadvipa->lmDB->MainLanguageID = NNFConst::MainLanguageID;
  cbLanguage->ItemIndex = dmfNewNavadvipa->lmDB->LanguageIDToItemIndex( dmfNewNavadvipa->lmDB->CurrentLanguageID );
  NNFConst::MainLanguageIndex = dmfNewNavadvipa->lmDB->LanguageIDToItemIndex( dmfNewNavadvipa->lmDB->CurrentLanguageID );
}

void __fastcall TfmfPrabhupadaSlovar::grPrabhupadaSlovarGetValue(TObject *Sender,
          const int ACol, const int ARow, TValue &Value)
{
  TColumn *CL = grPrabhupadaSlovar->Columns[ ACol ];
  if ( FilterSlovar.IsEmpty ) {
    if ( CL->Tag == 0 )
      Value = PrabhupadaSlovarVector[ ARow ]->Sanskrit;
    else
      Value = PrabhupadaSlovarVector[ ARow ]->Perevod;
  } else {
    if ( CL->Tag == 0 )
      Value = PrabhupadaSlovarVector[ PrabhupadaSlovarVector[ ARow ]->SearchIndex ]->Sanskrit;
    else
      Value = PrabhupadaSlovarVector[ PrabhupadaSlovarVector[ ARow ]->SearchIndex ]->Perevod;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::grPrabhupadaSlovarSetValue( TObject *Sender,
          const int ACol, const int ARow, const TValue &Value )
{
  TColumn *CL = grPrabhupadaSlovar->Columns[ ACol ];
  NNF::TSanskritPerevod *SP = PrabhupadaSlovarVector[ ARow ];

  TValue V = Value;
  String SSanskrit = SP->Sanskrit, SPerevod = SP->Perevod;

  if ( CL->Tag == 0 )
    SP->Sanskrit = V.AsString();
  else
    SP->Perevod = V.AsString();

  if ( SSanskrit != SP->Sanskrit || SPerevod != SP->Perevod ) {
    TFDParam *p = quUpdateSanskrit->FindParam( "IZNACHALYNO" );
    p->Value = SP->Sanskrit;
    p = quUpdateSanskrit->FindParam( "PEREVOD" );
    p->Value = SP->Perevod;
    p = quUpdateSanskrit->FindParam( "ID" );
    p->Value = SP->ID;

    quUpdateSanskrit->ExecSQL();
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aSearchExecute(TObject *Sender)
{
  FilterSlovar = NNF::TFilterSlovar( edSanskrit->Text, edPerevod->Text );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::PrepareYazykAndMaxID()
{
  quYazyk->Active = true;
  NNF::TYazykInfo YI;
  String ALang;
  while ( !quYazyk->Eof ) {
    YI.ID         = quYazykID->AsInteger;
    YI.Yazyk      = quYazykYAZYK->AsString;
    YI.YazykSlovo = quYazykYAZYK_SLOVO->AsString;
    ALang         = YI.Yazyk.SubString( 1, 2 );
    YI.Lang       = ALang;

    YazykVector.push_back( YI );

    cbYazyk->Items->Add( YI.YazykSlovo );
    //cbLang->Items->Add( YI.YazykSlovo );
    quYazyk->Next();
  }
  quYazyk->Active = false;

  quMaxID->Active = true;
  MaxID = quMaxID->Fields->Fields[ 0 ]->AsInteger;
  quMaxID->Active = false;
}

void __fastcall TfmfPrabhupadaSlovar::coResLoad( TObject *Sender )
{
  inherited::coResLoad( Sender );
  dmfNewNavadvipa->lmDB->CurrentLanguageID = coRes->Filer->ReadLongLongInt();
  edSanskrit->Width = coRes->Filer->ReadInt();
  scSanskrit->Width = coRes->Filer->ReadInt();
  skPerevod->Width = coRes->Filer->ReadInt();
  sbFontSize->Value = coRes->Filer->ReadInt();
  CaseSensitive = coRes->Filer->ReadBool();
  OrderBy = (NNF::TOrderBy)coRes->Filer->ReadInt();
  YazykVector.LoadFromFiler( coRes->Filer );
  YazykIndex = coRes->Filer->ReadInt();
  scSanskrit->Index = coRes->Filer->ReadInt();
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::coResSave( TObject *Sender )
{
  inherited::coResSave( Sender );
  coRes->Filer->WriteLongLongInt( dmfNewNavadvipa->lmDB->CurrentLanguageID );
  coRes->Filer->WriteInt( edSanskrit->Width );
  coRes->Filer->WriteInt( scSanskrit->Width );
  coRes->Filer->WriteInt( skPerevod->Width );
  coRes->Filer->WriteInt( sbFontSize->Value );
  coRes->Filer->WriteBool( CaseSensitive );
  coRes->Filer->WriteInt( (int)OrderBy );
  YazykVector.SaveToFiler( coRes->Filer );
  coRes->Filer->WriteInt( YazykIndex );
  coRes->Filer->WriteInt( scSanskrit->Index );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::coResEndLoad( TObject *Sender )
{
  // Данный прием обязательный в случае многих параллельных TSplitter. Когда он один, этого можно и не делать
  // Бывает, что после восстановления сохранённых размеров TControl-ов на форме, TSplitter совсем не туда, где ему положено быть и пользователь теряет возможность управлять программой!
  splSanskritPerevod->Position->X = edSanskrit->Position->X + edSanskrit->Size->Width + 1;
  // Этот хитрый прием необходим, так как замечена "заморозка" TSplitter!
  // Примечательно, что в VCL версии TSplitter не нуждается в таких выкрутасах!
  edSanskrit->Width = edSanskrit->Width + 1;
  edSanskrit->Width = edSanskrit->Width - 1;
  sbFontSizeChange( sbFontSize );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::sbFontSizeChange( TObject *Sender )
{
  int FS = sbFontSize->Value;

  grPrabhupadaSlovar->TextSettings->Font->Size = FS;
  edSanskrit->Font->Size                       = FS;
  edPerevod->Font->Size                        = FS;
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::cbYazykChange(TObject *Sender)
{
  YazykIndex = cbYazyk->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::SetYazykIndex( int Value )
{
  if ( FYazykIndex != Value ) {
    FYazykIndex = Value;

    ++UpdateRowCount;

    NeedSort = true;
    cbYazyk->ItemIndex = YazykIndex;

    TFDParam *P = quPrabhupadaSlovar->ParamByName( "YAZYK" );
    P->Value = YazykVector[ YazykIndex ].Yazyk;
    PreparePrabhupadaSlovar();

    --UpdateRowCount;

    FilterSlovar.IsReset = true;
    FilterSlovar = FilterSlovar;
  }
}

void __fastcall TfmfPrabhupadaSlovar::PreparePrabhupadaSlovar()
{
  quPrabhupadaSlovar->Active = true;
  int RC = quPrabhupadaSlovar->RecordCount;
  PrabhupadaSlovarVector.clear();
  PrabhupadaSlovarVector.reserve( RC );

  NNF::TSanskritPerevod *SP;
  while ( !quPrabhupadaSlovar->Eof ) {
    SP = new NNF::TSanskritPerevod();

    SP->ID       = quPrabhupadaSlovarID->AsInteger;
    SP->Sanskrit = quPrabhupadaSlovarIZNACHALYNO->AsString;
    SP->Perevod  = quPrabhupadaSlovarPEREVOD->AsString;
    // Внимание оптимизация! Здесь сделали напрямую присваивание WithoutDiakritik полям,
    // а не через свяйства Sanskrit и Perevod, чтобы в цикле не вызявалась фунция!
    SP->SanskritWithoutDiakritik = NNF::RemoveDiacritics( SP->Sanskrit );
    SP->PerevodWithoutDiakritik  = NNF::RemoveDiacritics( SP->Perevod );

    PrabhupadaSlovarVector.push_back( SP );

    quPrabhupadaSlovar->Next();
  }

  quPrabhupadaSlovar->Active = false;
  SortPrabhupadaSlovar();
  RefreshPrabhupadaSlovar( 0, PrabhupadaSlovarVector.size() );
}

void __fastcall TfmfPrabhupadaSlovar::grPrabhupadaSlovarSelChanged( TObject *Sender )
{
  if ( !Application->Terminated ) {
    int R = grPrabhupadaSlovar->Row, RC = grPrabhupadaSlovar->RowCount;

    if ( UpdateRowCount == 0 && R != -1 )
      YazykVector[ YazykIndex ].CurrentRow = R;

    if ( RC > 0 )
      ++R;

    edInfo->Text = IntToStr( R ) + L" / " + IntToStr( RC );
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::grPrabhupadaSlovarHeaderClick( TColumn *Column )
{
  if ( Column == scSanskrit ) {
    if ( OrderBy != NNF::TOrderBy::SanskritVozrastanie )
      OrderBy = NNF::TOrderBy::SanskritVozrastanie;
    else
      OrderBy = NNF::TOrderBy::SanskritUbyvanie;
  } else {
    if ( OrderBy != NNF::TOrderBy::PerevodVozrastanie )
      OrderBy = NNF::TOrderBy::PerevodVozrastanie;
    else
      OrderBy = NNF::TOrderBy::PerevodUbyvanie;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::SetOrderBy( NNF::TOrderBy Value )
{
  if ( FOrderBy != Value ) {
    FOrderBy = Value;

    NeedSort = true;
    cbOrderBy->ItemIndex = (int)Value;
    SortPrabhupadaSlovar();
    RefreshPrabhupadaSlovar( 0, grPrabhupadaSlovar->RowCount );
  }
}

void __fastcall TfmfPrabhupadaSlovar::SortPrabhupadaSlovar()
{
  if ( PrabhupadaSlovarVector.size() == 0 )
    return;

  switch ( OrderBy ) {
  case NNF::TOrderBy::SanskritVozrastanie :
    if ( NeedSort ) {
      std::sort( PrabhupadaSlovarVector.begin()
               , PrabhupadaSlovarVector.end()
               , [] ( const NNF::TSanskritPerevod *A, const NNF::TSanskritPerevod *B )
                 {
                   return A->Sanskrit == B->Sanskrit ?
                          NNF::PrabhupadaComareLess( A->Perevod,  B->Perevod  ) :
                          NNF::PrabhupadaComareLess( A->Sanskrit, B->Sanskrit );
                 }
               );
      NeedSort = false;
    }
    break;
  case NNF::TOrderBy::SanskritUbyvanie :
    if ( NeedSort ) {
      std::sort( PrabhupadaSlovarVector.begin()
               , PrabhupadaSlovarVector.end()
               , [] ( const NNF::TSanskritPerevod *A, const NNF::TSanskritPerevod *B )
                 {
                   return A->Sanskrit == B->Sanskrit ?
                          NNF::PrabhupadaComareMore( A->Perevod,  B->Perevod  ) :
                          NNF::PrabhupadaComareMore( A->Sanskrit, B->Sanskrit );
                 }
               );
      NeedSort = false;
    }
    break;
  case NNF::TOrderBy::PerevodVozrastanie :
    if ( NeedSort ) {
      std::sort( PrabhupadaSlovarVector.begin()
               , PrabhupadaSlovarVector.end()
               , [] ( const NNF::TSanskritPerevod *A, const NNF::TSanskritPerevod *B )
                 {
                   return A->Perevod == B->Perevod ?
                          NNF::PrabhupadaComareLess( A->Sanskrit, B->Sanskrit ) :
                          NNF::PrabhupadaComareLess( A->Perevod,  B->Perevod  );
                 }
               );
      NeedSort = false;
    }
  case NNF::TOrderBy::PerevodUbyvanie :
    if ( NeedSort ) {
      std::sort( PrabhupadaSlovarVector.begin()
               , PrabhupadaSlovarVector.end()
               , [] ( const NNF::TSanskritPerevod *A, const NNF::TSanskritPerevod *B )
                 {
                   return A->Perevod == B->Perevod ?
                          NNF::PrabhupadaComareMore( A->Sanskrit, B->Sanskrit ) :
                          NNF::PrabhupadaComareMore( A->Perevod,  B->Perevod  );
                 }
               );
      NeedSort = false;
    }
    break;
  }
}

void __fastcall TfmfPrabhupadaSlovar::PreparePrabhupadaBukvary()
{
  NNF::TPrabhupadaBukva B;

  std::unique_ptr< TFileStream > FS( new TFileStream( NNFConst::PrabhupadaSlovarFiles + L"PrabhupadaBukvary.txt", fmOpenRead ) );
  std::unique_ptr< TNNFTextStream > TS( new TNNFTextStream( FS.get() ) );
  int V = 0;
  String S;
  while ( TS->ReadStringLine( S ) ) {
    B.Bukva = S[ 3 ];
    B.Ves = ++V;
    NNF::PrabhupadaBukvary[ S[ 1 ] ] = B;
  }
}

void __fastcall TfmfPrabhupadaSlovar::SetFilterSlovar( NNF::TFilterSlovar Value )
{
  if ( !SetFilterStart )
    return;

  NNF::TFilterSlovar &FS = YazykVector[ YazykIndex ].FilterSlovar;
  if ( FS != Value || Value.IsReset ) {
    FS = Value;

    bool SIsReset = FS.IsReset;
    FS.IsReset = false;
    // В дальнейшем мы можем повысить скорость, еспользуя простое свойство IsEmpty вместо функции GetIsEmpty()!
    FS.IsEmpty = FS.GetIsEmpty();

    PreparePrabhupadaSearchVector();
    RefreshPrabhupadaSlovar( SIsReset ? YazykVector[ YazykIndex ].CurrentRow : 0, PrabhupadaSlovarVector.SearchCount );

    edSanskrit->Text = FS.Sanskrit;
    edPerevod->Text  = FS.Perevod;
  }
}

void __fastcall TfmfPrabhupadaSlovar::RefreshPrabhupadaSlovar( int ACurrentRow, int ARowCount )
{
  grPrabhupadaSlovar->RowCount = 0;
  grPrabhupadaSlovar->RowCount = ARowCount;

  grPrabhupadaSlovar->Row = ACurrentRow;
}

void __fastcall TfmfPrabhupadaSlovar::PreparePrabhupadaSearchVector()
{
  if ( !FilterSlovar.IsEmpty ) {
    int ActualIndex = -1;
    bool CheckSanskrit = !FilterSlovar.Sanskrit.IsEmpty(),
         CheckPerevod  = !FilterSlovar.Perevod.IsEmpty();
    TRegExOptions RO;
    RO = RO << roMultiLine;
    if ( !CaseSensitive )
      RO = RO << roIgnoreCase;
    std::unique_ptr< TRegEx > reSanskrit( new TRegEx( FilterSlovar.SanskritWithoutDiakritik, RO ) )
                            , rePerevod(  new TRegEx( FilterSlovar.PerevodWithoutDiakritik,  RO ) );

    bool NeedSanskrit
       , NeedPerevod;

    int L = FPrabhupadaSlovarVector.size();
    for ( int I = 0; I < L; ++I ) {
      NeedPerevod = false;
      NeedSanskrit = CheckSanskrit ? reSanskrit->IsMatch( PrabhupadaSlovarVector[ I ]->SanskritWithoutDiakritik ) : true;
      if ( NeedSanskrit )
        NeedPerevod  = CheckPerevod  ? rePerevod->IsMatch(  PrabhupadaSlovarVector[ I ]->PerevodWithoutDiakritik )  : true;
      if ( NeedPerevod )
        PrabhupadaSlovarVector[ ++ActualIndex ]->SearchIndex = I;
    }
    PrabhupadaSlovarVector.SearchCount = ActualIndex + 1;
  } else {
    PrabhupadaSlovarVector.SearchCount = PrabhupadaSlovarVector.size();
  }
}

void __fastcall TfmfPrabhupadaSlovar::SetCaseSensitive( bool Value )
{
  if ( FCaseSensitive != Value ) {
    FCaseSensitive = Value;
    FilterSlovar.IsReset = true;

    aCaseSensitive->Checked    = CaseSensitive;
    sbCaseSensitive->IsPressed = CaseSensitive;
    miCaseSensitive->IsChecked = CaseSensitive;
  }
}

void __fastcall TfmfPrabhupadaSlovar::aCaseSensitiveExecute(TObject *Sender)
{
  CaseSensitive = !CaseSensitive;
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::cbOrderByChange(TObject *Sender)
{
  OrderBy = ( NNF::TOrderBy )cbOrderBy->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::SanskritPerevodKeyDown( TObject *Sender, WORD &Key,
          System::WideChar &KeyChar, TShiftState Shift )
{
  switch ( Key ) {
  case vkReturn /*VK_RETURN*/ :
     if ( Shift == TShiftState() ) {
       aSearch->Execute();
       Key = 0;
     }
     break;
  case vkUp /*VK_UP*/ :
  case vkDown /*VK_DOWN*/ :
     grPrabhupadaSlovar->SetFocus();
     Key = 0;
     break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aDeleteExecute( TObject *Sender )
{
  if ( grPrabhupadaSlovar->RowCount  == 0 )
    return;

  TDialogService::MessageDialog( "Удалить слово?", TMsgDlgType::mtConfirmation, mbOKCancel, TMsgDlgBtn::mbOK, 0, DeleteSanskritPerevod );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::DeleteSanskritPerevod( TObject* Sender, const TModalResult AResult )
{
  if ( AResult == mrOk ) {
    int I = grPrabhupadaSlovar->Row;
    NNF::TSanskritPerevod *SP;
    TFDParam *p = quDeleteSanskrit->FindParam( "ID" );

    if ( PrabhupadaSlovarVector.SearchCount < PrabhupadaSlovarVector.size() ) {
      int N = PrabhupadaSlovarVector[ I ]->SearchIndex;
      SP = PrabhupadaSlovarVector[ N ];
      p->Value = SP->ID;
      //PrabhupadaSlovarVector.erase( std::remove( PrabhupadaSlovarVector.begin(), PrabhupadaSlovarVector.end(), SP ), PrabhupadaSlovarVector.end() );
      PrabhupadaSlovarVector.erase( PrabhupadaSlovarVector.begin() + N );
      PrabhupadaSlovarVector.SearchCount = PrabhupadaSlovarVector.SearchCount - 1;
    } else {
      SP = PrabhupadaSlovarVector[ I ];
      p->Value = SP->ID;
      PrabhupadaSlovarVector.erase( PrabhupadaSlovarVector.begin() + I );
    }
    grPrabhupadaSlovar->RowCount = grPrabhupadaSlovar->RowCount - 1;
    if ( I >= grPrabhupadaSlovar->RowCount )
      I = grPrabhupadaSlovar->RowCount - 1;
    RefreshPrabhupadaSlovar( I, grPrabhupadaSlovar->RowCount );

    quDeleteSanskrit->ExecSQL();
    delete SP;
  }
}

void __fastcall TfmfPrabhupadaSlovar::DeleteSanskritPerevodID( int AID )
{
  TFDParam *p = quDeleteSanskrit->FindParam( "ID" );
  p->Value = AID;
  quDeleteSanskrit->ExecSQL();
}

void __fastcall TfmfPrabhupadaSlovar::aInsertExecute(TObject *Sender)
{
  int I = grPrabhupadaSlovar->Row;
  NNF::TSanskritPerevod *SP = new NNF::TSanskritPerevod();

  int ARowCount;
  if ( PrabhupadaSlovarVector.SearchCount < PrabhupadaSlovarVector.size() ) {
    PrabhupadaSlovarVector.push_back( SP );
    SP->SearchIndex = PrabhupadaSlovarVector.SearchCount;
    PrabhupadaSlovarVector.SearchCount = PrabhupadaSlovarVector.SearchCount + 1;
    ARowCount = PrabhupadaSlovarVector.SearchCount;
  } else {
    PrabhupadaSlovarVector.insert( PrabhupadaSlovarVector.begin() + I, SP );
    ARowCount = PrabhupadaSlovarVector.size();
  }

  MaxID = MaxID + 1;
  SP->ID = MaxID;
  SP->Sanskrit = L"Санскрит";
  SP->Perevod  = L"Перевод";
  SP->SanskritWithoutDiakritik = NNF::RemoveDiacritics( SP->Sanskrit );
  SP->PerevodWithoutDiakritik  = NNF::RemoveDiacritics( SP->Perevod );

  TFDParam *p = quInsertSanskrit->FindParam( "ID" );
  p->Value = SP->ID;
  p = quInsertSanskrit->FindParam( "IZNACHALYNO" );
  p->Value = SP->Sanskrit;
  p = quInsertSanskrit->FindParam( "PEREVOD" );
  p->Value = SP->Perevod;
  p = quInsertSanskrit->FindParam( "YAZYK" );
  p->Value = YazykVector[ YazykIndex ].Yazyk;

  quInsertSanskrit->ExecSQL();

  grPrabhupadaSlovar->RowCount = grPrabhupadaSlovar->RowCount + 1;
  RefreshPrabhupadaSlovar( grPrabhupadaSlovar->Row, ARowCount );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aRemoveDuplicatesExecute(TObject *Sender)
{
  std::size_t SaveSize = PrabhupadaSlovarVector.size();

  NNF::TSanskritPerevod *iSP, *nSP;
  int n = 0, i = 1;
  while ( i < PrabhupadaSlovarVector.size() ) {
    do {
      if ( i >= PrabhupadaSlovarVector.size() )
        return;
      iSP = PrabhupadaSlovarVector[ i ];
      nSP = PrabhupadaSlovarVector[ n ];
      if ( iSP->Sanskrit == nSP->Sanskrit && iSP->Perevod == nSP->Perevod ) {
        PrabhupadaSlovarVector.erase( PrabhupadaSlovarVector.begin() + i );
        DeleteSanskritPerevodID( iSP->ID );
      } else
        break;
    } while ( true );
    ++n;
    ++i;
  }

  if ( SaveSize != PrabhupadaSlovarVector.size() )
    RefreshPrabhupadaSlovar( grPrabhupadaSlovar->Row, PrabhupadaSlovarVector.size() );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::SetBookmark( WORD Key )
{
  PrabhupadaZakladkaMap[ Key ] = NNF::TPrabhupadaZakladka( grPrabhupadaSlovar->Row, FilterSlovar );
}

void __fastcall TfmfPrabhupadaSlovar::GoToBookmark( WORD Key )
{
  NNF::TPrabhupadaZakladkaMap::iterator I = PrabhupadaZakladkaMap.find( Key );
  if ( I != PrabhupadaZakladkaMap.end() ) {
    FilterSlovar = (*I).second.FilterSlovar;
    grPrabhupadaSlovar->Row = (*I).second.RowNum;
  }
}

void __fastcall TfmfPrabhupadaSlovar::aSetBookmark0Execute(TObject *Sender)
{
  SetBookmark( '0' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aSetBookmark1Execute(TObject *Sender)
{
  SetBookmark( '1' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aSetBookmark2Execute(TObject *Sender)
{
  SetBookmark( '2' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aSetBookmark3Execute(TObject *Sender)
{
  SetBookmark( '3' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aSetBookmark4Execute(TObject *Sender)
{
  SetBookmark( '4' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aSetBookmark5Execute(TObject *Sender)
{
  SetBookmark( '5' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aSetBookmark6Execute(TObject *Sender)
{
  SetBookmark( '6' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aSetBookmark7Execute(TObject *Sender)
{
  SetBookmark( '7' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aSetBookmark8Execute(TObject *Sender)
{
  SetBookmark( '8' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aSetBookmark9Execute(TObject *Sender)
{
  SetBookmark( '9' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aGoToBookmark0Execute(TObject *Sender)
{
  GoToBookmark( '0' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aGoToBookmark1Execute(TObject *Sender)
{
  GoToBookmark( '1' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aGoToBookmark2Execute(TObject *Sender)
{
  GoToBookmark( '2' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aGoToBookmark3Execute(TObject *Sender)
{
  GoToBookmark( '3' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aGoToBookmark4Execute(TObject *Sender)
{
  GoToBookmark( '4' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aGoToBookmark5Execute(TObject *Sender)
{
  GoToBookmark( '5' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aGoToBookmark6Execute(TObject *Sender)
{
  GoToBookmark( '6' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aGoToBookmark7Execute(TObject *Sender)
{
  GoToBookmark( '7' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aGoToBookmark8Execute(TObject *Sender)
{
  GoToBookmark( '8' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aGoToBookmark9Execute(TObject *Sender)
{
  GoToBookmark( '9' );
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::coResDefault(TObject *Sender)
{
  Position = TFormPosition::ScreenCenter;
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aAboutExecute(TObject *Sender)
{
  fmfAboutPrabhupadaSlovar = new TfmfAboutPrabhupadaSlovar( this );
  fmfAboutPrabhupadaSlovar->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::cbLanguageChange(TObject *Sender)
{
  dmfNewNavadvipa->lmDB->CurrentLanguageID = dmfNewNavadvipa->lmDB->LanguageVector[ cbLanguage->ItemIndex ].LanguageID;
}
//---------------------------------------------------------------------------

void __fastcall TfmfPrabhupadaSlovar::aLanguageEditExecute(TObject *Sender)
{
  NNF::FormCreate( __classid( TfmfLanguage ), &fmfLanguage );
  NNF::FormShow( fmfLanguage );
}
//---------------------------------------------------------------------------

