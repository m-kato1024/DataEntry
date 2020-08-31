#define _CRT_SECURE_NO_WARNINGS

#include "gtest/gtest.h"



extern "C"
{
#include <sys/stat.h>
#include <stdio.h>
#include "./../DataEntry/DataManager.h"

}

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test001</testname>
	<category1>DMInitialization</category1>
	<category2>異常系</category2>
	<category3>第一引数チェック</category3>
	<case>
		1)
		第一引数pathをNULLで実行する。
	</case>
	<check>
		1)
		・戻り値がfalseであること。
		・強制終了しないこと。
	</check>
</testitem>*/
TEST(UnitTestDM, Test001) {

	bool ret =  DMInitialization(NULL);
	EXPECT_EQ(false, ret);
}



/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test002</testname>
	<category1>DMInitialization</category1>
	<category2>正常系</category2>
	<category3>データファイルなし</category3>
	<case>
		1)
		データファイルが存在しない状態で実行する。
	</case>
	<check>
		1)
		・戻り値がtrueであること。
		・件数が0件であること。
	</check>
</testitem>*/
TEST(UnitTestDM, Test002) {

	//データファイルを消しておく
	remove("data.txt");

	bool ret = DMInitialization("data.txt");
	EXPECT_EQ(true, ret);
	EXPECT_EQ(0, DMGetUserCount());

}




/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test003</testname>
	<category1>DMInitialization</category1>
	<category2>正常系</category2>
	<category3>データファイルあり</category3>
	<case>
		1）
		データファイルが存在する状態で実行する。
	</case>
	<check>
		1）
		・戻り値がtrueであること。
		・件数が登録されている数を一致すること。
	</check>
</testitem>*/
TEST(UnitTestDM, Test003)
{
	bool ret = DMInitialization("data\\test003.txt");
	EXPECT_EQ(true, ret);
	EXPECT_EQ(5, DMGetUserCount());
}

class UnitTestDM006 : public ::testing::Test
{
public:
	void SetUp()
	{
		remove("data.txt");//ファイル消す
		DMInitialization("data.txt");

	}

	void TearDown()
	{
		// 後処理
		DMTerminate("data.txt");
		remove("data.txt");//ファイル消す
	}
};
/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test004</testname>
	<category1>DMAddNew</category1>
	<category2>異常系</category2>
	<category3>第一引数チェック</category3>
	<case>
		1）
		第一引数input_numberを0で実行する。
	</case>
	<check>
		1）
		・戻り値がfalseであること。
		・強制終了しない。
	</check>
