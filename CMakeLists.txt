cmake_minimum_required(VERSION 3.16)
project(Bunny_Hop_Engine)
set(CMAKE_CXX_STANDARD 20)
enable_language(CXX)

option(-DoUnitTests "unit tests" ON)
option(-DoWarnings "warnings" OFF)
option(-DoClangTidy "clang tidy?" OFF)

set(Bunny_Hop_Engine_Compiler_Flags)

find_package(SFML CONFIG REQUIRED graphics system window network audio REQUIRED)
find_package(TGUI CONFIG REQUIRED)

find_package(Catch2 CONFIG REQUIRED)

set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.72.0 COMPONENTS date_time filesystem system timer REQUIRED)

include_directories(src)
include_directories(src/BHE)
include_directories(src/tests)


set(Moon_LightTrails_Main_Source_File src/BHE/main.cpp src/BHE/gameScene.cpp src/BHE/gameScene.hpp
        src/BHE/textureManager.cpp src/BHE/textureManager.hpp src/BHE/parallax.cpp src/BHE/parallax.hpp
        src/BHE/Print_helper.hpp src/BHE/drawable.cpp src/BHE/drawable.hpp src/BHE/entity.cpp src/BHE/entity.hpp
        src/BHE/player.cpp src/BHE/player.hpp src/BHE/delegate.hpp src/BHE/SystemEvent.cpp src/BHE/SystemEvent.hpp
        src/BHE/State_Machine.cpp src/BHE/State_Machine.h src/BHE/animationState.cpp src/BHE/animationState.hpp
        src/BHE/movement.cpp src/BHE/movement.hpp src/BHE/Json_Parser.cpp src/BHE/Json_Parser.hpp)

set(Moon_LightTrails_Test_Source_Files src/tests/test_delegate.cpp)

set(Moon_LightTrails_Main_Libs sfml-graphics sfml-system sfml-window sfml-window sfml-audio FLAC OpenAL
        OpenGL Vorbis tgui Catch2::Catch2)

if (-DoWarnings)
    message("Doing warnings")
    if (WIN32)
        # warning level 4 and all warnings as errors
        set(Bunny_Hop_Engine_Compiler_Flags ${Bunny_Hop_Engine_Compiler_Flags} /W3)
        #add_compile_options(/W3)
    else ()
        # lots of warnings and all warnings as errors
        #add_compile_options
        set(Bunny_Hop_Engine_Compiler_Flags ${Bunny_Hop_Engine_Compiler_Flags} -Wall -Wextra -pedantic -Wshadow -pedantic-errors -Wmisleading-indentation -Wswitch-default
                -Wswitch-enum -Wuninitialized -Wconversion
                -Warray-bounds -Wfloat-equal)

    endif ()
else()
    message("Not doing warnings")
endif ()

if(-DoClangTidy)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
else()
    message("Not doing clang tidy!")
endif()



if (-DoUnitTests)
    message("Do doing unit tests")
    add_compile_definitions(MOON_LIGHTTRAILS_CMAKE_OPTION_DO_TESTS)
    set(Moon_LightTrails_Main_Source_File ${Moon_LightTrails_Main_Source_File} ${Moon_LightTrails_Test_Source_Files} src/tests/test_drawable.cpp)
else()
    message("Not doing unit tests")
endif ()




if (WIN32)

    find_package(jsoncpp CONFIG REQUIRED)
    set(Bunny_Hop_Engine_Compiler_Flags ${Bunny_Hop_Engine_Compiler_Flags} /EHs)
    set(Moon_LightTrails_Main_Libs ${Moon_LightTrails_Main_Libs} jsoncpp_lib)
elseif (UNIX)
    set(Moon_LightTrails_Main_Libs ${Moon_LightTrails_Main_Libs} jsoncpp)
endif ()


add_compile_options(${Bunny_Hop_Engine_Compiler_Flags})
add_executable(Bunny_Hop_Engine ${Moon_LightTrails_Main_Source_File})


if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(Bunny_Hop_Engine PRIVATE ${Moon_LightTrails_Main_Libs} ${Boost_LIBRARIES})

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
