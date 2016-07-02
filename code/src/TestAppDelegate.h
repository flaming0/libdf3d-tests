#pragma once

#include <df3d/df3d.h>

class TestAppDelegate : public df3d::AppDelegate
{
public:
    df3d::EngineInitParams getInitParams() const override;

    bool onAppStarted() override;
    void onAppEnded() override { }

    void onAppWillResignActive() override { }
    void onAppDidEnterBackground() override { }

    void onAppWillEnterForeground() override { }
    void onAppDidBecomeActive() override { }

    void onRenderDestroyed() override { }
    void onRenderRecreated() override { }
};
