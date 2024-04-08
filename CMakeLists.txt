cmake_minimum_required(VERSION 3.10.0)
project(DPerX VERSION 0.1.0 LANGUAGES C CXX)

find_package(Threads REQUIRED)

set(IMGUI_SOURCES
    src/libs/imgui/imgui.cpp
    src/libs/imgui/imgui_demo.cpp
    src/libs/imgui/imgui_draw.cpp
    src/libs/imgui/imgui_widgets.cpp
    src/libs/imgui/imgui_tables.cpp
    src/libs/imgui/imgui_impl_win32.cpp
    src/libs/imgui/imgui_impl_dx11.cpp
)

set(SOURCES
    main.cpp
    src/aimbot.cpp
    src/aimbot.h
    src/esp.cpp
    src/esp.h
    src/localplayer.cpp
    src/localplayer.h
    src/server.cpp
    src/server.h
    src/spoofer.cpp
    src/spoofer.h
    src/ui.cpp
    src/ui.h
    src/moves.cpp
    src/moves.h
    src/spinbot.cpp
    src/spinbot.h

    src/signature.hpp
    src/game_info.hpp
    src/offsets.hpp
    src/player.h 
    src/memory.h
    src/vector2.h
)


add_executable(DPerX ${SOURCES} ${IMGUI_SOURCES} project.rc)

target_include_directories(DPerX PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/libs/imgui)

target_link_libraries(DPerX PRIVATE Threads::Threads d3d11 d3dcompiler dwmapi)
target_compile_features(DPerX PRIVATE cxx_std_20)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
