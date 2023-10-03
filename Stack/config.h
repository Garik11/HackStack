#ifndef CONFIG_H
    #define CONFIG_H

    #define DEBUG
    #define USE_HASH
    #define USE_CALIBRI

    typedef int Elem_t;
    #define specifier_Elem_t "%d"

    const unsigned long long MAX_DESCRIPTORS_SIZE   = 1000;
    const unsigned long long STACK_MAX_SIZE         = 1000;

    #ifdef DEBUG
        #define ON_DEBUG(...) __VA_ARGS__
    #else
        #define ON_DEBUG(...)
    #endif

    #ifdef USE_HASH
        #define ON_HASH(...) __VA_ARGS__
    #else
        #define ON_HASH(...)
    #endif

    #ifdef USE_CALIBRI
        #define ON_CALIBRI(...) __VA_ARGS__
    #else
        #define ON_CALIBRI(...)
    #endif
#endif // !CONFIG_H