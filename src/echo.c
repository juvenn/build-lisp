#include <stdio.h>
#include <stdlib.h> // free

#ifdef _WIN32

#include <string.h>
#include "win.h"

#else

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

