/*
 Author: Ayoub Serti
 subject: Plugin Architucture example 
*/

#include "PCHFile.h" //precompiled Headers
#include "PluginImpl.h"
#include "PluginLibrary.h"
#include "IPlugin.h"


// Init & Finish Functions
// in linux system PluginLibConstruct will be called at Library load 
// and PluginLibDestroy will be called at Library unload ( finish )
extern "C"
{
    void __attribute__ ((constructor)) PluginLibConstruct();
    void __attribute__ ((destructor)) PluginLibDestroy();
}

extern "C"{
    #include <dlfcn.h>
}

using namespace XTOOL;


//const definition
const char* cGetLibraryInfoName = "GetLibraryInfo"; //TODO: search if we need name mangling

//LibraryInfo function's implementation

//errors 
enum PlgLibErr
{
    PlgLibErr_OK = ERR_OK,
    PlgLibErr_LoadErr ,
    PlgLibErr_GetLibInfo_unexisting,
    PlgLibErr_NULL_LibInfos,
    PlgLibErr_LibNot_Loaded,
    
};


PluginLibrary::PluginLibrary()
{
    fRefCount =1;
    fLibraryPath="";
    fPluginCount =0;
    fLibHandle = NULL;
    fLibLoaded = false;
    fLibInfos  = NULL;
} 

PluginLibrary::PluginLibrary(const TFilePath& inLibraryPath)
{
    fRefCount =1;
    fLibraryPath=inLibraryPath;
    fPluginCount =0;
    fLibHandle = NULL;
    fLibLoaded = false;
    fLibInfos = NULL;
}

PluginLibrary::~PluginLibrary()
{
    if (fLibLoaded)
        if (fLibHandle)
            dlclose(fLibHandle);
    if (fLibInfos);
        //delete fLibInfos; //source de bug
    
}

TError PluginLibrary::LoadFromFile()
{
    TError error = PlgLibErr_OK;
    const char* xlib_path = fLibraryPath.c_str();
    fLibHandle = dlopen( xlib_path,RTLD_LAZY | RTLD_GLOBAL);
    if (fLibHandle == NULL)
    {
        //couldn't load library
        
        fputs(dlerror(),stderr);
        //may be we would like to throw exception
        error = PlgLibErr_LoadErr; 
    }
    else
    {
        //Find if GetLibraryInfo Exist
        GetLibraryInfoFunc xGetInfoFunc =  (GetLibraryInfoFunc)dlsym(fLibHandle,cGetLibraryInfoName);
        if (xGetInfoFunc == NULL)
        {
            fputs(dlerror(),stderr);
            error = PlgLibErr_GetLibInfo_unexisting;
        }
        else
        {
            fLibInfos = xGetInfoFunc();
            if ( fLibInfos != NULL )
            {
                fPluginCount = fLibInfos->pluginsType.size();
                fLibLoaded = true;
                fPluginTypes = fLibInfos->pluginsType;
                fPluginMap   = fLibInfos->pluginMap;
            }
            else
            {
                error = PlgLibErr_NULL_LibInfos;
            }
            /*
                TODO: store plugin types
            */
            
        }
    }
    
    return error;
}

TError PluginLibrary::UnLoad()
{
    TError error = PlgLibErr_OK;
    /*
      Unload shared object file
    */
    if ( fLibLoaded)
    {
        dlclose(fLibHandle);
    }
    
    
    return error;
}

uLONG  PluginLibrary::CountPlugins()
{
    
  return fPluginCount;
}

PluginLibrary* PluginLibrary::Retain()
{
    fRefCount++;
    return this;
}

void PluginLibrary::Release()
{
    if (!(--fRefCount))
       delete this;
}

IPlugin* PluginLibrary::RetainPluginByType(TPluginType inType)
{
    
    if ( fPluginMap.find(inType) != fPluginMap.end() )
    {
        return fPluginMap[inType];
    }
    return NULL;
}

TError  PluginLibrary::GetPluginsTypes(std::vector<TPluginType>& outTypes)
{
    TError error = ERR_OK;
    if ( fLibLoaded )
    {
        if ( fLibInfos != NULL)
        {
            outTypes = fPluginTypes;
        }
        else
        {
            error = PlgLibErr_NULL_LibInfos;    
        }
    }
    else{
        
        error = PlgLibErr_LibNot_Loaded;
    }
    return error;
}


void PluginLibConstruct()
{
#if defined(PLUGIN_PROJECT)
    XTOOL::PluginMain();
#endif 
}

void PluginLibDestroy()
{
    //perhaps we need it for force unregistring
}