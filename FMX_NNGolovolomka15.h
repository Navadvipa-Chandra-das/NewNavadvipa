//---------------------------------------------------------------------------

#ifndef FMX_NNGolovolomka15H
#define FMX_NNGolovolomka15H
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Fmx.Controls.hpp>
#include <Fmx.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TNNFGolovolomka15 : public TPanel
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
  TNotifyEvent FOnPobeda;
  void __fastcall SetKostyashkaSize( int Value );
  void __fastcall PrepareKostyahkaSize();
  void __fastcall CreateKostyahki();
  TPanel* __fastcall CreateKostyahka( int N );
  void __fastcall KostyashkaClick( TObject *Sender );
  int __fastcall OptimalFontSize();
  bool __fastcall ValidHod( TPanel *P );
protected:
  virtual void __fastcall Resize();
  virtual void __fastcall Loaded();
  virtual void __fastcall DoPobeda();
  __property bool IsMixWork = { read = FIsMixWork, write = FIsMixWork };
public:
  __fastcall TNNFGolovolomka15( TComponent* Owner );
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
  __property bool IsMix = { read = FIsMix, write = FIsMix, default = true };
  __property TNotifyEvent OnPobeda = { read = FOnPobeda, write = FOnPobeda };
  __property unsigned int MixCount = { read = FMixCount, write = FMixCount, default = 100 };
};
//---------------------------------------------------------------------------
#endif
