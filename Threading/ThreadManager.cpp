#include "PCHFile.h"
#include "ThreadManager.h"


namespace XTOOL
{
    //every single ThreadManager can manage 10 thread
    uLONG XThreadManager::sMaxThread = 10;
    
    XThreadManager::XThreadManager()
    {
        
        fMutex = new std::mutex();
    }
    
    XThreadManager::~XThreadManager()
    {
        delete fMutex;
    }
    
    bool XThreadManager::LockSection()
    {
        //TODO: Add debug & trace informations
        if (fMutex == NULL )
        {
            return false;
        }
        else
        {
            try{
                fMutex->lock();
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
        if (fMutex == NULL )
        {
            return false;
        }
        else
        {
            try{
                fMutex->unlock();
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
        if (fMutex == NULL )
        {
            return false;
        }
        else
        {
            return fMutex->try_lock();
        }
    }
}