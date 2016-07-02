#include <gtest/gtest.h>
#include "Common.h"
#include <df3d/df3d.h>

class ArrayTest : public testing::Test
{
protected:
    void SetUp() override
    {
        m_malloc = new df3d::MallocAllocator();
    }

    void TearDown() override
    {
        delete m_malloc;
    }

    df3d::MallocAllocator *m_malloc = nullptr;
};

TEST_F(ArrayTest, DefaultCtor)
{
    df3d::PodArray<int> a1(m_malloc);

    EXPECT_EQ(0, a1.capacity());
    EXPECT_EQ(0, a1.size());
    EXPECT_TRUE(a1.empty());
}

TEST_F(ArrayTest, CountCtor)
{
    size_t sz = 100;

    df3d::PodArray<int> a1(m_malloc, sz, 22);

    EXPECT_EQ(sz, a1.size());
    EXPECT_GE(a1.capacity(), a1.size());

    for (size_t i = 0; i < a1.size(); i++)
        EXPECT_EQ(a1[i], 22);

    df3d::PodArray<int> a2(m_malloc, 0);
    EXPECT_EQ(0, a2.size());

    df3d::PodArray<int> a3(m_malloc, sz);
    EXPECT_EQ(sz, a3.size());

    for (size_t i = 0; i < a3.size(); i++)
        EXPECT_EQ(a3[i], 0);
}

TEST_F(ArrayTest, CopyCtor)
{
    const size_t sz = 50;

    df3d::PodArray<int> a1(m_malloc, sz, 23);
    df3d::PodArray<int> a2 = a1;

    EXPECT_FALSE(a1.empty());
    EXPECT_FALSE(a2.empty());

    EXPECT_EQ(sz, a1.size());
    EXPECT_EQ(sz, a2.size());

    for (int i = 0; i < sz; i++)
    {
        EXPECT_EQ(a1[i], a2[i]);
        EXPECT_EQ(a1[i], 23);
    }
}

TEST_F(ArrayTest, MoveCtor)
{
    const size_t sz = 500;

    df3d::PodArray<int> a1(m_malloc, sz, 21);
    df3d::PodArray<int> a2(std::move(a1));

    EXPECT_EQ(a2.size(), sz);
    for (int i = 0; i < sz; i++)
    {
        EXPECT_EQ(21, a2[i]);
    }

    EXPECT_EQ(a1.size(), 0);
    EXPECT_EQ(a1.capacity(), 0);
    EXPECT_EQ(a1.data(), nullptr);
}

TEST_F(ArrayTest, AssignOp)
{
    const size_t sz = 1505;

    df3d::PodArray<int> a1(m_malloc, sz, 5);
    df3d::PodArray<int> a2(m_malloc);

    EXPECT_EQ(a2.size(), 0);
    EXPECT_EQ(a1.size(), sz);
    for (size_t i = 0; i < sz; i++)
        EXPECT_EQ(a1[i], 5);

    a2 = a1;

    EXPECT_EQ(a2.size(), sz);
    EXPECT_GE(a2.capacity(), sz);

    EXPECT_EQ(a1.size(), sz);

    EXPECT_NE(a1.data(), a2.data());

    for (size_t i = 0; i < sz; i++)
    {
        EXPECT_EQ(a1[i], a2[i]);
        EXPECT_EQ(a1[i], 5);
    }
}

TEST_F(ArrayTest, PushBack)
{
    const int SZ = 150000;

    df3d::PodArray<int> a1(m_malloc);
    EXPECT_EQ(a1.size(), 0);

    for (int i = 0; i < SZ; i++)
        a1.push_back(i);

    EXPECT_EQ(a1.size(), SZ);
    EXPECT_GE(a1.capacity(), a1.size());

    for (int i = 0; i < SZ; i++)
        EXPECT_EQ(a1[i], i);
}

TEST_F(ArrayTest, Resize)
{
    df3d::PodArray<int> a1(m_malloc);
    EXPECT_EQ(a1.size(), 0);

    const size_t SZ = 500;
    a1.resize(SZ);
    EXPECT_EQ(a1.size(), SZ);
    for (size_t i = 0; i < SZ; i++)
        a1[i] = i;
    for (size_t i = 0; i < SZ; i++)
        EXPECT_EQ(a1[i], i);

    a1.resize(SZ / 2);
    EXPECT_EQ(a1.size(), SZ / 2);
    for (size_t i = 0; i < a1.size(); i++)
        EXPECT_EQ(a1[i], i);

    auto prevSz = a1.size();

    a1.resize(SZ * 10);
    for (size_t i = 0; i < prevSz; i++)
        EXPECT_EQ(a1[i], i);
}

