#ifndef PRIORITY_QUEUE_HEADER
#define PRIORITY_QUEUE_HEADER

#include "huffman_tree.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct priority_queue_t priority_queue_t;
struct priority_queue_t;

/**
 * @brief Construct a priority queue
 *
 * Create a priority queue with size 0
 * @return A pointer to the allocated queue
 */
priority_queue_t *pq_init();

/**
 * @brief A Getter for size
 *
 * @param pq A pointer to the priority queue
 * @return The size of the priority queue
 */
size_t pq_size(priority_queue_t *pq);

/**
 * @brief Check if the queue is empty
 *
 * @param pq A pointer to the priority queue
 * @return `true` if the queue is empty or false otherwise
 */
bool pq_is_empty(priority_queue_t *pq);

/**
 * @brief Insert an element in the queue
 *
 * The element must be placed at the correct position
 * @param pq A pointer to the priority queue to insert into
 * @param value The node to insert in the queue
 */
void pq_insert(priority_queue_t *pq, huffman_node_t *value);

/**
 * @brief pops the node with minimum weight and returns it
 * Must check against the size of the queue
 *
 * @param pq The queue that has the node to be returned
 */
huffman_node_t *pq_delete_min(priority_queue_t *pq);

/**
 * @brief free the queue
 *
 * @param the queue to delete
 */
void pq_free(priority_queue_t *pq);
#endif
