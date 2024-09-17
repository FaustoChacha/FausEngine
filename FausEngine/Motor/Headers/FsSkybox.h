#ifndef FSSKYBOX
#define FSSKYBOX

#include"FsExport.h"
#include"FsMaths.h"

#include<string>
#include<vector>

namespace FausEngine {
	class FAUSENGINE_API  FsSkybox
	{
	public:
		FsSkybox();
		void Load(std::vector<std::string>);

		void SetColour(FsVector3);
		void SetActive(bool);
		FsVector3 GetColour();
		bool GetActive();
		unsigned int GetTextureID();
		~FsSkybox();

	private:
		unsigned int textureID;
		std::vector<std::string> pathFaces;
		FsVector3 colour;
		bool active;
	};
}
#endif // !FSSKYBOX
