#include "Cache.h"

Cache::Cache(int s, int ls) : size(s), line_size(ls), hits(0), misses(0) {
    num_lines = size / line_size;
}

bool Cache::access(int address) {
    int tag = address / line_size;
    if (cache_map.find(tag) != cache_map.end()) {
        hits++;
        lru_list.erase(cache_map[tag]);
        lru_list.push_front(tag);
        cache_map[tag] = lru_list.begin();
        return true; // Hit
    }

    misses++;
    if (lru_list.size() >= num_lines) {
        int last = lru_list.back();
        lru_list.pop_back();
        cache_map.erase(last);
    }
    lru_list.push_front(tag);
    cache_map[tag] = lru_list.begin();
    return false; // Miss
}

double Cache::get_hit_ratio() {
    if (hits + misses == 0) return 0;
    return (double)hits / (hits + misses);
}