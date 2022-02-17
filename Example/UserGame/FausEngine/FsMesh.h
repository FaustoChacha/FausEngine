#ifndef FSMESH
#define FSMESH

#include "FsDLL.h"

class EXPORTDLL FsMesh
{
public:
	FsMesh();

	void CreateMesh(float* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void RenderMesh();
	void ClearMesh();

	~FsMesh();

private:
	unsigned int VAO, VBO, IBO;
	unsigned int indexCount;
};


#endif // !FSMESH


