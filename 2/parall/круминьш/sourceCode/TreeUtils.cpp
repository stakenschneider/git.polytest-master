#include <ctime>
#include <fstream>
#include <omp.h>

#include "TreeUtils.h"

const char* EXTERNAL_FILE = "externalFile.txt";

/*
    Генерация случайного значения типа unsigned long long.

    Максимальный размер unsigned long long - FFFF FFFF FFFF FFFF 
    или 18 446 744 073 709 551 615. В treeUtils.h задана 
    константа максимального значения(4 294 967 295), для того, 
    чтобы несколько ограничить диапазон для генерации.
*/
unsigned long long llrand() {
    unsigned long long r = 0;

    /*
        Запись long long занимает 64 бита, а стандартный оператор 
        rand() позволяет генерировать значение лишь до 32767 (15 бит). 
        Для покрытия всех битовых значений, используется побитовый 
        сдвиг(15 раз за итерацию).

        По завершению цикла, биты полученного значения обрезаются, 
        в соответствии с максимальным значением.
    */
    for (int i = 0; i < 5; ++i) {
        r = (r << 15) | rand(); 
    }

    return r & MAX_VALUE;
}

tnode* makeRandomTree() {
    /* 
        Для равномерного распределения значений между ветками корня дерева,
        значение корня равно половине от максимального возможного случайного числа
    */ 
    tnode* tree = new tnode;
    tree->value = MAX_VALUE / 2; 

    srand(unsigned(time(NULL)));
    for (int i = 0; i < GENERATE_COUNT; i++) {
        unsigned long long random = llrand();
        addNode(random, tree);
    }

    printf("[+] Random tree generated\n");
    return tree;
}

void writeBinaryTree(tnode *tree, ostream &out) {
	if (!tree) {
		out << "# ";
	}
	else {
		out << tree->value << " ";
		writeBinaryTree(tree->left, out);
		writeBinaryTree(tree->right, out);
	}
}

bool readNextNum(ifstream &fin, long long &num) {
    while (fin.peek() == ' ')
        fin.ignore();

    bool bNum = false;
    char c = fin.peek();
    if (c >= '0' && c <= '9') {
        fin >> num;
        bNum = true;
    }
    else
        fin.ignore();

    return bNum;
}

void readBinaryTree(tnode *&tree, ifstream &fin) {
    if (fin.eof())
        return;

    long long num;
    if (readNextNum(fin, num)){
        tree = new tnode;
        tree->value = num;
        readBinaryTree(tree->left, fin);
        readBinaryTree(tree->right, fin);
    }
}

void exportTreeToFile(tnode* tree) {
	filebuf fb;
	fb.open(EXTERNAL_FILE, ios::out);
	ostream out(&fb);

	writeBinaryTree(tree, out);
	
	printf("[+] Tree exported to file %s\n", EXTERNAL_FILE);
}

tnode* importTreeFromFile() {
    ifstream fin;
    fin.open(EXTERNAL_FILE, ios::in);

    tnode* tree;
    readBinaryTree(tree, fin);
    fin.close();

    printf("[+] Tree imported from file %s\n", EXTERNAL_FILE);

    return tree;
}

unsigned long long getCountOfFile(){
    unsigned long long count = 0;
    
    ifstream fin;
    fin.open(EXTERNAL_FILE, ios::in);
    
    bool readingNum = false;
    while(fin.peek() != EOF){
        char c ;
        fin.get(c);
        if (c >= '0' && c <= '9') 
            readingNum = true;
        else if(readingNum){
            readingNum = false;
            count++;
        }
    }
        
    fin.close();
    return count;
}

unsigned long long getSumOfAllChilds(tnode* tree) {
	if (tree != NULL){
		unsigned long long leftSum = 0;
		unsigned long long rightSum = 0;

		if (tree->left != NULL) {
			tree->left->sum = getSumOfAllChilds(tree->left);
			leftSum = tree->left->sum + tree->left->value;
		}

		if (tree->right != NULL)
		{
			tree->right->sum = getSumOfAllChilds(tree->right);
			rightSum = tree->right->sum + tree->right->value;
		}

		return leftSum + rightSum;
	}
	return 0;
}

