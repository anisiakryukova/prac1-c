#ifndef CALC_H
#define CALC_H
 
/* Переводит строку в int; при ошибке возвращает 1, при успехе 0 */
int strToIntStrict(const char *src, int *out_val);
 
/* Проверяет количество аргументов, флаг -k и ключ */
int checkCmdArgs(int argc, char **argv);
 
/* Считает одно выражение (first op second) и пишет ответ в out_res */
int calcSingle(int first, int second, const char *op, int *out_res);
 
/* Проходит по всем выражениям и заполняет массив ответов */
int evalExpressions(int argc, char **argv, int *answers);
 
/* Выводит ответы и собранную из них строку с учётом ключа key */
int showOutput(int argc, const int *answers, char *out_str, int key);
 
#endif