</testitem>*/
TEST_F(UnitTestDM006, Test004)
{
	bool ret = DMAddNew(0, "木下拓真", "きのしたたくま");
	EXPECT_EQ(false, ret);
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test005</testname>
	<category1>DMAddNew</category1>
	<category2>異常系</category2>
	<category3>第一引数チェック</category3>
	<case>
		1）
		第一引数input_numberを11で実行する。
	</case>
	<check>
		1）
		・戻り値がfalseであること。
		・強制終了しない。
	</check>
</testitem>*/
//TEST_F(UnitTestDM006, Test005)
//{
//	bool ret = DMAddNew(11, "木下拓真", "きのしたたくま");
//	EXPECT_EQ(false, ret);
//}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test006</testname>
	<category1>DMAddNew</category1>
	<category2>正常計</category2>
	<category3>第一引数チェック</category3>
	<case>
		1）
		第一引数input_numberを1で実行する。
	</case>
	<check>
		1）
		・戻り値がtrueであること。
		・登録件数が1件であること
	</check>
</testitem>*/
TEST_F(UnitTestDM006, Test006)
{
	bool ret = DMAddNew(1, "木下拓真", "きのしたたくま");
	EXPECT_EQ(true, ret);
	EXPECT_EQ(1, DMGetUserCount());
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test007</testname>
	<category1>DMAddNew</category1>
	<category2>異常系</category2>
	<category3>第二引数チェック</category3>
	<case>
		1）
		第二引数input_nameをNULLで実行する。
	</case>
	<check>
		1）
		・戻り値がfalseであること。
		・強制終了しないこと。
	</check>
</testitem>*/
TEST_F(UnitTestDM006, Test007)
{
	bool ret = DMAddNew(1, NULL, "きのしたたくま");
	EXPECT_EQ(false, ret);
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test008</testname>
	<category1>DMAddNew</category1>
	<category2>正常系</category2>
	<category3>第二引数チェック</category3>
	<case>
		1）
		第二引数input_nameを「木下拓真」で実行する。
	</case>
	<check>
		1）
		・戻り値がtrueであること。
		・登録件数が1件であること
	</check>
</testitem>*/
TEST_F(UnitTestDM006, Test008)
{
	bool ret = DMAddNew(1, "木下拓真", "きのしたたくま");
	EXPECT_EQ(true, ret);
	EXPECT_EQ(1, DMGetUserCount());
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test009</testname>
	<category1>DMAddNew</category1>
	<category2>異常系</category2>
	<category3>第三引数チェック</category3>
	<case>
		1）
		第三引数input_yomiをNULLで実行する。
	</case>
	<check>
		1）
		・戻り値がfalseであること。
		・強制終了しないこと。
	</check>
</testitem>*/
TEST_F(UnitTestDM006, Test009)
{
	bool ret = DMAddNew(1, "木下拓真", NULL);
	EXPECT_EQ(false, ret);
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test010</testname>
	<category1>DMAddNew</category1>
	<category2>正常系</category2>
	<category3>第三引数チェック</category3>
	<case>
		1）
		第三引数input_yomiを「きのしたたくま」で実行する。
	</case>
	<check>
		1）
		・戻り値がtrueであること。
		・登録件数が1件であること。
	</check>
</testitem>*/
TEST_F(UnitTestDM006, Test010)
{
	bool ret = DMAddNew(1, "木下拓真", "きのしたたくま");
	EXPECT_EQ(true, ret);
	EXPECT_EQ(1, DMGetUserCount());
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test011</testname>
	<category1>DMDelete</category1>
	<category2>異常系</category2>
	<category3>入力された番号の内部データがないとき</category3>
	<case>
		1）
		内部データが存在しない状態で実行する。
	</case>
	<check>
		1）
		・件数の変化がないこと。
	</check>
</testitem>*/
TEST_F(UnitTestDM006, Test011)
{
	EXPECT_EQ(0, DMGetUserCount());
	DMDelete(1);
	EXPECT_EQ(0, DMGetUserCount());
}

class UnitTestDM012 : public ::testing::Test
{
public:
	void SetUp()
	{
		remove("data.txt");//ファイル消す
		DMInitialization("data.txt");
		DMAddNew(1, "木下拓真", "きのしたたくま");

	}

	void TearDown()
	{
		// 後処理
		DMTerminate("data.txt");
		remove("data.txt");//ファイル消す
	}
};
/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test012</testname>
	<category1>DMDelete</category1>
	<category2>正常系</category2>
	<category3>入力された番号の内部データがあるとき</category3>
	<case>
		1）
		内部データが存在する状態で実行する。
	</case>
	<check>
		1）
		・NOが初期化されていること。
		・名前が初期化されていること。
		・読み仮名が初期化されていること。
		・件数が減っていること。
	</check>
</testitem>*/
TEST_F(UnitTestDM012, Test012)
{
	EXPECT_EQ(1, DMGetUserCount());
	DMDelete(1);
	EXPECT_EQ(0, DMGetUserCount());
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test013</testname>
	<category1>DMListFetch</category1>
	<category2>正常系</category2>
	<category3>データファイルなし</category3>
	<case>
		1）
		データファイルが存在しない状態で実行する。
	</case>
	<check>
		1）
		・戻り値の件数が0件であること。
	</check>
</testitem>*/
TEST_F(UnitTestDM006, Test013)
{
	
	struct data result[DATA_MAX_COUNT];
	int ret = DMListFetch(result);
	EXPECT_EQ(0, ret);

}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test014</testname>
	<category1>DMListFetch</category1>
	<category2>正常系</category2>
	<category3>データファイルあり</category3>
	<case>
		1）
		データファイルが存在する状態で実行する。
	</case>
	<check>
		1）
		・戻り値の件数が登録されている数と一致すること。
	</check>
</testitem>*/
TEST_F(UnitTestDM012, Test014)
{
	
	struct data result[DATA_MAX_COUNT];
	int ret = DMListFetch(result);
	EXPECT_EQ(1, ret);
	EXPECT_EQ(1, result[0].number);
	EXPECT_STREQ("木下拓真", result[0].name);
	EXPECT_STREQ("きのしたたくま", result[0].yomi);
	
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test015</testname>
	<category1>DMSearch</category1>
	<category2>正常系</category2>
	<category3>データファイルなし</category3>
	<case>
		1）
		データファイルが存在しない状態で実行する。
	</case>
	<check>
		1）
		・戻り値の件数が0件であること。
	</check>
</testitem>*/
TEST(UnitTestDM, Test015)
{
	struct data search_result[DATA_MAX_COUNT];
	int ret = DMSearch("きのしたたくま", search_result);
	EXPECT_EQ(0, ret);
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test016</testname>
	<category1>DMSearch</category1>
	<category2>正常系</category2>
	<category3>データファイルあり</category3>
	<case>
		1）
		データファイルが存在する状態で実行する。
	</case>
	<check>
		1）
		・戻り値の件数が一致した数であること。
	</check>
</testitem>*/
TEST_F(UnitTestDM012, Test016)
{
	struct data search_result[DATA_MAX_COUNT];
	int ret = DMSearch("きのしたたくま",search_result);
	EXPECT_EQ(1, ret);
	EXPECT_EQ(1, search_result[0].number);
	EXPECT_STREQ("木下拓真", search_result[0].name);
	EXPECT_STREQ("きのしたたくま", search_result[0].yomi);
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test017</testname>
	<category1>DMTerminate</category1>
	<category2>正常系</category2>
	<category3>データファイルなし</category3>
	<case>
		1）
		データファイルが存在しない状態で実行する。
	</case>
	<check>
		1）
		・戻り値がtrueであること。
		・ファイルがつくられること。
	</check>
</testitem>*/
TEST(UnitTestDM, Test017)
{
	remove("data.txt");
	bool ret = DMTerminate("data.txt");
	EXPECT_EQ(true, ret);
	struct stat st;
	EXPECT_EQ(0, stat("data.txt", &st));
}



/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test018</testname>
	<category1>DMTerminate</category1>
	<category2>正常系</category2>
	<category3>データファイルあり</category3>
	<case>
		1）
		データファイルが存在する状態で実行する。
	</case>
	<check>
		1）
		・戻り値がtrueであること。
		・ファイルにデータが書き込まれること。
	</check>
</testitem>*/
TEST_F(UnitTestDM012, Test018)
{
	bool ret = DMTerminate("data.txt");
	DMInitialization("data.txt");
	struct data result[DATA_MAX_COUNT];
	int ret2 = DMListFetch(result);
	EXPECT_EQ(1, result[0].number);
	EXPECT_STREQ("木下拓真", result[0].name);
	EXPECT_STREQ("きのしたたくま", result[0].yomi);
	EXPECT_EQ(true, ret);
	EXPECT_EQ(1, ret2);
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test019</testname>
	<category1>DMGetUserCount</category1>
	<category2>正常系</category2>
	<category3>データファイルなし</category3>
	<case>
		1）
		データファイルが存在しない状態で実行する。
	</case>
	<check>
		1）
		・戻り値の登録件数が0件であること。
	</check>
</testitem>*/
TEST_F(UnitTestDM006, Test019)
{
	
	int ret = DMGetUserCount();
	EXPECT_EQ(0, ret);
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test020</testname>
	<category1>DMGetUserCount</category1>
	<category2>正常系</category2>
	<category3>データファイルあり</category3>
	<case>
		1）
		データファイルが存在する状態で実行する。
	</case>
	<check>
		1）
		・戻り値の件数が登録されている数と一致すること。
	</check>
</testitem>*/
class UnitTestDM020 : public ::testing::Test
{
public:
	void SetUp()
	{
		remove("data.txt");//ファイル消す
		DMInitialization("data.txt");
		DMAddNew(1, "TEST01", "test01");
		DMAddNew(2, "TEST02", "test02");
		DMAddNew(3, "TEST03", "test03");
	}

	void TearDown()
	{
		// 後処理
		DMTerminate("data.txt");
		remove("data.txt");//ファイル消す
	}
};

TEST_F(UnitTestDM020, Test020)
{
	int ret = DMGetUserCount();
	EXPECT_EQ(3, ret);
}

class UnitTestDM021 : public ::testing::Test
{
public:
	void SetUp()
	{
		remove("data.txt");//ファイル消す
		DMInitialization("data.txt");
		DMAddNew(1, "TEST01", "test01");
		DMAddNew(2, "TEST02", "test02");
		DMAddNew(3, "TEST03", "test03");
		DMTerminate("data.txt");

	}

	void TearDown()
	{
		// 後処理
		
		remove("data.txt");//ファイル消す
	}
};
/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test021</testname>
	<category1>DMInitialization</category1>
	<category2>正常系</category2>
	<category3>データファイルあり
読み込みチェック</category3>
	<case>
		1）
		データファイルが存在する状態で実行する。
	</case>
	<check>
		1）
		・外部ファイルに保存されているデータと、起動時に内部データとして読みだされたデータが同じであること
	</check>
</testitem>*/
TEST_F(UnitTestDM021, Test021)
{
	DMInitialization("data.txt");
	struct data result[DATA_MAX_COUNT];
	int ret = DMListFetch(result);
	EXPECT_EQ(3, ret);
	for (int i = 0; i < ret; i++) {
	
		    char name[100];
			char yomi[100];

			sprintf(name, "TEST%02d", i + 1);
			sprintf(yomi, "test%02d", i + 1);

			EXPECT_EQ(i + 1, result[i].number);
			EXPECT_STREQ(name, result[i].name);
			EXPECT_STREQ(yomi, result[i].yomi);
	}

}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test022</testname>
	<category1>DMInitialization</category1>
	<category2>正常系</category2>
	<category3>データファイルあり</category3>
	<case>
		1）
		データファイルが10件登録されている状態で実行する。
	</case>
	<check>
		1）
		・保存されているデータと同じデータが読み込まれてること。
	</check>
</testitem>*/
//TEST(UnitTestDM, Test022)
//{
//	
//	DMInitialization("data\\test022.txt");
//	
//	struct data result[DATA_MAX_COUNT] = { 0 };
//	DMListFetch(result);
//
//	char name[100];
//	char yomi[100];
//
//	for (int i = 0; i < DATA_MAX_COUNT; i++) {
//		sprintf(name, "K%d", i + 1);
//		sprintf(yomi, "Y%d", i + 1);
//		EXPECT_EQ(i + 1, result[i].number);
//		ASSERT_STREQ(name, result[i].name);
//		ASSERT_STREQ(yomi, result[i].yomi);
//		
//	}
//
//	EXPECT_EQ(10, DMGetUserCount());
//}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test023</testname>
	<category1>DMAddNew</category1>
	<category2>異常系</category2>
	<category3>文字数チェック</category3>
	<case>
		1）
		名前を40バイト以上入力して実行する。
	</case>
	<check>
		1)
		・一覧表示したときに39文字表示されていること。
	</check>
</testitem>*/
TEST_F(UnitTestDM006, Test023)
{
	
	DMAddNew(1, "あああああああああああああああああああああああああ","きのしたたくま");
	struct data result[DATA_MAX_COUNT] = { 0 };
	DMListFetch(result);
	
		
	size_t length = strlen(result[0].name);
		
	
	EXPECT_EQ(39, length);
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test024</testname>
	<category1>DMAddNew</category1>
	<category2>異常系</category2>
	<category3>文字数チェック</category3>
	<case>
		1）
		読み仮名を40バイト以上入力して実行する。
	</case>
	<check>
		1)
		・一覧表示したときに39文字表示されていること。
	</check>
</testitem>*/
TEST_F(UnitTestDM006, Test024)
{
	
	DMAddNew(1, "木下拓真", "あああああああああああああああああああああああああ");
	struct data result[DATA_MAX_COUNT] = { 0 };
	DMListFetch(result);


	size_t length = strlen(result[0].yomi);


	EXPECT_EQ(39, length);
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test025</testname>
	<category1>DMListFetch</category1>
	<category2>正常系</category2>
	<category3>引数チェック</category3>
	<case>
		1）
		データファイルが存在する状態で実行する。
	</case>
	<check>
		1)
		・UI側に正しいデータが返されていること。
	</check>
</testitem>*/
TEST_F(UnitTestDM012, Test025)
{
	struct data result[DATA_MAX_COUNT] = { 0 };
	DMListFetch(result);
	ASSERT_STREQ("木下拓真", result[0].name);
}

class UnitTestDM026 : public ::testing::Test
{
public:
	void SetUp()
	{
		remove("data.txt");//ファイル消す
		DMInitialization("data.txt");
		DMAddNew(1, "木下拓真", "きのしたたくま");
		DMAddNew(2, "加藤雅貴", "かとうまさき");
		
	}

	void TearDown()
	{
		// 後処理
		DMTerminate("data.txt");
		remove("data.txt");//ファイル消す
	}
};

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test026</testname>
	<category1>DMSearch</category1>
	<category2>異常系</category2>
	<category3>検索文字チェック</category3>
	<case>
		1)
		検索文字を40バイト以上入力して実行する。
	</case>
	<check>
		1)
		・戻り値が0であること。
		・検索結果が見つからないこと
	</check>
</testitem>*/
TEST_F(UnitTestDM026, Test026)
{
	struct data search_result[DATA_MAX_COUNT];
	int ret = DMSearch("きのしたたくまきのしたたくまきのしたたくまかとうまさき", search_result);
	EXPECT_EQ(0, ret);
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test027</testname>
	<category1>DMSearch</category1>
	<category2>正常系</category2>
	<category3>第二引数チェック</category3>
	<case>
		1）
		データファイルが存在する状態で実行する。
	</case>
	<check>
		1)
		・返す配列のデータに間違いがないこと。
	</check>
</testitem>*/
TEST_F(UnitTestDM012, Test027)
{
	struct data search_result[DATA_MAX_COUNT];
	DMSearch("きのしたたくま", search_result);
	ASSERT_STREQ("きのしたたくま", search_result[0].yomi);
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test028</testname>
	<category1>DMTerminate</category1>
	<category2>正常系</category2>
	<category3>データファイルあり
書き込みチェック</category3>
	<case>
		1）
		データファイルが存在する状態で実行する。
	</case>
	<check>
		1)
		・内部データと同じデータが外部ファイルに保存されていること。
	</check>
</testitem>*/
TEST_F(UnitTestDM012, Test028)
{
	DMTerminate("data.txt");
	DMInitialization("data.txt");
	struct data result[DATA_MAX_COUNT] = { 0 };
	DMListFetch(result);
	ASSERT_STREQ("木下拓真", result[0].name);

}

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test029</testname>
	<category1>DMTerminate</category1>
	<category2>異常系</category2>
	<category3>データファイルなし</category3>
	<case>
		1）
		存在しないファイルパスを指定して実行する。
	</case>
	<check>
		1)
		・戻り値がfalseであること。
		・強制終了しないこと。
	</check>
</testitem>*/
TEST(UnitTestDM, Test029)
{
	remove("data.txt");
	bool ret = DMTerminate("K:\\data.txt");
	EXPECT_EQ(false, ret);
}

class UnitTestDM030 : public ::testing::Test
{
public:
	void SetUp()
	{
		remove("data.txt");//ファイル消す
		DMInitialization("data.txt");
		DMAddNew(1, "木下拓真", "きのしたたくま");
		DMAddNew(2, "加藤雅貴", "かとうまさき");
		DMDelete(1);
		DMTerminate("data.txt");


	}

	void TearDown()
	{
		// 後処理
		DMTerminate("data.txt");
		remove("data.txt");//ファイル消す
	}
};
/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test030</testname>
	<category1>DMListFetch</category1>
	<category2>正常系</category2>
	<category3>データファイルあり</category3>
	<case>
		1）
		データファイルの1件目が0の状態で実行する。
	</case>
	<check>
		1)
		・戻り値が登録件数を一致すること。
	</check>
</testitem>*/
TEST_F(UnitTestDM030, Test030)
{
	DMInitialization("data.txt");
	struct data result[DATA_MAX_COUNT] = { 0 };
	int ret = DMListFetch(result);
	EXPECT_EQ(1, ret);
}

class UnitTestDM031 : public ::testing::Test
{
public:
	void SetUp()
	{
		remove("data.txt");//ファイル消す
		DMInitialization("data.txt");
		for (int i = 0; i < DATA_MAX_COUNT; i++) {
			DMAddNew(i+1, "TEST", "test");
		}
		
		DMTerminate("data.txt");


	}

	void TearDown()
	{
		// 後処理
		DMTerminate("data.txt");
		remove("data.txt");//ファイル消す
	}
};
/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test031</testname>
	<category1>DMInitialization</category1>
	<category2>正常系</category2>
	<category3>データファイルあり</category3>
	<case>
		1）
		データファイルが100登録されている状態で実行する。
	</case>
	<check>
		1)
		・戻り値がtrueであること。
		・件数が100件であること。
	</check>
</testitem>*/
TEST_F(UnitTestDM031, Test031)
{
	bool ret = DMInitialization("data.txt");
	EXPECT_EQ(true, ret);
	EXPECT_EQ(100, DMGetUserCount());

}

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test032</testname>
	<category1>DMAddNew</category1>
	<category2>正常系</category2>
	<category3>データファイルあり</category3>
	<case>
		1）
		データファイルが2件登録されている状態で実行する。
	</case>
	<check>
		1)
		・戻り値がtrueであること。
		・件数が2件であること。
	</check>
</testitem>*/
TEST(UnitTestDM, Test032)
{
	bool ret = DMInitialization("data\\test032.txt");
	EXPECT_EQ(true, ret);
	EXPECT_EQ(2, DMGetUserCount());
}

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test033</testname>
	<category1>DMAddNew</category1>
	<category2>正常系</category2>
	<category3>データファイルあり</category3>
	<case>
		1）
		データファイルが10件登録されている状態で実行する。
	</case>
	<check>
		1)
		・戻り値がtrueであること。
		・件数が10件であること。
	</check>
</testitem>*/
TEST(UnitTestDM, Test033)
{
	bool ret = DMInitialization("data\\test033.txt");
	EXPECT_EQ(true, ret);
	EXPECT_EQ(10, DMGetUserCount());
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test034</testname>
	<category1>DMAddNew</category1>
	<category2>異常系</category2>
	<category3>データファイルあり</category3>
	<case>
		1）
		データファイルが100登録されている状態で実行する。
	</case>
	<check>
		1)
		・戻り値がfalseであること。
	</check>
</testitem>*/
TEST_F(UnitTestDM031, Test034)
{
	DMInitialization("data.txt");
	bool ret = DMAddNew(101, "TEST", "test");
	EXPECT_EQ(false, ret);
}

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test035</testname>
	<category1>DMImport</category1>
	<category2>異常系</category2>
	<category3>第一引数チェック</category3>
	<case>
		第一引数をNULLで実行する。
	</case>
	<check>
		1)
		・戻り値が-1であること。
	</check>
</testitem>*/
TEST(UnitTestDM, Test035)
{
	int ret = DMImport(NULL);
	EXPECT_EQ(-1, ret);
}

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test036</testname>
	<category1>DMImport</category1>
	<category2>異常系</category2>
	<category3>ファイル指定チェック</category3>
	<case>
		1)
		存在しないファイルパスを指定した場合。
	</case>
	<check>
		1)
		・戻り値が-1であること。
	</check>
</testitem>*/
TEST(UnitTestDM, Test036)
{
	int ret = DMImport("K:\\data.csv");
	EXPECT_EQ(-1, ret);
}

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test037</testname>
	<category1>DMImport</category1>
	<category2>正常系</category2>
	<category3>外部ファイルデータなし</category3>
	<case>
		1)
		外部ファイルがデータ0件で実行する。
	</case>
	<check>
		1)
		・戻り値が0であること。
	</check>
