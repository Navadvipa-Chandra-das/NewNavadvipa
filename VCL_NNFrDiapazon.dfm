object frvDiapazon: TfrvDiapazon
  Left = 0
  Top = 0
  Width = 140
  Height = 22
  AutoSize = True
  TabOrder = 0
  object tbrDiapazon: TToolBar
    Left = 0
    Top = 0
    Width = 140
    Height = 22
    Align = alNone
    AutoSize = True
    Images = dmvNewNavadvipa.ilDB
    TabOrder = 0
  end
  object pmDiapazonKind: TPopupMenu
    Left = 1
    Top = 2
    object mipClearDiapazon: TMenuItem
      Action = aClearDiapazon
    end
    object mipSeparatorClear: TMenuItem
      Caption = '-'
    end
    object mipDiapazonKindInner: TMenuItem
      Action = aDiapazonKindInner
      GroupIndex = 1
      RadioItem = True
    end
    object mipDiapazonKindOuter: TMenuItem
      Action = aDiapazonKindOuter
      GroupIndex = 1
      RadioItem = True
    end
    object mipDiapazonKindHalhDiapazon: TMenuItem
      Action = aDiapazonKindHalfDiapazon
      GroupIndex = 1
      RadioItem = True
    end
    object mipDiapazonNull: TMenuItem
      Action = aDiapazonKindNull
      GroupIndex = 1
      RadioItem = True
    end
    object mipDiapazonNotNull: TMenuItem
      Action = aDiapazonKindNotNull
      GroupIndex = 1
      RadioItem = True
    end
  end
  object alDiapazon: TActionList
    Images = dmvNewNavadvipa.ilDB
    Left = 20
    Top = 1
    object aDiapazonKindInner: TAction
      Category = 'Diapazon'
      Caption = #1042#1085#1091#1090#1088#1077#1085#1085#1080#1081' '#1087#1077#1088#1080#1086#1076
      GroupIndex = 1
      Hint = #1042#1085#1091#1090#1088#1077#1085#1085#1080#1081' '#1087#1077#1088#1080#1086#1076
      ImageIndex = 10
      OnExecute = aDiapazonKindInnerExecute
    end
    object aDiapazonKindOuter: TAction
      Category = 'Diapazon'
      Caption = #1042#1085#1077#1096#1085#1080#1081' '#1087#1077#1088#1080#1086#1076
      GroupIndex = 1
      Hint = #1042#1085#1077#1096#1085#1080#1081' '#1087#1077#1088#1080#1086#1076
      ImageIndex = 99
      OnExecute = aDiapazonKindOuterExecute
    end
    object aDiapazonKindHalfDiapazon: TAction
      Category = 'Diapazon'
      Caption = #1055#1086#1083#1091#1087#1077#1088#1080#1086#1076
      GroupIndex = 1
      Hint = #1055#1086#1083#1091#1087#1077#1088#1080#1086#1076
      ImageIndex = 135
      OnExecute = aDiapazonKindHalfDiapazonExecute
    end
    object aDiapazonKindNull: TAction
      Category = 'Diapazon'
      Caption = #1055#1091#1089#1090#1086#1077' '#1079#1085#1072#1095#1077#1085#1080#1077
      Hint = #1055#1091#1089#1090#1086#1077' '#1079#1085#1072#1095#1077#1085#1080#1077
      ImageIndex = 90
      OnExecute = aDiapazonKindNullExecute
    end
    object aDiapazonKindNotNull: TAction
      Category = 'Diapazon'
      Caption = #1053#1077#1087#1091#1089#1090#1086#1077' '#1079#1085#1072#1095#1077#1085#1080#1077
      Hint = #1053#1077#1087#1091#1089#1090#1086#1077' '#1079#1085#1072#1095#1077#1085#1080#1077
      ImageIndex = 92
      OnExecute = aDiapazonKindNotNullExecute
    end
    object aSetDiapazon: TAction
      Category = 'Diapazon'
      Caption = 'aSetDiapazon'
      ImageIndex = 147
    end
    object aClearDiapazon: TAction
      Category = 'Diapazon'
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100
      Hint = #1054#1095#1080#1089#1090#1080#1090#1100
      ImageIndex = 116
      OnExecute = aClearDiapazonExecute
    end
  end
end
