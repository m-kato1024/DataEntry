#include "gtest/gtest.h"

extern "C"
{

#include "./../DataEntry/DataEntry.h"

}


// UI���̃e�X�g�P�[�X�P
// main()�̖߂�l��1�ł����OK
TEST(UITest, Test001) {
	EXPECT_EQ(1, testMethod());
}
