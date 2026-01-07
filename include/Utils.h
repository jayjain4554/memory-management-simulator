#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <iomanip>

// This struct acts as a container for your memory statistics [cite: 58, 59]
struct Metrics {
    size_t total_mem;
    size_t used_mem;
    size_t free_mem;
    size_t max_free_block;
    int num_free_blocks;

    void display() {
        // Calculations for utilization and external fragmentation [cite: 57, 61, 63]
        double utilization = (total_mem > 0) ? ((double)used_mem / total_mem) * 100.0 : 0;
        double ext_frag = (free_mem > 0) ? (1.0 - ((double)max_free_block / free_mem)) * 100.0 : 0;

        std::cout << "\n========== STATS ==========" << std::endl;
        std::cout << "Total Memory: " << total_mem << std::endl;
        std::cout << "Used Memory:  " << used_mem << std::endl;
        std::cout << "Free Memory:  " << free_mem << std::endl;
        std::cout << "Utilization:  " << std::fixed << std::setprecision(2) << utilization << "%" << std::endl;
        std::cout << "External Fragmentation: " << ext_frag << "%" << std::endl;
        std::cout << "===========================" << std::endl;
    }
};

#endif