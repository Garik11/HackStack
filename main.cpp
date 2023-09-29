#include <stdio.h>
#include "Stack.h"

#include "StackStruct.h"
//#include "StackHidden.h"
//Массив стэков                                             ++
//Внутренний заголовок маин не инключ спп инклюд            ++
//Можно объявить разные сьркуьуры но одинакового размера    ++ 
//Отделить hash                                             ++
//addres санитайзер                                         &&
//mprotect                                                  ??
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
    for(size_t i = 0; i < 10000; i++){
        StackPush(stk, i*i, &error);  
    }
    //*((int*)stk) = 100;
    for(size_t i = 0; i < 10000; i++)
        printf("%d\n", StackPop(stk, &error));
    StackDtor(stk);

    
}