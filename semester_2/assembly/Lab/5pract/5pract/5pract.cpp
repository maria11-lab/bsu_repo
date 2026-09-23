#include <iostream>

int main() {
	int16_t n, counter;
	int32_t x, result;
	std::cout << "Enter number: ";
	std::cin >> n >> x;

	_asm{
		mov si, 1
		mov bx, n
		xor cx, cx
	n1:
		test bx, si
		jz n2
		inc cx
	n2:
		shl si,1
		cmp si, 0 
		jnz n1

		mov counter, cx  
	}
	std::cout << "Num of 1: " << counter;
	_asm{
		mov eax, x         
		mov ebx, eax        
		shl eax, 4          
		sub eax, ebx        
		mov result, eax
	}
	std::cout << "\nX*15 = " << result;
	return 0;
}