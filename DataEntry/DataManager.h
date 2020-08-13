#pragma once
//データ登録の最大件数
#define DATA_MAX_COUNT (10)
//名前の最大バイト数
#define DATA_MAX_LENGTH (40)
#include <stdbool.h>
struct data {
	int number;
	char name[DATA_MAX_LENGTH];
	char yomi[DATA_MAX_LENGTH];
};
bool DMInitialization(char* path);
bool DMAddNew(int input_number, char* input_name, char* input_yomi);
void DMDelete(int input_number);
int DMListFetch(struct data result[]);
int DMSearch(char* input_yomi, struct data search_result[]);
bool DMTerminate(char* path);
int DMGetUserCount();