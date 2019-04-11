//
// Created by Ronald Lens on 2019-04-11.
//

#ifndef DRAGONFE_LEX_H
#define DRAGONFE_LEX_H

// token identifiers
#define TOK_NUM 256
#define TOK_ID 257
#define TOK_TRUE 258
#define TOK_FALSE 259

// reserved word structure
typedef struct Token {
	int token_id;
	union {
		int as_int;
		char *as_string;
	} value;
} Token;

typedef struct Word {
	char *lexeme;
	Token *token;
	struct Word *next;
} Word;

void token_init_words(void);
Token *token_get_word(char *lexeme);
Token *token_add_str(int token_id, char *value);
void token_free_words();

#endif //DRAGONFE_LEX_H
