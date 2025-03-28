
#include <iostream>


int main() {
	int x, res, res_c;
	std::cout << "Input x: ";
	std::cin >> x;

	_asm {
		mov eax, 4
		imul x
		dec eax
		mov res, eax

		mov eax, 4
		imul x
		inc eax
		imul res
		cdq

		mov ebx, 4
		idiv ebx
		mov res, eax
	}

	res_c = (4 * x - 1) * (4 * x + 1) / 4;
	std::cout << "The result calculated in assembler: " << res << '\n';
	std::cout << "The result calculated in C: " << res_c << '\n' << '\n';




	int num;
	int numOfDigits = 0;
	std::cout << "Input number: ";
	std::cin >> num;

	_asm {
		mov eax, num
		mov ebx, 10
	cycle1:
		inc numOfDigits
		cdq
		idiv ebx
		cmp eax, 0
		jne cycle1
	
		mov ecx, numOfDigits
		mov eax, 1
	cycle2:
		imul ebx
		loop cycle2

		add eax, num
		imul ebx
		inc eax
		mov num, eax

	}
	std::cout << "New number: " << num;

}
