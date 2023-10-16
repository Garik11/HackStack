#include "StackHidden.h"

static void StackSizeMultiplier (Stack* stk, StackErrorsBitmask* err_ret = NULL);
static void StackSizeDivider    (Stack* stk, StackErrorsBitmask* err_ret = NULL);

Stack* StackCtor(const char*    CREATION_FILE, 
                int             CREATION_LINE, 
                const char*     CREATION_FUNC, 
                StackErrorsBitmask* err_ret /* = NULL */
            )
{

    StackErrorsBitmask errors = STACK_ALL_OK;

    Stack* stk = NULL;
    StackGetStack(&stk, &errors);

    errors |= STACK_SET_ERROR(stk != NULL, STACK_CTOR_GETSTACK);
    if(errors != STACK_ALL_OK){
        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        if(err_ret != NULL) 
            *err_ret |= errors;

        return NULL;
    }

    ON_CALIBRI(
        stk->calibri_left  =    (Calibri)   stk;
        stk->calibri_right = /* (Calibri)*/ (stk->calibri_left + sizeof(stk));
    )

    #ifdef USE_CALIBRI
        stk->data = (char*)calloc(sizeof(BYTE), DATA_STANDART_SIZE * sizeof(Elem_t) + 2 * sizeof(Calibri));
    #else
        stk->data = (char*)calloc(sizeof(BYTE), DATA_STANDART_SIZE * sizeof(Elem_t));
    #endif

    errors |= STACK_SET_ERROR(stk->data != NULL, STACK_CTOR_DATA_CALLOC);
    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        StackBackStack(stk, &errors);

        if(err_ret != NULL)
            *err_ret |= errors;
        return NULL;
    }
    stk->size   = STARTING_POSITION ;
    stk->capaticy       = DATA_STANDART_SIZE;

    ON_DEBUG(
        stk->CREATION_FILE = CREATION_FILE;
        stk->CREATION_LINE = CREATION_LINE;
        stk->CREATION_FUNC = CREATION_FUNC;
    )
    ON_CALIBRI(
        *((Calibri*)stk->data) =
          (Calibri )(stk->data);

        *((Calibri*)(stk->data + stk->capaticy * sizeof(Elem_t) + sizeof(Calibri))) =
          (Calibri )(stk->data + stk->capaticy * sizeof(Elem_t) + sizeof(Calibri));
    )
    ON_HASH(
        stk->datahash   = StackGetDataHash  (stk);
        stk->structhash = StackGetStructHash(stk);
    )
    
    return stk;
}

void StackDtor(Stack *stk, StackErrorsBitmask* err_ret /* = NULL */){

    StackErrorsBitmask errors = StackVerificator(stk);

    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        if(err_ret != NULL)
            *err_ret |= errors;
        return;
    }

    StackBackStack(stk, &errors);

    if(err_ret != NULL)
        *err_ret |= errors;
}

StackErrorsBitmask StackVerificator(Stack *stk, StackErrorsBitmask errors /* = STACK_ALL_OK */){

    if(StackCheckExistence(stk) == false) 
        return STACK_NOT_DEFINED | STACK_WRONG_DESCRIPTOR;

    errors |= STACK_SET_ERROR(  stk->data != NULL,                  STACK_DATA_NOT_DEFINED  );
    errors |= STACK_SET_ERROR(  stk->size < stk->capaticy,          STACK_SIZE_MISMATCH     );
    errors |= STACK_SET_ERROR(  stk->size       != POISONED_NUM && 
                                stk->capaticy   != POISONED_NUM,    STACK_IS_POISONED       );

    ON_HASH(
        if(StackCmpStructHash       (stk) == false)    
            errors |= STACK_BAD_STRUCT_HASH;
        else if(StackCmpDataHash    (stk) == false)     
            errors |= STACK_BAD_DATA_HASH;
    )
    ON_CALIBRI(
        if(StackCmpStructCalibri    (stk) == false)    
            errors |= STACK_BAD_STRUCT_CALIBRI;
        else if(StackCmpDataCalibri (stk) == false) 
            errors |= STACK_BAD_DATA_CALIBRI;
    )

    return errors;
}

