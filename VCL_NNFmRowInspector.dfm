inherited fmvRowInspector: TfmvRowInspector
  Caption = #1048#1085#1089#1087#1077#1082#1090#1086#1088' '#1089#1090#1088#1086#1082#1080
  ClientHeight = 322
  ClientWidth = 530
  Constraints.MinWidth = 546
  OnKeyDown = SimpleKeyDownDialog
  ExplicitWidth = 546
  ExplicitHeight = 361
  PixelsPerInch = 96
  TextHeight = 13
  object sbSkip: TScrollBox [0]
    Left = 0
    Top = 0
    Width = 530
    Height = 286
    VertScrollBar.Tracking = True
    Align = alClient
    BorderStyle = bsNone
    TabOrder = 0
  end
  object paB: TNNVPanel [1]
    Left = 0
    Top = 286
    Width = 530
    Height = 36
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      530
      36)
    object buOK: TButton
      Left = 351
      Top = 4
      Width = 83
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = '&'#1055#1088#1080#1084#1077#1085#1080#1090#1100
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = buOKClick
    end
    object buClear: TButton
      Left = 441
      Top = 4
      Width = 82
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = '&'#1054#1090#1084#1077#1085#1080#1090#1100
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = buClearClick
    end
    object dnRowInspector: TDBNavigator
      Left = 28
      Top = 2
      Width = 116
      Height = 25
      VisibleButtons = [nbEdit, nbPost, nbCancel, nbRefresh]
      TabOrder = 0
    end
  end
  inherited coRes: TNNVConfig
    StoreKind = skFiler
    Top = 47
  end
end
