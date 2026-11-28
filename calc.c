#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"
 
int strToIntStrict(const char *src, int *out_val)
{
    char *tail = NULL;
    errno = 0;
    long num = strtol(src, &tail, 10);
 
    if (errno == ERANGE || num < INT_MIN || num > INT_MAX)
    {
        fprintf(stderr, "выход за пределы int\n");
        return 1;
    }
    if (tail == src || *tail != '\0')
    {
        return 1;
    }
    if (out_val != NULL)
    {
        *out_val = (int)num;
    }
    return 0;
}
 
int checkCmdArgs(int argc, char **argv)
{
    /* Минимум: имя программы + 3 аргумента выражения + "-k" + ключ = 6 */
    int expr_span = argc - 3;
    if (argc < 6 || expr_span <= 0 || expr_span % 3 != 0)
    {
        fprintf(stderr, "неверное число аргументов\n");
        return 1;
    }
    if (strcmp(argv[argc - 2], "-k") != 0)
    {
        fprintf(stderr, "ожидался флаг -k\n");
        return 1;
    }
    if (strToIntStrict(argv[argc - 1], NULL) == 1)
    {
        fprintf(stderr, "некорректный ключ дешифрования\n");
        return 1;
    }
    return 0;
}
 
int calcSingle(int first, int second, const char *op, int *out_res)
{
    long long acc = 0;
 
    if (strcmp(op, "+") == 0)
    {
        acc = (long long)first + (long long)second;
    }
    else if (strcmp(op, "-") == 0)
    {
        acc = (long long)first - (long long)second;
    }
    else if (strcmp(op, "*") == 0)
    {
        acc = (long long)first * (long long)second;
    }
    else if (strcmp(op, "%") == 0)
    {
        if (second == 0 || (first == INT_MIN && second == -1))
        {
            fprintf(stderr, "ошибка в операции %%\n");
            return 1;
        }
        acc = (long long)first % (long long)second;
    }
    else
    {
        fprintf(stderr, "неизвестный оператор\n");
        return 1;
    }
 
    if (acc < INT_MIN || acc > INT_MAX)
    {
        fprintf(stderr, "переполнение результата\n");
        return 1;
    }
 
    if (out_res != NULL)
    {
        *out_res = (int)acc;
    }
    return 0;
}
 
int evalExpressions(int argc, char **argv, int *answers)
{
    int count = (argc - 3) / 3;
    int idx = 0;
 
    for (int pos = 1; pos < argc - 2; pos += 3)
    {
        int lhs = 0;
        int rhs = 0;
        int res = 0;
 
        if (strToIntStrict(argv[pos], &lhs) == 1 || strToIntStrict(argv[pos + 2], &rhs) == 1)
        {
            fprintf(stderr, "некорректный операнд\n");
            return 1;
        }
        if (calcSingle(lhs, rhs, argv[pos + 1], &res) == 1)
        {
            return 1;
        }
        answers[idx++] = res;
    }
 
    if (idx != count)
    {
        return 1;
    }
    return 0;
}
 
int showOutput(int argc, const int *answers, char *out_str, int key)
{
    int count = (argc - 3) / 3;
 
    for (int i = 0; i < count; ++i)
    {
        printf("Ответ №%d: %d\n", i + 1, answers[i]);
        out_str[i] = (char)(answers[i] - key);
    }
    out_str[count] = '\0';
 
    printf("Результирующая строка: %s\n", out_str);
    return 0;
}

