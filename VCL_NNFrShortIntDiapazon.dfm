inherited frvShortIntDiapazon: TfrvShortIntDiapazon
  Width = 230
  ExplicitWidth = 230
  inherited tbrDiapazon: TToolBar
    Width = 230
    ExplicitWidth = 230
    object neBegin: TNNVNumberEdit
      Left = 0
      Top = 0
      Width = 96
      Height = 22
      MaxLength = 6
      TabOrder = 1
      NumberKind = ShortInt
      IsUserCanChangeCheckStyle = True
    end
    object neEnd: TNNVNumberEdit
      Left = 96
      Top = 0
      Width = 96
      Height = 22
      MaxLength = 6
      TabOrder = 0
      NumberKind = ShortInt
      IsUserCanChangeCheckStyle = True
    end
    object tbApplyDiapazon: TToolButton
      Left = 192
      Top = 0
      Action = aApplyDiapazon
      DropdownMenu = pmDiapazonKind
      PopupMenu = pmDiapazonKind
      Wrap = True
      Style = tbsDropDown
    end
  end
  inherited pmDiapazonKind: TPopupMenu
    Left = 6
    Top = 65534
  end
  inherited alDiapazon: TActionList
    Left = 27
    Top = 65532
    object aApplyDiapazon: TAction
      Category = 'Diapazon'
      Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100' '#1076#1080#1072#1087#1072#1079#1086#1085
      Hint = #1055#1088#1080#1084#1077#1085#1080#1090#1100' '#1076#1080#1072#1087#1072#1079#1086#1085
      OnExecute = aApplyDiapazonExecute
    end
  end
end
