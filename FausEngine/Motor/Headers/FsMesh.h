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
		//FsMesh(std::string path);
		~FsMesh();

		void Load(std::string path);
		void SetCollider(FsCollider&);
		void SetMaterial(FsMaterial&);
		void SetVisibility(bool);
		void SetTransform(FsTransform);
		void SetPosition(FsVector3);
		void SetScale(FsVector3);
		void SetRotation(FsVector3);
		FsTransform GetTransform();
		bool GetVisibility();
		void Render();

		

	private:
		std::shared_ptr<FsShader> shader;
		std::shared_ptr<FsMaterial> mat;
		std::shared_ptr<FsCollider> collider;

		std::vector<float> elementosVertice;
		std::vector<float> vertexElements;
		FsVector3 distanceCollider[4];

		bool on;
		unsigned int VBO, VAO;
		bool meshLoaded;
		std::string path;
		FsTransform transform;
		
		//FsLog logger;
	};

}
#endif //FSMESH