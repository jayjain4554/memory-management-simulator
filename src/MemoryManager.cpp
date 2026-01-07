#include "MemoryManager.h"
#include "Utils.h"
#include <iomanip>

MemoryManager::MemoryManager(size_t size) : total_capacity(size) {
    // Initialize with one large free block
    memory_list.push_back(Block(-1, 0, size, true));
}

int MemoryManager::allocate(int process_id, size_t size, std::string strategy) {
    auto best_it = memory_list.end();

    for (auto it = memory_list.begin(); it != memory_list.end(); ++it) {
        if (it->is_free && it->size >= size) {
            if (strategy == "first_fit") {
                best_it = it;
                break; // Stop at the very first suitable block [cite: 22]
            } else if (strategy == "best_fit") {
                // Find the smallest block that fits to minimize wasted space [cite: 23]
                if (best_it == memory_list.end() || it->size < best_it->size) {
                    best_it = it;
                }
            } else if (strategy == "worst_fit") {
                // Find the largest block to leave the largest possible remainder [cite: 24]
                if (best_it == memory_list.end() || it->size > best_it->size) {
                    best_it = it;
                }
            }
        }
    }

    if (best_it != memory_list.end()) {
        size_t remaining_size = best_it->size - size;
        
        best_it->is_free = false;
        best_it->id = process_id;
        best_it->size = size;

        // Split the block if there is leftover space [cite: 27]
        if (remaining_size > 0) {
            memory_list.insert(std::next(best_it), 
                Block(-1, best_it->start_addr + size, remaining_size, true));
        }
        return best_it->start_addr;
    }
    
    return -1; // Allocation failed [cite: 62]
}

void MemoryManager::deallocate(int process_id) {
    bool found = false;
    for (auto& block : memory_list) {
        if (!block.is_free && block.id == process_id) {
            block.is_free = true;
            block.id = -1; // Important: Reset ID to -1
            found = true;
            std::cout << "Successfully deallocated ID: " << process_id << "\n";
        }
    }
    if (found) {
        coalesce(); 
    } else {
        std::cout << "Error: Process ID " << process_id << " not found.\n";
    }
}

void MemoryManager::coalesce() {
    auto it = memory_list.begin();
    while (it != memory_list.end() && std::next(it) != memory_list.end()) {
        auto next_it = std::next(it);
        if (it->is_free && next_it->is_free) {
            it->size += next_it->size;
            memory_list.erase(next_it); // Merge current and next [cite: 32]
        } else {
            ++it;
        }
    }
}

void MemoryManager::dump_memory() {
    std::cout << "\n--- Memory Visualization ---" << std::endl;
    for (const auto& b : memory_list) {
        std::cout << "[0x" << std::hex << std::setw(4) << std::setfill('0') << b.start_addr 
                  << " - 0x" << std::setw(4) << (b.start_addr + b.size - 1) << "] "
                  << (b.is_free ? "FREE" : "USED (id=" + std::to_string(b.id) + ")") 
                  << std::dec << " Size: " << b.size << std::endl;
    }
}

void MemoryManager::print_stats() {
    Metrics m;
    m.total_mem = total_capacity;
    m.used_mem = 0;
    m.free_mem = 0;
    m.max_free_block = 0;
    m.num_free_blocks = 0;

    for (const auto& b : memory_list) {
        if (!b.is_free) {
            m.used_mem += b.size;
        } else {
            m.free_mem += b.size;
            m.num_free_blocks++;
            if (b.size > m.max_free_block) m.max_free_block = b.size;
        }
    }
    m.display(); // Calls the helper in Utils.h [cite: 132]
}

