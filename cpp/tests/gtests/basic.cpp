#include <gtest/gtest.h>

int addFunction(int, int);

int addFunction(int a, int b) {
    return a + b;
}

TEST(TestAddFunction, FirstTry) {
    ASSERT_EQ(2 + 2, 4);
}
TEST(TestAddFunction, FirstFail) {
    ASSERT_EQ(2 + 2, 5) << "Testing the add function. It must fail here";
}
TEST(TestNumbers, FirstOne) {
    ASSERT_GE(4, 3);
}
TEST(TestStrings, FirstTest) {
    ASSERT_STREQ("bla", "bla");
}
TEST(TestStrings, SecondTest) {
    ASSERT_STRNE("bla", "bla");
}
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
