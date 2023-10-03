#ifndef STACK_STRUCT_H
#define STACK_STRUCT_H
#include <stdint.h>

#include "Stack.h"
#include "config.h"

typedef unsigned long long HASH;

struct Stack {
    ON_CALIBRI(
        Calibri calibri_left;
    )
    ON_HASH(
        HASH structhash;
        HASH datahash;
    )

    char *data;

    size_t capaticy;
    size_t size;

    ON_DEBUG(
        const char* CREATION_FILE;
        int         CREATION_LINE;
        const char* CREATION_FUNC;
    )
    ON_CALIBRI(
        Calibri calibri_right;
    )
};

#endif // !STACK_STRUCT_H