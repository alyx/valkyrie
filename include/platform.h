#ifndef VALKYRIE_PLATFORM_H
#define VALKYRIE_PLATFORM_H

#if defined(GCC) || defined(__clang__) || defined(__ICC)
#   define UNUSED __attribute__((unused))
#else
#   define UNUSED
#endif

#endif /* VALKYRIE_PLATFORM_H */
