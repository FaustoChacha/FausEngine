#ifndef FSMODEL
#define FSMODEL

#include "FsDLL.h"
#include"FsMaths.h"

#include <vector>
#include <string>

#include "FsMesh.h"
#include "FsTexture.h"

namespace FausEngine {
	class EXPORTDLL FsModel
	{
	public:
		FsModel() = default;
		FsModel(std::string _pathModel, std::string _pathTextures);

		void LoadModel();
		void LoadAuxTexure(std::string);
		void SetTransform(FsTransform);
		void SetPosition(FsVector3&);
		void SetRotation(FsVector3&);
		void SetScale(FsVector3&);
		FsTransform* GetTransform();
		void RenderModel();
		void ClearModel();

		~FsModel();

	private:

		template<typename Node, typename Scene>
		void LoadNode(Node* node, const Scene* scene);
		template<typename Mesh, typename Scene>
		void LoadMesh(Mesh* mesh, const Scene* scene);
		template<typename Scene>
		void LoadMaterials(const Scene* scene);

		std::vector<FsMesh*> meshList;
		std::vector<FsTexture*> textureList;
		std::vector<unsigned int> meshToTex;

		std::string pathModel, pathTextures, pathAuxTex;
		FsTransform transform;

	};
}

#endif // !FSMODEL