#ifndef STACK_HASH_H
#define STACK_HASH_H

#include <stdint.h>

#include "Stack.h"
#include "StackStruct.h"
#include "Hash.h"

#include "config.h"

#ifdef USE_HASH
HASH StackGetStructHash     (Stack *stk, uint64_t seed = 5461216);
HASH StackGetDataHash       (Stack *stk, uint64_t seed = 5461216);
bool StackCmpStructHash     (Stack *stk, uint64_t seed = 5461216);
bool StackCmpDataHash       (Stack *stk, uint64_t seed = 5461216);
#endif // !DEBUG

#endif // !STACK_HASH