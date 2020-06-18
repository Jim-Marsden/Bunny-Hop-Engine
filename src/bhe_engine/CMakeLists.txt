cmake_minimum_required(VERSION 3.16)

project(Bunny_Hop_Engine)

set(EXECUTABLE_OUTPUT_PATH "../..")
add_executable(Bunny_Hop_Engine ${Bunny_Hop_Core_Files} engine_main.cpp)

#set(Bunny_Hop_Lib sfml-graphics sfml-system sfml-window sfml-window sfml-audio FLAC OpenAL
#      OpenGL Vorbis tgui Catch2::Catch2 jsoncpp pthread)

target_link_libraries(Bunny_Hop_Engine ${Bunny_Hop_Lib})



