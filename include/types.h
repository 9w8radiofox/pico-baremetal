#ifndef __COMMON_TYPES_H__
#define __COMMON_TYPES_H__

#include <stdint.h>
#include <stdbool.h>

// #include <asm/bits_per_long.h>
#define BITS_PER_LONG 32

typedef int8_t		s8;
typedef uint8_t		u8;
typedef int16_t		s16;
typedef uint16_t	u16;
typedef int32_t		s32;
typedef uint32_t	u32;
typedef int64_t		s64;
typedef uint64_t	u64;
typedef unsigned long	ulong;

#define array_size(x)		(sizeof(x) / sizeof((x)[0]))
#define ARRAY_SIZE(x)		array_size(x)

// Additional types
#define __weak			__attribute__((weak))
#define __weak_interrupt	__attribute__((weak, interrupt))
#define __constructor		__attribute__((constructor))
#define __constructor_n(n)	__attribute__((constructor(n)))
#define __noreturn		__attribute__((noreturn))

// Explicitly qualify io registers for readability and avoid coding error
#define __I 			const volatile
#define __O 			volatile
#define __IO			volatile

// Cast addr in io operations to avoid compile warnings
#define __CAST_I(x)		(const volatile void *)(x)
#define __CAST_O(x)		(volatile void *)(x)
#define __CAST_IO(x)		(volatile void *)(x)

#define STR(x) XSTR(x)
#define XSTR(x) #x
#define STR_COLOR_GREEN(x)	"\033[1;32m" #x "\033[0m"
#define STR_COLOR_RED(x)	"\033[1;31m" #x "\033[0m"

#define CONCAT2(a,b)	a##b

#ifndef offsetof
# define offsetof(TYPE, MEMBER)	((size_t)&((TYPE *)0)->MEMBER)
#endif
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#define MAX(a,b)			((a) > (b) ? (a) : (b))
#define MIN(a,b)			((a) < (b) ? (a) : (b))

#endif /* __COMMON_TYPES_H__ */
