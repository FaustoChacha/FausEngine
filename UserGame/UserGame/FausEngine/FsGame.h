#ifndef FSGAME
#define FSGAME

#include"FsDLL.h"
#include"FsObject.h"
#include"FsCamera.h"
#include"FsShader.h"

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
		template<typename light> void LoadLight(light*);

		static FsGame* GetInstance();
		FsShader* GetShader();
		FsCamera* GetCamera();

		//window
		bool* GetKeys();
		float GetMouseX();
		float GetMouseY();

	};

	//static std::string GetPath();

}
#endif // ! FGAME