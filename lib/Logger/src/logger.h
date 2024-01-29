#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <chrono>
#include <vector>

class CLogger
{
    public:
        typedef std::ostream& (*ManipFnc)(std::ostream&);
        typedef std::ios_base& (*FlagsFnc)(std::ios_base&);

        enum LogLevel : unsigned char
        {
            ERROR = 0,
            WARN = 1,
            INFO = 2,
            DEBUG = 3
        };


        CLogger(LogLevel out_log_level = kDefaultOutputLogLevel, bool debug = false);
        ~CLogger();
        template<class T> CLogger& operator<<(const T& rhs)
        {
            if (isDebugLogger) 
                std::cout << "Log() operator<< called." << std::endl;
            mStream << rhs;
            return *this;
        }
        CLogger& operator<< (ManipFnc manip);
        CLogger& operator() (LogLevel loglev = DEBUG);
        void flush();
        void setDebugLogger(bool debug);
            
    private:
        std::stringstream mStream;
        LogLevel mMessageLogLevel;
        static const LogLevel kDefaultOutputLogLevel = ERROR;
        static const LogLevel kDefaultMessageLogLevel = DEBUG;
        static const std::vector<std::string> kLogSeverityLevels; // defined in .cpp
        LogLevel mOutputLogLevel;
        bool isDebugLogger;
        bool isAfterFlush = false;
        std::chrono::steady_clock::time_point programStart;

};

extern CLogger Log;

const extern CLogger::LogLevel DEBUG;
const extern CLogger::LogLevel WARN;
const extern CLogger::LogLevel ERROR;
const extern CLogger::LogLevel INFO;
