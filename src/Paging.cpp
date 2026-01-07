#include "Paging.h"

PagingSystem::PagingSystem(int ps) : page_size(ps), page_faults(0) {}

int PagingSystem::translate(int virtual_addr) {
    int page_num = virtual_addr / page_size;
    int offset = virtual_addr % page_size;

    if (page_table.find(page_num) != page_table.end() && page_table[page_num].valid) {
        return (page_table[page_num].frame_number * page_size) + offset;
    }

    page_faults++;
    return -1; // Page Fault [cite: 108]
}

void PagingSystem::map_page(int page_num, int frame_num) {
    page_table[page_num] = {frame_num, true};
}