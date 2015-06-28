#include "PCHFile.h"

#include "threading.h"



namespace XTOOL
{

    //static function declaration
    static void* runThread(IThread* inThread)
    {
        if ( inThread != NULL)
        {
            return inThread->OnRun();
        }
        
    }

    IThread::IThread()
    {
        fStat =eNone;
        fThread = NULL;
    }
    
    IThread::~IThread()
    {
        if (fThread != NULL )
        {
            if ( (fStat & eDetached == 0) && (fStat & eRunning) )
            {
                Detach();
            }
            
            delete fThread;
        }
        
    }
    
    TError IThread::Start()
    {
        //TODO: catch exception 
        fThread = new std::thread(runThread,this); // create thread and pass
        if (fThread != NULL)
        {
            fStat = eRunning;
            return 0;
        }
        else
        {
            //error code
            return -1;
        }
    }
    
    TError IThread::Join()
    {
        if ( fThread != NULL )
        {
          fThread->join();
          // thread blocks
          fStat &= eJoined;
        }
        else
        {
            return -1;
        }
    
    }
    TError IThread::Detach()
    {
        if ( fThread != NULL )
        {
            fThread->detach();
            fStat &= eDetached;
            return 0;
        }
        else
        {
            return -1;
        }
    }
    
    std::thread* IThread::This()
    {
        return fThread;
    }
}

class TestThread : public XTOOL::IThread
{
    private:
    void* OnRun()
    {
        std::cout << " From Thread:;" << std::endl;
    }
};

