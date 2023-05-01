inherited frvPeriod: TfrvPeriod
  Width = 346
  ExplicitWidth = 346
  inherited tbrDiapazon: TToolBar
    Width = 346
    ExplicitWidth = 346
    object cbdBegin: TNNVComboBoxDateTime
      Left = 0
      Top = 0
      Width = 154
      Height = 22
      Enabled = False
      MaxLength = 19
      TabOrder = 0
      IsUserCanChangeCheckStyle = True
    end
    object cbdEnd: TNNVComboBoxDateTime
      Left = 154
      Top = 0
      Width = 154
      Height = 22
      MaxLength = 19
      TabOrder = 1
      IsUserCanChangeCheckStyle = True
    end
    object tbApplyDiapazon: TToolButton
      Left = 308
      Top = 0
      Action = aApplyDiapazon
      DropdownMenu = pmDiapazonKind
      PopupMenu = pmDiapazonKind
      Wrap = True
      Style = tbsDropDown
    end
  end
  inherited pmDiapazonKind: TPopupMenu
    Left = 55
    Top = 1
  end
  inherited alDiapazon: TActionList
    Left = 30
    object aApplyDiapazon: TAction
      Category = 'Diapazon'
      Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100' '#1076#1080#1072#1087#1072#1079#1086#1085
      Hint = #1055#1088#1080#1084#1077#1085#1080#1090#1100' '#1076#1080#1072#1087#1072#1079#1086#1085
      ImageIndex = 5
      OnExecute = aApplyDiapazonExecute
    end
  end
end
