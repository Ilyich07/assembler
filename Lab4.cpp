#include <iostream>
#include <iomanip>

int main() {

	double PI;
	int precision = 0;
	int newPrecision = 1;
	int numOfIter = 0;
	double sum = 0;
	int k = 0;
	int ten = 10;
	int eight = 8;
	int intPI;
	int intSum;
	unsigned short controlWord,newControlWord;



	for (numOfIter = 1; numOfIter <= 10000; ++numOfIter) {
		_asm {
			FINIT
			MOV ecx, numOfIter
		cycle :

			MOV k, ecx

			FLD1
			FLD1
			FADD
			FILD dword ptr[k] 
			FMUL
			FLD1
			FSUB // (2*k - 1) 

			FMUL ST(0), ST(0) // // (2*k - 1)^2


			FLD1
			FDIVR // 1 / (2*k - 1)^2

			FADD sum
			FSTP sum

			loop cycle


			FILD eight
			FMUL sum
			FSQRT // итоговое значение числа PI
			FST sum // сохран€ю PI
			FLDPI // загружаю PI
			FST PI // ищу разность



			MOV ecx, newPrecision // дл€ проверки цифр на совпадение пререгон€ю их в целую часть
			FILD ten
		cycle2 :
			FMUL ST(1), ST
			FMUL ST(2), ST
			loop cycle2


			FSTP ST(0) // удал€ю 10 из верхушки стека

			FNSTCW controlWord // настаиваю режим окгруление в меньшую сторону, чтобы избежать ошибки при записи в int 
			MOV ax, 0F3Fh
			MOV newControlWord, ax
			FLDCW newControlWord

			FISTP intPI // записываю целые части в int
			FISTP intSum

			FLDCW controlWord // возвращаю режим округлени€ 

			MOV eax, intPI
			CMP eax, intSum

			JNE _out
			INC precision

		_out:

		}
		if (newPrecision == precision) {

		std::cout << std::setprecision(18) << "Decimal precision: " << newPrecision << '\n';
		std::cout << "Number of iterations: " << numOfIter << '\n';
		std::cout << "The number of PI:  " << PI << '\n';
		std::cout << "The calculated PI: " << sum << '\n';
		std::cout << "----------------------------------" << '\n';
		++newPrecision;
		}
		sum = 0;
		k = 0;
	}

}
