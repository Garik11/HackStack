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

    stk->capaticy = 0;
    stk->size = 0;
    free(stk->data);
    stk->data = NULL;

    ON_DEBUG(
        stk->CREATION_FILE = NULL;
        stk->CREATION_FUNC = NULL;
    )
    ON_CALIBRI(
        stk->calibri_left = 0;
        stk->calibri_right = 0;
    )
    ON_HASH(
        stk->datahash = 0;
        stk->structhash = 0;
    )
}

//Допилить
bool StackCheckExistence (Stack* stk){

    return StacksArray >= stk && stk < (StacksArray + STACK_MAX_SIZE) &&
        ((stk - StacksArray) % sizeof(stk) == 0);
}

bool StackCheckNullificator (Stack *stk){

    bool status = FILLED;

    if(stk->capaticy == 0)  status = EMPTY;
    if(stk->data == NULL)   status = EMPTY;

    return status;
}

// POISONED ???
void StackGetStack (Stack** stk, StackErrorsBitmask* err_ret){

    StackErrorsBitmask errors = STACK_ALL_OK;

    for(size_t i = 0; i < STACK_MAX_SIZE; i++)
        if(StackCheckNullificator(&StacksArray[i]) == EMPTY){

            *stk = &StacksArray[i];
            return;

        }
    errors |= STACK_SET_ERROR(false, STACK_GET_ERROR);

    ON_DEBUG(
        BAD_STACK_DUMP(*stk, errors);
    )

    if(err_ret != NULL)
        *err_ret |= errors;
    return;
}

void StackBackStack(Stack* stk, StackErrorsBitmask* err_ret){
    
    StackErrorsBitmask errors = StackVerificator(stk);

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