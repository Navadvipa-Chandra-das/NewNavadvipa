// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef FMX_NNDispH
#define FMX_NNDispH

#include <map>
#include <list>

namespace NNF {

class PACKAGE TMultiResultElement
{
public:
  long long int PK;
  String Note;

  TMultiResultElement();
  ~TMultiResultElement();
  TMultiResultElement( const TMultiResultElement &a );
  TMultiResultElement( TMultiResultElement &&a );
  TMultiResultElement( const long long int aPK, const String &aNote );
};

using TMultiResult = PACKAGE std::list < TMultiResultElement >;

template < class Key, class T, class Compare = std::less < Key > , class Allocator = std::allocator < std::pair < const Key, T > > >
class PACKAGE Map : public std::map < Key, T, Compare, Allocator > {
private:
  using inherited = typename std::map < Key, T, Compare, Allocator >;
  bool CWFirst;

  typename inherited::iterator iCache;

public:
  Map( );
  typename inherited::iterator __fastcall FindCache( const Key& x );
  void __fastcall ResetCache( );
};

template < class Key, class T, class Compare, class Allocator >
Map < Key, T, Compare, Allocator >::Map( )
  : CWFirst( true )
{
  iCache = this->end();
}

template < class Key, class T, class Compare, class Allocator >
typename std::map < Key, T, Compare, Allocator >::iterator __fastcall Map < Key, T, Compare, Allocator >::FindCache( const Key& x )
{
  if ( CWFirst || !( ( iCache != this->end( ) ) &&
      ( ( *iCache ).first == x ) ) ) {
    iCache = this->find( x );
    CWFirst = ( iCache == this->end( ) );
  }
  return iCache;
}

template < class Key, class T, class Compare, class Allocator >
void __fastcall Map < Key, T, Compare, Allocator >::ResetCache( )
{
  CWFirst = true;
  iCache = this->end( );
}

using TIntEvent = PACKAGE void __fastcall( __closure * )( int Sender );

using TControlMap = PACKAGE Map< TControl*, bool >;

template < class SenderType, class EventType >
class PACKAGE TDispPairTemplate
{
  protected:
  virtual void __fastcall DoFirstEnter( SenderType Sender );
  virtual void __fastcall DoEnter( SenderType Sender );
  virtual void __fastcall DoExit( SenderType Sender );
  virtual void __fastcall DoLastExit( SenderType Sender );

  public:
  TDispPairTemplate( );

  bool fIsEnter;
  bool fFirstEnter;
  EventType OnFirstEnter;
  EventType OnEnter;
  EventType OnExit;
  EventType OnLastExit;

