#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

namespace FoxEngine {
    struct ProfileResult
    {
        std::string Name;
        long long Start, End;
        uint32_t ThreadId;
    };

    struct InstrumentationSession
    {
        std::string Name;
    };

    class Instrumentor
    {
    private:
        InstrumentationSession* currentSession;
        std::ofstream outputStream;
        int profileCount;
    public:
        Instrumentor()
            : currentSession(nullptr), profileCount(0)
        {
        }

        void beginSession(const std::string& name, const std::string& filepath = "results.json")
        {
            outputStream.open(filepath);
            writeHeader();
            currentSession = new InstrumentationSession{ name };
        }

        void endSession()
        {
            writeFooter();
            outputStream.close();
            delete currentSession;
            currentSession = nullptr;
            profileCount = 0;
        }

        void writeProfile(const ProfileResult& result)
        {
            if (profileCount++ > 0)
                outputStream << ",";

            std::string name = result.Name;
            std::replace(name.begin(), name.end(), '"', '\'');

            outputStream << "{";
            outputStream << "\"cat\":\"function\",";
            outputStream << "\"dur\":" << (result.End - result.Start) << ',';
            outputStream << "\"name\":\"" << name << "\",";
            outputStream << "\"ph\":\"X\",";
            outputStream << "\"pid\":0,";
            outputStream << "\"tid\":" << result.ThreadId << ",";
            outputStream << "\"ts\":" << result.Start;
            outputStream << "}";

            outputStream.flush();
        }

        void writeHeader()
        {
            outputStream << "{\"otherData\": {},\"traceEvents\":[";
            outputStream.flush();
        }

        void writeFooter()
        {
            outputStream << "]}";
            outputStream.flush();
        }

        static Instrumentor& getInstance()
        {
            static Instrumentor instance;
            return instance;
        }
    };

    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char* name)
            : name(name), stopped(false)
        {
            startTimePoint = std::chrono::high_resolution_clock::now();
        }

        ~InstrumentationTimer()
        {
            if (!stopped)
                Stop();
        }

        void Stop()
        {
            auto endTimePoint = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimePoint).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

            uint32_t threadId = std::hash<std::thread::id>{}(std::this_thread::get_id());
            Instrumentor::getInstance().writeProfile({name, start, end, threadId});

            stopped = true;
        }
    private:
        const char* name;
        std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;
        bool stopped;
    };
}

#define FOX_PROFILE 1
#if FOX_PROFILE
#define FOX_PROFILE_BEGIN_SESSION(name, filepath) ::FoxEngine::Instrumentor::getInstance().beginSession(name, filepath)
#define FOX_PROFILE_END_SESSION() ::FoxEngine::Instrumentor::getInstance().endSession()
#define FOX_PROFILE_SCOPE(name) ::FoxEngine::InstrumentationTimer timer##__LINE__(name)
#define FOX_PROFILE_FUNCTION() FOX_PROFILE_SCOPE(__FUNCSIG__)
#else
#define FOX_PROFILE_BEGIN_SESSION(name, filepath)
#define FOX_PROFILE_END_SESSION()
#define FOX_PROFILE_SCOPE(name)
#define FOX_PROFILE_FUNCTION()
#endif