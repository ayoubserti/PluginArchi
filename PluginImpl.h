/*
    Author: Ayoub Serti
    License: MIT
*/

#ifndef __PLUGIN_IMPL_H__
#define __PLUGIN_IMPL_H__

#include "Types.h"


namespace XTOOL
{
    class IPlugin;
    
    struct  LibraryInfo
    {
        uLONG majorVersion;
        uLONG minorVersion;
        std::vector<TPluginType> pluginsType;
        
        std::vector<IPlugin*>    plugins;
        
    };
    
    template<class Type>  
    class PluginImpl  : public Type //public TPluginType
    {
    public:
        
        
        PluginImpl();
        virtual ~PluginImpl();
        
        
        virtual TPluginType GetPluginType();
        
        virtual TFilePath GetPluginLibraryPath();
        
        virtual Type* Retain();
        
        virtual void     Release();
        
        virtual uLONG    GetRefCount() const;
        /*
        //this class should not load any PluginLibrary, because it's the Plugin Implementation
        //and it's implemented into a sharedLibrary which is handled via PluginLibrary class 
        virtual PluginLibrary* Load (const TPluginPath& inPluginPath);
    
        virtual TError         unLoad ();
        */
    protected:

        TPluginType          fType;
        TFilePath            fPath;
        uLONG                fRefCount;
        
    };
}
#endif //__PLUGIN_IMPL_H__