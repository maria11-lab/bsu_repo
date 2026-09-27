#include <iostream>

extern "C" int __stdcall RemoveMin1(int* arr, int n);
extern "C" int __cdecl RemoveMin2(int* arr, int n);
extern "C" int __fastcall RemoveMin3(int* arr, int n);

int main() {
    int a1[] = {1, -1, -1, 5};
    int a2[] = {10, 2, 8, 2};
    int a3[] = {3, 3, 3, 3};

    int n1 = sizeof(a1) / sizeof(int);
    int n2 = sizeof(a2) / sizeof(int);
    int n3 = sizeof(a3) / sizeof(int);


    std::cout << "Old arrays: ";
    std::cout << "\n\n";
    for (size_t i = 0; i < n1; ++i) {
        std::cout << a1[i] << ' ';
    }
    std::cout << '\n';
    for (size_t i = 0; i < n2; ++i) {
        std::cout << a2[i] << ' ';
    }
    std::cout << '\n';
    for (size_t i = 0; i < n3; ++i) {
        std::cout << a3[i] << ' ';
    }
    std::cout << "\n\n";

    RemoveMin1(a1,n1);
    RemoveMin1(a2,n2);
    RemoveMin1(a3,n3);

    std::cout << "New arrays: \n\n";

    for (size_t i = 0; i < n1; ++i) {
        std::cout << a1[i] << ' ';
    }
    std::cout << '\n';
    for (size_t i = 0; i < n2; ++i) {
        std::cout << a2[i] << ' ';
    }
    std::cout << '\n';
    for (size_t i = 0; i < n3; ++i) {
        std::cout << a3[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}