cmake_minimum_required(VERSION 3.1)

project(testapp)

include(${PROJECT_SOURCE_DIR}/code/libdf3d/cmake/libdf3d.cmake)

# Place all the binaries in appropriate directories.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
endforeach()

# Include df3d.
add_subdirectory(${PROJECT_SOURCE_DIR}/code/libdf3d)
# Include gtest
add_subdirectory(${PROJECT_SOURCE_DIR}/code/third-party/googletest)

set(testapp_HEADER_LIST
    ${PROJECT_SOURCE_DIR}/code/src/TestAppDelegate.h
    ${PROJECT_SOURCE_DIR}/code/src/EcsCoreTest.h
    ${PROJECT_SOURCE_DIR}/code/src/UtilsTest.h
    ${PROJECT_SOURCE_DIR}/code/src/Common.h
    ${PROJECT_SOURCE_DIR}/code/src/ArrayTest.h
)

set(testapp_SRC_LIST
    ${PROJECT_SOURCE_DIR}/code/src/TestAppDelegate.cpp
    ${PROJECT_SOURCE_DIR}/code/libdf3d/df3d/platform/desktop_common/glfwMain.cpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/code/libdf3d/
    ${PROJECT_SOURCE_DIR}/code/libdf3d/third-party
    ${PROJECT_SOURCE_DIR}/code/libdf3d/third-party/bullet/src
    ${PROJECT_SOURCE_DIR}/code/libdf3d/third-party/spark/include
    ${PROJECT_SOURCE_DIR}/code/libdf3d/third-party/sqrat
    ${PROJECT_SOURCE_DIR}/code/libdf3d/third-party/squirrel/include
    ${PROJECT_SOURCE_DIR}/code/libdf3d/third-party/turbobadger/src/tb
    ${PROJECT_SOURCE_DIR}/code/
    ${PROJECT_SOURCE_DIR}/third-party/googletest/googletest/include
)

add_executable(testapp ${testapp_HEADER_LIST} ${testapp_SRC_LIST})

target_link_libraries(testapp libdf3d gtest)

if (WINDOWS)
    set(PROJECT_BINARY_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    function(copy_dll dll_name)
        add_custom_command(TARGET testapp
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${dll_name} ${PROJECT_BINARY_DIR}/.
        )
    endfunction()

    copy_dll(${PROJECT_SOURCE_DIR}/code/libdf3d/third-party/prebuilt_win32/bin/glew32.dll)
endif()

