#include "memory.h"

bool Memory::inBounds(uint64_t address) const
{
	return address < ram_.size();
}

int Memory::store(uint64_t address, unsigned char byte)
{
	if (inBounds(address))
	    ram_[address] = byte;
	else
		throw std::out_of_range("Address out of range");

	return 0;
}

unsigned char Memory::load(uint64_t address) const
{
	if (inBounds(address))
	    return ram_[address];

	// else throw an error or return -1 or something
	return 0x00;
}


uint64_t Memory::size() const {return ram_.size();}

void Memory::clear() { std::fill(ram_.begin(), ram_.end(), 0); }

void Memory::dump()
{
    for (uint64_t i=0; i< ram_.size(); i++)
    {
        // At the start of a 16-byte row, print the memory address offset
        if (i % 16 == 0) {
            if (i > 0) std::cout << std::endl;
            fmt::print("{:04x}: ", i); // 4 digits hex
        }

        fmt::print("{:02x} ", ram_[i]);
    }
    std::cout << std::endl;
}
