#pragma once
#include <stdbool.h>

//--------------------------------------------------------------------
//define定義
//--------------------------------------------------------------------
//データ登録の最大件数
#define DATA_MAX_COUNT (10)
//名前、読み仮名の最大バイト数
#define DATA_FIELD_MAX_LENGTH (40)

//--------------------------------------------------------------------
//型定義
//--------------------------------------------------------------------
typedef struct _user{
	int number;
	char name[DATA_FIELD_MAX_LENGTH];
	char reading[DATA_FIELD_MAX_LENGTH];
}User;

//--------------------------------------------------------------------
// 外部公開関数宣言
//--------------------------------------------------------------------
bool DMLoad(const char*);
bool DMAddNew(User*);
void DMDelete(int);
int DMSearch(char*, User*);
bool DMSave(const char*);
int DMGetUserCount(void);

