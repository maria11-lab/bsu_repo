.686
.model flat, c

.code

; --- Вежливая процедура: Сумма цифр ---
_sum_digits PROC
    push ebx            ; Сохраняем, т.к. будем использовать для делителя
    push ecx            ; Сохраняем, чтобы НЕ ИСПОРТИТЬ индекс i в главном цикле
    
    mov ebx, 10         ; Делитель
    xor ecx, ecx        ; Локальный сумматор цифр
sum_loop:
    xor edx, edx
    div ebx             ; EAX / 10
    add ecx, edx        ; Суммируем остаток
    test eax, eax
    jnz sum_loop
    
    mov eax, ecx        ; Результат возвращаем в EAX
    pop ecx             ; Восстанавливаем оригинальный индекс i
    pop ebx             ; Восстанавливаем оригинальный EBX
    ret
_sum_digits ENDP

; --- Основная логика поиска (Универсальная) ---
_find_min_sum_logic PROC
    push esi            ; Сохраняем регистры согласно этикету
    push edi
    push ebx
    push ebp

    mov esi, eax        ; EAX = адрес массива (передаем из оберток ниже)
    mov ebx, edx        ; EDX = размер массива
    
    mov ebp, 0FFFFFFFFh ; Рекорд (минимальная сумма)
    mov edi, 0          ; Рекорд (индекс)
    xor ecx, ecx        ; i = 0 (Наш индекс, который ТЕПЕРЬ НЕ ПОРТИТСЯ)

find_loop:
    cmp ecx, ebx
    je done
    
    movzx eax, word ptr [esi + ecx * 2] ; Загружаем число
    call _sum_digits                    ; Теперь ECX после вызова гарантированно не изменится!
    
    cmp eax, ebp
    jae next_step                       ; Если текущая сумма >= минимальной, пропускаем
    
    mov ebp, eax        ; Новый рекорд суммы
    mov edi, ecx        ; Новый рекорд индекса
    
next_step:
    inc ecx             ; Просто инкрементируем, никаких push/pop!
    jmp find_loop

done:
    mov eax, edi        ; Возвращаем индекс в EAX
    pop ebp
    pop ebx
    pop edi
    pop esi
    ret
_find_min_sum_logic ENDP

; --- Обертки под разные соглашения о вызовах ---

_find_min_cdecl PROC
    push ebp
    mov ebp, esp
    mov eax, [ebp + 8]  ; arr
    mov edx, [ebp + 12] ; size
    call _find_min_sum_logic
    pop ebp
    ret
_find_min_cdecl ENDP

_find_min_stdcall@8 PROC
    push ebp
    mov ebp, esp
    mov eax, [ebp + 8]
    mov edx, [ebp + 12]
    call _find_min_sum_logic
    pop ebp
    ret 8
_find_min_stdcall@8 ENDP

@find_min_fastcall@8 PROC
    mov eax, ecx        ; В fastcall параметры уже в ECX и EDX
    ; EDX уже на месте, просто вызываем логику
    call _find_min_sum_logic
    ret
@find_min_fastcall@8 ENDP

END