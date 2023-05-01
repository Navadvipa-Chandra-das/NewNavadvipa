//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop
USEFORM("FMX_NNFrLogin.cpp", frfLogin); /* TFrame: File Type */
USEFORM("FMX_NNFmRes.cpp", fmfRes);
USEFORM("FMX_NNFmDB.cpp", fmfDB);
USEFORM("FMX_NNFmActionList.cpp", fmfActionList);
USEFORM("FMX_NNFmAboutPrabhupadaSlovar.cpp", fmfAboutPrabhupadaSlovar);
USEFORM("FMX_NNFmPrabhupadaSlovar.cpp", fmfPrabhupadaSlovar);
USEFORM("FMX_NNFmLogin.cpp", fmfLogin);
USEFORM("FMX_NNFmLanguage.cpp", fmfLanguage);
USEFORM("FMX_NNDmNewNavadvipa.cpp", dmfNewNavadvipa); /* TDataModule: File Type */
USEFORM("FMX_NNDmRes.cpp", dmfRes); /* TDataModule: File Type */
USEFORM("FMX_NNDmPrabhupadaSlovar.cpp", dmfPrabhupadaSlovar); /* TDataModule: File Type */
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Package source.
//---------------------------------------------------------------------------


#pragma argsused
extern "C" int _libmain(unsigned long reason)
{
  return 1;
}
//---------------------------------------------------------------------------
