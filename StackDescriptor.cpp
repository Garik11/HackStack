#include "StackDescriptor.h"

static Stack*       DESCRIPTORS[MAX_DESCRIPTORS_SIZE] = {};
static const size_t DESCRIPTOR_NULL = (size_t)-1;
static size_t       DESCRIPTORS_SIZE = DESCRIPTOR_NULL;

void DESCRIPTORINIT();

void DESCRIPTORINIT(){
    memset(DESCRIPTORS, 0, sizeof(Stack*) * MAX_DESCRIPTORS_SIZE);
    DESCRIPTORS_SIZE = 0;
}

void DESCRIPTORADD  (Stack* stk, StackErrorsBitmask *err_ret){
    if(DESCRIPTORS_SIZE == DESCRIPTOR_NULL)
        DESCRIPTORINIT();
    bool STATUS = false;
    for(size_t pos = 0; pos < MAX_DESCRIPTORS_SIZE; pos++)
        if(DESCRIPTORS[pos] == NULL){
            DESCRIPTORS[pos] = stk;
            STATUS = true;
            DESCRIPTORS_SIZE++;
            break;
        }
    if(STATUS == false){
        *err_ret |= STACK_DESCRIPTOR_NOT_ADDED;
        return;
    }
}

void DESCRIPTORDEC  (Stack* stk, StackErrorsBitmask *err_ret){
    bool STATUS = false;
    for(size_t pos = 0; pos < DESCRIPTORS_SIZE; pos++){
        if(DESCRIPTORS[pos] == stk)
        {
            STATUS = true;
            DESCRIPTORS[pos] = NULL;
            break;;
        }
    }
    if(STATUS == false){
        *err_ret |= STACK_DESCRIPTOR_NOT_DELETED;
        return;
    }
}

bool DESCRIPTORFIND (Stack* stk){
    bool STATUS = false;
        for(size_t pos = 0; pos < DESCRIPTORS_SIZE; pos++)
            if(DESCRIPTORS[pos] == stk){
                STATUS = true;
                break;
            }
    return STATUS;
}