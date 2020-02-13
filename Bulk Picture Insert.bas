Sub InsertSpecificNumberOfPictureForEachPage()
  Dim StrFolder As String
  Dim strFile As String
  Dim objDoc As Document
  Dim dlgFile As FileDialog
  Dim objInlineShape As InlineShape
  Dim nResponse As Integer
  Dim strPictureNumber As Integer
  Dim strPictureSize As String
  Dim n As Integer

  Set dlgFile = Application.FileDialog(msoFileDialogFolderPicker)
  
  With dlgFile
    If .Show = -1 Then
      StrFolder = .SelectedItems(1) & "\"
    Else
      MsgBox ("No Folder is selected!")
      Exit Sub
    End If
  End With

  strFile = Dir(StrFolder & "*.jpeg", vbNormal)
  strPictureNumber = InputBox("Input the number of the picture for each page", "Picture Number", "For exemple: 1")
  n = 1

  While strFile <> ""
    Selection.InlineShapes.AddPicture FileName:=StrFolder & strFile, LinkToFile:=False, SaveWithDocument:=True
    Selection.TypeParagraph
    Selection.Collapse Direction:=wdCollapsEnd
    'Selection.TypeText Text:=Left(strFile, InStrRev(strFile, ".") - 1)
    Selection.ParagraphFormat.Alignment = wdAlignParagraphCenter
    If ActiveDocument.InlineShapes.Count = strPictureNumber * n Then
      Selection.InsertNewPage
      Selection.TypeBackspace
      n = n + 1
    End If
    Selection.TypeParagraph
    strFile = Dir()
  Wend

  For Each objInlineShape In ActiveDocument.InlineShapes
    objInlineShape.Select
    Selection.ParagraphFormat.Alignment = wdAlignParagraphCenter
  Next objInlineShape

  nResponse = MsgBox("Do you want to resize all pictures?", 4, "Resize Picture")
  If nResponse = 6 Then
    strPictureSize = InputBox("Input the height and width of the picture, seperated by comma", "Height and Width", "For exemple:500,500")
    For Each objInlineShape In ActiveDocument.InlineShapes
      objInlineShape.Height = Split(strPictureSize, ",")(0)
      objInlineShape.Width = Split(strPictureSize, ",")(1)
    Next objInlineShape
  End If
End Sub

