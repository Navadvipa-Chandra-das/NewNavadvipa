// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef FMX_NNFormAdminH
#define FMX_NNFormAdminH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <FMX.Controls.hpp>
#include <System.Classes.hpp>
#include <FMX.Forms.hpp>
#include "FMX_NNCommon.h"
#include <set>
#include <map>

class PACKAGE TNNFFormList;

class PACKAGE TNNFFormAdmin : public TComponent {
  private:
  using inherited = TComponent;
  TNNFFormList *fFormList;

  protected:
  virtual void __fastcall Notification( TComponent *AComponent,
      TOperation Operation );

  public:
  __fastcall TNNFFormAdmin( TComponent* Owner );
  __property TNNFFormList *FormList = {write = fFormList };

  __published:
};

class PACKAGE TNNFFormCounter : public std::set < TComponent* > {
  private:
  using inherited = std::set < TComponent* >;
  int fCounter;

  public:
  TNNFFormCounter();
  void __fastcall Inc( TComponent *AOwner );
  void __fastcall Dec( TComponent *AOwner );
  __property int Counter = {read = fCounter };
};

class PACKAGE TNNFFormList : public std::map < TComponent*, TNNFFormCounter > {
  private:
  using inherited = std::map < TComponent*, TNNFFormCounter >;
  TNNFFormAdmin *fFormAdmin;

  public:
  TNNFFormList();
  ~TNNFFormList();
  iterator __fastcall New( System::TMetaClass* InstanceClass, void *Reference,
      TComponent *AOwner = NULL );
  void __fastcall Delete( TComponent *AForm, TComponent *AOwner = NULL );
  void __fastcall Remove( TComponent *AForm );
  bool __fastcall Exists( TComponent *AForm );
};

extern PACKAGE TNNFFormList NNFFormList;

#endif
