#ifndef FSMESH
#define FSMESH

#include <vector>
#include <string>

#include "FsDLL.h"
#include "FsMaths.h"
#include "FsMaterial.h"
#include "FsCollider.h"
#include "FsLog.h"
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
		std::shared_ptr<FsShader> shader;
		unsigned int VBO, VAO;
		bool meshLoaded;
		std::string path;
		std::vector<float> elementosVertice;
		std::vector<float> vertexElements;
		//FsCollider* collider = nullptr;
		std::shared_ptr<FsCollider> collider;
		FsVector3 distanceCollider[4];
		FsLog log;
	};

}
#endif //FSMESH