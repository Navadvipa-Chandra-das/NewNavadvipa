//---------------------------------------------------------------------------
#include <fmx.h>

#pragma hdrstop

#include "FMX_NNGolovolomka15.h"
#include <algorithm>
#include <vector>
#include <random>

#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck( TNNFGolovolomka15 * )
{
  new TNNFGolovolomka15( NULL) ;
}
//---------------------------------------------------------------------------

__fastcall TNNFGolovolomka15::TNNFGolovolomka15( TComponent* Owner )
  : inherited( Owner )
{
  PrepareKostyahkaSize();
  CreateKostyahki();
}
//---------------------------------------------------------------------------

void __fastcall TNNFGolovolomka15::CreateKostyahki()
{
  if ( ComponentState.Contains( csDesigning ) )
    return;

  TPanel *P;
  int N = 0;
  for ( int I = 0; I < 4; ++I ) {
    for ( int J = 0; J < 4; ++J ) {
      if ( N < 15 ) {
        P = CreateKostyahka( ++N );

        P->Position->X = J * KostyashkaSize;
        P->Position->Y = I * KostyashkaSize;
      } else {
        EmptyHeight = KostyashkaSize;
        EmptyWidth  = KostyashkaSize;
        EmptyLeft   = J * KostyashkaSize;
        EmptyTop    = I * KostyashkaSize;
      }
    }
  }
}

TPanel* __fastcall TNNFGolovolomka15::CreateKostyahka( int N )
{
  TPanel *P = new TPanel( this );
  TLabel *L = new TLabel( P );

  L->Text     = IntToStr( N );
  L->Align    = TAlignLayout::Client;
  L->AutoSize = true;
  L->OnClick  = KostyashkaClick;

  P->Height   = KostyashkaSize;
  P->Width    = KostyashkaSize;

  P->OnClick  = KostyashkaClick;
  P->Parent   = this;
  L->StyledSettings = L->StyledSettings >> TStyledSetting::Size >> TStyledSetting::Style;
  L->TextSettings->HorzAlign = TTextAlign::Center;
  L->TextSettings->VertAlign = TTextAlign::Center;
  L->TextSettings->Font->Style = L->TextSettings->Font->Style << fsBold;
  L->Parent   = P;

  return P;
}

void __fastcall TNNFGolovolomka15::StartPosition()
{
  int N = 0;
  TPanel *P;
  for ( int I = 0; I < 4; ++I ) {
    for ( int J = 0; J < 4; ++J ) {
      if ( ++N < 16 ) {
        P = GetKostyshka( N );

        P->Position->X = J * KostyashkaSize;
        P->Position->Y = I * KostyashkaSize;
      } else {
        EmptyLeft = J * KostyashkaSize;
        EmptyTop  = I * KostyashkaSize;
      }
    }
  }
}

TPanel* __fastcall TNNFGolovolomka15::GetKostyshka( int N )
{
  int L = ComponentCount;
  String SN = IntToStr( N );

  TPanel *P = nullptr;
  TLabel *LA;
  for ( int I = 0; I < L; ++I ) {
    P = dynamic_cast< TPanel* >( Components[ I ] );
    if ( P  ) {
      LA = dynamic_cast< TLabel* >( P->Components[ 0 ] );
      if ( LA->Text == SN )
        break;
      else
        P = nullptr;
    }
  }
  return P;
}

void __fastcall TNNFGolovolomka15::Resize()
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
      P->Position->X = P->Position->X / P->Width  * KostyashkaSize;
      P->Position->Y = P->Position->Y / P->Height * KostyashkaSize;
      P->Width  = KostyashkaSize;
      P->Height = KostyashkaSize;
    }
  }
  EmptyLeft   = EmptyLeft / EmptyWidth  * KostyashkaSize;
  EmptyTop    = EmptyTop  / EmptyHeight * KostyashkaSize;
  EmptyWidth  = KostyashkaSize;
  EmptyHeight = KostyashkaSize;
}

void __fastcall TNNFGolovolomka15::PrepareKostyahkaSize()
{
  int N = std::min( Width, Height );
  KostyashkaSize = N / 4;
}

void __fastcall TNNFGolovolomka15::SetKostyashkaSize( int Value )
{
  if ( FKostyashkaSize != Value ) {
    FKostyashkaSize = Value;

    int L = ComponentCount;

    TPanel *PA;
    TLabel *LA;
    for ( int I = 0; I < L; ++I ) {
      PA = dynamic_cast< TPanel* >( Components[ I ] );
      if ( PA ) {
        LA = dynamic_cast< TLabel* >( PA->Components[ 0 ] );
        if ( LA )
          LA->TextSettings->Font->Size = OptimalFontSize();
      }
    }
  }
}

int __fastcall TNNFGolovolomka15::OptimalFontSize()
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

void __fastcall TNNFGolovolomka15::Loaded()
{
  inherited::Loaded();
  if ( IsMix )
    Mix( MixCount );
}

void __fastcall TNNFGolovolomka15::KostyashkaClick( TObject *Sender )
{
  TPanel *P;
  TLabel *L = dynamic_cast< TLabel* >( Sender );
  if ( L )
    P = dynamic_cast< TPanel* >( L->Owner );
  else
    P = dynamic_cast< TPanel* >( Sender );
  if ( ValidHod( P ) ) {
    int N = P->Position->X;
    P->Position->X = EmptyLeft;
    EmptyLeft = N;
    N = P->Position->Y;
    P->Position->Y = EmptyTop;
    EmptyTop = N;

    if ( !IsMixWork && IsStartPosition() )
      DoPobeda();
  }
}

void __fastcall TNNFGolovolomka15::Mix( unsigned int AMixCount, unsigned int MS )
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
  }
}

bool __fastcall TNNFGolovolomka15::ValidHod( TPanel *P )
{
  if ( P ) {
    int AL = std::abs( P->Position->X - EmptyLeft )
      , AT = std::abs( P->Position->Y  - EmptyTop  );
    return std::abs( AL - AT ) == KostyashkaSize && AL <= KostyashkaSize && AT <= KostyashkaSize;
  } else
    return false;
}

void __fastcall TNNFGolovolomka15::DoPobeda()
{
  if ( FOnPobeda )
    FOnPobeda( this );
}

bool __fastcall TNNFGolovolomka15::IsStartPosition()
{
  int N = 0;
  TPanel *P;
  for ( int I = 0; I < 4; ++I ) {
    for ( int J = 0; J < 4; ++J ) {
      if ( ++N < 16 ) {
        P = GetKostyshka( N );
        if ( P->Position->X != J * KostyashkaSize ||
             P->Position->Y != I * KostyashkaSize )
          return false;
      }
    }
  }
  return true;
}
//---------------------------------------------------------------------------

namespace Fmx_nngolovolomka15
{
  void __fastcall PACKAGE Register()
  {
    TComponentClass classes[ 1 ] = { __classid( TNNFGolovolomka15 ) };
    RegisterComponents( L"FMX New Navadvipa", classes, 0 );
  }
}

