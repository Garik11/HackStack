#ifndef STACK_DESCRIPTOR_H
#define STACK_DESCRIPTOR_H
#include "Stack.h"
#include "StackStruct.h"
#include "config.h"

void DESCRIPTORADD  (Stack* stk, StackErrorsBitmask *err_ret);
void DESCRIPTORDEC  (Stack* stk, StackErrorsBitmask *err_ret);
bool DESCRIPTORFIND (Stack* stk);
#endif