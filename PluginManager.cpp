/*
 Author: Ayoub Serti
 subject: Plugin Architucture example 
*/
/*
    this file contains C++11 code
    please use flags -std=c++11 
*/
#include "PCHFile.h"
#include "PluginManager.h"
#include "PluginLibrary.h"


#include <assert.h> 
//12345

using namespace std;
namespace XTOOL
{
    enum PlgMgrErrors
    {
        PlgMgr_OK = ERR_OK,
        PlgMgr_Plugin_already_found,
        PlgMgr_Plugin_Not_found,
        PlgMgr_Plugin_Couldnt_load,
        //keep it in last position
        PlgMgr_NOT_Implemented
        
        
    };
    
    PluginManager* PluginManager::sInstance = NULL;
    TDirPath PluginManager::sPluginsDir = "/home/dectroo/PluginArchi/";
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
    
    TError PluginManager::Init()
    {
        TError error = PlgMgr_OK;
        ScanPlugins(sPluginsDir);
        //now, we have created all PluginLibrary objects
        //iterate over those Lib and search potential IPlugin without register them
        for (std::vector<PluginLibrary*>::iterator it = sLibraries.begin(), end = sLibraries.end(); (it != end) && (error == ERR_OK); ++it)
        {
            error = (*it)->LoadFromFile();
            if ( error == ERR_OK)
            {
                
                vector<TPluginType> plgTypes;
                error = (*it)->GetPluginsTypes(plgTypes);
                
                if ( error == ERR_OK )
                {
                    sLibPlugTypeMap[(*it)->Retain()] = plgTypes; 
                    for (TPluginType& plt : plgTypes)
                    {
                        if ( sCondidatePluginType.find(plt) == sCondidatePluginType.end())
                        {
                            // plugin type doesn't exist already, so add it and mark it doesn't be retained yet
                            sCondidatePluginType[plt] = false;
                        }
                        else
                        {
                            error = PlgMgr_Plugin_already_found;
                        }
                    }
                }
                else
                {
                    error = PlgMgr_Plugin_Couldnt_load;
                    std::cout << error << " could not load" << std::endl ;
                }
                
            }
            
        } 
        
        return error;
    }
    
    TError PluginManager::RegisterPlugin(const TPluginPath& inPluginPath)
    {
        TError error = PlgMgr_OK; //OK
        
        error = PlgMgr_NOT_Implemented;
        
        assert(error != PlgMgr_NOT_Implemented);
        
        
        return error;
    }
    
    TError PluginManager::RegisterPlugin (TPluginType inPluginType)
    {
        TError error = PlgMgr_OK;
        
        
        return error;
    }
    

    
    //private functions
    void PluginManager::ScanPlugins (const TDirPath& inDirPlugins )
    {
        if ( !sPluginsDir.empty())
        {
            //TODO:here create XFolders and iterate over XFiles;
            PluginLibrary* myPlLib = new PluginLibrary(inDirPlugins+"Plug0.so");
            sLibraries.push_back(myPlLib->Retain());
            myPlLib->Release();
        }
    }
    
    IPlugin*    PluginManager::RetainPluginByType(TPluginType  inPluginType)
    {
        
        IPlugin* result = NULL;
        
        if  (sPluginMap.find(inPluginType) != sPluginMap.end())
        {
            if ( sPluginMap[inPluginType])
                return   sPluginMap[inPluginType]->Retain();
            
        }
        else
        {
            if ( sCondidatePluginType.find(inPluginType) != sCondidatePluginType.end())
            {
                if (!sCondidatePluginType[inPluginType])
                {
                    //if plugin was found but it's not loaded from library 
                    PluginLibrary* plgLib = GetLibraryContainer(inPluginType);
                    if (plgLib)
                    {
                        IPlugin* iPlg = plgLib->RetainPluginByType(inPluginType);
                        if (iPlg != NULL)
                        {
                            sPluginMap[inPluginType] = iPlg->Retain();
                            sCondidatePluginType[inPluginType] = true;
                            result =sPluginMap[inPluginType]->Retain();
                        }
                        
                    }
                    else 
                    {
                        return NULL;
                    }
                }
            }
            else
            {
              //error = PlgMgr_Plugin_Not_found;   
            }
        }
        
        return result;
    }
    
    PluginLibrary* PluginManager::GetLibraryContainer( TPluginType inPluginType)
    {
        PluginLibrary* result = NULL;
        
        for (auto& elem : sLibPlugTypeMap)
        {
            if (find(elem.second.begin(),elem.second.end() ,inPluginType) != elem.second.end() )
            {
                result = elem.first;
                break;
            }
        }
        
        return result;
    }
    
}