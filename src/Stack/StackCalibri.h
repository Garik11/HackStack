#ifndef STACK_CALIBRI_H
#define STACK_CALIBRI_H

#include "StackStruct.h"

#ifdef USE_CALIBRI
bool StackCmpStructCalibri  (Stack* stk);
bool StackCmpDataCalibri    (Stack* stk);
#endif // USE_CALIBRI

#endif // !STACK_CALIBRI_H
