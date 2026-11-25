#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
int check_arguments(int argc, char *argv[])
{
	if (argc < 6) {
		return 1;
	}
	if (strcmp(argv[argc - 2], "-k") != 0) {
		return 1;
	}
	if ((argc - 3) % 3 != 0) {
		return 1;
	}
	if ((atoi(argv[argc - 1]) > 0) && (atoi(argv[argc - 1]) < 1024) == 0) {
		return 1;
	}
	return 0;
}
int calculate(const int left_arg, const char operation, const int right_arg)
{
	switch (operation) {
		case '+':
			return left_arg + right_arg;
		case '-':
			return left_arg - right_arg;
		case '*':
			return left_arg * right_arg;
		case '%':
			return left_arg % right_arg;
		default:
			return -1;
		}
}
void decrypted(int *answers, const int count_examples, const int key, char *text)
{
	for (int i = 0; i < count_examples; i++) {
		text[i] = (char)(answers[i] - key); 
	}
	text[count_examples] = '\0';
}
int main(int argc, char *argv[])
{
	if (check_arguments(argc, argv) == 1){
		return 1;
	}
	const int count_examples = (argc - 3) / 3;
	const int key = atoi(argv[argc - 1]);
	int *answers = malloc(count_examples *sizeof(int));
	char *text = malloc(count_examples + 1);
	for (int i = 0; i < count_examples; i++){
		int left = atoi(argv[1 + i*3]);
		char operation = argv[2 + i*3][0];
		int right = atoi(argv[3 + i*3]);
		answers[i] = calculate(left, operation, right);
		if (answers[i] == -1)
		{
			free(answers);
			free(text);
			return 1;
		}
		printf("Answer: %d: %d\n", i+1, answers[i]);
	}
	decrypted(answers, count_examples, key, text);
	printf("Result: %s\n", text);
	free(answers);
	free(text);
	fflush(stdout);
	return 0;
}

