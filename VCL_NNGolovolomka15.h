//---------------------------------------------------------------------------

#ifndef VCL_NNGolovolomka15H
#define VCL_NNGolovolomka15H
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TNNVGolovolomka15 : public TPanel
{
private:
  using inherited = TPanel;
  int FKostyashkaSize = 0;
  int FEmptyLeft;
  int FEmptyTop;
  int FEmptyWidth;
  int FEmptyHeight;
  unsigned int FMixCount = 100;
  bool FIsMix = true;
  bool FIsMixWork = false;
  TNotifyEvent FOnVijaya;
  void __fastcall SetKostyashkaSize( int Value );
  void __fastcall PrepareKostyahkaSize();
  void __fastcall CreateKostyahki();
  void __fastcall KostyashkaClick( TObject *Sender );
  int __fastcall OptimalFontSize();
  bool __fastcall ValidHod( TPanel *P );
protected:
  DYNAMIC void __fastcall Resize();
  virtual void __fastcall Loaded();
  virtual void __fastcall DoVijaya();
  __property bool IsMixWork = { read = FIsMixWork, write = FIsMixWork };
public:
  __fastcall TNNVGolovolomka15( TComponent* Owner );
  void __fastcall Mix( unsigned int AMixCount = 0, unsigned int MS = 0 );
  void __fastcall StartPosition();
  bool __fastcall IsStartPosition();
  TPanel* __fastcall GetKostyshka( int N );
  __property int KostyashkaSize = { read = FKostyashkaSize, write = SetKostyashkaSize };
  __property int EmptyLeft = { read = FEmptyLeft, write = FEmptyLeft };
  __property int EmptyTop = { read = FEmptyTop, write = FEmptyTop };
  __property int EmptyWidth = { read = FEmptyWidth, write = FEmptyWidth };
  __property int EmptyHeight = { read = FEmptyHeight, write = FEmptyHeight };
__published:
  __property Color = { default = clWhite };
  __property BevelInner = { default = bvNone };
  __property BevelOuter = { default = bvNone };
  __property bool IsMix = { read = FIsMix, write = FIsMix, default = true };
  __property TNotifyEvent OnVijaya = { read = FOnVijaya, write = FOnVijaya };
  __property unsigned int MixCount = { read = FMixCount, write = FMixCount, default = 100 };
};
//---------------------------------------------------------------------------
#endif
