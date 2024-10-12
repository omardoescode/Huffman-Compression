#ifndef INTERPOSE_HEADER
#define INTERPOSE_HEADER
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#if DEBUG
size_t my_fread(void *__restrict __ptr, size_t __size, size_t __n,
                FILE *__restrict __stream);

size_t my_fwrite(const void *__restrict __ptr, size_t __size, size_t __n,
                 FILE *__restrict __s);

#define fread my_fread
#define fwrite my_fwrite
#endif
#endif
