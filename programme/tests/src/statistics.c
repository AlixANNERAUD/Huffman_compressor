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
    Statistics s = statistics_create();
}

/**
 * @fn void statistics_add_tests()
 * @brief fonction qui ajoute tout les tests pour les tester
*/
void statistics_add_tests()
{
    CU_pSuite suite = CU_add_suite("statistics", NULL, NULL);
    CU_add_test(suite, "test_statistics_statistics", test_statistics_statistics);
}
