#ifndef STACK_PROTECT_H
#define STACK_PROTECT_H

#include <stdint.h>
#include "Hash.h"

#include "Stack.h"
#include "StackStruct.h"
#include "config.h"

HASH StackGetStructHash     (Stack *stk, uint64_t seed = 5461216);
HASH StackGetDataHash       (Stack *stk, uint64_t seed = 5461216);
bool StackCmpStructHash     (Stack *stk, uint64_t seed = 5461216);
bool StackCmpDataHash       (Stack *stk, uint64_t seed = 5461216);

bool StackCmpStructCalibri  (Stack* stk);
bool StackCmpDataCalibri    (Stack* stk);

#endif // !STACK_PROTECT