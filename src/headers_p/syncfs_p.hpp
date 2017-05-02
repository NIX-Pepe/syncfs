#ifndef syncfs_p_H
#define syncfs_p_H

#include <string>
#include <boost/shared_ptr.hpp> 
#include <map>
#include <ostream>
#include <fstream>

using namespace std;

class SyncFSPrivate
{
public:
    shared_ptr<map<string,int> > filesOrigin;
    shared_ptr<map<string,int> > filesTarget;
    bool isMirrorActive = false;
    string pathOrigin;
    string pathTarget;
    filebuf logFileBuf;
    ostream logFileStream;
    
    int openLogfile(const string path)
    {
        // firs open filebuffer 
        logFileBuf.open(path, ios::out);
        // and pass it to ostream for logging
        logFileStream.rdbuf(&logFileBuf);
        return 0;
    };
    
    /**
     * Log passed message to logfile 
     */
    void log(string functionName, string msg)
    {
        logFileStream << functionName << ": " << msg << "\n";
        logFileStream.flush();
    };
    
    /**
     * Return absolute path for origin filesystem.
     */
    string AbsPath(const string path){
        if(path.length() + pathOrigin.length() < PATH_MAX)
        {
            return pathOrigin + path;
        }else{
            return "";
        }
    };
    
    /**
     * Return absolute path for target filesystem
     */
    string AbsPathTarget(const string path){
        if(path.length() + pathTarget.length() < PATH_MAX)
        {
            return pathTarget + path;
        }else{
            return "";
        }
    };
    
    void loadFileVersions() {};
    
    SyncFSPrivate() : logFileStream(NULL) {
        const shared_ptr<map<string,int> > o(new map<string,int>());
        const shared_ptr<map<string,int> > t(new map<string,int>());
        filesOrigin = o;
        filesTarget = t;
    };
    
    ~SyncFSPrivate() {
        if(logFileBuf.is_open())
        {
            logFileBuf.close();
        }
    }
};


#endif //syncfs_p_H

