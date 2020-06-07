project(Bunny_Hop_Tests)

cmake_minimum_required(VERSION 3.16)

add_executable(Bunny_Hop_Tests ${Bunny_Hop_Core_Files} test_main.cpp test_delegate.cpp test_drawable.cpp test_pipeline.cpp)


target_link_libraries(Bunny_Hop_Tests ${Bunny_Hop_Lib})