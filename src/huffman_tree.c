#include "../include/huffman_tree.h"
#include "../include/priority_queue.h"
#include "../include/vector.h"

huffman_node_t *hn_init(wchar_t el, size_t wt, huffman_node_t *l,
                        huffman_node_t *r) {
  huffman_node_t *hn = (huffman_node_t *)malloc(sizeof(huffman_node_t));
  hn->element = el;
  hn->weight = wt;
  hn->left = l;
  hn->right = r;

  return hn;
}

void hn_copy(huffman_node_t *dest, const huffman_node_t *src) {
  dest->element = src->element;
  dest->weight = src->weight;
  dest->left = src->left;
  dest->right = src->right;
}

bool hn_is_leaf(huffman_node_t *hn) { return !(hn->left || hn->right); }

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

  while (chq->size > 1) {
    tmp1 = cihq_delete_min(chq);
    tmp2 = cihq_delete_min(chq);
    tmp3 = hn_combine(tmp1, tmp2);

    cihq_insert(chq, tmp3);
  }
  return tmp3;
}

void hn_print(const huffman_node_t *hn) {
  if (!hn)
    return;
  printf("%c(%d): %zu\n", hn->element, hn->element, hn->weight);
  hn_print(hn->left);
  hn_print(hn->right);
}

void hn_assign_codes_aux(huffman_node_t *hn, vector *codes, unsigned rsf) {
  if (!hn) {
    return;
  }

  if (hn_is_leaf(hn)) {
    v_set(codes, hn->element, rsf);
    return;
  }

  hn_assign_codes_aux(hn->left, codes, rsf << 1);
  hn_assign_codes_aux(hn->right, codes, (rsf << 1) + 1);
}
void hn_assign_codes(huffman_node_t *hn, vector *codes) {
  hn_assign_codes_aux(hn, codes, 0);
}
