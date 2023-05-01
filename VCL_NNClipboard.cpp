// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VCL_NNClipboard.h"
#include <Vcl.Clipbrd.hpp>

// ---------------------------------------------------------------------------

#pragma package(smart_init)

namespace NNV {

  __fastcall TClipboardStream::TClipboardStream(Word Format,
      TClipboardMode Mode) {
    THandle Handle;
    void *MemPtr;

    FMode = Mode;
    FFormat = Format;

    // В "режиме чтения" немедленно читаем данные буфера в поток...
    if (FMode == cmRead && Clipboard()->HasFormat(FFormat)) {
      Clipboard()->Open();
      try {
        Handle = Clipboard()->GetAsHandle(FFormat);
        MemPtr = GlobalLock((void*)Handle);
        try {
          Write(MemPtr, GlobalSize((void*)Handle));
        }
        __finally {
          GlobalUnlock((void*)Handle);
        }
        Position = 0;
      }
      __finally {
        Clipboard()->Close();
      }
    }
  }

  __fastcall TClipboardStream::~TClipboardStream() {
    void *P;

    // В "режиме записи" копируем в буфер все содержимое потока...
    if (FMode == cmWrite) {
      P = GlobalAlloc(HeapAllocFlags, Size);
      try {
        Position = 0;
        Read(P, Size);
        Clipboard()->SetAsHandle(FFormat, (unsigned int)GlobalHandle((void*)P));
      }
      catch (...) {
        GlobalFree((void*)P);
      }
    }
  }

}
