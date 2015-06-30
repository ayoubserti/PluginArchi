/*
    Author: Ayoub Serti
    License: MIT
*/

#ifndef __THREAD_MANAGER__
#define __THREAD_MANAGER__
#include "Types.h"
#include "RefManaged.h"

namespace std
{
    class mutex;
    class thread;
}

namespace XTOOL
{
    
    //XThread Manager 
    /*
        @class XThreadManager
        @abstract Manage a Threads
    */
    class XThreadManager : public RefManaged
    {
        public:
        //ctors
        XThreadManager();
        
        /*
          construct Manager with a maximum threads number
        */
        
        explicit XThreadManager(uLONG inThreadCount);
        
        //dtor
        
        virtual ~XThreadManager();
        
        
        /*
         @function LockSection
         @abstract lock a code section where it's called
         @param void
         @return true if succed, false otherwise
        */
         bool LockSection(void);
        
         /*
         @function UnLockSection
         @abstract unlock a code section where it's called
         @param void
         @return true if succed, false otherwise
        */
        bool UnLockSection(void);
        
        
         /*
         @function TryLockSection
         @abstract try to lock a code section where it's called
         @param void
         @return true if succed, false otherwise
        */
        bool TryLockSection(void);
        
        
        protected:
        
        mutable std::mutex* fMutex;
        
        private:
        static uLONG sMaxThread;
        
        
        
    };
    
}

#endif //__THREAD_MANAGER__