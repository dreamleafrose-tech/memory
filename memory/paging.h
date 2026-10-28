#ifndef _PAGING_H
#define _PAGING_H

#include <cstdint>
#include <vector>

// typedef uint32_t pte;
/*struct PTE {
     uint32_t entry;

};*/

const uint32_t PRESENT_MASK = 0x0002;
const uint32_t DIRTY_MASK = 0x0004;
class PTE {
     private:
          uint32_t entry; // 20 bits of vpn, 12 bits offset
     public:
          PTE();
          int get_pfn();
          bool get_dirty();
          bool get_present();
};

class pageTable {
     private:
          std::vector<PTE> table_;
     public:
          pageTable();
          PTE get_entry(int vpn);
          void set_entry(int vpn, PTE pte);
};
#endif