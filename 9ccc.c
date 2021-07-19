/* Step 3 Tokenizer */
/* メモリ管理ポリシー:短命なプログラムなのでfreeしなくてもよい */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

#include "9ccc.h"

/* エラー報告用関数 */
void error(char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}

/* エラー報告用関数2 */
void error_at(char *loc, char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	int pos = loc - user_input;
	fprintf(stderr, "%s\n", user_input);
	fprintf(stderr, "%*s", pos, " ");
	fprintf(stderr, "^ ");
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}

/* トークンを読み進める(記号->bool) */
bool consume(char op)
{
	if ((token->kind != TK_RESERVED) || (token->str[0] != op))
	{
		return false;
	}
	token = token->next;
	return true;
}

/* トークンを読み進める(記号->エラーメッセージ) */
void expect(char op)
{
	if ((token->kind != TK_RESERVED) || (token->str[0] != op))
	{
		error_at(token->str, "'%c'ではありません", op);
	}
	token = token->next;
}

/* トークンを読み進める(数値) */
int expect_number()
{
	if (token->kind != TK_NUM)
	{
		error_at(token->str, "数ではありません");
	}
	int val = token->val;
	token = token->next;
	return val;
}

/* EOFかどうかチェックする */
bool at_eof()
{
	return (token->kind == TK_EOF);
}

/* 新しいトークンを作成してcurにつなげる */
Token *new_token(TokenKind kind, Token *cur, char *str)
{
	Token *tok = calloc(1, sizeof(Token));
	tok->kind = kind;
	tok->str = str;
	cur->next = tok;
	return tok;
}

/* 入力文字列pをトークナイズしてそれを返す */
Token *tokenize()
{
	char *p = user_input;
	Token head;
	head.next = NULL;
	Token *cur = &head;

	while (*p)
	{
		// 空白文字をスキップする
		if (isspace(*p))
		{
			p++;
			continue;
		}

		// 記号である場合
		if ((*p == '+') || (*p == '-'))
		{
			cur = new_token(TK_RESERVED, cur, p);
			p++;
			continue;
		}

		// 数値である場合
		if (isdigit(*p))
		{
			cur = new_token(TK_NUM, cur, p);
			cur->val = strtol(p, &p, 10);
			continue;
		}

		error_at(p, "数字ではありません");
	}

	new_token(TK_EOF, cur, p);
	return head.next;
}

/*** MAIN PROGRAM ***/
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		error("引数の個数が正しくありません");
		return 1;
	}

	// トークナイズする
	user_input = argv[1];
	token = tokenize();

	// アセンブリ前半部分を出力
	printf(".intel_syntax noprefix\n");
	printf(".globl main\n");
	printf("main:\n");

	// 式の最初は数でなければならないので、それをチェックして
	// 最初のmov命令を出力
	printf("	mov rax, %d\n", expect_number());

	// '+ <数>' あるいは '- <数>'というトークンの並びを消費しつつ
	// アセンブリを出力
	while (!at_eof())
	{
		if (consume('+'))
		{
			printf("	add rax, %d\n", expect_number());
			continue;
		}

		expect('-');
		printf("	sub rax, %d\n", expect_number());
	}

	printf("	ret\n");

	return 0;
}
