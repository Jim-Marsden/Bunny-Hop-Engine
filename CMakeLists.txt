cmake_minimum_required(VERSION 3.16)
project(Moonlight_Trails)
set(CMAKE_CXX_STANDARD 17)
enable_language(CXX)

option(DoUnitTests "Unit tests!" OFF)
option(DoWarnings "Warnings!" OFF)

if (DoWarnings)
    if (MSVC)
        # warning level 4 and all warnings as errors
        add_compile_options(/W3)
    else ()
        # lots of warnings and all warnings as errors
        add_compile_options(-Wall -Wextra -pedantic -Wshadow -pedantic-errors -Wmisleading-indentation -Wswitch-default
                -Wswitch-enum -Wuninitialized -Wconversion
                -Warray-bounds -Wfloat-equal)
    endif ()
    set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
endif ()

include_directories(src)
include_directories(src/MT)
include_directories(src/tests)

set(Moon_LightTrails_Main_Source_File src/MT/main.cpp src/MT/gameScene.cpp src/MT/gameScene.hpp
        src/MT/textureManager.cpp src/MT/textureManager.hpp src/MT/parallax.cpp src/MT/parallax.hpp
        src/MT/Print_helper.hpp src/MT/drawable.cpp src/MT/drawable.hpp src/MT/entity.cpp src/MT/entity.hpp
        src/MT/player.cpp src/MT/player.hpp src/MT/delegate.hpp src/MT/SystemEvent.cpp src/MT/SystemEvent.hpp
        src/MT/State_Machine.cpp src/MT/State_Machine.h src/MT/animationState.cpp src/MT/animationState.hpp
        src/MT/movement.cpp src/MT/movement.hpp src/MT/Json_Parser.cpp src/MT/Json_Parser.hpp)

set(Moon_LightTrails_Test_Source_Files src/tests/test_delegate.cpp)

set(Moon_LightTrails_Main_Libs sfml-graphics sfml-system sfml-window sfml-window sfml-audio FLAC OpenAL
        OpenGL Vorbis tgui Catch2::Catch2)

if (DoUnitTests)
    add_compile_definitions(MOON_LIGHTTRAILS_CMAKE_OPTION_DO_TESTS)
    set(Moon_LightTrails_Main_Source_File ${Moon_LightTrails_Main_Source_File} ${Moon_LightTrails_Test_Source_Files})
endif ()

find_package(TGUI CONFIG REQUIRED)
find_package(SFML CONFIG REQUIRED graphics system window network audio REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.72.0 COMPONENTS date_time filesystem system timer REQUIRED)


if (WIN32)
    set(Moon_LightTrails_Main_Libs ${Moon_LightTrails_Main_Libs} jsoncpp_lib)
elseif (UNIX)
    set(Moon_LightTrails_Main_Libs ${Moon_LightTrails_Main_Libs} jsoncpp)
endif ()

add_executable(Moonlight_Trails ${Moon_LightTrails_Main_Source_File})


if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(Moonlight_Trails PRIVATE ${Moon_LightTrails_Main_Libs} ${Boost_LIBRARIES})

endif ()


configure_file(Scenes/TestScene.json Scenes/TestScene.json COPYONLY)
configure_file(Scenes/Textures/tree.png Scenes/Textures/tree.png COPYONLY)
configure_file(Scenes/Textures/parallax_test-bg001.png
        Scenes/Textures/parallax_test-bg001.png COPYONLY)

configure_file(Entity/Texture/animation_tests.png Entity/Texture/animation_tests.png COPYONLY)

configure_file(Entity/Test.json Entity/Test.json COPYONLY)
configure_file(Entity/Texture/default.png Entity/Texture/default.png COPYONLY)

configure_file(Settings/Controls.json Settings/Controls.json COPYONLY)

configure_file(Player/Player.json Player/Player.json COPYONLY)
configure_file(Player/Textures/player_animation_test_002.png Player/Textures/player_animation_test_002.png COPYONLY)
