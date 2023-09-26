#include "Hash.h"
unsigned long long HashNoCommutate(const void* ptr, size_t ptr_size_bytes, size_t seed,
    size_t coefficient1, size_t coefficient2, size_t coefficient3)
{
    unsigned long long hash = seed;
    const char* byte = (const char*)ptr;

    for(size_t pos = 0; pos < ptr_size_bytes; pos++){
        hash += ((unsigned long long)byte[pos] * coefficient1);
        hash *= coefficient2;
        hash ^= hash >> coefficient3;
    }
    return hash % seed;
}