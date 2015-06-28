/*
@Author: Ayoub Serti

*/
#include "Types.h"

#ifndef __THREADING__
#define __THREADING__

//forward declaration

namespace std{
    class thread;
}

namespace XTOOL
{
    //IThread is thread interface
    /*
      it's a java style thread definition
    */
    class IThread;
    
    static void* runThread(IThread* inThread);
    
    class IThread
    {
        public:
        
        
        IThread();
        virtual ~IThread();
        TError Start();
        TError Join();
        TError Detach();
        
        std::thread* This();
        
        
        private:
        
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
    };
    
    
}

#endif //__THREADING__