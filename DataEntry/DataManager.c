#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "DataManager.h"

//番号が有効範囲であるかチェックするマクロ
#define IS_VALID_NUMBER(a)	((a >= 1) && (a <= DATA_MAX_COUNT))

//内部変数の定義
static User _entryList[DATA_MAX_COUNT];
static int _userCount = 0;

/**
 * @brief 読み込み
 * @param path ファイル名
 * @retval false 失敗
 * @retval true  成功
 * @note DataManagerを利用する場合は必ず初めにこの処理を実行すること
*/
bool DMLoad(const char* path) 
{
	_userCount = 0;
	memset(_entryList, 0, sizeof(_entryList));

	FILE *fp = fopen(path, "rb");
	if (fp != NULL) {
		fread(_entryList, sizeof(User), DATA_MAX_COUNT, fp);
		for (int index = 0; index < DATA_MAX_COUNT; index++) {
			if (IS_VALID_NUMBER(_entryList[index].number)) {
				_userCount++;
			}
		}
		fclose(fp);
	}
	
	return true;
	
}
/**
 * @brief 新規登録
 * @param newData 新規登録情報
 * @retval false 失敗
 * @retval true  成功
 * @note numberが範囲外の時はfalseを返す
 　　　　newDataがNULLの場合はfalseを返す
*/
bool DMAddNew(User* newData) 
{
	if (newData == NULL) {
		return false;
	}
	if (!IS_VALID_NUMBER(newData->number)) {
		return false;
	}
	_entryList[newData->number - 1] = *newData;
	_userCount++;
	return true;
}

/**
 * @brief 削除
 * @param deleteNumber 削除する番号
 */
void DMDelete(int deleteNumber) 
{
	if (!IS_VALID_NUMBER(deleteNumber)) {
		return;
	}
	memset(&_entryList[deleteNumber - 1], 0, sizeof(User));
	_userCount--;
}

/**
 * @brief 検索及び一覧
 * @param searchWord      検索文字列
 * @param search_result[] 検索結果
 * @retval 見つかったデータの件数
 * @note searchWordをNULLで指定した場合は全件を返す
*/
int DMSearch(char* searchWord, User* result)
{
	int searchCount = 0;
	bool isValid;

	if (result == NULL) {
		return searchCount;
	}

	for (int i = 0; i < DATA_MAX_COUNT; i++) {
		isValid = false;

		if (_entryList[i].number != 0) {
			if (searchWord == NULL) {
				//全件指定の場合
				isValid = true;
			}
			else {
				//検索の場合
				if (strstr(_entryList[i].reading, searchWord) != NULL) {
					isValid = true;
				}
			}
		}

		if (isValid) {
			result[searchCount] = _entryList[i];
			searchCount++;
		}

	}
	return searchCount;
}

/**
 * @brief 保存
 * @param path ファイル名
 * @retval false 失敗
 * @retval true  成功
 * @note 本処理を呼び出さないと保存はされない。
*/
bool DMSave(const char* path) 
{
	bool ret = false;
	FILE *fp = fopen(path, "wb");
	if (fp != NULL) {
		fwrite(_entryList, sizeof(User), DATA_MAX_COUNT, fp);
		fclose(fp);
		ret = true;
	}
	return ret;
}

/**
 * @brief 件数を返す
 * @retval 0以上 登録件数
*/
int DMGetUserCount()
{
	return _userCount;
}

