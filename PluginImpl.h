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
    
    //implementation to deal with template link error 
    //ctor
template<typename Type>
PluginImpl<Type>::PluginImpl()
{
    
    fType = 0;
    fPath = "";
    fRefCount =1;
}
//dtor
template<class Type>
PluginImpl<Type>::~PluginImpl()
{
    
    
}
template<class Type>
TPluginType PluginImpl<Type>::GetPluginType()
{
    return Type::TYPE_PLUGIN;
}

template<class Type>
TFilePath PluginImpl<Type>::GetPluginLibraryPath()
{
    return fPath;
}

template<class Type>
Type* PluginImpl<Type>::Retain()
{
    fRefCount++;
    return this;
}

template<class Type>
void PluginImpl<Type>::Release()
{
    if (!(--fRefCount))
    {
        //no reference on this object
        delete this;
    }
}
template<class Type>
uLONG PluginImpl<Type>::GetRefCount() const
{
    //return reference count
    return fRefCount;
}


}
#endif //__PLUGIN_IMPL_H__