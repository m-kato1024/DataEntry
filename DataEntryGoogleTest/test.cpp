#include "gtest/gtest.h"

extern "C"
{

#include "./../DataEntry/DataEntry.h"

}


// UI側のテストケース１
// main()の戻り値が1であればOK
TEST(UITest, Test001) {
	EXPECT_EQ(1, testMethod());
}
