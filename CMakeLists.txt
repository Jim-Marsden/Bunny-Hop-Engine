cmake_minimum_required(VERSION 3.24)
project(Bunny_Hop_Engine)
set(CMAKE_CXX_STANDARD 20)
enable_language(CXX)


add_subdirectory(thrid_party)

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
        ${PROJECT_SOURCE_DIR}/src/bhe_core/animationState.cpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/animationState.hpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/Delegate.hpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/drawable.cpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/drawable.hpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/entity.cpp
        ${PROJECT_SOURCE_DIR}/ src/bhe_core/entity.hpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/Functional_Events.h
        ${PROJECT_SOURCE_DIR}/src/bhe_core/GameScene.cpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/Json_Parser.cpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/Json_Parser.hpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/movement.cpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/movement.hpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/parallax.cpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/parallax.hpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/Pipeline.hpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/player.cpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/player.hpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/Print_helper.hpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/Return_Status.hpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/State_Machine.cpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/State_Machine.hpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/SystemEvent.cpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/SystemEvent.hpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/textureManager.cpp
        ${PROJECT_SOURCE_DIR}/src/bhe_core/textureManager.hpp)

add_executable(bhe_engine src/bhe_engine/engine_main.cpp ${bhe_core_src})
target_include_directories(bhe_engine PRIVATE ${PROJECT_SOURCE_DIR}/src/)
target_link_libraries(bhe_engine SFML::Graphics nlohmann_json::nlohmann_json fmt::fmt)

add_executable(bhe_designer src/bhe_designer/designer_main.cpp ${bhe_core_src})
target_include_directories(bhe_engine PRIVATE ${PROJECT_SOURCE_DIR}/src/)
target_link_libraries(bhe_engine SFML::Graphics nlohmann_json::nlohmann_json)

add_executable(bhe_tests ${bhe_tests_src} ${bhe_core_src})
target_include_directories(bhe_tests PRIVATE ${PROJECT_SOURCE_DIR}/src/bhe_core ${PROJECT_SOURCE_DIR}/src/)
target_link_libraries(bhe_tests SFML::Graphics nlohmann_json::nlohmann_json Catch2::Catch2WithMain)

set_target_properties(bhe_engine bhe_designer bhe_tests
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        )
#
#set(bhe_engine_src src/bhe_engine/engine_main.cpp)
#
#set(bhe_designer_src
#        src/bhe_designer/designer_main.cpp
#        src/bhe_designer/DesignerWindow.cpp src/bhe_designer/DesignerWindow.h src/bhe_designer/gui_helpers.cpp src/bhe_designer/gui_helpers.hpp src/bhe_designer/gui_modes.cpp src/bhe_designer/gui_modes.hpp src/bhe_designer/scene_designer.cpp src/bhe_designer/scene_designer.hpp src/bhe_designer/designer_menu.cpp src/bhe_designer/designer_menu.hpp src/bhe_designer/designer_pallet.cpp src/bhe_designer/designer_pallet.hpp)
#
#
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#
#include_directories(src)
#add_executable(bhe_test_runner ${bhe_core_src} ${bhe_tests_src})
#target_link_libraries(bhe_test_runner PRIVATE ${bhe_libs})
#
#add_executable(bhe_designer ${bhe_core_src} ${bhe_designer_src})
#target_link_libraries(bhe_designer PRIVATE ${bhe_libs})
#
#add_executable(bhe_engine ${bhe_engine_src} ${bhe_core_src})
#target_link_libraries(bhe_engine ${bhe_libs})

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

