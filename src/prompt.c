#include <stdio.h>
#include <stdlib.h> // free

#ifdef _WIN32
// on Win where ther's no readline
#include <string.h>

char* readline(char* prompt) {
  char input[2048];
  fputs(prompt, stdout);
  fgets(input, 2048, stdin);
  char* buffer = malloc(strlen(input) + 1);
  strcpy(buffer, input);
  buffer[strlen(input)-1] = '\0';
  return buffer;
}

void add_history(char* input) {}

#else
// on *nix
#include <editline/readline.h>

#if defined __unix__
  // only necessary on unix
  #include <editline/history.h>
#endif

#endif

int main(int argc, char** argv) {
  puts("Lispy version 0.0.0.0.1");
  puts("Press Ctrl-c to exit.\n");

  while (1) {
    char* input = readline("lispy> ");
    add_history(input);
    printf("No you're a %s\n", input);
    free(input);
  }
  return 0;
}

