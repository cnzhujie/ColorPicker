object FormMain: TFormMain
  Left = 1038
  Top = 148
  Width = 372
  Height = 336
  BorderIcons = [biSystemMenu, biMinimize, biHelp]
  Caption = 'ColorPicker'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object pnlInfo: TPanel
    Left = 0
    Top = 0
    Width = 356
    Height = 100
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object pnlColor: TPanel
      Left = 256
      Top = 0
      Width = 100
      Height = 100
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      DesignSize = (
        100
        100)
      object imgLock: TImage
        Left = 79
        Top = 78
        Width = 16
        Height = 16
        Anchors = [akRight, akBottom]
        AutoSize = True
        Picture.Data = {
          055449636F6E0000010001001010000001002000680400001600000028000000
          1000000020000000010020000000000000040000000000000000000000000000
          000000000000000000000000333333003333331D333333B8333333FF333333FF
          333333FF333333FF333333FF333333FF333333FF333333FF333333FF333333F6
          333333940000000000000000333333003333334D333333FB333333FF333333FF
          333333FF333333FF333333FF333333FF333333FF333333FF333333FF333333FF
          333333F600000000000000003333330033333352333333FF333333FF333333FF
          333333FF333333FE333333C6333333DB333333FF333333FF333333FF333333FF
          333333FF00000000000000003333330033333352333333FF333333FF333333FF
          333333FF333333FD3333334C33333390333333FF333333FF333333FF333333FF
          333333FF00000000000000003333330033333352333333FF333333FF333333FF
          333333FF333333E9333333303333336D333333FC333333FF333333FF333333FF
          333333FF00000000000000003333330033333352333333FF333333FF333333FF
          333333FF333333BD3333331333333338333333E8333333FF333333FF333333FF
          333333FF00000000000000003333330033333352333333FF333333FF333333FF
          333333FF333333E6333333813333339D333333F8333333FF333333FF333333FF
          333333FF00000000000000003333330033333352333333FF333333FF333333FF
          333333FF333333FF333333FF333333FF333333FF333333FF333333FF333333FF
          333333FF0000000000000000333333003333334A333333F8333333FF333333FF
          333333FF333333FF333333FF333333FF333333FF333333FF333333FF333333FF
          333333F0000000000000000033333300333333123333338B333333CA333333C7
          333333CA333333CC333333CC333333CC333333CC333333C9333333C8333333C3
          3333336A00000000000000000000000033333300333333013333334733333395
          3333333C33333304333333073333330733333306333333643333338F33333322
          33333300000000000000000000000000000000003333330033333376333333FF
          3333336B33333300333333003333330033333303333333B1333333FD33333333
          3333330000000000000000000000000000000000333333003333335F333333FB
          3333339B33333307333333003333330033333322333333D1333333E433333327
          33333300000000000000000000000000000000003333330033333326333333D7
          333333E83333335C3333330E3333331A33333389333333FB333333A73333330C
          3333330000000000000000000000000000000000333333003333330233333374
          333333F3333333F0333333D0333333D7333333F9333333DA3333334233333300
          333333000000000000000000000000000000000000000000333333003333330D
          3333336B333333D3333333FC333333F6333333BB3333334A3333330233333300
          00000000E0000000E0000000E0000000E0000000E0000000E0000000E0000000
          E0000000E0000000E0000000F0010000F8E10000F8610000F8010000F8030000
          FC030000}
        Transparent = True
      end
    end
    object pnlColorValue: TPanel
      Left = 0
      Top = 0
      Width = 256
      Height = 100
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
      object pnlRGB: TPanel
        Left = 0
        Top = 0
        Width = 256
        Height = 25
        Cursor = crHandPoint
        Hint = #28857#20987#22797#21046#39068#33394#20540
        Align = alTop
        BevelOuter = bvNone
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnClick = pnlRGBClick
        object Label1: TLabel
          Left = 0
          Top = 0
          Width = 51
          Height = 25
          Align = alLeft
          Caption = '  RGB: '
        end
      end
      object pnlHSB: TPanel
        Left = 0
        Top = 75
        Width = 256
        Height = 25
        Cursor = crHandPoint
        Hint = #28857#20987#22797#21046#39068#33394#20540
        Align = alClient
        BevelOuter = bvNone
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = pnlHSBClick
        object Label4: TLabel
          Left = 0
          Top = 0
          Width = 50
          Height = 25
          Align = alLeft
          Caption = '  HSB: '
        end
      end
      object pnlCMYK: TPanel
        Left = 0
        Top = 50
        Width = 256
        Height = 25
        Cursor = crHandPoint
        Hint = #28857#20987#22797#21046#39068#33394#20540
        Align = alTop
        BevelOuter = bvNone
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        OnClick = pnlCMYKClick
        object Label3: TLabel
          Left = 0
          Top = 0
          Width = 66
          Height = 25
          Align = alLeft
          Caption = '  CMYK: '
        end
      end
      object pnlRGBNum: TPanel
        Left = 0
        Top = 25
        Width = 256
        Height = 25
        Cursor = crHandPoint
        Hint = #28857#20987#22797#21046#39068#33394#20540
        Align = alTop
        BevelOuter = bvNone
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
        OnClick = pnlRGBNumClick
        object Label2: TLabel
          Left = 0
          Top = 0
          Width = 51
          Height = 25
          Align = alLeft
          Caption = '  RGB: '
        end
      end
    end
  end
  object pnlIMG: TPanel
    Left = 0
    Top = 100
    Width = 356
    Height = 198
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    object stat: TStatusBar
      Left = 0
      Top = 179
      Width = 356
      Height = 19
      Panels = <
        item
          Width = 100
        end
        item
          Width = 50
        end>
      SimplePanel = False
    end
  end
  object tmr: TTimer
    OnTimer = tmrTimer
    Left = 144
    Top = 144
  end
end