</testitem>*/
TEST(UnitTestDM, Test037)
{
	int ret = DMImport("data\\test37.csv");
	EXPECT_EQ(0, ret);
}

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test038</testname>
	<category1>DMImport</category1>
	<category2>正常系</category2>
	<category3>外部ファイルデータあり</category3>
	<case>
		1）
		外部ファイルにデータが存在する状態で実行する。
	</case>
	<check>
		1）
		・戻り値が0以上であること。
	</check>
</testitem>*/
TEST(UnitTestDM, Test038)
{
	int ret = DMImport("data\\test38.csv");
	EXPECT_EQ(5, ret);
}

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test039</testname>
	<category1>DMImport</category1>
	<category2>正常系</category2>
	<category3>外部ファイルデータあり</category3>
	<case>
		1）
		外部ファイルにデータが100件以上存在する状態で実行。
	</case>
	<check>
		1）
		・戻り値が100であること。
	</check>
</testitem>*/
TEST(UnitTestDM, Test039)
{
	int ret = DMImport("data\\test39.csv");
	EXPECT_EQ(100, ret);
}

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test040</testname>
	<category1>DMImport</category1>
	<category2>正常系</category2>
	<category3>外部ファイルデータあり</category3>
	<case>
		1)
		外部ファイルのデータの名前が40バイト以上登録されてる状態で実行する。
	</case>
	<check>
		1)
		・一覧表示したときに39文字表示されていること。
	</check>
