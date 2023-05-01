// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <fmx.h>
#pragma hdrstop

#include "FMX_NNFormAdmin.h"
#include "FMX_NNCommon.h"
#include "FMX_NNFmRes.h"
#include <memory>

#pragma package(smart_init)

// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck( TNNFFormAdmin * ) {
  new TNNFFormAdmin( NULL );
}

// ---------------------------------------------------------------------------
__fastcall TNNFFormAdmin::TNNFFormAdmin( TComponent* Owner )
    : inherited( Owner ) {
}
// ---------------------------------------------------------------------------

void __fastcall TNNFFormAdmin::Notification( TComponent *AComponent,
    TOperation Operation )
{
  inherited::Notification( AComponent, Operation );
  if ( Operation == opRemove )
    fFormList->Remove( AComponent );
}

// ---------------------------------------------------------------------------

TNNFFormCounter::TNNFFormCounter() : inherited(), fCounter( 0 ) {
}

void __fastcall TNNFFormCounter::Inc( TComponent *AOwner ) {
  if ( AOwner ) {
    if ( !count( AOwner ) ) {
      fCounter++;
      insert( AOwner );
    }
  }
  else
    fCounter++;
}

void __fastcall TNNFFormCounter::Dec( TComponent *AOwner ) {
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

TNNFFormList::TNNFFormList() : inherited() {
  fFormAdmin = new TNNFFormAdmin( NULL );
  fFormAdmin->FormList = this;
}

TNNFFormList::~TNNFFormList() {
  delete fFormAdmin;
}

TNNFFormList::iterator __fastcall TNNFFormList::New
    ( System::TMetaClass* InstanceClass, void *Reference, TComponent *AOwner ) {
  if ( InstanceClass->InheritsFrom( __classid( TCustomForm ) ) ) {
    if ( !NNF::FormExists( InstanceClass, Reference ) ) {
      std::unique_ptr < NNF::TCursorMagic > cm
          ( new NNF::TCursorMagic( crHourGlass ) );
      Application->CreateForm( InstanceClass, Reference );
    }
  }
  else if ( InstanceClass->InheritsFrom( __classid( TDataModule ) ) ) {
    if ( !NNF::DMExists( InstanceClass, Reference ) ) {
      std::unique_ptr < NNF::TCursorMagic > cm
          ( new NNF::TCursorMagic( crHourGlass ) );
      Application->CreateForm( InstanceClass, Reference );
    }
  }
  iterator i =
      find( ( ( TComponent* )( ( *( ( TComponent * * )( Reference ) ) ) ) ) );
  if ( i == end() ) {
    i = insert( std::make_pair
        ( ( ( TComponent* )( ( *( ( TComponent * * )( Reference ) ) ) ) ),
        TNNFFormCounter() ) ).first;
    ( ( TComponent* )( ( *( ( TComponent** )( Reference ) ) ) ) )
        ->FreeNotification( fFormAdmin );
  }
  ( *i ).second.Inc( AOwner );
  return i;
}

void __fastcall TNNFFormList::Delete( TComponent *AForm, TComponent *AOwner ) {
  if ( empty() )
    return;
  TComponent *C;
  iterator i = find( AForm );
  if ( i != end() ) {
    ( *i ).second.Dec( AOwner );
    if ( ( *i ).second.Counter == 0 ) {
      std::unique_ptr < NNF::TCursorMagic > cm
          ( new NNF::TCursorMagic( crHourGlass ) );
      C = ( *i ).first;
      erase( i );
      delete C;
    }
  }
}

void __fastcall TNNFFormList::Remove( TComponent *AForm ) {
  if ( empty() )
    return;
  iterator i = find( AForm );
  if ( i != end() )
    erase( i );
}

bool __fastcall TNNFFormList::Exists( TComponent *AForm ) {
  return find( AForm ) != end();
}

TNNFFormList NNFFormList;

