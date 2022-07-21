#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <map>
#define GLEW_STATIC
#include "GL/glew.h"
#include "glm/glm.hpp"

#include "FsDLL.h"
#include "FsMaths.h"

namespace FausEngine {
	class EXPORTDLL Shader
	{
	public:
		Shader();
		~Shader();

		bool Load(const char* vsFilename,const char* fsFilename);
		void Use();

		unsigned int GetShaderId() const;

		void SetUniform3f(const char* name, const FsVector3& v);
		void SetUniformMatrix4fv(const char* name, const glm::mat4& m); // usado setting inicial 
		void SetUniform1f(const char* name, const float f); //usado
		void SetUniform1i(const char* name, const int v); // usado para el contador de luces


	private:

		unsigned int ShaderID;
	};
}
#endif // SHADER_H