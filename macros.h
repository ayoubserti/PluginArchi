#ifndef __MACROS_H__
#define __MACROS_H__


#if defined(_MSC_VER)
    //  Microsoft 
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#elif defined(_GCC) || defined(__GNUC__)
    //  GCC
    #define EXPORT __attribute__((visibility("default")))
    #define IMPORT
    #pragma warning("compile using GCC")
    
#else
   //unknown compiler
   #define EXPORT 
   #define IMPORT 
   #pragma warning ("would you realy compile this machin !!!")
   #error  "could notCompile"
#endif


#define PUBLIC_API EXPORT 

#endif