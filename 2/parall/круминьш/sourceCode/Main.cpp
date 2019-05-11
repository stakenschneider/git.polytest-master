#include <stdio.h>
#include <ctime>
#include <fstream>
#include <omp.h>
#include <math.h>

#include "Tree.h"
#include "TreeUtils.h"

using namespace std;

double startTime, endTime;    // временные засечки

int log2(int n ){
	return int(log(n)/log(2));
}

void defaultSum(){
    tnode* tree = importTreeFromFile();
   
    startTime = omp_get_wtime();
    unsigned long long sum = getSumOfAllChilds(tree);
    endTime = omp_get_wtime();
    
    printf("[Default] Time: %lf\n", endTime - startTime);
    printf("[Default] Sum: %llu\n", sum);
}

void pthreadSum(){
    tnode* tree = importTreeFromFile();
       
    int threads = omp_get_num_procs(); 
    unsigned long long elementCount = getCountOfFile();
    printf("Threads: %i, count of elements: %llu\n", threads, elementCount);
    
    pthreadArg arg;
    arg.tree = tree;
    arg.threadCount = threads;
    
    startTime = omp_get_wtime();
    getSumOfAllChilds_Pthread((void *) &arg);
    endTime = omp_get_wtime();
        
    printf("[Pthread] Time: %lf\n", endTime - startTime);
    printf("[Pthread] Sum: %llu\n", arg.tree->sum);
}

void openMpSum(){
    tnode* tree = importTreeFromFile();
       
    int threads = omp_get_num_procs();
    unsigned long long elementCount = getCountOfFile();
    printf("Procs: %i, count of elements: %llu\n", threads, elementCount);
    
    omp_set_nested(1);
    omp_set_max_active_levels((log2(20)));
    
    startTime = omp_get_wtime();
    unsigned long long sum = getSumOfAllChilds_OpenMP(tree);
    endTime = omp_get_wtime();
    
    printf("[OpenMP] Time: %lf\n", endTime - startTime);
    printf("[OpenMP] Sum: %llu\n", sum);
}

int main(){
    tnode* tree = makeRandomTree();
    exportTreeToFile(tree);
	      
    defaultSum();
    openMpSum();
    pthreadSum();
    
    return 0;
}