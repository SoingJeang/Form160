Private Sub Command1_Click() '402B40
  Dim Me As Me
  Dim var_58 As TextBox
  loc_00402BD3: Set var_58 = Me
  loc_00402BE2: var_50 = Text1.Text
  loc_00402C14: var_28 = var_50
  loc_00402C2B: var_68 = Len(var_28)
  loc_00402C32: var_68 = CInt(Me)
  loc_00402C44: var_118 = var_68

  loc_00402C5F: If 00000001h > var_68 Then GoTo loc_00402D54
  loc_00402C83: var_78 = Mid(var_28, 1, 1) 
  loc_00402CB7: var_54 = CStr(Left(4, 1))
  loc_00402CC7: var_50 = CStr(var_78)
  loc_00402CD9: var_A8 = Chr(Asc(var_54) xor Ansi(var_50))
  loc_00402CFC: var_38 = var_38 & var_A8
  loc_00402D42: 00000001h = 00000001h + 1
  loc_00402D4C: var_3C = 00000001h+var_3C
  loc_00402D4F: GoTo loc_00402C52             'loop char xor name[3] --> string

  loc_00402D54: 'Referenced from: 00402C5F
  loc_00402D63: var_68 = Len(var_38)
  loc_00402D6A: var_68 = CInt(var_58)
  loc_00402D75: var_120 = var_68
  loc_00402D87: If 00000001h > var_68 Then GoTo loc_00402EBA
  loc_00402D92: If var_18 <= 4 Then GoTo loc_00402D97
  loc_00402D97: 'Referenced from: 00402D92
  loc_00402DB1: call Asc(var_54) xor edx(var_78, var_38, 00000001h, 2, @Asc(%StkVar1), Asc(var_54) xor edx)
  loc_00402DEF: call Asc(var_54) xor edx(var_A8, 2, var_18, 2)
  loc_00402E0C: var_50 = CStr(var_78)
  loc_00402E41: var_4C = var_4C & Chr(Asc(CStr(var_A8)) xor ecx)     'loopchar xor 2000 
  loc_00402E8D: edx = var_18 + 1
  loc_00402EA0: 00000001h = 00000001h + var_3C
  loc_00402EA4: var_18 = var_18 + 1
  loc_00402EB2: var_3C = 00000001h+var_3C
  loc_00402EB5: GoTo loc_00402D80
  loc_00402EBA: 'Referenced from: 00402D87                            ' loopchar == "VeiajeEjbavwij"
  loc_00402EE2: If (var_4C = "VeiajeEjbavwij") = 0 Then GoTo loc_00402F89
  loc_00402F2B: var_78 = "Invalid"
  loc_00402F46: var_68 = "Password incorrect, please try again ..."
  loc_00402F87: GoTo loc_00402F99
  loc_00402F89: 'Referenced from: 00402EE2
  loc_00402F99: 'Referenced from: 00402F87
  loc_00402FC1: If (var_4C = "VeiajeEjbavwij") = 0 Then GoTo loc_00403056
  loc_00402FFA: var_78 = "Valid"
  loc_00403015: var_68 = "Password correct, hehe, :-)"
  loc_00403056: 'Referenced from: 00402FC1
  loc_00403062: GoTo loc_004030B7
  loc_004030B6: Exit Sub
  loc_004030B7: 'Referenced from: 00403062
  loc_004030CA: GoTo loc_00esi
  loc_004030CC: Exit Sub
End Sub