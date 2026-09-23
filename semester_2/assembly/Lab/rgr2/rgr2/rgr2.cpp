#include<iostream>

int main() {
	int a[]{ -1,-1,-1,-1 };
	int n= sizeof(a) / sizeof(int), d;
	std::cout << "old arr: ";
	for (size_t i = 0; i < n; ++i) {
		std::cout << a[i] << ' ';
	}
	std::cout << '\n';
	_asm {
		lea ebx, a
		mov eax, [ebx]
		mov ecx, n
		xor esi, esi
	find_min:
		inc esi
		cmp esi, ecx
		jz start_skip_min
		mov edx, [ebx + esi * 4]
		cmp eax, edx
		jl find_min
		mov eax, edx
		jmp find_min
	start_skip_min:
		xor esi, esi
		xor edi, edi
	cucle_skip_min:
		cmp esi, ecx
		jz fill_zero
		mov edx, [ebx + esi * 4]
		cmp eax, edx
		jz skip
		mov[ebx + edi * 4], edx
		inc edi
	skip:
		inc esi
		jmp cucle_skip_min
	fill_zero:
		cmp edi, ecx
		jz exit1
		mov dword ptr [ebx + edi * 4], 0 
		inc edi
		jmp fill_zero
	exit1 :
		mov d, eax
	}
	std::cout << "min: " << d << "\nnew arr: ";
	for (size_t i = 0; i < n; ++i) {
		std::cout << a[i] << ' ';
	}
	return 0;
}