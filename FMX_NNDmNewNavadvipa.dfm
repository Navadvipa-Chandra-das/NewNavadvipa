inherited dmfNewNavadvipa: TdmfNewNavadvipa
  OldCreateOrder = True
  Height = 507
  Width = 565
  inherited coData: TNNFConfig
    OnLoad = coDataLoad
    OnSave = coDataSave
  end
  object ilDB: TImageList
    Source = <>
    Destination = <>
    Left = 144
    Top = 16
  end
  object quDB: TNNFQuery
    Connection = conDB
    FetchOptions.AssignedValues = [evRecordCountMode, evUnidirectional, evCursorKind]
    FetchOptions.CursorKind = ckForwardOnly
    FetchOptions.Unidirectional = True
    NeedSave = False
    Left = 196
    Top = 16
  end
  object conDB: TFDConnection
    Params.Strings = (
      'DriverID=PostgreSQL_NewNavadvipa'
      'Database=NewNavadvipa'
      'User_Name=Navadvipa Chandra das'
      'Server=127.0.0.1'
      'MonitorBy=Remote')
    ConnectedStoredUsage = [auDesignTime]
    Transaction = trDB
    AfterConnect = conDBAfterConnect
    BeforeConnect = conDBBeforeConnect
    Left = 65535
    Top = 44
  end
  object trDB: TFDTransaction
    Connection = conDB
    Left = 29
    Top = 43
  end
  object monDB: TFDMoniRemoteClientLink
    Tracing = True
    Left = 58
    Top = 43
  end
  object quCommodKind: TNNFQuery
    Connection = conDB
    SQL.Strings = (
      'select'
      '  a."KindID"'
      ', a."ParentID"'
      ', a."Kind"'
      ', a."Actual"'
      ', a."InPrice"'
      'from'
      '  &PRABHUPADA_SCHEMA"CommodKind" a'
      'where'
      '    &ACTUAL_ONLY;')
    Left = 31
    Top = 84
    MacroData = <
      item
        Value = '"NewNavadvipa".'
        Name = 'PRABHUPADA_SCHEMA'
      end
      item
        Value = 'True'
        Name = 'ACTUAL_ONLY'
      end>
    object quCommodKindKindID: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'KindID'
      Origin = '"KindID"'
    end
    object quCommodKindParentID: TLargeintField
      FieldName = 'ParentID'
      Origin = '"ParentID"'
    end
    object quCommodKindKind: TWideStringField
      DisplayLabel = #1042#1080#1076
      FieldName = 'Kind'
      Origin = '"Kind"'
      Size = 100
    end
    object quCommodKindActual: TBooleanField
      DefaultExpression = 'True'
      DisplayLabel = #1040#1082#1090#1091#1072#1083#1100#1085#1086#1089#1090#1100
      FieldName = 'Actual'
      Origin = '"Actual"'
    end
    object quCommodKindInPrice: TBooleanField
      DisplayLabel = #1042#1082#1083#1102#1095#1072#1090#1100' '#1074' '#1087#1088#1072#1081#1089
      FieldName = 'InPrice'
      Origin = '"InPrice"'
    end
  end
  object quUsers: TNNFQuery
    Connection = conDB
    SQL.Strings = (
      'SELECT'
      '  a."UserID"'
      ', a."IsDeleted"'
      ', a."Name"'
      ', a."Note"'
      ', a."BirthDate"'
      ', a."CreateDate"'
      ', a."Anketa"'
      'FROM'
      '  &PRABHUPADA_SCHEMA"Users" a'
      'order by &ORDER_BY;')
    OrderByDefault = 'a."Name"'
    Left = 1
    Top = 84
    MacroData = <
      item
        Value = '"NewNavadvipa".'
        Name = 'PRABHUPADA_SCHEMA'
      end
      item
        Value = 'a."Name"'
        Name = 'ORDER_BY'
      end>
    object quUsersUserID: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'UserID'
      Origin = '"UserID"'
    end
    object quUsersIsDeleted: TBooleanField
      DefaultExpression = 'True'
      DisplayLabel = #1059#1076#1072#1083#1105#1085' '#1083#1080'?'
      FieldName = 'IsDeleted'
      Origin = '"IsDeleted"'
      Required = True
    end
    object quUsersName: TWideStringField
      DisplayLabel = #1051#1086#1075#1080#1085' '#1080#1084#1103
      FieldName = 'Name'
      Origin = '"Name"'
      Size = 32
    end
    object quUsersNote: TWideStringField
      DisplayLabel = #1050#1086#1084#1084#1077#1085#1090#1072#1088#1080#1081
      FieldName = 'Note'
      Origin = '"Note"'
      Size = 100
    end
    object quUsersBirthDate: TSQLTimeStampField
      FieldName = 'BirthDate'
      Origin = '"BirthDate"'
    end
    object quUsersCreateDate: TSQLTimeStampField
      FieldName = 'CreateDate'
      Origin = '"CreateDate"'
    end
    object quUsersAnketa: TADTField
      DisplayLabel = #1040#1085#1082#1077#1090#1072
      FieldName = 'Anketa'
      Origin = '"Anketa"'
      ObjectType = 'TAnketa'
      object quUsersAnketaFIO: TWideStringField
        DisplayLabel = #1060#1072#1084#1080#1083#1080#1103' '#1048#1084#1103' '#1054#1090#1095#1077#1089#1090#1074#1086
        FieldName = 'FIO'
        Origin = '"FIO"'
        Size = 100
      end
      object quUsersAnketaINN: TWideStringField
        DisplayLabel = #1048#1085#1076#1080#1074#1080#1076#1091#1072#1083#1100#1085#1099#1081' '#1085#1072#1083#1086#1075#1086#1074#1099#1081' '#1085#1086#1084#1077#1088
        FieldName = 'INN'
        Origin = '"INN"'
        Size = 12
      end
      object quUsersAnketaPassport: TWideStringField
        DisplayLabel = #1055#1072#1089#1087#1086#1088#1090
        FieldName = 'Passport'
        Origin = '"Passport"'
        Size = 12
      end
      object quUsersAnketaPassportKemVydan: TWideStringField
        DisplayLabel = #1050#1077#1084' '#1074#1099#1076#1072#1085' '#1087#1072#1089#1087#1086#1088#1090
        FieldName = 'PassportKemVydan'
        Origin = '"PassportKemVydan"'
        Size = 50
      end
      object quUsersAnketaPassportDate: TDateField
        DisplayLabel = #1044#1072#1090#1072' '#1074#1099#1076#1072#1095#1080' '#1087#1072#1089#1087#1086#1088#1090#1072
        FieldName = 'PassportDate'
        Origin = '"PassportDate"'
      end
    end
  end
  object dsUsers: TDataSource
    DataSet = quUsers
    Left = 65534
    Top = 128
  end
  object quCommod: TNNFQuery
    MasterSource = dsCommodKind
    MasterFields = 'KindID'
    Connection = conDB
    SQL.Strings = (
      'select'
      '  a."EntityID"'
      ', a."KindID"'
      ', a."Entity"'
      ', a."Actual"'
      ', a."Price"'
      'from'
      '  &PRABHUPADA_SCHEMA"Commod" a'
      'where'
      '    &END_TO_END_VIEWING'
      'and &ACTUAL_ONLY'
      'order by &ORDER_BY;')
    OrderByDefault = 'a."Entity"'
    PasteProcedure = '"PasteEntity"'
    Left = 56
    Top = 84
    ParamData = <
      item
        Name = 'KINDID'
        DataType = ftInteger
        ParamType = ptInput
        Value = Null
      end>
    MacroData = <
      item
        Value = '"NewNavadvipa".'
        Name = 'PRABHUPADA_SCHEMA'
      end
      item
        Value = 'a."KindID" = :KindID'
        Name = 'END_TO_END_VIEWING'
      end
      item
        Value = 'True'
        Name = 'ACTUAL_ONLY'
      end
      item
        Value = 'a."Entity"'
        Name = 'ORDER_BY'
      end>
    object quCommodEntityID: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'EntityID'
      Origin = '"EntityID"'
    end
    object quCommodKindID: TLargeintField
      FieldName = 'KindID'
      Origin = '"KindID"'
    end
    object quCommodEntity: TWideStringField
      DisplayLabel = #1058#1086#1074#1072#1088
      DisplayWidth = 35
      FieldName = 'Entity'
      Origin = '"Entity"'
      Size = 200
    end
    object quCommodActual: TBooleanField
      DefaultExpression = 'True'
      DisplayLabel = #1040#1082#1090#1091#1072#1083#1100#1085#1086#1089#1090#1100
      FieldName = 'Actual'
      Origin = '"Actual"'
    end
    object quCommodPrice: TFloatField
      DisplayLabel = #1062#1077#1085#1072
      FieldName = 'Price'
      Origin = '"Price"'
      Required = True
    end
  end
  object dsCommodKind: TDataSource
    DataSet = quCommodKind
    Left = 26
    Top = 128
  end
  object dsCommod: TDataSource
    DataSet = quCommod
    Left = 55
    Top = 128
  end
  object quColorKind: TNNFQuery
    Connection = conDB
    SQL.Strings = (
      'select'
      '  a."KindID"'
      ', a."ParentID"'
      ', a."Kind"'
      ', a."Actual"'
      'from'
      '  &PRABHUPADA_SCHEMA"ColorKind" a'
      'where'
      '    &ACTUAL_ONLY;')
    Left = 86
    Top = 84
    MacroData = <
      item
        Value = '"NewNavadvipa".'
        Name = 'PRABHUPADA_SCHEMA'
      end
      item
        Value = 'True'
        Name = 'ACTUAL_ONLY'
      end>
    object quColorKindKindID: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'KindID'
      Origin = '"KindID"'
    end
    object quColorKindParentID: TLargeintField
      FieldName = 'ParentID'
      Origin = '"ParentID"'
    end
    object quColorKindKind: TWideStringField
      DisplayLabel = #1042#1080#1076
      FieldName = 'Kind'
      Origin = '"Kind"'
      Size = 100
    end
    object quColorKindActual: TBooleanField
      DefaultExpression = 'True'
      DisplayLabel = #1040#1082#1090#1091#1072#1083#1100#1085#1086#1089#1090#1100
      FieldName = 'Actual'
      Origin = '"Actual"'
    end
  end
  object dsColorKind: TDataSource
    DataSet = quColorKind
    Left = 84
    Top = 128
  end
  object quColor: TNNFQuery
    MasterSource = dsColorKind
    MasterFields = 'KindID'
    Connection = conDB
    SQL.Strings = (
      'select'
      '  a."EntityID"'
      ', a."KindID"'
      ', a."Entity"'
      ', a."Actual"'
      ', a."FonColor"'
      ', a."FontColor"'
      ', a."VectorIndex"'
      ', a."EnumLiteral"'
      'from'
      '  &PRABHUPADA_SCHEMA"Color" a'
      'where'
      '    &END_TO_END_VIEWING'
      'and &ACTUAL_ONLY'
      'order by &ORDER_BY;')
    OrderByDefault = 'a."KindID", a."Entity"'
    PasteProcedure = '"PasteEntity"'
    Left = 116
    Top = 84
    ParamData = <
      item
        Name = 'KINDID'
        DataType = ftInteger
        ParamType = ptInput
        Value = Null
      end>
    MacroData = <
      item
        Value = '"NewNavadvipa".'
        Name = 'PRABHUPADA_SCHEMA'
      end
      item
        Value = 'a."KindID" = :KindID'
        Name = 'END_TO_END_VIEWING'
      end
      item
        Value = 'True'
        Name = 'ACTUAL_ONLY'
      end
      item
        Value = 'a."KindID", a."Entity"'
        Name = 'ORDER_BY'
      end>
    object quColorEntityID: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'EntityID'
      Origin = '"EntityID"'
    end
    object quColorKindID: TLargeintField
      FieldName = 'KindID'
      Origin = '"KindID"'
    end
    object quColorEntity: TWideStringField
      DisplayLabel = #1062#1074#1077#1090
      DisplayWidth = 35
      FieldName = 'Entity'
      Origin = '"Entity"'
      Size = 200
    end
    object quColorActual: TBooleanField
      Alignment = taCenter
      DefaultExpression = 'True'
      DisplayLabel = #1040#1082#1090#1091#1072#1083#1100#1085#1086#1089#1090#1100
      FieldName = 'Actual'
      Origin = '"Actual"'
    end
    object quColorEnumLiteral: TWideStringField
      DisplayLabel = #1051#1080#1090#1077#1088#1072#1083
      FieldName = 'EnumLiteral'
      Origin = '"EnumLiteral"'
      Size = 64
    end
    object quColorVectorIndex: TLargeintField
      DefaultExpression = '0'
      DisplayLabel = #1048#1085#1076#1077#1082#1089
      FieldName = 'VectorIndex'
      Origin = '"VectorIndex"'
    end
    object quColorFonColor: TIntegerField
      DefaultExpression = '0'
      DisplayLabel = #1062#1074#1077#1090' '#1092#1086#1085#1072
      FieldName = 'FonColor'
      Origin = '"FonColor"'
    end
    object quColorFontColor: TIntegerField
      DefaultExpression = '0'
      DisplayLabel = #1062#1074#1077#1090' '#1096#1088#1080#1092#1090#1072
      FieldName = 'FontColor'
      Origin = '"FontColor"'
    end
    object quColorFonColorUser: TIntegerField
      DisplayLabel = #1062#1074#1077#1090' '#1092#1086#1085#1072' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1103
      FieldKind = fkCalculated
      FieldName = 'FonColorUser'
      Calculated = True
    end
    object quColorFontColorUser: TIntegerField
      DisplayLabel = #1062#1074#1077#1090' '#1096#1088#1080#1092#1090#1072' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1103
      FieldKind = fkCalculated
      FieldName = 'FontColorUser'
      Calculated = True
    end
  end
  object dsColor: TDataSource
    DataSet = quColor
    Left = 113
    Top = 128
  end
  object quRightsKind: TNNFQuery
    Connection = conDB
    SQL.Strings = (
      'select'
      '  a."KindID"'
      ', a."ParentID"'
      ', a."Kind"'
      ', a."Actual"'
      'from'
      '  &PRABHUPADA_SCHEMA"RightsKind" a'
      'where'
      '    &ACTUAL_ONLY;')
    Left = 142
    Top = 84
    MacroData = <
      item
        Value = '"NewNavadvipa".'
        Name = 'PRABHUPADA_SCHEMA'
      end
      item
        Value = 'True'
        Name = 'ACTUAL_ONLY'
      end>
    object quRightsKindKindID: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'KindID'
      Origin = '"KindID"'
    end
    object quRightsKindParentID: TLargeintField
      FieldName = 'ParentID'
      Origin = '"ParentID"'
    end
    object quRightsKindKind: TWideStringField
      DisplayLabel = #1042#1080#1076' '#1087#1088#1072#1074
      FieldName = 'Kind'
      Origin = '"Kind"'
      Size = 100
    end
    object quRightsKindActual: TBooleanField
      DefaultExpression = 'True'
      DisplayLabel = #1040#1082#1090#1091#1072#1083#1100#1085#1086#1089#1090#1100
      FieldName = 'Actual'
      Origin = '"Actual"'
    end
  end
  object dsRightsKind: TDataSource
    DataSet = quRightsKind
    Left = 142
    Top = 128
  end
  object quRights: TNNFQuery
    MasterSource = dsRightsKind
    MasterFields = 'KindID'
    Connection = conDB
    SQL.Strings = (
      'select'
      '  a."EntityID"'
      ', a."KindID"'
      ', a."Entity"'
      ', a."Actual"'
      ', a."Literal"'
      ', a."VectorIndex"'
      'from'
      '  &PRABHUPADA_SCHEMA"Rights" a'
      'where'
      '    &END_TO_END_VIEWING'
      'and &ACTUAL_ONLY'
      'order by &ORDER_BY;')
    OrderByDefault = 'a."KindID", a."Entity"'
    PasteProcedure = '"PasteEntity"'
    Left = 170
    Top = 84
    ParamData = <
      item
        Name = 'KINDID'
        DataType = ftInteger
        ParamType = ptInput
        Value = Null
      end>
    MacroData = <
      item
        Value = '"NewNavadvipa".'
        Name = 'PRABHUPADA_SCHEMA'
      end
      item
        Value = 'a."KindID" = :KindID'
        Name = 'END_TO_END_VIEWING'
      end
      item
        Value = 'True'
        Name = 'ACTUAL_ONLY'
      end
      item
        Value = 'a."KindID", a."Entity"'
        Name = 'ORDER_BY'
      end>
    object quRightsEntityID: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'EntityID'
      Origin = '"EntityID"'
    end
    object quRightsKindID: TLargeintField
      FieldName = 'KindID'
      Origin = '"KindID"'
    end
    object quRightsEntity: TWideStringField
      DisplayLabel = #1055#1088#1072#1074#1086
      DisplayWidth = 35
      FieldName = 'Entity'
      Origin = '"Entity"'
      Size = 200
    end
    object quRightsActual: TBooleanField
      DefaultExpression = 'True'
      DisplayLabel = #1040#1082#1090#1091#1072#1083#1100#1085#1086#1089#1090#1100
      FieldName = 'Actual'
      Origin = '"Actual"'
    end
    object quRightsLiteral: TWideStringField
      DisplayLabel = #1051#1080#1090#1077#1088#1072#1083
      FieldName = 'Literal'
      Origin = '"Literal"'
      Size = 64
    end
    object quRightsVectorIndex: TLargeintField
      DefaultExpression = '0'
      DisplayLabel = #1048#1085#1076#1077#1082#1089
      FieldName = 'VectorIndex'
      Origin = '"VectorIndex"'
    end
  end
  object dsRights: TDataSource
    DataSet = quRights
    Left = 171
    Top = 128
  end
  object quRoleKind: TNNFQuery
    Connection = conDB
    SQL.Strings = (
      'select'
      '  a."KindID"'
      ', a."ParentID"'
      ', a."Kind"'
      ', a."Actual"'
      'from'
      '  &PRABHUPADA_SCHEMA"RoleKind" a'
      'where'
      '    &ACTUAL_ONLY;')
    Left = 199
    Top = 86
    MacroData = <
      item
        Value = '"NewNavadvipa".'
        Name = 'PRABHUPADA_SCHEMA'
      end
      item
        Value = 'True'
        Name = 'ACTUAL_ONLY'
      end>
    object quRoleKindKindID: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'KindID'
      Origin = '"KindID"'
    end
    object quRoleKindParentID: TLargeintField
      FieldName = 'ParentID'
      Origin = '"ParentID"'
    end
    object quRoleKindKind: TWideStringField
      DisplayLabel = #1042#1080#1076' '#1088#1086#1083#1077#1081
      FieldName = 'Kind'
      Origin = '"Kind"'
      Size = 100
    end
    object quRoleKindActual: TBooleanField
      DefaultExpression = 'True'
      DisplayLabel = #1040#1082#1090#1091#1072#1083#1100#1085#1086#1089#1090#1100
      FieldName = 'Actual'
      Origin = '"Actual"'
    end
  end
  object quRole: TNNFQuery
    MasterSource = dsRoleKind
    MasterFields = 'KindID'
    DetailFields = 'KindID'
    Connection = conDB
    FetchOptions.AssignedValues = [evCache]
    FetchOptions.Cache = [fiBlobs, fiMeta]
    SQL.Strings = (
      'select'
      '  a."EntityID"'
      ', a."KindID"'
      ', a."Entity"'
      ', a."Actual"'
      'from'
      '  &PRABHUPADA_SCHEMA"Role" a'
      'where'
      '    &END_TO_END_VIEWING'
      'and &ACTUAL_ONLY'
      'order by &ORDER_BY;')
    OrderByDefault = 'a."KindID", a."Entity"'
    PasteProcedure = '"PasteEntity"'
    Left = 226
    Top = 85
    ParamData = <
      item
        Name = 'KINDID'
        DataType = ftLargeint
        ParamType = ptInput
        Value = 80
      end>
    MacroData = <
      item
        Value = '"NewNavadvipa".'
        Name = 'PRABHUPADA_SCHEMA'
      end
      item
        Value = 'a."KindID" = :KindID'
        Name = 'END_TO_END_VIEWING'
      end
      item
        Value = 'True'
        Name = 'ACTUAL_ONLY'
      end
      item
        Value = 'a."KindID", a."Entity"'
        Name = 'ORDER_BY'
      end>
    object quRoleEntityID: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'EntityID'
      Origin = '"EntityID"'
    end
    object quRoleKindID: TLargeintField
      FieldName = 'KindID'
      Origin = '"KindID"'
    end
    object quRoleEntity: TWideStringField
      DisplayLabel = #1056#1086#1083#1100
      FieldName = 'Entity'
      Origin = '"Entity"'
      Size = 200
    end
    object quRoleActual: TBooleanField
      Alignment = taCenter
      DefaultExpression = 'True'
      DisplayLabel = #1040#1082#1090#1091#1072#1083#1100#1085#1086#1089#1090#1100
      FieldName = 'Actual'
      Origin = '"Actual"'
    end
  end
  object dsRoleKind: TDataSource
    DataSet = quRoleKind
    Left = 198
    Top = 129
  end
  object dsRole: TDataSource
    DataSet = quRole
    Left = 227
    Top = 129
  end
  object quUserRights: TNNFQuery
    MasterSource = dsUsers
    MasterFields = 'UserID'
    Connection = conDB
    SQL.Strings = (
      'select'
      '  a."UserRightsID"'
      ', a."UserID"'
      ', a."EntityID"'
      ', a."IsPlus"'
      ', &PRABHUPADA_SCHEMA"RightIDToName"( a."EntityID" ) as "Right"'
      
        ', &PRABHUPADA_SCHEMA"RightIDToKindID"( a."EntityID" ) as "RightI' +
        'D"'
      'from'
      '  &PRABHUPADA_SCHEMA"UserRights" a'
      'where'
      '    a."UserID" = :UserID'
      'order by &ORDER_BY;')
    OrderByDefault = '"Right"'
    Left = 282
    Top = 87
    ParamData = <
      item
        Name = 'USERID'
        DataType = ftLargeint
        ParamType = ptInput
        Value = Null
      end>
    MacroData = <
      item
        Value = '"NewNavadvipa".'
        Name = 'PRABHUPADA_SCHEMA'
      end
      item
        Value = '"Right"'
        Name = 'ORDER_BY'
      end>
    object quUserRightsUserRightsID: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'UserRightsID'
      Origin = '"UserRightsID"'
    end
    object quUserRightsUserID: TLargeintField
      FieldName = 'UserID'
      Origin = '"UserID"'
    end
    object quUserRightsEntityID: TLargeintField
      FieldName = 'EntityID'
      Origin = '"EntityID"'
    end
    object quUserRightsIsPlus: TBooleanField
      Alignment = taCenter
      DefaultExpression = 'True'
      DisplayLabel = #1055#1083#1102#1089'-'#1052#1080#1085#1091#1089
      DisplayWidth = 10
      FieldName = 'IsPlus'
      Origin = '"IsPlus"'
    end
    object quUserRightsRight: TWideStringField
      DisplayLabel = #1055#1088#1072#1074#1086
      DisplayWidth = 35
      FieldKind = fkInternalCalc
      FieldName = 'Right'
      Origin = '"Right"'
      Size = 200
    end
    object quUserRightsRightID: TLargeintField
      FieldKind = fkInternalCalc
      FieldName = 'RightID'
      Origin = '"RightID"'
      ReadOnly = True
    end
  end
  object dsUserRights: TDataSource
    DataSet = quUserRights
    Left = 284
    Top = 130
  end
  object quUserRoles: TNNFQuery
    MasterSource = dsUsers
    MasterFields = 'UserID'
    Connection = conDB
    SQL.Strings = (
      'select'
      '  a."UserRolesID"'
      ', a."UserID"'
      ', a."EntityID"'
      ', &PRABHUPADA_SCHEMA"RoleIDToName"( a."EntityID" ) as "Role"'
      ', &PRABHUPADA_SCHEMA"RoleIDToKindID"( a."EntityID" ) as "RoleID"'
      'from'
      '  &PRABHUPADA_SCHEMA"UserRoles" a'
      'where'
      '    a."UserID" = :UserID'
      'order by &ORDER_BY;')
    OrderByDefault = '"Role"'
    Left = 312
    Top = 86
    ParamData = <
      item
        Name = 'USERID'
        DataType = ftLargeint
        ParamType = ptInput
        Value = Null
      end>
    MacroData = <
      item
        Value = '"NewNavadvipa".'
        Name = 'PRABHUPADA_SCHEMA'
      end
      item
        Value = '"Role"'
        Name = 'ORDER_BY'
      end>
    object quUserRolesUserRolesID: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'UserRolesID'
      Origin = '"UserRolesID"'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
    end
    object quUserRolesUserID: TLargeintField
      FieldName = 'UserID'
      Origin = '"UserID"'
    end
    object quUserRolesEntityID: TLargeintField
      FieldName = 'EntityID'
      Origin = '"EntityID"'
    end
    object quUserRolesRole: TWideStringField
      DisplayLabel = #1056#1086#1083#1100
      DisplayWidth = 35
      FieldKind = fkInternalCalc
      FieldName = 'Role'
      Origin = '"Role"'
      Size = 200
    end
    object quUserRolesRoleID: TLargeintField
      FieldKind = fkInternalCalc
      FieldName = 'RoleID'
      Origin = '"RoleID"'
      ReadOnly = True
    end
  end
  object dsUserRoles: TDataSource
    DataSet = quUserRoles
    Left = 312
    Top = 130
  end
  object quRoleRights: TNNFQuery
    MasterSource = dsRole
    MasterFields = 'EntityID'
    Connection = conDB
    SQL.Strings = (
      'select'
      '  a."RoleRightsID"'
      ', a."RoleID"'
      ', a."EntityID"'
      ', &PRABHUPADA_SCHEMA"RightIDToName"( a."EntityID" ) as "Right"'
      
        ', &PRABHUPADA_SCHEMA"RightIDToKindID"( a."EntityID" ) as "RightI' +
        'D"'
      'from'
      '  &PRABHUPADA_SCHEMA"RoleRights" a'
      'where'
      '    a."RoleID" = :EntityID'
      'order by &ORDER_BY;')
    OrderByDefault = '"Right"'
    Left = 254
    Top = 85
    ParamData = <
      item
        Name = 'ENTITYID'
        DataType = ftLargeint
        ParamType = ptInput
        Value = Null
      end>
    MacroData = <
      item
        Value = '"NewNavadvipa".'
        Name = 'PRABHUPADA_SCHEMA'
      end
      item
        Value = '"Right"'
        Name = 'ORDER_BY'
      end>
    object quRoleRightsRoleRightsID: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'RoleRightsID'
      Origin = '"RoleRightsID"'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
    end
    object quRoleRightsRoleID: TLargeintField
      FieldName = 'RoleID'
      Origin = '"RoleID"'
    end
    object quRoleRightsEntityID: TLargeintField
      FieldName = 'EntityID'
      Origin = '"EntityID"'
    end
    object quRoleRightsRight: TWideStringField
      DisplayLabel = #1055#1088#1072#1074#1086
      DisplayWidth = 35
      FieldKind = fkInternalCalc
      FieldName = 'Right'
      Origin = '"Right"'
      Size = 200
    end
    object quRoleRightsRightID: TLargeintField
      FieldKind = fkInternalCalc
      FieldName = 'RightID'
      Origin = '"RightID"'
      ReadOnly = True
    end
  end
  object dsRoleRights: TDataSource
    DataSet = quRoleRights
    Left = 255
    Top = 129
  end
  object quLanguageKind: TNNFQuery
    Connection = conDB
    SQL.Strings = (
      'select'
      '  a."KindID"'
      ', a."ParentID"'
      ', a."Kind"'
      ', a."Actual"'
      'from'
      '  &PRABHUPADA_SCHEMA"LanguageKind" a'
      'where'
      '    &ACTUAL_ONLY;')
    Left = 341
    Top = 87
    MacroData = <
      item
        Value = '"NewNavadvipa".'
        Name = 'PRABHUPADA_SCHEMA'
      end
      item
        Value = 'True'
        Name = 'ACTUAL_ONLY'
      end>
    object quLanguageKindKindID: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'KindID'
      Origin = '"KindID"'
    end
    object quLanguageKindParentID: TLargeintField
      FieldName = 'ParentID'
      Origin = '"ParentID"'
    end
    object quLanguageKindKind: TWideStringField
      DisplayLabel = #1042#1080#1076' '#1089#1083#1086#1074' '#1076#1083#1103' '#1087#1077#1088#1077#1074#1086#1076#1072
      FieldName = 'Kind'
      Origin = '"Kind"'
      Size = 100
    end
    object quLanguageKindActual: TBooleanField
      DefaultExpression = 'True'
      DisplayLabel = #1040#1082#1090#1091#1072#1083#1100#1085#1086#1089#1090#1100
      FieldName = 'Actual'
      Origin = '"Actual"'
    end
  end
  object quLanguage: TNNFQuery
    MasterSource = dsLanguageKind
    MasterFields = 'KindID'
    DetailFields = 'KindID'
    Connection = conDB
    FetchOptions.AssignedValues = [evCache]
    FetchOptions.Cache = [fiBlobs, fiMeta]
    SQL.Strings = (
      'select'
      '  a."EntityID"'
      ', a."KindID"'
      ', a."Entity"'
      ', a."Actual"'
      ', a."Original"'
      'from'
      '  &PRABHUPADA_SCHEMA"Language" a'
      'where'
      '    &END_TO_END_VIEWING'
      'and &ACTUAL_ONLY'
      'order by &ORDER_BY;')
    OrderByDefault = 'a."KindID", a."Entity"'
    PasteProcedure = '"PasteEntity"'
    Left = 369
    Top = 87
    ParamData = <
      item
        Name = 'KINDID'
        DataType = ftLargeint
        ParamType = ptInput
        Value = 115
      end>
    MacroData = <
      item
        Value = '"NewNavadvipa".'
        Name = 'PRABHUPADA_SCHEMA'
      end
      item
        Value = 'a."KindID" = :KindID'
        Name = 'END_TO_END_VIEWING'
      end
      item
        Value = 'True'
        Name = 'ACTUAL_ONLY'
      end
      item
        Value = 'a."KindID", a."Entity"'
        Name = 'ORDER_BY'
      end>
    object quLanguageEntityID: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'EntityID'
      Origin = '"EntityID"'
    end
    object quLanguageKindID: TLargeintField
      FieldName = 'KindID'
      Origin = '"KindID"'
    end
    object quLanguageEntity: TWideStringField
      DisplayLabel = #1057#1090#1088#1086#1082#1086#1074#1086#1077' '#1080#1084#1103' '#1080#1079#1085#1072#1095#1072#1083#1100#1085#1086#1075#1086' '#1089#1083#1086#1074#1072
      FieldName = 'Entity'
      Origin = '"Entity"'
      Size = 200
    end
    object quLanguageActual: TBooleanField
      Alignment = taCenter
      DefaultExpression = 'True'
      DisplayLabel = #1040#1082#1090#1091#1072#1083#1100#1085#1086#1089#1090#1100
      FieldName = 'Actual'
      Origin = '"Actual"'
    end
    object quLanguageOriginal: TWideMemoField
      DisplayLabel = #1048#1079#1085#1072#1095#1072#1083#1100#1085#1086#1077' '#1089#1083#1086#1074#1086
      FieldName = 'Original'
      Origin = '"Original"'
      BlobType = ftWideMemo
    end
  end
  object dsLanguageKind: TDataSource
    DataSet = quLanguageKind
    Left = 340
    Top = 130
  end
  object dsLanguage: TDataSource
    DataSet = quLanguage
    Left = 368
    Top = 130
  end
  object quTranslate: TNNFQuery
    MasterSource = dsLanguage
    MasterFields = 'EntityID'
    DetailFields = 'LanguageID'
    Connection = conDB
    FetchOptions.AssignedValues = [evCache]
    FetchOptions.Cache = [fiBlobs, fiMeta]
    SQL.Strings = (
      'select'
      '  a."TranslateID"'
      ', a."LanguageID"'
      ', a."LanguagesID"'
      ', a."Translate"'
      ', b."Languages"'
      'from'
      '  &PRABHUPADA_SCHEMA"Translate" a'
      ', &PRABHUPADA_SCHEMA"Languages" b'
      'where'
      '    a."LanguageID" = :EntityID'
      'and b."LanguagesID" = a."LanguagesID"'
      'order by &ORDER_BY;')
    OrderByDefault = 'a."LanguagesID"'
    Left = 396
    Top = 87
    ParamData = <
      item
        Name = 'ENTITYID'
        DataType = ftLargeint
        ParamType = ptInput
        Value = Null
      end>
    MacroData = <
      item
        Value = '"NewNavadvipa".'
        Name = 'PRABHUPADA_SCHEMA'
      end
      item
        Value = 'a."LanguagesID"'
        Name = 'ORDER_BY'
      end>
    object quTranslateTranslateID: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'TranslateID'
      Origin = '"TranslateID"'
    end
    object quTranslateLanguageID: TLargeintField
      FieldName = 'LanguageID'
      Origin = '"LanguageID"'
    end
    object quTranslateLanguagesID: TLargeintField
      DefaultExpression = '1'
      FieldName = 'LanguagesID'
      Origin = '"LanguagesID"'
    end
    object quTranslateTranslate: TWideMemoField
      FieldName = 'Translate'
      Origin = '"Translate"'
      BlobType = ftWideMemo
    end
    object quTranslateLanguages: TWideStringField
      AutoGenerateValue = arDefault
      DisplayWidth = 20
      FieldKind = fkInternalCalc
      FieldName = 'Languages'
      Origin = '"Languages"'
      ReadOnly = True
      Size = 32
    end
  end
  object dsTranslate: TDataSource
    DataSet = quTranslate
    Left = 396
    Top = 131
  end
  object quLanguages: TNNFQuery
    Connection = conDB
    SQL.Strings = (
      'SELECT'
      '  a."LanguagesID"'
      ', a."LanguagesStringID"'
      ', a."Languages"'
      'FROM'
      '  &PRABHUPADA_SCHEMA"Languages" a'
      'order by &ORDER_BY;')
    OrderByDefault = 'a."Languages"'
    Left = 424
    Top = 87
    MacroData = <
      item
        Value = '"NewNavadvipa".'
        Name = 'PRABHUPADA_SCHEMA'
      end
      item
        Value = 'a."Languages"'
        Name = 'ORDER_BY'
      end>
    object quLanguagesLanguagesID: TLargeintField
      FieldName = 'LanguagesID'
      Origin = '"LanguagesID"'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
      Visible = False
    end
    object quLanguagesLanguagesStringID: TWideStringField
      DisplayLabel = #1057#1090#1088#1086#1082#1086#1074#1072#1103' '#1084#1077#1090#1082#1072
      FieldName = 'LanguagesStringID'
      Origin = '"LanguagesStringID"'
      Size = 5
    end
    object quLanguagesLanguages: TWideStringField
      DisplayLabel = #1071#1079#1099#1082
      FieldName = 'Languages'
      Origin = '"Languages"'
      Size = 32
    end
  end
  object dsLanguages: TDataSource
    DataSet = quLanguages
    Left = 424
    Top = 131
  end
  object PgDrLinkDB: TFDPhysPgDriverLink
    DriverID = 'PostgreSQL_NewNavadvipa'
    VendorLib = 'C:\PostgreSQL\psqlODBC\bin\libpq.dll'
    Left = 259
    Top = 16
  end
  object rmDB: TNNFRightsManager
    Connection = conDB
    Left = 296
    Top = 16
  end
  object lmDB: TNNFLanguageManager
    Connection = conDB
    Left = 328
    Top = 16
  end
  object SQLiteDrLinkDB: TFDPhysSQLiteDriverLink
    DriverID = 'SQLite_PrabhupadaSlovar'
    VendorLib = 'sqlite3.dll'
    EngineLinkage = slDynamic
    Left = 232
    Top = 16
  end
end
