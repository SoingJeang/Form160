00401361 > .  8D3D 8C314000 lea edi,dword ptr ds:[<EnterName>]
00401367   .  0FBE05 683140>movsx eax,byte ptr ds:[0x403168]
0040136E   .  03F8          add edi,eax
00401370   .  FE05 68314000 inc byte ptr ds:[0x403168]
00401376   .  A1 88314000   mov eax,dword ptr ds:[<EnterCode>]
0040137B   .  8B25 A0314000 mov esp,dword ptr ds:[0x4031A0]
00401381   .  40            inc eax
00401382   .  FF05 88314000 inc dword ptr ds:[<EnterCode>]
00401388   .  3307          xor eax,dword ptr ds:[edi]
0040138A   .  A3 88314000   mov dword ptr ds:[<EnterCode>],eax
0040138F   .  803D 68314000>cmp byte ptr ds:[0x403168],0x10  ; 16 次 
00401396      75 07         jnz short Chafe_1.0040139F
00401398   .  8005 66314000>add byte ptr ds:[0x403166],0x4
0040139F   >  C9            leave

checkName = 0x00000000 + reverse(EnterName)
echeckcode = EnterCode
echeckcode = (echeckcode + 1) ^ (checkName[-4-i:-1])