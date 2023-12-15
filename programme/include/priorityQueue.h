#ifndef PIRIORITY_QUEUE_H_DEFINED
#define PIRIORITY_QUEUE_H_DEFINED

#include "common.h"

#define PRIORITY_QUEUE_MAXIMUM_SIZE 256

/// @brief Structure représentant une file de priorité.
typedef struct {
    /// @brief Noeuds de la file de priorité.
    int nodes[PRIORITY_QUEUE_MAXIMUM_SIZE];
    /// @brief Taille de la file de priorité.
    size_t length;
} PriorityQueue;

/// @brief Constructeur de file de priorité.
/// @return File de priorité vide.
PriorityQueue PriorityQueue_create();

/// @brief Retourne la taille de la file de priorité.
/// @param queue File de priorité
/// @return Taille de la file de priorité.
size_t PriorityQueue_get_length(const PriorityQueue *queue);

/// @brief Défile le dernier élément de la file de priorité.
/// @param queue File de priorité à défiler.
/// @return Dernier élément de la file de priorité.
int PriorityQueue_pop(PriorityQueue *queue);

/// @brief Enfile un élément dans la file de priorité.
/// @param queue File de priorité.
/// @param node Nœud à enfiler.
void PriorityQueue_push(PriorityQueue *queue, int node);



#endif // PIRIORITY_QUEUE_H_DEFINED