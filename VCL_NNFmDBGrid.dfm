inherited fmvDBGrid: TfmvDBGrid
  Left = 272
  Top = 110
  BorderStyle = bsSizeToolWin
  Caption = #1057#1074#1086#1081#1089#1090#1074#1072' '#1090#1072#1073#1083#1080#1094#1099
  ClientHeight = 347
  ClientWidth = 374
  Constraints.MinHeight = 386
  Constraints.MinWidth = 390
  OldCreateOrder = True
  OnActivate = nil
  ExplicitWidth = 390
  ExplicitHeight = 386
  PixelsPerInch = 96
  TextHeight = 13
  object paProperty: TNNVPanel [0]
    Left = 0
    Top = 196
    Width = 374
    Height = 151
    Align = alBottom
    Ctl3D = True
    ParentCtl3D = False
    TabOrder = 1
    TabStop = True
    object edTitleCaption: TEdit
      Left = 0
      Top = 130
      Width = 374
      Height = 21
      Hint = #1047#1072#1075#1086#1083#1086#1074#1086#1082' '#1089#1090#1086#1083#1073#1094#1072
      Align = alBottom
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 5
      Text = 'edTitleCaption'
      OnChange = edTitleCaptionChange
    end
    object cbConfirmDelete: TCheckBox
      Tag = 10
      Left = 88
      Top = 86
      Width = 149
      Height = 17
      Caption = #1055#1086#1076#1090#1074#1077#1088#1078#1076#1072#1090#1100' '#1091#1076#1072#1083#1077#1085#1080#1077
      TabOrder = 1
      OnClick = cbGridOption
    end
    object cbTitle: TCheckBox
      Tag = 2
      Left = 4
      Top = 87
      Width = 81
      Height = 17
      Caption = #1047#1072#1075#1086#1083#1086#1074#1082#1080
      TabOrder = 0
      OnClick = cbGridOption
    end
    object cbRowLines: TCheckBox
      Tag = 6
      Left = 4
      Top = 107
      Width = 81
      Height = 17
      Caption = #1043#1086#1088'. '#1083#1080#1085#1080#1080
      TabOrder = 3
      OnClick = cbGridOption
    end
    object cbColLines: TCheckBox
      Tag = 5
      Left = 88
      Top = 107
      Width = 81
      Height = 17
      Caption = #1042#1077#1088#1090'. '#1083#1080#1085#1080#1080
      TabOrder = 4
      OnClick = cbGridOption
    end
    object cbIsFilteredColumn: TCheckBox
      Tag = 5
      Left = 176
      Top = 107
      Width = 133
      Height = 17
      Caption = #1057#1090#1086#1083#1073#1077#1094' '#1092#1080#1083#1100#1090#1088#1091#1077#1090#1089#1103
      TabOrder = 6
      OnClick = cbIsFilteredColumnClick
    end
    object paPropertyT: TNNVPanel
      Left = 0
      Top = 0
      Width = 374
      Height = 81
      Align = alTop
      TabOrder = 7
      object rgFontOwner: TRadioGroup
        Left = 0
        Top = 0
        Width = 86
        Height = 81
        Align = alLeft
        Caption = #1042#1083#1072#1076#1077#1083#1077#1094
        ItemIndex = 2
        Items.Strings = (
          '&'#1058#1072#1073#1083#1080#1094#1072
          '&'#1047#1072#1075#1086#1083#1086#1074#1086#1082
          '&'#1057#1090#1086#1083#1073#1077#1094' ')
        TabOrder = 0
        OnClick = clGridClick
      end
      object paFontColor: TNNVPanel
        Left = 86
        Top = 0
        Width = 288
        Height = 81
        Align = alClient
        BorderWidth = 4
        TabOrder = 1
        DesignSize = (
          288
          81)
        object paColorFontT: TNNVPanel
          Left = 4
          Top = 4
          Width = 280
          Height = 41
          Align = alTop
          TabOrder = 0
          object paFont: TNNVPanel
            Left = 0
            Top = 0
            Width = 99
            Height = 41
            Hint = #1054#1073#1088#1072#1079#1077#1094' '#1096#1088#1080#1092#1090#1072
            Align = alClient
            BevelInner = bvLowered
            BevelOuter = bvRaised
            BorderWidth = 4
            Caption = #1054#1073#1088#1072#1079#1077#1094
            ParentBackground = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnDblClick = paFontDblClick
          end
          object paColor: TNNVPanel
            Left = 99
            Top = 0
            Width = 81
            Height = 41
            Hint = #1062#1074#1077#1090
            Align = alRight
            BevelInner = bvLowered
            BevelOuter = bvRaised
            BorderWidth = 4
            ParentBackground = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 1
            OnDblClick = paColorDblClick
          end
          object paColorFont: TNNVPanel
            Left = 180
            Top = 0
            Width = 100
            Height = 41
            Hint = #1062#1074#1077#1090' '#1096#1088#1080#1092#1090#1072
            Align = alRight
            BevelInner = bvLowered
            BevelOuter = bvRaised
            BorderWidth = 4
            ParentBackground = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 2
            OnDblClick = buFontColorClick
          end
        end
        object buFont: TButton
          Left = 17
          Top = 51
          Width = 62
          Height = 25
          Caption = '&'#1064#1088#1080#1092#1090
          TabOrder = 1
          OnClick = paFontDblClick
        end
        object buColor: TButton
          Left = 106
          Top = 51
          Width = 64
          Height = 25
          Anchors = [akTop, akRight]
          Caption = '&'#1062#1074#1077#1090
          TabOrder = 2
          OnClick = paColorDblClick
        end
        object buFontColor: TButton
          Left = 190
          Top = 51
          Width = 86
          Height = 25
          Anchors = [akTop, akRight]
          Caption = #1062'&'#1074#1077#1090' '#1096#1088#1080#1092#1090#1072
          TabOrder = 3
          OnClick = buFontColorClick
        end
      end
    end
    object cbTabs: TCheckBox
      Tag = 7
      Left = 248
      Top = 86
      Width = 83
      Height = 17
      Caption = #1058#1072#1073#1091#1083#1103#1094#1080#1103
      TabOrder = 2
      OnClick = cbGridOption
    end
  end
  object clGrid: TCheckListBox [1]
    Left = 0
    Top = 0
    Width = 374
    Height = 196
    OnClickCheck = clGridClickCheck
    Align = alClient
    ItemHeight = 13
    TabOrder = 0
    OnClick = clGridClick
  end
  inherited fbRes: TNNVFlagBox
    Left = 112
  end
  inherited coRes: TNNVConfig
    Left = 140
  end
  inherited rrRes: TNNVRight
    Left = 56
  end
  object fdGrid: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Left = 84
    Top = 48
  end
end
