#include "../include/vector.h"
#include <stdio.h>
#include <stdlib.h>

static void v_increase_size(vector *v);
static void validate_allocation(void *v, const char *context) {
  if (!v) {
    printf("Memory allocation failed: %s", context);
    exit(1);
  }
}

struct vector {
  size_t capacity;
  size_t size;
  v_type *values;
};

const size_t v_capacity(const vector *v) { return v->capacity; }
const size_t v_size(const vector *v) { return v->size; }
v_type *v_arr(vector *v) { return v->values; }

vector *v_init(size_t initial_capacity) {
  size_t capacity =
      initial_capacity > MINIMUM_CAPACITY ? initial_capacity : MINIMUM_CAPACITY;
  v_type *values = malloc(capacity * sizeof(v_type));
  validate_allocation(values, "values initailized");

  vector *v = malloc(sizeof(vector));
  validate_allocation(v, "vector initialization");

  v->values = values;
  v->capacity = capacity;
  v->size = 0;
  return v;
}

v_type *v_get(const vector *v, size_t index) {
  if (index >= v->size) {
    return NULL;
  }

  return &v->values[index];
}

void v_copy(vector **dest, const vector *src) {
  v_dispose(*dest);
  *dest = v_init(src->capacity);

  for (size_t i = 0; i < src->size; i++) {
    v_append(*dest, *v_get(src, i));
  }
}

void v_dispose(vector *v) {
  if (!v)
    return;

  free(v->values);
  free(v);
}

void v_append(vector *v, v_type val) {
  if (v->size == v->capacity) {
    v_increase_size(v);
  }

  v->values[v->size++] = val;
}

void v_increase_size(vector *v) {
  v->capacity *= 2;

  v_type *new_values = realloc(v->values, v->capacity * sizeof(v_type));
  validate_allocation(new_values, "copying values");

  v->values = new_values;
}