void StackCheckAllErrors(StackErrorsBitmask errors){
    if(errors & STACK_NOT_DEFINED           ) print_error(STACK_NOT_DEFINED          );
    if(errors & STACK_CTOR_GETSTACK         ) print_error(STACK_CTOR_GETSTACK        );
    if(errors & STACK_DATA_NOT_DEFINED      ) print_error(STACK_DATA_NOT_DEFINED     );
    if(errors & STACK_SIZE_MISMATCH         ) print_error(STACK_SIZE_MISMATCH        );
    if(errors & STACK_MULTIPLY_CALLOC       ) print_error(STACK_MULTIPLY_CALLOC      );
    if(errors & STACK_DIVIDER_CALLOC        ) print_error(STACK_DIVIDER_CALLOC       );
    if(errors & STACK_IS_EMPTY              ) print_error(STACK_IS_EMPTY             );
    if(errors & STACK_TOO_BIG               ) print_error(STACK_TOO_BIG              );
    if(errors & STACK_IS_POISONED           ) print_error(STACK_IS_POISONED          );
    if(errors & STACK_BAD_STRUCT_HASH       ) print_error(STACK_BAD_STRUCT_HASH      );
    if(errors & STACK_BAD_DATA_HASH         ) print_error(STACK_BAD_DATA_HASH        );
    if(errors & STACK_BAD_STRUCT_CALIBRI    ) print_error(STACK_BAD_STRUCT_CALIBRI   );
    if(errors & STACK_BAD_DATA_CALIBRI      ) print_error(STACK_BAD_DATA_CALIBRI     );
    if(errors & STACK_WRONG_DESCRIPTOR      ) print_error(STACK_WRONG_DESCRIPTOR     );
    if(errors & STACK_CTOR_DATA_CALLOC      ) print_error(STACK_CTOR_DATA_CALLOC     );
    if(errors & STACK_GET_ERROR             ) print_error(STACK_GET_ERROR            );
    if(errors & STACK_NULLIFICATOR_BAD      ) print_error(STACK_NULLIFICATOR_BAD     );
}

static void StackSizeMultiplier(Stack* stk, StackErrorsBitmask* err_ret /* = NULL */){

    StackErrorsBitmask errors = StackVerificator(stk);

    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        if(err_ret != NULL)
            *err_ret |= errors;
        return;
    }

    errors = STACK_SET_ERROR(stk->capaticy * sizeof(Elem_t) * STACK_SIZE_MULTIPLIER < INT_MAX, STACK_TOO_BIG);
    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )
        
        if(err_ret != NULL)
            *err_ret |= errors;
        return;
    }

    #ifdef USE_CALIBRI
        void* new_str_data = recalloc(stk->data,    sizeof(BYTE), stk->capaticy * sizeof(Elem_t) * STACK_SIZE_MULTIPLIER + 2 * sizeof(Calibri),
                                                    sizeof(BYTE), stk->capaticy * sizeof(Elem_t) + 2 * sizeof(Calibri));
    #else
        void* new_str_data = recalloc(stk->data,    sizeof(BYTE), stk->capaticy * sizeof(Elem_t) * STACK_SIZE_MULTIPLIER,
                                                    sizeof(BYTE), stk->capaticy * sizeof(Elem_t));
    #endif // USE_CALIBRI

    errors = STACK_SET_ERROR(new_str_data != NULL, STACK_MULTIPLY_CALLOC);
    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        if(err_ret != NULL)
            *err_ret |= errors;
        return;
    }

    stk->data = (char*)new_str_data;
    stk->capaticy *= STACK_SIZE_MULTIPLIER;

    ON_CALIBRI(
        *((Calibri*)stk->data) = 
          (Calibri )stk->data;

        *((Calibri*)(stk->data + stk->capaticy * sizeof(Elem_t) + sizeof(Calibri))) = 
          (Calibri )(stk->data + stk->capaticy * sizeof(Elem_t) + sizeof(Calibri));
    )
}

static void StackSizeDivider(Stack* stk, StackErrorsBitmask* err_ret /* = NULL */){

    StackErrorsBitmask errors = StackVerificator(stk);

    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        if(err_ret != NULL)
            *err_ret |= errors;
        return;
    }
    
    #ifdef USE_CALIBRI
        void* new_str_data = recalloc(stk->data,    sizeof(BYTE), stk->capaticy * sizeof(Elem_t) / STACK_SIZE_MULTIPLIER + 2 * sizeof(Calibri),
                                                    sizeof(BYTE), stk->capaticy * sizeof(Elem_t) + 2 * sizeof(Calibri));
    #else
        void* new_str_data = recalloc(stk->data,    sizeof(BYTE), stk->capaticy * sizeof(Elem_t) / STACK_SIZE_MULTIPLIER,
                                                    sizeof(BYTE), stk->capaticy * sizeof(Elem_t));
    #endif // USE_CALIBRI

    errors = STACK_SET_ERROR(new_str_data != NULL, STACK_DIVIDER_CALLOC);
    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        if(err_ret != NULL)
            *err_ret |= errors;
        return;
    }

    stk->data = (char*)new_str_data;
    stk->capaticy /= STACK_SIZE_MULTIPLIER;

    ON_CALIBRI(
        *((Calibri*)stk->data) = 
          (Calibri)stk->data;

        *((Calibri*)(stk->data + stk->capaticy * sizeof(Elem_t) + sizeof(Calibri))) = 
          (Calibri )(stk->data + stk->capaticy * sizeof(Elem_t) + sizeof(Calibri));
    )
}

