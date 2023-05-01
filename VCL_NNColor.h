// ---------------------------------------------------------------------------
#ifndef VCL_NNColorH
#define VCL_NNColorH
// ---------------------------------------------------------------------------

#include <map>
#include "VCL_NNCommon.h"

namespace NNV {

struct PACKAGE TColorFonFont
{
private:
  TColor FFontColor;
  TColor FFonColor;
public:
  TColorFonFont();
  TColorFonFont( TColor AFontColor
               , TColor AFonColor );

  __property TColor FontColor = { read = FFontColor, write = FFontColor };
  __property TColor FonColor = { read = FFonColor, write = FFonColor };
};

class PACKAGE TColorVector : public std::vector< TColorFonFont >
{
private:
  using inherited = std::vector< TColorFonFont >;
  std::size_t FSize = 0;
public:
  TColorVector();
  ~TColorVector();
  __property std::size_t Size = { read = FSize, write = FSize };
  void __fastcall LoadFromFiler( TNNVTextStream *Filer );
  void __fastcall SaveToFiler( TNNVTextStream *Filer );
};

extern PACKAGE void __fastcall CycleColor( long long int ColorNo_
                                         , TColor &FonColor_
                                         , TColor &FontColor_ );

extern PACKAGE const long long int CycleColorCount;

};
#endif
