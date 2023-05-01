inherited fmfActionList: TfmfActionList
  Caption = #1043#1086#1088#1103#1095#1080#1077' '#1082#1083#1072#1074#1080#1096#1080
  DesignerMasterStyle = 0
  object paAction: TPanel [0]
    Align = Bottom
    Position.Y = 448.000000000000000000
    Size.Width = 640.000000000000000000
    Size.Height = 32.000000000000000000
    Size.PlatformDefault = False
    TabOrder = 5
    object buSet: TButton
      Anchors = [akTop, akRight]
      Position.X = 232.000000000000000000
      Position.Y = 4.000000000000000000
      Size.Width = 75.000000000000000000
      Size.Height = 25.000000000000000000
      Size.PlatformDefault = False
      TabOrder = 1
      TabStop = False
      Text = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100
    end
  end
  object edAction: TEdit [1]
    Touch.InteractiveGestures = [LongTap, DoubleTap]
    Align = Bottom
    TabOrder = 2
    TabStop = False
    ReadOnly = True
    Position.Y = 426.000000000000000000
    Size.Width = 640.000000000000000000
    Size.Height = 22.000000000000000000
    Size.PlatformDefault = False
  end
  inherited fbRes: TNNFFlagBox
    Left = 252
  end
  inherited coRes: TNNFConfig
    Left = 224
  end
end
