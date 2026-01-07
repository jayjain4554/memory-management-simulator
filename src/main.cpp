#include "MemoryManager.h"
#include "Cache.h"
#include "Paging.h"
#include <iostream>
#include <string>
#include <sstream>

int main() {
    MemoryManager* mm = nullptr;
    Cache* l1 = new Cache(128, 16);    // L1 Cache
    PagingSystem* vm = new PagingSystem(64); // Page size 64
    
    std::string line, cmd;
    std::string current_strategy = "first_fit";

    std::cout << "Memory Simulator Ready. Use 'init memory 1024' to start.\n";

    while (std::cout << "> " && std::getline(std::cin, line)) {
        if (line == "exit") break;
        std::stringstream ss(line);
        ss >> cmd;

        if (cmd == "init") {
            std::string sub; size_t size;
            ss >> sub >> size;
            if (mm) delete mm;
            mm = new MemoryManager(size);
            std::cout << "Initialized " << size << " bytes of physical memory.\n";
        } 
        else if (cmd == "set") {
            std::string sub, s1, s2;
            ss >> sub >> s1 >> s2;
            current_strategy = s1 + "_" + s2; // e.g., "first_fit"
            std::cout << "Strategy: " << current_strategy << "\n";
        }
        else if (cmd == "malloc") {
            if (!mm) { std::cout << "Init memory first!\n"; continue; }
            size_t size; ss >> size;
            static int pid_gen = 1;
            int addr = mm->allocate(pid_gen++, size, current_strategy);
            if (addr != -1) std::cout << "Allocated at address: " << addr << "\n";
            else std::cout << "Out of memory!\n";
        }
        else if (cmd == "stats") {
            if (mm) mm->print_stats();
            std::cout << "Cache Hit Ratio: " << l1->get_hit_ratio() * 100 << "%\n";
            std::cout << "Page Faults: " << vm->get_page_faults() << "\n";
        }
        else if (cmd == "dump") {
            if (mm) mm->dump_memory();
        }
        else if (cmd == "access") {
            int v_addr; 
            ss >> v_addr;

            // 1. Virtual Address -> Physical Address (Paging)
            int p_addr = vm->translate(v_addr);
            if (p_addr == -1) {
                std::cout << "[Page Fault] Mapping virtual page to frame...\n";
                // Map virtual page to a frame (simplified for simulation)
                vm->map_page(v_addr / 64, (v_addr / 64) % 16);
                p_addr = vm->translate(v_addr);
            }

            // 2. Check Cache
            if (l1->access(p_addr)) {
                std::cout << "L1 Cache Hit! Physical Address: " << p_addr << "\n";
            } else {
                std::cout << "L1 Cache Miss. Accessing RAM at: " << p_addr << "\n";
            }
        }
        else if (cmd == "free") {
            int pid;
            if (ss >> pid) {
                mm->deallocate(pid);
            } else {
                std::cout << "Usage: free <id>\n";
            }
        }
    }
    delete mm; delete l1; delete vm;
    return 0;
}