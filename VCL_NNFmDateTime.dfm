inherited fmvDateTime: TfmvDateTime
  Left = 272
  Top = 130
  ActiveControl = Calendar
  BorderStyle = bsNone
  Caption = 'fmvDateTime'
  ClientHeight = 164
  ClientWidth = 217
  OldCreateOrder = True
  ExplicitWidth = 217
  ExplicitHeight = 164
  PixelsPerInch = 96
  TextHeight = 13
  object paBevel: TNNVPanel [0]
    Left = 0
    Top = 0
    Width = 217
    Height = 164
    Align = alClient
    BevelInner = bvLowered
    BevelOuter = bvRaised
    TabOrder = 0
    object paTop: TNNVPanel
      Left = 2
      Top = 2
      Width = 213
      Height = 26
      Align = alTop
      TabOrder = 0
      object sbMonthPrior: TSpeedButton
        Left = 1
        Top = 1
        Width = 19
        Height = 20
        Hint = #1084#1077#1089#1103#1094#13#10#1085#1072#1079#1072#1076
        Flat = True
        Glyph.Data = {
          F6000000424DF600000000000000760000002800000010000000100000000100
          0400000000008000000000000000000000001000000010000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
          8888888888888888888888888888888888888888880788888888888880078888
          888888880F07777777788880FF0000000008880FFFFFFFFFFF0880FFFFFFFFFF
          FF08880FFFFFFFFFFF088880FF000000000888880F0888888888888880088888
          8888888888088888888888888888888888888888888888888888}
        OnClick = sbMonthPriorClick
      end
      object sbMonthNext: TSpeedButton
        Left = 99
        Top = 1
        Width = 19
        Height = 20
        Hint = #1084#1077#1089#1103#1094#13#10#1074#1087#1077#1088#1077#1076
        Flat = True
        Glyph.Data = {
          F6000000424DF600000000000000760000002800000010000000100000000100
          0400000000008000000000000000000000001000000010000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
          8888888888888888888888888888888888888888888880788888888888888007
          88888877777770F078888000000000FF078880FFFFFFFFFFF07880FFFFFFFFFF
          FF0880FFFFFFFFFFF0888000000000FF08888888888880F08888888888888008
          8888888888888088888888888888888888888888888888888888}
        OnClick = sbMonthNextClick
      end
      object sbCurrentDate: TSpeedButton
        Left = 118
        Top = 1
        Width = 19
        Height = 20
        Hint = #1090#1077#1082#1091#1097#1072#1103#13#10#1076#1072#1090#1072
        Flat = True
        Glyph.Data = {
          F6000000424DF600000000000000760000002800000010000000100000000100
          0400000000008000000000000000000000001000000010000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00300000000000
          003330FFFFFFFFFFF03330FFFF000FFFF03330FFFFF0FFFFF03330FFFF00FFFF
          F03330FFFFF0FFFFF03330FFFFFFFFFFF0333000F0F0F0F0F03330F0F000F070
          F03330F0F0F0F070F03330F0FF0FF0F0F03330FFFFFFFF00003330FFFFFFFF0F
          F03330999999990F033330FFFFFFFF0033333000000000033333}
        OnClick = sbCurrentDateClick
      end
      object laLeap: TLabel
        Left = 203
        Top = 4
        Width = 6
        Height = 13
        Hint = #1080#1085#1076#1080#1082#1072#1090#1086#1088#13#10#1074#1099#1089#1086#1082#1086#1089#1085#1086#1075#1086#13#10#1075#1086#1076#1072
        Caption = #1042
      end
      object edYear: TEdit
        Left = 138
        Top = 1
        Width = 49
        Height = 21
        Hint = #1075#1086#1076
        TabOrder = 1
        Text = '0'
        OnChange = edYearChange
        OnExit = edYearExit
      end
      object udYear: TUpDown
        Left = 187
        Top = 1
        Width = 13
        Height = 19
        Min = -32768
        Max = 32767
        TabOrder = 2
        Thousands = False
        OnClick = udYearClick
      end
      object cbMonth: TComboBox
        Left = 20
        Top = 1
        Width = 77
        Height = 21
        Hint = #1084#1077#1089#1103#1094
        Style = csDropDownList
        Ctl3D = False
        DropDownCount = 12
        ParentCtl3D = False
        TabOrder = 0
        OnChange = cbMonthChange
      end
    end
    object Calendar: TNNVCalendar
      Left = 2
      Top = 28
      Width = 213
      Height = 106
      Align = alClient
      BorderStyle = bsNone
      TabOrder = 1
      OnChange = CalendarChange
      OnDblClick = CalendarDblClick
    end
    object paTime: TNNVPanel
      Left = 2
      Top = 134
      Width = 213
      Height = 28
      Align = alBottom
      TabOrder = 2
      OnDblClick = CalendarDblClick
      object laTime: TLabel
        Left = 8
        Top = 7
        Width = 30
        Height = 13
        Caption = '&'#1042#1088#1077#1084#1103
        FocusControl = meTime
        OnClick = LabelClick
      end
      object sbOk: TSpeedButton
        Left = 109
        Top = 4
        Width = 48
        Height = 18
        Hint = #1074#1099#1073#1086#1088
        Caption = 'OK'
        Flat = True
        OnClick = CalendarDblClick
      end
      object sbCancel: TSpeedButton
        Left = 163
        Top = 4
        Width = 46
        Height = 18
        Hint = #1086#1090#1084#1077#1085#1072
        Caption = 'Cancel'
        Flat = True
        OnClick = sbCancelClick
      end
      object meTime: TMaskEdit
        Left = 45
        Top = 4
        Width = 58
        Height = 21
        Hint = #1074#1088#1077#1084#1103
        EditMask = '!00:00:00;1;_'
        MaxLength = 8
        TabOrder = 0
        Text = '  :  :  '
      end
    end
  end
  inherited fbRes: TNNVFlagBox
    Left = 120
    Top = 68
  end
  inherited coRes: TNNVConfig
    Enabled = False
    Left = 92
    Top = 68
  end
  inherited rrRes: TNNVRight
    Left = 148
    Top = 68
  end
  inherited alRes: TNNVActionList
    Left = 175
    Top = 68
  end
end
