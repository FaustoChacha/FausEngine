file(GLOB CODIGO Source/*.cpp )

add_library(FausEngine SHARED ${CODIGO} "Headers/FsObject.h")
set_target_properties(FausEngine PROPERTIES 
	COMPILE_DEFINITIONS EXPORTDLL
	)	
	#[[
	PUBLIC_HEADER Headers/fDirectionalLight.h
	PUBLIC_HEADER Headers/fGame.h
	PUBLIC_HEADER Headers/fLight.h
	PUBLIC_HEADER Headers/fMaterial.h
	PUBLIC_HEADER Headers/fMaths.h
	PUBLIC_HEADER Headers/fMesh.h
	PUBLIC_HEADER Headers/fModel.h
	PUBLIC_HEADER Headers/fObject.h
	PUBLIC_HEADER Headers/fPointLight.h
	PUBLIC_HEADER Headers/fSpotLight.h
	]]

target_link_libraries(FausEngine ${CONAN_LIBS})


set(PATH_INSTALL ${PROJECT_SOURCE_DIR}/out/install)
install(TARGETS 
	FausEngine DESTINATION  ${PATH_INSTALL}/bin 
	LIBRARY DESTINATION ${PATH_INSTALL}/bin 
	PUBLIC_HEADER DESTINATION ${PATH_INSTALL}/include) 