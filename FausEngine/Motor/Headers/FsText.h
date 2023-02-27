#ifndef FSTEXT
#define FSTEXT

#include"FsDLL.h"
#include"FsMaths.h"
#include"FsShader.h"

#include <map>
#include <iostream>
#include <string>



namespace FausEngine {

	struct Character {
		unsigned int texture; 
		FsVector2 size; 
		FsVector2 offset; 
		unsigned int advance;
	};

	class EXPORTDLL FsText
	{
	public:
		FsText();
		void Load(std::string font, int size, std::string text, FsVector2 position, FsVector3 color);
		void Render();
		void SetPosition(FsVector2);
		void SetText(std::string);
		void SetColor(FsVector3);
		FsVector3 GetColor();
		FsVector2 GetPosition();
		~FsText();

	private:
		//FsShader* shader;
		std::shared_ptr<FsShader> shader;
		std::string text;
		FsVector3 color;
		FsVector2 position;

		std::map<char, Character> Characters;

		//FsLog logger;
	};


}

#endif // !FSTEXT
