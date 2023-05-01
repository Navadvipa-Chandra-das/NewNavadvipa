inherited fmvChangePassword: TfmvChangePassword
  BorderStyle = bsToolWindow
  Caption = #1057#1084#1077#1085#1072' '#1087#1072#1088#1086#1083#1103
  ClientHeight = 151
  ClientWidth = 374
  ExplicitWidth = 380
  ExplicitHeight = 180
  PixelsPerInch = 96
  TextHeight = 13
  object laUser: TLabel [0]
    Left = 16
    Top = 12
    Width = 72
    Height = 13
    Caption = #1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1100
  end
  object laOldPassword: TLabel [1]
    Left = 16
    Top = 45
    Width = 78
    Height = 13
    Caption = #1057#1090#1072#1088#1099#1081' '#1087#1072#1088#1086#1083#1100
    FocusControl = edOldPassword
    OnClick = LabelClick
  end
  object laNewPassword: TLabel [2]
    Left = 16
    Top = 76
    Width = 72
    Height = 13
    Caption = #1053#1086#1074#1099#1081' '#1087#1072#1088#1086#1083#1100
    FocusControl = edNewPassword
    OnClick = LabelClick
  end
  object laConfirmNewPassword: TLabel [3]
    Left = 16
    Top = 108
    Width = 122
    Height = 13
    Caption = #1055#1086#1076#1090#1074#1077#1088#1078#1076#1077#1085#1080#1077' '#1087#1072#1088#1086#1083#1103
    FocusControl = edConfirmNewPassword
    OnClick = LabelClick
  end
  object edOldPassword: TEdit [4]
    Left = 152
    Top = 42
    Width = 201
    Height = 21
    PasswordChar = '#'
    TabOrder = 1
  end
  object edNewPassword: TEdit [5]
    Left = 152
    Top = 73
    Width = 201
    Height = 21
    PasswordChar = '#'
    TabOrder = 2
  end
  object edConfirmNewPassword: TEdit [6]
    Left = 152
    Top = 105
    Width = 201
    Height = 21
    PasswordChar = '#'
    TabOrder = 3
  end
  object edUser: TEdit [7]
    Left = 152
    Top = 10
    Width = 201
    Height = 21
    TabOrder = 0
  end
  inherited fbRes: TNNVFlagBox
    Left = 60
    Top = 12
  end
  inherited coRes: TNNVConfig
    Left = 88
    Top = 12
  end
  inherited rrRes: TNNVRight
    Left = 116
    Top = 12
  end
  inherited alRes: TNNVActionList
    Left = 144
    Top = 12
  end
end
