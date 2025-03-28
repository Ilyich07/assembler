#include <iostream>
#include <string>
#include <cstdint>
#include <iomanip>
#include <bitset>

int main() {
	uint16_t A1, A2;
	_int16 A3;
	uint16_t B1, B2;
	_int16 B3, C3;
	uint16_t C1, C2;

	std::cout << "Input A1, A2, A3" << std::endl;
	std::cin >> A1 >> A2 >> A3;
	std::cout << "Input B1, B2, B3" << std::endl;
	std::cin >> B1 >> B2 >> B3;
	
	_asm {
		mov ax, A1
		add ax, B1
		mov C1, ax

		jnc no_first_carry
		mov ax, A2
		inc ax
		mov A2, ax

		jnc no_first_carry
		mov ax, A3
		inc ax
		mov A3, ax

	no_first_carry:
		mov ax, A2
		add ax, B2
		mov C2, ax

		jnc no_second_carry
		mov ax, A3
		inc ax
		mov A3, ax

	no_second_carry:
		mov ax, A3
		add ax, B3
		mov C3, ax
	}

	std::cout << std::hex << std::setfill('0') << std::setw(4) << C3 << ' ';
	std::cout << std::setfill('0') << std::setw(4) << C2 << ' ';
	std::cout << std::setfill('0') << std::setw(4) << C1 << std::endl;

	std::cout << std::bitset<16>(C3) << ' ';
	std::cout << std::bitset<16>(C2) << ' ';
	std::cout << std::bitset<16>(C1);
	
}
