#include "priorityQueue.h"

PriorityQueue priority_queue_create() {
    PriorityQueue priorityQueue;
    priorityQueue.length = 0;
    return priorityQueue;
}

size_t priority_queue_get_length(const PriorityQueue *priorityQueue) {
    // Préconditions
    assert(priorityQueue != NULL);

    return priorityQueue->length;
}

HuffmanTree priority_queue_pop(PriorityQueue *priorityQueue) {
    // Préconditions
    assert(priorityQueue != NULL);
    assert(priorityQueue->length > 0);

    HuffmanTree node = priorityQueue->nodes[priorityQueue->length - 1];
    priorityQueue->length--;
    return node;
}

void priority_queue_push(PriorityQueue *priorityQueue, HuffmanTree node) {
    // Préconditions
    assert(priorityQueue != NULL);
    assert(priorityQueue->length < PRIORITY_QUEUE_MAXIMUM_SIZE);

    size_t i = priorityQueue->length;
    // On décale les éléments de la file pour insérer le nouvel élément
    // TODO : à revoir pour adapter au type arbre d'Huffman
    while (priorityQueue->nodes[i - 1] > node && i > 0) {
        priorityQueue->nodes[i] = priorityQueue->nodes[i - 1];
        i--;
    }
    
    priorityQueue->length++;
}
