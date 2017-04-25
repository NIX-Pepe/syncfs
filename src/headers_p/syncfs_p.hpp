#ifndef syncfs_p_H
#define syncfs_p_H

#include <string>
#include <boost/shared_ptr.hpp> 
#include <map>

using namespace std;

class SyncFSPrivate
{
public:
    shared_ptr<map<string,int> > filesOrigin;
    shared_ptr<map<string,int> > filesTarget;
    bool isMirrorActive = false;
    string pathOrigin;
    string pathTarget;
    
    void AbsPath(string *dest, const string path){
        if(path.length() + pathOrigin.length() < PATH_MAX)
        {
            *dest = pathOrigin + path;
        }else{
            dest = NULL;
        }
    };
    void loadFileVersions() {};
    
    SyncFSPrivate() {
        const shared_ptr<map<string,int> > o(new map<string,int>());
        const shared_ptr<map<string,int> > t(new map<string,int>());
        filesOrigin = o;
        filesTarget = t;
    };
};


#endif //syncfs_p_H

