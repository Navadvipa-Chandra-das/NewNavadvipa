// ---------------------------------------------------------------------------
#ifndef FMX_NNColorH
#define FMX_NNColorH
// ---------------------------------------------------------------------------

#include <map>
#include "FMX_NNCommon.h"

namespace NNF {

struct PACKAGE TColorFonFont
{
private:
  TAlphaColor FFontColor;
  TAlphaColor FFonColor;
public:
  TColorFonFont();
  TColorFonFont( TAlphaColor AFontColor
               , TAlphaColor AFonColor );

  __property TAlphaColor FontColor = { read = FFontColor, write = FFontColor };
  __property TAlphaColor FonColor = { read = FFonColor, write = FFonColor };
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
  void __fastcall LoadFromFiler( TNNFTextStream *Filer );
  void __fastcall SaveToFiler( TNNFTextStream *Filer );
};

extern PACKAGE void __fastcall CycleColor( long long int ColorNo_
                                         , TAlphaColor &FonColor_
                                         , TAlphaColor &FontColor_ );

extern PACKAGE const long long int CycleColorCount;

};
#endif
