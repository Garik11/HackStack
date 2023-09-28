#include "StackHidden.h"

#ifdef DEBUG
    #include "StackProtect.h"
    //#include "StackDescriptor.h"
#endif //DEBUG

Stack* StackCtor(const char*    CREATION_FILE, 
                int             CREATION_LINE, 
                const char*     CREATION_FUNC, 
                StackErrorsBitmask* err_ret /* = NULL */
){

    StackErrorsBitmask errors = STACK_ALL_OK;

    Stack* stk = NULL;
    StackGetStack(&stk, &errors);
    errors = STACK_SET_ERROR(stk != NULL, STACK_CTOR_GETSTACK);
    if(errors != STACK_ALL_OK){
        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        if(err_ret != NULL) *err_ret |= errors;

        return NULL;
    }

    ON_DEBUG(
        stk->calibri_left  = (Calibri)stk;
        stk->calibri_right = (Calibri)(stk->calibri_left + sizeof(stk));
    )

    #ifdef DEBUG
        stk->data = (char*)calloc(sizeof(BYTE), DATA_STANDART_SIZE * sizeof(Elem_t) + 2 * sizeof(Calibri));
    #else
        stk->data = (char*)calloc(sizeof(BYTE), DATA_STANDART_SIZE * sizeof(Elem_t));
    #endif
    errors = STACK_SET_ERROR(stk->data != NULL, STACK_CTOR_DATA_CALLOC);
    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        StackBackStack(stk, &errors);

        if(err_ret != NULL)
            *err_ret |= errors;
        return NULL;
    }
    stk->capacity   = STARTING_POSITION ;
    stk->size       = DATA_STANDART_SIZE;

    ON_DEBUG(
        //DESCRIPTORADD(stk, &errors);
        //if(errors != STACK_ALL_OK)
         //   BAD_STACK_DUMP(stk, errors);
        stk->CREATION_FILE = CREATION_FILE;
        stk->CREATION_LINE = CREATION_LINE;
        stk->CREATION_FUNC = CREATION_FUNC;

        *((Calibri*)stk->data) =
          (Calibri )(stk->data);

        *((Calibri*)(stk->data + stk->size * sizeof(Elem_t) + sizeof(Calibri))) =
          (Calibri )(stk->data + stk->size * sizeof(Elem_t) + sizeof(Calibri));
          
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

StackErrorsBitmask StackVerificator(Stack *stk, StackErrorsBitmask basicerror){

    StackErrorsBitmask errors = basicerror;

    #ifdef DEBUG
        if(StackCheckExistence(stk) == false)    return STACK_NOT_DEFINED | STACK_WRONG_DESCRIPTOR;
    #else
        if(stk == NULL)                     return STACK_NOT_DEFINED;
    #endif

    if(stk->data == NULL)                                           errors |= STACK_DATA_NOT_DEFINED;
    if(stk->capacity > stk->size)                                   errors |= STACK_SIZE_MISMATCH;
    if(stk->capacity == POISONED_NUM || stk->size == POISONED_NUM)  errors |= STACK_IS_POISONED;

    ON_DEBUG(
        if(StackCmpStructCalibri(stk) == false )    errors |= STACK_BAD_STRUCT_CALIBRI;
        if(StackCmpStructHash   (stk) == false )    errors |= STACK_BAD_STRUCT_HASH;
        else{
            //If something is wrong with the structure, then the pointer cannot be dereferenced.
            if(StackCmpDataHash     (stk) == false) errors |= STACK_BAD_DATA_HASH;
            if(StackCmpDataCalibri  (stk) == false) errors |= STACK_BAD_DATA_CALIBRI;
        }
    )

    return errors;
}

void StackCheckAllErrors(StackErrorsBitmask errors){
    if(errors & STACK_NOT_DEFINED           ) print_error(STACK_NOT_DEFINED          );
    if(errors & STACK_CTOR_GETSTACK         ) print_error(STACK_CTOR_GETSTACK          );
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
    if(errors & STACK_DESCRIPTOR_NOT_ADDED  ) print_error(STACK_DESCRIPTOR_NOT_ADDED );
    if(errors & STACK_CTOR_DATA_CALLOC      ) print_error(STACK_CTOR_DATA_CALLOC     );
}

void StackSizeMultiplier(Stack* stk, StackErrorsBitmask* err_ret){

    StackErrorsBitmask errors = StackVerificator(stk);
    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        if(err_ret != NULL)
            *err_ret |= errors;
        return;
    }

    errors = STACK_SET_ERROR(stk->size * sizeof(Elem_t) * STACK_SIZE_MULTIPLIER < INT_MAX, STACK_TOO_BIG);
    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )
        
        if(err_ret != NULL)
            *err_ret |= errors;
        return;
    }

    #ifdef DEBUG
    void* new_str_data = recalloc(stk->data,    sizeof(BYTE), stk->size * sizeof(Elem_t) * STACK_SIZE_MULTIPLIER + 2 * sizeof(Calibri),
                                                sizeof(BYTE), stk->size * sizeof(Elem_t) + 2 * sizeof(Calibri));
    #else
    void* new_str_data = recalloc(stk->data,    sizeof(BYTE), stk->size * sizeof(Elem_t) * STACK_SIZE_MULTIPLIER,
                                                sizeof(BYTE), stk->size * sizeof(Elem_t));
    #endif // DEBUG
    /*
    #ifdef DEBUG
        void* new_str_data = realloc(stk->data, stk->size * sizeof(Elem_t) * STACK_SIZE_MULTIPLIER + 2 * sizeof(Calibri));
    #else
        void* new_str_data = realloc(stk->data, stk->size * sizeof(Elem_t) * STACK_SIZE_MULTIPLIER);
    #endif
    */
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
    stk->size *= STACK_SIZE_MULTIPLIER;
    ON_DEBUG(
        *((Calibri*)stk->data) = 
          (Calibri )stk->data;

        *((Calibri*)(stk->data + stk->size * sizeof(Elem_t) + sizeof(Calibri))) = 
          (Calibri )(stk->data + stk->size * sizeof(Elem_t) + sizeof(Calibri));
    )
}

