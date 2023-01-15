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
		void CreateLogger(std::string loggerName, std::string fileName);
		void SetMessage(std::string logMsg, int type ); //0=info, 1=warn, 2=error
		void SetName(std::string name);

	private:
		std::string loggerName, fileName;
	};


}

#endif // !FSLOG
