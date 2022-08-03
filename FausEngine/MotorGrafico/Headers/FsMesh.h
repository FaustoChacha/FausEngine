#ifndef FSMESH
#define FSMESH

#include <vector>
#include <string>

#include "FsDLL.h"
#include "FsMaths.h"
#include "FsMaterial.h"

namespace FausEngine {

	class EXPORTDLL FsMesh
	{
	public:

		FsMesh();
		FsMesh(std::string path);
		~FsMesh();

		void LoadMesh();
		void Render();
		int algo()const;

		FsTransform meshTransform;
		FsMaterial material;

	private:
		unsigned int VBO, VAO;
		bool meshLoaded;
		std::string path;
		int a;
		std::vector<float> elementosVertice;
		std::vector<float> vertexElements;
	};

}
#endif //FSMESH