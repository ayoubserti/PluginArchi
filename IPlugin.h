/*
 Author: Ayoub Serti
 subject: Plugin Architucture example 
*/

#ifndef __I_PLUGIN_H__
#define __I_PLUGIN_H__

#include "macros.h"
#include "Types.h"

namespace XTOOL
{
    
    /*
        IPlugin is an interface for implementing plug-in 
        every new plugin must inheritent/implement this interface
    */
    
    //PluginLibrary foreword declaration
    class PluginLibrary;
    
    class IPlugin 
    {
        public:
        
            virtual TPluginType GetPluginType()         =0;
        
            virtual TFilePath   GetPluginLibraryPath()  =0;
            
            virtual IPlugin* Retain()                   =0;
            
            virtual void Release()                      =0;
            
            enum { TYPE_PLUGIN = 0x3F3F3F3F}; //'????' =  0x3F3F3F3F
            

    };
    
    template<class Type>  
    class PUBLIC_API PluginImpl  : public Type //public TPluginType
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
    private:

        TPluginType          fType;
        TFilePath            fPath;
        uLONG                fRefCount;
        
        
    };
    
    
}//namespace XTOOL


#endif //__I_PLUGIN_H__