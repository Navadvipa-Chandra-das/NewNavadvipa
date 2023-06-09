﻿//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop

#include "VCL_NNColorIndex.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace NNColor {

const std::size_t CycleColor0 = 0;
const std::size_t CycleColor3 = 1;
const std::size_t CycleColor4 = 2;
const std::size_t Service = 3;
const std::size_t CommodAss = 4;
const std::size_t CommodAssOwner = 5;
const std::size_t CommodAssDetail = 6;
const std::size_t CommodLack = 7;
const std::size_t CommodOld = 8;
const std::size_t CommodWithNote = 9;
const std::size_t CommentInPrim = 10;
const std::size_t CommentSummaSecond = 11;
const std::size_t ErrorSubconto = 12;
const std::size_t GrayLine = 13;
const std::size_t CommentSummaFirst = 14;
const std::size_t SummaFirst = 15;
const std::size_t SummaSecond = 16;
const std::size_t InDialogQuantity = 17;
const std::size_t InDialogPriceBig = 18;
const std::size_t CycleColor21 = 19;
const std::size_t SerialWithGuaranty = 20;
const std::size_t SerialWaitWithGuaranty = 21;
const std::size_t SerialSupplierWithoutGuaranty = 22;
const std::size_t CycleColor10 = 23;
const std::size_t CycleColor11 = 24;
const std::size_t CycleColor12 = 25;
const std::size_t CycleColor13 = 26;
const std::size_t CycleColor22 = 27;
const std::size_t CycleColor23 = 28;
const std::size_t CycleColor24 = 29;
const std::size_t CycleColor26 = 30;
const std::size_t SerialWithoutGuaranty = 31;
const std::size_t SerialSaleWithGuaranty = 32;
const std::size_t SerialSaleWithoutGuaranty = 33;
const std::size_t SerialWaitWithoutGuaranty = 34;
const std::size_t SerialTemporaryWithGuaranty = 35;
const std::size_t SerialTemporaryWithoutGuaranty = 36;
const std::size_t SerialSupplierWithGuaranty = 37;
const std::size_t SerialXWithGuaranty = 38;
const std::size_t SerialXWithoutGuaranty = 39;
const std::size_t SerialPayAndStore = 40;
const std::size_t CycleColor5 = 41;
const std::size_t CycleColor6 = 42;
const std::size_t CycleColor7 = 43;
const std::size_t CycleColor8 = 44;
const std::size_t CycleColor9 = 45;
const std::size_t SerialNotPayAndStore = 46;
const std::size_t SerialChangeSupplierWithGuaranty = 47;
const std::size_t SerialChangeSupplierWithoutGuaranty = 48;
const std::size_t CommentPartSumma3 = 49;
const std::size_t PartSumma3 = 50;
const std::size_t NotActualOper = 51;
const std::size_t PrimWithComment = 52;
const std::size_t ActualComment = 53;
const std::size_t PriceCommodPayBig = 54;
const std::size_t PartPay = 55;
const std::size_t HotKey = 56;
const std::size_t HotKeyWithoutShift = 57;
const std::size_t EmptyHotKey = 58;
const std::size_t ChessMinusSumma = 59;
const std::size_t ChessNeutralConstr = 60;
const std::size_t ChessAccount = 61;
const std::size_t ChessItog = 62;
const std::size_t KalaYantra = 63;
const std::size_t InDialogPriceSmall = 64;
const std::size_t InDialogCommodNullQuantity = 65;
const std::size_t InDialogCommodMinusQuantity = 66;
const std::size_t CycleColor14 = 67;
const std::size_t CycleColor15 = 68;
const std::size_t CycleColor16 = 69;
const std::size_t CycleColor17 = 70;
const std::size_t CycleColor18 = 71;
const std::size_t CycleColor19 = 72;
const std::size_t CycleColor20 = 73;
const std::size_t CycleColor25 = 74;
const std::size_t SummaSmallOpt = 75;
const std::size_t SummaDiler = 76;
const std::size_t SummaOpt = 77;
const std::size_t SummaEntry = 78;
const std::size_t SummaSmallThanEntry = 79;
const std::size_t SummaMoreThanRetail = 80;
const std::size_t CommodMarkdown1 = 81;
const std::size_t CommodMarkdown2 = 82;
const std::size_t CommodMarkdown3 = 83;
const std::size_t CommodMarkdown4 = 84;
const std::size_t SlyUserEnter = 85;
const std::size_t SlyUserDelete = 86;
const std::size_t SlyUserCreate = 87;
const std::size_t StorehousOperAndPrimDifferent = 88;
const std::size_t KaemkaIndicatorNormal = 89;
const std::size_t FieldIndicatorNormal = 90;
const std::size_t KaemkaIndicatorSignal = 91;
const std::size_t FieldIndicatorSignal = 92;
const std::size_t PrimPayAndNotShipment = 93;
const std::size_t PrimShipmentAndNotPay = 94;
const std::size_t TabelVyhodovNotAny = 95;
const std::size_t TabelVyhodovProgul = 96;
const std::size_t PriceLastCommod = 97;
const std::size_t SerialPay = 98;
const std::size_t SerialPayByNotSrok = 99;
const std::size_t OperComokNotPayDebetPrim = 100;
const std::size_t OperComokNotPayCreditPrim = 101;
const std::size_t CommodVeryOld = 102;
const std::size_t CommentColorWinow = 103;
const std::size_t SchetCreditPayBeznalAndNotDocuments = 104;
const std::size_t SchetCreditAcceptlAndNotPayAndNotOtgr = 105;
const std::size_t SerialStoreButNotPayProvider = 106;
const std::size_t CycleColor2 = 107;
const std::size_t CycleColor1 = 108;
const std::size_t ServiceClient1_7 = 109;
const std::size_t ServiceClient8_14 = 110;
const std::size_t SerialDifferentCommod = 111;
const std::size_t ServiceClient15_21 = 112;
const std::size_t ServiceClient22_28 = 113;
const std::size_t ServiceClientMore29 = 114;
const std::size_t TabelVyhodovOtpusk = 115;
const std::size_t TabelVyhodovBolnichnyi = 116;
const std::size_t TabelVyhodovNotStandartTime = 117;
const std::size_t TabelVyhodovPolovinaStavka = 118;
const std::size_t SummaRetail = 119;
const std::size_t SerialPayButNotPayProvider = 120;
const std::size_t ExitFromProgram = 121;
const std::size_t PrintPrim = 122;
const std::size_t ProgramTryVzlom = 123;
const std::size_t CommodPay = 124;
const std::size_t BuhgalterCommod = 125;
const std::size_t DoctorZayavkaNotExecute = 126;

}
