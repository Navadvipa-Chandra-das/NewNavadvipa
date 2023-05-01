inherited fmvLock: TfmvLock
  ActiveControl = edPassword
  BorderStyle = bsToolWindow
  Caption = ''
  ClientHeight = 97
  ClientWidth = 283
  ExplicitWidth = 289
  ExplicitHeight = 126
  PixelsPerInch = 96
  TextHeight = 13
  object laUser: TLabel [0]
    Left = 7
    Top = 6
    Width = 72
    Height = 13
    Caption = '&'#1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1100
    FocusControl = edUser
  end
  object laPassword: TLabel [1]
    Left = 7
    Top = 33
    Width = 37
    Height = 13
    Caption = #1055#1072'&'#1088#1086#1083#1100
    FocusControl = edPassword
  end
  object edUser: TEdit [2]
    Left = 99
    Top = 3
    Width = 180
    Height = 21
    ReadOnly = True
    TabOrder = 0
  end
  object edPassword: TEdit [3]
    Left = 99
    Top = 33
    Width = 180
    Height = 21
    PasswordChar = '*'
    TabOrder = 1
  end
  object buUnLock: TButton [4]
    Left = 52
    Top = 61
    Width = 180
    Height = 25
    Caption = '&'#1056#1072#1079#1073#1083#1086#1082#1080#1088#1086#1074#1072#1090#1100
    Default = True
    ImageIndex = 22
    Images = dmvNewNavadvipa.ilDB
    TabOrder = 2
    OnClick = buUnLockClick
  end
  inherited fbRes: TNNVFlagBox
    Left = 67
    Top = 41
  end
  inherited coRes: TNNVConfig
    Left = 96
    Top = 41
  end
  inherited rrRes: TNNVRight
    Left = 123
    Top = 41
  end
  inherited alRes: TNNVActionList
    Left = 151
    Top = 41
    object aPrepareLock: TAction
      Category = 'Setup'
      Caption = 'aPrepareLock'
      ImageIndex = 10
    end
    object aPrepareUnLock: TAction
      Category = 'Setup'
      Caption = 'aPrepareUnLock'
      ImageIndex = 15
    end
  end
end
