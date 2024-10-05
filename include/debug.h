#include <stdio.h>
#include <stdlib.h>
#define DEBUG 0
#if defined(DEBUG) && (DEBUG == 1)
#define debug_c(x) printf("%c", x)
#define debug_s(x)                                                             \
  printf("-- "                                                                 \
         "%s"                                                                  \
         "",                                                                   \
         x)
#define debug_u(x) printf("%u", x)
#else
#define debug_c(x)
#define debug_s(x)
#define debug_u(x)
#endif
