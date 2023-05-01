// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "VCL_NNColor.h"
#include "VCL_NNColorIndex.h"
#include "VCL_NNDmNewNavadvipa.h"
// #include <math.h>

// ---------------------------------------------------------------------------
#pragma package(smart_init)

namespace NNV {

const long long int CycleColorCount = 27;

TColorFonFont::TColorFonFont()
  : FFontColor( clBlack )
  , FFonColor( clWhite )
{
};

TColorFonFont::TColorFonFont( TColor AFontColor
                            , TColor AFonColor )
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

void __fastcall TColorVector::LoadFromFiler( TNNVTextStream *Filer )
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

void __fastcall TColorVector::SaveToFiler( TNNVTextStream *Filer )
{
  std::size_t L = size();
  Filer->WriteSizeType( L );
  for ( std::size_t i = 0; i < L; ++i ) {
    Filer->WriteColor( operator[]( i ).FontColor );
    Filer->WriteColor( operator[]( i ).FonColor );
  }
}

void __fastcall CycleColor( long long int ColorNo_
                          , TColor &FonColor_
                          , TColor &FontColor_)
{
  ColorNo_ = fmod( ColorNo_, CycleColorCount );
  int N = ColorNo_;
  switch ( N ) {
  case 0:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor0 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor0 ].FonColor;
    break;
  case 1:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor1 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor1 ].FonColor;
    break;
  case 2:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor2 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor2 ].FonColor;
    break;
  case 3:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor3 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor3 ].FonColor;
    break;
  case 4:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor4 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor4 ].FonColor;
    break;
  case 5:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor5 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor5 ].FonColor;
    break;
  case 6:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor6 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor6 ].FonColor;
    break;
  case 7:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor7 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor7 ].FonColor;
    break;
  case 8:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor8 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor8 ].FonColor;
    break;
  case 9:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor9 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor9 ].FonColor;
    break;
  case 10:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor10 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor10 ].FonColor;
    break;
  case 11:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor11 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor11 ].FonColor;
    break;
  case 12:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor12 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor12 ].FonColor;
    break;
  case 13:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor13 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor13 ].FonColor;
    break;
  case 14:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor14 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor14 ].FonColor;
    break;
  case 15:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor15 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor15 ].FonColor;
    break;
  case 16:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor16 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor16 ].FonColor;
    break;
  case 17:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor17 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor17 ].FonColor;
    break;
  case 18:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor18 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor18 ].FonColor;
    break;
  case 19:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor19 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor19 ].FonColor;
    break;
  case 20:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor20 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor20 ].FonColor;
    break;
  case 21:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor21 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor21 ].FonColor;
    break;
  case 22:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor22 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor22 ].FonColor;
    break;
  case 23:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor23 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor23 ].FonColor;
    break;
  case 24:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor24 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor24 ].FonColor;
    break;
  case 25:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor25 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor25 ].FonColor;
    break;
  case 26:
    FontColor_ = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor26 ].FontColor;
    FonColor_  = dmvNewNavadvipa->ColorVector[ NNColor::CycleColor26 ].FonColor;
    break;
  default:
    throw Exception("Непонятный циклический цвет");
  }
}

};

