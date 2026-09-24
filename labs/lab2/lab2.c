#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  while (1) {
    char *buffer = NULL;
    size_t len = 0;
    printf("Enter programs to run.\n> ");
    ssize_t pathinput = getline(&buffer, &len, stdin);
    if (pathinput == -1) {
      free(buffer);
      perror("Getline Failed");
      exit(EXIT_FAILURE);
    } else if (pathinput > 0 && buffer[pathinput - 1] == '\n') {
      buffer[pathinput - 1] = '\0';
    }
    pid_t childpid = fork();
    if (childpid == 0) {
      execl(buffer, buffer, NULL);
    } else {
      int status;
      waitpid(childpid, &status, 0);
    }

    free(buffer);
  }
}
