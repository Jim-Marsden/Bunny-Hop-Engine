
set(SFML_BRANCH event_api)
set(SFML_REPO https://github.com/SFML/SFML.git)


include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY ${SFML_REPO}
        GIT_TAG        ${SFML_BRANCH}
)

FetchContent_MakeAvailable(SFML)

fetchContent_Declare(ImGui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG v1.87)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

FetchContent_Declare(
        jsoncpp
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG master)

FetchContent_MakeAvailable(jsoncpp)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG master)

FetchContent_MakeAvailable(fmt)

#[[FetchContent_Declare(
        jsoncpp
        GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
        GIT_TAG master)

FetchContent_MakeAvailable(jsoncpp)]]

set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
        GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml
        GIT_TAG master)
FetchContent_MakeAvailable(ImGui-SFML)


FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1)

FetchContent_MakeAvailable(Catch2)
#
#FetchContent_Declare(
#        imgui
#        GIT_REPOSITORY https://github.com/ocornut/imgui
#        GIT_TAG 35b1148efb839381b84de9290d9caf0b66ad7d03
#)
#
#FetchContent_MakeAvailable(imgui)

#FetchContent_Declare(
#        Catch2
#        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#        GIT_TAG v2.13.1)
#
#FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)



#set(SFML_REPO https://github.com/SFML/SFML.git)
#set(SFML_BRANCH master)
#
#Include(FetchContent)
#
#FetchContent_Declare(
#        Catch2
#        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#        GIT_TAG v2.13.1)
#
#FetchContent_MakeAvailable(Catch2)
#
##FetchContent_Declare(
##        Vorbis
##        GIT_REPOSITORY https://github.com/xiph/vorbis.git
##        GIT_TAG master
##)
##FetchContent_MakeAvailable(Vorbis)
#
#FetchContent_Declare(
#        sfml
#        GIT_REPOSITORY ${SFML_REPO}
#        GIT_TAG ${SFML_BRANCH}
#)
#
#FetchContent_MakeAvailable(sfml)
#
##FetchContent_Declare(
##        TGUI
##        GIT_REPOSITORY https://github.com/texus/TGUI.git
##        GIT_TAG 0.9)
##
##FetchContent_MakeAvailable(TGUI)
#
#
#FetchContent_Declare(
#        jsoncpp
#        GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
#        GIT_TAG master)
#
#FetchContent_MakeAvailable(jsoncpp)
#
