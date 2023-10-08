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
    Stack *stk = STACK_CTOR(&error);
    for(int i = 0; i < 100; i++) 
        StackPush(stk, i*i, &error);
    for(int i = 0; i < 100; i++)
        printf("%d\n", StackPop(stk, &error));
    STACK_DUMP(stk, STACK_ALL_OK);
    StackDump(stk, STACK_ALL_OK, "stk", NULL, NULL, NULL);
    StackDtor(stk, &error);
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
