#ifndef FSGAME
#define FSGAME

#include"FsDLL.h"
#include"FsObject.h"
#include"FsCamera.h"

#include"Shader.h"

#include <string>
#include<iostream>
#include<vector>

namespace FausEngine {

	class EXPORTDLL FsGame
	{
	public:
		FsGame();
		~FsGame();

		bool Construct(float width, float height, std::string name);
		void Run(std::vector<FsObject*>);

		void SetCamera(FsCamera&);

		template<typename light>
		void SetLight(light*);
		void SetPathEngine(std::string);


		static FsGame* GetSelfReference();
		Shader* GetShader();

		int* GetCountLights();

		std::string GetPathEngine();
		FsCamera* GetCamera();
		bool* GetKeys();
		float GetMouseX();
		float GetMouseY();

	private:
		Shader MainShader;

	};


}
#endif // ! FGAME