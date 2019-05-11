#ifndef TEST_H
#define TEST_H

#include "tree.h"
#include <stdint.h>

static const int32_t EXPONENT_PRESISION = 4000;
static const int32_t EXPONENT_PERFORMANSE_RETRIES = 10;
static const char* EXPONENT_STATISTICS = "exponent.statistics";

static const uint32_t SMALL_TREE_PERFORMANSE_RETRIES = 20000;
static const char* SMALL_TREE_FILENAME = "small_tree";
static const char* SMALL_TREE_STATISTICS = "small_tree.statistics";

static const uint32_t AVERAGE_TREE_PERFORMANSE_RETRIES = 200;
static const char* AVERAGE_TREE_FILENAME = "average_tree";
static const char* AVERAGE_TREE_STATISTICS = "average_tree.statistics";

static const uint32_t BIG_TREE_PERFORMANSE_RETRIES = 2;
static const char* BIG_TREE_FILENAME = "big_tree";
static const char* BIG_TREE_STATISTICS = "big_tree.statistics";

// Utils.

int initTests(int argc, char** argv);
void printStatistics(const char* statisticsFile);
void setSingleCoreCpuMode();
void delay();
tree parseTreeFromResourceFile(const char* filename);
long double getExponentSimple(int32_t presision);

#ifdef MPI_ENABLED
long double getExponentMpi(int32_t presision);
#endif

// Tests.

#ifdef MPI_ENABLED
void testMpiPerformance();
void testMpiStatistics();
#endif

void testSmallTreeSingleEquality();
void testAverageTreeSingleEquality();
void testBigTreeSingleEquality();

void testSmallTreeDoubleEquality();
void testAverageTreeDoubleEquality();
void testBigTreeDoubleEquality();

void testSmallTreePerformance();
void testAverageTreePerformance();
void testBigTreePerformance();

void testSmallTreeStatistics();
void testAverageTreeStatistics();
void testBigTreeStatistics();

#endif /* TEST_H */