TEST_F(ArrayTest, Reserve)
{
    df3d::PodArray<int> a1(m_malloc);
    EXPECT_EQ(a1.size(), 0u);
    EXPECT_GE(a1.capacity(), 0u);

    const size_t sz = 200;

    a1.reserve(sz);
    EXPECT_EQ(a1.size(), 0);
    EXPECT_GE(a1.capacity(), sz);
}

TEST_F(ArrayTest, Clear)
{
    df3d::PodArray<int> a1(m_malloc);
    EXPECT_EQ(a1.size(), 0);

    const size_t SZ = 500;
    a1.resize(SZ);
    EXPECT_EQ(a1.size(), SZ);

    for (size_t i = 0; i < SZ; i++)
        a1[i] = i;

    for (int i = 0; i < SZ; i++)
        EXPECT_EQ(a1[i], i);

    a1.clear();
    EXPECT_EQ(a1.size(), 0);

    for (int i = 0; i < SZ; i++)
        a1.push_back(i + 600);
    EXPECT_EQ(a1.size(), SZ);
    for (int i = 0; i < SZ; i++)
        EXPECT_EQ(a1[i], i + 600);
}

TEST_F(ArrayTest, ShrinkToFit)
{
    df3d::PodArray<int> a1(m_malloc);
    EXPECT_EQ(a1.size(), 0);

    a1.shrink_to_fit();
    EXPECT_EQ(a1.size(), 0);

    const size_t SZ = 550;
    for (size_t i = 0; i < SZ; i++)
        a1.push_back(i);
    EXPECT_EQ(a1.size(), SZ);

    if (a1.size() == a1.capacity())
        a1.push_back(SZ + 1);

    EXPECT_LT(a1.size(), a1.capacity());

    a1.shrink_to_fit();

    EXPECT_EQ(a1.capacity(), a1.size());
    for (size_t i = 0; i < a1.size(); i++)
        EXPECT_EQ(a1[i], i);

    const size_t newSZ = 150;
    a1.resize(newSZ);
    for (size_t i = 0; i < newSZ; i++)
        EXPECT_EQ(a1[i], i);

    a1.resize(2000);
    for (size_t i = 0; i < newSZ; i++)
        EXPECT_EQ(a1[i], i);

    a1.shrink_to_fit();
    EXPECT_EQ(a1.capacity(), a1.size());
    for (size_t i = 0; i < newSZ; i++)
        EXPECT_EQ(a1[i], i);

    a1.clear();
    a1.shrink_to_fit();
    EXPECT_EQ(a1.capacity(), a1.size());
    EXPECT_EQ(a1.capacity(), 0u);
}

TEST_F(ArrayTest, Access)
{
    df3d::PodArray<int> a1(m_malloc);

    a1.push_back(55);

    ASSERT_EQ(a1.size(), 1u);
    EXPECT_GE(a1.capacity(), a1.size());
    EXPECT_EQ(a1[0], 55);
    EXPECT_EQ(*a1.data(), 55);

    *a1.data() = 56;

    EXPECT_EQ(a1[0], 56);
    EXPECT_EQ(*a1.data(), 56);

    df3d::PodArray<int> a2(m_malloc);

    a2.push_back(33);
    EXPECT_EQ(a2.front(), 33);
    EXPECT_EQ(a2.back(), 33);

    a2.push_back(43);
    EXPECT_EQ(a2.front(), 33);
    EXPECT_EQ(a2.back(), 43);

    a2.push_back(77);

    EXPECT_EQ(a2.back(), 77);

    a2.front() = 90;
    a2.back() = 100;

    EXPECT_EQ(a2.front(), 90);
    EXPECT_EQ(a2.back(), 100);
    EXPECT_EQ(a2[1], 43);
}

TEST_F(ArrayTest, Iterator)
{
    df3d::PodArray<int> a1(m_malloc);

    const size_t SZ = 500;
    a1.resize(SZ);
    EXPECT_EQ(a1.size(), SZ);

    for (size_t i = 0; i < SZ; i++)
        a1[i] = i;

    size_t idx = 0;
    for (auto el : a1)
        EXPECT_EQ(el, idx++);

    idx = 1000;
    for (auto &el : a1)
        el = idx++;

    idx = 1000;
    for (auto el : a1)
        EXPECT_EQ(el, idx++);
}
