#pragma once

#include <queue>

namespace Fyzxs{
namespace Downloader{

    class DownloaderManager{
    public:
        static void Initialize(size_t);//Thread Pool Size
        queueThread(DownloaderThread)
        shutdown

        //THREAD POOL??? 
        //How can I tell when a thread finishes for the thread pool?

    private:
        std::queue<DownloaderThread> queuedThreads
        std::vector<DownloaderThread> inProgressThreads


    };

}
}