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
    IPlugin* plg = PluginManager::Get().RetainPluginByType('PLG0');
    
    printf("%p\n", plg);
    
    
}
