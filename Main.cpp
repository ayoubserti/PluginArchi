/*
    Author: Serti Ayoub
    Main file; for dev testing purpose
*/
#include "PCHFile.h"
#include "PluginManager.h"
#include "Plugin0.h"
#include <iostream>

using namespace XTOOL;
using namespace std;

int main()
{
   // PluginManager::Get().RegisterPlugin("");
    cout << PluginManager::Get().Init() << endl;
    CPlugin* plg = dynamic_cast<CPlugin*>(PluginManager::Get().RetainPluginByType('PLG0'));
    plg->showMessage();
    printf("%p\n", plg);
    
    
}
