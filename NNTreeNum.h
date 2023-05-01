// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef NNTreeNumH
#define NNTreeNumH

#include <list>

template <class T, class ParentType, class Allocator = std::allocator< std::pair< ParentType, T > > >
class PACKAGE TNNTreeNumerator : public std::list< std::pair< ParentType, T >, Allocator >
{
  private:
    bool IsComplete;
    typedef typename std::list< std::pair< ParentType, T >, Allocator > inherited;
    String __fastcall GetText();
  public:
    TNNTreeNumerator( bool IsComplete_ )
      : IsComplete( IsComplete_ )
    {
    };
    TNNTreeNumerator()
      : IsComplete( true )
    {
    };
    void __fastcall AddParent( ParentType ParentID );
    __property String Text = { read = GetText };
};

template <class T, class ParentType, class Allocator = std::allocator< std::pair< ParentType, T > > >
void __fastcall TNNTreeNumerator< T, ParentType, Allocator >::AddParent( ParentType ParentID )
{
  bool B = false;
  iterator i = begin();
  for ( ; i != end(); i++ )
    if ( (*i).first == ParentID ) {
      B = true;
      break;
    }
  if ( !B ) {
    typename T N = T(); // значение по умолчанию для типа T
    push_back( std::make_pair( ParentID, N ) );
  } else {
    iterator j = i;
    ++j;
    erase( j, end() );
  }
  (*(rbegin())).second++;
}

template <class T, class ParentType, class Allocator = std::allocator< std::pair< ParentType, T > > >
String __fastcall TNNTreeNumerator< T, ParentType, Allocator >::GetText()
{
  String S;
  bool B = true;
  for ( iterator i = begin(); i != end(); i++ ) {
    if ( !B ) S = S + (String)'.';
    S = S + String( (*i).second );
    if ( B ) B = false;
  }
  if ( !IsComplete ) {
    int N = S.Pos( "." );
    if ( N != 0 )
      S = S.SubString( N + 1, S.Length() - N );
    else
      S = "";
  }
  return S;
}

//typedef PACKAGE TNNTreeNumerator< int, String > TCWStrNumerator;
typedef PACKAGE TNNTreeNumerator< int, double > TNNDoubleNumerator;

#endif
