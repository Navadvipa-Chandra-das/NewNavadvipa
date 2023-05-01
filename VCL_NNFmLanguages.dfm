inherited fmvLanguages: TfmvLanguages
  Caption = #1071#1079#1099#1082#1080
  OnKeyDown = KeyDownDialog
  PixelsPerInch = 96
  TextHeight = 13
  inherited paT: TNNVPanel
    inherited pcDB: TNNVPageControl
      inherited tsDB: TTabSheet
        inherited tbrDBTree: TToolBar
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
  object dgLanguages: TNNVDBGrid [2]
    Left = 0
    Top = 57
    Width = 1185
    Height = 695
    Align = alClient
    DataSource = dmvNewNavadvipa.dsLanguages
    Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect, dgTitleClick, dgTitleHotTrack]
    PopupMenu = pmDBGrid
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnEnter = DBGridEnter
    OnKeyDown = DBGridKeyDown
    Columns = <
      item
        Expanded = False
        FieldName = 'LanguagesID'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'LanguagesStringID'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Languages'
        Visible = True
      end>
  end
  inherited coRes: TNNVConfig
    StoreKind = skFiler
  end
end
