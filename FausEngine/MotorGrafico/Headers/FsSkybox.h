#ifndef FSSKYBOX
#define FSSKYBOX

#include"FsDLL.h"
#include<string>
#include<vector>

namespace FausEngine {
	class EXPORTDLL FsSkybox
	{
	public:
		FsSkybox();
		FsSkybox(std::vector<std::string>);
		void Load();


		~FsSkybox();

	private:
		unsigned int textureID;
		std::vector<std::string> pathFaces;
	};
}
#endif // !FSSKYBOX
