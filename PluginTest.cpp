/*
    Author: Ayoub Serti
    @abstract: this is a Plugin Test
*/

#include "PCHFile.h"
#include "Types.h"
#include "IPlugin.h"
#include "PluginImpl.h"
#include "PluginLibrary.h"
#include <iostream>


using namespace XTOOL;
using namespace std;

extern "C"
{
    LibraryInfo*  GetLibraryInfo();
}

class CPlugin : public IPlugin
{
    public:
    enum {
        TYPE_PLUGIN = 'PLG0'
    };
    
   /* TPluginType GetPluginType()
    {
        return TYPE_PLUGIN;
    }*/
    
    void showMessage()
    {
        cout << "Sa marche" << endl;
    }
    
};

class CPluginImp : public PluginImpl<CPlugin>
{
    public:
    CPluginImp(const TPluginPath& inPath)
    {
        fPath = inPath;
        fType = CPlugin::TYPE_PLUGIN;
    }
};

//global objects
LibraryInfo* gLibInfos;
CPluginImp* gPluginImp;

LibraryInfo*  GetLibraryInfo()
{
    
    return gLibInfos;
}

void PluginMain()
{
    gPluginImp = new CPluginImp("/home/dectroo/Test");
    gLibInfos = new LibraryInfo();
    gLibInfos->majorVersion = 0x0;
    gLibInfos->minorVersion = 0x01;
    
    gLibInfos->pluginsType.push_back(CPlugin::TYPE_PLUGIN);
    gLibInfos->plugins.push_back(gPluginImp->Retain());
}
