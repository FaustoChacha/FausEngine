file(GLOB CODIGO Source/*.cpp )

make_directory(${CMAKE_BINARY_DIR}/bin/Shaders)

add_library(FausEngine SHARED ${CODIGO})
set_target_properties(FausEngine PROPERTIES 
	COMPILE_DEFINITIONS EXPORTDLL
	)	

target_link_libraries(FausEngine ${CONAN_LIBS})

file(GLOB FSSHADERS Shaders/*.glsl)
add_custom_command(
    TARGET FausEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${FSSHADERS}
        ${CMAKE_BINARY_DIR}/bin/Shaders
   )

file(GLOB IMG Shaders/*.png)
add_custom_command(
    TARGET FausEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${IMG}
        ${CMAKE_BINARY_DIR}/bin/Shaders
   )

###########################################
set(PATH_INSTALL ${PROJECT_SOURCE_DIR}/out/install)
install(TARGETS 
	FausEngine DESTINATION  ${PATH_INSTALL}/bin 
	LIBRARY DESTINATION ${PATH_INSTALL}/bin 
	PUBLIC_HEADER DESTINATION ${PATH_INSTALL}/include) 