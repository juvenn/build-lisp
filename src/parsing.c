#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

#ifdef _WIN32

#include "win.h"

#else

#include <editline/readline.h>
#if defined __unix__
  // only necessary on unix
  #include <editline/history.h>
#endif

#endif


int main(int argc, char** argv) {
  /* Create polish notation calc parser */
  mpc_parser_t* Number   = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr     = mpc_new("expr");
  mpc_parser_t* Lispy    = mpc_new("lispy");
  
  /* Define language */
  mpca_lang(MPCA_LANG_DEFAULT,
            "                                                  \
            number   : /-?[0-9]+(\\.[0-9]+)?/ ;                \
            operator : '+' | '-' | '*' | '/' | '%' |           \
                       \"add\" | \"sub\" | \"mul\" | \"div\" ; \
            expr     : <number> | '(' <operator> <expr>+ ')' ; \
            lispy    : /^/ <operator> <expr>+ /$/ ;            \
            ",
            Number, Operator, Expr, Lispy);


  puts("Lispy version 0.0.0.0.1");
  puts("Press Ctrl-c to exit.\n");

  while (1) {
    char* input = readline("lispy> ");
    add_history(input);

    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      /* print AST on success */
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      /* print error on failure */
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  }
  mpc_cleanup(4, Number, Operator, Expr, Lispy);
  return 0;
}

