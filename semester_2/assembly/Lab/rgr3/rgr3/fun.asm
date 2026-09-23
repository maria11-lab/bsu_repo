.386
.model flat 

public _RemoveMin1@8
public RemoveMin2
public @RemoveMin3@8

.code

_RemoveMin1@8 proc
    push ebp
    mov ebp, esp
    
    mov ebx, [ebp + 8]
    mov esi, [ebp + 12]
    call core_logic

    mov esp, ebp
    pop ebp
    
    
    ret 8
_RemoveMin1@8 endp

RemoveMin2 proc
    push ebp
    mov ebp, esp
    mov ebx, [ebp + 8]
    mov esi, [ebp + 12]
    call core_logic
    pop ebp
    ret
RemoveMin2 endp

@RemoveMin3@8 proc
    mov ebx, ecx
    mov esi, edx
    call core_logic
    ret
@RemoveMin3@8 endp

core_logic proc
    push ebx
    push esi
    push edi

    test esi, esi
    jz done_empty

    mov eax, [ebx]
    xor ecx, ecx
find_m:
    inc ecx
    cmp ecx, esi
    jge start_d
    mov edi, [ebx + ecx * 4]
    cmp edi, eax
    jge find_m
    mov eax, edi
    jmp find_m

start_d:
    push eax
    xor ecx, ecx
    xor edi, edi
d_loop:
    cmp ecx, esi
    jge f_z
    mov edx, [ebx + ecx * 4]
    cmp edx, eax
    jz skip
    mov [ebx + edi * 4], edx
    inc edi
skip:
    inc ecx
    jmp d_loop

f_z:
    cmp edi, esi
    jge fin
    mov dword ptr [ebx + edi * 4], 0
    inc edi
    jmp f_z

fin:
    pop eax
done_empty:
    pop edi
    pop esi
    pop ebx
    ret
core_logic endp

end