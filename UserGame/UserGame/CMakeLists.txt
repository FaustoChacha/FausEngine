# CMakeList.txt : CMake project for UserGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
include_directories(FausEngine )

# Add source to this project's executable.
add_executable (UserGame "main.cpp" "UserGame.h" "UserGame.cpp" "Escenario.h" "Escenario.cpp")

target_link_libraries(UserGame ${CMAKE_CURRENT_LIST_DIR}/FausEngine/Libs/FausEngine.lib)

#[[
make_directory(${CMAKE_BINARY_DIR}/UserGame/Shaders)
file(GLOB FSSHADERS ${CMAKE_CURRENT_LIST_DIR}/FausEngine/Shaders/*.glsl)
file(GLOB IMG ${CMAKE_CURRENT_LIST_DIR}/FausEngine/Shaders/*.png)


add_custom_command(
    TARGET UserGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${FSSHADERS}
        ${CMAKE_BINARY_DIR}/UserGame/shaders
   )

add_custom_command(
    TARGET UserGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${IMG}
        ${CMAKE_BINARY_DIR}/UserGame/shaders
   )

   ]]
# TODO: Add tests and install targets if needed.
