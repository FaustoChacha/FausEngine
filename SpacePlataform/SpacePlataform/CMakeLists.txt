# CMakeList.txt : CMake project for UserGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
include_directories(FausEngine )

file(GLOB SRCGame *.cpp "SpacePlataform.cpp" "SpacePlataform.h" )

# Add source to this project's executable.
add_executable (SpacePlataform ${SRCGame})

target_link_libraries(SpacePlataform ${CMAKE_CURRENT_LIST_DIR}/FausEngine/libs/FausEngine.lib)

##################### MALLAS

file(GLOB MODELS Assets/Models/*.obj)
make_directory(${CMAKE_BINARY_DIR}/SpacePlataform/Models)
add_custom_command(
    TARGET SpacePlataform PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${MODELS}
        ${CMAKE_BINARY_DIR}/SpacePlataform/Models
   )

   ##################TEXTURAS
file(GLOB pngTEX Assets/Textures/*.png)
make_directory(${CMAKE_BINARY_DIR}/SpacePlataform/Textures)
add_custom_command(
    TARGET SpacePlataform PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${pngTEX}
        ${CMAKE_BINARY_DIR}/SpacePlataform/Textures
   )

file(GLOB jpgTEX Assets/Textures/*.tga)
make_directory(${CMAKE_BINARY_DIR}/SpacePlataform/Textures)
add_custom_command(
    TARGET SpacePlataform PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${jpgTEX}
        ${CMAKE_BINARY_DIR}/SpacePlataform/Textures
   )

   file(GLOB jpgTEX Assets/Textures/*.jpg)
make_directory(${CMAKE_BINARY_DIR}/SpacePlataform/Textures)
add_custom_command(
    TARGET SpacePlataform PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${jpgTEX}
        ${CMAKE_BINARY_DIR}/SpacePlataform/Textures
   )

   ########################FUENTES
file(GLOB fonts Assets/Fonts/*.ttf)

make_directory(${CMAKE_BINARY_DIR}/SpacePlataform/Fonts)
add_custom_command(
    TARGET SpacePlataform PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${fonts}
        ${CMAKE_BINARY_DIR}/SpacePlataform/Fonts
   )

file(GLOB fontsOTF Assets/Fonts/*.otf)

make_directory(${CMAKE_BINARY_DIR}/SpacePlataform/Fonts)
add_custom_command(
    TARGET SpacePlataform PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${fontsOTF}
        ${CMAKE_BINARY_DIR}/SpacePlataform/Fonts
   )

   ################## DLL
   
file(GLOB fsdll FausEngine/Libs/FausEngine.dll)

make_directory(${CMAKE_BINARY_DIR}/SpacePlataform)
add_custom_command(
    TARGET SpacePlataform PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${fsdll}
        ${CMAKE_BINARY_DIR}/SpacePlataform
   )