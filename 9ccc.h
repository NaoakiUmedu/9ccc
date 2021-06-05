/*** 9ccc.h ***/
#include <stdbool.h>

/*** Utility Types Declear ***/
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

/*** Function Prototypes ***/
void error(char *fmt, ...);	// エラー報告用関数 
bool consume(char op);		// トークンを読み進める(記号->bool)
void expect(char op);		// トークンを読み進める(記号->エラーメッセージ)
int expect_number();		// トークンを読み進める(数値->エラーメッセージ)
bool at_eof();				// EOFに来たかどうか判定する
Token *new_token(TokenKind kind, Token *cur, char *str);	// 新しいトークンを作成して、curにつなげる
Token *tokenize(char *p);	// 入力文字列pをトークナイズして返す
