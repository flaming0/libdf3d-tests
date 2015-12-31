cmake_minimum_required(VERSION 3.1)

project(testapp)

include(${PROJECT_SOURCE_DIR}/libdf3d/cmake/libdf3d.cmake)

# Include all the game dependencies.
add_subdirectory(${PROJECT_SOURCE_DIR}/libdf3d)
add_subdirectory(${PROJECT_SOURCE_DIR}/third-party/googletest)

set(testapp_HEADER_LIST
    ${PROJECT_SOURCE_DIR}/src/TestAppDelegate.h
)

set(testapp_SRC_LIST
    ${PROJECT_SOURCE_DIR}/src/TestAppDelegate.cpp
    ${PROJECT_SOURCE_DIR}/src/EcsCoreTest.h
    ${PROJECT_SOURCE_DIR}/src/UtilsTest.h
)

include_directories(
    ${PROJECT_SOURCE_DIR}/libdf3d/libdf3d
    ${PROJECT_SOURCE_DIR}/libdf3d/third-party
    ${PROJECT_SOURCE_DIR}/libdf3d/third-party/bullet/src
    ${PROJECT_SOURCE_DIR}/libdf3d/third-party/spark/include
    ${PROJECT_SOURCE_DIR}/libdf3d/third-party/libRocket/Include
    ${PROJECT_SOURCE_DIR}/libdf3d/third-party/squirrel/include
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/third-party/googletest/googletest/include
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

add_library(testapp STATIC ${testapp_SRC_LIST} ${testapp_HEADER_LIST})
target_link_libraries(testapp libdf3d gtest)
