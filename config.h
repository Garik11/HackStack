#ifndef CONFIG_H
    #define CONFIG_H

    #define DEBUG

    typedef int Elem_t;
    #define specifier_Elem_t "%d"

    const unsigned long long MAX_DESCRIPTORS_SIZE   = 1000;
    const unsigned long long STACK_MAX_SIZE         = 1000;

    #ifdef DEBUG
        #define ON_DEBUG(...) __VA_ARGS__
    #else
        #define ON_DEBUG(...)
    #endif

#endif // !CONFIG_H