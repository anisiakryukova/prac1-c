#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
 
int main(int argc, char **argv)
{
    if (checkCmdArgs(argc, argv) == 1)
    {
        return 1;
    }
 
    int status = 1;
    int expr_count = (argc - 3) / 3;
    int *answers = calloc((size_t)expr_count, sizeof(int));
    char *out_str = calloc((size_t)expr_count + 1, sizeof(char));
    int key = 0;
 
    if (answers == NULL || out_str == NULL)
    {
        fprintf(stderr, "ошибка выделения памяти\n");
        goto cleanup;
    }
    if (strToIntStrict(argv[argc - 1], &key) == 1)
    {
        goto cleanup;
    }
    if (evalExpressions(argc, argv, answers) == 1)
    {
        goto cleanup;
    }
    if (showOutput(argc, answers, out_str, key) == 1)
    {
        goto cleanup;
    }
 
    status = 0;
 
cleanup:
    free(answers);
    free(out_str);
    return status;
}

