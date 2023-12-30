/**
 * @file statistique.c
 * fichier de test du TAD Statistique
*/

#include "statistics.h"

#include "main.h"

#include "CUnit/Basic.h"

/**
 * @fn void test_statistics_statistics()
 * @brief fonction qui test statistics
*/
void test_statistics_statistics() {
    Statistics s;
    statistics_initialize(s);
    for (int i = 0; i < STATISTICS_MAX; i++) {
        CU_ASSERT_EQUAL(statistics_get_count(&s, i), 0);
    }
}

void test_statistics_get_count() {
    Statistics s;
    statistics_initialize(s);
    statistics_set_count(&s, 0, 1);
    CU_ASSERT_EQUAL(statistics_get_count(&s, 0), 1);
}

void test_statistics_set_count() {
    Statistics s;
    statistics_initialize(s);
    statistics_set_count(&s, 0, 1);
    CU_ASSERT_EQUAL(statistics_get_count(&s, 0), 1);
}

void test_statistics_increase_count() {
    Statistics s;
    statistics_initialize(s);
    statistics_increase_count(&s, 0);
    CU_ASSERT_EQUAL(statistics_get_count(&s, 0), 1);
}

void test_statistics_serialization() {
    Statistics s;
    statistics_initialize(s);
    statistics_set_count(&s, 0, 1);
    unsigned char* buffer[sizeof(Statistics)];
    statistics_serialize(s, buffer, STATISTICS_MAX);
    Statistics s2;
    statistics_deserialize(s2, buffer);
    CU_ASSERT_EQUAL(statistics_get_count(&s2, 0), 1);
}

/**
 * @fn void statistics_add_tests()
 * @brief fonction qui ajoute tout les tests pour les tester
*/
void statistics_add_tests()
{
    CU_pSuite suite = CU_add_suite("statistics", NULL, NULL);
    CU_add_test(suite, "test_statistics_statistics", test_statistics_statistics);
    CU_add_test(suite, "test_statistics_get_count", test_statistics_get_count);
    CU_add_test(suite, "test_statistics_set_count", test_statistics_set_count);
    CU_add_test(suite, "test_statistics_increase_count", test_statistics_increase_count);
    CU_add_test(suite, "test_statistics_serialization", test_statistics_serialization);
}
