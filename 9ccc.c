/* Step 3 Tokenizer */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

/* Utility Types Declear */
typedef enum
{
	TK_RESERVED,	// signal
	TK_NUM,			// number
	TK_EOF,			// end of input
} TokenKind;

typedef struct Token Token;

struct Token
{
	TokenKind kind;
	Token *next;
	int val;		// number
	char *str;		// string
};

/* Valiables Declear */
Token *token;	// now seening token

void error(char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		fprintf(stderr, "Number of arguments is ileagal\n!");
		return 1;
	}

	char *p = argv[1];

	printf(".intel_syntax noprefix\n");
	printf(".globl main\n");

	printf("main:\n");
	printf("	mov rax, %ld\n", strtol(p, &p, 10));

	while (*p)
	{
		if(*p == '+')
		{
			p++;
			printf("	add rax, %ld\n", strtol(p, &p, 10));
			continue;
		}

		if(*p == '-')
		{
			p++;
			printf("	sub rax, %ld\n", strtol(p, &p, 10));
			continue;
		}

		fprintf(stderr, "Unexpected char: '%c'\n", *p);
	}

	printf("	ret\n");

	return 0;
}
