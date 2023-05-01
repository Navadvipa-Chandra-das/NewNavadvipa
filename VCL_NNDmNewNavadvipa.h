// ---------------------------------------------------------------------------

#ifndef VCL_NNDmNewNavadvipaH
#define VCL_NNDmNewNavadvipaH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "VCL_NNDmRes.h"
#include "VCL_NNRightsManager.h"
#include <System.ImageList.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ImgList.hpp>
#include "VCL_NNDBMiracle.h"
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <Vcl.Dialogs.hpp>
#include <FireDAC.Moni.Base.hpp>
#include <FireDAC.Moni.RemoteClient.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.PG.hpp>
#include <FireDAC.Phys.PGDef.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Wait.hpp>
#include "VCL_NNCommon.h"
#include "VCL_NNColor.h"
#include "VCL_NNLanguageManager.h"
// ---------------------------------------------------------------------------

namespace NNV {

extern PACKAGE const long long int RootRightsKindID;
extern PACKAGE const long long int RootColorKindID;
extern PACKAGE const long long int RootCommodKindID;
extern PACKAGE const long long int RootRoleKindID;
extern PACKAGE const long long int RootLanguageKindID;

enum PACKAGE class TImagesKind : int {
    imAccount = 1
  , imAccount_a = 2
  , imAccount_p = 3
  , imAccount_u = 4
  , imMeasure = 5
  , imWorld = 8
  , imCurshist = 9
  , imReasonKind = 10
  , imCommod = 11
  , imCommodJ = 185
  , imCommodJJ = 184
  , imCommodNA = 12
  , imCommodNAJ = 183
  , imCommodNAJJ = 182
  , imCommodAss = 13
  , imContrAgent = 15
  , imContrAgentNA = 84
  , imService = 77
  , imServiceJ = 181
  , imServiceJJ = 180
  , imServiceNA = 78
  , imServiceNAJ = 179
  , imServiceNAJJ = 186
  , imPriceDetailKind = 23
  , imFixedAssetsKind = 24
  , imFixedAssetsKindNA = 85
  , imUMAssetsKind = 25
  , imUMAssetsKindNA = 86
  , imPrimKindStamp = 17
  , imPrimKind = 16
  , imPrimKindNA = 171
  , imOfficeDefault = 17
  , imGrid = 58
  , imSerial = 79
  , imSerialNA = 80
  , imDocument = 17
  , imDocumentNA = 89
  , imStorehouse = 90
  , imStorehouseNA = 91
  , imCash = 92
  , imCashNA = 93
  , imCalccount = 94
  , imCalccountNA = 95
  , imDepartment = 18
  , imDepartmentNA = 96
  , imEnterprise = 68
  , imSubconto = 67
  , imCurrency = 8
  , imOperdoc = 83
  , imOperdocNA = 99
  , imUsers = 100
  , imMessages = 14
  , imPower = 37
  , imSetup = 62
  , imRoles = 106
  , imPriceDetailKindP = 123
  , imPriceDetailKindPR = 124
  , imCashReason = 165
  , imCashReasonNA = 166
  , imDocfilter = 135
  , imVishnya = 147
  , imVishnyaNA = 148
  , imMera = 163
  , imMeraNA = 164
  , imCommodAcount = 154
  , imTablet = 172
  , imShowDocument = 74
  , imGreenLamp = 175
  , imRedLamp = 177
  , imTable = 69
};

}

