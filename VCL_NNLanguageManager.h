// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef VCL_NNLanguageManagerH
#define VCL_NNLanguageManagerH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <Vcl.Controls.hpp>
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
#include <FireDAC.Comp.Client.hpp>
#include "VCL_NNDBMiracle.h"
#include "VCL_NNCommon.h"
#include <set>
#include <vector>
// ---------------------------------------------------------------------------

class PACKAGE TNNVLanguage;

namespace NNV {

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

using TLanguageSet = PACKAGE std::set< TNNVLanguage* >;
using TLanguageVector = PACKAGE std::vector< TLanguage >;

}

class PACKAGE TNNVLanguageManager : public TComponent
{
private:
  using inherited = TComponent;
  long long int FCurrentLanguageID = 0;
  NNV::TLanguageSet *LanguageSet;
  TFDConnection *fConnection = nullptr;
  NNV::TLanguageVector FLanguageVector;
  NNV::TStringSet FLanguageExcludeStringSet;
  NNV::TStringSet FPairExcludeStringSet;
  TNNVQuery *FQuery = nullptr;
  NNV::TStringMap FLanguageMap;
  void __fastcall SetConnection( TFDConnection *Value );
  void __fastcall SetCurrentLanguageID( long long int Value );
  void __fastcall SetMainLanguageID( long long int Value );
  void __fastcall PrepareLanguageExcludeStringSet();
  void __fastcall PrepareOwnerWordsRecursive( TComponent *AOwner
                                            , NNV::TDoInsertLanguageRow ADoInsertLanguageRow
                                            , String &AOwnerClassNamePrefix
                                            , bool &AFirstMinusOne );
protected:
  virtual void __fastcall Notification( TComponent *AComponent, TOperation Operation );
  __property TNNVQuery *Query = { read = FQuery, write = FQuery };
public:
  __fastcall TNNVLanguageManager( TComponent* Owner );
  __fastcall ~TNNVLanguageManager();
  void __fastcall PrepareOwnerWords( TComponent *AOwner
                                   , NNV::TDoInsertLanguageRow ADoInsertLanguageRow
                                   , NNV::TDoPrepareOwner ADoPrepareOwner
                                   , TNotifyEvent ADoUnPrepareOwner );
  void __fastcall LoadLanguages();
  void __fastcall AddComp( TNNVLanguage *aComp );
  void __fastcall EraseComp( TNNVLanguage *aComp );
  void __fastcall SendMessage( int aMessage );
  void __fastcall PrepareLanguage( TComponent *AOwner );
  void __fastcall PrepareStrings( TStrings *AStrings );
  int __fastcall LanguageIDToItemIndex( long long int ALanguageID );
  void __fastcall PrepareLanguageOwner( const String &AOwnerString );
  void __fastcall UnPrepareLanguageOwner( TObject *Sender );
  void __fastcall SetLanguageRow( const String &ALanguage
                                , String &ATranslate
                                , bool &ATranslateSet );
  __property NNV::TLanguageVector LanguageVector = { read = FLanguageVector };
  __property long long int CurrentLanguageID = { read = FCurrentLanguageID, write = SetCurrentLanguageID };
  __property long long int MainLanguageID = { write = SetMainLanguageID };
  __property NNV::TStringSet LanguageExcludeStringSet = { read = FLanguageExcludeStringSet };
  __property NNV::TStringSet PairExcludeStringSet = { read = FPairExcludeStringSet };
  __property NNV::TStringMap LanguageMap = { read = FLanguageMap };
__published:
  __property TFDConnection *Connection = { read = fConnection, write = SetConnection };
};

class PACKAGE TNNVLanguage : public TComponent {
private:
  using inherited = TComponent;
  friend class TNNVLanguageManager;
  TNNVLanguageManager *fManager = nullptr;
  TNotifyEvent fOnLanguage;
  bool FFirstApplyWork = true;
  void __fastcall SetManager( TNNVLanguageManager *Value );
protected:
  void __fastcall Notification( TComponent *AComponent, TOperation Operation );
  virtual void __fastcall DoLanguage();
  __property bool FirstApplyWork = { read = FFirstApplyWork, write = FFirstApplyWork };
public:
  __fastcall TNNVLanguage( TComponent* Owner );
  void __fastcall Apply();
__published:
  __property TNotifyEvent OnLanguage = { read = fOnLanguage, write = fOnLanguage };
  __property TNNVLanguageManager* Manager = { read = fManager, write = SetManager };
};

// ---------------------------------------------------------------------------
#endif
