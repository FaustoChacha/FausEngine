# CMakeList.txt: archivo del proyecto de CMake de nivel superior, establezca la configuración global
# e incluya los subproyectos aquí.
#
cmake_minimum_required (VERSION 3.8)

project ("FausEngine")

# Incluya los subproyectos.
#add_subdirectory ("conanPr")

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
	${SrcUser})
 
target_link_libraries(FausExe FausEngine) #${CONAN_LIBS

# TODO: Agregue pruebas y destinos de instalación si es necesario.
