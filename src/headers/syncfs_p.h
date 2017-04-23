#ifndef syncfs_p_H
#define syncfs_p_H

#include <iostream>
#include <string>
using namespace std;

class SyncFSPrivate
{
public:
    void doFoo();
    double doBar(bool really, int howMuch);
    int number;
protected:
    void onUpdate();
    string name;
private:
    float variable;
};


#endif //syncfs_p_H

