/*
    Author: Ayoub Serti
    version 0.1
*/

#ifndef __REF_MANAGED_H__
#define __REF_MANAGED_H__

namespace XTOOL 
{
     /*
       #discussion
            -RefManaged is a class for retaining and releasing easly class instance whitout worries 
            of class specification
            -All implementation is done here
    */
    class RefManaged 
    {
        public:
        
        RefManaged(){
            fRefCount =1;
        };
        virtual ~RefManaged()
        {
            ;
        }
        
        /*final function (not allowed to be overloaded)*/
        RefManaged* Retain()
        {
            fRefCount++;
            return this;
        }
        
        void Release()
        {
            if (!(--fRefCount))
                delete this;
        }
        
    protected:
         unsigned long fRefCount;
    private:
        template<typename T>
        friend T* XTOOL::RetainManagedRef(T* inReference);
        
        template<typename T>
        friend unsigned long  XTOOL::ReleaseManagedRef(T* &inReference);
        
    };
    
    template<typename T>
    T* RetainManagedRef(T* inReference)
    {
        if (!inReference) return 0;
        return dynamic_cast<T*>(inReference->Retain());
    }
    
    template<typename T>
    unsigned long ReleaseManagedRef(T* &inReference)
    {
        if ( inReference)
        {
            unsigned long refCount = inReference->fRefCount;
            inReference->Release();
            inReference=0; //make it NULL
            return refCount -1 ;
        }
        else 
        {
            return 0;
        }
        
    }
    
}//namespace XTOOL

#endif //__REF_MANAGED_H__
