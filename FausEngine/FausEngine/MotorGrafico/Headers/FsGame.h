#ifndef FSGAME
#define FSGAME

#include"FsDLL.h"
#include"FsObject.h"
#include"FsCamera.h"
//#include"FsShader.h"
//#include"FsSkybox.h"
#include <string>

namespace FausEngine {

	class EXPORTDLL FsGame
	{
	public:
		FsGame();
		~FsGame();

		bool Construct(float width, float height, std::string name);
		void Run(std::vector<FsObject*>);

		void SetCamera(FsCamera&);
		//void SetCurrentShader(FsShader*);
		//void SetSkybox(FsSkybox*);
		//template<typename light>
		//void SetLight(light*);
		void SetPathEngine(std::string);


		static FsGame* GetSelfReference();
		int* GetCountLights();
		//FsShader* GetCurrentShader();
		std::string GetPathEngine();
		FsCamera* GetCamera();
		bool* GetKeys();
		float GetMouseX();
		float GetMouseY();

	};


}
#endif // ! FGAME