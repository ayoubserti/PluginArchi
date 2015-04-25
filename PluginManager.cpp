/*
 Author: Ayoub Serti
 subject: Plugin Architucture example 
*/
#include "PCHFile.h"
#include "PluginManager.h"
//12345
namespace XTOOL
{
    enum PlgMgrErrors
    {
        PlgMgr_OK = ERR_OK
        
    };
    
    PluginManager* PluginManager::sInstance = NULL;
    PluginManager::sPluginsDir = "";
    //ctor
    PluginManager::PluginManager()
    {
        
    }
    
    PluginManager& PluginManager::Get()
    {
        if (!PluginManager::sInstance)
            sInstance = new PluginManager();
        
        return *sInstance;
    }
    
    TError PluginManager::RegisterPlugin(const TPluginPath& inPluginPath)
    {
        TError error = PlgMgr_OK; //OK
                
        
        return error;
    }
    
    //private functions
    void PluginManager::ScanPlugins (const TDirPath& inDirPlugins )
    {
        if ( !TDirPath.empty())
        {}
    }
    
    
}