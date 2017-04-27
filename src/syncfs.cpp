#include "headers/syncfs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
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
}

int SyncFS::Getattr(const char *path, struct stat *statbuf) {
    
    /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    cout << "Getattr: " << abspath << "\n";
    if(abspath.length() == 0)
        return -ENOENT;
    
    /**
     * read attribute of from origin file
     */
    return stat(abspath.c_str(), statbuf);
}
int SyncFS::Readlink(const char *path, char *link, size_t size) {
    return 0;
}
int SyncFS::Mknod(const char *path, mode_t mode, dev_t dev) {
    return 0;
}
int SyncFS::Mkdir(const char *path, mode_t mode) {
    return 0;
}
int SyncFS::Unlink(const char *path) {
    return 0;
}
int SyncFS::Rmdir(const char *path) {
    return 0;
}
int SyncFS::Symlink(const char *path, const char *link) {
    return 0;
}
int SyncFS::Rename(const char *path, const char *newpath) {
    return 0;
}
int SyncFS::Link(const char *path, const char *newpath) {
    return 0;
}
int SyncFS::Chmod(const char *path, mode_t mode) {
    return 0;
}
int SyncFS::Chown(const char *path, uid_t uid, gid_t gid) {
    return 0;
}
int SyncFS::Truncate(const char *path, off_t newSize) {
    return 0;
}
int SyncFS::Utime(const char *path, struct utimbuf *ubuf) {
    return 0;
}
int SyncFS::Open(const char *path, struct fuse_file_info *fileInfo) {
    /**
     * check if path length isn't exceeding maximum and complement prefix
     */
    string abspath = d->AbsPath(path);
    if(abspath.length() == 0)
        return -ENOENT;
    
    fileInfo->fh = (abspath.c_str(), fileInfo->flags);
    return 0;
}
int SyncFS::Read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {
    int err = pread(fileInfo->fh, buf, size, offset);
    if(err > 0)
        return -err;
    return 0;
}
int SyncFS::Write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {
    int err = pwrite(fileInfo->fh, buf, size, offset);
    if(err > 0)
        return -err;
    return 0;
}
int SyncFS::Statfs(const char *path, struct statvfs *statInfo) {
    return 0;
}
int SyncFS::Flush(const char *path, struct fuse_file_info *fileInfo) {
    return 0;
}
int SyncFS::Release(const char *path, struct fuse_file_info *fileInfo) {
    return 0;
}
int SyncFS::Fsync(const char *path, int datasync, struct fuse_file_info *fi) {
    return 0;
}
int SyncFS::Setxattr(const char *path, const char *name, const char *value, size_t size, int flags) {
    return 0;
}
int SyncFS::Getxattr(const char *path, const char *name, char *value, size_t size) {
    return 0;
}
int SyncFS::Listxattr(const char *path, char *list, size_t size) {
    return 0;
}
int SyncFS::Removexattr(const char *path, const char *name) {
    return 0;
}
int SyncFS::Opendir(const char *path, struct fuse_file_info *fileInfo) {
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
    DIR *dir = (DIR*)fileInfo->fh;
    closedir(dir);
    return 0;
}
int SyncFS::Fsyncdir(const char *path, int datasync, struct fuse_file_info *fileInfo) {
    return 0;
}
int SyncFS::Init(struct fuse_conn_info *conn) {
    return 0;
}
int SyncFS::Truncate(const char *path, off_t offset, struct fuse_file_info *fileInfo) {
    return 0;
}
