#pragma once

#include <stdint.h>
#include <string>
#include <map>

namespace Laskon{
namespace Downloader{

    enum DownloadState { 
        kUnknown=0, 
        kQueued=1, 
        kInProgress=2, 
        kPaused=3, 
        kCancelRequested=4, 
        kCancelled=5, 
        kComplete=6, 
        kFailed=7
    };
    enum DownloadType { 
        kUnknown = 0, 
        kHttp = 1, 
        kLocalFile = 2 
    };

    class DownloadManager{
    public:
        static DownloadManager& get_instance(){
            static DownloadManager instance_;
            return instance_;
        }
        /*
            Static Methods
        */
        static size_t Enqueue(const std::wstring, const DownloadType);
        static DownloadState State(const size_t);
        static void Pause(const size_t);
        static void Cancel(const size_t);

    private:
        DownloadManager(){};
        DownloadManager(DownloadManager const&);
        void operator=(DownloadManager const&);
        static void set_state(const size_t, const DownloadState);
        std::pair<std::wstring, DownloadState> get_download(const size_t);

        std::map<std::wstring, DownloadState> downloads_;
    };
        

}
}