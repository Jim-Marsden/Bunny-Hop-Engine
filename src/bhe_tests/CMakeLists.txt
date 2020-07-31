project(Bunny_Hop_Tests)

cmake_minimum_required(VERSION 3.16)

set(EXECUTABLE_OUTPUT_PATH "../..")

set(Bunny_Hop_Tests_Files test_main.cpp test_delegate.cpp test_drawable.cpp test_pipeline.cpp test_animationState.cpp test_ReturnStatus.cpp)

add_executable(Bunny_Hop_Tests ${Bunny_Hop_Core_Files} ${Bunny_Hop_Tests_Files})


target_link_libraries(Bunny_Hop_Tests ${Bunny_Hop_Lib})