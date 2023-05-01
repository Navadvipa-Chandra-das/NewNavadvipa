// Nizhnyaya Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#ifndef FMX_NNConstH
#define FMX_NNConstH
//---------------------------------------------------------------------------
#define SHORT_WIDTH    84
#define LONG_WIDTH     128
namespace NNFConst {

extern PACKAGE const char *PRABHUPADA_SCHEMA;
extern PACKAGE const char *PrabhupadaSchemaDefault;

extern PACKAGE int MainLanguageIndex;
extern PACKAGE const int MainLanguageID;
using t_char = std::ctype< char >;
using char_mask = t_char::mask;
extern PACKAGE void __fastcall PrepareLocale( const String &NlsDateFormatLong_
                                            , const String &NlsDateFormatShort_
                                            , const String &EditMaskDateFormatLong_
                                            , const String &EditMaskDateFormatShort_ );
extern PACKAGE TCommonCustomForm* FormBack;
PACKAGE enum TBufferType
{
  btNone   = 0
, btOracle = 1
, btTree   = 2
};

extern PACKAGE int NationalNumdec;
extern PACKAGE const int MaxStoryComboBox;

extern PACKAGE const char *Version;
extern PACKAGE const char *NotValidLogic;
extern PACKAGE const char *OraclePackageNotDefine;
extern PACKAGE const char *OracleSessionNotDefine;
extern PACKAGE const char *OracleSessionNotConnected;
extern PACKAGE const String TableUserReg;
extern PACKAGE const String FieldUserRegKey;
extern PACKAGE const String FieldUserData;
extern PACKAGE const char *OtherUserChangeRecord;
extern PACKAGE String FieldUserChange;
extern PACKAGE const char *RecordNotChanged;
extern PACKAGE const char *RecordChanged;
extern PACKAGE const char *RecordInserted;
extern PACKAGE const char *RecordDeleted;
extern PACKAGE const char *C_GalkaEmpty;
extern PACKAGE const char *C_Galka;
extern PACKAGE const char *C_GalkaTurizm;
extern PACKAGE const char *C_GalkaInternet;
extern PACKAGE String S_GalkaEmpty;
extern PACKAGE String S_Galka;
extern PACKAGE String S_GalkaTurizm;
extern PACKAGE String S_GalkaInternet;
extern PACKAGE String S_GalkaLico;
extern PACKAGE const char *NotExistDialogForm;
extern PACKAGE const char *Navadvipa;
extern PACKAGE const char *LogoStr;
extern PACKAGE const char *CWFloatFormatNote;
extern PACKAGE const char *CWStrToFloatNote;
extern PACKAGE const char *CWStrToFloatDefNote;
extern PACKAGE const char *CWFormatStrDefNote;
extern PACKAGE const char *LogoStrNote;
extern PACKAGE const char *DataSetNotActive;
extern PACKAGE const char *DataSetBrowse;
extern PACKAGE const char *DataSetEdit;
extern PACKAGE const char *DataSetInsert;
extern PACKAGE const char *DataSetSetKey;
extern PACKAGE const char *DataSetCalcFields;
extern PACKAGE const char *DataSetFilter;
extern PACKAGE const char *DataSetNewValue;
extern PACKAGE const char *DataSetOldValue;
extern PACKAGE const char *DataSetCurValue;
extern PACKAGE const char *DataSetBlockRead;
extern PACKAGE const char *DataSetInternalCalc;
extern PACKAGE const char *DataSetOpening;
extern PACKAGE const char *NotFindDataModule;
extern PACKAGE const char *NotFindDataSet;
extern PACKAGE const char *DeletedRow;
extern PACKAGE const char *Attention;
extern PACKAGE const char *SearchNotPossible;
extern PACKAGE const char *AttemptSearchEmpty;
extern PACKAGE const char *RecordNotFind;
extern PACKAGE const char *FieldSearchNotDefined;
extern PACKAGE const char *ReportOptions;
extern PACKAGE const char *NodeNotFind;
extern PACKAGE const char *NodeNotUnerstand;
extern PACKAGE const char *NodeImpossibleMove;
extern PACKAGE const char *ToNode;
extern PACKAGE const char *MoveNode;
extern PACKAGE const char *ToNodeSample;
extern PACKAGE const char *NotUnderstandStartNode;
extern PACKAGE const char *SortOnlyWithinLimitsLevel;
extern PACKAGE const char *MoreAttentive;
extern PACKAGE const char *SortingIsImpossibleInThisCase;
extern PACKAGE const char *TargetAndStartNodeEqual;
extern PACKAGE const char *TheNode;
extern PACKAGE const char *DeleteImpossible;
extern PACKAGE const char *ToDeleteNode;
extern PACKAGE const char *TheMergeNodeImpossible;
extern PACKAGE const char *TheAnd;
extern PACKAGE const char *InsertImpossible;
extern PACKAGE const char *TheNewNodeText;
extern PACKAGE const char *NodeAdminNotFound;
extern PACKAGE const char *LocateNodeIsNull;
extern PACKAGE const char *TooLargeLengthDecimalPart;
extern PACKAGE const char *ToKeepChanges;
extern PACKAGE const char *TheSymbol;
extern PACKAGE const char *IsInadmissibleInLine;
extern PACKAGE const char *OnTheTree;
extern PACKAGE const char *TheTextForSearch;
extern PACKAGE const char *IncorrectValue;
extern PACKAGE const char *ToMakeLevel;
extern PACKAGE const char *C_EditMaskDateFormatShort;
extern PACKAGE const char *C_EditMaskDateFormatLong;
extern PACKAGE const char *C_Doctor;
extern PACKAGE String S_Doctor;
extern PACKAGE String Enterprise;
extern PACKAGE const String SerialValidChars;
extern PACKAGE String NlsNumericCharacters;
extern PACKAGE String NlsDateFormatShort;
extern PACKAGE String LongTimeFormat;
extern PACKAGE String NlsDateFormatLong;
extern PACKAGE String EditMaskDateFormatShort;
extern PACKAGE String EditMaskDateFormatLong;
extern PACKAGE String StrEmptyDateLong;
extern PACKAGE String StrEmptyDateShort;
extern PACKAGE String SaveStrEmptyDateLong;
extern PACKAGE String SaveStrEmptyDateShort;
extern PACKAGE const String FLOAT_FORMAT;
extern PACKAGE const String SAMPLE_FLOAT_FORMAT;
extern PACKAGE const String DBSearchDialogFilterKey;
extern PACKAGE const char CharPercent;
extern PACKAGE const char CharUnderline;
extern PACKAGE const char VarSeparator;
extern PACKAGE const char CharPoint;
extern PACKAGE const char CharComma;
extern PACKAGE const String StrCharPercent;
extern PACKAGE const String StrCharUnderline;
extern PACKAGE const String Point;
extern PACKAGE const String Comma;
extern PACKAGE const char *FILTER_PREDICAT;
extern PACKAGE const char *GenderMale;
extern PACKAGE const char *GenderAvg;
extern PACKAGE const char *GenderFemale;
extern PACKAGE const String strGenderMale;
extern PACKAGE const String strGenderAvg;
extern PACKAGE const String strGenderFemale;
extern PACKAGE const unsigned int MaxTreeHistory;
extern PACKAGE const unsigned int MaxFormHistory;
extern PACKAGE const int limit_pick_list;
extern PACKAGE const char *SorryNoExistsRight;
extern PACKAGE const char *SorryNoRight;
extern PACKAGE const double Epsilon;
extern PACKAGE const int CriticalFormPlaceDelta;
extern PACKAGE const int CriticalFormPlaceMinus;
extern PACKAGE const String AllAcount;
extern PACKAGE const String NullAcount;
extern PACKAGE const String Empty;
extern PACKAGE const String NotEmpty;
extern PACKAGE const String SetTitle;
extern PACKAGE const String SET_VARIABLE;
extern PACKAGE const String COMMA_TEMP_REPLACE;
extern PACKAGE const char   *CharINFO;
extern PACKAGE const String INFO;
extern PACKAGE const char   *CharAVANCE;
extern PACKAGE const String AVANCE;
extern PACKAGE const char *NotAcceptAllEnterprise;
extern PACKAGE const String Space;
extern PACKAGE const String SingleCommas;
extern PACKAGE const String DoubleCommas;
extern PACKAGE const String LeftScobka;
extern PACKAGE const String RightScobka;
extern PACKAGE const String FieldOff;
extern PACKAGE const String Where;
extern PACKAGE const String ORDER_BY;
extern PACKAGE const String ACTUAL_ONLY;
extern PACKAGE const String END_TO_END_VIEWING;
extern PACKAGE const String ActualOnly;
extern PACKAGE const String EndToEndViewing;
extern PACKAGE const String True;
extern PACKAGE const String False;
extern PACKAGE const String And;
extern PACKAGE const String Or;
extern PACKAGE const String KindID;
extern PACKAGE const char *DemoVersion;
extern PACKAGE const String TabletRest;
extern PACKAGE const char *NotValidBufferFormat;
extern PACKAGE const char *Sorry;
extern PACKAGE const char *SerialNotValid;
extern PACKAGE const char *Filter;
extern PACKAGE std::locale loc;
extern PACKAGE const t_char &char_o;
extern PACKAGE TBufferType BufferType;
extern PACKAGE String ProgramDir;
extern const String BackSlash;
extern const String Slash;
extern PACKAGE const String NodeDelimeter;
extern PACKAGE const String AltDelimeter;
extern PACKAGE const String PrabhupadaSlovarFiles;
extern PACKAGE const char SystemDecimalSeparator;
extern PACKAGE const char SystemThousandSeparator;
extern PACKAGE bool LocaleFormatRun;
}
#endif
