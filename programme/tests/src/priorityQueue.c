#include "priorityQueue.h"

#include "main.h"

#include "CUnit/Basic.h"

void test_priority_queue_create() {

    PriorityQueue pq = priority_queue_create();
    CU_ASSERT_FALSE(pq.length);
}

void test_priority_queue_get_length() {

    PriorityQueue pq = priority_queue_create();
    HuffmanTree a = huffman_tree_new_leaf('a', 1);
    HuffmanTree b = huffman_tree_new_leaf('b', 2);
    priority_queue_push(&pq, a);
    priority_queue_push(&pq, b);
    CU_ASSERT_EQUAL(priority_queue_get_length(&pq), 2);
    huffman_tree_delete(priority_queue_pop((&pq)));
    CU_ASSERT_EQUAL(priority_queue_get_length(&pq), 1);
    huffman_tree_delete(priority_queue_pop((&pq)));
    CU_ASSERT_EQUAL(priority_queue_get_length(&pq), 0);
}

void test_priority_queue_push_and_pop() {
    HuffmanTree a = huffman_tree_new_leaf('a', 2);
    PriorityQueue pq = priority_queue_create();
    priority_queue_push(&pq, a);
    CU_ASSERT_EQUAL(priority_queue_get_length(&pq), 1);
    HuffmanTree ht = priority_queue_pop(&pq);
    CU_ASSERT_EQUAL(ht, a);
    CU_ASSERT_EQUAL(priority_queue_get_length(&pq), 0);
    huffman_tree_delete(ht);

}

void test_priority_queue_sort() {
    PriorityQueue pq = priority_queue_create();
    for (int i = 0; i < 100; i++) {
        HuffmanTree ht = huffman_tree_new_leaf('a', i);
        priority_queue_push(&pq, ht);   // Ajout de nœud avec un poids croissant pour forcer le triage
    }
    CU_ASSERT_EQUAL(priority_queue_get_length(&pq), 100);
    for (int i = 0; i < 100; i++) {
        HuffmanTree ht = priority_queue_pop(&pq);
        CU_ASSERT_EQUAL(huffman_tree_get_weight(ht), i);    // Vérification le défilement renvoie les nœuds dans l'ordre croissant
        huffman_tree_delete(ht);
    }
    CU_ASSERT_EQUAL(priority_queue_get_length(&pq), 0);
    for (int i = 0; i < 100; i++) {
        HuffmanTree ht = huffman_tree_new_leaf(i, 0xABCD);
        priority_queue_push(&pq, ht);   // Ajout de nœud avec une valeur croissante pour forcer le triage
    }
    CU_ASSERT_EQUAL(priority_queue_get_length(&pq), 100);
    for (int i = 0; i < 100; i++) {
        HuffmanTree ht = priority_queue_pop(&pq);
        CU_ASSERT_EQUAL(huffman_tree_get_value(ht), i);    // Vérification le défilement renvoie les nœuds dans l'ordre croissant
        huffman_tree_delete(ht);
    }
    CU_ASSERT_EQUAL(priority_queue_get_length(&pq), 0);
}

void priority_queue_add_tests()
{
    CU_pSuite suite = CU_add_suite("PriorityQueue", NULL, NULL);
    CU_add_test(suite, "test_priority_queue_create", test_priority_queue_create);
    CU_add_test(suite, "test_priority_queue_get_length", test_priority_queue_get_length);
    CU_add_test(suite, "test_priority_queue_push_and_pop", test_priority_queue_push_and_pop);
    CU_add_test(suite, "test_priority_queue_sort", test_priority_queue_sort);
}
