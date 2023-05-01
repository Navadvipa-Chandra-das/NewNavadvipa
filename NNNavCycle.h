// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef NNNavCycleH
#define NNNavCycleH
//---------------------------------------------------------------------------

#include <list>

namespace NN {

template < class TClientType, class TActiveProc >
class PACKAGE TNavCycle : public std::list< TClientType >
{
private:
  typedef std::list< TClientType > inherited;
  typename inherited::iterator Current;
  bool Work;
public:
  TActiveProc ActiveProc;
  TNavCycle( const TActiveProc &aActiveProc );
  void __fastcall Add( TClientType Client );
  void __fastcall Remove( TClientType Client );
  void __fastcall Prev();
  void __fastcall Next();
  void __fastcall Clear();
  void __fastcall IncCurrent();
  void __fastcall DecCurrent();
};

template < class TClientType, class TActiveProc >
TNavCycle< TClientType, TActiveProc >::TNavCycle( const TActiveProc &aActiveProc )
  : inherited()
  , Work( false )
  , ActiveProc( aActiveProc )
{
  Current = this->end();
}


template < class TClientType, class TActiveProc >
void __fastcall TNavCycle< TClientType, TActiveProc >::Add( TClientType Client )
{
  if ( !Work ) {
    Current = std::find( this->begin(), this->end(), Client );
    if ( Current == this->end() ) {
      this->push_back( Client );
      Current = --this->end();
    }
  }
}

template < class TClientType, class TActiveProc >
void __fastcall TNavCycle< TClientType, TActiveProc >::Remove( TClientType Client )
{
  if ( Application->Terminated )
    return;
  this->remove( Client );
  Current = this->empty() ? this->end() : --this->end();
}

template < class TClientType, class TActiveProc >
void __fastcall TNavCycle< TClientType, TActiveProc >::Clear()
{
  this->clear();
  Current = this->end();
}

template < class TClientType, class TActiveProc >
void __fastcall TNavCycle< TClientType, TActiveProc >::Prev()
{
  DecCurrent();
  if ( Current != this->end() ) {
    Work = true;
    try {
      ActiveProc( (*Current) );
    } __finally {
      Work = false;
    }
  }
}

template < class TClientType, class TActiveProc >
void __fastcall TNavCycle< TClientType, TActiveProc >::Next()
{
  IncCurrent();
  if ( Current != this->end() ) {
    Work = true;
    try {
      ActiveProc( (*Current) );
    } __finally {
      Work = false;
    }
  }
}

template < class TClientType, class TActiveProc >
void __fastcall TNavCycle< TClientType, TActiveProc >::IncCurrent()
{
  if ( !this->empty() ) {
    if ( Current == --this->end() )
      Current = this->begin();
    else
      ++Current;
  }
}

template < class TClientType, class TActiveProc >
void __fastcall TNavCycle< TClientType, TActiveProc >::DecCurrent()
{
  if ( !this->empty() ) {
    if ( Current == this->begin() )
      Current = --this->end();
    else
      --Current;
  }
}

}

#endif