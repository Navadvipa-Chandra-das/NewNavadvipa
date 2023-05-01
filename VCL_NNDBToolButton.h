// ---------------------------------------------------------------------------
#ifndef VCL_NNDBToolButtonH
#define VCL_NNDBToolButtonH
// ---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <Vcl.Controls.hpp>
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.DBCtrls.hpp>
// ---------------------------------------------------------------------------

class PACKAGE TNNVDBToolButton : public TToolButton {
private:
  using inherited = TToolButton;
  TFieldDataLink* FDataLink;
  bool fWork;
  int fCheckImageIndex;
  int fUnCheckImageIndex;
  bool fAllowDown;
  bool fAllowUp;
  TDataSource* __fastcall GetDataSource();
  void __fastcall SetDataSource(TDataSource* Value);

  String __fastcall GetDataField() {
    return FDataLink->FieldName;
  };
  void __fastcall SetDataField(const String Value);

  TField* __fastcall GetField() {
    return FDataLink->Field;
  };

  bool __fastcall GetReadOnly() {
    return FDataLink->ReadOnly;
  };

  void __fastcall SetReadOnly(bool Value) {
    FDataLink->ReadOnly = Value;
  };
  void __fastcall DataChange(TObject *Sender);
  bool __fastcall StoreUnCheckImageIndex();

protected:
  virtual void __fastcall Notification(TComponent* AComponent,
      TOperation Operation);
  virtual void __fastcall Loaded(void);

public:
  __fastcall TNNVDBToolButton(TComponent* Owner);

  __fastcall ~TNNVDBToolButton() {
    delete FDataLink;
    FDataLink = NULL;
  };
  DYNAMIC void __fastcall Click();
  __property TField *Field = { read = GetField };
  __property int CheckImageIndex = { read = fCheckImageIndex, write = fCheckImageIndex };
  __property bool ReadOnly = { read = GetReadOnly, write = SetReadOnly };
  __property bool AllowDown = { read = fAllowDown, write = fAllowDown };
  __property bool AllowUp = { read = fAllowUp, write = fAllowUp };

__published:
  __property TDataSource* DataSource = { read = GetDataSource, write = SetDataSource };
  __property String DataField = { read = GetDataField, write = SetDataField };
  __property Style = { default = tbsCheck };
  __property int UnCheckImageIndex = { read = fUnCheckImageIndex, write = fUnCheckImageIndex, stored = StoreUnCheckImageIndex };
};
// ---------------------------------------------------------------------------
#endif
