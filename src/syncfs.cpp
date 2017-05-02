#include "headers/syncfs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/xattr.h>
#include <dirent.h>
#include <errno.h>
#include <syncfs_p.hpp>

using namespace std;


SyncFS* SyncFS::_instance = NULL;

#define RETURN_ERRNO(x) (x) == 0 ? 0 : -errno

SyncFS* SyncFS::Instance() {
    if(_instance == NULL) {
        _instance = new SyncFS();
    }
    return _instance;
}

SyncFS::SyncFS() :
    d(new SyncFSPrivate())
{

}

SyncFS::~SyncFS()
{
    delete d;
}


void SyncFS::setRootDir(string path, string path2) {
    cout << "setRootDir: " << path << "\n";
    cout << "setRootDir: " << path2 << "\n";
    d->pathOrigin = path;
    d->pathTarget = path2;
    d->openLogfile("syncfsTestLog.log");
}

int SyncFS::Getattr(const char *path, struct stat *statbuf) {
    d->log("Getattr", "path: "+(string)path);
    /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
    
    /**
     * read attribute of from origin file
     */
     errno = 0;
    int res =lstat(abspath.c_str(), statbuf);
    if(res < 0)
        return -errno;
    
    return res;
}
int SyncFS::Readlink(const char *path, char *link, size_t size) {
    d->log("Readlink", "path: "+(string)path);
    /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
        
    errno = 0;
    int res =readlink(path,link,size);
    if(res < 0)
        return -errno;
    
    return res;
}
int SyncFS::Mknod(const char *path, mode_t mode, dev_t dev) {
    d->log("Mknod", "path: "+(string)path);
    /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
        
    /** 
     * if it's not a normal file which is to be created deny access
     */
    //if(dev != S_IFREG)
    //    return -EACCES;
        
    errno = 0;
    int res =mknod(abspath.c_str(), mode,dev);
    if(res < 0)
        return -errno;
        
    return res;
}
int SyncFS::Mkdir(const char *path, mode_t mode) {
    d->log("Mkdir", "path: "+(string)path);
    /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
        
    errno = 0;
    int res =mkdir(abspath.c_str(), mode);
    if(res < 0)
        return -errno;
        
    return res;
}
int SyncFS::Unlink(const char *path) {
    d->log("Unlink", "path: "+(string)path);
    /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
        
    errno = 0;
    int res =unlink(abspath.c_str());
    if(res < 0)
        return -errno;
        
    return res;
}

