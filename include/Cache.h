#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <list>
#include <unordered_map>

struct CacheLine {
    int tag;
    bool valid;
};

class Cache {
private:
    int size;
    int line_size;
    int num_lines;
    std::list<int> lru_list; // Tracks access order for LRU
    std::unordered_map<int, std::list<int>::iterator> cache_map;
    int hits;
    int misses;

public:
    Cache(int s, int ls);
    bool access(int address); // Returns true on Hit, false on Miss
    double get_hit_ratio();
    int get_hits() { return hits; }
    int get_misses() { return misses; }
};

#endif