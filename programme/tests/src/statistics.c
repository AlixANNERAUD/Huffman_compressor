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
void test_statistics_statistics()
{
    Statistics s;
    statistics_initialize(s);
    for (int i = 0; i < STATISTICS_MAX; i++)
    {
        CU_ASSERT_EQUAL(statistics_get_count(s, i), 0);
    }
}

void test_statistics_count()
{
    Statistics s;
    statistics_initialize(s);
    for (unsigned int i = 0; i < STATISTICS_MAX; i++)
        for (unsigned int j = 0; j <= 0xFFFF - i; j++)
            statistics_increment_count(s, byte_create(i));

    for (unsigned int i = 0; i < STATISTICS_MAX; i++)
        CU_ASSERT_EQUAL(statistics_get_count(s, byte_create(i)), 0xFFFF - i + 1)
}

void test_statistics_serialization()
{
    Statistics s;
    statistics_initialize(s);
    for (unsigned int i = 0; i < 0xFF; i++)
        for (unsigned int j = 0; j < 0xFF - i; j++)
            statistics_increment_count(s, byte_create(i));
    unsigned char buffer[sizeof(Statistics) + sizeof(FileSize)];
    statistics_serialize(s, buffer, sizeof(buffer));
    Statistics s2;
    statistics_initialize(s2);
    CU_ASSERT(statistics_deserialize(s2, buffer));
    FileSize Sum = 0;
    for (unsigned int i = 0; i < 0xFF; i++) {
        CU_ASSERT_EQUAL(statistics_get_count(s2, byte_create(i)), 0xFF - i);
        Sum += 0xFF - i;
    }
    CU_ASSERT_EQUAL(statistics_get_total_count(s2), Sum);
}

/**
 * @fn void statistics_add_tests()
 * @brief fonction qui ajoute tout les tests pour les tester
 */
void statistics_add_tests()
{
    CU_pSuite suite = CU_add_suite("statistics", NULL, NULL);
    CU_add_test(suite, "test_statistics_statistics", test_statistics_statistics);
    CU_add_test(suite, "test_statistics_count", test_statistics_count);
    CU_add_test(suite, "test_statistics_serialization", test_statistics_serialization);
}
