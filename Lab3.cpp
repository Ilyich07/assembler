#include <iostream>

// 50 = 2*x + 3*y

int main() {
	int x = 0;
	int y = 0;
	int numOfRoots = 0;
	int roots[20];


		_asm {
		cycle_x :
			inc x
			mov y, 0
			mov eax, 2
			mul x
			mov ebx, eax
			cmp ebx, 50
			jl cycle_y
			jmp _out

		cycle_y :
			inc y
			mov eax, 3
			mul y
			add eax, ebx
			cmp eax, 50
			jg cycle_x
			jl cycle_y

			mov eax, numOfRoots
			mov ebx, x
			mov roots[8*eax], ebx
			mov ebx, y
			mov roots[8*eax + 4], ebx
			inc numOfRoots
			jmp cycle_x

		_out:
		}
		for (int i = 0; i < 2*numOfRoots; ++i) {
			std::cout << "2 * " << roots[i] << " + 3 * " << roots[i + 1] << " = " << 2 * x + 3 * y << '\n';
			++i;
		}
		std::cout << "The number of roots: " << numOfRoots << '\n';



	int num, den;
	std::cout << "Enter an integer numerator: ";
	std::cin >> num;
	std::cout << "Enter the natural denominator: ";
	std::cin >> den;

	_asm {
		mov eax, num
		cmp eax, 0
		jg possitive
		neg eax

	possitive :
		mov ebx, den

	cycle :
		cmp eax, ebx
		jg greater
		jl lower
		je nod

	lower :
		sub ebx, eax
		jmp cycle

	greater :
		sub eax, ebx
		jmp cycle

	nod :
		mov eax, num
		cdq
		idiv ebx
		mov num, eax
		mov eax, den
		cdq
		div ebx
		mov den, eax

	}
	std::cout << " Reduced fraction: " << num << "/" << den;
}


