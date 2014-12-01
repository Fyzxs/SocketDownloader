#pragma once
#include <thread>
#include <memory>
#include "DownloadItem.h"

/*
    This is intended to be an abstract class.
    It currently doesn't need a cpp file.
*/

namespace Fyzxs{
namespace Downloader{
    class DownloaderThread{
    public:
        //Not sure if this works for passing in the download item. Rusty C++
        DownloaderThread(const std::shared_ptr<DownloadItem>& download_item) : worker(){ download_item_ = download_item; };
        ~DownloaderThread(){
            Shutdown();
            if (worker.joinable()){
                worker.join();
            }
        }
        virtual void Shutdown() { shutdown_ = true; }
        bool IsFinished() { return finished_; }
        virtual void Start(){ worker = std::thread(&DoWork, this); }
        virtual bool operator==(const DownloaderThread& rhs){ return this->download_item_ == rhs.download_item_; }
        //So we know if our threads are equal... This is an adventure in 
        //the land of C# and Java; ... yeahhhhh.....

    protected:
        std::shared_ptr<DownloadItem> download_item_;//Item with the Download Information in it 
                             //*jazzhands* FLEXIBLE
    private:
        virtual void DoWork() = 0;//main.cpp - technically; the sample is for HTTP downloading.
        /*
            HA! Apparently I am going C++11. YAY THREADS! ... This doesn't change anything; I still don't know what I'm doing.
        */
        std::thread worker;
        bool shutdown_;
        bool finished_;
    };
}
}