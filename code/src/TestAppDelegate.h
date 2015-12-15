#pragma once

#include "df3d.h"

class TestAppDelegate : public df3d::AppDelegate
{
public:
    df3d::EngineInitParams getInitParams() const override;

    bool onAppStarted() override;
    void onAppEnded() override;

    void onAppPaused() override;
    void onAppResumed() override;
};
