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
    
    
    class IPlugin 
    {
        public:
        
            virtual TPluginType GetPluginType()         =0;
        
            virtual TFilePath   GetPluginLibraryPath()  =0;
            
            virtual IPlugin* Retain()                   =0;
            
            virtual void Release()                      =0;
            
            enum { TYPE_PLUGIN = 0x3F3F3F3F}; //'????' =  0x3F3F3F3F
            

    };

    
}//namespace XTOOL


#endif //__I_PLUGIN_H__