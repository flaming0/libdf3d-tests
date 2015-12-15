#pragma once

#include <gtest/gtest.h>
#include <df3d.h>

class EcsCoreTest : public testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(EcsCoreTest, EntityManagerTest)
{
    auto e = df3d::world().spawn();
    EXPECT_TRUE(e.valid());
    EXPECT_TRUE(df3d::world().alive(e));
    df3d::world().destroy(e);
    EXPECT_FALSE(df3d::world().alive(e));
    EXPECT_TRUE(e.valid());

    std::vector<df3d::Entity> entities;
    for (int i = 0; i < 100; i++)
        entities.push_back(df3d::world().spawn());

    for (auto e : entities)
    {
        EXPECT_TRUE(e.valid());
        EXPECT_TRUE(df3d::world().alive(e));
    }

    for (auto e : entities)
        df3d::world().destroy(e);

    for (auto e : entities)
    {
        EXPECT_TRUE(e.valid());
        EXPECT_FALSE(df3d::world().alive(e));
    }
}
