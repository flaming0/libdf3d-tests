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
/*
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
}*/

TEST_F(EcsCoreTest, DataHolderTest)
{
    struct MyData
    {
        std::string idstr;
        int idint = 0;
    };

    df3d::ComponentDataHolder<MyData> holder1;

    const int SZ = 1000;

    std::vector<df3d::Entity> ents;
    for (int i = 0; i < SZ; i++)
    {
        ents.push_back(df3d::world().spawn());

        MyData d;
        d.idint = ents.back().id;
        d.idstr = std::to_string(d.idint) + "_ent";

        holder1.add(ents.back(), d);
    }

    for (auto e : ents)
    {
        EXPECT_TRUE(df3d::world().alive(e));
        ASSERT_TRUE(holder1.lookup(e).valid());
        EXPECT_TRUE(holder1.getData(e).idint == e.id);
        EXPECT_TRUE(holder1.getData(e).idstr == std::to_string(e.id) + "_ent");
    }

    for (int i = SZ / 2; i > 0; i--)
    {
        holder1.remove(ents[i]);

        EXPECT_FALSE(holder1.lookup(ents[i]).valid());
    }

    for (auto e : ents)
    {
        auto inst = holder1.lookup(e);
        if (inst.valid())
        {
            EXPECT_TRUE(holder1.getData(inst).idint == e.id);
            EXPECT_TRUE(holder1.getData(inst).idstr == std::to_string(e.id) + "_ent");
        }
    }

    EXPECT_TRUE(holder1.getSize() == SZ / 2);

    holder1.clear();
    EXPECT_TRUE(holder1.getSize() == 0);

    for (auto e : ents)
        df3d::world().destroy(e);
    ents.clear();

    // Random test.

    for (int i = 0; i < SZ; i++)
    {
        ents.push_back(df3d::world().spawn());

        MyData d;
        d.idint = ents.back().id;
        d.idstr = std::to_string(d.idint) + "_ent";

        holder1.add(ents.back(), d);
    }

    for (auto e : ents)
    {
        EXPECT_TRUE(df3d::world().alive(e));
        ASSERT_TRUE(holder1.lookup(e).valid());
        EXPECT_TRUE(holder1.getData(e).idint == e.id);
        EXPECT_TRUE(holder1.getData(e).idstr == std::to_string(e.id) + "_ent");
    }

    while (holder1.getSize() != SZ / 2)
    {
        auto idx = std::rand() % ents.size();
        auto e = ents.at(idx);

        holder1.remove(e);
        df3d::world().destroy(e);
        ents.erase(ents.begin() + idx);
    }

    for (auto e : ents)
    {
        EXPECT_TRUE(df3d::world().alive(e));
        ASSERT_TRUE(holder1.lookup(e).valid());
        EXPECT_TRUE(holder1.getData(e).idint == e.id);
        EXPECT_TRUE(holder1.getData(e).idstr == std::to_string(e.id) + "_ent");
    }

    while (holder1.getSize() != 0)
    {
        auto idx = std::rand() % ents.size();
        auto e = ents.at(idx);

        holder1.remove(e);
        df3d::world().destroy(e);
        ents.erase(ents.begin() + idx);
    }

    for (auto e : ents)
        EXPECT_FALSE(df3d::world().alive(e));

    EXPECT_TRUE(holder1.getSize() == 0);
}
