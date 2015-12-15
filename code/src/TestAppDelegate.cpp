#include "TestAppDelegate.h"

df3d::EngineInitParams TestAppDelegate::getInitParams() const
{
    return df3d::EngineInitParams();
}

bool TestAppDelegate::onAppStarted()
{
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
