cmake_minimum_required(VERSION 3.1)

project(ships3d)

include(${PROJECT_SOURCE_DIR}/libdf3d/cmake/libdf3d.cmake)
include(${PROJECT_SOURCE_DIR}/libdf3d/cmake/cotire.cmake)

# Include all the game dependencies.
add_subdirectory(${PROJECT_SOURCE_DIR}/libdf3d)
add_subdirectory(${PROJECT_SOURCE_DIR}/third-party/src/squirrel)

if (ANDROID)
    find_host_package(Boost REQUIRED)
else()
    find_package(Boost REQUIRED)
endif()

set(ships3d_HEADER_LIST
    ${PROJECT_SOURCE_DIR}/src/Ships3dAppDelegate.h
    ${PROJECT_SOURCE_DIR}/src/stdafx.h
    ${PROJECT_SOURCE_DIR}/src/effects/SpaceParticles.h
    ${PROJECT_SOURCE_DIR}/src/effects/SunGlowOverlay.h
    ${PROJECT_SOURCE_DIR}/src/effects/NPCVisuals.h
    ${PROJECT_SOURCE_DIR}/src/game/inventory/InventoryItem.h
    ${PROJECT_SOURCE_DIR}/src/game/missions/Mission.h
    ${PROJECT_SOURCE_DIR}/src/game/missions/BattleMission.h
    ${PROJECT_SOURCE_DIR}/src/game/missions/MissionTriggers.h
    ${PROJECT_SOURCE_DIR}/src/game/ArcballCamera.h
    ${PROJECT_SOURCE_DIR}/src/game/AsteroidObstacle.h
    ${PROJECT_SOURCE_DIR}/src/game/CollisionListener.h
    ${PROJECT_SOURCE_DIR}/src/game/Constants.h
    ${PROJECT_SOURCE_DIR}/src/game/NPCShip.h
    ${PROJECT_SOURCE_DIR}/src/game/NPCShipAIControlBlock.h
    ${PROJECT_SOURCE_DIR}/src/game/NPCLifecycle.h
    ${PROJECT_SOURCE_DIR}/src/game/Events.h
    ${PROJECT_SOURCE_DIR}/src/game/FPSCamera.h
    ${PROJECT_SOURCE_DIR}/src/game/GameConfigs.h
    ${PROJECT_SOURCE_DIR}/src/game/GameController.h
    ${PROJECT_SOURCE_DIR}/src/game/GameEntity.h
    ${PROJECT_SOURCE_DIR}/src/game/GameEntityLifecycle.h
    ${PROJECT_SOURCE_DIR}/src/game/GameplayRequirements.h
    ${PROJECT_SOURCE_DIR}/src/game/GameState.h
    ${PROJECT_SOURCE_DIR}/src/game/Gun.h
    ${PROJECT_SOURCE_DIR}/src/game/PlayerLifecycle.h
    ${PROJECT_SOURCE_DIR}/src/game/PlayerShip.h
    ${PROJECT_SOURCE_DIR}/src/game/PlayerShipCamera.h
    ${PROJECT_SOURCE_DIR}/src/game/ShipMovement.h
    ${PROJECT_SOURCE_DIR}/src/scenes/DebugTestScene.h
    ${PROJECT_SOURCE_DIR}/src/scenes/DebugViewer.h
    ${PROJECT_SOURCE_DIR}/src/scenes/GalaxyMap.h
    ${PROJECT_SOURCE_DIR}/src/scenes/GameScene.h
    ${PROJECT_SOURCE_DIR}/src/scenes/Hangar.h
    ${PROJECT_SOURCE_DIR}/src/scenes/Level.h
    ${PROJECT_SOURCE_DIR}/src/scenes/LevelVisuals.h
    ${PROJECT_SOURCE_DIR}/src/scenes/MainMenu.h
    ${PROJECT_SOURCE_DIR}/src/script/ScriptBindings.h
    ${PROJECT_SOURCE_DIR}/src/script/ScriptManager.h
    ${PROJECT_SOURCE_DIR}/src/ui/DefaultPopup.h
    ${PROJECT_SOURCE_DIR}/src/ui/GalaxyMapUi.h
    ${PROJECT_SOURCE_DIR}/src/ui/GuiEventsProxy.h
    ${PROJECT_SOURCE_DIR}/src/ui/HangarUi.h
    ${PROJECT_SOURCE_DIR}/src/ui/LevelUi.h
    ${PROJECT_SOURCE_DIR}/src/ui/MainMenuUi.h
    ${PROJECT_SOURCE_DIR}/src/ui/PlayerShipControls.h
    ${PROJECT_SOURCE_DIR}/src/ui/ProgressBar.h
    ${PROJECT_SOURCE_DIR}/src/ui/ElementProgressBar.h
    ${PROJECT_SOURCE_DIR}/src/ui/UiHelpers.h
    ${PROJECT_SOURCE_DIR}/src/utils/ContactSensorCallback.h
    ${PROJECT_SOURCE_DIR}/src/utils/Easing.h
    ${PROJECT_SOURCE_DIR}/src/utils/EventMgr.h
    ${PROJECT_SOURCE_DIR}/src/utils/LoadingController.h
    ${PROJECT_SOURCE_DIR}/src/utils/ShipsUtils.h
)

