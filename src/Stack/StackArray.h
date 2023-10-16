#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

#include "StackStruct.h"
#include "StackHidden.h"

void StackNullificator      (Stack*  stk, StackErrorsBitmask* err_ret);
void StackGetStack          (Stack** stk, StackErrorsBitmask* err_ret);
void StackBackStack         (Stack*  stk, StackErrorsBitmask* err_ret);
bool StackCheckExistence    (Stack*  stk);
bool StackCheckNullificator (Stack*  stk);

#endif // !STACK_ARRAY_H