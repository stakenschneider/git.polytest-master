#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t pid;
  int rv;
  switch(pid=fork()) {
  case -1:
          perror("fork"); /* произошла ошибка */
          exit(1); /*выход из родительского процесса*/
  case 0:
          printf(" CHILD: Это процесс потомок!\n");
          printf(" CHILD: Мой PID %d\n", getpid());
          printf(" CHILD: PID моего родителя %d\n",getppid());
          printf(" CHILD: Выход!\n");
          exit(rv);
  default:
          printf("PARENT: Это процесс родитель!\n");
          printf("PARENT: Мой PID %d\n", getpid());
          printf("PARENT: PID моего потомка %d\n",pid);
          printf("PARENT: Я жду, пока потомок не вызовет exit()...\n");
          wait(&rv);
          printf("PARENT: Код возврата потомка:%d\n", WEXITSTATUS(rv));
          printf("PARENT: Выход!\n");
  }
}