unsigned long long getSumOfAllChilds_OpenMP(tnode* tree) {
    if (tree != NULL) {
        unsigned long long leftSum = 0;
	unsigned long long rightSum = 0;
		
	if (omp_get_active_level() >= omp_get_max_active_levels())
            return getSumOfAllChilds(tree);

        #pragma omp parallel num_threads(2) 
        {
            #pragma omp sections
            {
                #pragma omp section 
                { 
                    // сумма потомков для левого поддерева
                    if (tree->left != NULL){
                        tree->left->sum = getSumOfAllChilds_OpenMP(tree->left);
                        leftSum = tree->left->sum + tree->left->value;
                    }
		}

		#pragma omp section 
		{ 
                    // сумма потомков для правого поддерева
                    if (tree->right != NULL){
                        tree->right->sum = getSumOfAllChilds_OpenMP(tree->right);
                        rightSum = tree->right->sum + tree->right->value;
                    }				
		} 
            }
	}
        return leftSum + rightSum;
    }
    return 0;
}

void* getSumOfAllChilds_Pthread(void *args){
    pthreadArg *arg = (pthreadArg *)args; 
	
    if (arg->tree != NULL){	
        unsigned long long leftSum = 0; 
	unsigned long long rightSum = 0;
		
	// Когда доступно 1 или менее потоков, используется метод без распараллеливания 
	if (arg->threadCount <= 1){
            arg->tree->sum = getSumOfAllChilds(arg->tree);
            return 0;
	}
        int leftJoinStatus, rightJoinStatus; // статус pthread_join
        int leftCreateStatus, rightCreateStatus;// статус завершения pthread_create

	// поток для левого поддерева
	pthread_t leftThread;
	pthreadArg leftArg;
	if (arg->tree->left != NULL){		
            leftArg.tree = arg->tree->left;
            leftArg.threadCount = arg->threadCount/2;
            leftCreateStatus = pthread_create(&leftThread, NULL, getSumOfAllChilds_Pthread, (void*) &leftArg);	
            if (leftCreateStatus != 0) {
                printf("[ERROR] Can't create thread. Status: %d\n", leftCreateStatus);
		exit(ERROR_CREATE_THREAD);
            }
	}

	// поток для правого поддерева
	pthread_t rightThread;
	pthreadArg rightArg;
	if (arg->tree->right != NULL){		
            rightArg.tree = arg->tree->right;
            rightArg.threadCount =  arg->threadCount/2;
            rightCreateStatus = pthread_create(&rightThread, NULL, getSumOfAllChilds_Pthread, (void*) &rightArg);	
            if (rightCreateStatus != 0) {
                printf("[ERROR] Can't create thread. Status: %d\n", rightCreateStatus);
		exit(ERROR_CREATE_THREAD);
            }
	}		
		
        // ожидание завершения потоков
	leftCreateStatus = pthread_join(leftThread, (void**)&leftJoinStatus);
	if (leftCreateStatus != SUCCESS) {
            printf("[ERROR] Can't join thread. Status: %d\n", leftCreateStatus);
            exit(ERROR_JOIN_THREAD);
	}
	if (arg->tree->left != NULL){
            arg->tree->left->sum = leftArg.tree->sum;
            leftSum = arg->tree->left->sum + arg->tree->left->value;
	}

	rightCreateStatus = pthread_join(rightThread, (void**)&rightJoinStatus);
	if (rightCreateStatus != SUCCESS) {
            printf("[ERROR] Can't join thread. Status: %d\n", rightCreateStatus);
            exit(ERROR_JOIN_THREAD);
	}
	if (arg->tree->right != NULL){
            arg->tree->right->sum = rightArg.tree->sum;
            rightSum = arg->tree->right->sum + arg->tree->right->value;
	}
		
	arg->tree->sum = leftSum + rightSum;
    }
    return 0;
}