class TdmvNewNavadvipa : public TdmvRes {
__published: // IDE-managed Components
  TImageList *ilDB;
  TNNVQuery *quDB;
  TColorDialog *cdNN;
  TNNVStoryData *sdDB;
  TFDConnection *conDB;
  TFDTransaction *trDB;
  TFDPhysPgDriverLink *PgDrLinkDB;
  TNNVRightsManager *rmDB;
  TFDMoniRemoteClientLink *monDB;
  TNNVQuery *quCommodKind;
  TLargeintField *quCommodKindKindID;
  TLargeintField *quCommodKindParentID;
  TWideStringField *quCommodKindKind;
  TBooleanField *quCommodKindActual;
  TBooleanField *quCommodKindInPrice;
  TNNVQuery *quUsers;
  TLargeintField *quUsersUserID;
  TBooleanField *quUsersIsDeleted;
  TWideStringField *quUsersName;
  TWideStringField *quUsersNote;
  TSQLTimeStampField *quUsersBirthDate;
  TSQLTimeStampField *quUsersCreateDate;
  TDataSource *dsUsers;
  TNNVQuery *quCommod;
  TDataSource *dsCommodKind;
  TDataSource *dsCommod;
  TADTField *quUsersAnketa;
  TWideStringField *quUsersAnketaFIO;
  TWideStringField *quUsersAnketaINN;
  TWideStringField *quUsersAnketaPassport;
  TWideStringField *quUsersAnketaPassportKemVydan;
  TDateField *quUsersAnketaPassportDate;
  TLargeintField *quCommodEntityID;
  TLargeintField *quCommodKindID;
  TWideStringField *quCommodEntity;
  TFloatField *quCommodPrice;
  TBooleanField *quCommodActual;
  TNNVQuery *quColorKind;
  TLargeintField *quColorKindKindID;
  TLargeintField *quColorKindParentID;
  TWideStringField *quColorKindKind;
  TBooleanField *quColorKindActual;
  TDataSource *dsColorKind;
  TNNVQuery *quColor;
  TLargeintField *quColorEntityID;
  TLargeintField *quColorKindID;
  TWideStringField *quColorEntity;
  TBooleanField *quColorActual;
  TDataSource *dsColor;
  TIntegerField *quColorFonColor;
  TIntegerField *quColorFontColor;
  TLargeintField *quColorVectorIndex;
  TWideStringField *quColorEnumLiteral;
  TIntegerField *quColorFonColorUser;
  TIntegerField *quColorFontColorUser;
  TNNVQuery *quRightsKind;
  TLargeintField *quRightsKindKindID;
  TLargeintField *quRightsKindParentID;
  TWideStringField *quRightsKindKind;
  TBooleanField *quRightsKindActual;
  TDataSource *dsRightsKind;
  TNNVQuery *quRights;
  TLargeintField *quRightsEntityID;
  TLargeintField *quRightsKindID;
  TWideStringField *quRightsEntity;
  TBooleanField *quRightsActual;
  TWideStringField *quRightsLiteral;
  TLargeintField *quRightsVectorIndex;
  TDataSource *dsRights;
  TNNVQuery *quRoleKind;
  TLargeintField *quRoleKindKindID;
  TLargeintField *quRoleKindParentID;
  TWideStringField *quRoleKindKind;
  TBooleanField *quRoleKindActual;
  TNNVQuery *quRole;
  TDataSource *dsRoleKind;
  TDataSource *dsRole;
  TNNVQuery *quUserRights;
  TDataSource *dsUserRights;
  TNNVQuery *quUserRoles;
  TDataSource *dsUserRoles;
  TLargeintField *quRoleEntityID;
  TLargeintField *quRoleKindID;
  TWideStringField *quRoleEntity;
  TBooleanField *quRoleActual;
  TLargeintField *quUserRightsUserRightsID;
  TLargeintField *quUserRightsUserID;
  TLargeintField *quUserRightsEntityID;
  TBooleanField *quUserRightsIsPlus;
  TLargeintField *quUserRolesUserRolesID;
  TLargeintField *quUserRolesUserID;
  TLargeintField *quUserRolesEntityID;
  TNNVQuery *quRoleRights;
  TDataSource *dsRoleRights;
  TLargeintField *quRoleRightsRoleRightsID;
  TLargeintField *quRoleRightsRoleID;
  TLargeintField *quRoleRightsEntityID;
  TWideStringField *quRoleRightsRight;
  TWideStringField *quUserRightsRight;
  TWideStringField *quUserRolesRole;
  TLargeintField *quRoleRightsRightID;
  TLargeintField *quUserRightsRightID;
  TLargeintField *quUserRolesRoleID;
  TNNVLanguageManager *lmDB;
  TNNVQuery *quLanguageKind;
  TLargeintField *quLanguageKindKindID;
  TLargeintField *quLanguageKindParentID;
  TWideStringField *quLanguageKindKind;
  TBooleanField *quLanguageKindActual;
  TNNVQuery *quLanguage;
  TLargeintField *quLanguageEntityID;
  TLargeintField *quLanguageKindID;
  TWideStringField *quLanguageEntity;
  TBooleanField *quLanguageActual;
  TDataSource *dsLanguageKind;
  TDataSource *dsLanguage;
  TNNVQuery *quTranslate;
  TDataSource *dsTranslate;
  TLargeintField *quTranslateTranslateID;
  TLargeintField *quTranslateLanguageID;
  TLargeintField *quTranslateLanguagesID;
  TWideMemoField *quTranslateTranslate;
  TWideMemoField *quLanguageOriginal;
  TNNVQuery *quLanguages;
  TDataSource *dsLanguages;
  TLargeintField *quLanguagesLanguagesID;
  TWideStringField *quLanguagesLanguagesStringID;
  TWideStringField *quLanguagesLanguages;
  TWideStringField *quTranslateLanguages;

