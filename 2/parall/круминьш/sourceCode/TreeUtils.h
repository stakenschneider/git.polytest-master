#pragma once

#include "Tree.h"

/* Константы */
#define MAX_VALUE 0xFFFFFFFF        // 4 294 967 295 (максимальное значения для генерации)
#define GENERATE_COUNT 9999999     // количество генераций случайного числа
extern const char* EXTERNAL_FILE;   // внеший файл для экспорта и импорта дерева

#define SUCCESS 0
#define ERROR_CREATE_THREAD -1
#define ERROR_JOIN_THREAD   -2

struct pthreadArg {
    struct tnode *tree;
    int threadCount;
};

/* Прототипы функций */
tnode* makeRandomTree();
void exportTreeToFile(tnode* tree);
tnode* importTreeFromFile();
unsigned long long getCountOfFile();
unsigned long long getSumOfAllChilds(tnode* tree);
unsigned long long getSumOfAllChilds_OpenMP(tnode* tree);
void* getSumOfAllChilds_Pthread(void *args);