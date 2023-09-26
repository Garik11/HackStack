#ifndef STACK_STRUCT_H
#define STACK_STRUCT_H
#include <stdint.h>
#include "config.h"
#include "Stack.h"

typedef unsigned long long HASH;

struct Stack {
    ON_DEBUG(
        Calibri calibri_left;

        HASH structhash;
        HASH datahash;
    )

    char *data;

    size_t size;
    size_t capacity;

    ON_DEBUG(
        const char* CREATION_FILE;
        int         CREATION_LINE;
        const char* CREATION_FUNC;

        Calibri calibri_right;
    )
};


#endif // !STACK_STRUCT_H