</testitem>*/
TEST(UnitTestDM, Test040)
{
	DMImport("data\\test40.csv");
	struct data result[DATA_MAX_COUNT] = { 0 };
	DMListFetch(result);


	size_t length = strlen(result[0].name);


	EXPECT_EQ(39, length);
}

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test041</testname>
	<category1>DMImport</category1>
	<category2>正常系</category2>
	<category3>外部ファイルデータあり</category3>
	<case>
		1)
		外部ファイルのデータの読み仮名が40バイト以上登録されてる状態で実行する。
	</case>
	<check>
		1)
		・一覧表示したときに39文字表示されていること。
	</check>
</testitem>*/
TEST(UnitTestDM, Test041)
{
	DMImport("data\\test41.csv");
	struct data result[DATA_MAX_COUNT] = { 0 };
	DMListFetch(result);


	size_t length = strlen(result[0].yomi);


	EXPECT_EQ(39, length);
}

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test042</testname>
	<category1>DMImport</category1>
	<category2>正常系</category2>
	<category3>外部ファイルデータあり
読み込みチェック</category3>
	<case>
		1)
		外部ファイルに5，6，7番が入っている状態で実行し、新規登録で5番を追加する。
	</case>
	<check>
		1)
		・同じ番号が2件ないこと。
		・データが上書きされていること。
	</check>