void StackSizeDivider(Stack* stk, StackErrorsBitmask* err_ret){

    StackErrorsBitmask errors = StackVerificator(stk);
    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        if(err_ret != NULL)
            *err_ret |= errors;
        return;
    }
    #ifdef DEBUG
    void* new_str_data = recalloc(stk->data,    sizeof(BYTE), stk->size * sizeof(Elem_t) / STACK_SIZE_MULTIPLIER + 2 * sizeof(Calibri),
                                                sizeof(BYTE), stk->size * sizeof(Elem_t) + 2 * sizeof(Calibri));
    #else
    void* new_str_data = recalloc(stk->data,    sizeof(BYTE), stk->size * sizeof(Elem_t) / STACK_SIZE_MULTIPLIER,
                                                sizeof(BYTE), stk->size * sizeof(Elem_t));
    #endif // DEBUG

    /*
    #ifdef DEBUG
        void* new_str_data = realloc(stk->data, stk->size * sizeof(Elem_t) / STACK_SIZE_MULTIPLIER + 2 * sizeof(Calibri));
    #else
        void* new_str_data = realloc(stk->data, stk->size * sizeof(Elem_t) / STACK_SIZE_MULTIPLIER);
    #endif
    */
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
    stk->size /= STACK_SIZE_MULTIPLIER;
    ON_DEBUG(
        *((Calibri*)stk->data) = 
          (Calibri)stk->data;

        *((Calibri*)(stk->data + stk->size * sizeof(Elem_t) + sizeof(Calibri))) = 
          (Calibri )(stk->data + stk->size * sizeof(Elem_t) + sizeof(Calibri));
    )
}

void StackDump(Stack *stk, StackErrorsBitmask errors, const char* STACK_NAME, const char* FILE_NAME, int LINE, const char* FUNC){

    printf(MY_BEST_BUG);
    errors |= StackVerificator(stk);
    
    StackCheckAllErrors(errors);

    /*if stk == NULL*/
    if(errors & STACK_NOT_DEFINED){
        printf("Stack[error] \"%s\" called from %s(%d) in %s\n", STACK_NAME , FILE_NAME, LINE, FUNC);
        return;
    }
    if(errors & STACK_BAD_STRUCT_HASH || errors & STACK_BAD_STRUCT_CALIBRI){
        printf("Stack[%p] \"%s\" called from file:%s(%d) func:%s\n", stk, STACK_NAME, FILE_NAME, LINE, FUNC);
        printf("\t{size     = %lu\n", stk->size);
        printf("\t capacity = %lu\n", stk->capacity);
        printf("\t data[error]\n");
        printf("\t}\n");
        return;
    }
    
    #ifdef DEBUG
        printf("Stack[%p] \"%s\" created in file:%s(%d) func:%s\n\
            called from file:%s(%d) func:%s\n", 
            stk, STACK_NAME, 
            stk->CREATION_FILE, stk->CREATION_LINE, stk->CREATION_FUNC, 
            FILE_NAME, LINE, FUNC);
    #else
        printf("Stack[%p] \"%s\" called from file:%s(%d) func:%s\n", 
            stk, STACK_NAME, 
            FILE_NAME, LINE, FUNC);
    #endif

    printf("\t{size     = %lu\n", stk->size);
    printf("\t capacity = %lu\n", stk->capacity);

    /*if stk->data == NULL*/
    if(errors & STACK_DATA_NOT_DEFINED){
        printf("\t data[error]\n");
        printf("\t}\n");
        return;
    }

    size_t number_of_elements = stk->size;

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

    if(stk->capacity + 1 == stk->size)
        StackSizeMultiplier(stk, &errors);

    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )

        if(err_ret != NULL)
            *err_ret |= errors;
        return;
    }

    #ifdef DEBUG
        *((Elem_t*)(stk->data + stk->capacity * sizeof(Elem_t) + sizeof(Calibri))) = element;
    #else
        *((Elem_t*)(stk->data + stk->capacity * sizeof(Elem_t))) = element;
    #endif // DEBUG

    stk->capacity++;

    ON_DEBUG(
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

    if(stk->capacity * STACK_SIZE_MULTIPLIER < stk->size && stk->size > DATA_STANDART_SIZE)
        StackSizeDivider(stk, &errors);

    errors = STACK_SET_ERROR(stk->capacity != 0, STACK_IS_EMPTY);

    if(errors != STACK_ALL_OK){

        ON_DEBUG(
            BAD_STACK_DUMP(stk, errors);
        )
        
        if(err_ret != NULL)
            *err_ret |= errors;
        return 0;
    }

    stk->capacity--;

    ON_DEBUG(
        stk->datahash   = StackGetDataHash  (stk);
        stk->structhash = StackGetStructHash(stk);
    )

    #ifdef DEBUG
        return *((Elem_t*)(stk->data + stk->capacity * sizeof(Elem_t) + sizeof(Calibri)));
    #else
        return *((Elem_t*)(stk->data + stk->capacity * sizeof(Elem_t)));
    #endif // DEBUG
}