cmake_minimum_required(VERSION 3.16)
project(Moonlight_Trails)



#configure_file(test.json test.json COPYONLY)
#find_path(BOOST_INCLUDE_DIR boost)
#include_directories(${BOOST_INCLUDE_DIR})


find_package(TGUI CONFIG REQUIRED)
find_package(SFML CONFIG REQUIRED graphics system window  network audio)
find_package(jsoncpp CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)



set(CMAKE_CXX_STANDARD 17)
set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.72.0 COMPONENTS date_time filesystem system timer)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(Moonlight_Trails main.cpp)
    target_link_libraries(Moonlight_Trails PRIVATE sfml-graphics sfml-system sfml-window sfml-window sfml-audio FLAC OpenAL
            OpenGL Vorbis tgui jsoncpp_lib Catch2::Catch2 ${Boost_LIBRARIES})
endif()



#[[
#configure_file(test.json test.json COPYONLY)
set(Boost_USE_STATIC_LIBS ON)
find_package(BOOST 1.68.0 REQUIRED COMPONENTS )
#find_path(BOOST_INCLUDE_DIR boost)
#include_directories(${BOOST_INCLUDE_DIR})


find_package(TGUI CONFIG REQUIRED)
find_package(SFML CONFIG REQUIRED graphics system window  network audio)
find_package(jsoncpp CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

add_executable(Moonlight_Trails main.cpp)
target_link_libraries(Moonlight_Trails PRIVATE sfml-graphics sfml-system sfml-window sfml-window sfml-audio FLAC OpenAL
        OpenGL Vorbis tgui jsoncpp_lib Catch2::Catch2 )]]



