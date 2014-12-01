/*
Why are you here? What do you expect from this old of a checkin?
My C++ is rusty and I'm "psuedo-coding". It'll take me ACTUALLY implementing
and reading a few books; to get my head back around C++ object initialization.
I think I've been in C# and Java land for too long
*/

/*
    I'm currently strongly leaning towards this being shoved into
    it's own little wrapper class. 
    Have some call backs for state updates (in/out); but to to keep it 
    fairly well abstracted.
    Yea... Needs to; once download_item is loaded; hit up a factory
    (That's gonna make a co-worker of mine cringe; both C++ guys seem to have
    issue with factories)
    and get the proper downloader.
    This will simplify updates to FTP; Gopher; HTTP(s), LocalFile, ect
    --- Or through the processof thinking; all that's shoved into the derived class;
    This now just needs the method for the workerThread.
*/
//abstract DoWork();//Virtual... yada yada

#include "DownloaderThread.h"

namespace Fyzxs{
namespace Downloader{
    bool DownloaderThread::operator==(const DownloaderThread& rhs){
        
    }
}
}