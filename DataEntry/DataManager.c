﻿#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "DataManager.h"


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
	
	FILE *fp;
	if (path == NULL) {
		return false;
	}
	fp = fopen(path, "r");
	
	memset(_entryList, 0, sizeof(_entryList));

	while (fp != NULL) {
		fscanf(fp, "%d", &_entryList[count].number);
		fscanf(fp, "%s", _entryList[count].name);
		fscanf(fp, "%s", _entryList[count].yomi);
		
		if (_entryList[count].number != 0) {
			_userCount++;
		}
		count++;
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
	
	memset(&_entryList[input_number - 1], 0, sizeof(struct data));

	_entryList[input_number - 1].number = input_number;
	strncpy(_entryList[input_number - 1].name, input_name, DATA_MAX_LENGTH - 1);
	strncpy(_entryList[input_number - 1].yomi, input_yomi, DATA_MAX_LENGTH - 1);

	_userCount++;

	return true;

}
/**
 * @brief 削除
 * @param input_number 入力された登録番号
*/
void DMDelete(int input_number) {
	for (int i = 0; i < DATA_MAX_COUNT; i++) {
		if (input_number == _entryList[i].number) {
			_entryList[i].number = 0;
			_entryList[i].name[0] =  '\0';
			_entryList[i].yomi[0] =  '\0';

			_userCount--;

		}

	}
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
		if (strstr(_entryList[i].yomi, input_yomi) != NULL) {
			
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
		fprintf(fp, "%d\t%s\t%s\n", _entryList[i].number, _entryList[i].name, _entryList[i].yomi);
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