  void __fastcall DoTryFirstEnter( SenderType Sender );
  void __fastcall DoTryEnter( SenderType Sender );
  void __fastcall DoTryExit( SenderType Sender );
  void __fastcall DoTryLastExit( SenderType Sender );
};

template < class SenderType, class EventType >
TDispPairTemplate < SenderType, EventType >::TDispPairTemplate( )
  : OnFirstEnter( nullptr )
  , OnEnter( nullptr )
  , OnExit( nullptr )
  , OnLastExit( nullptr )
  , fIsEnter( false )
  , fFirstEnter( false ) {
}

template < class SenderType, class EventType >
void __fastcall TDispPairTemplate < SenderType, EventType >::DoFirstEnter( SenderType Sender ) {
  if ( OnFirstEnter )
    OnFirstEnter( Sender );
}

template < class SenderType, class EventType >
void __fastcall TDispPairTemplate < SenderType, EventType >::DoEnter( SenderType Sender ) {
  if ( OnEnter )
    OnEnter( Sender );
}

template < class SenderType, class EventType >
void __fastcall TDispPairTemplate < SenderType, EventType >::DoExit( SenderType Sender ) {
  if ( OnExit )
    OnExit( Sender );
}

template < class SenderType, class EventType >
void __fastcall TDispPairTemplate < SenderType, EventType >::DoLastExit( SenderType Sender ) {
  if ( OnLastExit )
    OnLastExit( Sender );
}

template < class SenderType, class EventType >
void __fastcall TDispPairTemplate < SenderType, EventType >::DoTryFirstEnter( SenderType Sender ) {
  if ( !fFirstEnter ) {
    fFirstEnter = true;
    DoFirstEnter( Sender );
  }
}

template < class SenderType, class EventType >
void __fastcall TDispPairTemplate < SenderType, EventType >::DoTryEnter( SenderType Sender ) {
  DoTryFirstEnter( Sender );
  if ( !fIsEnter ) {
    fIsEnter = true;
    DoEnter( Sender );
  }
}

template < class SenderType, class EventType >
void __fastcall TDispPairTemplate < SenderType, EventType >::DoTryExit( SenderType Sender ) {
  if ( fIsEnter ) {
    fIsEnter = false;
    DoExit( Sender );
  }
}

template < class SenderType, class EventType >
void __fastcall TDispPairTemplate < SenderType, EventType >::DoTryLastExit( SenderType Sender ) {
  DoTryExit( Sender );
  if ( fFirstEnter ) {
    fFirstEnter = false;
    DoLastExit( Sender );
  }
}

// TMapDispatcher

template < class Key, class T, class Compare = std::less < Key >, class Allocator = std::allocator < std::pair < const Key, T > > >
class PACKAGE TMapDispatcher : public Map < Key, T, Compare, Allocator >
{
private:
  using inherited = /*typename*/ Map< Key, T, Compare, Allocator >;

public:
  TMapDispatcher( );
  ~TMapDispatcher( );
  typename inherited::iterator current;
  void __fastcall Reset( ); // сброс текущего объекта
  void __fastcall Reset( Key index ); // сброс объекта index
  void __fastcall ResetAll( );
  void __fastcall ResetAllWithoutCurrent( );
  void __fastcall MakeCurrent( Key index );
  void __fastcall erase_item( typename inherited::iterator i );
};

template < class Key, class T, class Compare, class Allocator >
TMapDispatcher < Key, T, Compare, Allocator >::TMapDispatcher( )
{
  current = this->end( );
}

template < class Key, class T, class Compare, class Allocator >
TMapDispatcher < Key, T, Compare, Allocator >::~TMapDispatcher( )
{
  for ( typename inherited::iterator i = this->begin( );
  i != this->end( ); i++ )
    delete( *i ).second;
}

template < class Key, class T, class Compare, class Allocator >
void __fastcall TMapDispatcher < Key, T, Compare, Allocator >::Reset( )
{
  if ( current != this->end( ) )
    ( *current ).second->DoTryLastExit( ( *current ).first );
  current = this->end( );
}

template < class Key, class T, class Compare, class Allocator >
void __fastcall TMapDispatcher < Key, T, Compare, Allocator >::Reset( Key index )
{
  typename inherited::iterator i = this->find( index );
  if ( ( i != this->end( ) ) ) {
    ( *i ).second->DoTryLastExit( ( *i ).first );
    if ( i == current )
      current = this->end( );
  }
}

template < class Key, class T, class Compare, class Allocator >
void __fastcall TMapDispatcher < Key, T, Compare, Allocator >::MakeCurrent( Key index )
{
  typename inherited::iterator i_new = this->find( index );
  if ( ( i_new != current ) && ( i_new != this->end( ) ) ) {
    if ( current != this->end( ) )
      ( *current ).second->DoTryExit( ( *current ).first );
    current = i_new;
    ( *i_new ).second->DoTryEnter( ( *i_new ).first );
  }
}

template < class Key, class T, class Compare, class Allocator >
void __fastcall TMapDispatcher < Key, T, Compare, Allocator >::erase_item( typename inherited::iterator i )
{
  delete( *i ).second;
  this->erase( i );
}

template < class Key, class T, class Compare, class Allocator >
void __fastcall TMapDispatcher < Key, T, Compare, Allocator >::ResetAll( )
{
  if ( this->empty( ) )
    return;
  for ( typename inherited::iterator i = this->begin( );
  i != this->end( ); i++ )
    ( *i ).second->DoTryLastExit( ( *i ).first );
  current = this->end( );
}

template < class Key, class T, class Compare, class Allocator >
void __fastcall TMapDispatcher < Key, T, Compare, Allocator >::ResetAllWithoutCurrent()
{
  if ( this->empty() )
    return;
  for ( typename inherited::iterator i = this->begin( );
  i != this->end( ); i++ )
    if ( i != current )
      ( *i ).second->DoTryLastExit( ( *i ).first );
}

using TDispPair = TDispPairTemplate < int, TIntEvent >;

class PACKAGE TControlPair : public TDispPairTemplate < TObject*, TNotifyEvent >
{
private:
  using inherited = TDispPairTemplate < TObject*, TNotifyEvent >;

  protected:
  virtual void __fastcall DoEnter( TObject *Sender );
  virtual void __fastcall DoExit( TObject *Sender );

public:
  TControlPair( );
};

class PACKAGE TDispMap : public TMapDispatcher < int, TDispPair* >
{
private:
  using inherited = TMapDispatcher< int, TDispPair* >;

public:
  iterator __fastcall Add( int index );
  TDispMap( );
};

class PACKAGE TControlList : public TMapDispatcher < TControl*, TControlPair* >
{
  private:
  using inherited = TMapDispatcher < TControl*, TControlPair* >;

  public:
  TControlList( );
  iterator __fastcall Add( TControl* index );
};

template < class Key, class T, class Compare = std::less < Key >, class Allocator = std::allocator < std::pair < const Key, T > > >
class PACKAGE TBookmarks : public std::map < Key, T, Compare, Allocator >
{
private:
  using inherited = typename std::map < Key, T, Compare, Allocator >;

public:
  TBookmarks( );
  void __fastcall GoTo( Key index );
};

template < class Key, class T, class Compare, class Allocator >
TBookmarks < Key, T, Compare, Allocator >::TBookmarks( ) : inherited()
{
}

template < class Key, class T, class Compare, class Allocator >
void __fastcall TBookmarks < Key, T, Compare, Allocator >::GoTo( Key index )
{
  typename inherited::iterator i = this->find( index );
  if ( i != this->end( ) )
    ( *i ).second.Execute( );
}

}

#endif
