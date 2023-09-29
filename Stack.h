#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "config.h"
#include "Best_cat_welcome.h"

#define STACK_CTOR(error) StackCtor(__FILE__, __LINE__, __func__, error)

typedef size_t StackErrorsBitmask;
typedef unsigned long long Calibri;

struct Stack;

//hex
enum StackErrors{
    STACK_ALL_OK                    = 0 << 0 ,
    STACK_NOT_DEFINED               = 1 << 0 ,
    STACK_CTOR_GETSTACK             = 1 << 1 ,
    STACK_DATA_NOT_DEFINED          = 1 << 2 ,
    STACK_SIZE_MISMATCH             = 1 << 3 ,
    STACK_MULTIPLY_CALLOC           = 1 << 4 ,
    STACK_DIVIDER_CALLOC            = 1 << 5 ,
    STACK_IS_EMPTY                  = 1 << 6 ,
    STACK_TOO_BIG                   = 1 << 7 ,
    STACK_IS_POISONED               = 1 << 8 ,
    STACK_BAD_STRUCT_HASH           = 1 << 9 ,
    STACK_BAD_DATA_HASH             = 1 << 10,
    STACK_BAD_STRUCT_CALIBRI        = 1 << 11,
    STACK_BAD_DATA_CALIBRI          = 1 << 12,
    STACK_WRONG_DESCRIPTOR          = 1 << 13,
    STACK_CTOR_DATA_CALLOC          = 1 << 16,
    STACK_GET_ERROR                 = 1 << 17,
    STACK_NULLIFICATOR_BAD          = 1 << 18
};

Stack*  StackCtor(const char* CREATION_FILE, int CREATION_LINE, const char* CREATION_FUNC, StackErrorsBitmask* err_ret = NULL);
void    StackDtor(Stack *stk, StackErrorsBitmask* err_ret = NULL);

void    StackPush(Stack *stk, Elem_t element, StackErrorsBitmask* err_ret = NULL);
Elem_t  StackPop (Stack *stk, StackErrorsBitmask* err_ret = NULL);

void StackCheckAllErrors(StackErrorsBitmask errors);

#endif // STACK_H