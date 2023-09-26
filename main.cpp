#include <stdio.h>
#include "Stack.h"
#include "Best_cat_welcome.h"
#include "config.h"
#include "StackStruct.h"
#include "StackHidden.h"
//Массив стэков
//Внутренний заголовок маин не инключ спп инклюд            ++
//Можно объявить разные сьркуьуры но одинакового размера    ++ 
//Отделить hash                                             ++
//addres санитайзер                                         &&
//mprotect
//Макрос ON_CALIBRI
//дебаг, хэш, калибри отдельно
//оптимизировать код новыми макросами
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
    StackPush(stk, 10, &error);  
    StackPop(stk, &error);  
    StackDtor(stk);
}