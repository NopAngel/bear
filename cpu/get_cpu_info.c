/*
*
*   get_cpu_info.c - obtain cpu info
*
*  (C) 2025 Angel Nieto/NopAngel <angelnieto1402@gmail.com>
*
*           This code is licenced under the APACHE 2.0
*/


unsigned int get_cpu_cycles() {
    unsigned int low, high;
    __asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high));
    return low;
}