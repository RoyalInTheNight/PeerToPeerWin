//
// Created by MikoG on 12.12.2022.
//
#include "NativeInterface.h"

template<class __Key, class __tn> void npmap<__Key, __tn>::np_memcpy(void *__dst, const void *__src, size_t __dstsize) {
    if ((uintptr_t)__dst % sizeof(int64_t) == 0 &&
        (uintptr_t)__src % sizeof(int64_t) == 0 &&
        __dstsize % sizeof(int64_t) == 0) {

        int64_t *d = (int64_t *)__dst;
        const int64_t *s = (int64_t *)__src;

        for (int32_t i = 0; i < __dstsize / sizeof(int64_t); i++)
            *(d + i) = *(s + i);
    }

    else {
        char *d = (char *)__dst;
        const char *s = (const char *)__src;

        for (int32_t i = 0; i < __dstsize; i++)
            *(d + i) = *(s + i);
    }
}

template<class __Key, class __tn> void npmap<__Key, __tn>::np_memset(void *__dst, uint8_t __char, size_t __len) {
    if ((uintptr_t)__dst % sizeof(int64_t) == 0 &&
        __len % sizeof(int64_t) == 0) {

        int64_t  *d = (int64_t *)__dst;

        for (int32_t i = 0; i < __len / sizeof(int64_t); i++)
            *(d + i) = __char;
    }

    else {
        char *d = (char *)__dst;

        for (int32_t i = 0; i < __len; i++)
            *(d + i) = __char;
    }
}