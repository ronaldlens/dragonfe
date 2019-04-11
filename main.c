#include <stdlib.h>
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

int load_file(char *filename) {
	char *buffer = 0;
	long length;
	fp = fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "Cannot open file %s.\n", filename);
		return 2;
	}

	fseek(fp,0, SEEK_END);
	length = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	buffer = malloc(length);
	if (!buffer) {
		fprintf(stderr, "Cannot allocate bufffer to read source\n");
		return 3;
	}
	fread(buffer, 1, length, fp);
	fclose(fp);
	return 0;

}
int main(int argc, char *argv[])
{
	test_lex();

	if (argc == 1) {
		fprintf(stderr, "No arguments\n");
		return 1;
	}

	return load_file(argv[1]);
}