#include <iostream>
#include "mmu.h"

int main( [[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	MMU mmu(41'943'040, 4'096); // 10,240 pages available

	// allocate a
	// set some data
	// retrieve data
	// deallocate a

	mmu.dump();
	/*const size_t a_size = 100, b_size = 100;
	
	uint64_t a_base = mmu.allocate(a_size);
	uint64_t b_base = mmu.allocate(b_size);
	
	if (a_base < 0 || b_base < 0) {
		std::cerr << "allocation failed" << std::endl;
		return EXIT_FAILURE;
	}
	Process a = {
		.base_register = a_base,
		.bound_register = a_base + a_size
	};
	Process b = {
		.base_register = b_base,
		.bound_register = b_base + b_size
	};

	mmu.printFreeList();
	mmu.deallocate(a.base_register);
	mmu.deallocate(b.base_register);
	mmu.printFreeList(); // one hole of 2048 again
	*/
	/*uint64_t address = 4;
	unsigned char data = 'A';
	std::string a_data = "Hello, Alice";
	int status = mmu.storeString(address, a_data);
	if (status < 0) { std::cerr << "future error info" << std::endl; }

	std::string x = mmu.loadString(address);
	std::cout << "Read from location "<< address << ": " << x << std::endl;*/

    return EXIT_SUCCESS;
}
