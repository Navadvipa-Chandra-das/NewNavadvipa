// Wanderer library - aut"FMX_NNConst.h"lotyh e-mail alejan@rambler.ru
#include <fmx.h>
#pragma hdrstop
#include "FMX_NNConst.h"
#include "FMX_NNStrUtil.h"
//------------------------------------Fmx_nnconst--------------------------------
#pragma package(smart_init)
namespace NNFConst {

const char *PRABHUPADA_SCHEMA = "PRABHUPADA_SCHEMA";
const char *PrabhupadaSchemaDefault = "\"NewNavadvipa\".";

int MainLanguageIndex;
const int MainLanguageID = 1;

TCommonCustomForm *FormBack = nullptr;

int NationalNumdec = 2;
const int MaxStoryComboBox = 10;

const char *Version                = "3.6";
const char *NotValidLogic          = "Такого быть не должно";
const char *OraclePackageNotDefine    = "->OraclePackage не определен";
const char *OracleSessionNotDefine    = "->OracleSession не определена";
const char *OracleSessionNotConnected = "->OracleSession не открыта";
const String TableUserReg    = "\"UserReg\"";
const String FieldUserRegKey = "\"UserRegKey\"";
const String FieldUserData   = "\"UserData\"";
const char *OtherUserChangeRecord     = "Другой пользователь изменил эту запись, поле ";
String FieldUserChange;
const char *RecordNotChanged   = "Не изменена";
const char *RecordChanged      = "Изменена";
const char *RecordInserted     = "Вставлена";
const char *RecordDeleted      = "Удалена";
const char *C_GalkaEmpty       = "\x9E";
const char *C_Galka            = "\x6C";
const char *C_GalkaTurizm      = "\x51";
const char *C_GalkaInternet    = "\x28";
const char *C_GalkaLico        = "\x4A";
String S_GalkaEmpty(    C_GalkaEmpty    );
String S_Galka(         C_Galka         );
String S_GalkaTurizm(   C_GalkaTurizm   );
String S_GalkaInternet( C_GalkaInternet );
String S_GalkaLico(     C_GalkaLico     );
const char *NotExistDialogForm = "Не определена форма диалога для ";
const char *Navadvipa          = "Навадвипа";
const char *LogoStr             = "Бухгалтерская программа \"Троянда\" тел. (06257) 4-35-45";
const char *CWFloatFormatNote   = "Форматирует число до указанного кол-ва знаков после запятой";
const char *CWStrToFloatNote    = "Преобразует строку в реальное число";
const char *CWStrToFloatDefNote = "Преобразует строку в реальное число, если неудается, то возвращает умолчание"
                                  ", которое передается во втором параметре";
const char *CWFormatStrDefNote  = "Возвращает строку формата для чисел с нужным округлением";
const char *LogoStrNote         = "Имя программы + телефон";
const char *DataSetNotActive    = "Не активна";
const char *DataSetBrowse       = "Просмотр";
const char *DataSetEdit         = "Редактирование";
const char *DataSetInsert       = "Добавление";
const char *DataSetSetKey       = "Установка ключа";
const char *DataSetCalcFields   = "Вычисление полей";
const char *DataSetFilter       = "Фильтрация";
const char *DataSetNewValue     = "Новое значение";
const char *DataSetOldValue     = "Старое значение полей";
const char *DataSetCurValue     = "Текущее значение";
const char *DataSetBlockRead    = "Блокировка отображения";
const char *DataSetInternalCalc = "Внутреннее вычисление";
const char *DataSetOpening      = "Открытие";
const char *NotFindDataModule  = "Не найден DataModule ";
const char *NotFindDataSet     = "Не найден DataSet ";
const char *DeletedRow         = "Удалить строку ?";
const char *Attention          = "Пожалуйста, внимание!";
const char *SearchNotPossible  = "Поиск невозможен при закрытом DataSet";
const char *AttemptSearchEmpty = "Попытка искать пустые значения!";
const char *RecordNotFind      = "Строка не найдена";
const char *FieldSearchNotDefined = "Не определено поле для поиска";
const char *ReportOptions         = "Свойства отчета ";
const char *NodeNotFind        = "Ветка не найдена";
const char *NodeNotUnerstand   = "Непонятная ветка TСWDBTreeView";
const char *NodeImpossibleMove = "Нельзя перемещать ветку ";
const char *ToNode             = "\nна ветку ";
const char *MoveNode           = "Перемещать ветку ";
const char *ToNodeSample       = " на ветку ";
const char *NotUnderstandStartNode = "Непонятная начальная ветка TСWDBTreeView";
const char *SortOnlyWithinLimitsLevel = "Пожалуйста, сортируйте только в пределах уровня!";
const char *MoreAttentive      = "Пожалуйста, повнимательней";
const char *SortingIsImpossibleInThisCase = "Сортировка невозможна в данном случае!";
const char *TargetAndStartNodeEqual = "Целевая и начальная ветка равны!";
const char *TheNode            = "Ветку ";
const char *DeleteImpossible   = " удалять нельзя!";
const char *ToDeleteNode       = "Удалять ветку ";
const char *TheMergeNodeImpossible = "Невозможно слияние веток ";
const char *TheAnd             = " и ";
const char *InsertImpossible   = "Добавление невозможно";
const char *TheNewNodeText     = "<Новая!>";
const char *NodeAdminNotFound  = "NodeAdmin не найден";
const char *LocateNodeIsNull   = "->LocateNode == NULL";
const char *TooLargeLengthDecimalPart = "Слишком большая длина десятичной части";
const char *ToKeepChanges         = "Сохранить изменения ?\n";
const char *TheSymbol             = "Символ ";
const char *IsInadmissibleInLine  = " недопустим в преобразуемой строке";
const char *OnTheTree         = " по дереву";
const char *TheTextForSearch  = "Текст для поиска";
const char *IncorrectValue    = "Некорректная величина";
const char *ToMakeLevel       = "Сделать подуровень ветки\n";
const char *C_EditMaskDateFormatShort = "!99/99/9999;1;_";
const char *C_EditMaskDateFormatLong = "!99/99/9999 99:99:99;1;_";
const char *C_Doctor          = "Доктор";
String S_Doctor( C_Doctor );
String Enterprise( "ROSE." );
const String SerialValidChars( L"0123456789 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+-/\()<>{}_=:;*\t" );
String NlsNumericCharacters =  String( FormatSettings.DecimalSeparator  ) +
                               String( FormatSettings.ThousandSeparator );
String NlsDateFormatShort   =  String( "dd" ) + String( FormatSettings.DateSeparator ) +
                               String( "mm" ) + String( FormatSettings.DateSeparator ) +
                               String( "yyyy" );
String LongTimeFormat       =  String( "hh" ) + String( FormatSettings.TimeSeparator ) +
                               String( "nn" ) + String( FormatSettings.TimeSeparator ) +
                               String( "ss" );
String NlsDateFormatLong    =  String( "dd" ) + String( FormatSettings.DateSeparator ) +
                               String( "mm" ) + String( FormatSettings.DateSeparator ) +
                               String( "yyyy " ) +
                               String( "hh" ) + String( FormatSettings.TimeSeparator ) +
                               String( "nn" ) + String( FormatSettings.TimeSeparator ) +
                               String( "ss" );
String EditMaskDateFormatShort = C_EditMaskDateFormatShort;
String EditMaskDateFormatLong  = C_EditMaskDateFormatLong;
String StrEmptyDateLong  = String( "  " ) + String( FormatSettings.DateSeparator ) +
                           String( "  " ) + String( FormatSettings.DateSeparator ) +
                           String( "       " ) +
                           String( FormatSettings.TimeSeparator ) +  String( "  " ) +
                           String( FormatSettings.TimeSeparator ) +  String( "  " );
String StrEmptyDateShort = String( "  " ) + String( FormatSettings.DateSeparator ) +
                           String( "  " ) + String( FormatSettings.DateSeparator ) + String( "    " );
String SaveStrEmptyDateLong  = StrEmptyDateLong;
String SaveStrEmptyDateShort = StrEmptyDateShort;
const String FLOAT_FORMAT( "#,##0" );
const String SAMPLE_FLOAT_FORMAT( "###0" );
const String DBSearchDialogFilterKey( L"Диалог" );
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
const char *GenderMale   = "Мужской";
const char *GenderAvg    = "Средний";
const char *GenderFemale = "Женский";
const String strGenderMale(   GenderMale   );
const String strGenderAvg(    GenderAvg    );
const String strGenderFemale( GenderFemale );
const unsigned int MaxTreeHistory = 32;
const unsigned int MaxFormHistory = 32;
const int limit_pick_list = 108;
const char *SorryNoExistsRight = "Право не определено!";
const char *SorryNoRight = "Извините, пожалуйста, но у Вас нет права ";
const double Epsilon = 0.0001;
const int CriticalFormPlaceDelta = 40;
const int CriticalFormPlaceMinus = 10;
const String AllAcount( "все" );
const String NullAcount( "пусто" );
const String Empty( "Пусто" );
const String NotEmpty( "Не пусто" );
const String SetTitle( "Выбор" );
const String SET_VARIABLE( "SET_VARIABLE" );
const String COMMA_TEMP_REPLACE( "!#@^&!@#" );
const char   *CharINFO = "INFO";
const String INFO( CharINFO );
const char   *CharAVANCE = "АВАНС";
const String AVANCE( CharAVANCE );
const char *NotAcceptAllEnterprise = "Недопустимы все предприятия";
const String Space( ' ' );
const String SingleCommas( "'" );
const String DoubleCommas( "\"" );
const String LeftScobka( "(" );
const String RightScobka( ")" );
const String FieldOff( "откл." );
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
const String TabletRest( "остаток" );
const char *NotValidBufferFormat = "Извините, пожалуйста, но формат буфера не подходит";
const char *Sorry = "Извините, пожалуйста, но ";
const char *SerialNotValid = "серийный номер не правильный! ";
const char* Filter = "Фильтр: ";
std::locale loc;
const t_char &char_o = std::use_facet< t_char >( loc );
TBufferType BufferType = btNone;
String ProgramDir;
const String BackSlash( "\\" );
const String Slash( "/" );
const String NodeDelimeter( " \\ " );
const String AltDelimeter( " / " );
const String PrabhupadaSlovarFiles( "./PrabhupadaSlovarFiles/" );
const char SystemDecimalSeparator  = FormatSettings.DecimalSeparator;
const char SystemThousandSeparator = FormatSettings.ThousandSeparator;
bool LocaleFormatRun = false;
bool IsLocaleFirst = true;
void __fastcall PrepareLocale( const String &NlsDateFormatLong_
                             , const String &NlsDateFormatShort_
                             , const String &EditMaskDateFormatLong_
                             , const String &EditMaskDateFormatShort_ )
{
  NlsNumericCharacters =  String( FormatSettings.DecimalSeparator  ) +
                          String( FormatSettings.ThousandSeparator );
  String ds( FormatSettings.DateSeparator ),
         ts( FormatSettings.TimeSeparator );
  FormatSettings.LongDateFormat        = NlsDateFormatLong_;
  FormatSettings.ShortDateFormat       = NlsDateFormatShort_;
  NlsDateFormatShort      = NNF::ReplaceStr( NlsDateFormatShort_, "/", ds );
  NlsDateFormatShort      = NNF::ReplaceStr( NlsDateFormatShort,  ":", ts );
  NlsDateFormatLong       = NNF::ReplaceStr( NlsDateFormatLong_,  "/", ds );
  NlsDateFormatLong       = NNF::ReplaceStr( NlsDateFormatLong,   ":", ts );
  EditMaskDateFormatShort = EditMaskDateFormatShort_;
  EditMaskDateFormatLong  = EditMaskDateFormatLong_;
  SaveStrEmptyDateLong    = StrEmptyDateLong;
  SaveStrEmptyDateShort   = StrEmptyDateShort;
  StrEmptyDateLong        = NNF::ReplaceStr( NlsDateFormatLong,  "d", Space );
  StrEmptyDateLong        = NNF::ReplaceStr( StrEmptyDateLong,   "m", Space );
  StrEmptyDateLong        = NNF::ReplaceStr( StrEmptyDateLong,   "y", Space );
  StrEmptyDateLong        = NNF::ReplaceStr( StrEmptyDateLong,   "h", Space );
  StrEmptyDateLong        = NNF::ReplaceStr( StrEmptyDateLong,   "n", Space );
  StrEmptyDateLong        = NNF::ReplaceStr( StrEmptyDateLong,   "s", Space );
  StrEmptyDateShort       = NNF::ReplaceStr( NlsDateFormatShort, "d", Space );
  StrEmptyDateShort       = NNF::ReplaceStr( StrEmptyDateShort,  "m", Space );
  StrEmptyDateShort       = NNF::ReplaceStr( StrEmptyDateShort,  "y", Space );
  StrEmptyDateShort       = NNF::ReplaceStr( StrEmptyDateShort,  "h", Space );
  StrEmptyDateShort       = NNF::ReplaceStr( StrEmptyDateShort,  "n", Space );
  StrEmptyDateShort       = NNF::ReplaceStr( StrEmptyDateShort,  "s", Space );
  if ( IsLocaleFirst ) {
    SaveStrEmptyDateLong  = StrEmptyDateLong;
    SaveStrEmptyDateShort = StrEmptyDateShort;
    IsLocaleFirst         = false;
  }
}
}
