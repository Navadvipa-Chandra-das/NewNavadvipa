inherited fmvLogin: TfmvLogin
  ActiveControl = frvLogin.edPassword
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1051#1086#1075#1080#1085' '#1073#1080#1073#1083#1080#1086#1090#1077#1082#1080' '#1053#1080#1078#1085#1077#1081' '#1053#1072#1074#1072#1076#1074#1080#1087#1099
  ClientHeight = 238
  ClientWidth = 362
  Constraints.MinHeight = 208
  Constraints.MinWidth = 362
  OldCreateOrder = True
  Position = poScreenCenter
  ExplicitWidth = 368
  ExplicitHeight = 267
  PixelsPerInch = 96
  TextHeight = 13
  inline frvLogin: TfrvLogin [0]
    Left = 0
    Top = 0
    Width = 362
    Height = 238
    Align = alClient
    TabOrder = 0
    ExplicitWidth = 362
    ExplicitHeight = 208
    inherited imLogin: TImage
      Width = 362
      Height = 238
      ExplicitLeft = 0
      ExplicitTop = 10
      ExplicitWidth = 437
      ExplicitHeight = 229
    end
    inherited edPort: TEdit
      Text = '5432'
    end
  end
  inherited fbRes: TNNVFlagBox [1]
  end
  inherited coRes: TNNVConfig [2]
    StoreKind = skFile
    UseUserNameInRegistryKey = False
  end
  inherited rrRes: TNNVRight [3]
  end
  inherited alRes: TNNVActionList [4]
  end
end