</testitem>*/
TEST(UnitTestDM, Test042)
{
	int count = 0;
	DMImport("data\\test42.csv");
	DMAddNew(5, "木下拓真", "きのしたたくま");
	struct data result[DATA_MAX_COUNT] = { 0 };
	DMListFetch(result);
	for (int i = 0; i < DATA_MAX_COUNT; i++) {
		if (result[i].number == 5) {
			count++;
		}
	}
	
	EXPECT_EQ(1, count);
	EXPECT_EQ(3, DMGetUserCount());

}

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test043</testname>
	<category1>DMExport</category1>
	<category2>異常系</category2>
	<category3>データファイルなし</category3>
	<case>
		1）
		データファイルが存在しない状態で実行する。
	</case>
	<check>
		1）
		・戻り値が0であること。
	</check>
</testitem>*/
TEST_F(UnitTestDM006, Test043)
{
	int ret = DMExport("data\\test.csv");
	EXPECT_EQ(0, ret);
}

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test044</testname>
	<category1>DMExport</category1>
	<category2>正常系</category2>
	<category3>データファイルあり</category3>
	<case>
		1）
		データファイルが存在する状態で実行する。
	</case>
	<check>
		1）
		・戻り値が0以上であること。
	</check>
</testitem>*/
TEST_F(UnitTestDM012, Test044)
{
	int ret = DMExport("data\\test.csv");
	EXPECT_EQ(1, ret);
}

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test045</testname>
	<category1>DMExport</category1>
	<category2>正常系</category2>
	<category3>データファイルあり
