mov ecx, 1
0040157D  |.  8B45 E4       mov eax,[local.7]                        ;  name
00401580  |>  8A18          /mov bl,byte ptr ds:[eax]                ; one
00401582  |.  32D9          |xor bl,cl                               ; ecx = 1      name[i] ^= ecx      ecx++
00401584  |.  8818          |mov byte ptr ds:[eax],bl
00401586  |.  41            |inc ecx
00401587  |.  40            |inc eax
00401588  |.  8038 00       |cmp byte ptr ds:[eax],0x0
0040158B  |.^ 75 F3         \jnz short cosh_3.00401580
0040158D  |.  33C0          xor eax,eax
0040158F  |.  33DB          xor ebx,ebx
00401591  |.  33C9          xor ecx,ecx
00401593  |.  B9 0A000000   mov ecx,0xA
00401598  |.  33D2          xor edx,edx
0040159A  |.  8B45 F0       mov eax,[local.4]                        ;  password
0040159D  |>  8A18          /mov bl,byte ptr ds:[eax]
0040159F  |.  32D9          |xor bl,cl                              ; ecx = 0xA     password[i] ^= ecx  ecx++
004015A1  |.  8818          |mov byte ptr ds:[eax],bl
004015A3  |.  41            |inc ecx
004015A4  |.  40            |inc eax
004015A5  |.  8038 00       |cmp byte ptr ds:[eax],0x0
004015A8  |.^ 75 F3         \jnz short cosh_3.0040159D
004015AA  |.  8B45 E4       mov eax,[local.7]
004015AD  |.  8B55 F0       mov edx,[local.4]
004015B0  |>  33C9          /xor ecx,ecx
004015B2  |.  8A18          |mov bl,byte ptr ds:[eax]
004015B4  |.  8A0A          |mov cl,byte ptr ds:[edx]
004015B6  |.  3AD9          |cmp bl,cl
004015B8  |.  75 09         |jnz short <cosh_3.ErrorMessage>
004015BA  |.  40            |inc eax
004015BB  |.  42            |inc edx
004015BC  |.  8038 00       |cmp byte ptr ds:[eax],0x0
004015BF  |.^ 75 EF         \jnz short cosh_3.004015B0
004015C1  |.  EB 16         jmp short <cosh_3.SuccessMessage>
004015C3 >|>  6A 00         push 0x0
004015C5  |.  68 6C304000   push cosh_3.0040306C                     ;  ASCII "ERROR"
004015CA  |.  68 40304000   push cosh_3.00403040                     ;  ASCII "One of the Details you entered was wrong"
004015CF  |.  8B4D E0       mov ecx,[local.8]
004015D2  |.  E8 BB020000   call <jmp.&MFC42.#?MessageBoxA@CWnd@@QAE>
004015D7  |.  EB 14         jmp short cosh_3.004015ED
004015D9 >|>  6A 00         push 0x0
004015DB  |.  68 34304000   push cosh_3.00403034                     ;  ASCII "YOU DID IT"
004015E0  |.  68 20304000   push cosh_3.00403020                     ;  ASCII "Well done,Cracker"

