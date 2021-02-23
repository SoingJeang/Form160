Private Sub Command1_Click() '402B10
  Dim Me As Me
  Dim var_4C As TextBox
  Dim var_48 As TextBox
  Dim var_12C As Label
  Dim var_124 As Label
  loc_00402BE6: var_124 = var_4C
  loc_00402C06: var_28 = Text1.Text                                 'name
  loc_00402C37: var_eax = Unknown_VTable_Call[edx+00000054h]
  loc_00402C8E: var_28 = Text1.Text
  loc_00402CE6: If var_124 = 0 Then GoTo loc_00402D9C
  loc_00402D50: var_74 = " Der Name muss mindestens 5 Chars haben "
  loc_00402D6D: MsgBox(var_74, 64, "Colormaster´s Crackme 7.0", var_94, var_A4)
  loc_00402D97: GoTo loc_0040379E
  loc_00402D9C: 'Referenced from: 00402CE6
  loc_00402DBE: call edi(var_48, var_74, %ecx = %S_edx_S, var_48, var_4C, Me, var_124, var_28, var_48, var_4C, Me, var_4C, Me, Me)
  loc_00402DCD: var_28 = Text1.Text
  loc_00402DFB: var_EC = Len(var_28)

  loc_00402E46: For var_24 =  To Len(var_28) Step 1
  loc_00402E4F: var_184 = var_178
  loc_00402E6A: If var_184 = 0 Then GoTo loc_00403099
  loc_00402E7E: call edi(var_4C, %ecx = %S_edx_S, %ecx = %S_edx_S)
  loc_00402E8D: var_2C = Text1.Text                                     
  loc_00402EBE: var_118 = Asc(var_2C)                                               '一个字符 ascii()
  loc_00402ECF: call edi(var_50, Asc(var_2C), %ecx = %S_edx_S)
  loc_00402ED1: var_12C = edi(var_50, Asc(var_2C), %ecx = %S_edx_S)
  loc_00402EE5: call edi(var_48, %ecx = %S_edx_S, %ecx = %S_edx_S)
  loc_00402EF4: var_28 = Label2.Caption                                             '???
  loc_00402FA8: var_198 = var_12C
  loc_00402FBC: Label2.Caption = CStr(((var_28 * var_118) * global_401100) / Hex(21))
  loc_00403020: call edi(var_48, %ecx = %S_edx_S, %ecx = %S_edx_S)
  loc_00403027: var_eax = Text1.SetFocus
  loc_00403065: SendKeys "{HOME}{DEL}", True
  loc_00403086: Next var_24
  loc_0040308C: var_184 = Next var_24
  loc_00403094: GoTo loc_00402E64 'loop
  loc_00403099: 'Referenced from: 00402E6A
  loc_004030A7: call edi(var_4C, Next var_24, %ecx = %S_edx_S, var_168, var_178)
  loc_004030A9: var_124 = edi(var_4C, Next var_24, %ecx = %S_edx_S, var_168, var_178)
  loc_004030BD: call edi(var_48, %ecx = %S_edx_S, %ecx = %S_edx_S)
  loc_004030CC: var_28 = Label1.Caption
  loc_00403108: call __vbaStrR8(Fix(var_28))
  loc_00403113: var_2C = __vbaStrR8(Fix(var_28))
  loc_00403123: Label1.Caption = var_2C
  loc_0040316C: call edi(var_4C, var_48, %ecx = %S_edx_S)
  loc_0040316E: var_124 = edi(var_4C, var_48, %ecx = %S_edx_S)
  loc_00403182: call edi(var_48, %ecx = %S_edx_S, %ecx = %S_edx_S)
  loc_0040318D: var_28 = Label4.Caption
  loc_004031B2: Label4.MousePointer = var_28
  loc_00403203: SendKeys "{END}", True
  loc_00403220: call edi(var_4C, %ecx = %S_edx_S, %ecx = %S_edx_S)
  loc_0040322B: var_2C = Label3.Caption
  loc_00403251: call edi(var_54, var_2C, %ecx = %S_edx_S)
  loc_0040325C: var_34 = Text1.Text
  loc_00403294: call edi(var_64, %ecx = %S_edx_S, %ecx = %S_edx_S)
  loc_00403299: var_154 = edi(var_64, %ecx = %S_edx_S, %ecx = %S_edx_S)
  loc_004032AA: call edi(var_48, edi(var_64, %ecx = %S_edx_S, %ecx = %S_edx_S), %ecx = %S_edx_S)
  loc_004032B9: var_28 = Text1.Text
  loc_00403319: var_EC = (var_2C + Asc(var_28))
  loc_00403334: call edi(var_50, Err.Number, %ecx = %S_edx_S)
  loc_00403343: var_30 = Label3.Caption
  loc_0040336B: Asc(var_34) = Asc(var_34) * 0019h
  loc_004033A2: var_6C = (var_30 - Asc(var_34))
  loc_004033AF: var_84 = Hex(var_6C)
  loc_004033C3: call edi(var_58, %ecx = %S_edx_S, %ecx = %S_edx_S)
  loc_004033CE: var_38 = Label3.Caption
  loc_004033FE: var_9C = var_38
  loc_0040340E: var_B4 = Hex(var_38)
  loc_00403422: call edi(var_5C, %ecx = %S_edx_S, %ecx = %S_edx_S)
  loc_0040342D: var_3C = Text1.Text
  loc_00403459: call edi(var_60, var_3C, %ecx = %S_edx_S)
  loc_00403464: var_40 = Text1.Text
  loc_00403499: Asc(var_3C) = Asc(var_3C) * Len(var_40)
  loc_004034B2: Asc(var_3C) = Asc(var_3C) - 0000001Bh
  loc_004034C1: var_FC = Asc(var_3C)
  loc_004034D8: var_94 = ((var_28 * var_118) * global_401100) & var_84
  loc_0040350D: var_44 = CStr(var_94 & var_B4 &)
  loc_0040351D: var_eax = Unknown_VTable_Call[ecx+00000054h]
  loc_004035CB: call edi(var_48, %ecx = %S_edx_S, %ecx = %S_edx_S)
  loc_004035D6: var_28 = Text2.Text
  loc_00403602: call edi(var_4C, var_28, %ecx = %S_edx_S)
  loc_0040360D: var_2C = Label5.Caption
  loc_00403633: call edi(var_50, var_2C, %ecx = %S_edx_S)
  loc_0040363E: var_30 = Text1.Text
  loc_0040369F: var_3C = var_2C & CStr(Len(var_30)) & "-CM"
  loc_004036C5: esi = (var_28 = var_3C) + 1
  loc_004036EB: If (var_28 = var_3C) + 1 = 0 Then GoTo loc_0040379C
  loc_00403772: MsgBox(" Gratulation ,du hast es geschafft!", 64, "Colormaster´s Crackme 7.0", var_94, var_A4)
  loc_0040379C: 'Referenced from: 004036EB
  loc_0040379E: 'Referenced from: 00402D97
  loc_004037A7: GoTo loc_00403839
  loc_00403838: Exit Sub
  loc_00403839: 'Referenced from: 004037A7
  loc_0040385B: Exit Sub
End Sub