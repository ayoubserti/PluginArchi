#include "PCHFile.h"
#include "ThreadManager.h"


namespace XTOOL
{
    //every single ThreadManager can manage 10 thread
    uLONG XThreadManager::sMaxThread = 10;
    
    XThreadManager::XThreadManager()
    {
        
        
    }
    
    XThreadManager::~XThreadManager()
    {
        
    }
    
    bool XThreadManager::LockSection()
    {
        //TODO: Add debug & trace informations
        
        {
            try{
                fMutex.lock();
            }
            catch(std::exception& e)
            {
                //log exception
                return false;
            }
            return true;
        }
    }
    
    bool XThreadManager::UnLockSection()
    {
        //TODO: Add debug & trace informations
        
        {
            try{
                fMutex.unlock();
            }
            catch(std::exception& e)
            {
                //log exception
                return false;
            }
            return true;
        }
    }
    
     bool XThreadManager::TryLockSection()
    {
        //TODO: Add debug & trace informations
        
        {
            return fMutex.try_lock();
        }
    }
}