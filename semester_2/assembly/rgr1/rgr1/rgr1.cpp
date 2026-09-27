#include <iostream>
int main() {
    int32_t n;
    int res, count = 0;
    std::cout << "Enter a num:  ";
    std::cin >> n;

    _asm {
        mov eax, n
        mov esi, 2
        check_two:
            mov ebx, eax
            and ebx, 1
            jnz odd_factors
            xor edx, edx
            div esi
            push esi
            inc count
            jmp check_two
        odd_factors :
            mov esi, 3
        n1 :
            cmp eax, 1
            jz end_asm
            xor edx, edx
            mov ecx, eax
            div esi
            cmp edx, 0
            jnz n2
            push esi
            inc count
            jmp n1
        n2 :
            mov eax, ecx
            add esi, 2
            jmp n1
        end_asm :
    }
    std::cout << "Result: ";
    for (size_t i = 0; i < count; ++i) {
        _asm { pop res }
        std::cout << res << " ";
    }

    return 0;
}  
