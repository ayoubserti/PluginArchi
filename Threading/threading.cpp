#include "PCHFile.h"

#include "threading.h"
#include "RefManaged.h"
#include "ThreadManager.h"

namespace XTOOL
{

   
    
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
        fManager = new XThreadManager();
    }
    
    IThread::IThread(XThreadManager* inManager)
    {
        fStat = eNone;
        fThread = NULL;
        fManager = RetainManagedRef(inManager);
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
        
        ReleaseManagedRef(fManager);
        
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
    
    TError IThread::SetManager (XThreadManager* inManager)
    {
        ReleaseManagedRef(fManager);
        fManager = RetainManagedRef(inManager);
        
        return 0;
    }
}


