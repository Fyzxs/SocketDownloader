#pragma once


namespace Fyzxs{
namespace Downloader{
    class DownloaderThread{
    public:
        Shutdown();
        IsFinished();
        

    protected:
        virtual ctor(){};//Whatever makes the class "abstract"
        //Copy Constructor (go refresh on reasons for stuff - like in the singleton)
        DownloadItem download_item_;//Item with the Download Information in it 
                                    //*jazzhands*FLEXIBLE

        operator=();//So we know if our threads are equal... This is an adventure in 
        //the land of C# and Java; ... yeahhhhh.....

    private:
        bool shutdown_;
        bool finished_;
        std::Thread worker = std::Thread(DoWork);

        abstract DoWork();//main.cpp - technically; the sample is for HTTP downloading.
    };
}
}