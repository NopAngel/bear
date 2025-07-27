#include "cache.h"

void cache_flush() {
    asm volatile("wbinvd"); // Flush cache x86
}

void cache_invalidate() {
    asm volatile("invlpg [0]"); // page invalid
}