#include "gtest/gtest.h"


extern "C"
{

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
	bool ret = DMInitialization("data.txt");
	EXPECT_EQ(true, ret);
	EXPECT_EQ(0, DMGetUserCount());
}


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
TEST(UnitTestDM, Test004)
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
TEST(UnitTestDM, Test005)
{
	bool ret = DMAddNew(11, "木下拓真", "きのしたたくま");
	EXPECT_EQ(false, ret);
}


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
TEST(UnitTestDM, Test006)
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
TEST(UnitTestDM, Test007)
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
TEST(UnitTestDM, Test008)
{
	bool ret = DMAddNew(2, "木下拓真", "きのしたたくま");
	EXPECT_EQ(true, ret);
	EXPECT_EQ(2, DMGetUserCount());
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
TEST(UnitTestDM, Test009)
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
TEST(UnitTestDM, Test010)
{
	bool ret = DMAddNew(3, "木下拓真", "きのしたたくま");
	EXPECT_EQ(true, ret);
	EXPECT_EQ(3, DMGetUserCount());
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
		・NOが初期化されていないこと。
		・名前が初期化されていないこと。
		・読み仮名が初期化されていないこと。
		・件数の変化がないこと。
	</check>
</testitem>*/
TEST(UnitTestDM, Test011)
{
	
}


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
TEST(UnitTestDM, Test012)
{
	DMDelete(1);
	EXPECT_EQ(2, DMGetUserCount());
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
TEST(UnitTestDM, Test013)
{
	////データファイルを消しておく
	//remove("data.txt");
	//struct data result[DATA_MAX_COUNT];
	//int ret = DMListFetch(result);
	//EXPECT_EQ(0, ret);

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
TEST(UnitTestDM, Test014)
{
	struct data result[DATA_MAX_COUNT];
	int ret = DMListFetch(result);
	EXPECT_EQ(2, ret);
	
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
TEST(UnitTestDM, Test016)
{
	struct data search_result[DATA_MAX_COUNT];
	int ret = DMSearch("きのしたたくま",search_result);
	EXPECT_EQ(2, ret);
}


/*
--------------------------------------------------------------------------------
<testitem>
	<testclass>UnitTestDM</testclass>
	<testname>Test017</testname>
	<category1>DMTerminate</category1>
	<category2>異常系</category2>
	<category3>データファイルなし</category3>
	<case>
		1）
		データファイルが存在しない状態で実行する。
	</case>
	<check>
		1）
		・戻り値がfalseであること。
		・強制終了しないこと。
	</check>
</testitem>*/
TEST(UnitTestDM, Test017)
{
	remove("data.txt");
	bool ret = DMTerminate("data.txt");
	EXPECT_EQ(false, ret);
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
TEST(UnitTestDM, Test018)
{

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
TEST(UnitTestDM, Test019)
{
	/*remove("data.txt");
	int ret = DMGetUserCount();
	EXPECT_EQ(2, ret);*/
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
TEST(UnitTestDM, Test021)
{

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
TEST(UnitTestDM, Test022)
{

}


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
TEST(UnitTestDM, Test023)
{

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
TEST(UnitTestDM, Test024)
{

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
TEST(UnitTestDM, Test025)
{

}


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
		・39文字の中で検索されること
	</check>
</testitem>*/
TEST(UnitTestDM, Test026)
{

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
TEST(UnitTestDM, Test027)
{

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
TEST(UnitTestDM, Test028)
{

}


