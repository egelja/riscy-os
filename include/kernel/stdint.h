#ifndef __KERNEL_STDINT_H__
#define __KERNEL_STDINT_H__

#include "generated/autoconf.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#    define NULL 0
#endif

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

#if CONFIG_64_BIT
typedef uint64_t size_t;
typedef int64_t ssize_t;
#else
typedef uint32_t size_t;
typedef int32_t ssize_t;
#endif

/* Checks */
/* NOLINTBEGIN */
_Static_assert(sizeof(int8_t) == 1, "int8_t is not 1 byte!");
_Static_assert(sizeof(int16_t) == 2, "int16_t is not 2 bytes long!");
_Static_assert(sizeof(int32_t) == 4, "int32_t is not 4 bytes long!");
_Static_assert(sizeof(int64_t) == 8, "int64_t is not 8 bytes long!");

_Static_assert(sizeof(uint8_t) == 1, "uint8_t is not 1 byte!");
_Static_assert(sizeof(uint16_t) == 2, "uint16_t is not 2 bytes long!");
_Static_assert(sizeof(uint32_t) == 4, "uint32_t is not 4 bytes long!");
_Static_assert(sizeof(uint64_t) == 8, "uint64_t is not 8 bytes long!");

_Static_assert(sizeof(size_t) == sizeof(sizeof(int)), "size_t not set correctly!");
_Static_assert(sizeof(ssize_t) == sizeof(sizeof(int)), "size_t not set correctly!");
/* NOLINTEND */

#ifdef __cplusplus
}
#endif

#endif
