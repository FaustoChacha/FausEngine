cmake_minimum_required (VERSION 3.8)
#include(GenerateExportHeader)

project(FausEngine VERSION 1.0.0 #[[DESCRIPTION "Prueba de mi DLL"]] )

################# CONAN SETUP ###########################
find_program(conan conan)
execute_process(COMMAND ${conan} install -s build_type=${CMAKE_BUILD_TYPE} ${CMAKE_CURRENT_SOURCE_DIR})
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
#########################################################

add_subdirectory("MotorGrafico")

add_executable (FausEngineE  
	"ejemplo/main.cpp" 
	"MotorGrafico/Source/Window.cpp"
	"ejemplo/UserGame.cpp"
	"ejemplo/Escenario.cpp"
)

target_link_libraries(FausEngineE FausEngine) #${CONAN_LIBS}
