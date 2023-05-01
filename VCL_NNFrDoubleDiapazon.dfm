inherited frvDoubleDiapazon: TfrvDoubleDiapazon
  Width = 406
  ExplicitWidth = 406
  inherited tbrDiapazon: TToolBar
    Width = 406
    ExplicitWidth = 406
    object neBegin: TNNVNumberEdit
      Left = 0
      Top = 0
      Width = 184
      Height = 22
      MaxLength = 25
      TabOrder = 0
      IsUserCanChangeCheckStyle = True
    end
    object neEnd: TNNVNumberEdit
      Left = 184
      Top = 0
      Width = 184
      Height = 22
      MaxLength = 25
      TabOrder = 1
      IsUserCanChangeCheckStyle = True
    end
    object tbApplyDiapazon: TToolButton
      Left = 368
      Top = 0
      Action = aApplyDiapazon
      DropdownMenu = pmDiapazonKind
      PopupMenu = pmDiapazonKind
      Wrap = True
      Style = tbsDropDown
    end
  end
  inherited pmDiapazonKind: TPopupMenu
    Left = 22
    Top = 65533
  end
  inherited alDiapazon: TActionList
    Left = 45
    Top = 65535
    object aApplyDiapazon: TAction
      Category = 'Diapazon'
      Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100' '#1076#1080#1072#1087#1072#1079#1086#1085
      Hint = #1055#1088#1080#1084#1077#1085#1080#1090#1100' '#1076#1080#1072#1087#1072#1079#1086#1085
      ImageIndex = 5
      OnExecute = aApplyDiapazonExecute
    end
  end
end
