// Free list is a singly linked list kept sorted by address.
// Allocation sizes are tracked in a side table, standing in for the
// per-block header a real allocator would store in memory.

#include "allocator.h"

#include <iostream>
#include <map>

const int FreeListAllocator::FAILED = -1;

struct FreeListAllocator::Impl {
    struct Block {
        uint64_t start;
        uint64_t size;
        Block* next;
    };

    Block* freeList;
    std::map<uint64_t, uint64_t> allocated;  // address -> size
    Policy policy;
};

FreeListAllocator::FreeListAllocator(uint64_t base, uint64_t size, Policy policy)
    : impl(new Impl) {
    impl->policy = policy;
    impl->freeList = (size > 0) ? new Impl::Block{base, size, nullptr} : nullptr;
}

FreeListAllocator::~FreeListAllocator() {
    Impl::Block* current = impl->freeList;
    while (current != nullptr) {
        Impl::Block* next = current->next;
        delete current;
        current = next;
    }
    delete impl;
}

uint64_t FreeListAllocator::allocate(uint64_t blockSize) {
    if (blockSize == 0) return FAILED;

    Impl::Block* best = nullptr;
    Impl::Block* bestPrev = nullptr;
    Impl::Block* prev = nullptr;

    for (Impl::Block* cur = impl->freeList; cur != nullptr; prev = cur, cur = cur->next) {
        if (cur->size < blockSize) continue;

        bool take = false;
        if (best == nullptr) take = true;
        else if (impl->policy == BEST_FIT && cur->size < best->size) take = true;
        else if (impl->policy == WORST_FIT && cur->size > best->size) take = true;

        if (take) {
            best = cur;
            bestPrev = prev;
        }
        if (impl->policy == FIRST_FIT) break;
    }

    if (best == nullptr) return FAILED;

    uint64_t address = best->start;
    if (best->size == blockSize) {
        // Exact fit: remove the block from the free list entirely.
        if (bestPrev) bestPrev->next = best->next;
        else impl->freeList = best->next;
        delete best;
    } else {
        // Carve the allocation off the front of the block.
        best->start += blockSize;
        best->size -= blockSize;
    }

    impl->allocated[address] = blockSize;
    return address;
}

bool FreeListAllocator::free(uint64_t address) {
    auto it = impl->allocated.find(address);
    if (it == impl->allocated.end()) {
        std::cerr << "free: address " << address
                  << " is not an allocated block (bad address or double free)" << std::endl;
        return false;
    }
    uint64_t size = it->second;
    impl->allocated.erase(it);

    // Find where this block belongs in the address-ordered list.
    Impl::Block* prev = nullptr;
    Impl::Block* next = impl->freeList;
    while (next != nullptr && next->start < address) {
        prev = next;
        next = next->next;
    }

    bool mergePrev = prev != nullptr && prev->start + prev->size == address;
    bool mergeNext = next != nullptr && address + size == next->start;

    if (mergePrev && mergeNext) {
        prev->size += size + next->size;
        prev->next = next->next;
        delete next;
    } else if (mergePrev) {
        prev->size += size;
    } else if (mergeNext) {
        next->start = address;
        next->size += size;
    } else {
        Impl::Block* node = new Impl::Block{address, size, next};
        if (prev) prev->next = node;
        else impl->freeList = node;
    }
    return true;
}

uint64_t FreeListAllocator::getFreeMemory() const {
    uint64_t total = 0;
    for (Impl::Block* cur = impl->freeList; cur != nullptr; cur = cur->next)
        total += cur->size;
    return total;
}

void FreeListAllocator::printFreeList() const {
    if (impl->freeList == nullptr) {
        std::cout << "Free list: (empty)" << std::endl;
        return;
    }
    for (Impl::Block* cur = impl->freeList; cur != nullptr; cur = cur->next) {
        std::cout << "Free Block: [" << cur->start << ", "
                  << (cur->start + cur->size) << "]  size " << cur->size << std::endl;
    }
}
