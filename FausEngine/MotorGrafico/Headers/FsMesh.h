#ifndef FSMESH
#define FSMESH

#include <vector>
#include <string>

#include "FsDLL.h"
#include "FsMaths.h"
#include "FsMaterial.h"
#include "FsCollider.h"
//#pragma warning


namespace FausEngine {

	class EXPORTDLL FsMesh
	{
	public:

		FsMesh();
		FsMesh(std::string path);
		~FsMesh();

		void LoadMesh();
		void SetCollider(FsCollider&);
		void Render();

		FsTransform transform;
		FsMaterial material;

		bool on;

	private:
		unsigned int VBO, VAO;
		bool meshLoaded;
		std::string path;
		std::vector<float> elementosVertice;
		std::vector<float> vertexElements;
		FsCollider* collider = nullptr;
		FsVector3 distanceCollider[4];
	};

}
#endif //FSMESH