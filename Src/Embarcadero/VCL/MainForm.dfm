object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = 'frmMain'
  ClientHeight = 1415
  ClientWidth = 2264
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -25
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnCreate = FormCreate
  PixelsPerInch = 200
  TextHeight = 35
  object Panel1: TPanel
    Left = 1937
    Top = 0
    Width = 327
    Height = 1379
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Align = alRight
    TabOrder = 0
    object btnCount: TButton
      Left = 12
      Top = 21
      Width = 291
      Height = 52
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'btnCount'
      TabOrder = 0
      OnClick = btnCountClick
    end
    object btnParse: TButton
      Left = 12
      Top = 391
      Width = 291
      Height = 52
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'btnParse'
      TabOrder = 1
      OnClick = btnParseClick
    end
    object btnShow: TButton
      Left = 12
      Top = 85
      Width = 291
      Height = 53
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'btnShow'
      TabOrder = 2
      OnClick = btnShowClick
    end
    object lbValues: TListBox
      Left = 12
      Top = 154
      Width = 291
      Height = 202
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      ItemHeight = 35
<<<<<<< HEAD
      MultiSelect = True
=======
<<<<<<< HEAD
>>>>>>> old-project/main
=======
>>>>>>> old-project/fish
>>>>>>> fish
      TabOrder = 3
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 1937
    Height = 1379
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Align = alClient
    TabOrder = 1
    object Splitter1: TSplitter
      Left = 1
      Top = 1186
      Width = 1935
      Height = 6
      Cursor = crVSplit
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Align = alBottom
      ExplicitLeft = 2
      ExplicitTop = 179
      ExplicitWidth = 2229
    end
    object Panel3: TPanel
      Left = 1
      Top = 1
      Width = 1935
      Height = 85
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Align = alTop
      TabOrder = 0
      object lblDirectory: TLabel
        Left = 33
        Top = 25
        Width = 129
        Height = 35
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Caption = 'lblDirectory'
      end
      object edtDirectory: TEdit
        Left = 221
        Top = 22
        Width = 1361
        Height = 43
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        TabOrder = 0
        Text = 'edtDirectory'
      end
    end
    object memError: TMemo
      Left = 1
      Top = 1192
      Width = 1935
      Height = 186
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Align = alBottom
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -29
      Font.Name = 'Courier New'
      Font.Style = []
      Lines.Strings = (
        'memError')
      ParentFont = False
      ScrollBars = ssVertical
      TabOrder = 1
    end
    object lvOutput: TListView
      Left = 1
      Top = 86
      Width = 1935
      Height = 1100
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Align = alClient
      Columns = <>
      TabOrder = 2
    end
  end
  object sbMain: TStatusBar
    Left = 0
    Top = 1379
    Width = 2264
    Height = 36
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Panels = <>
  end
<<<<<<< HEAD
  object ProjectMenu: TPopupMenu
    Left = 971
    Top = 490
    object S1: TMenuItem
      Caption = #214'ffnen'
    end
  end
=======
<<<<<<< HEAD
>>>>>>> old-project/main
=======
>>>>>>> old-project/fish
>>>>>>> fish
end
