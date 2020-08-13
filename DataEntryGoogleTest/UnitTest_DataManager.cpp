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
