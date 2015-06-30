/*
 Author: Ayoub Serti
 subject: FileSystem API
*/


#ifndef __X_FILE_H__
#define __X_FILE_H__

//> TODO: manage Headers
#include "Types.h"
#include "RefManaged.h"


/*
    Discussion:
        this implemtention is only POSIX-system 
*/

#if !defined(_GCC) || !defined(__GNUC__)
#error "Only GCC compiled source"
#endif

namespace XTOOL
{

    //foreword declaration
    class XFile;
    
    /*
      @class XFileIterator
      @abstract a custom  output iterator
      
    */
    class XFileIterator: public std::iterator<std::output_iterator_tag, XFile*>
    {
        // no nead to override std::iterator functions because we manipulate only pointers (i.e XFile*)
    };
    
    /*
        XFolder class representing directory in FileSystem
    */
    class XFolder final : public RefManaged
    {
    public:
        typedef XFileIterator iterator;
        typedef std::vector<XFile*> XFiles;
        typedef std::vector<XFolder*> XFolders;
        
        //default ctor
        XFolder();
        // construct from a Dir Path roots
        XFolder(const TDirPath& inDirPath);
        ~XFolder();
        
        iterator    firstFile() ;
        iterator    end() ;
        
        std::vector<TString>  GetFilesNames();
        std::vector<TString>  GetFoldersNames();
    
    private:
        
        XFiles      fFiles;
        XFolders    fFolders;
        
    };
    
    class XFile : public RefManaged
    {
    public:
        XFile();
        ~XFile();
        
        inline TString GetFilePath(){return fPath;}
        inline TString GetFileName(){return fName;}
    private:
       
       XFolder* fParentFolder;
       TString  fPath;
       TString  fName;
    };

}
#endif //__X_FILE_H__