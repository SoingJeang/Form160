Private Sub Command1_Click() '404230
  Dim var_B8 As TextBox
  Dim var_A8 As TextBox
  loc_0040432C: var_5C = CLng(Timer)
  loc_0040438B: For var_80 = 1 To 1000 Step 1
  loc_00404393: If var_14C = 0 Then GoTo loc_00404461 '失败
  loc_004043ED: For var_58 = 1 To 250 Step 1
  loc_004043F5: If var_16C = 0 Then GoTo loc_00404444
  loc_00404409: If (global_00402A34 <> global_00402A34) <> 0 Then GoTo loc_0040442A
  loc_00404424: var_24 = CInt(1)
  loc_0040442A: 'Referenced from: 00404409
  loc_0040443C: Next var_58
  loc_00404442: GoTo loc_004043F3
  loc_00404444: 'Referenced from: 004043F5
  loc_00404456: Next var_80
  loc_0040445C: GoTo loc_00404391
  loc_00404461: 'Referenced from: 00404393
  loc_0040446D: CLng(Timer) = CLng(Timer) - var_5C
  loc_00404479: If CLng(Timer) <= 5 Then GoTo loc_0040452C '时间小于5秒，正常行为
  loc_004044B8: var_100 = "Cheater!!!   CHEATER!!!   Cheater!!!   CHEATER!!!"
  loc_004044D6: var_F0 = "  You have SmartCheck loaded!...Close it and try again!!!"
  loc_004044E6: var_B8 = "  You have SmartCheck loaded!...Close it and try again!!!"
  loc_00404505: MsgBox(var_B8, 0, "Cheater!!!   CHEATER!!!   Cheater!!!   CHEATER!!!", 10, 10)
  loc_00404527: GoTo loc_00404F86
  
  loc_0040452C: 'Referenced from: 00404479
  loc_0040454F: var_84 = Text1.Text
  loc_0040459F: If ebx <> 0 Then GoTo loc_00404EDE  '失败 len() >= 5
  loc_004045F8: var_84 = Text1.Text
  loc_00404623: var_100 = Len(var_84)

'第一次循环，var_48 ++
  loc_0040466E: For var_6C = 1 To Len(var_84) Step 1
  loc_0040467A: var_1D0 = var_18C
  loc_0040469E: If var_1D0 = 0 Then GoTo loc_00404899
  loc_004046CB: var_84 = Text1.Text
  loc_00404716: var_88 = Text1.Text
  loc_00404791: var_8C = Mid$(var_84, CLng(var_6C), 2) 'str(1,1) str(2,1)
  loc_004047B4: var_ret_2 = CLng(var_6C + 1) 'index + 1
  loc_004047CC: var_90 = Mid$(var_88, var_ret_2, 1)
  loc_004047F6: edi = (var_8C = var_90) + 1
  loc_0040483B: If (var_8C = var_90) + 1 = 0 Then GoTo loc_00404874 ' if(str[index] == str[index+1]) var_48 += 1 
  loc_0040486E: var_48 = var_48 + 1
  loc_00404874: 'Referenced from: 0040483B
  loc_00404886: Next var_6C

  loc_0040488C: var_1D0 = Next var_6C 'var_1D0 = len + 1

  loc_00404894: GoTo loc_00404698
  loc_00404899: 'Referenced from: 0040469E
  loc_004048C0: var_84 = Text1.Text
  loc_004048F1: Len(var_84) = Len(var_84) - 00000001h
  loc_00404900: var_F0 = Len(var_84)
  loc_00404921: var_134 = (var_48 = Len(var_84))
  loc_00404941: If var_134 <> 0 Then GoTo loc_00404EDE '失败
  loc_00404982: var_84 = Text1.Text
  loc_004049B3: var_100 = Len(var_84)
  
  ' Second Loop ascii累加
  loc_004049FE: For var_6C = 1 To Len(var_84) Step 1
  loc_00404A0A: var_1D4 = var_1BC
  loc_00404A28: If var_1D4 = 0 Then GoTo loc_00404D4B ' 成功
  loc_00404A55: var_84 = Text1.Text
  loc_00404A8C: var_B0 = Len(var_84)
  loc_00404AE0: var_C0 = var_A8
  loc_00404B04: var_88 = CStr(Left(var_A8, 1)) ""
  loc_00404B17: var_E0 = Asc(var_88)
  loc_00404B5C: var_90 = Hex$(Asc(var_88))
  loc_00404B70: var_8C = Hex$(Len(var_84) ) '长度的hex码 * str(1,1)
  loc_00404B91: var_eax = TextBox.1784
  loc_00404BBC: var_38 = var_98
  loc_00404C5B: var_84 = Text1.Text
  loc_00404CBA: var_88 = Mid$(var_84, CLng(var_6C), 1) 'str(index, 1)
  loc_00404CC3: var_100 = Asc(var_88)                   'ascii(str(1,1))
  loc_00404CF1: var_34 = var_34 + Asc(var_88)           '累加'
  loc_00404D3A: Next var_6C
  loc_00404D40: var_1D4 = Next var_6C

  loc_00404D46: GoTo loc_00404A22
  loc_00404D4B: 'Referenced from: 00404A28
  loc_00404D82: var_84 = Hex$(var_34)
  loc_00404DA0: var_eax = TextBox.1784
  loc_00404DE2: var_34 = var_8C
                                    ' if(var_84 == var_34) var_f0 = "ffff"
  loc_00404E11: var_F0 = "FFFF"
  loc_00404E30: If (var_34 = "FFFF") = 0 Then GoTo loc_00404EE3
  loc_00404E6A: var_100 = "Correct serial!"
  loc_00404E88: var_F0 = "Good job, tell me how you do that!"
  loc_00404EB7: MsgBox("Good job, tell me how you do that!", 0, "Correct serial!", 10, 10)
  loc_00404ED9: GoTo loc_00404F86
  loc_00404EDE: 'Referenced from: 0040459F
  loc_00404EE3: 'Referenced from: 00404E30
  loc_00404F17: var_100 = "Wrong serial!"
  loc_00404F35: var_F0 = "Sorry, try again!"
  loc_00404F64: MsgBox("Sorry, try again!", 0, "Wrong serial!", 10, 10)
  loc_00404F86: 'Referenced from: 00404527
  loc_00404F9A: GoTo loc_0040501A
  loc_00405019: Exit Sub
  loc_0040501A: 'Referenced from: 00404F9A
  loc_0040508A: Exit Sub
End Sub