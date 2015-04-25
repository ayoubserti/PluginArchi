/*
 Author: Ayoub Serti
 subject: Plugin Architucture example 
*/

#include "PCHFile.h" //precompiled Headers
#include "PluginLibrary.h"
#include "IPlugin.h"

extern "C"{
    #include <dlfcn.h>
}

using namespace XTOOL;


//const definition
const char* cGetLibraryInfoName = "GetLibraryInfo"; //TODO: search if we need name mangling

//errors 
enum PlgLibErr
{
    PlgLibErr_OK = ERR_OK,
    PlgLibErr_LoadErr ,
    PlgLibErr_GetLibInfo_unexisting
};

PluginLibrary::PluginLibrary()
{
    fRefCount =1;
    fLibraryPath="";
    fPluginCount =0;
    fLibHandle = NULL;
    fLibLoaded = false;
}

PluginLibrary::PluginLibrary(const TFilePath& inLibraryPath)
{
    fRefCount =1;
    fLibraryPath=inLibraryPath;
    fPluginCount =0;
    fLibHandle = NULL;
    fLibLoaded = false;
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
            LibraryInfo* libInfo = xGetInfoFunc();
            if ( libInfo != NULL )
            {
                fPluginCount = libInfo->pluginsType.size();
                fLibLoaded = true;
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
    
    if ( !(fPluginMap.find(inType) != fPluginMap.end() ))
    {
        return fPluginMap[inType];
    }
    return NULL;
}