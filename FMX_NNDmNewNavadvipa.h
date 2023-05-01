//---------------------------------------------------------------------------

#ifndef FMX_NNDmNewNavadvipaH
#define FMX_NNDmNewNavadvipaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "FMX_NNDmRes.h"
#include "FMX_NNLanguageManager.h"
#include "FMX_NNRightsManager.h"
#include "FMX_NNColor.h"
#include <FMX.ImgList.hpp>
#include <System.ImageList.hpp>
#include "FMX_NNDBMiracle.h"
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
#include <FireDAC.FMXUI.Wait.hpp>
#include <FireDAC.Moni.Base.hpp>
#include <FireDAC.Moni.RemoteClient.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.PG.hpp>
#include <FireDAC.Phys.PGDef.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.Phys.SQLite.hpp>
#include <FireDAC.Phys.SQLiteDef.hpp>
#include <FireDAC.Stan.ExprFuncs.hpp>
//---------------------------------------------------------------------------
class TdmfNewNavadvipa : public TdmfRes
{
__published:	// IDE-managed Components
  TImageList *ilDB;
  TNNFQuery *quDB;
  TFDConnection *conDB;
  TFDTransaction *trDB;
  TFDMoniRemoteClientLink *monDB;
  TNNFQuery *quCommodKind;
  TLargeintField *quCommodKindKindID;
  TLargeintField *quCommodKindParentID;
  TWideStringField *quCommodKindKind;
  TBooleanField *quCommodKindActual;
  TBooleanField *quCommodKindInPrice;
  TNNFQuery *quUsers;
  TLargeintField *quUsersUserID;
  TBooleanField *quUsersIsDeleted;
  TWideStringField *quUsersName;
  TWideStringField *quUsersNote;
  TSQLTimeStampField *quUsersBirthDate;
  TSQLTimeStampField *quUsersCreateDate;
  TADTField *quUsersAnketa;
  TWideStringField *quUsersAnketaFIO;
  TWideStringField *quUsersAnketaINN;
  TWideStringField *quUsersAnketaPassport;
  TWideStringField *quUsersAnketaPassportKemVydan;
  TDateField *quUsersAnketaPassportDate;
  TDataSource *dsUsers;
  TNNFQuery *quCommod;
  TLargeintField *quCommodEntityID;
  TLargeintField *quCommodKindID;
  TWideStringField *quCommodEntity;
  TBooleanField *quCommodActual;
  TFloatField *quCommodPrice;
  TDataSource *dsCommodKind;
  TDataSource *dsCommod;
  TNNFQuery *quColorKind;
  TLargeintField *quColorKindKindID;
  TLargeintField *quColorKindParentID;
  TWideStringField *quColorKindKind;
  TBooleanField *quColorKindActual;
  TDataSource *dsColorKind;
  TNNFQuery *quColor;
  TLargeintField *quColorEntityID;
  TLargeintField *quColorKindID;
  TWideStringField *quColorEntity;
  TBooleanField *quColorActual;
  TWideStringField *quColorEnumLiteral;
  TLargeintField *quColorVectorIndex;
  TIntegerField *quColorFonColor;
  TIntegerField *quColorFontColor;
  TIntegerField *quColorFonColorUser;
  TIntegerField *quColorFontColorUser;
  TDataSource *dsColor;
  TNNFQuery *quRightsKind;
  TLargeintField *quRightsKindKindID;
  TLargeintField *quRightsKindParentID;
  TWideStringField *quRightsKindKind;
  TBooleanField *quRightsKindActual;
  TDataSource *dsRightsKind;
  TNNFQuery *quRights;
  TLargeintField *quRightsEntityID;
  TLargeintField *quRightsKindID;
  TWideStringField *quRightsEntity;
  TBooleanField *quRightsActual;
  TWideStringField *quRightsLiteral;
  TLargeintField *quRightsVectorIndex;
  TDataSource *dsRights;
  TNNFQuery *quRoleKind;
  TLargeintField *quRoleKindKindID;
  TLargeintField *quRoleKindParentID;
  TWideStringField *quRoleKindKind;
  TBooleanField *quRoleKindActual;
  TNNFQuery *quRole;
  TLargeintField *quRoleEntityID;
  TLargeintField *quRoleKindID;
  TWideStringField *quRoleEntity;
  TBooleanField *quRoleActual;
  TDataSource *dsRoleKind;
  TDataSource *dsRole;
  TNNFQuery *quUserRights;
  TLargeintField *quUserRightsUserRightsID;
  TLargeintField *quUserRightsUserID;
  TLargeintField *quUserRightsEntityID;
  TBooleanField *quUserRightsIsPlus;
  TWideStringField *quUserRightsRight;
  TLargeintField *quUserRightsRightID;
  TDataSource *dsUserRights;
  TNNFQuery *quUserRoles;
  TLargeintField *quUserRolesUserRolesID;
  TLargeintField *quUserRolesUserID;
  TLargeintField *quUserRolesEntityID;
  TWideStringField *quUserRolesRole;
  TLargeintField *quUserRolesRoleID;
  TDataSource *dsUserRoles;
  TNNFQuery *quRoleRights;
  TLargeintField *quRoleRightsRoleRightsID;
  TLargeintField *quRoleRightsRoleID;
  TLargeintField *quRoleRightsEntityID;
  TWideStringField *quRoleRightsRight;
  TLargeintField *quRoleRightsRightID;
  TDataSource *dsRoleRights;
  TNNFQuery *quLanguageKind;
  TLargeintField *quLanguageKindKindID;
  TLargeintField *quLanguageKindParentID;
  TWideStringField *quLanguageKindKind;
  TBooleanField *quLanguageKindActual;
  TNNFQuery *quLanguage;
  TLargeintField *quLanguageEntityID;
  TLargeintField *quLanguageKindID;
  TWideStringField *quLanguageEntity;
  TBooleanField *quLanguageActual;
  TWideMemoField *quLanguageOriginal;
  TDataSource *dsLanguageKind;
  TDataSource *dsLanguage;
  TNNFQuery *quTranslate;
  TLargeintField *quTranslateTranslateID;
  TLargeintField *quTranslateLanguageID;
  TLargeintField *quTranslateLanguagesID;
  TWideMemoField *quTranslateTranslate;
  TWideStringField *quTranslateLanguages;
  TDataSource *dsTranslate;
  TNNFQuery *quLanguages;
  TLargeintField *quLanguagesLanguagesID;
  TWideStringField *quLanguagesLanguagesStringID;
  TWideStringField *quLanguagesLanguages;
  TDataSource *dsLanguages;
  TFDPhysPgDriverLink *PgDrLinkDB;
  TNNFRightsManager *rmDB;
  TNNFLanguageManager *lmDB;
  TFDPhysSQLiteDriverLink *SQLiteDrLinkDB;
  void __fastcall coDataLoad(TObject *Sender);
  void __fastcall coDataSave(TObject *Sender);
  void __fastcall conDBAfterConnect(TObject *Sender);
  void __fastcall DataModuleCreate(TObject *Sender);
  void __fastcall conDBBeforeConnect(TObject *Sender);
private:	// User declarations
  using inherited = TdmfRes;
  NNF::TDoLogin FOnLogin;
  String FPseudoPassword;
  NNF::TBufferIntBox FBufferIntBox;
  NNF::TColorVector FColorVector;
  NNF::TMapFiler FMapFiler;
  long long int FUserID = 0;
  String __fastcall GetUserName();
protected:
  virtual void __fastcall Loaded();
public:		// User declarations
  __fastcall TdmfNewNavadvipa( TComponent* Owner );
  __fastcall TdmfNewNavadvipa( TComponent* Owner
                             , NNF::TDoLogin AOnLogin );
  void __fastcall DoLogin();
  void __fastcall ResetConfig( const String &AUser, TNNFQuery *AQuery );
  void __fastcall CreateNewUser( const String &AUser
                               , const String &APassword
                               , const String &ARole
                               , bool IsSuperUser );
  void __fastcall InsertLanguageRow( const String &ALanguage
                                   , String &ATranslate
                                   , bool &ATranslateSet );
  void __fastcall PrepareLanguageOwner( const String &AOwnerString );
  void __fastcall UnPrepareLanguageOwner( TObject *Sender );
  long long int __fastcall GetUserID( const String &AUserName );
  void __fastcall AfterLogon( long long int AUserID );
  __property String UserName = { read = GetUserName };
  __property NNF::TColorVector ColorVector = { read = FColorVector };
  __property NNF::TMapFiler MapFiler = { read = FMapFiler };
  __property NNF::TDoLogin OnLogin = { read = FOnLogin, write = FOnLogin };
  __property String PseudoPassword = { read = FPseudoPassword, write = FPseudoPassword };
  __property NNF::TBufferIntBox BufferIntBox = { read = FBufferIntBox };
  __property long long int UserID = { read = FUserID };
};
//---------------------------------------------------------------------------
extern PACKAGE TdmfNewNavadvipa *dmfNewNavadvipa;
//---------------------------------------------------------------------------
#endif
