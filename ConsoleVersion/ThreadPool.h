#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <vector>
#include "DownloaderThread.h"

namespace Fyzxs{
namespace Downloader{

    class DownloaderThreadPool{
    public:
        static void Initialize(size_t, size_t, size_t);//Thread Pool Size; PollPeriodMs; buffer_size : Starts "pollingThread"
        static void Shutdown();//call stop && clear threads
        static void Stop();//set running false - kill pollingThread
        static void Resume();//set running true - recreate pollingThread


        /*
            I'm doing this as a singleton because... 
            I DON'T HAVE REASONS!!! ... Getting my head wrapped on C++
            It's either a singleton or functions...
            TRYING THINGS!!! LEAVE ME ALONE!!! *crys*
        */
        static DownloaderThreadPool& get_instance(){
            static DownloaderThreadPool instance_;
            return instance_;
        }

    private:
        std::mutex running_lock;//Mutuex to lock thread operations on
        std::mutex thread_lock;//lock when handling threads
        std::queue<DownloaderThread> queuedThreads;
        std::vector<DownloaderThread> activeThreads;
        std::thread pollingThread;//Thread to check the DB and adjust thread states

        bool running_ = false;
        size_t maxThreads_ = 3;
        size_t pollPeriod_ = 1000;
        size_t bufferSize_ = 1024;

        void PollPersistantStore();//Clear finished threads THEN If running && activeThreads < max_threads then check store for {STATES}

    };

}
}