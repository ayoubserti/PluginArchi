/*
    Author: Serti Ayoub
    Main file; for dev testing purpose
*/
#include "PCHFile.h"
#include "PluginManager.h"
#include "Plugin0.h"
#include "Threading/threading.h"
#include "Threading/ThreadManager.h"

using namespace XTOOL;
using namespace std;

class ThreadPlg : public IThread
{
    void* OnRun()
    {
        
       if( fManager->LockSection())
       {
           printf("%p\n", fManager);  
            CPlugin* plg = dynamic_cast<CPlugin*>(PluginManager::Get().RetainPluginByType('PLG0'));
            plg->showMessage();
            printf("%p\n", plg);    
            plg->Release();
           //std::this_thread::yield();
             //std::this_thread::sleep_for(std::chrono::seconds(2));   
            PluginImpl<CPlugin>* plgIm  = reinterpret_cast<PluginImpl<CPlugin>*>(plg);
             cout << "reference " << plgIm->GetRefCount() << endl;
          fManager->UnLockSection();
       }
        
    }
};


int main()
{
   cout << PluginManager::Get().Init() << endl;
   IThread* t1 = new ThreadPlg();
   IThread* t2 = new ThreadPlg();
   XThreadManager* ThrMgr = new XThreadManager();
   t1->SetManager(ThrMgr);
   t2->SetManager(ThrMgr);
   t1->Start();
   t2->Start();
   t2->Detach();
   t1->Detach();
   /*CPlugin* plg = dynamic_cast<CPlugin*>(PluginManager::Get().RetainPluginByType('PLG0'));
   PluginImpl<CPlugin>* plgIm  = dynamic_cast<PluginImpl<CPlugin>*>(plg);
   cout << plgIm->GetRefCount() << endl;*/
   ThrMgr->Release();
   
   int a;
   cin >> a;
    
}
