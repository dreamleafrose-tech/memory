#include "paging.h"

int PTE::get_pfn() {
     return entry >> 12;
}
bool PTE::get_dirty() {
     return (entry & DIRTY_MASK) >> 4;
}

bool PTE::get_present() {
     return (entry & PRESENT_MASK) >> 2;
}

PTE pageTable::get_entry(int vpn) {
     return table_[vpn];
}
void pageTable::set_entry(int vpn, PTE pte) {
     table_[vpn] = pte;
}