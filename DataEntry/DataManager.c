#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "DataManager.h"


static struct data _entryList[DATA_MAX_COUNT];

static int _userCount = 0;
static int line = 0;

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
			count++;
		}
		
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


/**
 * @brief インポート
 * @param path ファイル名
 * @retval false 失敗
 * @retval true  成功
*/
bool DMImport(char* path) {
	int count = 0;
	char buf[READ_LINE_BUFFER_SIZE] = { 0 };
	char kugiri[] = ",";
	char *tok;

	FILE *fp;
	fp = fopen(path, "r");
	if (path == NULL) {
		return false;
	}
	if (fp == NULL) {
		return false;
	}
	memset(_entryList, 0, sizeof(_entryList));
	while (fgets(buf, READ_LINE_BUFFER_SIZE, fp) != NULL) {
		
		DMLinefeed_deleting(buf);
		
		tok = strtok(buf, kugiri);
		_entryList[count].number = atoi(tok);
		while (tok != NULL) {
			tok = strtok(NULL, kugiri);
			if (_entryList[count].name[0] == '\0') {
				strcpy(_entryList[count].name, tok);
			}
			else if (_entryList[count].yomi[0] == '\0') {
				strcpy(_entryList[count].yomi, tok);
			}
		}

		if (line == DATA_MAX_COUNT) {
			break;
		}

		if (_entryList[count].number != 0) {
			line++;
			count++;
		}
		
		if (feof(fp)) {
			break;
		}
	}
	fclose(fp);
	
	return true;

}

/**
 * @brief エクスポート
 * @param path ファイル名
 * @retval 0     成功	
 * @retval 1     データ0件
 * @retval 2     失敗
*/
int DMExport(char* path) {
	FILE *fp;
	fp = fopen(path, "w");
	if (fp == NULL) {
		return 2;
	}

	for (int i = 0; i < DATA_MAX_COUNT; i++) {
		fprintf(fp, "%d,%s,%s\n", _entryList[i].number, _entryList[i].name, _entryList[i].yomi);
		if (_entryList[i].number != 0) {
			line++;
		}
	}
	
	if (line == 0) {
		return 1;
	}

	fclose(fp);
	return 0;
}

/**
 * @brief インポートした件数を返す
 * @retval 0以上 インポート件数
*/
int DMLine() {
	return line;
}

/**
 * @brief 改行を削除
 * @retval str 読み込んだ1行
*/
void DMLinefeed_deleting(char *str) {
	char *p;
	p = strchr(str, '\n');
	if (p != NULL) {
		*p = '\0';
	}
}