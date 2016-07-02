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
    df3d::svc().replaceWorld(0, "data/test_world.world");
    world().setCamera(df3d::FPSCamera::createDefault(1.0f));
    world().physics().getPhysicsWorld()->setGravity({ 0.0f, -10.0f, 0.0f });

    // Partially manually.
    auto e = world().spawn();

    world().staticMesh().add(e, "data/cube_textured.obj", df3d::ResourceLoadingMode::IMMEDIATE);
    world().sceneGraph().translate(e, { 0.0f, -10.0, 0.0f });
    world().sceneGraph().scale(e, { 50.0f, 0.0001f, 50.0f });
    df3d::PhysicsComponentCreationParams params;
    params.mass = 0.0f;     // Make it static body.
    params.shape = df3d::CollisionShapeType::BOX;
    world().physics().add(e, params, world().staticMesh().getMeshData(e));

    //df3d::svc().debugConsole()->getCVars().set(df3d::CVAR_DEBUG_DRAW, "1");

    auto testEnt = world().spawn(std::string("data/teapot.entity"));

    world().timeManager().subscribeUpdate([testEnt]() {
        if (df3d::svc().inputManager().getKey(df3d::KeyCode::KEY_7))
            world().sceneGraph().translate(testEnt, { 0.0f, -0.3f, 0.0f });
        else if (df3d::svc().inputManager().getKey(df3d::KeyCode::KEY_8))
            world().sceneGraph().translate(testEnt, { 0.0f, 0.3f, 0.0f });
        else if (df3d::svc().inputManager().getKey(df3d::KeyCode::KEY_6))
            world().sceneGraph().scale(testEnt, { 1.001f, 1.001f, 1.001f });
        else if (df3d::svc().inputManager().getKey(df3d::KeyCode::KEY_5))
            world().sceneGraph().rotatePitch(testEnt, 1.0f);
        else if (df3d::svc().inputManager().getKey(df3d::KeyCode::KEY_4))
            world().sceneGraph().rotateYaw(testEnt, 1.0f);

        if (df3d::svc().inputManager().getMouseButtonReleased(df3d::MouseButton::MIDDLE))
            world().sceneGraph().detachAllChildren(testEnt);

        if (df3d::svc().inputManager().getKeyPressed(df3d::KeyCode::KEY_0))
        {
            auto e1 = world().sceneGraph().getByName("first");
            //world().destroy(testEnt);
            world().sceneGraph().detachChild(testEnt, e1);
        }
        if (df3d::svc().inputManager().getKeyPressed(df3d::KeyCode::KEY_1))
        {
            auto e1 = world().sceneGraph().getByName("second");
            //world().destroy(e1);
            world().sceneGraph().detachChild(testEnt, e1);
        }

        if (df3d::svc().inputManager().getKey(df3d::KeyCode::KEY_2))
        {
            auto e1 = world().sceneGraph().getByName("first");
            world().sceneGraph().attachChild(testEnt, e1);
        }
        if (df3d::svc().inputManager().getKey(df3d::KeyCode::KEY_3))
        {
            auto e1 = world().sceneGraph().getByName("second");
            world().sceneGraph().attachChild(testEnt, e1);
        }
    });

    return true;
}

void df3dSetApplicationDelegate()
{
    df3d::Application::setupDelegate(make_unique<TestAppDelegate>());
}
