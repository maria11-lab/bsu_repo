#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, ".1251");
	char x1, y1, y11;
	short pr1;
	short x2, y2, pr2;
	int x3, y3, pr3;
	cout << "введите два числа длиною в байт" << endl;
	//cin >> x1 >> y1; //так нельзя ввести байты, будут коды символов
	cin >> x2 >> y2; //вводим в поля длиною short
	x1 = x2; // копируем
	y1 = y2;
	//сумма двух чисел типа byte
	//если уверены, что результат поместится в байт
	_asm {
		mov al, x1
		add al, y1
		cbw
		mov pr1, ax
	}
	cout << pr1 << endl;

	//если не уверены, что результат поместится в байт
	_asm {
		mov al,x1
		cbw
		mov pr1,ax
		mov al,y1
		cbw
		add pr1,ax
	}
	cout<<pr1<<endl;
	//произведение двух чисел типа byte
	_asm {
		mov al,x1
		imul y1
		mov pr1,ax
	}
	cout<<pr1<<endl;

	//произведение двух чисел типа short
	//если результат умещается в слово
	cout << "введите два числа длиною в слово" << endl;
	cin >> x2 >> y2;
	_asm {
		mov ax,x2
		imul y2
		mov pr2,ax
	}
	cout<<pr2<<endl;
	//произведение двух чисел типа short
	//если результат не умещается в слово
	_asm {
		mov ax,x2
		imul y2
		mov pr2,ax
		mov word ptr pr3,ax
		mov word ptr pr3+2,dx
	}
	cout<<pr3<<endl;

	//произведение двух чисел типа int
	//если результат умещается в int
	cout << "введите два числа int длиною в 4 байта" << endl;
	cin >> x3 >> y3;
	_asm {
		mov eax,x3
		imul y3
		mov pr3,eax
	}
	cout<<pr3<<endl;
}