#ifndef STACK_HIDDEN_H
#define STACK_HIDDEN_H

#include <stddef.h>
#include <limits.h>
#include <stdint.h>

#include "Stack.h"
#include "StackStruct.h"
#include "StackArray.h"
#include "StackCalibri.h"
#include "StackHash.h"

#include "../recalloc/recalloc.h"
#include "config.h"

//stderr
#define print_error(error_code)     printf("ERROR: "#error_code"!\n")
#define STACK_DUMP(stk, errors)     StackDump(stk, errors, #stk, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define BAD_STACK_DUMP(stk, errors) do{StackDump(stk, errors, #stk, __FILE__, __LINE__, __PRETTY_FUNCTION__); exit(-1);}    while(0)

#define STACK_SET_ERROR(сondition, сondition_name) ((сondition) == 0) ? сondition_name : STACK_ALL_OK

enum StackStatus{
    EMPTY,
    FILLED
};

static const size_t POISONED_NUM =     (size_t)-1 / 2;
static const size_t SIZE_T_OVERFLOW =  (size_t)-1;

static const size_t DATA_STANDART_SIZE = 16;
static const size_t STARTING_POSITION  = 0;

static const size_t STACK_SIZE_MULTIPLIER  = 2;

StackErrorsBitmask StackVerificator (Stack *stk, StackErrorsBitmask basicerror = STACK_ALL_OK);

void StackDump( Stack *stk, 
                StackErrorsBitmask errors, 
                const char* STACK_NAME, 
                const char* FILE_NAME, 
                int LINE, 
                const char* FUNC
            );

void StackSizeMultiplier(Stack* stk, StackErrorsBitmask* err_ret = NULL);
void StackSizeDivider   (Stack* stk, StackErrorsBitmask* err_ret = NULL);

#endif // !STACK_HIDDEN_H
