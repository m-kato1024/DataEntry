#include "gtest/gtest.h"

int main(int argc, char **argv) {

	::testing::InitGoogleTest(&argc, argv);

	//����̎����������{�������ꍇ�̃t�B���^�[
	//::testing::GTEST_FLAG(filter) = "*.Test017";

	return RUN_ALL_TESTS();
}
