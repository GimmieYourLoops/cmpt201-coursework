#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  char *buffer = NULL;
  size_t len = 0;
  char **bufferarray = malloc(5 * sizeof(char *));
  int count = 0;

  while (1) {
    printf("Enter input: ");
    ssize_t userinput = getline(&buffer, &len, stdin);
    if (userinput < 0) {
      free(buffer);
      perror("Getline failed.");
      exit(EXIT_FAILURE);
    } else if (userinput > 0 && buffer[userinput - 1] == '\n') {
      buffer[userinput - 1] = '\0';
      if (count == 5) {
        for (int i = 1; i < 5; i++) {
          bufferarray[i - 1] = bufferarray[i];
        }
        bufferarray[count - 1] = strdup(buffer);
      } else {
        bufferarray[count] = strdup(buffer);
        count++;
      }
      if (strcmp(buffer, "print") == 0) {
        for (int i = 0; i < count; i++) {
          printf("%s\n", bufferarray[i]);
          bufferarray[i] = NULL;
        }
        count = 0;
      }
    }
  }
  for (int i = 0; i < 5; i++) {
    free(bufferarray[i]);
  }
  free(bufferarray);
}
