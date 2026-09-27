#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

extern "C" int __stdcall task1(int index, int size, int* arr);
extern "C" int __fastcall task3(int index, int size, int* arr);
extern "C" int __cdecl task2(int index, int size, int* arr);
using namespace std;


void printMatrix(int* matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(4) << matrix[i * n + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    const int n = 5;
    int matrix[n][n];

    srand((int)time(NULL));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10 + 10;
        }
    }

    int targetIndex = rand() % n;

    printMatrix((int*)matrix, n);

    int* mAddr = &matrix[0][0];

    task1(targetIndex, n, mAddr);

    printMatrix((int*)matrix, n);

    const int m = 3;
    int arr[m][m];
    int index = rand() % m;
    
    for (size_t i = 0;i < m;++i) {
        for (size_t j = 0;j < m;++j) {
            arr[i][j] = rand() % 10;
        }
    }

    printMatrix((int*)arr, m);

    task3(index, m, (int*)arr);

    printMatrix((int*)arr, m);

	const int d = 9, v = sqrt(d);
    int* b = new int[9];

    for (int i = 0; i < d; i++) {
        b[i] = rand() % 10 + 10;

    }
    printMatrix(b, v);

    task2(index, v, b);

    printMatrix(b, v);


    int q = 0, w = 0, e = 0, r = 0;


    _asm{
        mov eax, b
        mov ecx, [b]
        mov ebx, [eax]
        mov edx, [ecx]
	mov q, eax
    mov w, ecx
    mov e, ebx
    mov r, edx
    }

    std::cout << q << ' ' << w << ' ' << e << ' ' << r;


    return 0;
}



//std::srand(std::time(NULL));
// a[i][j]=std::rand()%10+5;


//.386
//.model flat
//Public _task@12

//.code

//_task@12 proc
//...
//_task@12 endp

//end