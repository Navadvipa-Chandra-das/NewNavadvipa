// Wanderer library - author Oleg Zolotyh e-mail alejan@rambler.ru
#ifndef VCL_NNDBComboBoxDateTimeH
#define VCL_NNDBComboBoxDateTimeH
//---------------------------------------------------------------------------
#include "VCL_NNComboBoxDateTime.h"

class PACKAGE TNNVDBComboBoxDateTime : public TNNVComboBoxDateTime
{
private:
  using inherited = TNNVComboBoxDateTime;
  TFieldDataLink* FDataLink = nullptr;
  bool fWork;
  bool fWorkUpdateData;
  TDataSource* __fastcall GetDataSource();
  void __fastcall SetDataSource( TDataSource* Value );
  String __fastcall GetDataField();
  void __fastcall SetDataField( const String Value );
  TField* __fastcall GetField();
  bool __fastcall GetReadOnly();
  void __fastcall SetReadOnly( bool Value );
  void __fastcall DataChange( TObject *Sender );
  void __fastcall ForUpdateData( TObject *Sender );
protected:
  virtual void __fastcall Notification( TComponent *AComponent, TOperation Operation );
  virtual void __fastcall DoExecute();
  virtual void __fastcall SetIsEmpty( bool Value );
  virtual bool __fastcall IsNull();
public:
  __fastcall TNNVDBComboBoxDateTime( TComponent* Owner );
  __fastcall ~TNNVDBComboBoxDateTime();
  __property TField *Field = { read = GetField };
__published:
  __property bool ReadOnly = { read = GetReadOnly, write = SetReadOnly };
  __property String DataField = { read = GetDataField, write = SetDataField };
  __property TDataSource* DataSource = { read = GetDataSource, write = SetDataSource };
};
//---------------------------------------------------------------------------
#endif

