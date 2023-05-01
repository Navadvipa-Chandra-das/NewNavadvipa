//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop

#include "VCL_NNGolovolomka15.h"
#include <algorithm>
#include <vector>
#include <random>

#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck( TNNVGolovolomka15 * )
{
  new TNNVGolovolomka15( NULL) ;
}
//---------------------------------------------------------------------------

__fastcall TNNVGolovolomka15::TNNVGolovolomka15( TComponent* Owner )
  : inherited( Owner )
{
  TControlStyle c = ControlStyle;
  c = c >> csSetCaption;
  ControlStyle = c;

  TFontStyles F = Font->Style;
  F = F << fsBold;
  Font->Style = F;

  BevelInner = bvNone;
  BevelOuter = bvNone;

  Color = clWhite;

  randomize();
  PrepareKostyahkaSize();
  CreateKostyahki();
}
//---------------------------------------------------------------------------

void __fastcall TNNVGolovolomka15::CreateKostyahki()
{
  if ( ComponentState.Contains( csDesigning ) )
    return;

  TPanel *P;
  int N = 0;
  inherited::Loaded();
  for ( int I = 0; I < 4; ++I ) {
    for ( int J = 0; J < 4; ++J ) {
      if ( N < 15 ) {
        P = new TPanel( this );

        P->Height           = KostyashkaSize;
        P->Width            = KostyashkaSize;
        P->Caption          = IntToStr( ++N );
        P->Left             = J * KostyashkaSize;
        P->Top              = I * KostyashkaSize;
        P->BevelInner       = bvLowered;
        P->BevelWidth       = 2;
        P->BorderWidth      = 2;
        P->ParentBackground = false;

        P->OnClick    = KostyashkaClick;
        P->Parent     = this;
      } else {
        EmptyHeight = KostyashkaSize;
        EmptyWidth  = KostyashkaSize;
        EmptyLeft   = J * KostyashkaSize;
        EmptyTop    = I * KostyashkaSize;
      }
    }
  }
}

void __fastcall TNNVGolovolomka15::StartPosition()
{
  int N = 0;
  TPanel *P;
  for ( int I = 0; I < 4; ++I ) {
    for ( int J = 0; J < 4; ++J ) {
      if ( ++N < 16 ) {
        P = GetKostyshka( N );

        P->Left = J * KostyashkaSize;
        P->Top  = I * KostyashkaSize;
      } else {
        EmptyLeft = J * KostyashkaSize;
        EmptyTop  = I * KostyashkaSize;
      }
    }
  }
}

TPanel* __fastcall TNNVGolovolomka15::GetKostyshka( int N )
{
  int L = ComponentCount;
  String SN = IntToStr( N );

  TPanel *P = nullptr;
  for ( int I = 0; I < L; ++I ) {
    P = dynamic_cast< TPanel* >( Components[ I ] );
    if ( P && P->Caption == SN )
      break;
    else
      P = nullptr;
  }
  return P;
}

void __fastcall TNNVGolovolomka15::Resize()
{
  inherited::Resize();

  PrepareKostyahkaSize();

  int L = ComponentCount;
  if ( L == 0 )
    return;

  TPanel *P;
  for ( int I = 0; I < L; ++I ) {
    P = dynamic_cast< TPanel* >( Components[ I ] );
    if ( P ) {
      P->Left   = P->Left / P->Width  * KostyashkaSize;
      P->Top    = P->Top  / P->Height * KostyashkaSize;
      P->Width  = KostyashkaSize;
      P->Height = KostyashkaSize;
    }
  }
  EmptyLeft   = EmptyLeft / EmptyWidth  * KostyashkaSize;
  EmptyTop    = EmptyTop  / EmptyHeight * KostyashkaSize;
  EmptyWidth  = KostyashkaSize;
  EmptyHeight = KostyashkaSize;
}

void __fastcall TNNVGolovolomka15::PrepareKostyahkaSize()
{
  int N = std::min( Width, Height );
  KostyashkaSize = N / 4;
}

