object FDebug: TFDebug
  Left = 0
  Top = 0
  Caption = #1054#1090#1083#1072#1076#1082#1072
  ClientHeight = 267
  ClientWidth = 314
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object RichEdit1: TRichEdit
    Left = 0
    Top = 30
    Width = 314
    Height = 237
    Align = alClient
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Lines.Strings = (
      'RichEdit1')
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object CoolBar1: TCoolBar
    Left = 0
    Top = 0
    Width = 314
    Height = 30
    AutoSize = True
    Bands = <
      item
        Control = ToolBar1
        ImageIndex = -1
        MinHeight = 26
        Width = 308
      end>
    object ToolBar1: TToolBar
      Left = 11
      Top = 0
      Width = 299
      Height = 26
      Caption = 'ToolBar1'
      Images = FMyMailAgent.ImageList1
      TabOrder = 0
      object ToolButton2: TToolButton
        Left = 0
        Top = 0
        Caption = 'ToolButton2'
        ImageIndex = 5
        OnClick = ToolButton2Click
      end
      object ToolButton1: TToolButton
        Left = 23
        Top = 0
        Caption = 'ToolButton1'
        ImageIndex = 6
        OnClick = ToolButton1Click
      end
      object ToolButton3: TToolButton
        Left = 46
        Top = 0
        Caption = 'ToolButton3'
        ImageIndex = 12
        OnClick = ToolButton3Click
      end
    end
  end
  object IdLogEvent1: TIdLogEvent
    Active = True
    LogTime = False
    ReplaceCRLF = False
    OnReceived = IdLogEvent1Sent
    OnSent = IdLogEvent1Sent
    OnStatus = IdLogEvent1Status
    Left = 128
    Top = 88
  end
  object SaveDialog1: TSaveDialog
    Left = 192
    Top = 88
  end
  object FindDialog1: TFindDialog
    OnFind = FindDialog1Find
    Left = 248
    Top = 88
  end
end
