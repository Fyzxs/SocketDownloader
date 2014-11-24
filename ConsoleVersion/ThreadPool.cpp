
static void Initialize(size_t max_active_threads, 
                       size_t db_poll_period_ms, 
                       size_t stream_read_buffer_size)
{
    get_instance().set_max_active_threads(max_active_threads);
    get_instance().set_db_poll_period_ms(...);
    get_instance().set_stream_read_buffer_size);
    //Clean Up PersistantStore (in case of ungraceful shutdown)
        //This is up to the store to figure out; but return everything to a 
        //safe state
    Resume();
}
static void Shutdown()//call stop && clear threads
{
    Stop();
    //loop active Threads; stop - put in new queue
    //move queued items to new queue (or shove active into front of queue)
}
static void Stop()//set running false - kill pollingThread
{
    lock{
        running_ = false;
    }
}
static void Resume()//set running true - recreate pollingThread
{
    lock{
        running_ - true;
        pollingThread = Thread(PollPersistantStore);
        pollingThead.start();
    }
}

void PollPersistantStore(){//It's more "ThreadManagement"
    if(!running_){ return; }

    lock-running{
        if(!running_){ return; }
    }

    lock-thread{

        //Clean Up Finished Active Threads
        //query story for completed items
            //lock & adjust activeThreads
        //Query for new items
            //add to queued threads
    }
}