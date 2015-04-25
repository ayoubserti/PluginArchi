#include "RefManaged.h"
#include <stdio.h>
using namespace XTOOL;
class Test : public RefManaged
{};

int main()
{
    Test* mytest = new Test();
    
    RetainManagedRef(mytest);
    RetainManagedRef(mytest);
    RetainManagedRef(mytest);
    delete mytest;
    printf ("%p",mytest);
    fflush(stdout);
    RetainManagedRef(mytest);
    
    long a = ReleaseManagedRef(mytest);
    printf ("%d",a);
    return 0;
}