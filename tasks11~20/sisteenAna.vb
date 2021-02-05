Private Sub Command1_Click() '403620
  Dim var_2C As TextBox
  loc_004036BB: var_1C = Text1.Text
  loc_00403704: If var_2C <> 0 Then GoTo loc_00403A24
  loc_00403727: var_1C = Text1.Text
  loc_00403751: var_ret_1 = Len(var_1C)
  loc_0040375A: var_EC = var_ret_1
  loc_0040377C: 
  loc_00403787: If var_18 > var_ret_1 Then GoTo loc_00403AA4
  loc_004037AA: var_1C = Text1.Text
  loc_004037E5: var_24 = Text1.Text
  loc_00403831: var_28 = Mid$(var_24, vbNull, 1)
  loc_00403859: var_20 = Mid$(var_1C, vbNull, 1)
  loc_004038AD: If var_2C <> 0 Then GoTo loc_00403A22
  loc_004038D3: var_1C = Text1.Text
  loc_00403909: var_58 = var_18 xor 0002h
  loc_0040391B: var_28 = Str$()
  loc_0040393F: var_20 = Mid$(var_1C, vbNull, 1)
  loc_0040394B: var_48 = Asc(var_20)
  loc_0040397D: var_C8 = (Str$(Asc(var_20)) - global_4010D8)
  loc_00403997: var_68 = var_28
  loc_004039A5: var_80 = Right(var_28, 1)
  loc_00403A04: If (var_C8 <> var_80) <> 0 Then GoTo loc_00403A22
  loc_00403A0E: 00000001h = 00000001h + var_18
  loc_00403A18: var_18 = 00000001h+var_18
  loc_00403A1D: GoTo loc_0040377C
  loc_00403A22: 'Referenced from: 004038AD
  loc_00403A24: 'Referenced from: 00403704
  loc_00403A8C: MsgBox("Sorry, try again!", 0, "Wrong serial!", var_60, var_70)
  loc_00403AA2: GoTo loc_00403B22
  loc_00403AA4: 'Referenced from: 00403787
  loc_00403B0C: MsgBox("Good job, tell me how you do that!", 0, "Correct serial!", var_60, var_70)
  loc_00403B22: 'Referenced from: 00403AA2
  loc_00403B36: GoTo loc_00403B87
  loc_00403B86: Exit Sub
  loc_00403B87: 'Referenced from: 00403B36
  loc_00403B87: Exit Sub
End Sub