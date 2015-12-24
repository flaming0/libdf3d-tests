#include "TestAppDelegate.h"

#include <gtest/gtest.h>
#include "EcsCoreTest.h"
#include "UtilsTest.h"

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

    // Partially load from scene def file.
    df3d::replaceWorld("data/test_world.world");
    df3d::world().setCamera(make_shared<df3d::FPSCamera>(1.0f, true));
    df3d::world().physics().getPhysicsWorld()->setGravity({ 0.0f, -10.0f, 0.0f });

    // Partially manually.
    auto e = df3d::world().spawn();

    df3d::world().staticMesh().add(e, "data/cube_textured.obj", df3d::ResourceLoadingMode::IMMEDIATE);
    df3d::world().transform().translate(e, { 0.0f, -10.0, 0.0f });
    df3d::world().transform().scale(e, { 50.0f, 0.0001f, 50.0f });
    df3d::PhysicsComponentCreationParams params;
    params.mass = 0.0f;     // Make it static body.
    df3d::world().physics().add(e, params, df3d::world().staticMesh().getMeshData(e));

    //df3d::svc().debugConsole()->getCVars().set(df3d::CVAR_DEBUG_DRAW, "1");

    auto testEnt = df3d::world().spawn(std::string("data/teapot.entity"));

    df3d::svc().world().timeManager().subscribeUpdate([testEnt]() {
        if (df3d::svc().inputManager().getKey(df3d::KeyCode::KEY_7))
            df3d::world().transform().translate(testEnt, { 0.0f, -0.3f, 0.0f });
        else if (df3d::svc().inputManager().getKey(df3d::KeyCode::KEY_8))
            df3d::world().transform().translate(testEnt, { 0.0f, 0.3f, 0.0f });
        else if (df3d::svc().inputManager().getKey(df3d::KeyCode::KEY_6))
            df3d::world().transform().scale(testEnt, { 1.001f, 1.001f, 1.001f });
        else if (df3d::svc().inputManager().getKey(df3d::KeyCode::KEY_5))
            df3d::world().transform().rotatePitch(testEnt, 1.0f);
        else if (df3d::svc().inputManager().getKey(df3d::KeyCode::KEY_4))
            df3d::world().transform().rotateYaw(testEnt, 1.0f);

        if (df3d::svc().inputManager().getMouseButtonReleased(df3d::MouseButton::MIDDLE))
            df3d::world().transform().detachAllChildren(testEnt);

        if (df3d::svc().inputManager().getKeyPressed(df3d::KeyCode::KEY_0))
        {
            auto e1 = df3d::world().debugName().getByName("first");
            //df3d::world().destroy(testEnt);
            df3d::world().transform().detachChild(testEnt, e1);
        }
        if (df3d::svc().inputManager().getKeyPressed(df3d::KeyCode::KEY_1))
        {
            auto e1 = df3d::world().debugName().getByName("second");
            //df3d::world().destroy(e1);
            df3d::world().transform().detachChild(testEnt, e1);
        }

        if (df3d::svc().inputManager().getKey(df3d::KeyCode::KEY_2))
        {
            auto e1 = df3d::world().debugName().getByName("first");
            df3d::world().transform().attachChild(testEnt, e1);
        }
        if (df3d::svc().inputManager().getKey(df3d::KeyCode::KEY_3))
        {
            auto e1 = df3d::world().debugName().getByName("second");
            df3d::world().transform().attachChild(testEnt, e1);
        }
    });

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
