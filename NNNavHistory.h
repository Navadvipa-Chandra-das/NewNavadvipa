// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef NNNavHistoryH
#define NNNavHistoryH
//---------------------------------------------------------------------------

#include <list>

namespace NN {

template < class TClientType, class TActiveProc >
class PACKAGE TNavHistory : public std::list< TClientType >
{
private:
  typedef std::list< TClientType > inherited;
  typename inherited::iterator Current;
  bool Work;
public:
  unsigned int MaxSize;
  TActiveProc ActiveProc;
  TNavHistory( unsigned int aMaxSize
             , const TActiveProc &aActiveProc );
  void __fastcall Add( TClientType Client );
  void __fastcall Remove( TClientType Client );
  void __fastcall Prev();
  void __fastcall Next();
  void __fastcall Clear();
  bool __fastcall Bof();
  bool __fastcall Eof();
};

template < class TClientType, class TActiveProc >
TNavHistory< TClientType, TActiveProc >::TNavHistory( unsigned int aMaxSize
                                                    , const TActiveProc &aActiveProc )
  : Work( false )
  , MaxSize( aMaxSize )
  , ActiveProc( aActiveProc )
{
  Current = this->end();
}

template < class TClientType, class TActiveProc >
void __fastcall TNavHistory< TClientType, TActiveProc >::Add( TClientType Client )
{
  if ( !Work ) {
    bool B = false;
    if ( Current != this->end() ) {
      B = (*Current) == Client;
      this->erase( ++Current, this->end() );
    }
    if ( !B ) {
      this->push_back( Client );
      if ( this->size() > MaxSize ) this->pop_front();
    }
    Current = --this->end();
  }
}

template < class TClientType, class TActiveProc >
void __fastcall TNavHistory< TClientType, TActiveProc >::Remove( TClientType Client )
{
  if ( Application->Terminated )
    return;
  this->remove( Client );
  Current = this->empty() ? this->end() : --this->end();
}

template < class TClientType, class TActiveProc >
void __fastcall TNavHistory< TClientType, TActiveProc >::Clear()
{
  this->clear();
  Current = this->end();
}

template < class TClientType, class TActiveProc >
void __fastcall TNavHistory< TClientType, TActiveProc >::Prev()
{
  if ( !Bof() ) {
    Work = true;
    try {
      ActiveProc( (*(--Current)) );
    } __finally {
      Work = false;
    }
  }
}

template < class TClientType, class TActiveProc >
void __fastcall TNavHistory< TClientType, TActiveProc >::Next()
{
  if ( !Eof() ) {
    Work = true;
    try {
      ActiveProc( (*(++Current)) );
    } __finally {
      Work = false;
    }
  }
}

template < class TClientType, class TActiveProc >
bool __fastcall TNavHistory< TClientType, TActiveProc >::Bof()
{
  return this->empty() ? true : Current == this->begin();
}

template < class TClientType, class TActiveProc >
bool __fastcall TNavHistory< TClientType, TActiveProc >::Eof()
{
  return this->empty() ? true : Current == --this->end();
}

}

#endif