int SyncFS::Rmdir(const char *path) {
    d->log("", "path: "+(string)path);
    /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
        
    errno = 0;
    int res = rmdir(abspath.c_str());
    if(res < 0)
        return -errno;
        
    return res;
}
int SyncFS::Symlink(const char *path, const char *link) {
    d->log("Symlink", "path: "+(string)path);
    return -EACCES;
}
int SyncFS::Rename(const char *path, const char *newpath) {
    d->log("Rename", "path: "+(string)path);
    /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
        
    string newAbspath = d->AbsPath(path);
    if(newAbspath.length() == 0)
        return -ENOENT;
        
    errno = 0;
    int res = rename(abspath.c_str(), newAbspath.c_str());
    if(res < 0)
        return -errno;
        
    return res;
}
int SyncFS::Link(const char *path, const char *newpath) {
    d->log("Link", "path: "+(string)path);
    return -EACCES;
}
int SyncFS::Chmod(const char *path, mode_t mode) {
    d->log("Chmod", "path: "+(string)path);
    /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
        
    errno = 0;
    int res = chmod(abspath.c_str(),mode);
    if(res < 0)
        return -errno;
        
    return res;
}
int SyncFS::Chown(const char *path, uid_t uid, gid_t gid) {
    d->log("Chown", "path: "+(string)path);
    /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
        
    errno = 0;
    int res = chown(abspath.c_str(), uid, gid);
    if(res < 0)
        return -errno;
        
    return res;
}
int SyncFS::Truncate(const char *path, off_t newSize) {
    d->log("Truncate", "path: "+(string)path);
    /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
        
    errno = 0;
    int res = truncate(abspath.c_str(), newSize);
    if(res < 0)
        return -errno;
        
    return res;
}
int SyncFS::Utime(const char *path, struct utimbuf *ubuf) {
    d->log("Utime", "path: "+(string)path);
    return 0;
}
int SyncFS::Open(const char *path, struct fuse_file_info *fileInfo) {
    d->log("Open", "path: "+(string)path);
    /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
    
    d->log("Open", "fullpath: "+abspath);
    
    errno = 0;
    int ret = open(abspath.c_str(), fileInfo->flags);
    if(ret < 0)
        return -errno;
    
    fileInfo->fh = ret;
    d->log("Open", "fh: "+to_string(fileInfo->fh));
    
    return 0;
}
int SyncFS::Read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {
    d->log("Read", "path: "+(string)path);
    errno = 0;
    int ret = pread(fileInfo->fh, buf, size, offset);
    
    if(ret < 0)
        return -errno;
    return ret;
}
int SyncFS::Write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {
    d->log("Write", "path: "+(string)path);
    errno = 0;
    int ret = pwrite(fileInfo->fh, buf, size, offset);
    if(ret < 0)
        return -errno;
    return ret;
}
int SyncFS::Statfs(const char *path, struct statvfs *statInfo) {
    d->log("Statfs", "path: "+(string)path);
    /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
        
    errno = 0;
    int res =  statvfs(abspath.c_str(), statInfo);
    if(res < 0)
        return -errno;
        
    return res;
}
int SyncFS::Flush(const char *path, struct fuse_file_info *fileInfo) {
    d->log("Flush", "path: "+(string)path);
    return 0;
}
int SyncFS::Release(const char *path, struct fuse_file_info *fileInfo) {
    d->log("Release", "path: "+(string)path);
    errno = 0;
    int res = close(fileInfo->fh);
     if(res < 0)
        return -errno;
        
    return res;
}
int SyncFS::Fsync(const char *path, int datasync, struct fuse_file_info *fi) {
    d->log("Fsync", "path: "+(string)path);
    return 0;
}
int SyncFS::Setxattr(const char *path, const char *name, const char *value, size_t size, int flags) {
    d->log("Setxattr", "path: "+(string)path);
   /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
        
    errno = 0;
    int res =  setxattr(abspath.c_str(), name, value, size,flags);
    if(res < 0)
        return -errno;
        
    return res;
}
int SyncFS::Getxattr(const char *path, const char *name, char *value, size_t size) {
    d->log("Getxattr", "path: "+(string)path);
     /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
        
    errno = 0;
    int res =  getxattr(abspath.c_str(), name, value, size);
    if(res < 0)
        return -errno;
        
    return res;
}
int SyncFS::Listxattr(const char *path, char *list, size_t size) {
    d->log("Listxattr", "path: "+(string)path);
    /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
        
    errno = 0;
    int res = listxattr(abspath.c_str(), list, size);
    if(res < 0)
        return -errno;
        
    return res;
}
int SyncFS::Removexattr(const char *path, const char *name) {
    d->log("Removexattr", "path: "+(string)path);
    /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
        
    errno = 0;
    int res = removexattr(abspath.c_str(), name);
    if(res < 0)
        return -errno;
        
    return res;
}
int SyncFS::Opendir(const char *path, struct fuse_file_info *fileInfo) {
    d->log("Opendir", "path: "+(string)path);
    /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
    
    errno = 0;
    
    DIR *dir = opendir(abspath.c_str());
	fileInfo->fh = (uint64_t)dir;
	return NULL == dir ? -errno : 0;
}
int SyncFS::Readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fileInfo) {
    d->log("Readdir", "path: "+(string)path);
    /**
     * read contents of directory in path  push list back to filler
     */
    DIR *dir = (DIR*)fileInfo->fh;
    dirent *entr = NULL;
    errno = 0;
    while((entr = readdir(dir)) != NULL)
    {
        if(filler(buf,entr->d_name, NULL,0)!=0)
            return -ENOMEM;
    }
    
    if(errno != 0)
        return -errno;
    
    return 0;
}
int SyncFS::Releasedir(const char *path, struct fuse_file_info *fileInfo) {
    d->log("Releasedir", "path: "+(string)path);
    DIR *dir = (DIR*)fileInfo->fh;
    closedir(dir);
    return 0;
}
int SyncFS::Fsyncdir(const char *path, int datasync, struct fuse_file_info *fileInfo) {
    d->log("Fsyncdir", "path: "+(string)path);
    return 0;
}
int SyncFS::Init(struct fuse_conn_info *conn) {
    d->log("Init", " ... ");
    return 0;
}
int SyncFS::Truncate(const char *path, off_t offset, struct fuse_file_info *fileInfo) {
    d->log("Truncate", "path: "+(string)path);
    return 0;
}
