#include <stdint.h>
#include <string>
#include <map>
#include "DownloadManager.h"

namespace Laskon{
namespace Downloader{

    size_t DownloadManager::Enqueue(const std::wstring uri, const DownloadType downloadType){
        if (downloadType != DownloadType::kHttp) {
            fprintf(stderr, "Only Http is currently implemented");
            return -1;
        }

        fprintf(stdout, "Queuing [uri=%s]", uri);
        
        DownloadManager &dm = DownloadManager::get_instance(); 
        dm.downloads_.insert(std::pair<std::wstring, DownloadState>(uri, DownloadState::kQueued));
        return dm.downloads_.size();

    }

    DownloadState DownloadManager::State(const size_t downloadId){
        DownloadManager &dm = DownloadManager::get_instance();
        std::pair<std::wstring, DownloadState> dlPair = dm.get_download(downloadId);
        return dlPair.second;//It's either valid or returned kInvalid
    }
    void DownloadManager::Pause(const size_t downloadId){
        set_state(downloadId, DownloadState::kPaused);
    }
    void DownloadManager::Cancel(const size_t downloadId){
        set_state(downloadId, DownloadState::kCancelRequested);
    }

    void DownloadManager::set_state(const size_t downloadId, const DownloadState downloadState){
        DownloadManager &dm = DownloadManager::get_instance();
        std::pair<std::wstring, DownloadState> dlPair = dm.get_download(downloadId);
        dlPair.second = downloadState;
    }

    /*
        Returns the appropriate pair; or creates a new pair of '\0', DownloadState::kUnknown
    */
    std::pair<std::wstring, DownloadState> DownloadManager::get_download(const size_t downloadId){
        DownloadManager &dm = DownloadManager::get_instance();

        if (downloadId >= 1 && downloadId <= dm.downloads_.size()){

            std::map<std::wstring, DownloadState>::iterator it(dm.downloads_.begin()),
                itEnd(dm.downloads_.end());
            int i = 0;
            while (it != itEnd && i < downloadId){
                ++i;
                if (i == downloadId){
                    fprintf(stdout, "Returning [state=%d] for [url=%s]", (*it).second, (*it).first);
                    return (*it);
                }
                ++it;
            }
        }

        fprintf(stderr, "[downloadId=%d] is an invalid id", downloadId);
        return std::pair<std::wstring, DownloadState>('\0', DownloadState::kUnknown);
    }

}
}