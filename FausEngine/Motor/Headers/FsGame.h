#ifndef FSGAME
#define FSGAME

#include"FsDLL.h"
#include"FsScene.h"
#include"FsCamera.h"
#include"FsShader.h"
#include"FsSkybox.h"

#include"FsMesh.h"

//#include<stdio.h>
#include <string>
#include<iostream>
#include<vector>

namespace FausEngine {

	// codigo ascii alfanumericos imprimibles teclado USA
	enum class Keys {
		SPACE = 32, 
		APOSTROPHE = 39,
     	COMMA = 44,
		MINUS = 45, 
		DOT = 46,
		SLASH = 47,
        N0 = 48,
		N1 = 49,
		N2 = 50,
		N3 = 51,
		N4 = 52,
		N5 = 53,
		N6 = 54,
		N7 = 55,
		N8 = 56,
		N9 = 57,
		SEMICOLON = 59,
		EQUAL = 61,
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		LEFT_BRACKET = 91, // [ 
		BACKSLASH = 92, // \ 
		RIGHT_BRACKET = 93, // ]
		GRAVE_ACCENT = 96,  // ` 
		ESCAPE = 256,
		ENTER = 257,
		TAB =   258,
		RETROCESO = 259,
		INSERT = 260,
		DELETE = 261,
		RIGHT = 262,
		LEFT = 263,
		DOWN = 264,
		UP = 265,
		PAGE_UP = 266,
		PAGE_DOWN = 267,
		HOME = 268,
		END = 269,
		CAPS_LOCK = 280,
		NUM_LOCK = 282,
		PRINT_SCREEN = 283,
		PAUSE = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		LEFT_SHIFT = 340,
		LEFT_CONTROL = 341,
		LEFT_ALT = 342,
		LEFT_SUPER = 343,
		RIGHT_SHIFT = 344,
		RIGHT_CONTROl = 345,
		RIGHT_ALT = 346,
		RIGHT_SUPER = 347,
		MENU = 348,
	};

	class EXPORTDLL FsGame
	{
	public:
		FsGame();
		~FsGame();

		bool Construct(float width, float height, std::string name, bool fullscreen);
		void Run(std::vector<FsScene*>);
		//void Run(std::vector<std::shared_ptr<FsScene>>);
		void SetScene(int);

		void SetCamera(FsCamera&);
		void SetSkybox(FsSkybox&);
		template<typename light> void LoadLight(light*);
		//template<typename light> void LoadDLight(std::shared_ptr<light>);
		//template<typename light> void LoadRLight(light&);
		//template<typename light> void LoadLight(std::shared_ptr<light>);

		static std::shared_ptr<FsGame> GetReference();
		std::shared_ptr<FsShader> GetShader(int);
		std::shared_ptr<FsCamera> GetCamera();

		//window
		float GetMouseX();
		float GetMouseY();
		bool GetKeyPress(Keys);
		void SetKeyRelease(Keys);


	};
}
#endif // ! FGAME