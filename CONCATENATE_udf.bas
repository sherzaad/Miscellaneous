Attribute VB_Name = "CONCATENATE_udf"
Function CONCATENATE_udf(delim As String, ParamArray Vals() As Variant)
'does same thing as CONCATENATE but allows inputs of range(s) instead of only individual cell addresses
'if no delimiter is required, input delim as "". To use 'comma' as delimiter for example, input delim as ","
Dim rng As Range, c As Range
Dim i As Integer
Dim str As String

    Set rng = Nothing
        
    str = ""
    
    For i = 0 To UBound(Vals)
        Set rng = Range(Vals(i).Address)
        
        For Each c In rng
            str = str & c.Value & delim
        Next
    Next
    
    If delim <> "" Then
        CONCATENATE_udf = Left(str, Len(str) - 1)
    Else
        CONCATENATE_udf = str
    End If

End Function
