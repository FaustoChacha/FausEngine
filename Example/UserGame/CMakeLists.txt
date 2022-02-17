# CMakeList.txt : CMake project for UserGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
include_directories(FausEngine )

# Add source to this project's executable.
add_executable (UserGame "main.cpp" "UserGame.h" "UserGame.cpp" "Escenario.h" "Escenario.cpp")

target_link_libraries(UserGame ${CMAKE_CURRENT_LIST_DIR}/FausEngine/Libs/FausEngine.lib)
# TODO: Add tests and install targets if needed.
