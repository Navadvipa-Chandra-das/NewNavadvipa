inherited fmvLanguage: TfmvLanguage
  ActiveControl = tvLanguage
  Caption = #1071#1079#1099#1082#1080
  PixelsPerInch = 96
  TextHeight = 13
  object splLanguage: TNNVSplitter [0]
    Left = 216
    Top = 57
    Height = 695
    ExplicitLeft = 342
    ExplicitTop = 577
    ExplicitHeight = 100
  end
  inherited paT: TNNVPanel
    inherited pcDB: TNNVPageControl
      inherited tsSetup: TTabSheet
        inherited tbrSetup: TToolBar
          object cbLanguageOwner: TComboBox
            Left = 212
            Top = 0
            Width = 197
            Height = 22
            Style = csDropDownList
            TabOrder = 1
            OnChange = cbLanguageOwnerChange
          end
          object tbPrepareOwnerWords: TToolButton
            Left = 409
            Top = 0
            Action = aPrepareOwnerWords
          end
          object tbSelectNonLatinica: TToolButton
            Left = 432
            Top = 0
            Action = aSelectNonLatinica
          end
        end
      end
    end
    inherited paTL: TNNVPanel
      inherited dbngDB: TDBNavigator
        Hints.Strings = ()
      end
    end
  end
  object tvLanguage: TNNVDBTreeView [3]
    Left = 0
    Top = 57
    Width = 216
    Height = 695
    Align = alLeft
    Images = dmvNewNavadvipa.ilDB
    Indent = 19
    PopupMenu = pmDBTreeView
    TabOrder = 2
    OnEnter = DBTreeViewEnter
    EditKindID = deKindID
    OnNodeAdminChange = DBTreeViewNodeAdminChange
  end
  object paLanguage: TNNVPanel [4]
    Left = 219
    Top = 57
    Width = 966
    Height = 695
    Align = alClient
    TabOrder = 3
    object splLanguageB: TNNVSplitter
      Left = 0
      Top = 431
      Width = 966
      Height = 3
      Cursor = crVSplit
      Align = alBottom
      ExplicitTop = 0
      ExplicitWidth = 434
    end
    object dgLanguage: TNNVDBGrid
      Left = 0
      Top = 0
      Width = 966
      Height = 431
      Align = alClient
      DataSource = dmvNewNavadvipa.dsLanguage
      Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgConfirmDelete, dgCancelOnExit, dgMultiSelect, dgTitleClick, dgTitleHotTrack]
      PopupMenu = pmDBGrid
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnDrawColumnCell = dgLanguageDrawColumnCell
      OnEditButtonClick = DBGridEditButtonClick
      OnEnter = DBGridEnter
      OnKeyDown = DBGridKeyDown
      OnTitleClick = DBGridTitleClick
      OnDBCut = dgLanguageDBCut
      OnDBPaste = dgLanguageDBPaste
      Columns = <
        item
          Expanded = False
          FieldName = 'EntityID'
          Visible = False
          OrderBy = 'a."KindID", a."EntityID"'
        end
        item
          Expanded = False
          FieldName = 'KindID'
          Visible = False
          OrderBy = 'a."KindID", a."EntityID"'
        end
        item
          Expanded = False
          FieldName = 'Actual'
          Font.Charset = SYMBOL_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Wingdings'
          Font.Style = []
          ReadOnly = True
          Visible = True
          OrderBy = 'a."KindID", a."Actual"'
        end
        item
          Expanded = False
          FieldName = 'Entity'
          Width = 269
          Visible = True
          OrderBy = 'a."KindID", a."Entity"'
        end
        item
          Expanded = False
          FieldName = 'Original'
          Width = 564
          Visible = True
          OrderBy = 'a."KindID", a."Original"'
        end>
    end
    object paLanguageB: TNNVPanel
      Left = 0
      Top = 434
      Width = 966
      Height = 261
      Align = alBottom
      TabOrder = 1
      object splLanguageBB: TNNVSplitter
        Left = 0
        Top = 157
        Width = 966
        Height = 3
        Cursor = crVSplit
        Align = alBottom
        ExplicitTop = 0
        ExplicitWidth = 160
      end
      object paLanguageBB: TNNVPanel
        Left = 0
        Top = 160
        Width = 966
        Height = 101
        Align = alBottom
        TabOrder = 0
        object splSlovo: TNNVSplitter
          Left = 376
          Top = 0
          Height = 101
          ExplicitLeft = 393
          ExplicitTop = 59
          ExplicitHeight = 100
        end
        object dmeSlovo: TDBMemo
          Left = 0
          Top = 0
          Width = 376
          Height = 101
          Align = alLeft
          DataField = 'Original'
          DataSource = dmvNewNavadvipa.dsLanguage
          TabOrder = 0
        end
        object dmePerevod: TDBMemo
          Left = 379
          Top = 0
          Width = 587
          Height = 101
          Align = alClient
          DataField = 'Translate'
          DataSource = dmvNewNavadvipa.dsTranslate
          TabOrder = 1
        end
      end
      object dgTranslate: TNNVDBGrid
        Left = 0
        Top = 0
        Width = 966
        Height = 157
        Align = alClient
        DataSource = dmvNewNavadvipa.dsTranslate
        Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgConfirmDelete, dgCancelOnExit, dgMultiSelect, dgTitleClick, dgTitleHotTrack]
        PopupMenu = pmDBGrid
        TabOrder = 1
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        OnEditButtonClick = DBGridEditButtonClick
        OnEnter = DBGridEnter
        OnKeyDown = DBGridKeyDown
        OnTitleClick = DBGridTitleClick
        OnDBCut = dgTranslateDBCut
        OnDBCopy = dgTranslateDBCopy
        OnDBPaste = dgTranslateDBPaste
        Columns = <
          item
            Expanded = False
            FieldName = 'TranslateID'
            Visible = False
            OrderBy = 'a."LanguageID", a."TranslateID"'
          end
          item
            Expanded = False
            FieldName = 'LanguageID'
            Visible = False
            OrderBy = 'a."LanguageID", a."TranslateID"'
          end
          item
            Expanded = False
            FieldName = 'LanguagesID'
            Visible = False
            OrderBy = 'a."LanguagesID"'
          end
          item
            ButtonStyle = cbsEllipsis
            Expanded = False
            FieldName = 'Languages'
            Width = 128
            Visible = True
            Dialog = DLanguages
            OrderBy = '"Languages"'
          end
          item
            Expanded = False
            FieldName = 'Translate'
            Width = 459
            Visible = True
            OrderBy = 'a."Translate"'
          end>
      end
    end
  end
  inherited fbRes: TNNVFlagBox
    ShowInWindowList = True
  end
  inherited coRes: TNNVConfig
    OnEndLoad = coResEndLoad
  end
  inherited alRes: TNNVActionList
    object aPrepareOwnerWords: TAction
      Category = 'Setup'
      Caption = #1055#1086#1076#1075#1086#1090#1086#1074#1080#1090#1100' '#1089#1083#1086#1074#1072
      Hint = #1055#1086#1076#1075#1086#1090#1086#1074#1080#1090#1100' '#1089#1083#1086#1074#1072
      ImageIndex = 25
      OnExecute = aPrepareOwnerWordsExecute
    end
    object aSelectNonLatinica: TAction
      Category = 'Setup'
      Caption = #1042#1099#1073#1088#1072#1090#1100' '#1085#1077' '#1083#1072#1090#1080#1085#1080#1094#1091
      Hint = #1042#1099#1073#1088#1072#1090#1100' '#1085#1077' '#1083#1072#1090#1080#1085#1080#1094#1091
      ImageIndex = 107
      OnExecute = aSelectNonLatinicaExecute
    end
  end
  inherited dsData: TDataSource
    Left = 279
    Top = 47
  end
  inherited mmDB: TMainMenu
    inherited miDBProperty: TMenuItem
      object miPrepareOwnerWords: TMenuItem
        Action = aPrepareOwnerWords
      end
      object miSelectNonLatinica: TMenuItem
        Action = aSelectNonLatinica
      end
    end
  end
  object naLanguageKind: TNNVNodeAdmin
    OnLoadNodes = naLanguageKindLoadNodes
    OnGetNodeParams = naLanguageKindGetNodeParams
    OnFirstEnter = naLanguageKindFirstEnter
    OnEnter = naLanguageKindEnter
    OnLastExit = naLanguageKindLastExit
    ActualOnlyNeed = True
    EndToEndViewingNeed = True
    TreeView = tvLanguage
    LoadOrder = 0
    DetailDataSet = dmvNewNavadvipa.quLanguage
    DataSource = dmvNewNavadvipa.dsLanguageKind
    Left = 79
    Top = 170
  end
  object DLanguages: TNNVDialog
    OnPrepare = DLanguagesPrepare
    OnExecute = DLanguagesExecute
    Left = 394
    Top = 48
  end
end
