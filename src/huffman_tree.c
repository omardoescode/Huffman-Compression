#include "../include/huffman_tree.h"
#include "../include/priority_queue.h"
#include "../include/vector.h"
#include <assert.h>
#include <stdint.h>

struct huffman_node_t {
  wchar_t element;
  size_t weight;
  huffman_node_t *left;
  huffman_node_t *right;
};

huffman_node_t *hn_init(wchar_t el, size_t wt, huffman_node_t *l,
                        huffman_node_t *r) {
  huffman_node_t *hn = (huffman_node_t *)malloc(sizeof(huffman_node_t));
  hn->element = el;
  hn->weight = wt;
  hn->left = l;
  hn->right = r;

  return hn;
}

huffman_node_t *hn_init_array(size_t size) {
  return malloc(sizeof(huffman_node_t) * size);
}

huffman_node_t *hn_array_get(huffman_node_t *hn, size_t index) {
  return hn + index;
}

wchar_t hn_element(huffman_node_t *hn) { return hn->element; }
size_t hn_weight(huffman_node_t *hn) { return hn->weight; }
huffman_node_t *hn_left(huffman_node_t *hn) { return hn->left; }
huffman_node_t *hn_right(huffman_node_t *hn) { return hn->right; }

void hn_copy(huffman_node_t *dest, const huffman_node_t *src) {
  dest->element = src->element;
  dest->weight = src->weight;
  dest->left = src->left;
  dest->right = src->right;
}

bool hn_is_leaf(const huffman_node_t *hn) { return !(hn->left || hn->right); }

int hn_compare(const huffman_node_t *v1, const huffman_node_t *v2) {
  if (v1->weight < v2->weight)
    return -1;
  if (v1->weight == v2->weight)
    return 0;
  return 1;
}

huffman_node_t *hn_combine(huffman_node_t *v1, huffman_node_t *v2) {
  return hn_init('\0', v1->weight + v2->weight, v1, v2);
}

huffman_node_t *hn_create_tree(priority_queue_t *chq) {
  huffman_node_t *tmp1, *tmp2, *tmp3;

  while (pq_size(chq) > 1) {
    tmp1 = pq_delete_min(chq);
    tmp2 = pq_delete_min(chq);
    tmp3 = hn_combine(tmp1, tmp2);

    pq_insert(chq, tmp3);
  }
  return tmp3;
}

void hn_print(const huffman_node_t *hn) {
  if (!hn) {
    return;
  }

  if (hn_is_leaf(hn)) {
    printf("%lc (%u): %zu\n", (wchar_t)hn->element, hn->element, hn->weight);
    return;
  }

  hn_print(hn->left);
  hn_print(hn->right);
}

static void hn_assign_codes_aux(huffman_node_t *hn, vector *codes,
                                unsigned rsf) {
  if (!hn) {
    return;
  }

  if (hn_is_leaf(hn)) {
    v_set(codes, hn->element, rsf);
    return;
  }

  assert(hn->element == '\0');

  hn_assign_codes_aux(hn->left, codes, rsf << 1);
  hn_assign_codes_aux(hn->right, codes, (rsf << 1) + 1);
}

void hn_assign_codes(huffman_node_t *hn, vector *codes) {
  hn_assign_codes_aux(hn, codes, 1);
}

void hn_free(huffman_node_t *hn) {
  if (!hn)
    return;
  hn_free(hn->left);
  hn_free(hn->right);
  free(hn);
}
