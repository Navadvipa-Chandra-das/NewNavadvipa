inherited frvLongLongIntDiapazon: TfrvLongLongIntDiapazon
  Width = 398
  ExplicitWidth = 398
  inherited tbrDiapazon: TToolBar
    Width = 398
    ExplicitWidth = 398
    object neBegin: TNNVNumberEdit
      Left = 0
      Top = 0
      Width = 180
      Height = 22
      MaxLength = 20
      TabOrder = 0
      NumberKind = LongLongInt
      IsUserCanChangeCheckStyle = True
    end
    object neEnd: TNNVNumberEdit
      Left = 180
      Top = 0
      Width = 180
      Height = 22
      MaxLength = 20
      TabOrder = 1
      NumberKind = LongLongInt
      IsUserCanChangeCheckStyle = True
    end
    object tbApplyDiapazon: TToolButton
      Left = 360
      Top = 0
      Action = aApplyDiapazon
      DropdownMenu = pmDiapazonKind
      PopupMenu = pmDiapazonKind
      Wrap = True
      Style = tbsDropDown
    end
  end
  inherited pmDiapazonKind: TPopupMenu
    Top = 10
  end
  inherited alDiapazon: TActionList
    Top = 9
    object aApplyDiapazon: TAction
      Category = 'Diapazon'
      Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100' '#1076#1080#1072#1087#1072#1079#1086#1085
      Hint = #1055#1088#1080#1084#1077#1085#1080#1090#1100' '#1076#1080#1072#1087#1072#1079#1086#1085
      ImageIndex = 5
      OnExecute = aApplyDiapazonExecute
    end
  end
end
