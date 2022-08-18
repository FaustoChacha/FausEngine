file(GLOB CODIGO Source/*.cpp )



add_library(FausEngine SHARED ${CODIGO})
set_target_properties(FausEngine PROPERTIES 
	COMPILE_DEFINITIONS EXPORTDLL
	)	

target_link_libraries(FausEngine ${CONAN_LIBS})
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")



######################################################
#[[
make_directory(${CMAKE_BINARY_DIR}/bin/Shaders)

file(GLOB FSSHADERS Shaders/*.glsl)
add_custom_command(
    TARGET FausEngine PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${FSSHADERS}
        ${CMAKE_BINARY_DIR}/bin/shaders
   )
   
file(GLOB IMG Shaders/*.png)
add_custom_command(
    TARGET FausEngine PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${IMG}
        ${CMAKE_BINARY_DIR}/bin/shaders
   )
   ]]
#### modelos y texturas

file(GLOB MODELS ../ejemplo/Models/*.obj)
make_directory(${CMAKE_BINARY_DIR}/bin/Models)
add_custom_command(
    TARGET FausEngine PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${MODELS}
        ${CMAKE_BINARY_DIR}/bin/Models
   )

file(GLOB pngTEX ../ejemplo/Textures/*.png)

make_directory(${CMAKE_BINARY_DIR}/bin/Textures)
add_custom_command(
    TARGET FausEngine PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${pngTEX}
        ${CMAKE_BINARY_DIR}/bin/Textures
   )

file(GLOB jpgTEX ../ejemplo/Textures/*.jpg)

make_directory(${CMAKE_BINARY_DIR}/bin/Textures)
add_custom_command(
    TARGET FausEngine PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${jpgTEX}
        ${CMAKE_BINARY_DIR}/bin/Textures
   )

   #[[
install(FILES 
IMG DESTINATION ${CMAKE_BINARY_DIR}/bin/ejemplo
)
]]


###########################################
set(PATH_INSTALL ${PROJECT_SOURCE_DIR}/out/install)
install(TARGETS 
	FausEngine DESTINATION  ${PATH_INSTALL}/bin 
	LIBRARY DESTINATION ${PATH_INSTALL}/bin 
	PUBLIC_HEADER DESTINATION ${PATH_INSTALL}/include) 