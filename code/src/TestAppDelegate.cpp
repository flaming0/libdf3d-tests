#include "TestAppDelegate.h"

#include <gtest/gtest.h>
#include "EcsCoreTest.h"

df3d::EngineInitParams TestAppDelegate::getInitParams() const
{
    auto params = df3d::EngineInitParams();
    params.createConsole = true;
    params.windowWidth = 1280;
    params.windowHeight = 960;
    return params;
}

bool TestAppDelegate::onAppStarted()
{
    int argc = 1;
    char* argv[] = { "app" };
    ::testing::InitGoogleTest(&argc, argv);

    RUN_ALL_TESTS();

    auto e2 = df3d::world().spawn();
    df3d::world().audio().add(e2, "data/4mjb00vZq77d.ogg");
    df3d::world().audio().play(e2);

    df3d::replaceWorld(df3d::World::newWorld("data/test_world.world"));
    df3d::world().setCamera(make_shared<df3d::FPSCamera>(1.0f, true));

    return true;
}

void TestAppDelegate::onAppEnded()
{

}

void TestAppDelegate::onAppPaused()
{

}

void TestAppDelegate::onAppResumed()
{

}

void df3dInitialized()
{
    df3d::Application::setupDelegate(make_unique<TestAppDelegate>());
}