void __fastcall TNNVGolovolomka15::SetKostyashkaSize( int Value )
{
  if ( FKostyashkaSize != Value ) {
    FKostyashkaSize = Value;
    Font->Size = OptimalFontSize();
  }
}

int __fastcall TNNVGolovolomka15::OptimalFontSize()
{
  int R;
  if ( KostyashkaSize < 20 )
    R = 8;
  else if ( KostyashkaSize < 40 )
    R = 12;
  else if ( KostyashkaSize < 80 )
    R = 16;
  else if ( KostyashkaSize < 140 )
    R = 24;
  else if ( KostyashkaSize < 200 )
    R = 32;
  else
    R = 64;
  return R;
}

void __fastcall TNNVGolovolomka15::Loaded()
{
  inherited::Loaded();
  if ( IsMix )
    Mix( MixCount );
}

void __fastcall TNNVGolovolomka15::KostyashkaClick( TObject *Sender )
{
  TPanel *P = dynamic_cast< TPanel* >( Sender );
  if ( ValidHod( P ) ) {
    int N = P->Left;
    P->Left = EmptyLeft;
    EmptyLeft = N;
    N = P->Top;
    P->Top = EmptyTop;
    EmptyTop = N;

    if ( !IsMixWork && IsStartPosition() )
      DoVijaya();
  }
}

void __fastcall TNNVGolovolomka15::Mix( unsigned int AMixCount, unsigned int MS )
{
  int N, VS, CC = ComponentCount;

  if ( CC == 0 )
    return;

  if ( AMixCount == 0 )
    AMixCount = MixCount;

  std::vector< TPanel* > V;
  TPanel *P, *OldP = nullptr;

  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen( rd() ); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> R0_1( 0, 1 ), R0_2( 0, 2 ), R0_3( 0, 3 );

  IsMixWork = true;
  for ( int I = 1; I <= AMixCount; ++I ) {
    V.clear();
    for ( int J = 0; J < CC; ++J ) {
      P = dynamic_cast< TPanel* >( Components[ J ] );
      if ( ValidHod( P ) )
        V.push_back( P );
    }
    VS = V.size();
    assert( VS > 1 && VS < 5 );
    P = nullptr;
    while ( !P ) {
      switch ( VS ) {
      case 2 :
        N = R0_1( gen );
        break;
      case 3 :
        N = R0_2( gen );
        break;
      case 4 :
        N = R0_3( gen );
        break;
      }
      P = V[ N ];
      if ( P == OldP )
        P = nullptr;
    }
    KostyashkaClick( P );
    OldP = P;
    if ( MS > 0 )
      Sleep( MS );
    Application->ProcessMessages();
    IsMixWork = false;
  }
}

bool __fastcall TNNVGolovolomka15::ValidHod( TPanel *P )
{
  if ( P ) {
    int AL = std::abs( P->Left - EmptyLeft )
      , AT = std::abs( P->Top  - EmptyTop  );
    return std::abs( AL - AT ) == KostyashkaSize && AL <= KostyashkaSize && AT <= KostyashkaSize;
  } else
    return false;
}

void __fastcall TNNVGolovolomka15::DoVijaya()
{
  if ( FOnVijaya )
    FOnVijaya( this );
}

bool __fastcall TNNVGolovolomka15::IsStartPosition()
{
  int N = 0;
  TPanel *P;
  for ( int I = 0; I < 4; ++I ) {
    for ( int J = 0; J < 4; ++J ) {
      if ( ++N < 16 ) {
        P = GetKostyshka( N );
        if ( P->Left != J * KostyashkaSize ||
             P->Top  != I * KostyashkaSize )
          return false;
      }
    }
  }
  return true;
}
//---------------------------------------------------------------------------

namespace Vcl_nngolovolomka15
{
  void __fastcall PACKAGE Register()
  {
    TComponentClass classes[ 1 ] = { __classid( TNNVGolovolomka15 ) };
    RegisterComponents( L"VCL New Navadvipa", classes, 0 );
  }
}

