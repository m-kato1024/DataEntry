// DataManager.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//


#include "DataManager.h"

struct data list1[10];

int gUserCount = 0;

/*********************************
関数名：DMInitialization
機能：初期化
**********************************/
int DMInitialization(char* path) {

	memset(list1, 0, sizeof(list1));

	FILE *fp;
	fp = fopen(path, "r");
	if (fp == NULL) {
		return 1;
	}
	while (1) {
		fscanf(fp, "%d", &list1->number);
		fscanf(fp, "%s", list1->name);
		fscanf(fp, "%s", list1->yomi);
		if (list1->number != 0) {
			gUserCount++;
		}
		if (feof(fp)) {
			break;
		}

	}
	return 0;
	fclose(fp);
}
/*********************************
関数名：DMAddNew
機能：新規登録
**********************************/
void DMAddNew(int input_number, char* input_name, char* input_yomi) {

	list1[input_number - 1].number = input_number;

	strcpy(list1[input_number - 1].name, input_name);

	strcpy(list1[input_number - 1].yomi, input_yomi);

	gUserCount++;

}
/*********************************
関数名：DMDelete
機能：削除
**********************************/
void DMDelete(int input_number) {
	for (int i = 0; i < 10; i++) {
		if (input_number == list1[i].number) {
			list1[i].number = { 0 };
			strcpy(list1[i].name, '\0');
			strcpy(list1[i].yomi, '\0');

			gUserCount--;

		}

	}
}
/*********************************
関数名：DMListFetch
機能：一覧取得
**********************************/
int DMListFetch(struct data result[]) {
	int count = 0;

	for (int i = 0; i < 10; i++) {
		if (list1[i].number != 0) {
			result[count] = list1[i];
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
	char tem[40];

	for (int i = 0; i < 10; i++) {
		if (strstr(list1[i].yomi, input_yomi) != NULL) {
			
			search_result[searchCount] = list1[i];
			searchCount++;
		}
			
	}
	return searchCount;
}

/*********************************
関数名：DMTerminate
機能：終了
**********************************/
int DMTerminate(char* path) {
	FILE *fp;
	fp = fopen(path, "w");
	if (fp == NULL) {
		return 1;
	}

	for (int i = 0; i < 10; i++) {
		fprintf(fp, "%d\t%s\t%s\n", list1[i].number, list1[i].name, list1[i].yomi);
	}

	fclose(fp);
	return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
