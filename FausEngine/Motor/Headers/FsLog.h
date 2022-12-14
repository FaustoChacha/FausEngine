#ifndef FSLOG
#define FSLOG

#include"FsDLL.h"
#include<iostream>

namespace FausEngine {
	
	class EXPORTDLL FsLog
	{
	public:
		FsLog();
		~FsLog();

		void Logger(std::string logMsg, std::string from);

	};


}

#endif // !FSLOG
