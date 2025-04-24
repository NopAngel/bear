unsigned int get_cpu_cycles() {
    unsigned int low, high;
    __asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high));
    return low;
}