  void __fastcall coDataLoad( TObject *Sender );
  void __fastcall coDataSave( TObject *Sender );
  void __fastcall DBGridColor( TNNVDBGrid *dg, long long int AColorNo );
  void __fastcall conDBBeforeConnect( TObject *Sender );
  void __fastcall DataModuleCreate( TObject *Sender );
  void __fastcall quCommodNewRecord( TDataSet *DataSet );
  void __fastcall dsCommodDataChange( TObject *Sender, TField *Field);
  void __fastcall dsColorDataChange( TObject *Sender, TField *Field );
  void __fastcall quColorNewRecord(TDataSet *DataSet);
  void __fastcall quColorCalcFields(TDataSet *DataSet);
  void __fastcall coDataDefault( TObject *Sender );
  void __fastcall quRightsNewRecord( TDataSet *DataSet );
  void __fastcall dsRoleDataChange( TObject *Sender, TField *Field);
  void __fastcall dsRightsDataChange( TObject *Sender, TField *Field);
  void __fastcall quRoleRightsNewRecord( TDataSet *DataSet);
  void __fastcall quRoleNewRecord( TDataSet *DataSet );
  void __fastcall quUserRightsNewRecord( TDataSet *DataSet );
  void __fastcall quUserRolesNewRecord( TDataSet *DataSet );
  void __fastcall conDBAfterConnect(TObject *Sender);
  void __fastcall rrDataRight( TObject *Sender );
  void __fastcall dsLanguageDataChange( TObject *Sender, TField *Field );
  void __fastcall quLanguageNewRecord( TDataSet *DataSet );
  void __fastcall quTranslateNewRecord( TDataSet *DataSet );
private: // User declarations
  using inherited = TdmvRes;
  String __fastcall GetUserName();
  NNV::TDoLogin FOnLogin;
  String FPseudoPassword;
  NNV::TBufferIntBox FBufferIntBox;
  NNV::TMapFiler FMapFiler;
  NNV::TColorVector FColorVector;
  long long int FUserID = 0;
protected:
  virtual void __fastcall Loaded();
  virtual void __fastcall DoLogin();
public: // User declarations
  __fastcall TdmvNewNavadvipa( TComponent* Owner );
  __fastcall TdmvNewNavadvipa( TComponent* Owner
                             , NNV::TDoLogin AOnLogin );
  __property NNV::TMapFiler MapFiler = { read = FMapFiler };
  __property NNV::TColorVector ColorVector = { read = FColorVector };
  void __fastcall ResetConfig( const String &AUser, TNNVQuery *AQuery );
  void __fastcall CreateNewUser( const String &AUser
                               , const String &APassword
                               , const String &ARole
                               , bool IsSuperUser );
  void __fastcall PrepareLanguageOwner( const String &AOwnerString );
  void __fastcall UnPrepareLanguageOwner( TObject *Sender );
  void __fastcall InsertLanguageRow( const String &ALanguage
                                   , String &ATranslate
                                   , bool &ATranslateSet );
  long long int __fastcall GetUserID( const String &AUserName );
  void __fastcall AfterLogon( long long int AUserID );
  void __fastcall SetNewUserPassword( const String &AUser
                                    , const String &APassword );
  void __fastcall DeleteUser( const String &AUser );
  void __fastcall SetUserRole( const String &AUser, const String &ARole, bool IsGrant );
  void __fastcall ChangePassword( TComponent *ASenderForm );
  void __fastcall SetIsDeletedUser( bool AIsDeleted );
  void __fastcall SetNodeParamsCommodKind( TNNVNodeParams &NodeParams );
  void __fastcall SetNodeParamsColorKind( TNNVNodeParams &NodeParams );
  void __fastcall SetNodeParamsRightsKind( TNNVNodeParams &NodeParams );
  void __fastcall SetNodeParamsRoleKind( TNNVNodeParams &NodeParams );
  void __fastcall SetNodeParamsLanguageKind( TNNVNodeParams &NodeParams );
  void __fastcall ColorIndexGenerate();
  void __fastcall RightsIndexGenerate();
  void __fastcall ColorVectorLoadFromDB();
  long long int __fastcall EntityIDToKindID( long long int AEntityID );

  __property String UserName = { read = GetUserName };
  __property NNV::TDoLogin OnLogin = { read = FOnLogin, write = FOnLogin };
  __property String PseudoPassword = { read = FPseudoPassword, write = FPseudoPassword };
  __property NNV::TBufferIntBox BufferIntBox = { read = FBufferIntBox };
  __property long long int UserID = { read = FUserID };
};

// ---------------------------------------------------------------------------
extern PACKAGE TdmvNewNavadvipa *dmvNewNavadvipa;
// ---------------------------------------------------------------------------
#endif

