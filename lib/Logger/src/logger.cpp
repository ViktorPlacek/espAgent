#include "logger.h"

using namespace std;
using namespace std::chrono;

const vector<string> CLogger::kLogSeverityLevels = {"ERROR", "WARN ", "INFO ", "DEBUG"};
const extern CLogger::LogLevel DEBUG = CLogger::DEBUG;
const extern CLogger::LogLevel WARN = CLogger::WARN;
const extern CLogger::LogLevel ERROR = CLogger::ERROR;
const extern CLogger::LogLevel INFO = CLogger::INFO;

CLogger::CLogger(LogLevel out_log_level, bool debug) : mOutputLogLevel(out_log_level), isDebugLogger(debug)
{
    if (isDebugLogger) 
        std::cout << "Log() LogLevel-parameter constructor called." << std::endl;
    programStart = chrono::steady_clock::now();
    mMessageLogLevel = kDefaultMessageLogLevel; // necessary for the case that the first call of CLogger object is without using operator()
}

CLogger::~CLogger()
{
    if (isDebugLogger) 
        std::cout << "Log() destructor called." << std::endl;
}
        
CLogger& CLogger::operator<<(ManipFnc manip)
{
    if (isDebugLogger) 
        std::cout << "Log() operator<< for flush and endl called." << std::endl;
    manip(mStream);

    if (manip == static_cast<ManipFnc>(std::flush)
     || manip == static_cast<ManipFnc>(std::endl) ) {
         this->flush();
     }
     return *this;
}
CLogger& CLogger::operator() (LogLevel loglev)
{
    if (isDebugLogger) 
        std::cout << "Log() operator() called." << std::endl;

    mMessageLogLevel = loglev;
    return *this;
}
void CLogger::flush()
{
    auto fromStart = duration_cast<milliseconds>(steady_clock::now() - programStart);
    if (isDebugLogger) {
        cout << "Output Log Level = " << mOutputLogLevel << endl;
        cout << "Message Log Level = " << mMessageLogLevel << endl;
    }

    if (mOutputLogLevel >= mMessageLogLevel) {
        cout << setw(6) << fromStart.count() << setw(0) << " ";
        cout << kLogSeverityLevels[mMessageLogLevel] << " :: " << mStream.str();
    }

    mStream.str( std::string() );
    mStream.clear();
    mMessageLogLevel = kDefaultMessageLogLevel;

}
    
void CLogger::setDebugLogger(bool debug) {
    isDebugLogger = debug;
}