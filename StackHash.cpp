#include "StackHash.h"

#ifdef DEBUG
HASH StackGetStructHash(Stack *stk, uint64_t seed){

    HASH backup = stk->structhash;
    stk->structhash = 0;

    HASH hash = HashNoCommutate(stk, sizeof(Stack), seed, 
        0xDEADFALL, 0xc945225, 0x5);

    stk->structhash = backup;
    return hash;
}

HASH StackGetDataHash(Stack *stk, uint64_t seed){
    return (stk->data == NULL) ? 0 :
        HashNoCommutate(stk->data, stk->capaticy * sizeof(Elem_t) + 2 * sizeof(Calibri), seed,
            0xF00, 0xc2b2ae35, 0x9);
}

bool StackCmpStructHash(Stack *stk, uint64_t seed){
    HASH hash_from_stk = stk->structhash;
    HASH hach_real_stk = StackGetStructHash(stk, seed);
    return hash_from_stk == hach_real_stk;
}

bool StackCmpDataHash  (Stack *stk, uint64_t seed){
    HASH hash_from_stk = stk->datahash;
    HASH hach_real_stk = StackGetDataHash(stk, seed);
    return hash_from_stk == hach_real_stk;
}

#endif