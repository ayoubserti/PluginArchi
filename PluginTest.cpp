/*
    Author: Ayoub Serti
    @abstract: this is a Plugin Test
*/

#include "PCHFile.h"
#include "Types.h"
#include "Plugin0.h"
#include "PluginLibrary.h"
#include <iostream>



using namespace std;

using namespace XTOOL;



extern "C"
{
    LibraryInfo*  GetLibraryInfo();
}

void CPlugin::showMessage()
{
    cout << "Sa marche" << endl;
}


CPluginImp::CPluginImp(const TPluginPath& inPath)
{
    fPath = inPath;
    fType = CPlugin::TYPE_PLUGIN;
}

CPluginImp::CPluginImp(){};
//global objects
LibraryInfo* gLibInfos;
CPluginImp* gPluginImp;

LibraryInfo*  GetLibraryInfo()
{
    
    return gLibInfos;
}

void XTOOL::PluginMain()
{ 
    cout << " From Plugin0" << endl; 
    gPluginImp = new CPluginImp();//"/home/dectroo/Test");
    gLibInfos = new LibraryInfo();
    gLibInfos->majorVersion = 0x0;
    gLibInfos->minorVersion = 0x01;
    
    gLibInfos->pluginsType.push_back(CPlugin::TYPE_PLUGIN);
    gLibInfos->plugins.push_back(gPluginImp->Retain());
}
