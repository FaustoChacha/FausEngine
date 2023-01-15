#include"../Headers/FsLog.h"
#include <fstream>
#include"spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

using namespace FausEngine;
using namespace spdlog;


FsLog::FsLog()
{
    loggerName = "empty_logger";
    fileName = "log";
    
}

FsLog::~FsLog()
{
}

void FsLog::CreateLogger(std::string ln, std::string fn) {
    loggerName = ln;
    fileName = fn;
}

void FsLog::SetName(std::string n) {
    loggerName = n;
}

void FsLog::SetMessage(std::string logMsg, int type) {
    try
    {
        auto logger = spdlog::basic_logger_mt(loggerName, "logs/"+ fileName +".txt");
        switch (type)
        {
        case 0:
            logger->info(logMsg);
            break;
        case 1:
            logger->warn(logMsg);
            break;
        case 2: 
            logger->error(logMsg);
        default:
            logger->info(logMsg);
            break;
        }
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }
}



