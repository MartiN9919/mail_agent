object FSettings: TFSettings
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 268
  ClientWidth = 473
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCanResize = FormCanResize
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 9
    Top = 6
    Width = 207
    Height = 203
    Caption = ' '#1055#1086#1095#1090#1086#1074#1099#1081' '#1103#1097#1080#1082' '
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 29
      Width = 37
      Height = 13
      Caption = #1051#1086#1075#1080#1085' :'
    end
    object Label2: TLabel
      Left = 16
      Top = 59
      Width = 44
      Height = 13
      Caption = #1055#1072#1088#1086#1083#1100' :'
    end
    object Label3: TLabel
      Left = 16
      Top = 90
      Width = 30
      Height = 13
      Caption = #1061#1086#1089#1090' :'
    end
    object Label4: TLabel
      Left = 16
      Top = 117
      Width = 32
      Height = 13
      Caption = #1055#1086#1088#1090' :'
    end
    object Label9: TLabel
      Left = 16
      Top = 143
      Width = 86
      Height = 13
      Caption = #1055#1086#1076#1076#1077#1088#1078#1082#1072' TLS :'
    end
    object EditUserName: TEdit
      Left = 70
      Top = 26
      Width = 123
      Height = 21
      TabOrder = 0
    end
    object EditPassword: TEdit
      Left = 70
      Top = 53
      Width = 123
      Height = 21
      PasswordChar = '*'
      TabOrder = 1
      Text = 'EditPass'
    end
    object EditHost: TEdit
      Left = 70
      Top = 87
      Width = 123
      Height = 21
      TabOrder = 2
    end
    object EditPort: TEdit
      Left = 70
      Top = 114
      Width = 123
      Height = 21
      TabOrder = 3
    end
    object ComboBoxUseTLS: TComboBox
      Left = 70
      Top = 163
      Width = 123
      Height = 21
      TabOrder = 4
      Text = 'NoTLSSupport'
      Items.Strings = (
        'NoTLSSupport'
        'UseImplicitTLS'
        'UseExplicitTLS'
        'UseRequireTLS  '
        ' ')
    end
  end
  object GroupBox2: TGroupBox
    Left = 229
    Top = 6
    Width = 225
    Height = 203
    Caption = ' '#1055#1086#1080#1089#1082' '
    TabOrder = 1
    object Label5: TLabel
      Left = 18
      Top = 29
      Width = 56
      Height = 13
      Caption = #1048#1085#1090#1077#1088#1074#1072#1083' :'
    end
    object Label6: TLabel
      Left = 18
      Top = 54
      Width = 35
      Height = 13
      Caption = #1071#1097#1080#1082' :'
    end
    object Label7: TLabel
      Left = 18
      Top = 80
      Width = 21
      Height = 13
      Caption = #1054#1090' :'
    end
    object Label8: TLabel
      Left = 16
      Top = 117
      Width = 95
      Height = 13
      Caption = #1054#1090#1084#1077#1095#1072#1090#1100' '#1087#1080#1089#1100#1084#1072' :'
    end
    object EditFrom: TEdit
      Left = 88
      Top = 77
      Width = 121
      Height = 21
      TabOrder = 0
    end
    object EditInterval: TEdit
      Left = 88
      Top = 26
      Width = 121
      Height = 21
      TabOrder = 1
    end
    object CheckBoxAsSeen: TCheckBox
      Left = 26
      Top = 134
      Width = 109
      Height = 31
      Caption = ' '#1055#1088#1086#1095#1090#1077#1085#1085#1099#1084#1080
      TabOrder = 2
    end
    object CheckBoxAsDeleted: TCheckBox
      Left = 26
      Top = 165
      Width = 95
      Height = 17
      Caption = ' '#1059#1076#1072#1083#1077#1085#1085#1099#1084#1080
      TabOrder = 3
    end
    object ComboBoxMailBox: TComboBox
      Left = 88
      Top = 51
      Width = 121
      Height = 21
      TabOrder = 4
      Text = 'INBOX'
      Items.Strings = (
        'INBOX'
        #1042#1093#1086#1076#1103#1097#1080#1077
        #1054#1090#1087#1088#1072#1074#1083#1077#1085#1085#1099#1077
        #1059#1076#1072#1083#1077#1085#1085#1099#1077
        #1057#1087#1072#1084
        #1063#1077#1088#1085#1086#1074#1080#1082#1080)
    end
  end
  object bApply: TButton
    Left = 290
    Top = 221
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
    ModalResult = 1
    TabOrder = 2
    OnClick = bApplyClick
  end
  object bCancel: TButton
    Left = 379
    Top = 221
    Width = 75
    Height = 25
    Hint = #1054#1090#1084#1077#1085#1072'|'#1042#1077#1088#1085#1091#1090#1100' '#1087#1088#1077#1078#1085#1080#1077' '#1085#1072#1089#1090#1088#1086#1081#1082#1080
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 3
    OnClick = bCancelClick
  end
end
