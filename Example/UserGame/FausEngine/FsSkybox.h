#ifndef FSSKYBOX
#define FSSKYBOX

#include "FsDLL.h"
#include <vector>
#include <string>

#include "FsMesh.h"
#include "FsShader.h"

namespace FausEngine {

	class EXPORTDLL FsSkybox
	{
	public:
		FsSkybox();

		FsSkybox(std::vector<std::string> faceLocations);

		template<typename Mat4>
		void DrawSkybox(Mat4 viewMatrix, Mat4 projectionMatrix);

		void Load();
		~FsSkybox();

	private:
		FsMesh* skyMesh;
		FsShader* skyShader;

		unsigned int textureId;
		unsigned int uniformProjection, uniformView;
	};
}

#endif // !FSSKYBOX