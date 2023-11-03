#include <stdio.h>
#include "src/Stack/Stack.h"
#include "src/Stack/StackStruct.h"
//#include "StackHidden.h"
//Массив стэков                                             ++
//Внутренний заголовок маин не инключ спп инклюд            ++
//Можно объявить разные сьркуьуры но одинакового размера    ++ 
//Отделить hash                                             ++
//addres санитайзер                                         &&
//mprotect                                                  ??//perror("something");
//Макрос ON_CALIBRI                                         ++
//дебаг, хэш, калибри отдельно                              ++
//оптимизировать код новыми макросами                       ++
//каллоки                                                   ++
//написать рекаллок                                         ++
//спрятать вычесление адресации             
//для калибри тоже самое
//RETURN

//Сигфолт в функции
//alt alt alt hex-redactor DOS

int main(void){

    printf(MY_BEST_STACK);
    printf(MY_BEST_CAT);
    
    StackErrorsBitmask error = STACK_ALL_OK;
    Stack *stk  = STACK_CTOR(&error);
    assert(error == STACK_ALL_OK);
    Stack *stk2 = STACK_CTOR(&error);
    assert(error == STACK_ALL_OK);
    StackPush(stk, 100);
    StackPush(stk2, 1000000);
    printf("f1 = %d\n", StackPop(stk));
    printf("f1 = %d\n", StackPop(stk));
    //printf("f2 = %d\n", StackPop(stk2));
    StackDtor(stk);
    StackDtor(stk2);
}

/*
    StackErrorsBitmask error = STACK_ALL_OK;
    Stack *stk = STACK_CTOR(&error);

    memset((void*)stk, 0, sizeof(Stack));

    Stack *stk2 = STACK_CTOR(&error);

    printf("%p %p\n", stk, stk2);

    StackPush(stk2, 1000);
    printf("%d\n", StackPop(stk2));

    printf("%d\n", StackPop(stk2));
*/
