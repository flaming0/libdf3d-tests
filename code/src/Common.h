#pragma once

#include <df3d/df3d.h>

df3d::World& world()
{
    return df3d::svc().world(0);
}
