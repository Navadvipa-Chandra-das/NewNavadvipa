object frvLogin: TfrvLogin
  Left = 0
  Top = 0
  Width = 345
  Height = 237
  TabOrder = 0
  object imLogin: TImage
    Left = 0
    Top = 0
    Width = 345
    Height = 237
    Align = alClient
    ExplicitLeft = 208
    ExplicitTop = 37
    ExplicitWidth = 105
    ExplicitHeight = 105
  end
  object laUser: TLabel
    Left = 24
    Top = 13
    Width = 72
    Height = 13
    Caption = '&'#1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1100
    FocusControl = cbUser
    OnClick = LabelClick
  end
  object laPassword: TLabel
    Left = 24
    Top = 40
    Width = 37
    Height = 13
    Caption = #1055#1072'&'#1088#1086#1083#1100
    FocusControl = edPassword
    OnClick = LabelClick
  end
  object laDatabase: TLabel
    Left = 24
    Top = 75
    Width = 65
    Height = 13
    Caption = '&'#1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093
    FocusControl = edDatabase
    OnClick = LabelClick
  end
  object laServer: TLabel
    Left = 24
    Top = 107
    Width = 37
    Height = 13
    Caption = '&'#1057#1077#1088#1074#1077#1088
    FocusControl = edServer
    OnClick = LabelClick
  end
  object laPort: TLabel
    Left = 24
    Top = 138
    Width = 25
    Height = 13
    Caption = #1055#1086#1088'&'#1090
    FocusControl = edPort
    OnClick = LabelClick
  end
  object laSchema: TLabel
    Left = 24
    Top = 170
    Width = 31
    Height = 13
    Caption = #1057#1093#1077'&'#1084#1072
    FocusControl = edSchema
    OnClick = LabelClick
  end
  object cbUser: TComboBox
    Left = 116
    Top = 10
    Width = 189
    Height = 21
    TabOrder = 0
  end
  object edPassword: TEdit
    Left = 116
    Top = 40
    Width = 189
    Height = 21
    PasswordChar = '*'
    TabOrder = 1
  end
  object edDatabase: TEdit
    Left = 116
    Top = 72
    Width = 189
    Height = 21
    TabOrder = 2
  end
  object edServer: TEdit
    Left = 116
    Top = 104
    Width = 189
    Height = 21
    TabOrder = 3
  end
  object edPort: TEdit
    Left = 116
    Top = 135
    Width = 189
    Height = 21
    TabOrder = 4
  end
  object chbResetConfig: TCheckBox
    Left = 116
    Top = 205
    Width = 97
    Height = 17
    Caption = #1057#1073#1088#1086#1089' &'#1085#1072#1089#1090#1088#1086#1077#1082
    TabOrder = 6
  end
  object edSchema: TEdit
    Left = 116
    Top = 167
    Width = 189
    Height = 21
    TabOrder = 5
  end
end
