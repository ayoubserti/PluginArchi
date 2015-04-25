/*
 Author: Ayoub Serti
 subject: Plugin Architucture example 
*/

#include "PCHFile.h"
#include "IPlugin.h"

using namespace XTOOL;

//ctor
template<class Type>
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

