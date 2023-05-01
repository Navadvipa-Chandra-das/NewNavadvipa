#pragma hdrstop

#include "RoseFastReportLibrary.h"
#include "cwtreenum.h"
#include "cwconst.h"
#include "dm_data.h"

#pragma package(smart_init)

namespace RoseFastReportLibrary
{

cw::TFastReportLibrary *Library;

class TT
{
public :
  TT();
  ~TT();
};

TT::TT()
{
  Library = new cw::TFastReportLibrary();
}

TT::~TT()
{
  delete Library;
  Library = NULL;
}

TT tt;

}

namespace cw {

TCWDoubleNumerator TreeNum;

__fastcall TFastReportLibrary::TFastReportLibrary()
  : inherited()
{
  fsGlobalUnit()->AddedBy = this;
  fsGlobalUnit()->AddMethod( "procedure ClearTreeNum"
                           , &CallMethod
                           , cwconst::Navadvipa
                           , "Очистка древовидного списка" );
  fsGlobalUnit()->AddMethod( "function IncTreeNum( Parent_ : Double ) : String"
                           , &CallMethod
                           , cwconst::Navadvipa
                           , "Увеличение древовидного индекса и возврат его" );
  fsGlobalUnit()->AddMethod( "function TreeNum : String"
                           , &CallMethod
                           , cwconst::Navadvipa
                           , "Возврат древовидного индекса" );
  fsGlobalUnit()->AddMethod( "function GetNumdec( CurrencyNo_ : Integer ) : Integer"
                           , &CallMethod
                           , cwconst::Navadvipa
                           , "До скольки округлять валюту?" );
  fsGlobalUnit()->AddMethod( "function UserName : String"
                           , &CallMethod
                           , cwconst::Navadvipa
                           , "Полное имя пользователя" );
  fsGlobalUnit()->AddMethod( "function ApplicationTitle : String"
                           , &CallMethod
                           , cwconst::Navadvipa
                           , "Имя программы" );

  fsGlobalUnit()->AddedBy = NULL;
}

__fastcall TFastReportLibrary::~TFastReportLibrary()
{
  if ( fsGlobalUnit() )
    fsGlobalUnit()->RemoveItems( this );
}

Variant __fastcall TFastReportLibrary::CallMethod( System::TObject* Instance
                                                 , TMetaClass* ClassType
                                                 , const AnsiString MethodName
                                                 , Variant &Params )
{
  Variant R = 0;

  if ( MethodName == "CLEARTREENUM" ) {
    TreeNum.clear();
  } else if ( MethodName == "INCTREENUM" ) {
    double P = Params.GetElement( 0 );
    TreeNum.AddParent( P );
    R = TreeNum.Text;
  } else if ( MethodName == "TREENUM" ) {
    R = TreeNum.Text;
  } else if ( MethodName == "GETNUMDEC" ) {
    int P = Params.GetElement( 0 );
    R = dmData->CurrencyManager->CurrencyToNumdec( P );
  } else if ( MethodName == "USERNAME" ) {
    R = dmData->UserName;
  } else if ( MethodName == "APPLICATIONTITLE" ) {
    R = Application->Title;
  }
  return R;
}

}