set(ships3d_SRC_LIST
    ${PROJECT_SOURCE_DIR}/src/Ships3dAppDelegate.cpp
    ${PROJECT_SOURCE_DIR}/src/effects/SpaceParticles.cpp
    ${PROJECT_SOURCE_DIR}/src/effects/SunGlowOverlay.cpp
    ${PROJECT_SOURCE_DIR}/src/effects/NPCVisuals.cpp
    ${PROJECT_SOURCE_DIR}/src/game/inventory/InventoryItem.cpp
    ${PROJECT_SOURCE_DIR}/src/game/missions/Mission.cpp
    ${PROJECT_SOURCE_DIR}/src/game/missions/BattleMission.cpp
    ${PROJECT_SOURCE_DIR}/src/game/missions/MissionTriggers.cpp
    ${PROJECT_SOURCE_DIR}/src/game/ArcballCamera.cpp
    ${PROJECT_SOURCE_DIR}/src/game/AsteroidObstacle.cpp
    ${PROJECT_SOURCE_DIR}/src/game/NPCShip.cpp
    ${PROJECT_SOURCE_DIR}/src/game/NPCShipAIControlBlock.cpp
    ${PROJECT_SOURCE_DIR}/src/game/NPCLifecycle.cpp
    ${PROJECT_SOURCE_DIR}/src/game/Events.cpp
    ${PROJECT_SOURCE_DIR}/src/game/FPSCamera.cpp
    ${PROJECT_SOURCE_DIR}/src/game/GameConfigs.cpp
    ${PROJECT_SOURCE_DIR}/src/game/GameController.cpp
    ${PROJECT_SOURCE_DIR}/src/game/GameEntityLifecycle.cpp
    ${PROJECT_SOURCE_DIR}/src/game/GameplayRequirements.cpp
    ${PROJECT_SOURCE_DIR}/src/game/GameState.cpp
    ${PROJECT_SOURCE_DIR}/src/game/Gun.cpp
    ${PROJECT_SOURCE_DIR}/src/game/PlayerLifecycle.cpp
    ${PROJECT_SOURCE_DIR}/src/game/PlayerShip.cpp
    ${PROJECT_SOURCE_DIR}/src/game/PlayerShipCamera.cpp
    ${PROJECT_SOURCE_DIR}/src/game/ShipMovement.cpp
    ${PROJECT_SOURCE_DIR}/src/scenes/DebugTestScene.cpp
    ${PROJECT_SOURCE_DIR}/src/scenes/DebugViewer.cpp
    ${PROJECT_SOURCE_DIR}/src/scenes/GalaxyMap.cpp
    ${PROJECT_SOURCE_DIR}/src/scenes/GameScene.cpp
    ${PROJECT_SOURCE_DIR}/src/scenes/Hangar.cpp
    ${PROJECT_SOURCE_DIR}/src/scenes/Level.cpp
    ${PROJECT_SOURCE_DIR}/src/scenes/LevelVisuals.cpp
    ${PROJECT_SOURCE_DIR}/src/scenes/MainMenu.cpp
    ${PROJECT_SOURCE_DIR}/src/script/ScriptBindings.cpp
    ${PROJECT_SOURCE_DIR}/src/script/ScriptManager.cpp
    ${PROJECT_SOURCE_DIR}/src/ui/DefaultPopup.cpp
    ${PROJECT_SOURCE_DIR}/src/ui/GalaxyMapUi.cpp
    ${PROJECT_SOURCE_DIR}/src/ui/GuiEventsProxy.cpp
    ${PROJECT_SOURCE_DIR}/src/ui/HangarUi.cpp
    ${PROJECT_SOURCE_DIR}/src/ui/LevelUi.cpp
    ${PROJECT_SOURCE_DIR}/src/ui/MainMenuUi.cpp
    ${PROJECT_SOURCE_DIR}/src/ui/PlayerShipControls.cpp
    ${PROJECT_SOURCE_DIR}/src/ui/ProgressBar.cpp
    ${PROJECT_SOURCE_DIR}/src/ui/ElementProgressBar.cpp
    ${PROJECT_SOURCE_DIR}/src/ui/UiHelpers.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/ContactSensorCallback.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/EventMgr.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/LoadingController.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/ShipsUtils.cpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/libdf3d/libdf3d
    ${PROJECT_SOURCE_DIR}/libdf3d/third-party
    ${PROJECT_SOURCE_DIR}/libdf3d/third-party/bullet/src
    ${PROJECT_SOURCE_DIR}/libdf3d/third-party/spark/include
    ${PROJECT_SOURCE_DIR}/libdf3d/third-party/libRocket/Include
    ${PROJECT_SOURCE_DIR}/third-party/include
    ${PROJECT_SOURCE_DIR}/third-party/include/squirrel
    ${PROJECT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS}
)

add_definitions(-DBULLET_FORCE_NO_ALIGNMENT)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd\"4138\" /wd\"4251\" /wd\"4457\" /wd\"4458\"")

    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif()

if (WINDOWS)
    add_definitions(-D_CONSOLE)
endif()

if (DF3D_BUILD_SHARED_LIB)
    message(STATUS "df3d is shared")
    add_definitions(-DJSON_DLL -DDF3D_SHARED_LIBRARY)
endif()

add_library(ships3d STATIC ${ships3d_SRC_LIST} ${ships3d_HEADER_LIST})
target_link_libraries(ships3d libdf3d squirrel)

set_target_properties(ships3d PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "$(PROJECT_SOURCE_DIR)/src/stdafx.h")
cotire(ships3d)
