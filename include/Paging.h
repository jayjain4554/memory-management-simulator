#ifndef PAGING_H
#define PAGING_H

#include <unordered_map>

struct PageTableEntry {
    int frame_number;
    bool valid;
};

class PagingSystem {
private:
    int page_size;
    std::unordered_map<int, PageTableEntry> page_table;
    int page_faults;

public:
    PagingSystem(int ps);
    int translate(int virtual_addr); // Returns physical frame or -1 if Page Fault
    void map_page(int page_num, int frame_num);
    int get_page_faults() { return page_faults; }
};

#endif