#ifndef HUFFMAN_TREE_HEADER
#define HUFFMAN_TREE_HEADER

#include "../include/vector.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct priority_queue_t priority_queue_t;
struct priority_queue_t;

typedef struct huffman_node_t huffman_node_t;
struct huffman_node_t;

/**
 * @brief Create a huffman node tree
 *
 * @param el the element of the node
 * @param wt the weight of the node
 * @param l a pointer to the left sub-tree of the node
 * @param r a pointer to the right sub-tree of the node
 * @return A pointer to the allocated node
 */
huffman_node_t *hn_init(wchar_t el, size_t wt, huffman_node_t *l,
                        huffman_node_t *r);

/**
 * @brief Create a huffman node array
 *
 * Creates an array of nodes of the given size
 *
 * @param size The size of the initailized array
 * @return A pointer to the new array
 */
huffman_node_t *hn_init_array(size_t size);

/**
 * @brief Getter for nodes in arrays
 *
 * Fetches a Huffman node from the given array based on the index provided.
 *
 * @param hn the huffman node
 * @param index the index of the element to retreive
 * @return A pointer to the the node at the given index
 */
huffman_node_t *hn_array_get(huffman_node_t *hn, size_t index);

/**
 * @brief Getter for node element
 *
 * Return the element (symbol) of the given node
 *
 * @param hn A pointer to the node
 * @return The element of the node
 */
wchar_t hn_element(huffman_node_t *hn);

/**
 * @brief Getter for node weight
 *
 * Returns the weight (frequency) of the given node
 *
 * @param hn A pointer to the node
 * @return The weight of the node
 */
size_t hn_weight(huffman_node_t *hn);

/**
 * @brief Getter for node left
 *
 * Retrieves the left child node of a Huffman node.
 *
 * @param hn A pointer to the node
 * @return The left of the node
 */
huffman_node_t *hn_left(huffman_node_t *hn);

/**
 * @brief Getter for node right
 *
 * Retreives a pointer to the right node
 *
 * @param hn A pointer to the node
 * @return The right of the node
 */
huffman_node_t *hn_right(huffman_node_t *hn);

/**
 * @brief Copy the source node into the destination node *
 *
 * Copies the entire source node including the left nodes and right nodes
 * recursively
 *
 * @param dest The destination to which the source node is copied
 * @param src The tree to copy entirely
 */
void hn_copy(huffman_node_t *dest, const huffman_node_t *src);

/**
 * @brief Check if a node is a leaf
 *
 * A node is considered a leaf when it has neither left nor right sub-trees
 *
 * @param hn The tree to check against
 * @return `true` if it's a leaf
 */
bool hn_is_leaf(const huffman_node_t *hn);

/**
 * @brief Compares the given nodes
 *
 * Compare the nodes depending on the weights
 *
 * @param v1 a pointer to the first node
 * @param v2 a pointer to the second node
 * @return 1 if the weight of `v1` is greater than `v2`, 0 if they are equal, -1
 * if the weight of `v1` is less than `v2`.
 */
int hn_compare(const huffman_node_t *v1, const huffman_node_t *v2);

/**
 * @brief creates a new tree with given children
 *
 * The new node has no element '\0', the paramaters as their children and a
 * weight equal to the sum of the nodes
 *
 * @param v1 The left node of the created tree
 * @param v1 The right node of the created tree
 * @return A pointer to the newly created tree
 */
huffman_node_t *hn_combine(huffman_node_t *v1, huffman_node_t *v2);

/**
 * @brief Constructs a standard huffman tree
 *
 * A standard huffman tree is built using a priority queue that has all the
 * nodes and constructs a tree that gives less depth to the nodes with higher
 * Using a min priority queue, We keep combining the first two nodes in the
 * priority queue until one remains
 *
 * @param pq The priority queue that has all the nodes @return a pointer to the
 * huffman tree */
huffman_node_t *hn_create_tree(priority_queue_t *pq);

/**
 * @brief Assigns uniques codes to each leaf in the tree and placing them the
 * given vector
 *
 * A code is assigned depending on the unique path to each node. By going left,
 * 0 is appended. By going right, 1 is appended
 * To get around leftmost zeros value getting lost, A 1 is prefixed into each
 * code and must be dealth with later
 * @param The tree used to assign codes and a vector to assign codes to
 */
void hn_assign_codes(huffman_node_t *hn, vector *codes);

/**
 * @brief
 * print all element of the leaves in a huffman tree
 * @param hn a pointer to a huffman tree
 */
void hn_print(const huffman_node_t *hn);

/**
 * @brief free a huffman node
 *
 * The left and right nodes must be recursively freed first
 * @param hn The pointer to the tree to free
 */
void hn_free(huffman_node_t *hn);
#endif
