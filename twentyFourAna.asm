loc_4012AD:                             ; CODE XREF: .text:004012B6j
.text:004012AD                 add     eax, [ebx]
.text:004012AF                 inc     ebx
.text:004012B0                 cmp     ebx, offset unk_40317C
.text:004012B6                 jnz     short loc_4012AD ; 循环相加每个ascii字符
.text:004012B8                 pop     ebx             ; password
.text:004012B9                 add     eax, ebx
.text:004012BB                 xor     ds:dword_4012D9, eax
.text:004012C1                 shr     eax, 10h
.text:004012C4                 sub     word ptr ds:dword_4012D9, ax
.text:004012CB                 mov     esi, offset loc_4011EC
.text:004012D0                 mov     ecx, 3Eh
.text:004012D5                 xor     ebx, ebx
.text:004012D7                 jmp     short loc_4012DD
.text:004012D7 ; ---------------------------------------------------------------------------
.text:004012D9 dword_4012D9    dd 584554h              ; CODE XREF: .text:004012E9j
.text:004012D9                                         ; DATA XREF: .text:CheckFuncw ...
.text:004012DD ; ---------------------------------------------------------------------------
.text:004012DD
.text:004012DD loc_4012DD:                             ; CODE XREF: .text:004012D7j
.text:004012DD                                         ; .text:004012E1j
.text:004012DD                 lodsd
.text:004012DE                 xor     ebx, eax
.text:004012E0                 dec     ecx
.text:004012E1                 jnz     short loc_4012DD
.text:004012E3                 cmp     ebx, 0AFFCCFFBh
.text:004012E9                 jz      short near ptr dword_4012D9
.text:004012EB
.text:004012EB WrongResultFunc:                        ; CODE XREF: .text:0040128Aj
.text:004012EB                                         ; .text:004012A1j
.text:004012EB                 push    offset aYourSerialIsNo ; "Your serial is not valid."
.text:004012F0                 push    dword_40315C
.text:004012F6                 call    SetWindowTextA
.text:004012FB                 xor     eax, eax
.text:004012FD                 leave
.text:004012FE                 retn    10h
.text:00401301 ; ---------------------------------------------------------------------------
.text:00401301                 push    offset aYesYouFoundYou ; "YES! You found your serial!!"
.text:00401306                 push    dword_40315C