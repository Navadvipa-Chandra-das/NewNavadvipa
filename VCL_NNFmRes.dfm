object fmvRes: TfmvRes
  Left = 0
  Top = 0
  Caption = 'fmvRes'
  ClientHeight = 281
  ClientWidth = 418
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  ShowHint = True
  OnActivate = FormActivate
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnDeactivate = FormDeactivate
  OnKeyDown = FormKeyDown
  OnMouseDown = FormMouseDown
  PixelsPerInch = 96
  TextHeight = 13
  object fbRes: TNNVFlagBox
    Left = 84
    Top = 48
  end
  object coRes: TNNVConfig
    OnLoad = coResLoad
    OnSave = coResSave
    Left = 113
    Top = 48
  end
  object rrRes: TNNVRight
    Left = 141
    Top = 48
  end
  object alRes: TNNVActionList
    Left = 198
    Top = 48
    object aActionListSetup: TAction
      Category = 'Setup'
      Caption = #1043#1086#1088#1103#1095#1080#1077' '#1082#1083#1072#1074#1080#1096#1080
      Hint = #1043#1086#1088#1103#1095#1080#1077' '#1082#1083#1072#1074#1080#1096#1080
      ImageIndex = 21
      OnExecute = aActionListSetupExecute
    end
    object aRelease: TAction
      Category = 'Setup'
      Caption = #1040#1074#1072#1088#1080#1081#1085#1086#1077' '#1079#1072#1082#1088#1099#1090#1080#1077' '#1086#1082#1085#1072
      Hint = #1040#1074#1072#1088#1080#1081#1085#1086#1077' '#1079#1072#1082#1088#1099#1090#1080#1077' '#1086#1082#1085#1072
      ImageIndex = 62
      OnExecute = aReleaseExecute
    end
    object aClearCase: TAction
      Category = 'Setup'
      Caption = #1055#1091#1089#1090#1086#1081' '#1074#1099#1073#1086#1088
      Hint = #1055#1091#1089#1090#1086#1081' '#1074#1099#1073#1086#1088
      ImageIndex = 116
      OnExecute = aClearCaseExecute
    end
    object aPrepareLanguage: TAction
      Category = 'Setup'
      Caption = #1055#1086#1076#1075#1086#1090#1086#1074#1080#1090#1100' '#1103#1079#1099#1082
      Hint = #1055#1086#1076#1075#1086#1090#1086#1074#1080#1090#1100' '#1103#1079#1099#1082
      ImageIndex = 169
      OnExecute = aPrepareLanguageExecute
    end
  end
  object lnRes: TNNVLanguage
    Left = 169
    Top = 48
  end
end
