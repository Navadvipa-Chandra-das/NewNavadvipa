// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNFormAdmin.h"
#include "VCL_NNCommon.h"
#include "VCL_NNFmRes.h"
#include <memory>

#pragma package(smart_init)

// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck( TNNVFormAdmin * ) {
  new TNNVFormAdmin( NULL );
}

// ---------------------------------------------------------------------------
__fastcall TNNVFormAdmin::TNNVFormAdmin( TComponent* Owner )
    : inherited( Owner ) {
}
// ---------------------------------------------------------------------------

void __fastcall TNNVFormAdmin::Notification( TComponent *AComponent,
    TOperation Operation ) {
  inherited::Notification( AComponent, Operation );
  if ( Operation == opRemove )
    fFormList->Remove( AComponent );
}

// ---------------------------------------------------------------------------

TNNVFormCounter::TNNVFormCounter() : inherited(), fCounter( 0 ) {
}

void __fastcall TNNVFormCounter::Inc( TComponent *AOwner ) {
  if ( AOwner ) {
    if ( !count( AOwner ) ) {
      fCounter++;
      insert( AOwner );
    }
  }
  else
    fCounter++;
}

void __fastcall TNNVFormCounter::Dec( TComponent *AOwner ) {
  if ( AOwner ) {
    if ( count( AOwner ) ) {
      fCounter--;
      erase( AOwner );
    }
  }
  else
    fCounter--;
}

// ---------------------------------------------------------------------------

TNNVFormList::TNNVFormList() : inherited() {
  fFormAdmin = new TNNVFormAdmin( NULL );
  fFormAdmin->FormList = this;
}

TNNVFormList::~TNNVFormList() {
  delete fFormAdmin;
}

TNNVFormList::iterator __fastcall TNNVFormList::New
    ( System::TMetaClass* InstanceClass, void *Reference, TComponent *AOwner ) {
  if ( InstanceClass->InheritsFrom( __classid( TCustomForm ) ) ) {
    if ( !NNV::FormExists( InstanceClass, Reference ) ) {
      std::unique_ptr < NNV::TCursorMagic > cm
          ( new NNV::TCursorMagic( crHourGlass ) );
      Application->CreateForm( InstanceClass, Reference );
    }
  }
  else if ( InstanceClass->InheritsFrom( __classid( TDataModule ) ) ) {
    if ( !NNV::DMExists( InstanceClass, Reference ) ) {
      std::unique_ptr < NNV::TCursorMagic > cm
          ( new NNV::TCursorMagic( crHourGlass ) );
      Application->CreateForm( InstanceClass, Reference );
    }
  }
  iterator i =
      find( ( ( TComponent* )( ( *( ( TComponent * * )( Reference ) ) ) ) ) );
  if ( i == end() ) {
    i = insert( std::make_pair
        ( ( ( TComponent* )( ( *( ( TComponent * * )( Reference ) ) ) ) ),
        TNNVFormCounter() ) ).first;
    ( ( TComponent* )( ( *( ( TComponent** )( Reference ) ) ) ) )
        ->FreeNotification( fFormAdmin );
  }
  ( *i ).second.Inc( AOwner );
  return i;
}

void __fastcall TNNVFormList::Delete( TComponent *AForm, TComponent *AOwner ) {
  if ( empty() )
    return;
  TComponent *C;
  iterator i = find( AForm );
  if ( i != end() ) {
    ( *i ).second.Dec( AOwner );
    if ( ( *i ).second.Counter == 0 ) {
      std::unique_ptr < NNV::TCursorMagic > cm
          ( new NNV::TCursorMagic( crHourGlass ) );
      C = ( *i ).first;
      erase( i );
      delete C;
    }
  }
}

void __fastcall TNNVFormList::Remove( TComponent *AForm ) {
  if ( empty() )
    return;
  iterator i = find( AForm );
  if ( i != end() )
    erase( i );
}

bool __fastcall TNNVFormList::Exists( TComponent *AForm ) {
  return find( AForm ) != end();
}

TNNVFormList NNVFormList;

