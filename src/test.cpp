#include <iostream>

#include "ViewModel/HsCalcStateWrapper.hpp"

int main(int argc, char *argv[]) {
	std::ios_base::sync_with_stdio(false);

	HsCalcStateWrapper wrapper(Dyadic);
	std::cout << wrapper.execCommand("sin pi", 20);
	std::cout << wrapper.reevalCommand(100);

	return 0; // and here, the destructor automatically runs
}
