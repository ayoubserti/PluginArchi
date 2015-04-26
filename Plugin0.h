#ifndef __PLUGIN_0_H__
#define __PLUGIN_0_H__


#include "PluginImpl.h"
#include "IPlugin.h"


namespace XTOOL
{
class CPlugin : public XTOOL::IPlugin
{
    public:
    enum {
        TYPE_PLUGIN = 'PLG0'
    };
    
    
    void showMessage();
    
};


class CPluginImp : public PluginImpl<CPlugin>
{
    public:
    CPluginImp();
    CPluginImp(const TPluginPath& inPath);
};

}

#endif 