// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef VCL_NNRightsManagerH
#define VCL_NNRightsManagerH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <Vcl.Controls.hpp>
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <set>
#include <vector>
// ---------------------------------------------------------------------------

namespace NNV {

PACKAGE enum class TIsThrow : unsigned char {
  Abort
, ThrowException
, ShowMessage
, Quiet
};

};

class PACKAGE TNNVRight;

namespace NNV {

using TCompList = PACKAGE std::set< TNNVRight* >;
using TBoolVector = PACKAGE std::vector< bool >;

}

class PACKAGE TNNVRightsManager : public TComponent
{
private:
  using inherited = TComponent;
  NNV::TBoolVector FRights;
  int NumRights;
  bool fSuperUser;
  NNV::TCompList *CompList;
  TFDConnection *fConnection;
  int fUserNo;
  void __fastcall SetConnection( TFDConnection *Value );
protected:
  virtual void __fastcall Notification( TComponent *AComponent, TOperation Operation );
public:
  __fastcall TNNVRightsManager( TComponent* Owner );
  __fastcall ~TNNVRightsManager();
  void __fastcall LoadRights();
  void __fastcall RefreshRights( long long int AUserID );
  bool __fastcall IsRight( int ARightIndex, NNV::TIsThrow AIsThrow = NNV::TIsThrow::Quiet );
  void __fastcall AddComp( TNNVRight *aComp );
  void __fastcall EraseComp( TNNVRight *aComp );
  void __fastcall RevokeAll();
  void __fastcall SendMessage( int aMessage );
  __property bool SuperUser = {read = fSuperUser, write = fSuperUser};
  __property int UserNo = {read = fUserNo};
  __property NNV::TBoolVector Rights = { read = FRights };
__published:
  __property TFDConnection *Connection = { read = fConnection, write = SetConnection };
};

class PACKAGE TNNVRight : public TComponent {
private:
  using inherited = TComponent;
  TNNVRightsManager *fManager = nullptr;
  TNotifyEvent fOnRight;

  void __fastcall SetManager(TNNVRightsManager *Value);

protected:
  void __fastcall Notification( TComponent *AComponent, TOperation Operation );

  virtual void __fastcall DoRight()
  {
    if ( fOnRight )
      fOnRight(this);
  };

public:
  __fastcall TNNVRight( TComponent* Owner );

  void __fastcall Apply()
  {
    DoRight();
  };

__published:
  __property TNotifyEvent OnRight = { read = fOnRight, write = fOnRight };
  __property TNNVRightsManager* Manager = { read = fManager, write = SetManager };
};

// ---------------------------------------------------------------------------
#endif
