#ifndef _MMU_H
#define _MMU_H

#include <cstdint>
#include <vector>

#include "memory.h"
#include "allocator.h"

// contiguous memory process
/*struct Process {
	uint64_t base_register;
	uint64_t bound_register;
};*/

struct Process {
	uint64_t page_table_base_register; // a phyiscal address
	//std::vector<Page> page_table;
};

class MMU
{
  private:
	// std::vector<uint64_t> physical_addresses;
	// std::vector<uint64_t> virtual_addresses;
	Memory ram_;
	uint64_t memory_size_;
	uint64_t page_size_;
	// compute page size bits
	int offset_bits = 12;
	int vpn_bits = 20;

	Process running_;
	FreeListAllocator allocator_; // normally in the kernel, not the MMU
	
	pageTable page_table;
	/**
	 * @brief bounds checking the allocation using base and bound registers
	 * 
	 * @param address
	 * @param length
	 * @return true 
	 * @return false 
	 */
	bool inBounds(uint64_t address, size_t length);

  public:
   	MMU(): ram_(Memory(DEFAULT_MEMORY_SIZE)), memory_size_(DEFAULT_MEMORY_SIZE) {};

    MMU(uint64_t memory_size, uint64_t page_size): ram_(Memory(memory_size)), memory_size_(memory_size), page_size_(page_size) {};
	~MMU();

    /**
     * @brief translate a virtual to physical address
     *
     * @param virtual_address
     * @return uint64_t physical_address
     */
    uint64_t translate(uint64_t virtual_address);
    
	/**
	* @brief load a process
	* 
	* @param Process to load and "run"
	*/ 
	void setRegisters(Process& p) {
		running_ = p;
	}

	Process getRegisters() {
		return running_;
	}
	/**
	 * @brief allocate pages for a process' page table
	 *
	 * Assume, for now, allocation of `requested`
	 * always succeeds
	 *
	 * @return uint64_t base address
	 */
	uint64_t allocate_page_table();

	/**
	 * @brief allocate memory address space
	 *
	 * Assume, for now, allocation of `requested`
	 * always succeeds
	 *
	 * @param requested address space size
	 * @return uint64_t base address
	 */
	uint64_t allocate(size_t requested);

	/**
	 * @brief free pages used to hold the process' page table
	 *
	 * Assume allocate always works and that
	 * deallocate will too
	 *
	 * @param base_address
	 * @param requested size from allocate()
	 */
	bool deallocate_page_table(uint64_t base_address);
	
	/**
	 * @brief free allocated memory
	 *
	 * Assume allocate always works and that
	 * deallocate will too
	 *
	 * @param base_address
	 * @param requested size from allocate()
	 */
	bool deallocate(uint64_t base_address);

	/**
	* @brief store data to memory
	*
	* This function stores a single byte to the specified address
	*
	* @param address The location to which the byte will be stored
	* @param byte the byte to store
	*/
	int store(uint64_t address, unsigned char byte);

	/**
	* @brief load data from memory
	*
	* This function loads a single byte from the specified address
	*
	* @param address The location from which the byte will be read
	* @return the byte read from memory
	*/
	unsigned char load(uint64_t address);

	int storeString(uint64_t address, std::string s);
	std::string loadString(uint64_t address);
	/**
	 * @brief dump memory in hex for inspection
	 *
	 */
	void dump();
	
	// pass through to allocator
	uint64_t freeMemory() const { return allocator_.getFreeMemory(); }
	void printFreeList() const { allocator_.printFreeList(); }

	// and maybe this week, pages!
};

#endif
