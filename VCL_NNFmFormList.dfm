inherited fmvFormList: TfmvFormList
  Left = 192
  Top = 108
  BorderStyle = bsToolWindow
  Caption = #1054#1090#1082#1088#1099#1090#1099#1077' '#1086#1082#1085#1072
  ClientHeight = 212
  ClientWidth = 289
  Position = poScreenCenter
  OnKeyUp = FormKeyUp
  OnShow = FormShow
  ExplicitWidth = 295
  ExplicitHeight = 241
  PixelsPerInch = 96
  TextHeight = 13
  object lbForm: TListBox [0]
    Left = 0
    Top = 0
    Width = 289
    Height = 177
    ItemHeight = 13
    TabOrder = 0
    OnDblClick = lbFormDblClick
  end
  object buOK: TButton [1]
    Left = 64
    Top = 184
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object buCancel: TButton [2]
    Left = 152
    Top = 184
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
  inherited coRes: TNNVConfig
    StoreKind = skFiler
  end
end
