// ---------------------------------------------------------------------------

#ifndef VCL_NNClipboardH
#define VCL_NNClipboardH
// ---------------------------------------------------------------------------

namespace NNV {

  PACKAGE enum TClipboardMode {
    cmRead, cmWrite
  };

  class PACKAGE TClipboardStream : public TMemoryStream {
  private:
    using inherited = TMemoryStream;
    TClipboardMode FMode;
    Word FFormat;

  public:
    __fastcall TClipboardStream(Word Format, TClipboardMode Mode);
    __fastcall ~TClipboardStream();
  };

}

#endif
