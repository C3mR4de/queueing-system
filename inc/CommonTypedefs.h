#ifndef COMMON_TYPEDEFS_H
#define COMMON_TYPEDEFS_H

#include <stdint.h>

typedef uintmax_t ID;
typedef intmax_t  TimeMoment;
typedef bool   (*Comparator)(const void*, const void*);

#define SOURCE_REQUESTS_COUNT 7ULL

#endif
