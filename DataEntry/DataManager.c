﻿#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "DataManager.h"

static void DMLinefeed_deleting(char *str);
static struct data _entryList[DATA_MAX_COUNT];

static int _userCount = 0;



/**
 * @brief 初期化
 * @param path ファイル名
 * @retval false 失敗
 * @retval true  成功
 * @note DataManagerを利用する場合は必ず初めにこの処理を実行すること
*/
bool DMInitialization(char* path) {
	int count = 0;
	_userCount = 0;
	

	FILE *fp;
	if (path == NULL) {
		return false;
	}
	fp = fopen(path, "r");
	
	
	memset(_entryList, 0, sizeof(_entryList));

	while (fp != NULL) {
	
		/*if (feof(fp)) {
			break;
		}*/
		fscanf(fp, "%d", &_entryList[count].number);
		fscanf(fp, "%s", _entryList[count].name);
		fscanf(fp, "%s", _entryList[count].yomi);
	 
		
		if (_entryList[count].number != 0) {
			_userCount++;
			
		}
		count++;
		
		if (_userCount == DATA_MAX_COUNT) {
			break;
		}
		if (feof(fp)) {
			break;
		}

	}
	if(fp != NULL){
		fclose(fp);
	}
	
	return true;
	
}
/**
 * @brief 新規登録
 * @param input_number 入力された登録番号
 * @param input_name   入力された登録名前
 * @param input_yomi   入力された登録読み仮名
 * @retval false 失敗
 * @retval true  成功
 * @note input_numberが範囲外の時はエラー
 　　　　input_name,input_yomiがNULLの場合エラー
*/

bool DMAddNew(int input_number, char* input_name, char* input_yomi) {

	if (input_number < 1 || input_number > DATA_MAX_COUNT) {
		return false;
	}
	if (input_name == NULL || input_yomi == NULL) {
		return false;
	}
	
	if (_entryList[input_number - 1].number == 0) {
		_userCount++;
	}
	memset(&_entryList[input_number - 1], 0, sizeof(struct data));

	
	_entryList[input_number - 1].number = input_number;
	strncpy(_entryList[input_number - 1].name, input_name, DATA_MAX_LENGTH - 1);
	strncpy(_entryList[input_number - 1].yomi, input_yomi, DATA_MAX_LENGTH - 1);

	

	return true;

}
/**
 * @brief 削除
 * @param input_number 入力された登録番号
 * @retval false 失敗
 * @retval true  成功
*/
bool DMDelete(int input_number) {
	for (int i = 0; i < DATA_MAX_COUNT; i++) {
		if (input_number == _entryList[i].number) {
			_entryList[i].number = 0;
			strcpy(_entryList[i].name, "　");
			strcpy(_entryList[i].yomi, "　");

			_userCount--;
			return true;
		}
		

	}
	return false;
}
/**
 * @brief 一覧取得
 * @param  result[] 出力結果
 * @retval 0以上 件数
*/
int DMListFetch(struct data result[]) {
	int count = 0;

	for (int i = 0; i < DATA_MAX_COUNT; i++) {
		if (_entryList[i].number != 0) {
			result[count] = _entryList[i];
			count++;
		}
	}
	return count;
}
/**
 * @brief 検索
 * @param input_yomi      入力された読み仮名
 * @param search_result[] 検索結果
 * @retval 0以上 件数
*/
int DMSearch(char* input_yomi, struct data search_result[]) {
	int searchCount = 0;

	for (int i = 0; i < DATA_MAX_COUNT; i++) {
		if (strstr(_entryList[i].yomi, input_yomi) != NULL && _entryList[i].number != 0) {
			
			search_result[searchCount] = _entryList[i];
			searchCount++;
		}
			
	}
	return searchCount;
}

/**
 * @brief 終了
 * @param path ファイル名
 * @retval false 失敗
 * @retval true  成功
 * @note 呼び出さないとセーブされない
*/
bool DMTerminate(char* path) {
	FILE *fp;
	fp = fopen(path, "w");
	if (fp == NULL) {
		return false;
	}

	for (int i = 0; i < DATA_MAX_COUNT; i++) {
		if (_entryList[i].number == 0 && strcmp(_entryList[i].name, "　") != 0 && strcmp(_entryList[i].yomi, "　") != 0) {
			fprintf(fp, "%d\t%s　\t%s　\n", _entryList[i].number, _entryList[i].name, _entryList[i].yomi);
		}
		else {
			fprintf(fp, "%d\t%s\t%s\n", _entryList[i].number, _entryList[i].name, _entryList[i].yomi);
		}
		
			
		
		
			
	
		
	}

	fclose(fp);
	return true;
}

/**
 * @brief 件数を返す
 * @retval 0以上 登録件数
*/
int DMGetUserCount(){
	return _userCount;
}


/**
 * @brief インポート
 * @param path ファイル名
 * @retval 0以下 失敗
 * @retval 0以上 成功
*/
int DMImport(char* path) {
	
	char buf[READ_LINE_BUFFER_SIZE] = { 0 };
	char kugiri[] = ",";
	char *tok;

	struct data tempUser = { 0 };

	FILE *fp;

	if (path == NULL) {
		return -1;
	}
	
	fp = fopen(path, "r");

	if (fp == NULL) {
		return -1;
	}
	_userCount = 0;
	memset(_entryList, 0, sizeof(_entryList));
	while (fgets(buf, READ_LINE_BUFFER_SIZE, fp) != NULL) {
		
		DMLinefeed_deleting(buf);
		
		tok = strtok(buf, kugiri);
		memset(&tempUser, 0, sizeof(tempUser));
		tempUser.number = atoi(tok);
		while (tok != NULL) {
			tok = strtok(NULL, kugiri);
			if (tempUser.name[0] == '\0') {
				strncpy(tempUser.name, tok, DATA_MAX_LENGTH - 1);
			}
			else if (tempUser.yomi[0] == '\0') {
				strncpy(tempUser.yomi, tok, DATA_MAX_LENGTH - 1);
			}
		}

		DMAddNew(tempUser.number, tempUser.name, tempUser.yomi);

		if (_userCount == DATA_MAX_COUNT) {
			break;
		}
		
		if (feof(fp)) {
			break;
		}
	}
	fclose(fp);
	
	return _userCount;

}

/**
 * @brief エクスポート
 * @param path ファイル名
 * @retval 0以上 成功	
 * @retval 0以下 失敗
*/
int DMExport(char* path) {
	int line = 0;
	FILE *fp;
	if (path == NULL) {
		return -1;
	}
	fp = fopen(path, "w");
	if (fp == NULL) {
		return -1;
	}

	for (int i = 0; i < DATA_MAX_COUNT; i++) {
		
		if (_entryList[i].number != 0) {
			fprintf(fp, "%d,%s,%s\n", _entryList[i].number, _entryList[i].name, _entryList[i].yomi);
			line++;
		}
	}
	

	fclose(fp);
	return line;
}


/**
 * @brief 改行を削除
 * @retval str 読み込んだ1行
*/
static void DMLinefeed_deleting(char *str) {
	char *p;
	p = strchr(str, '\n');
	if (p != NULL) {
		*p = '\0';
	}
}