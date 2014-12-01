#pragma once

/*
This is intended to be an abstract class.
It currently doesn't need a cpp file.
*/

namespace Fyzxs{
namespace Downloader{

    /*
    The type of download that is being done.
    */
    enum DownloadType {
        kUnknown = 0,
        kHttp = 1,
        kLocalFile = 2
    };

    class DownloadItem{
    public:
        virtual bool operator==(const DownloadItem& rhs) = 0;
    protected:
        DownloadItem(const DownloadType download_type){ download_type_ = download_type; };

    private:
        DownloadType download_type_ = DownloadType::kUnknown;
    };

}}