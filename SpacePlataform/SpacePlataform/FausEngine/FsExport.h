#pragma once
#ifndef FSDLL
#define FSDLL

#ifdef WIN32
	#ifdef FAUSENGINE_EXPORTS
		#define FAUSENGINE_API  __declspec(dllexport)
	#else 
		#define FAUSENGINE_API  __declspec(dllimport)
	#endif // EXPORTDLL
#else 
	#define EXPORTDLL
#endif // WIN32
#endif
