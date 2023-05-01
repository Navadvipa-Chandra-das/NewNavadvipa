// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef VCL_NNFormAdminH
#define VCL_NNFormAdminH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <Vcl.Controls.hpp>
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
#include "VCL_NNCommon.h"
#include <set>
#include <map>

class PACKAGE TNNVFormList;

class PACKAGE TNNVFormAdmin : public TComponent {
  private:
  using inherited = TComponent;
  TNNVFormList *fFormList;

  protected:
  virtual void __fastcall Notification( TComponent *AComponent,
      TOperation Operation );

  public:
  __fastcall TNNVFormAdmin( TComponent* Owner );
  __property TNNVFormList *FormList = {write = fFormList };

  __published:
};

class PACKAGE TNNVFormCounter : public std::set < TComponent* > {
  private:
  using inherited = std::set < TComponent* >;
  int fCounter;

  public:
  TNNVFormCounter();
  void __fastcall Inc( TComponent *AOwner );
  void __fastcall Dec( TComponent *AOwner );
  __property int Counter = {read = fCounter };
};

class PACKAGE TNNVFormList : public std::map < TComponent*, TNNVFormCounter > {
  private:
  using inherited = std::map < TComponent*, TNNVFormCounter >;
  TNNVFormAdmin *fFormAdmin;

  public:
  TNNVFormList();
  ~TNNVFormList();
  iterator __fastcall New( System::TMetaClass* InstanceClass, void *Reference,
      TComponent *AOwner = NULL );
  void __fastcall Delete( TComponent *AForm, TComponent *AOwner = NULL );
  void __fastcall Remove( TComponent *AForm );
  bool __fastcall Exists( TComponent *AForm );
};

extern PACKAGE TNNVFormList NNVFormList;

#endif
