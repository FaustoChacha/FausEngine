#ifndef MESH
#define MESH

#include <vector>
#include <string>

#include "GL/glew.h"	
#include "glm/glm.hpp"

#include "FsDLL.h"
#include "FsMaths.h"
#include"FsMaterial.h"

namespace FausEngine {

	class EXPORTDLL Mesh
	{
	public:

		Mesh();
		~Mesh();

		bool LoadMesh(std::string path);
		void Render();

		FsTransform meshTransform;
		FsMaterial material;

	private:
		unsigned int mVBO, mVAO;
		bool meshLoaded;

		std::vector<float> vertexElements;
	};

}
#endif //MESH