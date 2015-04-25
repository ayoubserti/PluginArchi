/*
 Author: Ayoub Serti
 subject: Plugin Architucture example 
*/

#ifndef __PLUGIN_MANAGER_H__
#define __PLUGIN_MANAGER_H__

#include "Types.h"



namespace XTOOL 
{
    class IPlugin;
    class PluginLibrary;
    /*
      
      PluginManager allows register, unregister, load, unload and scan plugins in a specific directory
      
      PluginManager is a singleton class
    */
    class PluginManager
    {
        public:
        
         /*
            @function Get 
            @abstact  
            
            @params void
            @return PluginManager reference 
            
        */
        
        static PluginManager& Get(void);
        
        /*
         @function Init 
         @abstract initialize PluginManager
         @discuss  Init try scan Plugins Lib Folder and registe all found plugins
         @params void
         @return ERR_OK if it's OK else an error code
        */
        
        TError Init(void);
        /*
            @function RegisterPlugin 
            @abstact  register a plugin by its library path, return Err_OK if OK else an error code 
            
            @params inPluginPath Path of the plugin library
            @return error value 
            @TODO: specify error list with its meanings
        */
        TError RegisterPlugin (const TFilePath& inPluginPath);
         
        
        /*
            @function UnRegisterPlugin 
            @abstact  unregister a plugin by its library path, return Err_OK if OK else an error code 
            
            @params inPluginPath Path of the plugin library
            @return error value 
            @TODO: specify error list with its meanings
        */
        TError UnRegisterPlugin  (const TFilePath& inPluginPath  );
        
        /*
            @function UnRegisterPluginByName
            @abstact  unregister a plugin by it  Name, return Err_OK if OK else an error code 
            
            @params inPluginName Name of the plugin
            @return error value 
            @TODO: specify error list with its meanings
                   may be this function unuseful
        */
        static TError UnRegisterPluginByName  (const TString& inPluginName    );
        
        /*
            @function UnRegisterPluginByType
            @abstact  unregister a plugin by it Type, return Err_OK if OK else an error code 
            @discuss: every plugin have a type which is a unsigned long (ex: 'PLG0')
            @params inPluginType Path of the plugin library
            @return error value 
            @TODO: specify error list with its meanings
        */
        static TError UnRegisterPluginByType  (TPluginType inPluginType);
        
        /*
            @function LoadPluginLibrary 
            @abstact  unregister a plugin by it Type, return Err_OK if OK else an error code 
            @discuss: every plugin have a type which is a unsigned long (ex: 'PLG0')
            @params inPluginType Path of the plugin library
            @return error value 
        */
        
        static PluginLibrary* LoadPluginLibrary (const TString& inPluginPath) ;
        
        
    private:
        
        std::map<TPluginType,IPlugin*> sPluginMap;
        std::vector<PluginLibrary*>    sLibraries;
        //for memory effeciency, we did not Create/Load plugin at init time, we just pick up there types
        // when user ask for plugin, PMgr load it and mark it as loaded in sCondidatePluginType
        std::map<TPluginType,bool>     sCondidatePluginType;
        static PluginManager*                 sInstance;
        static TDirPath                       sPluginsDir;
        
        //private ctor
        PluginManager();
        
        //scan Plugins  in a specific dir
        /*
        @function ScanPlugins
        @abstact scan inDirPlugins for plugin to register
        @discuss this made static so nobody can scan plugins at/in an unappropriate moment/directory 
        @params inDirPlugins directory from which scan libraries and get 
        @return void
        */
        void ScanPlugins (const TDirPath& inDirPlugins );
        
         
        
        
    };
}//namespace XTOOL


#endif
