#include "gtest/gtest.h"

int main(int argc, char **argv) {

	::testing::InitGoogleTest(&argc, argv);

	//特定の試験だけ実施したい場合のフィルター
	//::testing::GTEST_FLAG(filter) = "*.Test017";

	return RUN_ALL_TESTS();
}