書き込みチェック</category3>
	<case>
		1）
		データファイルが存在する状態で実行する。
	</case>
	<check>
		1)
		・内部データと同じデータが外部ファイルに保存されていること。
	</check>
</testitem>*/
TEST_F(UnitTestDM012, Test045)
{
	DMExport("data\\test.csv");
	DMImport("data\\test.csv");
	struct data result[DATA_MAX_COUNT] = { 0 };
	DMListFetch(result);
	ASSERT_STREQ("木下拓真", result[0].name);

}

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test046</testname>
	<category1>DMExport</category1>
	<category2>異常系</category2>
	<category3>第一引数チェック</category3>
	<case>
		1)
		第一引数をNULLで実行する。
	</case>
	<check>
		1)
		・戻り値が-1であること。
	</check>
</testitem>*/
TEST(UnitTestDM, Test046)
{
	int ret = DMExport(NULL);
	EXPECT_EQ(-1, ret);
}

class UnitTestDM047 : public ::testing::Test
{
public:
	void SetUp()
	{
		remove("data.txt");//ファイル消す
		DMInitialization("data.txt");
		DMAddNew(1, "TEST1", "test1");
		DMAddNew(2, "TEST2", "test2");
		DMAddNew(3, "TEST3", "test3");
		DMAddNew(4, "TEST4", "tsst4");
		DMAddNew(5, "TEST5", "test5");
		DMDelete(5);
		

	}

	void TearDown()
	{
		// 後処理
		DMTerminate("data.txt");
		remove("data.txt");//ファイル消す
	}
};

/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test047</testname>
	<category1>DMExport</category1>
	<category2>正常系</category2>
	<category3>データファイルあり
書き込みチェック</category3>
	<case>
		1)
		5件登録されているデータの1件を削除した状態で実行する。
	</case>
	<check>
		1)
		・削除したデータが出力されないこと。
	</check>
</testitem>*/
TEST_F(UnitTestDM047, Test047)
{
	int ret = DMExport("data\\test.csv");
	EXPECT_EQ(4, ret);
}


