#ifndef HASH_H
#define HASH_H

#include <stddef.h>

unsigned long long HashNoCommutate( const void* ptr, size_t ptr_size_bytes, size_t seed,
                                    size_t coefficient1, size_t coefficient2, size_t coefficient3);

#endif // !HASH_H