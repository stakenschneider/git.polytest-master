#include <stdio.h>
#include <fstream>
#include <iostream>

#include "Tree.h"

using namespace std;

/* Добавить узел */
tnode* addNode(unsigned long long v, tnode *tree)
{
	// Если дерева нет, то формируем корень
	if (tree == NULL)
	{
		tree = new tnode;		// память под узел
		tree->value = v;		// значение
		tree->sum = 0;			// сумма дочерних
		tree->left = NULL;		// ветви инициализируем пустотой
		tree->right = NULL;
	}
	else if (v < tree->value)	// условие добавление левого потомка
		tree->left = addNode(v, tree->left);
	else if(v > tree->value)
		tree->right = addNode(v, tree->right);
	return(tree);
}
