/*
 Author: Ayoub Serti
 subject: Plugin Architucture example 
*/

#ifndef __PLUGIN_LIBRARY_H__
#define __PLUGIN_LIBRARY_H__

#include "Types.h"



namespace XTOOL
{
    class IPlugin;
    /*
     PluginLibrary is a Wrap of dlfnct 
     Windows must re-implent this class
    */
    struct  LibraryInfo
    {
        uLONG majorVersion;
        uLONG minorVersion;
        std::vector<TPluginType> pluginsType;
    };
    
    
    class PluginLibrary
    {
    public:
       
        typedef  LibraryInfo* (*GetLibraryInfoFunc)(void);
        
        explicit PluginLibrary(const TFilePath& inLibraryPath);
        
        virtual ~PluginLibrary();
        
        virtual TError LoadFromFile();
        
        virtual TError UnLoad();
        
        virtual uLONG  CountPlugins();
        
        virtual PluginLibrary* Retain();
        
        virtual void           Release();
        
        virtual IPlugin*       RetainPluginByType(TPluginType inType);
        
        virtual TError         GetPluginsTypes(std::vector<TPluginType> outTypes);
        
        
    protected:
        
        typedef std::map<TPluginType,IPlugin*> TPluginMap;
        
        TFilePath    fLibraryPath;
        uLONG        fPluginCount;
        TPluginMap   fPluginMap;
        uLONG           fRefCount;
        
    
    private:
         
        PluginLibrary(); //private constructor
       
        typedef void*   TLibHandle;
        TLibHandle      fLibHandle;
        bool            fLibLoaded;
        LibraryInfo*    fLibInfos;
        std::vector<TPluginType>  fPluginTypes;
        
        
    };
}


#endif //__PLUGIN_LIBRARY_H__