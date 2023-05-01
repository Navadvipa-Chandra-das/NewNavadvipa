inherited fmvCode: TfmvCode
  Caption = 'fmvCode'
  PixelsPerInch = 96
  TextHeight = 13
  object meCode: TMemo [0]
    Left = 0
    Top = 0
    Width = 418
    Height = 281
    Align = alClient
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
  inherited coRes: TNNVConfig
    Connection = dmvNewNavadvipa.conDB
  end
end
