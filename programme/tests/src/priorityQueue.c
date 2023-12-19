#include "priorityQueue.h"

#include "main.h"

#include "CUnit/Basic.h"

void test_priority_queue_create() {

    PriorityQueue pq = PriorityQueue_create();
    CU_ASSERT_PTR_NULL(pq.nodes);
    CU_ASSERT_FALSE(pq.length);
}

void test_priority_queue_get_length() {

    PriorityQueue pq = PriorityQueue_create();
    HuffmanTree a = huffman_tree_new_leaf('a', 1);
    HuffmanTree b = huffman_tree_new_leaf('b', 2);
    PriorityQueue_push(&pq, a);
    PriorityQueue_push(&pq, b);
    CU_ASSERT_EQUAL(PriorityQueue_get_length(&pq), 2);
    PriorityQueue_pop(&pq);
    CU_ASSERT_EQUAL(PriorityQueue_get_length(&pq), 1);

}

void test_priority_queue_push_and_pop() {

    PriorityQueue pq;
    pq = PriorityQueue_create();
    HuffmanTree a = huffman_tree_new_leaf('a', 2);
    int length_before = pq.length;
    PriorityQueue_push(&pq, a);
    CU_ASSERT_EQUAL(PriorityQueue_get_length(&pq)-length_before, 1);
    length_before = pq.length;
    HuffmanTree ht = PriorityQueue_pop(&pq);
    CU_ASSERT_EQUAL(ht, a);
    CU_ASSERT_EQUAL(PriorityQueue_get_length(&pq)-length_before, -1);

}

void priorityQueue_add_tests()
{
    CU_pSuite suite = CU_add_suite("PriorityQueue", NULL, NULL);
    CU_add_test(suite, "test_priority_queue_create", test_priority_queue_create);
    CU_add_test(suite, "test_priority_queue_get_length", test_priority_queue_get_length);
    CU_add_test(suite, "test_priority_queue_push_and_pop", test_priority_queue_push_and_pop);
}