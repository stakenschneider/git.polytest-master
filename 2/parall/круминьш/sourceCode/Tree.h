#pragma once

#include <iostream>

using namespace std;

/* Структура бинарного дерева*/
struct tnode
{
	unsigned long long value = 0;   // числовое значение
	unsigned long long sum = 0;	// сумма значений дочерних узлов 
	struct tnode *left = NULL;	// левый потомок
	struct tnode *right =NULL;	// правый потомок
};

/* Добавить узел */
tnode* addNode(unsigned long long v, tnode *tree);
