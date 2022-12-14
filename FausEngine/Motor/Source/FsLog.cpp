#include"../Headers/FsLog.h"
#include <fstream>

using namespace FausEngine;

FsLog::FsLog()
{
}

FsLog::~FsLog()
{
}

std::string GetCurrentDataTime(std::string s) {
    time_t now = time(0);
    struct tm  tstruct;
    char  buf[80];
    tstruct = *localtime(&now);
    if (s == "now")
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    else if (s == "date")
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    return std::string(buf);
}

void FsLog::Logger(std::string logMsg, std::string from) {
    std::string filePath =" log_" + GetCurrentDataTime("date") + ".txt";
    std::string now = GetCurrentDataTime("now");
    std::ofstream ofs(filePath.c_str(), std::ios_base::out | std::ios_base::app);
    ofs << now << '\t' << logMsg << '\n';
    ofs.close();
}
