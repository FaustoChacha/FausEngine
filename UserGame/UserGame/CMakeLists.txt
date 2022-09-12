# CMakeList.txt : CMake project for UserGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
include_directories(FausEngine )

# Add source to this project's executable.
add_executable (UserGame "main.cpp" "UserGame.h" "UserGame.cpp" "Escenario.h" "Escenario.cpp")

target_link_libraries(UserGame ${CMAKE_CURRENT_LIST_DIR}/FausEngine/Libs/FausEngine.lib)

##################### MALLAS

file(GLOB MODELS Assets/Models/*.obj)
make_directory(${CMAKE_BINARY_DIR}/UserGame/Models)
add_custom_command(
    TARGET UserGame PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${MODELS}
        ${CMAKE_BINARY_DIR}/UserGame/Models
   )

   ##################TEXTURAS
file(GLOB pngTEX Assets/Textures/*.png)
make_directory(${CMAKE_BINARY_DIR}/UserGame/Textures)
add_custom_command(
    TARGET UserGame PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${pngTEX}
        ${CMAKE_BINARY_DIR}/UserGame/Textures
   )

file(GLOB jpgTEX Assets/Textures/*.jpg)
make_directory(${CMAKE_BINARY_DIR}/UserGame/Textures)
add_custom_command(
    TARGET UserGame PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${jpgTEX}
        ${CMAKE_BINARY_DIR}/UserGame/Textures
   )

   ########################FUENTES
file(GLOB fonts Assets/Fonts/*.ttf)

make_directory(${CMAKE_BINARY_DIR}/UserGame/Fonts)
add_custom_command(
    TARGET UserGame PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${fonts}
        ${CMAKE_BINARY_DIR}/UserGame/Fonts
   )

file(GLOB fontsOTF Assets/Fonts/*.otf)

make_directory(${CMAKE_BINARY_DIR}/UserGame/Fonts)
add_custom_command(
    TARGET UserGame PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${fontsOTF}
        ${CMAKE_BINARY_DIR}/UserGame/Fonts
   )

   ################## DLL
   
file(GLOB fsdll FausEngine/Libs/FausEngine.dll)

make_directory(${CMAKE_BINARY_DIR}/UserGame)
add_custom_command(
    TARGET UserGame PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${fsdll}
        ${CMAKE_BINARY_DIR}/UserGame
   )