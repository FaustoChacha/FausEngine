#ifndef FSSKYBOX
#define FSSKYBOX

#include"FsDLL.h"
#include"FsMaths.h"
#include"FsLog.h"
#include<string>
#include<vector>

namespace FausEngine {
	class EXPORTDLL FsSkybox
	{
	public:
		FsSkybox();
		FsSkybox(std::vector<std::string>);
		unsigned int GetTextureID();
		void Load();
		~FsSkybox();

		FsVector3 colour;
		bool on;

	private:
		
		unsigned int textureID;
		std::vector<std::string> pathFaces;
		FsLog logger;
	};
}
#endif // !FSSKYBOX
