cmake_minimum_required(VERSION 3.21.0)
#include(GenerateExportHeader)

project(FausEngine )
#find_package(IntelDPCPP REQUIRED)

################# CONAN SETUP ###########################
find_program(conan conan)
execute_process(COMMAND ${conan} install -s build_type=${CMAKE_BUILD_TYPE} ${CMAKE_CURRENT_SOURCE_DIR})
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
#########################################################

add_subdirectory("Motor")

file(GLOB SrcUser ejemplo/*.cpp)


add_executable (FausExe  
	"Motor/Source/Window.cpp"
	${SrcUser}
 )
 
target_link_libraries(FausExe FausEngine) #${CONAN_LIBS

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17) 


#[[
add_custom_command(
    TARGET FausExe POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${FSSHADERS}
        ${CMAKE_BINARY_DIR}/bin/shaders
   )
   ]]