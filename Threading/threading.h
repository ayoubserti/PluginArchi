/*
@Author: Ayoub Serti

*/
#include "Types.h"

#ifndef __THREADING__
#define __THREADING__

//forward declaration

namespace std{
    class thread;
    class mutex;
}

namespace XTOOL
{
    //IThread is thread interface
    /*
      it's a java style thread definition
    */
    class IThread;
    
    class XThreadManager;
    
    static void* runThread(IThread* inThread);
    
    class IThread
    {
        public:
        
        
        IThread();
        explicit IThread( XThreadManager* inManager);
        
        virtual ~IThread();
        TError Start();
        TError Join();
        TError Detach();
        
        std::thread* This();
        
        /*
          Set a Thread Manager. TODO: think about the safety of this function
        */
        TError SetManager (XThreadManager* inManager);
        
        
        protected:
        
        virtual void* OnRun()    = 0; // make it private
        enum Thread_Stat
        {
            eNone =0,
            eRunning =1,
            eDetached = 2,
            eJoined = 4
        };
        std::thread* fThread;
        unsigned long fStat;
        
        friend  void* XTOOL::runThread(IThread* inThread); //C approach. maybe we would use std::function instead 
        XThreadManager* fManager;
        
    };
    
    //ThreadMessage
    
    class ThreadMessage
    {
        
    };
    
}

#endif //__THREADING__