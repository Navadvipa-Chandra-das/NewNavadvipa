// New Navadvipa library - author Navadvipa Chandra das e-mail navadvipa.chandra.das@nizhnyaya-navadvipa.ru
#include <vcl.h>
#pragma hdrstop
#include "VCL_NNConst.h"
#include "VCL_NNStrUtil.h"

#pragma package(smart_init)

namespace NNVConst {

const char *PRABHUPADA_SCHEMA = "PRABHUPADA_SCHEMA";
const char *PrabhupadaSchemaDefault = "\"NewNavadvipa\".";

int MainLanguageIndex;
const int MainLanguageID = 1;

TColor FonColorValueChange = clYellow;
TColor FontColorValueChange = clBlack;

TCustomForm *FormBack = nullptr;

int NationalNumdec = 2;
const int MaxStoryComboBox = 10;

const char *Version = "3.6";
const char *NotValidLogic = "������ ���� �� ������";
const char *OraclePackageNotDefine = "->OraclePackage �� ���������";
const char *OracleSessionNotDefine = "->OracleSession �� ����������";
const char *OracleSessionNotConnected = "->OracleSession �� �������";
const String TableUserReg = L"\"UserReg\"";
const String FieldUserRegKey = L"\"UserRegKey\"";
const String FieldUserData = L"\"UserData\"";
const char *OtherUserChangeRecord =
    "������ ������������ ������� ��� ������, ���� ";
String FieldUserChange;
const char *RecordNotChanged = "�� ��������";
const char *RecordChanged = "��������";
const char *RecordInserted = "���������";
const char *RecordDeleted = "�������";
const char *C_GalkaEmpty = "\x9E";
const char *C_Galka = "\x6C";
const char *C_GalkaTurizm = "\x51";
const char *C_GalkaInternet = "\x28";
const char *C_GalkaLico = "\x4A";
String S_GalkaEmpty( C_GalkaEmpty );
String S_Galka( C_Galka );
String S_GalkaTurizm( C_GalkaTurizm );
String S_GalkaInternet( C_GalkaInternet );
String S_GalkaLico( C_GalkaLico );
const char *NotExistDialogForm = "�� ���������� ����� ������� ��� ";
const char *Navadvipa = "���������";
const char *LogoStr =
    "������������� ��������� \"�������\" ���. (06257) 4-35-45";
const char *CWFloatFormatNote =
    "����������� ����� �� ���������� ���-�� ������ ����� �������";
const char *CWStrToFloatNote = "����������� ������ � �������� �����";
const char *CWStrToFloatDefNote =
    "����������� ������ � �������� �����, ���� ���������, �� ���������� ���������" ", ������� ���������� �� ������ ���������";
const char *CWFormatStrDefNote =
    "���������� ������ ������� ��� ����� � ������ �����������";
const char *LogoStrNote = "��� ��������� + �������";
const char *DataSetNotActive = "�� �������";
const char *DataSetBrowse = "��������";
const char *DataSetEdit = "��������������";
const char *DataSetInsert = "����������";
const char *DataSetSetKey = "��������� �����";
const char *DataSetCalcFields = "���������� �����";
const char *DataSetFilter = "����������";
const char *DataSetNewValue = "����� ��������";
const char *DataSetOldValue = "������ �������� �����";
const char *DataSetCurValue = "������� ��������";
const char *DataSetBlockRead = "���������� �����������";
const char *DataSetInternalCalc = "���������� ����������";
const char *DataSetOpening = "��������";
const char *NotFindDataModule = "�� ������ DataModule ";
const char *NotFindDataSet = "�� ������ DataSet ";
const char *DeletedRow = "������� ������ ?";
const char *Attention = "����������, ��������!";
const char *AttemptSearchEmpty = "������� ������ ������ ��������!";
const char *RecordNotFind = "������ �� �������";
const char *FieldSearchNotDefined = "�� ���������� ���� ��� ������";
const char *ReportOptions = "�������� ������ ";
const char *NodeNotFind = "����� �� �������";
const char *NodeNotUnerstand = "���������� ����� T�WDBTreeView";
const char *NodeImpossibleMove = "������ ���������� ����� ";
const char *ToNode = "\n�� ����� ";
const char *MoveNode = "���������� ����� ";
const char *ToNodeSample = " �� ����� ";
const char *NotUnderstandStartNode = "���������� ��������� ����� T�WDBTreeView";
const char *SortOnlyWithinLimitsLevel =
    "����������, ���������� ������ � �������� ������!";
const char *MoreAttentive = "����������, ��������������";
const char *SortingIsImpossibleInThisCase =
    "���������� ���������� � ������ ������!";
const char *TargetAndStartNodeEqual = "������� � ��������� ����� �����!";
const char *TheNode = "����� ";
const char *DeleteImpossible = " ������� ������!";
const char *ToDeleteNode = "������� ����� ";
const char *TheMergeNodeImpossible = "���������� ������� ����� ";
const char *TheAnd = " � ";
const char *InsertImpossible = "���������� ����������";
const char *TheNewNodeText = "<�����!>";
const char *NodeAdminNotFound = "NodeAdmin �� ������";
const char *LocateNodeIsNull = "->LocateNode == NULL";
const char *TooLargeLengthDecimalPart =
    "������� ������� ����� ���������� �����";
const char *ToKeepChanges = "��������� ��������� ?\n";
const char *TheSymbol = "������ ";
const char *IsInadmissibleInLine = " ���������� � ������������� ������";
const char *OnTheTree = " �� ������";
const char *TheTextForSearch = "����� ��� ������";
const char *IncorrectValue = "������������ ��������";
const char *ToMakeLevel = "������� ���������� �����\n";
const char *C_EditMaskDateFormatShort = "!99/99/9999;1;_";
const char *C_EditMaskDateFormatLong = "!99/99/9999 99:99:99;1;_";
const char *C_Doctor = "������";
String S_Doctor( C_Doctor );
String Enterprise( L"ROSE." );
const String SerialValidChars
    ( L"0123456789 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+-/\()<>{}_=:;*\t"
    );
String NlsNumericCharacters = String( FormatSettings.DecimalSeparator ) +
                              String( FormatSettings.ThousandSeparator );
String NlsDateFormatShort = String( L"dd" ) + String( FormatSettings.DateSeparator ) +
                            String( L"mm" ) + String( FormatSettings.DateSeparator ) +
                            String( L"yyyy" );
String LongTimeFormat = String( L"hh" ) + String( FormatSettings.TimeSeparator ) +
                        String( L"nn" ) + String( FormatSettings.TimeSeparator ) +
                        String( L"ss" );
String NlsDateFormatLong = String( L"dd" ) + String( FormatSettings.DateSeparator ) +
                           String( L"mm" ) + String( FormatSettings.DateSeparator ) +
                           String( L"yyyy " ) +
                           String( L"hh" ) + String( FormatSettings.TimeSeparator ) +
                           String( L"nn" ) + String( FormatSettings.TimeSeparator ) +
                           String( L"ss" );
String EditMaskDateFormatShort = C_EditMaskDateFormatShort;
String EditMaskDateFormatLong = C_EditMaskDateFormatLong;
String StrEmptyDateLong = String( L"  " ) + String( FormatSettings.DateSeparator ) +
                          String( L"  " ) + String( FormatSettings.DateSeparator ) +
                          String( L"       " ) +
                          String( FormatSettings.TimeSeparator ) + String( L"  " ) +
                          String( FormatSettings.TimeSeparator ) + String( L"  " );
String StrEmptyDateShort = String( L"  " ) + String( FormatSettings.DateSeparator ) +
                           String( L"  " ) + String( FormatSettings.DateSeparator ) +
                           String( L"    " );
const String EditMaskNumberKindShortInt( L"!cccccc;0;_" );
const String EditMaskNumberKindInt( L"!ccccccccccc;0;_" );
const String EditMaskNumberKindLongLongInt( L"!cccccccccccccccccccc;0;_" );
const String EditMaskNumberKindDouble(      L"!ccccccccccccccccccccccccc;0;_" );
const String FLOAT_FORMAT( L"#,##0" );
const String SAMPLE_FLOAT_FORMAT( L"###0" );
const String DBSearchDialogFilterKey( L"������" );
const char CharPercent = '*';
const char CharUnderline = '?';
const char VarSeparator = ':';
const char CharPoint = '.';
const char CharComma = ',';
const String StrCharPercent( CharPercent );
const String StrCharUnderline( CharUnderline );
const String Point( CharPoint );
const String Comma( CharComma );
const char *FILTER_PREDICAT = "COOL_FILTER";
const char *GenderMale = "�������";
const char *GenderAvg = "�������";
const char *GenderFemale = "�������";
const String strGenderMale( GenderMale );
const String strGenderAvg( GenderAvg );
const String strGenderFemale( GenderFemale );
const unsigned int MaxTreeHistory = 32;
const unsigned int MaxFormHistory = 32;
const int limit_pick_list = 108;
const char *SorryNoExistsRight = "����� �� ����������!";
const char *SorryNoRight = "��������, ����������, �� � ��� ��� ����� ";
const double Epsilon = 0.0001;
const int CriticalFormPlaceDelta = 40;
const int CriticalFormPlaceMinus = 10;
const String AllAcount( L"���" );
const String NullAcount( L"�����" );
const String Empty( L"�����" );
const String NotEmpty( L"�� �����" );
const String SetTitle( L"�����" );
const String SET_VARIABLE( L"SET_VARIABLE" );
const String COMMA_TEMP_REPLACE( L"!#@^&!@#" );
const char *CharINFO = "INFO";
const String INFO( CharINFO );
const char *CharAVANCE = "�����";
const String AVANCE( CharAVANCE );
const char *NotAcceptAllEnterprise = "����������� ��� �����������";
const String Space( L" " );
const String EmptyStr( L"" );
const String SingleCommas( L"'" );
const String DoubleCommas( L"\"" );
const String LeftScobka( L"(" );
const String RightScobka( L")" );
const String FieldOff( L"����." );
const String Where( L"where " );
const String ORDER_BY( L"ORDER_BY" );
const String ACTUAL_ONLY( L"ACTUAL_ONLY" );
const String END_TO_END_VIEWING( L"END_TO_END_VIEWING" );
const String ActualOnly( L"a.\"Actual\" = true" );
const String EndToEndViewing( L"a.\"KindID\" = :KindID" );
const String True( L"True" );
const String False( L"False" );
const String And( L" and " );
const String Or( L" or " );
const String KindID( L"KindID" );
const char *DemoVersion = " DEMO ";
const String TabletRest( "�������" );
const char *NotValidBufferFormat =
    "��������, ����������, �� ������ ������ �� ��������";
const char *Sorry = "��������, ����������, �� ";
const char *SerialNotValid = "�������� ����� �� ����������!";
const char* Filter = "������: ";
const char* Search = "�����: ";
std::locale loc;
const t_char &char_o = std::use_facet < t_char > ( loc );
String ProgramDir;
const String BackSlash( L"\\" );
const String Slash( L"/" );
const String NodeDelimeter( L" \\ " );
const String AltDelimeter( L" / " );
const String PrabhupadaSlovarFiles( "./PrabhupadaSlovarFiles/" );
const char SystemDecimalSeparator = FormatSettings.DecimalSeparator;
const char SystemThousandSeparator = FormatSettings.ThousandSeparator;

bool LocaleFormatRun = false;

}
