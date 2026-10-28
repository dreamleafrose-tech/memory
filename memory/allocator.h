// This class does NOT own or create any memory. It only keeps track of which
// addresses in a region [base, base + size) are free and which are handed out.
// Your memory object (from the other class) owns the actual storage; use the
// addresses returned here to index into it.
//

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#pragma pack(1)
#include <cstdint>

class FreeListAllocator {
private:
    struct Impl;
    Impl* impl;

public:
    enum Policy { FIRST_FIT, BEST_FIT, WORST_FIT };

    // Returned by allocate() when the request cannot be satisfied.
    static const int FAILED;

    // Manage the region of addresses [base, base + size]. All of it starts free.
	FreeListAllocator() {}
    FreeListAllocator(uint64_t base, uint64_t size, Policy policy = FIRST_FIT);
    ~FreeListAllocator();

    FreeListAllocator(const FreeListAllocator&) = delete;
    FreeListAllocator& operator=(const FreeListAllocator&) = delete;

	/**
	 * @brief Reserve a block of blockSize
	 *
	 * @param blockSize the starting address
	 * @return uint32_t or FreeListAllocator::FAILED if no single free block is large enough
	 */
    uint64_t allocate(uint64_t blockSize);

	/**
	 * @brief Release the block previously returned by allocate() at this address.
	 *
	 * The allocator remembers each block's size. Returns false (and prints an
	 * error) if the address was never allocated or was already freed.
	 *
	 * @param address
	 * @return true
	 * @return false
	 */
    bool free(uint64_t address);

    /**
     * @brief Total number of free blocks (not necessarily contiguous!).
     *
     * @return uint32_t
     */
    uint64_t getFreeMemory() const;

	/**
	 * @brief Print each free block as [start, end] in address order.
	 *
	 */
	void printFreeList() const;

};

#endif
