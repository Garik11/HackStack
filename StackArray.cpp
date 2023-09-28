#include "StackArray.h"

void StackNullificator (Stack *stk, StackErrorsBitmask* err_ret){
    StackErrorsBitmask errors = StackVerificator(stk);
    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        if(err_ret != NULL)
            *err_ret |= errors;
        return;
    }

    stk->size = 0;
    stk->capacity = 0;
    free(stk->data);
    stk->data = NULL;

    ON_DEBUG(
        stk->calibri_left = 0;
        stk->calibri_right = 0;
        stk->CREATION_FILE = NULL;
        stk->CREATION_FUNC = NULL;
        stk->datahash = 0;
        stk->structhash = 0;
    )
}

bool StackCheckExistence (Stack* stk){
    for(size_t pos = 0; pos < STACK_MAX_SIZE; pos++)
        if(&StacksArray[pos] == stk)
            return true;
    return false;
}

bool StackCheckNullificator (Stack *stk, StackErrorsBitmask* err_ret){
    StackErrorsBitmask errors = STACK_ALL_OK;
    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        if(err_ret != NULL)
            *err_ret |= errors;
        return FILLED;
    }

    bool status = FILLED;

    if(stk->size == 0) status = EMPTY;
    if(stk->data == NULL) status = EMPTY;

    return status;
}

void StackGetStack (Stack** stk, StackErrorsBitmask* err_ret){

    StackErrorsBitmask errors = STACK_ALL_OK;

    for(size_t i = 0; i < STACK_MAX_SIZE; i++)
        if(StackCheckNullificator(&StacksArray[i], &errors) == EMPTY){
            if(errors != STACK_ALL_OK){

                ON_DEBUG(
                    BAD_STACK_DUMP(*stk, errors);
                )

                if(err_ret != NULL)
                    *err_ret |= errors;
                return;
            }
            *stk = &StacksArray[i];
            return;

        }
    *err_ret = STACK_SET_ERROR(false, STACK_GET_ERROR);

    ON_DEBUG(
        BAD_STACK_DUMP(*stk, errors);
    )

    if(err_ret != NULL)
        *err_ret |= errors;
    return;
}

void StackBackStack(Stack* stk, StackErrorsBitmask* err_ret){
    
    StackErrorsBitmask errors = STACK_ALL_OK;

    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        if(err_ret != NULL)
            *err_ret |= errors;
        return;
    }

    StackNullificator(stk, &errors);

    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        if(err_ret != NULL)
            *err_ret |= errors;
        return;
    }
}