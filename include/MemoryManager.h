#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <list>
#include <string>
#include "Utils.h"
#include <map>
#include <cmath>
#include <algorithm>

struct Block {
    int id;             // -1 if free [cite: 28]
    size_t start_addr;
    size_t size;
    bool is_free;

    Block(int i, size_t addr, size_t s, bool free) 
        : id(i), start_addr(addr), size(s), is_free(free) {}
};

class MemoryManager {
private:
    size_t total_capacity;
    std::list<Block> memory_list; // Linked list to track blocks [cite: 176]

public:
    MemoryManager(size_t size);
    int allocate(int process_id, size_t size, std::string strategy); // First, Best, Worst Fit [cite: 21]
    void deallocate(int process_id);
    void coalesce();    // Merges adjacent free blocks [cite: 32, 178]
    void dump_memory(); // Shows the visual map [cite: 37, 50]
    void print_stats(); // Reports fragmentation [cite: 40, 54]
};

#endif