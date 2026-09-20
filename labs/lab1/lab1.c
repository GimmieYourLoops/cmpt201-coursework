#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  size_t len = 0;
  char *buffer = NULL;
  char *delimiter = " ";
  char *ptr = NULL;
  printf("Please input a message: ");
  ssize_t charsread = getline(&buffer, &len, stdin);
  if (charsread == -1) {
    perror("Getline Failed\n");
    exit(EXIT_FAILURE);
  }
  char *token = strtok_r(buffer, delimiter, &ptr);
  while (token != NULL) {
    printf("%s\n", token);
    token = strtok_r(NULL, delimiter, &ptr);
  }
  free(buffer);
}

/*
 Take input from user
 break getline into tokens (ie individual words)
 probably in that same process (iterative?)
 printf individual tokens
 */
