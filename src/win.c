#include "win.h"

/* fake readline */
char* readline(char* prompt) {
  char input[2048];
  fputs(prompt, stdout);
  fgets(input, 2048, stdin);
  char* buffer = malloc(strlen(input) + 1);
  strcpy(buffer, input);
  buffer[strlen(input)-1] = '\0';
  return buffer;
}

/* fake add history of readline */
void add_history(char* input) {}
