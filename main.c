#include <stdio.h>
#include "lex.h"

FILE *fp;

void test_lex() {
	token_init_words();

	Token *token = token_get_word("true");
	printf("found %s\n", token->value.as_string);
	token_add_str(TOK_ID, "test1");
	token_add_str(TOK_ID, "test2");
	token_add_str(TOK_ID, "test3");
	token = token_get_word("test2");
	printf("found token %d with %s\n", token->token_id, token->value.as_string);
	token_free_words();
	token = token_get_word("true");
	if (token == NULL) {
		printf("word list emptied\n");
	}
}

int main(int argc, char *argv[])
{
	test_lex();
	return 0;

	if (argc == 1) {
		fprintf(stderr, "No arguments\n");
		return 1;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "Cannot open file %s.\n", argv[1]);
		return 2;
	}

	fclose(fp);
	return 0;
}