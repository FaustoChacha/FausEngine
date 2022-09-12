#pragma once
#ifndef FSDLL
#define FSDLL

#ifdef WIN32
	#ifdef EXPORTDLL
		#define EXPORTDLL __declspec(dllexport)
	#else 
		#define EXPORTDLL __declspec(dllimport)
	#endif // EXPORTDLL
#else 
	#define EXPORTDLL
#endif // WIN32
#endif
