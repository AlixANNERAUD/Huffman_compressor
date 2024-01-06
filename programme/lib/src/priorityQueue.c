#include "priorityQueue.h"

PriorityQueue priority_queue_create()
{
    PriorityQueue priorityQueue;
    priorityQueue.length = 0;
    return priorityQueue;
}

size_t priority_queue_get_length(const PriorityQueue *priorityQueue)
{
    return priorityQueue->length;
}

HuffmanTree priority_queue_pop(PriorityQueue *priorityQueue)
{
    // Préconditions
    assert(priorityQueue->length > 0);
    HuffmanTree node = priorityQueue->nodes[--priorityQueue->length]; // On récupère le dernier élément de la file tout en décrémentant la taille de la file
    return node;
}

void priority_queue_push(PriorityQueue *priorityQueue, HuffmanTree node)
{
    // - Préconditions                                      // Pointeur non nul
    assert(priorityQueue->length < PRIORITY_QUEUE_MAXIMUM_SIZE); // File non pleine
    int i = priorityQueue->length; // On commence par la fin car on devra probablement décaler les éléments vers la fin de la file.
    // - On décale les éléments de la file pour insérer le nouvel élément
    while (huffman_tree_greater_than(node, priorityQueue->nodes[i - 1]) && i > 0)
    {
        priorityQueue->nodes[i] = priorityQueue->nodes[i - 1];
        i--;
    }
    // - On insère le nouvel élément
    priorityQueue->nodes[i] = node;
    priorityQueue->length++;
}
