#ifndef FSMESH
#define FSMESH

#include "FsExport.h"
#include "FsMaths.h"
#include "FsMaterial.h"
#include "FsCollider.h"
#include"FsShader.h"
//#pragma warning
#include <vector>
#include <string>
#include<iostream>

namespace FausEngine {

	class FAUSENGINE_API  FsMesh
	{
	public:
		FsMesh();

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

		~FsMesh();

	private:
		std::shared_ptr<FsShader> shader;
		std::shared_ptr<FsMaterial> mat;
		std::shared_ptr<FsCollider> collider;

		std::vector<float> vertexElements;
		FsVector3 distanceCollider[4];

		bool on;
		unsigned int VBO, VAO;
		bool meshLoaded;
		std::string path;
		FsTransform transform;

	};

}
#endif //FSMESH