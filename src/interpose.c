#include "../include/interpose.h"

// Declare pointers to store the original functions
static size_t (*original_fread)(void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream) = NULL;
static size_t (*original_fwrite)(const void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __s) = NULL;

size_t my_fread(void *__restrict __ptr, size_t __size, size_t __n,
                FILE *__restrict __stream) {
  // Initialize the original function pointer if not done already
  if (!original_fread) {
    original_fread = (size_t (*)(void *, size_t, size_t, FILE *))dlsym(RTLD_NEXT, "fread");
  }

  // Log the action
  printf("Reading %zu with size %zu from file\n", *(size_t*)__ptr, __size);

  // Call the original fread function
  return original_fread(__ptr, __size, __n, __stream);
}

size_t my_fwrite(const void *__restrict __ptr, size_t __size, size_t __n,
                 FILE *__restrict __s) {
  // Initialize the original function pointer if not done already
  if (!original_fwrite) {
    original_fwrite = (size_t (*)(const void *, size_t, size_t, FILE *))dlsym(RTLD_NEXT, "fwrite");
  }

  // Log the action
  printf("Writing %zu with size %zu to file\n", *(size_t*)__ptr, __size);

  // Call the original fwrite function
  return original_fwrite(__ptr, __size, __n, __s);
}
