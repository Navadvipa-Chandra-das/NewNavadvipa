//---------------------------------------------------------------------------

#ifndef FMX_NNFmPrabhupadaSlovarH
#define FMX_NNFmPrabhupadaSlovarH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "FMX_NNFmRes.h"
#include "FMX_NNDBMiracle.h"
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.Rtti.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.FMXUI.Wait.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.SQLite.hpp>
#include <FireDAC.Phys.SQLiteDef.hpp>
#include <FireDAC.Phys.SQLiteWrapper.Stat.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.ExprFuncs.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FMX.ActnList.hpp>
#include <System.Actions.hpp>
#include <FMX.ImgList.hpp>
#include <System.ImageList.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.SpinBox.hpp>
#include "FMX_NNCommon.h"
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.Menus.hpp>
#include <FMX.Controls3D.hpp>
#include <FMX.Layers3D.hpp>
#include <System.Math.Vectors.hpp>
#include "FMX_NNFlagBox.h"
#include "FMX_NNLanguageManager.h"
#include "FMX_NNRightsManager.h"
#include "FMX_NNActionList.h"
//---------------------------------------------------------------------------

class TfmfPrabhupadaSlovar : public TfmfRes
{
__published:	// IDE-managed Components
  TLayout *laT;
  TLayout *laB;
  TLayout *laC;
  TEdit *edSanskrit;
  TSplitter *splSanskritPerevod;
  TEdit *edPerevod;
  TGrid *grPrabhupadaSlovar;
  TStringColumn *scSanskrit;
  TStringColumn *skPerevod;
  TToolBar *tbrPrabhupadaSlovar;
  TNNFQuery *quPrabhupadaSlovar;
  TNNFQuery *quYazyk;
  TActionList *alPrabhupadaSlovar;
  TImageList *ilPrabhupadaSlovar;
  TAction *aSearch;
  TSpeedButton *sbSearch;
  TIntegerField *quYazykID;
  TWideMemoField *quYazykYAZYK;
  TWideMemoField *quYazykYAZYK_SLOVO;
  TWideMemoField *quPrabhupadaSlovarIZNACHALYNO;
  TWideMemoField *quPrabhupadaSlovarPEREVOD;
  TAction *aCaseSensitive;
  TSpeedButton *sbCaseSensitive;
  TAction *aDelete;
  TAction *aInsert;
  TSpeedButton *sbDelete;
  TSpeedButton *sbInsert;
  TNNFQuery *quUpdateSanskrit;
  TNNFQuery *quDeleteSanskrit;
  TNNFQuery *quInsertSanskrit;
  TNNFQuery *quMaxID;
  TIntegerField *quPrabhupadaSlovarID;
  TAction *aRemoveDuplicates;
  TSpeedButton *sbRemoveDuplicates;
  TAction *aSetBookmark0;
  TAction *aSetBookmark1;
  TAction *aSetBookmark2;
  TAction *aSetBookmark3;
  TAction *aSetBookmark4;
  TAction *aSetBookmark5;
  TAction *aSetBookmark6;
  TAction *aSetBookmark7;
  TAction *aSetBookmark8;
  TAction *aSetBookmark9;
  TAction *aGoToBookmark0;
  TAction *aGoToBookmark1;
  TAction *aGoToBookmark2;
  TAction *aGoToBookmark3;
  TAction *aGoToBookmark4;
  TAction *aGoToBookmark5;
  TAction *aGoToBookmark6;
  TAction *aGoToBookmark7;
  TAction *aGoToBookmark8;
  TAction *aGoToBookmark9;
  TMenuItem *mipSetBookmark0;
  TMenuItem *mipSetBookmark1;
  TMenuItem *mipSetBookmark3;
  TMenuItem *mipSetBookmark4;
  TMenuItem *mipSetBookmark5;
  TMenuItem *mipSetBookmark6;
  TMenuItem *mipSetBookmark7;
  TMenuItem *mipSetBookmark8;
  TMenuItem *mipSetBookmark9;
  TMenuItem *mipGoToBookmark0;
  TMenuItem *mipGoToBookmark1;
  TMenuItem *mipGoToBookmark2;
  TMenuItem *mipGoToBookmark3;
  TMenuItem *mipGoToBookmark4;
  TMenuItem *mipGoToBookmark5;
  TMenuItem *mipGoToBookmark6;
  TMenuItem *mipGoToBookmark7;
  TMenuItem *mipGoToBookmark8;
  TMenuItem *mipGoToBookmark9;
  TMenuItem *mipSetBookmark2;
  TMainMenu *mmPrabupadaSlovar;
  TMenuItem *miAction;
  TMenuItem *miSetBookmark;
  TMenuItem *miGoToBookmark;
  TLayout *laTComboBox;
  TComboBox *cbOrderBy;
  TComboBox *cbYazyk;
  TLayout3D *Layout3D1;
  TMenuItem *miSearch;
  TMenuItem *miCaseSensitive;
  TMenuItem *miDelete;
  TMenuItem *miInsert;
  TMenuItem *miRemoveDuplicates;
  TAction *aAbout;
  TSpeedButton *sbAbout;
  TLayout *laTEdit;
  TSpinBox *sbFontSize;
  TEdit *edInfo;
  TComboBox *cbLanguage;
  TAction *aLanguageEdit;
  TMenuItem *MenuItem1;
  void __fastcall grPrabhupadaSlovarGetValue( TObject *Sender, const int ACol, const int ARow,
          TValue &Value );
  void __fastcall FormCreate( TObject *Sender );
  void __fastcall aSearchExecute( TObject *Sender );
  void __fastcall coResLoad( TObject *Sender );
  void __fastcall coResSave( TObject *Sender );
  void __fastcall coResEndLoad( TObject *Sender );
  void __fastcall sbFontSizeChange( TObject *Sender );
  void __fastcall cbYazykChange( TObject *Sender );
  void __fastcall grPrabhupadaSlovarSetValue( TObject *Sender, const int ACol, const int ARow,
          const TValue &Value );
  void __fastcall grPrabhupadaSlovarSelChanged( TObject *Sender );
  void __fastcall grPrabhupadaSlovarHeaderClick( TColumn *Column );
  void __fastcall aCaseSensitiveExecute( TObject *Sender );
  void __fastcall cbOrderByChange( TObject *Sender );
  void __fastcall SanskritPerevodKeyDown( TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift );
  void __fastcall aDeleteExecute( TObject *Sender );
  void __fastcall aInsertExecute( TObject *Sender );
  void __fastcall aRemoveDuplicatesExecute( TObject *Sender );
  void __fastcall aSetBookmark0Execute(TObject *Sender);
  void __fastcall aSetBookmark1Execute(TObject *Sender);
  void __fastcall aSetBookmark2Execute(TObject *Sender);
  void __fastcall aSetBookmark3Execute(TObject *Sender);
  void __fastcall aSetBookmark4Execute(TObject *Sender);
  void __fastcall aSetBookmark5Execute(TObject *Sender);
  void __fastcall aSetBookmark6Execute(TObject *Sender);
  void __fastcall aSetBookmark7Execute(TObject *Sender);
  void __fastcall aSetBookmark8Execute(TObject *Sender);
  void __fastcall aSetBookmark9Execute(TObject *Sender);
  void __fastcall aGoToBookmark0Execute(TObject *Sender);
  void __fastcall aGoToBookmark1Execute(TObject *Sender);
  void __fastcall aGoToBookmark2Execute(TObject *Sender);
  void __fastcall aGoToBookmark3Execute(TObject *Sender);
  void __fastcall aGoToBookmark4Execute(TObject *Sender);
  void __fastcall aGoToBookmark5Execute(TObject *Sender);
  void __fastcall aGoToBookmark6Execute(TObject *Sender);
  void __fastcall aGoToBookmark7Execute(TObject *Sender);
  void __fastcall aGoToBookmark8Execute(TObject *Sender);
  void __fastcall aGoToBookmark9Execute(TObject *Sender);
  void __fastcall coResDefault( TObject *Sender );
  void __fastcall aAboutExecute(TObject *Sender);
  void __fastcall cbLanguageChange(TObject *Sender);
  void __fastcall aLanguageEditExecute(TObject *Sender);
private:	// User declarations
  using inherited = TfmfRes;
  int FYazykIndex = -1;
  NNF::TYazykVector FYazykVector;
  NNF::TPrabhupadaSlovarVector FPrabhupadaSlovarVector;
  NNF::TOrderBy FOrderBy = NNF::TOrderBy::PerevodUbyvanie;
  bool FNeedSort = true;
  bool FCaseSensitive = true;
  int FUpdateRowCount = 0;
  bool FSetFilterStart = false;
  int FMaxID;
  void __fastcall SetCaseSensitive( bool Value );
  void __fastcall PrepareYazykAndMaxID();
  void __fastcall PreparePrabhupadaSlovar();
  void __fastcall PrepareBukvaryPrabhupada();
  void __fastcall PreparePrabhupadaBukvary();
  void __fastcall SetYazykIndex( int Value );
  void __fastcall SetOrderBy( NNF::TOrderBy Value );
  void __fastcall SortPrabhupadaSlovar();
  NNF::TFilterSlovar& __fastcall GetFilterSlovar()
  {
    return YazykVector[ YazykIndex ].FilterSlovar;
  };
  NNF::TPrabhupadaZakladkaMap& __fastcall GetPrabhupadaZakladkaMap()
  {
    return YazykVector[ YazykIndex ].PrabhupadaZakladkaMap;
  };
  void __fastcall SetFilterSlovar( NNF::TFilterSlovar Value );
  void __fastcall PreparePrabhupadaSearchVector();
  void __fastcall RefreshPrabhupadaSlovar( int ACurrentRow, int ARowCount );
  void __fastcall DeleteSanskritPerevod( TObject* Sender, const TModalResult AResult );
  void __fastcall DeleteSanskritPerevodID( int AID );
  void __fastcall SetBookmark( WORD Key );
  void __fastcall GoToBookmark( WORD Key );
  void __fastcall PrepareLanguages();
protected:
  virtual void __fastcall Loaded();
  __property NNF::TYazykVector YazykVector = { read = FYazykVector };
  __property NNF::TPrabhupadaSlovarVector PrabhupadaSlovarVector = { read = FPrabhupadaSlovarVector };
  __property int YazykIndex = { read = FYazykIndex, write = SetYazykIndex };
  __property NNF::TOrderBy OrderBy = { read = FOrderBy, write = SetOrderBy };
  __property bool NeedSort = { read = FNeedSort, write = FNeedSort };
  __property NNF::TFilterSlovar FilterSlovar = { read = GetFilterSlovar, write = SetFilterSlovar };
  __property NNF::TPrabhupadaZakladkaMap PrabhupadaZakladkaMap = { read = GetPrabhupadaZakladkaMap };
  __property bool CaseSensitive = { read = FCaseSensitive, write = SetCaseSensitive };
  __property int UpdateRowCount = { read = FUpdateRowCount, write = FUpdateRowCount };
  __property bool SetFilterStart = { read = FSetFilterStart, write = FSetFilterStart };
  __property int MaxID = { read = FMaxID, write = FMaxID };
public:		// User declarations
  __fastcall TfmfPrabhupadaSlovar( TComponent* Owner );
};
//---------------------------------------------------------------------------

extern PACKAGE TfmfPrabhupadaSlovar *fmfPrabhupadaSlovar;
//---------------------------------------------------------------------------
#endif
