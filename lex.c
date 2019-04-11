//
// Created by Ronald Lens on 2019-04-11.
//
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"

// private variables
Word *word_list = NULL;

///////////////////////////////////////
// private functions
void token_add_reserve(char *lexeme, int token_id);
Word *token_get_free_ptr_of_wordlist(void);
void token_free_word(Word *word);

void token_add_reserve(char *lexeme, int token_id) {
	Word *word;
	word = token_get_free_ptr_of_wordlist();
	word->lexeme = strdup(lexeme);
	word->token = calloc(1, sizeof(Token));
	word->token->token_id = token_id;
	word->token->value.as_string = strdup(lexeme);
}

Word *token_get_free_ptr_of_wordlist(void) {
	if (word_list == NULL) {
		word_list = calloc(1,sizeof(Word));
		return word_list;
	}

	Word *word;
	word = word_list;
	while (word->next != NULL) {
		word = word->next;
	}
	word->next = calloc(1, sizeof(Word));
	return word->next;
}

///////////////////////////////////////
// public functions

void token_init_words(void) {
	token_add_reserve("true", TOK_TRUE);
	token_add_reserve("false", TOK_FALSE);
}


Token *token_get_word(char *lexeme) {
	Word *word;
	word = word_list;
	while(1) {
		if (word == NULL) {
			return NULL;
		}
		if (strcmp(lexeme, word->lexeme)==0) {
			return word->token;
		}
		word = word->next;
	}
}

Token *token_add_str(int token_id, char *value) {
	Word *word;
	word = token_get_free_ptr_of_wordlist();
	word->lexeme = strdup(value);
	word->token = calloc(1, sizeof(Token));
	word->token->token_id = token_id;
	word->token->value.as_string = strdup(value);
	return word->token;
}

void token_free_word(Word *word) {
	assert(word != NULL);
	free(word->lexeme);
	if (word->token->token_id != TOK_NUM) {
		free(word->token->value.as_string);
	}
	free(word->token);
	free(word);
}

void token_free_words() {
	Word *current = word_list;
	Word *next;
	while (current != NULL) {
		next = current->next;
		token_free_word(current);
		current = next;
	}
}