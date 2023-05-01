// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef FMX_NNLanguageManagerH
#define FMX_NNLanguageManagerH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Comp.Client.hpp>
#include "FMX_NNCommon.h"
#include "FMX_NNDBMiracle.h"
#include <set>
#include <vector>
// ---------------------------------------------------------------------------

class PACKAGE TNNFLanguage;

namespace NNF {

extern PACKAGE const int FieldIndexLanguageStringID;
extern PACKAGE const int FieldIndexTranslate;

class PACKAGE TLanguage
{
private:
  int FItemIndex = -1;
  long long int FLanguageID;
  String FLanguageStringID;
  String FLanguage;
public:
  TLanguage();
  ~TLanguage();
  __property long long int LanguageID = { read = FLanguageID, write = FLanguageID };
  __property String LanguageStringID = { read = FLanguageStringID, write = FLanguageStringID };
  __property String Language = { read = FLanguage, write = FLanguage };
  __property int ItemIndex = { read = FItemIndex, write = FItemIndex };
};

using TLanguageSet = PACKAGE std::set< TNNFLanguage* >;
using TLanguageVector = PACKAGE std::vector< TLanguage >;

}

class PACKAGE TNNFLanguageManager : public TComponent
{
private:
  using inherited = TComponent;
  long long int FCurrentLanguageID = 0;
  NNF::TLanguageSet *LanguageSet;
  TFDConnection *fConnection = nullptr;
  NNF::TLanguageVector FLanguageVector;
  NNF::TStringSet FLanguageExcludeStringSet;
  NNF::TStringSet FPairExcludeStringSet;
  TNNFQuery *FQuery = nullptr;
  NNF::TStringMap FLanguageMap;
  void __fastcall SetConnection( TFDConnection *Value );
  void __fastcall SetCurrentLanguageID( long long int Value );
  void __fastcall SetMainLanguageID( long long int Value );
  void __fastcall PrepareLanguageExcludeStringSet();
  void __fastcall PrepareOwnerWordsRecursive( TComponent *AOwner
                                            , NNF::TDoInsertLanguageRow ADoInsertLanguageRow
                                            , String &AOwnerClassNamePrefix
                                            , bool &AFirstMinusOne );
protected:
  virtual void __fastcall Notification( TComponent *AComponent, TOperation Operation );
  __property TNNFQuery *Query = { read = FQuery, write = FQuery };
public:
  __fastcall TNNFLanguageManager( TComponent* Owner );
  __fastcall ~TNNFLanguageManager();
  void __fastcall PrepareOwnerWords( TComponent *AOwner
                                   , NNF::TDoInsertLanguageRow ADoInsertLanguageRow
                                   , NNF::TDoPrepareOwner ADoPrepareOwner
                                   , TNotifyEvent ADoUnPrepareOwner );
  void __fastcall LoadLanguages();
  void __fastcall AddComp( TNNFLanguage *aComp );
  void __fastcall EraseComp( TNNFLanguage *aComp );
  void __fastcall SendMessage( int aMessage );
  void __fastcall PrepareStrings( TStrings *AStrings );
  int __fastcall LanguageIDToItemIndex( long long int ALanguageID );
  void __fastcall PrepareLanguageOwner( const String &AOwnerString );
  void __fastcall UnPrepareLanguageOwner( TObject *Sender );
  void __fastcall SetLanguageRow( const String &ALanguage
                                , String &ATranslate
                                , bool &ATranslateSet );
  __property NNF::TLanguageVector LanguageVector = { read = FLanguageVector };
  __property long long int CurrentLanguageID = { read = FCurrentLanguageID, write = SetCurrentLanguageID };
  __property long long int MainLanguageID = { write = SetMainLanguageID };
  __property NNF::TStringSet LanguageExcludeStringSet = { read = FLanguageExcludeStringSet };
  __property NNF::TStringSet PairExcludeStringSet = { read = FPairExcludeStringSet };
  __property NNF::TStringMap LanguageMap = { read = FLanguageMap };
__published:
  __property TFDConnection *Connection = { read = fConnection, write = SetConnection };
};

class PACKAGE TNNFLanguage : public TComponent {
private:
  using inherited = TComponent;
  friend class TNNFLanguageManager;
  TNNFLanguageManager *fManager = nullptr;
  TNotifyEvent fOnLanguage;
  bool FFirstApplyWork = true;
  void __fastcall SetManager( TNNFLanguageManager *Value );
protected:
  void __fastcall Notification( TComponent *AComponent, TOperation Operation );
  virtual void __fastcall DoLanguage();
  __property bool FirstApplyWork = { read = FFirstApplyWork, write = FFirstApplyWork };
public:
  __fastcall TNNFLanguage( TComponent* Owner );
  void __fastcall Apply();
__published:
  __property TNotifyEvent OnLanguage = { read = fOnLanguage, write = fOnLanguage };
  __property TNNFLanguageManager* Manager = { read = fManager, write = SetManager };
};

// ---------------------------------------------------------------------------
#endif
