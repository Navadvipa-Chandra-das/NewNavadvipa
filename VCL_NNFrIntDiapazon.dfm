inherited frvIntDiapazon: TfrvIntDiapazon
  Width = 310
  ExplicitWidth = 310
  inherited tbrDiapazon: TToolBar
    Width = 310
    ExplicitWidth = 310
    object neBegin: TNNVNumberEdit
      Left = 0
      Top = 0
      Width = 136
      Height = 22
      MaxLength = 11
      TabOrder = 0
      NumberKind = Int
      IsUserCanChangeCheckStyle = True
    end
    object neEnd: TNNVNumberEdit
      Left = 136
      Top = 0
      Width = 136
      Height = 22
      MaxLength = 11
      TabOrder = 1
      NumberKind = Int
      IsUserCanChangeCheckStyle = True
    end
    object tbApplyDiapazon: TToolButton
      Left = 272
      Top = 0
      Action = aApplyDiapazon
      DropdownMenu = pmDiapazonKind
      PopupMenu = pmDiapazonKind
      Wrap = True
      Style = tbsDropDown
    end
  end
  inherited pmDiapazonKind: TPopupMenu
    Top = 7
  end
  inherited alDiapazon: TActionList
    Top = 6
    object aApplyDiapazon: TAction
      Category = 'Diapazon'
      Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100' '#1076#1080#1072#1087#1072#1079#1086#1085
      Hint = #1055#1088#1080#1084#1077#1085#1080#1090#1100' '#1076#1080#1072#1087#1072#1079#1086#1085
      ImageIndex = 5
      OnExecute = aApplyDiapazonExecute
    end
  end
end
