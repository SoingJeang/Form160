Private Sub Command1_Click() '40E680
  'Data Table: 402AEC
  Dim var_AC As Variant
  Dim var_DC As Variant
  Dim var_BC As Variant
  Dim var_11C As Variant
  Dim var_176 As Integer
  loc_40E28C: If (Me.txtname.Text = vbNullString) Then
  loc_40E2B0:   MsgBox("You have to enter you name first.", &H40, "Error", var_FC, var_11C)
  loc_40E2C0:   Exit Sub
  loc_40E2C1: End If
  loc_40E2E1: If (Me.txtkey.Text = vbNullString) Then
  loc_40E305:   MsgBox("You have to enter a key first.", &H40, "Error", var_FC, var_11C)
  loc_40E315:   Exit Sub
  loc_40E316: End If
  loc_40E336: If (Me.txtkey.Text = vbNullString) Then
  loc_40E35A:   MsgBox("You have to enter at least 5 chars.", &H40, "Error", var_FC, var_11C)
  loc_40E36A:   Exit Sub
  loc_40E36B: End If
  loc_40E393: For var_14C = 1 To CVar(Len(Me.txtname.Text)): var_12C = var_14C 'Variant
  loc_40E3C1:   var_FC = Mid(CVar(Me.txtname.Text), CLng(var_12C), 1)
  loc_40E3D5:   var_11C = var_94 & CVar(Asc(CStr(var_FC))) 
  loc_40E3D9:   var_94 = var_11C 'Variant
  loc_40E3EF: Next var_14C 'Variant
  loc_40E3F5: ' Referenced from: 40E422
  loc_40E404: If (Len(var_94) > 9) Then
  loc_40E41E:   var_94 = Fix((var_94 / 3.141592654)) 'Variant
  loc_40E422:   GoTo loc_40E3F5
  loc_40E425: End If

  loc_40E445: var_BC = (var_94 Xor &H30F85678 - CVar(global_76))
  loc_40E449: var_94 = var_94 Xor &H30F85678 'Variant

  'no ues code
  loc_40E45A: For var_170 = 1 To 10: var_12C = var_170 'Variant
  loc_40E489:   If (Me.txtkey.Text = global_52(CLng(var_12C))) Then
  loc_40E48C:   End If
  loc_40E48F: Next var_170 'Variant

  loc_40E4B0: var_DC = (CVar(Me.txtkey.Text) - var_94)
  loc_40E4DE: If (Fix((var_94 / 3.141592654)) = CVar(Len(Me.txtname.Text))) Then
  loc_40E502:   MsgBox("Wow, you have found a correct key!", &H40, "Correct key", var_FC, var_11C)
  loc_40E533:   MsgBox("Mail me, how you got it: CyberBlade@gmx.net ", &H40, "Correct key!", var_FC, var_11C)
  loc_40E550:   Me.Command2.Caption = "Exit"
  loc_40E55B: Else
  loc_40E567:   global_80 = (global_80 + 1)
  loc_40E570:   var_176 = global_80
  loc_40E579:   If (var_176 = 6) Then
  loc_40E592:     var_AC = "-=Do you need a hint ?=-"
  loc_40E5B3:     If (MsgBox("Mail me, how you got it: CyberBlade@gmx.net ", &H24, "I can't stand it anymore", var_FC, var_11C) = 7) Then
  loc_40E5B6:       Exit Sub
  loc_40E5BA:     Else
  loc_40E5DB:       MsgBox("Forget it.", &H40, "he, he...", var_FC, var_11C)
  loc_40E5F0:       global_80 = 0
  loc_40E5F3:     End If
  loc_40E5F6:   Else
  loc_40E5FC:     If (var_176 > 3) Then
  loc_40E620:       MsgBox("Have you ever been trying to be successful in cracking my password ?", &H20, "Failed", var_FC, var_11C)
  loc_40E633:     Else
  loc_40E639:       If (var_176 <= 3) Then
  loc_40E65D:         MsgBox("Sorry, wrong key.", &H40, "Failed", var_FC, var_11C)
  loc_40E66D:       End If
  loc_40E66D:     End If
  loc_40E66D:   End If
  loc_40E66D: End If
  loc_40E677: Me.txtkey.SetFocus
  loc_40E67F: Exit Sub
End Sub