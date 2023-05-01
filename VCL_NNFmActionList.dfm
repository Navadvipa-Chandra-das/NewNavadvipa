inherited fmvActionList: TfmvActionList
  Left = 288
  Top = 146
  HelpContext = 4
  BorderStyle = bsSizeToolWin
  Caption = #1043#1086#1088#1103#1095#1080#1077' '#1082#1083#1072#1074#1080#1096#1080
  ClientHeight = 324
  Constraints.MinHeight = 363
  Constraints.MinWidth = 323
  OldCreateOrder = True
  OnResize = FormResize
  ExplicitHeight = 363
  PixelsPerInch = 96
  TextHeight = 13
  object paAction: TNNVPanel [0]
    Left = 0
    Top = 292
    Width = 418
    Height = 32
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      418
      32)
    object hkAction: THotKey
      Left = 4
      Top = 6
      Width = 221
      Height = 19
      Anchors = [akLeft, akTop, akRight]
      HotKey = 32833
      TabOrder = 0
    end
    object buSet: TButton
      Left = 232
      Top = 4
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100
      Default = True
      TabOrder = 1
      TabStop = False
      OnClick = buSetClick
    end
  end
  object dgAction: TNNVDrawGrid [1]
    Left = 0
    Top = 0
    Width = 418
    Height = 271
    Align = alClient
    ColCount = 2
    DefaultColWidth = 128
    DefaultRowHeight = 15
    DefaultDrawing = False
    FixedCols = 0
    RowCount = 2
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goRowSelect, goThumbTracking]
    TabOrder = 0
    OnDrawCell = dgActionDrawCell
    OnSelectCell = dgActionSelectCell
  end
  object edAction: TEdit [2]
    Left = 0
    Top = 271
    Width = 418
    Height = 21
    TabStop = False
    Align = alBottom
    ReadOnly = True
    TabOrder = 2
  end
  inherited fbRes: TNNVFlagBox
    Left = 252
  end
  inherited coRes: TNNVConfig
    Left = 224
  end
end
