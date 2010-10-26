#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdarg.h>

#define _debug(...) { printf(":%i\t", __LINE__); printf(__VA_ARGS__); printf("\n"); }

#ifdef _DEBUG
#if defined(__func__)
#define debug(...) { printf("%s", __func__); _debug(__VA_ARGS__); }
#elif defined(__FUNCTION__)
#define debug(...) { printf("%s", __FUNCTION__); _debug(__VA_ARGS__); }
#else
#define debug(...) { printf("%s", __FILE__); _debug(__VA_ARGS__); }
#endif
#else
#define debug(...) {}
#endif

#endif