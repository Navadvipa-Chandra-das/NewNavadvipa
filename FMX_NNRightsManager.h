// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef FMX_NNRightsManagerH
#define FMX_NNRightsManagerH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <FMX.Controls.hpp>
#include <System.Classes.hpp>
#include <FMX.Forms.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <set>
#include <vector>
// ---------------------------------------------------------------------------

namespace NNF {

PACKAGE enum class TIsThrow : unsigned char {
  Abort
, ThrowException
, ShowMessage
, Quiet
};

};

class PACKAGE TNNFRight;

namespace NNF {

using TCompList = PACKAGE std::set< TNNFRight* >;
using TBoolVector = PACKAGE std::vector< bool >;

}

class PACKAGE TNNFRightsManager : public TComponent
{
private:
  using inherited = TComponent;
  NNF::TBoolVector FRights;
  int NumRights;
  bool fSuperUser;
  NNF::TCompList *CompList;
  TFDConnection *fConnection;
  int fUserNo;
  void __fastcall SetConnection( TFDConnection *Value );
protected:
  virtual void __fastcall Notification( TComponent *AComponent, TOperation Operation );
public:
  __fastcall TNNFRightsManager( TComponent* Owner );
  __fastcall ~TNNFRightsManager();
  void __fastcall LoadRights();
  void __fastcall RefreshRights( long long int AUserID );
  bool __fastcall IsRight( int ARightIndex, NNF::TIsThrow AIsThrow = NNF::TIsThrow::Quiet );
  void __fastcall AddComp( TNNFRight *aComp );
  void __fastcall EraseComp( TNNFRight *aComp );
  void __fastcall RevokeAll();
  void __fastcall SendMessage( int aMessage );
  __property bool SuperUser = {read = fSuperUser, write = fSuperUser};
  __property int UserNo = {read = fUserNo};
  __property NNF::TBoolVector Rights = { read = FRights };
__published:
  __property TFDConnection *Connection = { read = fConnection, write = SetConnection };
};

class PACKAGE TNNFRight : public TComponent {
private:
  using inherited = TComponent;
  TNNFRightsManager *fManager = nullptr;
  TNotifyEvent fOnRight;

  void __fastcall SetManager(TNNFRightsManager *Value);

protected:
  void __fastcall Notification( TComponent *AComponent, TOperation Operation );

  virtual void __fastcall DoRight()
  {
    if ( fOnRight )
      fOnRight(this);
  };

public:
  __fastcall TNNFRight( TComponent* Owner );

  void __fastcall Apply()
  {
    DoRight();
  };

__published:
  __property TNotifyEvent OnRight = { read = fOnRight, write = fOnRight };
  __property TNNFRightsManager* Manager = { read = fManager, write = SetManager };
};

// ---------------------------------------------------------------------------
#endif
