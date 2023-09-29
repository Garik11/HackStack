#include "StackCalibri.h"

#ifdef USE_CALIBRI
bool StackCmpStructCalibri(Stack* stk){
    return  stk->calibri_left  == (unsigned long long)stk &&
            stk->calibri_right == (unsigned long long)stk + sizeof(stk);
}

bool StackCmpDataCalibri(Stack* stk){
    return *((Calibri*)stk->data) == 
             (Calibri )stk->data &&

           *((Calibri*)(stk->data + stk->capaticy * sizeof(Elem_t) + sizeof(Calibri))) == 
             (Calibri )(stk->data + stk->capaticy * sizeof(Elem_t) + sizeof(Calibri));
}
#endif // !USE_CALIBRI