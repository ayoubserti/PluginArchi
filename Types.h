/*
 Author: Ayoub Serti
 subject: Plugin Architucture example 
*/

#ifndef  __TYPES_H__
#define  __TYPES_H__

/*
    File: Types.h
    abstract: contains all types
*/
#ifndef NULL
#define NULL 0
#endif

#ifndef ERR_OK
#define ERR_OK 0 
#endif
namespace XTOOL
{
    typedef unsigned long TError;
    typedef unsigned long TPluginType;
    typedef unsigned long uLONG;
    typedef std::string   TString;
    typedef TString       TFilePath;
    typedef TString       TDirPath;
    typedef TString       TPluginPath;
    
    
}


#endif  //__TYPES_H__
