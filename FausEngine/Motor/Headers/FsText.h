#ifndef FSTEXT
#define FSTEXT

#include"FsExport.h"
#include"FsMaths.h"
#include"FsShader.h"

#include <map>
#include <iostream>
#include <string>

namespace FausEngine {

	struct Character {
		unsigned int texture = {};
		FsVector3 size; 
		FsVector3 offset; 
		unsigned int advance;
	};

	class FAUSENGINE_API  FsText
	{
	public:
		FsText();
		void Load(std::string font, int size, std::string text, FsVector3 position, FsVector3 color);
		
		void SetPosition(FsVector3);
		void SetText(std::string);
		void SetColor(FsVector3);

		FsVector3 GetPosition();
		FsVector3 GetColor();
		
		void Render();
		~FsText();

	private:
		std::shared_ptr<FsShader> shader;
		std::string text;
		FsVector3 color;
		FsVector3 position;

		std::map<char, Character> Characters;
	};


}

#endif // !FSTEXT
