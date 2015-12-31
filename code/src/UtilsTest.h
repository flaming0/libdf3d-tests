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

TEST_F(UtilsTest, StartsWithTest)
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

TEST_F(UtilsTest, ClampTest)
{
    EXPECT_EQ(df3d::utils::clamp(4, 3, 5), 4);
    EXPECT_EQ(df3d::utils::clamp(14, 3, 5), 5);
    EXPECT_EQ(df3d::utils::clamp(-14, 3, 5), 3);
    EXPECT_EQ(df3d::utils::clamp(3, 3, 5), 3);
    EXPECT_EQ(df3d::utils::clamp(5, 3, 5), 5);
}

TEST_F(UtilsTest, EndsWithTest)
{
    EXPECT_TRUE(df3d::utils::ends_with("fdsfdsaa", "dsaa"));
    EXPECT_TRUE(df3d::utils::ends_with("fdsfdsaa", "aa"));
    EXPECT_TRUE(df3d::utils::ends_with("fdsfdsaa", "a"));
    EXPECT_TRUE(df3d::utils::ends_with("fdsfdsaa", "fdsfdsaa"));
    EXPECT_FALSE(df3d::utils::ends_with("fdsfdsaa", "sa"));
    EXPECT_FALSE(df3d::utils::ends_with("fdsfdsaa", "safd"));
    EXPECT_FALSE(df3d::utils::ends_with("fdsfdsaa", "safdfdsfsddfdsf"));
}

TEST_F(UtilsTest, TrimTest)
{
    std::string str1 = "   abcd";
    std::string str2 = "abs   ";
    std::string str3 = "   a ";
    std::string str4 = "   a b c ";

    df3d::utils::trim(str1);
    df3d::utils::trim(str4);
    EXPECT_EQ(str1, "abcd");
    EXPECT_EQ(str4, "a b c");

    df3d::utils::trim_left(str2);
    EXPECT_EQ(str2, "abs   ");
    df3d::utils::trim_right(str2);
    EXPECT_EQ(str2, "abs");
    df3d::utils::trim(str2);
    EXPECT_EQ(str2, "abs");

    df3d::utils::trim(str3);
    EXPECT_EQ(str3, "a");

    str3 = "";
    df3d::utils::trim(str3);
    EXPECT_EQ(str3, "");
}

TEST_F(UtilsTest, ReplaceAllTest)
{
    std::string s1;
    df3d::utils::replace_all(s1, "fd", "ss");
    EXPECT_EQ(s1, "");

    s1 = "afttsfd ftt tff ftty";
    df3d::utils::replace_all(s1, "ftt", ".");
    EXPECT_EQ(s1, "a.sfd . tff .y");

    df3d::utils::replace_all(s1, "a", ".");
    EXPECT_EQ(s1, "..sfd . tff .y");

    df3d::utils::replace_all(s1, ".", "");
    EXPECT_EQ(s1, "sfd  tff y");
}

TEST_F(UtilsTest, AnyTest)
{
    df3d::utils::Any a1;
    EXPECT_TRUE(a1.empty());
    a1.clear();
    EXPECT_TRUE(a1.empty());

    df3d::utils::Any a3(a1);
    EXPECT_TRUE(a3.empty());
    a3.clear();
    EXPECT_TRUE(a3.empty());

    df3d::utils::Any a2(56);
    EXPECT_FALSE(a2.empty());
    EXPECT_EQ(a2.get<int>(), 56);

    df3d::utils::Any a4(a2);
    EXPECT_FALSE(a2.empty());
    EXPECT_EQ(a2.get<int>(), 56);
    EXPECT_FALSE(a4.empty());
    EXPECT_EQ(a4.get<int>(), 56);
}

TEST_F(UtilsTest, DictTest)
{
    df3d::utils::Dict d1;
    EXPECT_FALSE(d1.contains("a_key"));

    d1.set("a_key", 228);
    EXPECT_TRUE(d1.contains("a_key"));
    EXPECT_EQ(d1.get<int>("a_key"), 228);

    d1.set("a_key", 2298);
    EXPECT_EQ(d1.get<int>("a_key"), 2298);

    d1.erase("a_key");
    EXPECT_FALSE(d1.contains("a_key"));
}
