#if DEBUG
#include "../include/interpose.h"
#include "../include/debug.h"

void binary(const size_t x, char i) {
  if (i == 8)
    return;
  binary(x / 2, i + 1);
  printf("%zu", x % 2);
}

// Declare pointers to store the original functions
static size_t (*original_fread)(void *__restrict __ptr, size_t __size,
                                size_t __n, FILE *__restrict __stream) = NULL;
static size_t (*original_fwrite)(const void *__restrict __ptr, size_t __size,
                                 size_t __n, FILE *__restrict __s) = NULL;

size_t my_fread(void *__restrict __ptr, size_t __size, size_t __n,
                FILE *__restrict __stream) {
  // Initialize the original function pointer if not done already
  if (!original_fread) {
    original_fread =
        (size_t(*)(void *, size_t, size_t, FILE *))dlsym(RTLD_NEXT, "fread");
  }

  size_t res = original_fread(__ptr, __size, __n, __stream);

  if (res != 0) {
    printf("-- fread(");
    binary(*((size_t *)__ptr), 0);
    printf(", %zu, %zu, <file>);\n", __size, __n);
  }

  return res;
}

size_t my_fwrite(const void *__restrict __ptr, size_t __size, size_t __n,
                 FILE *__restrict __s) {
  // Initialize the original function pointer if not done already
  if (!original_fwrite) {
    original_fwrite = (size_t(*)(const void *, size_t, size_t, FILE *))dlsym(
        RTLD_NEXT, "fwrite");
  }

  int res = original_fwrite(__ptr, __size, __n, __s);

  // Print if res is not zero
  if (res != 0) {
    printf("-- fwrite(");
    binary(*((size_t *)__ptr), 0);
    printf(", %zu, %zu, <file>);\n", __size, __n);
  }

  return res;
}
#endif
