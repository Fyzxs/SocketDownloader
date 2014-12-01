#pragma once

#include <stdint.h>
#include <string>
#include <map>

namespace Fyzxs{
namespace Downloader{

    /*
        This should be a real state machine. But... TO BAD FOR YO---- me... oh...
        TODO: StateMachine-ify (hahaha)
    */
    enum DownloadState { 
        kUnknown=0, 
        kQueued=1, 
        kResume=2,
        kInProgress=3,
        kPaused=4,
        kCancelRequested=5,
        kCancelled=6,
        kComplete=7,
        kFailed=8
    };

    class DownloadManager{
    public:
        /*
            I'm doing this as a singleton because... 
            I DON'T HAVE REASONS!!! ... Getting my head wrapped on C++
            It's either a singleton or functions...
            TRYING THINGS!!! LEAVE ME ALONE!!! *crys*
        */
        static DownloadManager& get_instance(){
            static DownloadManager instance_;
            return instance_;
        }
        //
        //  Static Methods
        //

        /*
            Enqueue a download to start getting processed
        */
        static size_t Enqueue(const std::wstring, const DownloadType);
        /*
            Get the current state for the download
        */
        static DownloadState State(const size_t);
        /*
            Pause the download
        */
        static void Pause(const size_t);
        /*
            Cancel the download
        */
        static void Cancel(const size_t);
        /*
            Resume the download
        */
        static void Resume(const size_t);
        /*
            Retrieve how much of the file has been downloaded
        */
        static size_t Downloaded(const size_t);

    private:
        DownloadManager(){};
        DownloadManager(DownloadManager const&);
        void operator=(DownloadManager const&);

        /*
            Private statics... HACK!
        */
        /*
            Quick hack to extract the file name
        */
        static std::wstring& get_local_path(std::wstring const&);

        /*
            Update the state of the download
        */
        static void set_state(const size_t, const DownloadState);
        /*
            Retrieve the download information
        */
        std::pair<std::wstring, DownloadState> get_download(const size_t);

        /*
            Temporary hack of storing the download
        */
        std::map<std::wstring, DownloadState> downloads_;
    };
        

}
}