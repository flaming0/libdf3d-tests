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

TEST_F(EcsCoreTest, TagComponentProcessorTest)
{
    std::vector<df3d::Entity> ents;
    for (int i = 0; i < 100; i++)
        ents.push_back(df3d::world().spawn());

    df3d::TagComponentProcessor tags;

    int MEGA_TAG = 4;
    int OTHER_MEGA_TAG = 2;

    for (auto e : ents)
        tags.add(e, MEGA_TAG);

    for (auto e : ents)
    {
        EXPECT_TRUE(tags.hasTag(e, MEGA_TAG));
        EXPECT_FALSE(tags.hasTag(e, OTHER_MEGA_TAG));
    }

    auto withTag = tags.getEntities(OTHER_MEGA_TAG);
    EXPECT_TRUE(withTag.empty());

    withTag = tags.getEntities(MEGA_TAG);
    for (auto e : ents)
        EXPECT_TRUE(withTag.count(e) == 1);

    for (auto e : ents)
        tags.remove(e);

    for (auto e : ents)
    {
        EXPECT_FALSE(tags.hasTag(e, MEGA_TAG));
        EXPECT_FALSE(tags.hasTag(e, OTHER_MEGA_TAG));
    }

    for (int i = 0; i < 100; i++)
        tags.add(ents[i], i);

    for (int i = 0; i < 100; i++)
        EXPECT_TRUE(tags.hasTag(ents[i], i));

    std::list<df3d::Entity> cleaning(ents.begin(), ents.end());
    (static_cast<df3d::EntityComponentProcessor&>(tags)).cleanStep(cleaning);

    for (int i = 0; i < 100; i++)
        EXPECT_FALSE(tags.hasTag(ents[i], i));

    for (auto e : ents)
        df3d::world().destroy(e);

    ents.clear();

    for (int i = 0; i < 100; i++)
        ents.push_back(df3d::world().spawn());

    for (auto e : ents)
    {
        tags.add(e, MEGA_TAG);
        tags.add(e, OTHER_MEGA_TAG);
    }

    for (auto e : ents)
    {
        EXPECT_TRUE(tags.hasTag(e, MEGA_TAG));
        EXPECT_TRUE(tags.hasTag(e, OTHER_MEGA_TAG));
    }

    for (auto e : ents)
        tags.remove(e);

    for (auto e : ents)
    {
        EXPECT_FALSE(tags.hasTag(e, MEGA_TAG));
        EXPECT_FALSE(tags.hasTag(e, OTHER_MEGA_TAG));
    }
}
