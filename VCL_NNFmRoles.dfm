inherited fmvRoles: TfmvRoles
  ActiveControl = tvRoles
  Caption = #1056#1086#1083#1080
  OnKeyDown = KeyDownDialog
  PixelsPerInch = 96
  TextHeight = 13
  object splRoles: TNNVSplitter [0]
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
  object tvRoles: TNNVDBTreeView [3]
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
  object dgRoles: TNNVDBGrid [4]
    Left = 219
    Top = 57
    Width = 966
    Height = 695
    Align = alClient
    DataSource = dmvNewNavadvipa.dsRole
    Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect, dgTitleClick, dgTitleHotTrack]
    PopupMenu = pmDBGrid
    TabOrder = 3
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnDrawColumnCell = dgRolesDrawColumnCell
    OnDblClick = DBGridDblClick
    OnEditButtonClick = DBGridEditButtonClick
    OnEnter = DBGridEnter
    OnKeyDown = DBGridKeyDown
    OnDBCut = dgRolesDBCut
    OnDBPaste = dgRolesDBPaste
    Columns = <
      item
        Expanded = False
        FieldName = 'EntityID'
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'KindID'
        Visible = False
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
      end
      item
        Expanded = False
        FieldName = 'Entity'
        Visible = True
      end>
  end
  inherited coRes: TNNVConfig
    OnEndLoad = coResEndLoad
  end
  object naRoleKind: TNNVNodeAdmin
    OnLoadNodes = naRoleKindLoadNodes
    OnGetNodeParams = naRoleKindGetNodeParams
    OnFirstEnter = naRoleKindFirstEnter
    OnEnter = naRoleKindEnter
    OnLastExit = naRoleKindLastExit
    ActualOnlyNeed = True
    EndToEndViewingNeed = True
    TreeView = tvRoles
    LoadOrder = 0
    DetailDataSet = dmvNewNavadvipa.quRole
    DataSource = dmvNewNavadvipa.dsRoleKind
    Left = 79
    Top = 170
  end
end
