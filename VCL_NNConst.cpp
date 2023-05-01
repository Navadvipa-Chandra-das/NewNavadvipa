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
const char *NotValidLogic = "Такого быть не должно";
const char *OraclePackageNotDefine = "->OraclePackage не определен";
const char *OracleSessionNotDefine = "->OracleSession не определена";
const char *OracleSessionNotConnected = "->OracleSession не открыта";
const String TableUserReg = L"\"UserReg\"";
const String FieldUserRegKey = L"\"UserRegKey\"";
const String FieldUserData = L"\"UserData\"";
const char *OtherUserChangeRecord =
    "Другой пользователь изменил эту запись, поле ";
String FieldUserChange;
const char *RecordNotChanged = "Не изменена";
const char *RecordChanged = "Изменена";
const char *RecordInserted = "Вставлена";
const char *RecordDeleted = "Удалена";
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
const char *NotExistDialogForm = "Не определена форма диалога для ";
const char *Navadvipa = "Навадвипа";
const char *LogoStr =
    "Бухгалтерская программа \"Троянда\" тел. (06257) 4-35-45";
const char *CWFloatFormatNote =
    "Форматирует число до указанного кол-ва знаков после запятой";
const char *CWStrToFloatNote = "Преобразует строку в реальное число";
const char *CWStrToFloatDefNote =
    "Преобразует строку в реальное число, если неудается, то возвращает умолчание" ", которое передается во втором параметре";
const char *CWFormatStrDefNote =
    "Возвращает строку формата для чисел с нужным округлением";
const char *LogoStrNote = "Имя программы + телефон";
const char *DataSetNotActive = "Не активна";
const char *DataSetBrowse = "Просмотр";
const char *DataSetEdit = "Редактирование";
const char *DataSetInsert = "Добавление";
const char *DataSetSetKey = "Установка ключа";
const char *DataSetCalcFields = "Вычисление полей";
const char *DataSetFilter = "Фильтрация";
const char *DataSetNewValue = "Новое значение";
const char *DataSetOldValue = "Старое значение полей";
const char *DataSetCurValue = "Текущее значение";
const char *DataSetBlockRead = "Блокировка отображения";
const char *DataSetInternalCalc = "Внутреннее вычисление";
const char *DataSetOpening = "Открытие";
const char *NotFindDataModule = "Не найден DataModule ";
const char *NotFindDataSet = "Не найден DataSet ";
const char *DeletedRow = "Удалить строку ?";
const char *Attention = "Пожалуйста, внимание!";
const char *AttemptSearchEmpty = "Попытка искать пустые значения!";
const char *RecordNotFind = "Строка не найдена";
const char *FieldSearchNotDefined = "Не определено поле для поиска";
const char *ReportOptions = "Свойства отчета ";
const char *NodeNotFind = "Ветка не найдена";
const char *NodeNotUnerstand = "Непонятная ветка TСWDBTreeView";
const char *NodeImpossibleMove = "Нельзя перемещать ветку ";
const char *ToNode = "\nна ветку ";
const char *MoveNode = "Перемещать ветку ";
const char *ToNodeSample = " на ветку ";
const char *NotUnderstandStartNode = "Непонятная начальная ветка TСWDBTreeView";
const char *SortOnlyWithinLimitsLevel =
    "Пожалуйста, сортируйте только в пределах уровня!";
const char *MoreAttentive = "Пожалуйста, повнимательней";
const char *SortingIsImpossibleInThisCase =
    "Сортировка невозможна в данном случае!";
const char *TargetAndStartNodeEqual = "Целевая и начальная ветка равны!";
const char *TheNode = "Ветку ";
const char *DeleteImpossible = " удалять нельзя!";
const char *ToDeleteNode = "Удалять ветку ";
const char *TheMergeNodeImpossible = "Невозможно слияние веток ";
const char *TheAnd = " и ";
const char *InsertImpossible = "Добавление невозможно";
const char *TheNewNodeText = "<Новая!>";
const char *NodeAdminNotFound = "NodeAdmin не найден";
const char *LocateNodeIsNull = "->LocateNode == NULL";
const char *TooLargeLengthDecimalPart =
    "Слишком большая длина десятичной части";
const char *ToKeepChanges = "Сохранить изменения ?\n";
const char *TheSymbol = "Символ ";
const char *IsInadmissibleInLine = " недопустим в преобразуемой строке";
const char *OnTheTree = " по дереву";
const char *TheTextForSearch = "Текст для поиска";
const char *IncorrectValue = "Некорректная величина";
const char *ToMakeLevel = "Сделать подуровень ветки\n";
const char *C_EditMaskDateFormatShort = "!99/99/9999;1;_";
const char *C_EditMaskDateFormatLong = "!99/99/9999 99:99:99;1;_";
const char *C_Doctor = "Доктор";
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
const char *GenderMale = "Мужской";
const char *GenderAvg = "Средний";
const char *GenderFemale = "Женский";
const String strGenderMale( GenderMale );
const String strGenderAvg( GenderAvg );
const String strGenderFemale( GenderFemale );
const unsigned int MaxTreeHistory = 32;
const unsigned int MaxFormHistory = 32;
const int limit_pick_list = 108;
const char *SorryNoExistsRight = "Право не определено!";
const char *SorryNoRight = "Извините, пожалуйста, но у Вас нет права ";
const double Epsilon = 0.0001;
const int CriticalFormPlaceDelta = 40;
const int CriticalFormPlaceMinus = 10;
const String AllAcount( L"все" );
const String NullAcount( L"пусто" );
const String Empty( L"Пусто" );
const String NotEmpty( L"Не пусто" );
const String SetTitle( L"Выбор" );
const String SET_VARIABLE( L"SET_VARIABLE" );
const String COMMA_TEMP_REPLACE( L"!#@^&!@#" );
const char *CharINFO = "INFO";
const String INFO( CharINFO );
const char *CharAVANCE = "АВАНС";
const String AVANCE( CharAVANCE );
const char *NotAcceptAllEnterprise = "Недопустимы все предприятия";
const String Space( L" " );
const String EmptyStr( L"" );
const String SingleCommas( L"'" );
const String DoubleCommas( L"\"" );
const String LeftScobka( L"(" );
const String RightScobka( L")" );
const String FieldOff( L"откл." );
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
const char *NotValidBufferFormat =
    "Извините, пожалуйста, но формат буфера не подходит";
const char *Sorry = "Извините, пожалуйста, но ";
const char *SerialNotValid = "серийный номер не правильный!";
const char* Filter = "Фильтр: ";
const char* Search = "Поиск: ";
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
