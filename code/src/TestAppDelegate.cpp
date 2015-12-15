#include "TestAppDelegate.h"

#include <gtest/gtest.h>
#include "EcsCoreTest.h"

df3d::EngineInitParams TestAppDelegate::getInitParams() const
{
    return df3d::EngineInitParams();
}

bool TestAppDelegate::onAppStarted()
{
    int argc = 1;
    char* argv[] = { "app" };
    ::testing::InitGoogleTest(&argc, argv);

    RUN_ALL_TESTS();

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
