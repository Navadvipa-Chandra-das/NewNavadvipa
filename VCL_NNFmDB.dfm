inherited fmvDB: TfmvDB
  Caption = 'fmvDB'
  ClientHeight = 774
  ClientWidth = 1185
  Menu = mmDB
  ExplicitWidth = 1201
  ExplicitHeight = 833
  PixelsPerInch = 96
  TextHeight = 13
  object paT: TNNVPanel [0]
    Left = 0
    Top = 0
    Width = 1185
    Height = 57
    Align = alTop
    TabOrder = 1
    object pcDB: TNNVPageControl
      Left = 281
      Top = 0
      Width = 904
      Height = 57
      ActivePage = tsSetup
      Align = alClient
      Images = dmvNewNavadvipa.ilDB
      TabOrder = 0
      object tsDB: TTabSheet
        Caption = #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093
        ImageIndex = 44
        object tbrDBTree: TToolBar
          Left = 0
          Top = 0
          Width = 896
          Height = 29
          Align = alClient
          Caption = 'tbrDBTree'
          Images = dmvNewNavadvipa.ilDB
          TabOrder = 0
          object tbDBAutoEdit: TToolButton
            Left = 0
            Top = 0
            Action = aDBAutoEdit
            Style = tbsCheck
          end
          object tbRowInspector: TToolButton
            Left = 23
            Top = 0
            Action = aRowInspector
          end
          object tbDBSelectAll: TToolButton
            Left = 46
            Top = 0
            Action = aDBSelectAll
          end
          object tbDBCut: TToolButton
            Left = 69
            Top = 0
            Action = aDBCut
          end
          object tbDBCopy: TToolButton
            Left = 92
            Top = 0
            Action = aDBCopy
          end
          object tbDBPaste: TToolButton
            Left = 115
            Top = 0
            Action = aDBPaste
          end
          object tbDBMerge: TToolButton
            Left = 138
            Top = 0
            Action = aDBMerge
          end
          object tbDBCachedUpdates: TToolButton
            Left = 161
            Top = 0
            Action = aDBCachedUpdates
            Style = tbsCheck
          end
          object tbRemeberRow: TToolButton
            Left = 184
            Top = 0
            Action = aRemeberRow
          end
          object tbStoreData: TToolButton
            Left = 207
            Top = 0
            Action = aStoreData
          end
          object tbTVNodeAdminReload: TToolButton
            Left = 230
            Top = 0
            Action = aTVNodeAdminReload
          end
          object tbDBTreeViewReload: TToolButton
            Left = 253
            Top = 0
            Action = aDBTreeViewReload
          end
          object tbDBTreeNodeActualInvert: TToolButton
            Left = 276
            Top = 0
            Action = aDBTreeViewNodeActualInvert
          end
          object tbDBTreeViewActualOnly: TToolButton
            Left = 299
            Top = 0
            Action = aDBTreeViewActualOnly
            Style = tbsCheck
          end
          object tbDBTreeViewEndToEndViewing: TToolButton
            Left = 322
            Top = 0
            Action = aDBTreeViewEndToEndViewing
            Style = tbsCheck
          end
          object tbDBTreeNodePrev: TToolButton
            Left = 345
            Top = 0
            Action = aDBTreeNodePrev
          end
          object tbDBTreeNodeNext: TToolButton
            Left = 368
            Top = 0
            Action = aDBTreeNodeNext
          end
          object deKindID: TDBEdit
            Left = 391
            Top = 0
            Width = 91
            Height = 22
            Hint = #1053#1086#1084#1077#1088' '#1074#1077#1090#1086#1095#1082#1080
            ReadOnly = True
            TabOrder = 0
          end
        end
      end
      object tsSetup: TTabSheet
        Hint = #1053#1072#1089#1090#1088#1086#1081#1082#1072
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072
        ImageIndex = 1
        object tbrSetup: TToolBar
          Left = 0
          Top = 0
          Width = 896
          Height = 28
          Align = alClient
          Caption = 'tbrSetup'
          Images = dmvNewNavadvipa.ilDB
          TabOrder = 0
          object tbActionListSetup: TToolButton
            Left = 0
            Top = 0
            Action = aActionListSetup
          end
          object tbDBGridProperty: TToolButton
            Left = 23
            Top = 0
            Action = aDBGridProperty
          end
          object tbAutoMergeMainMenu: TToolButton
            Left = 46
            Top = 0
            Action = aAutoMergeMainMenu
            Style = tbsCheck
          end
          object cbEnterKind: TComboBox
            Left = 69
            Top = 0
            Width = 74
            Height = 21
            Hint = #1058#1080#1087' Enter'
            Style = csDropDownList
            TabOrder = 0
            OnChange = cbEnterKindChange
            Items.Strings = (
              #1054#1073#1099#1095#1085#1099#1081
              #1042#1085#1080#1079
              #1051#1102#1073#1080#1084#1099#1081)
          end
          object tbRelease: TToolButton
            Left = 143
            Top = 0
            Action = aRelease
          end
          object tbClearCase: TToolButton
            Left = 166
            Top = 0
            Action = aClearCase
          end
          object tbPrepareLanguage: TToolButton
            Left = 189
            Top = 0
            Action = aPrepareLanguage
          end
        end
      end
    end
    object paTL: TNNVPanel
      Left = 0
      Top = 0
      Width = 281
      Height = 57
      Align = alLeft
      TabOrder = 1
      object tbrDB: TToolBar
        Left = 0
        Top = 27
        Width = 281
        Height = 30
        Align = alBottom
        Caption = 'tbrDB'
        Images = dmvNewNavadvipa.ilDB
        TabOrder = 0
        object tbDBSearch: TToolButton
          Left = 0
          Top = 0
          Action = aDBSearch
        end
        object tbDBQuickSearch: TToolButton
          Left = 23
          Top = 0
          Action = aDBQuickSearch
        end
        object tbDBSearchNext: TToolButton
          Left = 46
          Top = 0
          Action = aDBSearchNext
        end
        object tbDBSearchReset: TToolButton
          Left = 69
          Top = 0
          Action = aDBSearchReset
        end
      end
      object dbngDB: TDBNavigator
        Left = 4
        Top = 4
        Width = 264
        Height = 25
        DataSource = dsData
        VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
        TabOrder = 1
      end
    end
  end
  object paStatus: TNNVPanel [1]
    Left = 0
    Top = 752
    Width = 1185
    Height = 22
    Align = alBottom
    TabOrder = 0
    object edDBStatus: TEdit
      Left = 0
      Top = 0
      Width = 165
      Height = 22
      TabStop = False
      Align = alLeft
      ReadOnly = True
      TabOrder = 0
      ExplicitHeight = 21
    end
    object sbQuickSearch: TScrollBox
      Left = 241
      Top = 0
      Width = 944
      Height = 22
      Align = alClient
      BorderStyle = bsNone
      TabOrder = 1
      OnEnter = sbQuickSearchEnter
      OnExit = sbQuickSearchExit
    end
    object tbrStatus: TToolBar
      Left = 165
      Top = 0
      Width = 76
      Height = 22
      Align = alLeft
      Caption = 'tbrStatus'
      Images = dmvNewNavadvipa.ilDB
      TabOrder = 2
      object tbEraseFilterSearch: TToolButton
        Left = 0
        Top = 0
        Action = aEraseFilterSearch
      end
      object tbDBSearchVectorClear: TToolButton
        Left = 23
        Top = 0
        Action = aDBSearchVectorClear
      end
    end
  end
  inherited alRes: TNNVActionList
    Images = dmvNewNavadvipa.ilDB
    Top = 47
    object aDBGridProperty: TAction [0]
      Category = 'Setup'
      Caption = #1057#1074#1086#1081#1089#1090#1074#1072' '#1090#1072#1073#1083#1080#1094#1099
      Hint = #1057#1074#1086#1081#1089#1090#1074#1072' '#1090#1072#1073#1083#1080#1094#1099
      ImageIndex = 72
      ShortCut = 16455
      OnExecute = aDBGridPropertyExecute
    end
    object aDBCut: TAction [1]
      Category = 'DB'
      Caption = #1042#1099#1088#1077#1079#1072#1090#1100
      Hint = #1042#1099#1088#1077#1079#1072#1090#1100
      ImageIndex = 59
      ShortCut = 24664
      OnExecute = aDBCutExecute
    end
    object aDBCopy: TAction [2]
      Category = 'DB'
      Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100
      Hint = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100
      ImageIndex = 60
      ShortCut = 24643
      OnExecute = aDBCopyExecute
    end
    object aDBPaste: TAction [3]
      Category = 'DB'
      Caption = #1042#1089#1090#1072#1074#1080#1090#1100
      Hint = #1042#1089#1090#1072#1074#1080#1090#1100
      ImageIndex = 61
      ShortCut = 24662
      OnExecute = aDBPasteExecute
    end
    object aDBMerge: TAction [4]
      Category = 'DB'
      Caption = #1057#1083#1080#1090#1100
      Hint = #1057#1083#1080#1090#1100
      ImageIndex = 62
      ShortCut = 24653
      OnExecute = aDBMergeExecute
    end
    object aDBCachedUpdates: TAction [5]
      Category = 'DB'
      Caption = #1050#1101#1096#1080#1088#1086#1074#1072#1090#1100' '#1076#1072#1085#1085#1099#1077
      Hint = #1050#1101#1096#1080#1088#1086#1074#1072#1090#1100' '#1076#1072#1085#1085#1099#1077
      ImageIndex = 31
      OnExecute = aDBCachedUpdatesExecute
    end
    object aDBAutoEdit: TAction [6]
      Category = 'DB'
      Caption = #1040#1074#1090#1086'-'#1088#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1090#1072#1073#1083#1080#1094#1099
      Hint = #1040#1074#1090#1086'-'#1088#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1090#1072#1073#1083#1080#1094#1099
      ImageIndex = 94
      OnExecute = aDBAutoEditExecute
    end
    object aRemeberRow: TAction [7]
      Category = 'DB'
      Caption = #1047#1072#1087#1086#1084#1085#1080#1090#1100' '#1089#1090#1088#1086#1082#1091
      Hint = #1047#1072#1087#1086#1084#1085#1080#1090#1100' '#1089#1090#1088#1086#1082#1091
      ImageIndex = 187
      ShortCut = 32857
      OnExecute = aRemeberRowExecute
    end
    object aStoreData: TAction [8]
      Category = 'DB'
      Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1087#1086#1083#1103' '#1089#1090#1088#1086#1082
      Hint = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1087#1086#1083#1103' '#1089#1090#1088#1086#1082
      ImageIndex = 188
      ShortCut = 32853
      OnExecute = aStoreDataExecute
    end
    object aTVNodeAdminReload: TAction [9]
      Category = 'DB'
      Caption = #1054#1073#1085#1086#1074#1080#1090#1100' '#1074#1077#1090#1082#1091' '#1076#1077#1088#1077#1074#1072
      Hint = #1054#1073#1085#1086#1074#1080#1090#1100' '#1074#1077#1090#1082#1091' '#1076#1077#1088#1077#1074#1072
      ImageIndex = 57
      OnExecute = aTVNodeAdminReloadExecute
    end
    object aDBTreeViewReload: TAction [11]
      Category = 'DB'
      Caption = #1054#1073#1085#1086#1074#1080#1090#1100' '#1074#1089#1105' '#1076#1077#1088#1077#1074#1086
      Hint = #1054#1073#1085#1086#1074#1080#1090#1100' '#1074#1089#1105' '#1076#1077#1088#1077#1074#1086
      ImageIndex = 44
      OnExecute = aDBTreeViewReloadExecute
    end
    object aDBTreeViewNodeActualInvert: TAction [12]
      Category = 'DB'
      Caption = #1048#1085#1074#1077#1088#1090#1080#1088#1086#1074#1072#1090#1100' '#1072#1082#1090#1091#1072#1083#1100#1085#1086#1089#1090#1100' '#1074#1077#1090#1086#1095#1082#1080
      Hint = #1048#1085#1074#1077#1088#1090#1080#1088#1086#1074#1072#1090#1100' '#1072#1082#1090#1091#1072#1083#1100#1085#1086#1089#1090#1100' '#1074#1077#1090#1086#1095#1082#1080
      ImageIndex = 12
      ShortCut = 49217
      OnExecute = aDBTreeViewNodeActualInvertExecute
    end
    object aDBTreeViewActualOnly: TAction [13]
      Category = 'DB'
      Caption = #1058#1086#1083#1100#1082#1086' '#1072#1082#1090#1091#1072#1083#1100#1085#1099#1077' '#1074#1077#1090#1086#1095#1082#1080
      Hint = #1058#1086#1083#1100#1082#1086' '#1072#1082#1090#1091#1072#1083#1100#1085#1099#1077' '#1074#1077#1090#1086#1095#1082#1080
      ImageIndex = 135
      ShortCut = 57409
      OnExecute = aDBTreeViewActualOnlyExecute
    end
    object aTVNodeAdminPrint: TAction [14]
      Category = 'DB'
      Caption = #1055#1077#1095#1072#1090#1100' '#1074#1077#1090#1082#1080' '#1076#1077#1088#1077#1074#1072
      Hint = #1055#1077#1095#1072#1090#1100' '#1074#1077#1090#1082#1080' '#1076#1077#1088#1077#1074#1072
      ImageIndex = 75
      OnExecute = aTVNodeAdminPrintExecute
    end
    object aDBTreeViewEndToEndViewing: TAction [15]
      Category = 'DB'
      Caption = #1057#1082#1074#1086#1079#1085#1086#1081' '#1087#1088#1086#1089#1084#1086#1090#1088
      Hint = #1057#1082#1074#1086#1079#1085#1086#1081' '#1087#1088#1086#1089#1084#1086#1090#1088
      ImageIndex = 155
      ShortCut = 16468
      OnExecute = aDBTreeViewEndToEndViewingExecute
    end
    object aAutoMergeMainMenu: TAction [16]
      Category = 'Setup'
      Caption = #1057#1083#1080#1090#1100' '#1075#1083#1072#1074#1085#1086#1077' '#1084#1077#1085#1102
      Hint = #1057#1083#1080#1090#1100' '#1075#1083#1072#1074#1085#1086#1077' '#1084#1077#1085#1102
      ImageIndex = 58
      OnExecute = aAutoMergeMainMenuExecute
    end
    object aDBSearch: TAction [17]
      Category = 'DB'
      Caption = #1053#1072#1081#1090#1080
      Hint = #1053#1072#1081#1090#1080
      ImageIndex = 27
      ShortCut = 16454
      OnExecute = aDBSearchExecute
    end
    object aDBSearchNext: TAction [18]
      Category = 'DB'
      Caption = #1053#1072#1081#1090#1080' '#1076#1072#1083#1077#1077
      Hint = #1053#1072#1081#1090#1080' '#1076#1072#1083#1077#1077
      ImageIndex = 28
      ShortCut = 114
      OnExecute = aDBSearchNextExecute
    end
    object aDBQuickSearch: TAction [19]
      Category = 'DB'
      Caption = #1041#1099#1089#1090#1088#1099#1081' '#1087#1086#1080#1089#1082
      Hint = #1041#1099#1089#1090#1088#1099#1081' '#1087#1086#1080#1089#1082
      ImageIndex = 30
      ShortCut = 16453
      OnExecute = aDBQuickSearchExecute
    end
    object aDBSearchReset: TAction [20]
      Category = 'DB'
      Caption = #1055#1088#1077#1088#1074#1072#1090#1100' '#1087#1086#1080#1089#1082
      Hint = #1055#1088#1077#1088#1074#1072#1090#1100' '#1087#1086#1080#1089#1082
      ImageIndex = 29
      ShortCut = 24646
      OnExecute = aDBSearchResetExecute
    end
    object aEraseFilterSearch: TAction [21]
      Category = 'DB'
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1092#1080#1083#1100#1090#1088' '#1087#1086#1080#1089#1082#1072
      Hint = #1059#1076#1072#1083#1080#1090#1100' '#1092#1080#1083#1100#1090#1088' '#1087#1086#1080#1089#1082#1072
      ImageIndex = 175
      ShortCut = 16465
      OnExecute = aEraseFilterSearchExecute
    end
    object aDBTreeNodePrev: TAction [22]
      Category = 'DB'
      Caption = #1055#1088#1077#1076#1099#1076#1091#1097#1072#1103' '#1074#1077#1090#1086#1095#1082#1072
      Hint = #1055#1088#1077#1076#1099#1076#1091#1097#1072#1103#13#10#1074#1077#1090#1086#1095#1082#1072
      ImageIndex = 97
      ShortCut = 24698
      OnExecute = aDBTreeNodePrevExecute
      OnUpdate = aDBTreeNodePrevUpdate
    end
    object aDBTreeNodeNext: TAction [23]
      Category = 'DB'
      Caption = #1057#1083#1077#1076#1091#1102#1097#1072#1103' '#1074#1077#1090#1086#1095#1082#1072
      Hint = #1057#1083#1077#1076#1091#1102#1097#1072#1103#13#10#1074#1077#1090#1086#1095#1082#1072
      ImageIndex = 98
      ShortCut = 24699
      OnExecute = aDBTreeNodeNextExecute
      OnUpdate = aDBTreeNodeNextUpdate
    end
    object aDBSelectAll: TAction [25]
      Category = 'DB'
      Caption = #1042#1099#1076#1077#1083#1080#1090#1100' '#1074#1089#1077
      Hint = #1042#1099#1076#1077#1083#1080#1090#1100' '#1074#1089#1077
      ImageIndex = 167
      ShortCut = 24641
      OnExecute = aDBSelectAllExecute
    end
    object aDBSearchVectorClear: TAction [26]
      Category = 'DB'
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1092#1080#1083#1100#1090#1088' '#1087#1086#1080#1089#1082#1072
      Hint = #1054#1095#1080#1089#1090#1080#1090#1100' '#1092#1080#1083#1100#1090#1088' '#1087#1086#1080#1089#1082#1072
      ImageIndex = 116
      OnExecute = aDBSearchVectorClearExecute
    end
    object aRowInspector: TAction
      Category = 'DB'
      Caption = #1048#1085#1089#1087#1077#1082#1090#1086#1088' '#1089#1090#1088#1086#1082#1080
      Hint = #1048#1085#1089#1087#1077#1082#1090#1086#1088' '#1089#1090#1088#1086#1082#1080
      ImageIndex = 23
      ShortCut = 16506
      OnExecute = aRowInspectorExecute
    end
  end
  object dsData: TDataSource
    OnDataChange = dsDataDataChange
    Left = 280
    Top = 48
  end
  object mmDB: TMainMenu
    Images = dmvNewNavadvipa.ilDB
    Left = 225
    Top = 48
    object miDB: TMenuItem
      Caption = #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093
      GroupIndex = 1
      object miDBAutoEdit: TMenuItem
        Action = aDBAutoEdit
      end
      object miDBSelectAll: TMenuItem
        Action = aDBSelectAll
      end
      object miDBCut: TMenuItem
        Action = aDBCut
      end
      object miDBCopy: TMenuItem
        Action = aDBCopy
      end
      object miDBPaste: TMenuItem
        Action = aDBPaste
      end
      object miDBMerge: TMenuItem
        Action = aDBMerge
      end
      object miDBCachedUpdates: TMenuItem
        Action = aDBCachedUpdates
      end
      object miRemeberRow: TMenuItem
        Action = aRemeberRow
      end
      object miStoreData: TMenuItem
        Action = aStoreData
      end
      object miTVNodeAdminReload: TMenuItem
        Action = aTVNodeAdminReload
      end
      object miDBTreeViewReload: TMenuItem
        Action = aDBTreeViewReload
      end
      object miDBTreeViewNodeActualInvert: TMenuItem
        Action = aDBTreeViewNodeActualInvert
      end
      object miDBTreeViewActualOnly: TMenuItem
        Action = aDBTreeViewActualOnly
      end
      object miDBTreeViewEndToEndViewing: TMenuItem
        Action = aDBTreeViewEndToEndViewing
      end
      object miDBSearch: TMenuItem
        Action = aDBSearch
      end
      object miDBSearchNext: TMenuItem
        Action = aDBSearchNext
      end
      object miDBSearchReset: TMenuItem
        Action = aDBSearchReset
      end
      object miSearchEdit: TMenuItem
        Action = aDBQuickSearch
      end
      object miEraseFilterSearch: TMenuItem
        Action = aEraseFilterSearch
      end
      object miRowInspector: TMenuItem
        Action = aRowInspector
      end
    end
    object miDBProperty: TMenuItem
      Caption = #1057#1074#1086#1081#1089#1090#1074#1072
      GroupIndex = 3
      object miActionListSetup: TMenuItem
        Action = aActionListSetup
      end
      object miDBGridProperty: TMenuItem
        Action = aDBGridProperty
      end
      object miAutoMergeMainMenu: TMenuItem
        Action = aAutoMergeMainMenu
      end
      object miRelease: TMenuItem
        Action = aRelease
      end
      object miClearCase: TMenuItem
        Caption = #1055#1091#1089#1090#1086#1081' '#1074#1099#1073#1086#1088
        Hint = #1055#1091#1089#1090#1086#1081' '#1074#1099#1073#1086#1088
        ImageIndex = 116
      end
      object miPrepareLanguage: TMenuItem
        Action = aPrepareLanguage
      end
    end
  end
  object sdDB: TNNVDBSearchDialog
    DataSource = dsData
    QuickScrollBox = sbQuickSearch
    OnExecute = sdDBExecute
    Left = 253
    Top = 48
  end
  object ddDB: TNNVDateTimeDialog
    OnPrepare = ddDBPrepare
    OnExecute = ddDBExecute
    Left = 308
    Top = 48
  end
  object pmDBGrid: TPopupMenu
    Images = dmvNewNavadvipa.ilDB
    Left = 336
    Top = 47
    object mipDBCut: TMenuItem
      Action = aDBCut
    end
    object mipDBCopy: TMenuItem
      Action = aDBCopy
    end
    object mipDBPaste: TMenuItem
      Action = aDBPaste
    end
    object mipDBMerge: TMenuItem
      Action = aDBMerge
    end
    object mipDBGridSeparator: TMenuItem
      Caption = '-'
    end
    object mipDBAutoEdit: TMenuItem
      Action = aDBAutoEdit
    end
    object mipDBCachedUpdates: TMenuItem
      Action = aDBCachedUpdates
    end
    object mipRemeberRow: TMenuItem
      Action = aRemeberRow
    end
    object mipStoreData: TMenuItem
      Action = aStoreData
    end
    object mipDBSelectAll: TMenuItem
      Action = aDBSelectAll
    end
    object mipDBGridProperty: TMenuItem
      Action = aDBGridProperty
    end
    object mipRowInspector: TMenuItem
      Action = aRowInspector
    end
  end
  object pmDBTreeView: TPopupMenu
    Images = dmvNewNavadvipa.ilDB
    Left = 365
    Top = 48
    object mitDBCut: TMenuItem
      Action = aDBCut
    end
    object mitDBPaste: TMenuItem
      Action = aDBPaste
    end
  end
end
