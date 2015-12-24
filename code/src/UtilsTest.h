#include <gtest/gtest.h>
#include <df3d.h>

class UtilsTest : public testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(UtilsTest, SplitTest)
{
    std::string str1 = " a bbbb c d ";
    std::string str2 = "";
    std::string str3 = "aaa";
    std::string str4 = "a b";

    auto res1 = df3d::utils::split(str1, ' ');
    auto res2 = df3d::utils::split(str2, ' ');
    auto res3 = df3d::utils::split(str3, ' ');
    auto res4 = df3d::utils::split(str4, ' ');

    ASSERT_EQ(res1.size(), 4);
    ASSERT_EQ(res2.size(), 0);
    ASSERT_EQ(res3.size(), 1);
    ASSERT_EQ(res4.size(), 2);

}

TEST_F(UtilsTest, StartsWith)
{
    std::string str1 = "abcd";
    std::string str2 = "--xx";
    std::string str3 = "aaabbbb";

    EXPECT_TRUE(df3d::utils::starts_with(str1, "a"));
    EXPECT_TRUE(df3d::utils::starts_with(str1, "ab"));
    EXPECT_FALSE(df3d::utils::starts_with(str1, "cd"));
    EXPECT_TRUE(df3d::utils::starts_with(str2, "--x"));
    EXPECT_TRUE(df3d::utils::starts_with(str3, "aaabbbb"));
    EXPECT_FALSE(df3d::utils::starts_with(str3, "aaabbbbaaa"));
    EXPECT_TRUE(df3d::utils::starts_with(str3, "aaabbb"));
    EXPECT_TRUE(df3d::utils::starts_with(str3, "a"));
}

TEST_F(UtilsTest, Clamp)
{
    EXPECT_EQ(df3d::utils::clamp(4, 3, 5), 4);
    EXPECT_EQ(df3d::utils::clamp(14, 3, 5), 5);
    EXPECT_EQ(df3d::utils::clamp(-14, 3, 5), 3);
    EXPECT_EQ(df3d::utils::clamp(3, 3, 5), 3);
    EXPECT_EQ(df3d::utils::clamp(5, 3, 5), 5);
}

TEST_F(UtilsTest, EndsWith)
{

}
