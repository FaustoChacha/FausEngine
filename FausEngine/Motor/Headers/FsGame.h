#ifndef FSGAME
#define FSGAME

#include"FsDLL.h"
#include"FsObject.h"
#include"FsCamera.h"
#include"FsShader.h"
#include"FsSkybox.h"

#include <string>
#include<iostream>
#include<vector>

namespace FausEngine {
	class EXPORTDLL FsGame
	{
	public:
		FsGame();
		~FsGame();

		bool Construct(float width, float height, std::string name, bool fullscreen);
		void Run(std::vector<FsObject*>);
		void SetScene(int);

		void SetCamera(FsCamera&);
		void SetSkybox(FsSkybox&);
		template<typename light> void LoadLight(light*);

		static FsGame* GetInstance();
		FsShader* GetShader(int);
		FsCamera* GetCamera();

		//window
		bool* GetKeys();
		float GetMouseX();
		float GetMouseY();

	};
}
#endif // ! FGAME