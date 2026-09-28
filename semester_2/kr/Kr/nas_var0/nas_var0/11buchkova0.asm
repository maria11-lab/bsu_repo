.386
.model flat

public _task1@12
public _task2
public @task3@12

.code

_task1@12 proc
	push ebp
	mov ebp, esp
    ;надо ещё все регистры запушить и потом запопить
	mov edx, [ebp+8]
    mov ebx, [ebp+12]
    mov esi, [ebp+16]
    mov ecx, 0

loop_start:
    cmp ecx, ebx
    jge loop_end

    cmp ecx, edx
    je next_step

    mov eax, edx
    imul eax, ebx
    add eax, ecx
    shl eax, 2

    mov edi, ecx
    imul edi, ebx
    add edi, edx
    shl edi, 2

    push dword ptr [esi + eax]
    push dword ptr [esi + edi]
    pop dword ptr [esi + eax]
    pop dword ptr [esi + edi]

next_step:
    inc ecx
    jmp loop_start

loop_end:
    pop ebp
	ret 12
_task1@12 endp

_task2 proc
	push ebp
	mov ebp, esp
    ;надо ещё все регистры запопить и потом запушить
	mov edx, [ebp+8]
    mov ebx, [ebp+12]
    mov esi, [ebp+16]
    mov ecx, 0

loop_start:
    cmp ecx, ebx
    jge loop_end

    cmp ecx, edx
    je next_step

    mov eax, edx
    imul eax, ebx
    add eax, ecx
    shl eax, 2

    mov edi, ecx
    imul edi, ebx
    add edi, edx
    shl edi, 2

    push dword ptr [esi + eax]
    push dword ptr [esi + edi]
    pop dword ptr [esi + eax]
    pop dword ptr [esi + edi]

next_step:
    inc ecx
    jmp loop_start

loop_end:
    pop ebp
	ret
_task2 endp


@task3@12 proc
    push ebp
    mov ebp, esp
    mov ebx, edx
	mov edx, ecx
    mov esi, [ebp+8]
    mov ecx, 0

loop_start:
    cmp ecx, ebx
    jge loop_end

    cmp ecx, edx
    je next_step

    mov eax, edx
    imul eax, ebx
    add eax, ecx
    shl eax, 2

    mov edi, ecx
    imul edi, ebx
    add edi, edx
    shl edi, 2

    push dword ptr [esi + eax]
    push dword ptr [esi + edi]
    pop dword ptr [esi + eax]
    pop dword ptr [esi + edi]

next_step:
    inc ecx
    jmp loop_start

loop_end:
    pop ebp
    ret 4
@task3@12 endp
end