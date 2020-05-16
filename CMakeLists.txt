cmake_minimum_required(VERSION 3.16)
project(Moonlight_Trails)
set(CMAKE_CXX_STANDARD 17)
enable_language(CXX)



configure_file(Scenes/TestScene.json Scenes/TestScene.json COPYONLY)
configure_file(Scenes/Textures/tree.png Scenes/Textures/tree.png COPYONLY)
configure_file(Scenes/Textures/parallax_test-bg001.png
        Scenes/Textures/parallax_test-bg001.png COPYONLY)

configure_file(Scenes/Textures/default.png Scenes/Textures/default.png COPYONLY)


add_executable(Moonlight_Trails main.cpp GameScene.cpp GameScene.h TextureManager.cpp TextureManager.h Parallax.cpp Parallax.h Print_helper.hpp Drawable.cpp Drawable.h Entity.cpp Entity.h)

if(WIN32)

    find_package(TGUI CONFIG REQUIRED)
    find_package(SFML CONFIG REQUIRED graphics system window  network audio)
    find_package(jsoncpp CONFIG REQUIRED)
    find_package(Catch2 CONFIG REQUIRED)



    set(Boost_USE_STATIC_LIBS        ON) # only find static libs
    set(Boost_USE_MULTITHREADED      ON)
    set(Boost_USE_STATIC_RUNTIME    OFF)
    find_package(Boost 1.72.0 COMPONENTS date_time filesystem system timer)
    if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        target_link_libraries(Moonlight_Trails PRIVATE sfml-graphics sfml-system sfml-window sfml-window sfml-audio FLAC OpenAL
                OpenGL Vorbis tgui jsoncpp_lib Catch2::Catch2 ${Boost_LIBRARIES})

    endif()
elseif(LINUX)
    set(Boost_USE_STATIC_LIBS        ON) # only find static libs
    set(Boost_USE_MULTITHREADED      ON)
    set(Boost_USE_STATIC_RUNTIME    OFF)
    find_package(Boost 1.72.0 COMPONENTS date_time filesystem system timer)
    if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        target_link_libraries(Moonlight_Trails PRIVATE sfml-graphics sfml-system sfml-window sfml-window sfml-audio FLAC OpenAL
                OpenGL Vorbis tgui jsoncpp_lib Catch2::Catch2 ${Boost_LIBRARIES})

    endif()

endif()



