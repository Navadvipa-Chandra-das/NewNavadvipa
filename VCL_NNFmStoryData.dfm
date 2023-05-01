inherited fmvStoryData: TfmvStoryData
  Left = 328
  Top = 108
  BorderStyle = bsSizeToolWin
  Caption = #1059#1089#1090#1072#1085#1086#1074#1082#1072' '#1087#1086#1083#1077#1081
  ClientHeight = 183
  ClientWidth = 242
  Constraints.MinHeight = 222
  Constraints.MinWidth = 258
  Font.Charset = RUSSIAN_CHARSET
  ExplicitWidth = 258
  ExplicitHeight = 222
  PixelsPerInch = 96
  TextHeight = 13
  object paB: TNNVPanel [0]
    Left = 0
    Top = 157
    Width = 242
    Height = 26
    Align = alBottom
    TabOrder = 0
    object ToolBar1: TToolBar
      Left = 0
      Top = 0
      Width = 242
      Height = 24
      Caption = 'ToolBar1'
      Images = dmvNewNavadvipa.ilDB
      TabOrder = 0
      object tbAllSelect: TToolButton
        Left = 0
        Top = 0
        Action = aAllSelect
      end
      object tbNoneSelect: TToolButton
        Left = 23
        Top = 0
        Action = aNoneSelect
      end
      object tbInvertSelect: TToolButton
        Left = 46
        Top = 0
        Action = aInvertSelect
      end
      object ToolButton1: TToolButton
        Left = 69
        Top = 0
        Width = 8
        Caption = 'ToolButton1'
        ImageIndex = 118
        Style = tbsSeparator
      end
      object tbOK: TToolButton
        Left = 77
        Top = 0
        Action = aOK
      end
      object ToolButton3: TToolButton
        Left = 100
        Top = 0
        Action = aCancel
      end
    end
  end
  object clData: TCheckListBox [1]
    Left = 0
    Top = 0
    Width = 242
    Height = 157
    Align = alClient
    ItemHeight = 13
    TabOrder = 1
  end
  inherited coRes: TNNVConfig
    StoreKind = skFiler
  end
  inherited alRes: TNNVActionList
    object aAllSelect: TAction
      Category = 'Setup'
      Caption = #1042#1099#1076#1077#1083#1080#1090#1100' '#1074#1089#1077
      Hint = #1042#1099#1076#1077#1083#1080#1090#1100' '#1074#1089#1077
      ImageIndex = 176
      OnExecute = aAllSelectExecute
    end
    object aNoneSelect: TAction
      Category = 'Setup'
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100
      Hint = #1054#1095#1080#1089#1090#1080#1090#1100
      ImageIndex = 174
      OnExecute = aNoneSelectExecute
    end
    object aInvertSelect: TAction
      Category = 'Setup'
      Caption = #1053#1072#1086#1073#1086#1088#1086#1090
      Hint = #1053#1072#1086#1073#1086#1088#1086#1090
      ImageIndex = 117
      OnExecute = aInvertSelectExecute
    end
    object aOK: TAction
      Category = 'Setup'
      Caption = #1044#1077#1083#1072#1077#1084'!'
      Hint = #1044#1077#1083#1072#1077#1084'!'
      ImageIndex = 42
      ShortCut = 13
      OnExecute = aOKExecute
    end
    object aCancel: TAction
      Category = 'Setup'
      Caption = #1059#1093#1086#1076#1080#1084'!'
      Hint = #1059#1093#1086#1076#1080#1084'!'
      ImageIndex = 15
      ShortCut = 27
      OnExecute = aCancelExecute
    end
  end
end
