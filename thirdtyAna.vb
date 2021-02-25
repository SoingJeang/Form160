Private Sub Command1_Click() '4030F0
  Dim Me As Me
  Dim var_48 As TextBox
  loc_0040318C: var_40 = Text1.Text
  loc_004031BE: var_28 = var_40
  loc_004031DA: var_58 = Len(var_28)
  loc_004031E1: var_58 = CInt(Me)
  loc_004031E7: var_108 = var_58
  loc_004031FC: If 00000001h > var_58 Then GoTo loc_0040332F ' JUdge
  loc_00403206: If 00000001h <= 4 Then GoTo loc_0040320D  '1-4
  loc_0040320D: 'Referenced from: 00403206
  loc_00403271: var_40 = CStr(Mid(var_28, 1, 1))
  loc_0040328E: var_44 = CStr(Mid(2000, 1, 1))
  loc_004032CD: var_38 = var_38 & Chr(Asc(var_40) xor secd)
  loc_00403312: esi = 00000001h + 1
  loc_00403319: 00000001h = 00000001h + 00000001h
  loc_0040332A: GoTo loc_004031EF
  loc_0040332F: 'Referenced from: 004031FC
  loc_00403370: If (var_38 = "qBQSYdXUe_B\V") = 0 Then GoTo loc_0040345E ' Success
  loc_0040339A: var_68 = "Valid"
  loc_004033B5: var_58 = "Password correct, hehe, :-)"
  loc_00403435: Set var_48 = global_00404038
  loc_0040345C: GoTo loc_004034D8
  loc_0040345E: 'Referenced from: 00403370
  loc_00403482: var_68 = "Invalid"
  loc_0040349D: var_58 = "Password incorrect, please try again ..."
  loc_004034D8: 'Referenced from: 0040345C
  loc_004034E4: GoTo loc_00403536
  loc_00403535: Exit Sub
  loc_00403536: 'Referenced from: 004034E4
  loc_00403544: GoTo loc_00esi
  loc_00403546: Exit Sub
End Sub