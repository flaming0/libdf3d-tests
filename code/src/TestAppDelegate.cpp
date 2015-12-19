#include "TestAppDelegate.h"

#include <gtest/gtest.h>
#include "EcsCoreTest.h"

df3d::EngineInitParams TestAppDelegate::getInitParams() const
{
    auto params = df3d::EngineInitParams();
    params.createConsole = true;
    return params;
}

bool TestAppDelegate::onAppStarted()
{
    //int argc = 1;
    //char* argv[] = { "app" };
    //::testing::InitGoogleTest(&argc, argv);

    //RUN_ALL_TESTS();

    auto e1 = df3d::world().spawn();
    df3d::world().staticMesh().add(e1, "data/teapot.obj", df3d::ResourceLoadingMode::IMMEDIATE);
    df3d::world().transform().setPosition(df3d::world().transform().lookup(e1), glm::vec3(0.0f, 0.0f, -20.0f));
    df3d::world().transform().setScale(df3d::world().transform().lookup(e1), glm::vec3(4.0f, 4.0f, 4.0f));

    df3d::world().setCamera(make_shared<df3d::FPSCamera>(1.0f, true));
    //df3d::svc().debugConsole()->show();

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
