cmake_minimum_required(VERSION 3.16)
project(Bunny_Hop_Engine)
set(CMAKE_CXX_STANDARD 20)
enable_language(CXX)


#[[

* The following block is for building on windows, using vcpkg.
* The else block will be for using fetch content.
]]

if (WIN32)
    find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
    find_package(Catch2 CONFIG REQUIRED)
    find_package(TGUI CONFIG REQUIRED)
    find_package(jsoncpp CONFIG REQUIRED)


    set(bhe_libs
            Catch2::Catch2
            sfml-audio
            sfml-graphics
            sfml-system
            sfml-window
            tgui
            jsoncpp_lib
            jsoncpp_object
            )

else()

    Include(FetchContent)

    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v2.13.1)

    FetchContent_MakeAvailable(Catch2)

    FetchContent_Declare(
            Vorbis
            GIT_REPOSITORY https://github.com/xiph/vorbis.git
            GIT_TAG master
    )
    FetchContent_MakeAvailable(Vorbis)
    set(SFML_VERSION "2.5.1")

    FetchContent_Declare(
            sfml
            GIT_REPOSITORY "https://github.com/SFML/SFML.git"
            GIT_TAG "${SFML_VERSION}"
    )

    FetchContent_GetProperties(sfml)
    if (NOT sfml_POPULATED)
        message("alskdfjasldfjasldfj;alsdjf;djf;lkasjdf;asdjf;lkj")
        FetchContent_Populate(sfml)
        add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
    endif ()


    FetchContent_Declare(
            TGUI
            GIT_REPOSITORY https://github.com/texus/TGUI.git
            GIT_TAG 0.9)

    FetchContent_MakeAvailable(TGUI)


    FetchContent_Declare(
            jsoncpp
            GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
            GIT_TAG master)

    FetchContent_MakeAvailable(jsoncpp)


    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)

endif ()

include(CTest)
include(Catch)
#add_subdirectory("csv-parser")


set(bhe_tests_src
        src/bhe_tests/test_animationState.cpp
        src/bhe_tests/test_delegate.cpp
        src/bhe_tests/test_drawable.cpp
        src/bhe_tests/test_entity.cpp
        src/bhe_tests/test_main.cpp
        src/bhe_tests/test_pipeline.cpp
        src/bhe_tests/test_ReturnStatus.cpp
        src/bhe_tests/test_State_Machine.cpp)

set(bhe_core_src
        src/bhe_core/animationState.cpp
        src/bhe_core/animationState.hpp
        src/bhe_core/delegate.hpp
        src/bhe_core/drawable.cpp
        src/bhe_core/drawable.hpp
        src/bhe_core/entity.cpp
        src/bhe_core/entity.hpp
        src/bhe_core/Functional_Events.h
        src/bhe_core/gameScene.cpp
        src/bhe_core/Json_Parser.cpp
        src/bhe_core/Json_Parser.hpp
        src/bhe_core/movement.cpp
        src/bhe_core/movement.hpp
        src/bhe_core/parallax.cpp
        src/bhe_core/parallax.hpp
        src/bhe_core/pipeline.hpp
        src/bhe_core/player.cpp
        src/bhe_core/player.hpp
        src/bhe_core/Print_helper.hpp
        src/bhe_core/Return_Status.hpp
        src/bhe_core/State_Machine.cpp
        src/bhe_core/State_Machine.hpp
        src/bhe_core/systemEvent.cpp
        src/bhe_core/systemEvent.hpp
        src/bhe_core/textureManager.cpp
        src/bhe_core/textureManager.hpp)

set(bhe_engine_src src/bhe_engine/engine_main.cpp)

set(bhe_designer_src src/bhe_designer/basePannel.cpp
        src/bhe_designer/basePannel.hpp
        src/bhe_designer/baseWindowElement.hpp
        src/bhe_designer/baseWindowElement.cpp
        src/bhe_designer/designer_main.cpp
        src/bhe_designer/pallet_pannel.cpp
        src/bhe_designer/pallet_pannel.hpp
        src/bhe_designer/windowManager.cpp
        src/bhe_designer/windowManager.hpp src/bhe_designer/designer_window.cpp src/bhe_designer/designer_window.h)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(src)
add_executable(bhe_test_runner ${bhe_core_src} ${bhe_tests_src})
target_link_libraries(bhe_test_runner PRIVATE ${bhe_libs})

add_executable(bhe_designer ${bhe_core_src} ${bhe_designer_src})
target_link_libraries(bhe_designer PRIVATE ${bhe_libs})

add_executable(bhe_engine ${bhe_engine_src} ${bhe_core_src})
target_link_libraries(bhe_engine ${bhe_libs})

catch_discover_tests(bhe_test_runner)


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


configure_file(.Test/images/test.png .Test/images/test.png COPYONLY)


#[[
add_subdirectory(SFML)
add_subdirectory(TGUI)
add_subdirectory(vorbis)
add_subdirectory(jsoncpp)

#add_subdirectory(boost)
add_subdirectory(Catch2)


#find_package(SFML CONFIG REQUIRED graphics system window network audio REQUIRED)
#find_package(TGUI CONFIG REQUIRED)

#find_package(Catch2 CONFIG REQUIRED)

set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.72.0 COMPONENTS date_time filesystem system timer REQUIRED)


include_directories(src)
include_directories(src/BHE)
include_directories(src/tests)

set(Bunny_Hop_Core_Files ../bhe_core/gameScene.cpp ../bhe_core/gameScene.hpp
        ../bhe_core/textureManager.cpp ../bhe_core/textureManager.hpp ../bhe_core/parallax.cpp ../bhe_core/parallax.hpp
        ../bhe_core/Print_helper.hpp ../bhe_core/drawable.cpp ../bhe_core/drawable.hpp ../bhe_core/entity.cpp ../bhe_core/entity.hpp
        ../bhe_core/player.cpp ../bhe_core/player.hpp ../bhe_core/delegate.hpp ../bhe_core/systemEvent.cpp ../bhe_core/systemEvent.hpp
        ../bhe_core/State_Machine.cpp ../bhe_core/State_Machine.hpp ../bhe_core/animationState.cpp ../bhe_core/animationState.hpp
        ../bhe_core/movement.cpp ../bhe_core/movement.hpp ../bhe_core/Json_Parser.cpp ../bhe_core/Json_Parser.hpp ../bhe_core/pipeline.hpp
        ../bhe_core/Return_Status.hpp ../bhe_core/Functional_Events.h)

set(Bunny_Hop_Lib sfml-graphics sfml-system sfml-window sfml-window sfml-audio FLAC OpenAL
        OpenGL vorbis tgui Catch2::Catch2 Boost::timer)


if (WIN32)

    #find_package(jsoncpp CONFIG REQUIRED)
    set(Bunny_Hop_Engine_Compiler_Flags ${Bunny_Hop_Engine_Compiler_Flags} /EHs)
    set(Bunny_Hop_Lib ${Bunny_Hop_Lib} jsoncpp_lib)
elseif (UNIX)
    set(Bunny_Hop_Lib ${Bunny_Hop_Lib} jsoncpp pthread)

endif ()


add_compile_options(${Bunny_Hop_Engine_Compiler_Flags})


if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    #target_link_libraries(Bunny_Hop_Core PRIVATE ${Bunny_Hop_Lib} ${Boost_LIBRARIES})

endif ()

add_subdirectory(src/bhe_engine)
add_subdirectory(src/bhe_designer)
add_subdirectory(src/bhe_tests)


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


configure_file(.Test/images/test.png .Test/images/test.png COPYONLY)
]]