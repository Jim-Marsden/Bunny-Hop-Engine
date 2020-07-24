project(Bunny_Hop_Designer)

cmake_minimum_required(VERSION 3.16)
set(EXECUTABLE_OUTPUT_PATH "../..")


add_executable(Bunny_Hop_Designer ${Bunny_Hop_Core_Files} designer_main.cpp pallet_pannel.cpp pallet_pannel.hpp windowManager.cpp windowManager.hpp baseWindowElement.cpp baseWindowElement.hpp basePannel.cpp basePannel.hpp)

#set(Bunny_Hop_Lib sfml-graphics sfml-system sfml-window sfml-window sfml-audio FLAC OpenAL
#      OpenGL Vorbis tgui Catch2::Catch2 jsoncpp pthread)

target_link_libraries(Bunny_Hop_Designer ${Bunny_Hop_Lib})



