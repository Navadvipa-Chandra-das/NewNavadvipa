// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <fmx.h>
#pragma hdrstop

#include "FMX_NNDisp.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

namespace NNF {

TMultiResultElement::TMultiResultElement()
  : PK( 0 )
  , Note()
{
}

TMultiResultElement::~TMultiResultElement()
{
}

TMultiResultElement::TMultiResultElement( const TMultiResultElement &a )
  : PK( a.PK )
  , Note( a.Note )
{
}

TMultiResultElement::TMultiResultElement( TMultiResultElement &&a )
  : PK( a.PK )
  , Note( a.Note )
{
}

TMultiResultElement::TMultiResultElement( const long long int aPK, const String &aNote)
  : PK( aPK )
  , Note( aNote )
{
}

TControlPair::TControlPair()
{
}

void __fastcall TControlPair::DoEnter( TObject *Sender )
{
  ((TControl*)Sender)->Visible = true;
  inherited::DoEnter( Sender );
}

void __fastcall TControlPair::DoExit( TObject *Sender )
{
  ((TControl*)Sender)->Visible = false;
  inherited::DoExit( Sender );
}

TDispMap::TDispMap() : inherited() {
}

TDispMap::iterator __fastcall TDispMap::Add( int index )
{
  iterator i = find( index );
  if ( i == end() )
    i = insert( std::make_pair( index, new TDispPair ) ).first;
  return i;
}

// TControlList

TControlList::TControlList() : inherited() {
}

TControlList::iterator __fastcall TControlList::Add( TControl* index )
{
  iterator i = find( index );
  index->Visible = false;
  if ( i == end() )
    i = insert( std::make_pair( index, new TControlPair() ) ).first;
  return i;
}

}
