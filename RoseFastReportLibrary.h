#ifndef RoseFastReportLibraryH
#define RoseFastReportLibraryH

#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include "frxClass.hpp"
#include "fs_iinterpreter.hpp"

namespace cw {

class PACKAGE TFastReportLibrary : public TObject
{
private:
  typedef TObject inherited;
  Variant __fastcall CallMethod( System::TObject* Instance
                               , TMetaClass* ClassType
                               , const AnsiString MethodName
                               , Variant &Params );
public:
  __fastcall TFastReportLibrary();
  __fastcall ~TFastReportLibrary();
};

}

#endif
