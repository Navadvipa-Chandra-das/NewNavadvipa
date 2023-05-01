inherited fmvRights: TfmvRights
  ActiveControl = tvRights
  Caption = #1055#1088#1072#1074#1072
  OnKeyDown = KeyDownDialog
  PixelsPerInch = 96
  TextHeight = 13
  object splRights: TNNVSplitter [0]
    Left = 216
    Top = 57
    Height = 695
    ExplicitLeft = 342
    ExplicitTop = 577
    ExplicitHeight = 100
  end
  inherited paT: TNNVPanel
    inherited pcDB: TNNVPageControl
      inherited tsDB: TTabSheet
        ExplicitTop = 25
        ExplicitHeight = 28
        inherited tbrDBTree: TToolBar
          Height = 28
          ExplicitHeight = 28
        end
      end
      inherited tsSetup: TTabSheet
        ExplicitTop = 25
        ExplicitHeight = 28
        inherited tbrSetup: TToolBar
          Height = 28
          ExplicitHeight = 28
        end
      end
    end
    inherited paTL: TNNVPanel
      inherited dbngDB: TDBNavigator
        Hints.Strings = ()
      end
    end
  end
  object tvRights: TNNVDBTreeView [3]
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
  object dgRights: TNNVDBGrid [4]
    Left = 219
    Top = 57
    Width = 966
    Height = 695
    Align = alClient
    DataSource = dmvNewNavadvipa.dsRights
    Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect, dgTitleClick, dgTitleHotTrack]
    PopupMenu = pmDBGrid
    TabOrder = 3
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnDrawColumnCell = dgRightsDrawColumnCell
    OnDblClick = DBGridDblClick
    OnEnter = DBGridEnter
    OnKeyDown = DBGridKeyDown
    OnDBCut = dgRightsDBCut
    OnDBPaste = dgRightsDBPaste
    Columns = <
      item
        Expanded = False
        FieldName = 'EntityID'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'KindID'
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'Actual'
        Font.Charset = SYMBOL_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Wingdings'
        Font.Style = []
        ReadOnly = True
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Entity'
        Width = 303
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Literal'
        Width = 87
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'VectorIndex'
        Visible = True
      end>
  end
  inherited coRes: TNNVConfig
    OnEndLoad = coResEndLoad
  end
  object naRightsKind: TNNVNodeAdmin
    OnLoadNodes = naRightsKindLoadNodes
    OnGetNodeParams = naRightsKindGetNodeParams
    OnFirstEnter = naRightsKindFirstEnter
    OnEnter = naRightsKindEnter
    OnLastExit = naRightsKindLastExit
    ActualOnlyNeed = True
    EndToEndViewingNeed = True
    TreeView = tvRights
    LoadOrder = 0
    DetailDataSet = dmvNewNavadvipa.quRights
    DataSource = dmvNewNavadvipa.dsRightsKind
    Left = 78
    Top = 170
  end
end
