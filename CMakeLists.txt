cmake_minimum_required(VERSION 3.1)

project(testapp_exec)

include(${PROJECT_SOURCE_DIR}/code/libdf3d/cmake/libdf3d.cmake)

# Place all the binaries in appropriate directories.
if (DF3D_DESKTOP)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

    foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
    endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/code)

include_directories(
    ${PROJECT_SOURCE_DIR}/code/libdf3d/
)

if (DF3D_DESKTOP)
    add_executable(testapp_exec ${PROJECT_SOURCE_DIR}/code/libdf3d/libdf3d/platform/desktop_common/glfwMain.cpp)
else()

endif()

target_link_libraries(testapp_exec libdf3d testapp)
