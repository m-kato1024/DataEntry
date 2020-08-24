#pragma once
#include <stdbool.h>

//--------------------------------------------------------------------
//define定義
//--------------------------------------------------------------------
//データ登録の最大件数
#define DATA_MAX_COUNT (10)
//名前の最大バイト数
#define DATA_MAX_LENGTH (40)
//ファイル1行の最大サイズ　10件以上格納する場合は先頭の２の数字に注意する
#define READ_LINE_BUFFER_SIZE (3+1+DATA_MAX_LENGTH+1+DATA_MAX_LENGTH+1)
#define END_OF_TEST (0x03)
//--------------------------------------------------------------------
//型定義
//--------------------------------------------------------------------
struct data {
	int number;
	char name[DATA_MAX_LENGTH];
	char yomi[DATA_MAX_LENGTH];
};

//--------------------------------------------------------------------
//関数宣言
//--------------------------------------------------------------------
bool DMInitialization(char* path);
bool DMAddNew(int input_number, char* input_name, char* input_yomi);
bool DMDelete(int input_number);
int DMListFetch(struct data result[]);
int DMSearch(char* input_yomi, struct data search_result[]);
bool DMTerminate(char* path);
int DMGetUserCount();