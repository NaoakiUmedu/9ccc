/*** 9ccc.h ***/
#include <stdbool.h>

/*** Utility Types Declear ***/
typedef enum
{
	TK_RESERVED, // signal
	TK_NUM,		 // number
	TK_EOF,		 // end of input
} TokenKind;

typedef struct Token Token;

struct Token
{
	TokenKind kind;
	Token *next;
	int val;   // number
	char *str; // string
};

/*** グローバル変数 ***/
Token *token; // now seening token
char *user_input;

/*** Function Prototypes ***/
// エラー報告用関数
void error(char *fmt, ...);
// トークンを読み進める(記号->bool)
bool consume(char op);
// トークンを読み進める(記号->エラーメッセージ)
void expect(char op);
// トークンを読み進める(数値->エラーメッセージ)
int expect_number();
// EOFに来たかどうか判定する
bool at_eof();
// 新しいトークンを作成して、curにつなげる
Token *new_token(TokenKind kind, Token *cur, char *str);
// 入力文字列pをトークナイズして返す
Token *tokenize(void);
// エラーメッセージの改良
void error_at(char *loc, char *fmt, ...);