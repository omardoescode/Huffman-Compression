#include "../include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void v_increase_size(vector *v, size_t new_capacity);
void validate_allocation(void *v, const char *context) {
  if (!v) {
    printf("Memory allocation failed: %s", context);
    exit(1);
  }
}
size_t max(size_t v1, size_t v2) { return v1 > v2 ? v1 : v2; }

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
  memset(values, 0, capacity * sizeof(v_type));

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

  /* printf("Inserting at index: %lc: ", index); */
  return &v->values[index];
}

void v_copy(vector **dest, const vector *src) {
  v_free(*dest);
  *dest = v_init(src->capacity);

  for (size_t i = 0; i < src->size; i++) {
    v_append(*dest, *v_get(src, i));
  }
}

void v_free(vector *v) {
  if (!v)
    return;
  if (!v->values)
    return;

  free(v->values);
  free(v);
}

void v_append(vector *v, v_type val) {
  if (v->size == v->capacity) {
    v_increase_size(v, 2 * v->capacity);
  }

  v->values[v->size++] = val;
}

void v_increase_size(vector *v, size_t new_capacity) {
  if (new_capacity < v->capacity)
    return;

  v->capacity = max(max(new_capacity, MINIMUM_CAPACITY), 2 * v->capacity);

  v_type *new_values = malloc(v->capacity * sizeof(v_type));
  validate_allocation(new_values, "copying values");

  for (int i = 0; i < v->size; i++)
    new_values[i] = v->values[i];
  memset(new_values + v->size, 0, (v->capacity - v->size) * sizeof(v_type));

  v->values = new_values;
}

void v_set(vector *v, size_t index, v_type val) {
  // This will either create a space for index if not there or do nothing if it
  // exists
  v_increase_size(v, index + 1);

  v->values[index] = val;
  if (index >= v->size)
    v->size = index + 1;
}
