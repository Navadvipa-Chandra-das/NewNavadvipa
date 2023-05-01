// ---------------------------------------------------------------------------
#include <fmx.h>
#pragma hdrstop

#include "FMX_NNColor.h"
#include "FMX_NNColorIndex.h"
#include "FMX_NNDmNewNavadvipa.h"
// #include <math.h>

// ---------------------------------------------------------------------------
#pragma package(smart_init)

namespace NNF {

const long long int CycleColorCount = 27;

TColorFonFont::TColorFonFont()
  : FFontColor( claBlack )
  , FFonColor( claWhite )
{
};

TColorFonFont::TColorFonFont( TAlphaColor AFontColor
                            , TAlphaColor AFonColor )
  : FFontColor( AFontColor )
  , FFonColor( AFonColor )
{
};

TColorVector::TColorVector()
  : inherited()
{
}

TColorVector::~TColorVector()
{
}

void __fastcall TColorVector::LoadFromFiler( TNNFTextStream *Filer )
{
  TColorFonFont FP;
  std::size_t L = Filer->ReadSizeType();
  clear();
  reserve( L );
  for ( std::size_t i = 0; i < L; ++i ) {
    FP.FontColor = Filer->ReadColor();
    FP.FonColor  = Filer->ReadColor();
    push_back( FP );
  }
  Size = L;
}

void __fastcall TColorVector::SaveToFiler( TNNFTextStream *Filer )
{
  std::size_t L = size();
  Filer->WriteSizeType( L );
  for ( std::size_t i = 0; i < L; ++i ) {
    Filer->WriteColor( operator[]( i ).FontColor );
    Filer->WriteColor( operator[]( i ).FonColor );
  }
}

void __fastcall CycleColor( long long int ColorNo_
                          , TAlphaColor &FonColor_
                          , TAlphaColor &FontColor_ )
{
  ColorNo_ = fmod( ColorNo_, CycleColorCount );
  int N = ColorNo_;
  switch ( N ) {
  case 0:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor0 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor0 ].FonColor;
    break;
  case 1:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor1 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor1 ].FonColor;
    break;
  case 2:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor2 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor2 ].FonColor;
    break;
  case 3:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor3 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor3 ].FonColor;
    break;
  case 4:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor4 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor4 ].FonColor;
    break;
  case 5:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor5 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor5 ].FonColor;
    break;
  case 6:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor6 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor6 ].FonColor;
    break;
  case 7:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor7 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor7 ].FonColor;
    break;
  case 8:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor8 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor8 ].FonColor;
    break;
  case 9:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor9 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor9 ].FonColor;
    break;
  case 10:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor10 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor10 ].FonColor;
    break;
  case 11:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor11 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor11 ].FonColor;
    break;
  case 12:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor12 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor12 ].FonColor;
    break;
  case 13:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor13 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor13 ].FonColor;
    break;
  case 14:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor14 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor14 ].FonColor;
    break;
  case 15:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor15 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor15 ].FonColor;
    break;
  case 16:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor16 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor16 ].FonColor;
    break;
  case 17:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor17 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor17 ].FonColor;
    break;
  case 18:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor18 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor18 ].FonColor;
    break;
  case 19:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor19 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor19 ].FonColor;
    break;
  case 20:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor20 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor20 ].FonColor;
    break;
  case 21:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor21 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor21 ].FonColor;
    break;
  case 22:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor22 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor22 ].FonColor;
    break;
  case 23:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor23 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor23 ].FonColor;
    break;
  case 24:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor24 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor24 ].FonColor;
    break;
  case 25:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor25 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor25 ].FonColor;
    break;
  case 26:
    FontColor_ = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor26 ].FontColor;
    FonColor_  = dmfNewNavadvipa->ColorVector[ NNColor::CycleColor26 ].FonColor;
    break;
  default:
    throw Exception("Непонятный циклический цвет");
  }
}

};

