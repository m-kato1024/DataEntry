


#include "DataManager.h"

static struct data _entryList[DATA_MAX_COUNT];

static int _userCount = 0;

/*********************************
関数名：DMInitialization
機能：初期化
**********************************/
bool DMInitialization(char* path) {
	int count = 0;
	
	FILE *fp;
	if (path == NULL) {
		return false;
	}
	fp = fopen(path, "r");
	
	memset(_entryList, 0, sizeof(_entryList));

	while (fp != NULL) {
		fscanf(fp, "%d", _entryList[count].number);
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
/*********************************
関数名：DMAddNew
機能：新規登録
**********************************/
bool DMAddNew(int input_number, char* input_name, char* input_yomi) {

	if (input_number < 0 || input_number > DATA_MAX_COUNT) {
		return false;
	}
	_entryList[input_number - 1].number = input_number;

	strcpy(_entryList[input_number - 1].name, input_name);

	strcpy(_entryList[input_number - 1].yomi, input_yomi);

	_userCount++;

	return true;

}
/*********************************
関数名：DMDelete
機能：削除
**********************************/
void DMDelete(int input_number) {
	for (int i = 0; i < DATA_MAX_COUNT; i++) {
		if (input_number == _entryList[i].number) {
			_entryList[i].number = { 0 };
			_entryList[i].name[0] =  '\0';
			_entryList[i].yomi[0] =  '\0';

			_userCount--;

		}

	}
}
/*********************************
関数名：DMListFetch
機能：一覧取得
**********************************/
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
/*********************************
関数名：DMSearch
機能：検索
**********************************/
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

/*********************************
関数名：DMTerminate
機能：終了
**********************************/
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

/*********************************
関数名：DMGetUserCount
機能：登録人数を返す
**********************************/
int DMGetUserCount(){
	return _userCount;
}