void StackDump(Stack *stk, StackErrorsBitmask errors, const char* STACK_NAME, const char* FILE_NAME, int LINE, const char* FUNC){

    printf(MY_BEST_BUG);
    errors |= StackVerificator(stk);
    
    StackCheckAllErrors(errors);

    const char* sname = (STACK_NAME == NULL) ? "???" : STACK_NAME   ;
    const char* fname = (FILE_NAME  == NULL) ? "???" : FILE_NAME    ;
    const char* func =  (FUNC       == NULL) ? "???" : FUNC         ;

    /*if stk == NULL*/
    if(errors & STACK_NOT_DEFINED){
        printf("Stack[error] \"%s\" called from %s(%d) in %s\n", sname , fname, LINE, func);
        return;
    }
    if(errors & STACK_BAD_STRUCT_HASH || errors & STACK_BAD_STRUCT_CALIBRI){
        printf("Stack[%p] \"%s\" called from file:%s(%d) func:%s\n", stk, sname, fname, LINE, func);
        printf("\t{size     = %lu\n", stk->capaticy);
        printf("\t capacity = %lu\n", stk->size);
        printf("\t data[error]\n");
        printf("\t}\n");
        return;
    }
    
    #ifdef DEBUG
        printf("Stack[%p] \"%s\" created in file:%s(%d) func:%s\n\
            called from file:%s(%d) func:%s\n", 
            stk, sname, 
            stk->CREATION_FILE, stk->CREATION_LINE, stk->CREATION_FUNC, 
            fname, LINE, func);
    #else
        printf("Stack[%p] \"%s\" called from file:%s(%d) func:%s\n", 
            stk, sname, 
            fname, LINE, func);
    #endif

    printf("\t{size     = %lu\n", stk->capaticy);
    printf("\t capacity = %lu\n", stk->size);

    /*if stk->data == NULL*/
    if(errors & STACK_DATA_NOT_DEFINED){
        printf("\t data[error]\n");
        printf("\t}\n");
        return;
    }

    size_t number_of_elements = stk->capaticy;

    #ifdef linux
        size_t size_data = malloc_usable_size(stk->data);
        size_t size_data_elements = size_data / sizeof(Elem_t);
        printf("\t malloc_usable_size(data) = %lu bytes\n", size_data);
        printf("\t malloc_usable_size(data) = %lu elements\n", size_data_elements);
    #endif

    printf("\t data[%p]\n", stk->data);
    printf("\t\t{\n");

    for(size_t i = 0; i < number_of_elements; i++)
        printf("\t\t *[%lu] = "specifier_Elem_t"\n", i, *((Elem_t*)(stk->data + i * sizeof(Elem_t) + sizeof(Calibri))));
    printf("\t\t}\n");
    printf("\t}\n");
}

void StackPush(Stack *stk, Elem_t element, StackErrorsBitmask* err_ret /* = NULL */){

    StackErrorsBitmask errors = StackVerificator(stk);

    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        if(err_ret != NULL)
            *err_ret |= errors;
        return;
    }

    if(stk->size + 1 == stk->capaticy)
        StackSizeMultiplier(stk, &errors);

    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        if(err_ret != NULL)
            *err_ret |= errors;
        return;
    }
    
    //#warning move data sizeof(calibri) forward
    #ifdef USE_CALIBRI
        *((Elem_t*)(stk->data + stk->size * sizeof(Elem_t) + sizeof(Calibri))) = element;
    #else
        *((Elem_t*)(stk->data + stk->size * sizeof(Elem_t))) = element;
    #endif // !USE_CALIBRI

    stk->size++;

    ON_HASH(
        stk->datahash   = StackGetDataHash  (stk);
        stk->structhash = StackGetStructHash(stk);
    )
}

Elem_t StackPop (Stack *stk, StackErrorsBitmask* err_ret /* = NULL */){

    StackErrorsBitmask errors = StackVerificator(stk);

    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        if(err_ret != NULL)
            *err_ret |= errors;
        return 0;
    }

    if(stk->size * STACK_SIZE_MULTIPLIER < stk->capaticy && stk->capaticy > DATA_STANDART_SIZE)
        StackSizeDivider(stk, &errors);

    errors = STACK_SET_ERROR(stk->size != 0, STACK_IS_EMPTY);
    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )
        
        if(err_ret != NULL)
            *err_ret |= errors;
        return 0;
    }

    stk->size--;

    #ifdef USE_CALIBRI
        //return ((Elem_t*)stk->data)[stk->size]
        Elem_t value = *((Elem_t*)(stk->data + stk->size * sizeof(Elem_t) + sizeof(Calibri)));
        *((Elem_t*)(stk->data + stk->size * sizeof(Elem_t) + sizeof(Calibri))) = 0;
    #else
        Elem_t value = *((Elem_t*)(stk->data + stk->size * sizeof(Elem_t)));
        *((Elem_t*)(stk->data + stk->size * sizeof(Elem_t))) = 0;
    #endif // !USE_CALIBRI

    ON_HASH(
        stk->datahash   = StackGetDataHash  (stk);
        stk->structhash = StackGetStructHash(stk);
    )

    return value;
}