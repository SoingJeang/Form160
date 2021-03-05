0043E4C0   > \50                   push eax                                            ;  kernel32.BaseThreadInitThunk
0043E4C1   .  53                   push ebx
0043E4C2   .  57                   push edi
0043E4C3   .  8BF8                 mov edi,eax                                         ;  kernel32.BaseThreadInitThunk
0043E4C5   .  68 14E54300          push defiler_.0043E514                              ; /pModule = "kernel32.dll"
0043E4CA   .  FF15 8C124400        call dword ptr ds:[<&kernel32.GetModuleHandleA>]    ; \GetModuleHandleA
0043E4D0   .  8BD8                 mov ebx,eax                                         ;  kernel32.BaseThreadInitThunk
0043E4D2   .  85DB                 test ebx,ebx
0043E4D4   .  74 2A                je short defiler_.0043E500
0043E4D6   .  90                   nop
0043E4D7   .  68 24E54300          push defiler_.0043E524                              ; /ProcNameOrOrdinal = "lstrcmp"
0043E4DC   .  53                   push ebx                                            ; |hModule = 7EFDE000
0043E4DD   .  FF15 88124400        call dword ptr ds:[<&kernel32.GetProcAddress>]      ; \GetProcAddress
0043E4E3   .  8BD8                 mov ebx,eax                                         ;  kernel32.BaseThreadInitThunk
0043E4E5   .  85DB                 test ebx,ebx
0043E4E7   .  74 17                je short defiler_.0043E500
0043E4ED   .  68 2CE54300          push defiler_.0043E52C                              ;  ASCII "Exit1"
0043E4F2   .  FF77 08              push dword ptr ds:[edi+0x8]
0043E4F5   .  FFD3                 call ebx
0043E4F7   .  74 6B                je short defiler_.0043E564
0043E500   >  5E                   pop esi                                             ;  kernel32.760733CA
0043E501   .  5B                   pop ebx                                             ;  kernel32.760733CA
0043E502   .  58                   pop eax                                             ;  kernel32.760733CA
0043E503   .  85C0                 test eax,eax                                        ;  kernel32.BaseThreadInitThunk
0043E505   .^ 0F84 3520FFFF        je defiler_.00430540
0043E50B   .  8B10                 mov edx,dword ptr ds:[eax]
0043E50D   .^ E9 2920FFFF          jmp defiler_.0043053B
0043E512      90                   nop
0043E513      90                   nop
0043E514   .  6B 65 72 6E 65 6C 33>ascii "kernel32.dll",0
0043E521      90                   nop
0043E522      90                   nop
0043E523      90                   nop
0043E524   .  6C 73 74 72 63 6D 70>ascii "lstrcmp",0
0043E52C   .  45 78 69 74 31 00    ascii "Exit1",0
0043E532      90                   nop
0043E533      90                   nop
0043E534   .  45 78 69 74 00       ascii "Exit",0
0043E539      90                   nop
0043E53A      90                   nop
0043E53B      90                   nop
0043E53C   .  44 6F 20 79 6F 75 20>ascii "Do you fickbirne"
0043E54C   .  20 72 65 61 6C 6C 79>ascii " really want to "
0043E55C   .  71 75 69 74 3F 00    ascii "quit?",0
0043E562      90                   nop
0043E563      90                   nop
0043E564   >  6A 04                push 0x4                                            ; /Style = MB_YESNO|MB_APPLMODAL
0043E566   .  68 34E54300          push defiler_.0043E534                              ; |Title = "Exit"
0043E56B   .  68 3CE54300          push defiler_.0043E53C                              ; |Text = "Do you fickbirne really want to quit?"
0043E570   .  6A 00                push 0x0                                            ; |hOwner = NULL
0043E572   .  FF15 7C144400        call dword ptr ds:[<&user32.MessageBoxA>]           ; \MessageBoxA
0043E578   .  83F8 07              cmp eax,0x7
0043E57B   .^ 74 83                je short defiler_.0043E500
0043E57D   .  6A 00                push 0x0                                            ; /ExitCode = 0x0
0043E57F   .  FF15 64114400        call dword ptr ds:[<&kernel32.ExitProcess>]         ; \ExitProcess

