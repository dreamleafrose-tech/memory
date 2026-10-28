#include "mmu.h"

MMU::~MMU() {}

bool MMU::inBounds(uint64_t address, size_t length) {
	// virtual address = 0, base_reg = 1024, length = 4096 - always fails with 2048
	// virtual address = 0, base_reg = 2000, length = 400
	// virtual address = 99, base_reg = 0, length = 400, bound_reg = 100
	uint64_t physical_address = translate(address);
	return (physical_address + length) < running_.bound_register;
}

uint64_t MMU::translate(uint64_t virtual_address)
{
	// continguous memory
	//uint64_t physical_address = virtual_address + running_.base_register;
	
	// Paging: on each memory reference, determine the vpn bits
	// and fetch the PTE for that vpn, which holds the pfn for this reference
	// then bring the offset bits through, as-is. Assemble the pfn and offset,
	// return it reference = 0x00f73255
	int vpn = (virtual_address >> 12) & 0x000fffff; // shift based on the page size, 4096B - to obtain the vpn with no offset
	
	PTE pte = page_table.get_entry(vpn);  // get the pte from the page table
	
	int pfn = pte.get_pfn();  // extract the pfn from the pte
	
	uint64_t physical_address = (pfn << 12) | (virtual_address & 0x00000fff);
	
	return physical_address;
}

uint64_t MMU::allocate_page_table() {
	uint64_t ptbr = 0;
	// allocate pages for page table
	return ptbr;
}

uint64_t MMU::allocate(size_t requested)
{
	uint64_t ptbr = allocate_page_table();
}

bool MMU::deallocate_page_table(uint64_t base_address) {
	// deallocate the page table at ptbr
	return true;
}

bool MMU::deallocate(uint64_t base_address)
{
    // update free space tracking and free the memory address space
    bool success = allocator_.free(base_address);
    // free the pages used by the page table
    return allocator_.free(base_address);
}

int MMU::store(uint64_t address, unsigned char byte)
{
	uint64_t physical_address = translate(address);
	ram_.store(physical_address, byte);
	return 0;
}

unsigned char MMU::load(uint64_t address)
{
	uint64_t physical_address = translate(address);
	return ram_.load(physical_address);
}
int MMU::storeString(uint64_t address, std::string s) {
	if (inBounds(address, s.length())) {
		uint64_t physical_address = translate(address);
		for (uint64_t i = 0; i < s.length(); i++)
			ram_.store(physical_address, s[i]);
		return 0;
	}
	return -1;
}
std::string MMU::loadString(uint64_t address) {
	std::string s;
	if (inBounds(address, s.length())) {
		uint64_t physical_address = translate(address);
		for (uint64_t i = 0; i < s.length(); i++)
			s += ram_.load(physical_address+i);
	}
	return s;
}

void MMU::dump()
{
	ram_.dump();
}