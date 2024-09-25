#ifndef VECTOR_HEADER
#define VECTOR_HEADER
#define MINIMUM_CAPACITY 10
#define v_type size_t
#include <stdint.h>
#include <wchar.h>

typedef struct vector vector;

vector *v_init(size_t initial_capacity);
const size_t v_capacity(const vector *v);
const size_t v_size(const vector *v);
v_type *v_arr(vector *v);
void v_copy(vector **dest, const vector *src);
v_type *v_get(const vector *v, size_t index);
void v_append(vector *v, v_type val);
void v_set(vector *v, size_t index, v_type val);
void v_dispose(vector *v);
#endif
