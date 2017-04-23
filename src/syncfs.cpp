#include "headers/syncfs.h"
#include <iostream>
#include <string>

using namespace std;


SyncFS* SyncFS::_instance = NULL;

#define RETURN_ERRNO(x) (x) == 0 ? 0 : -errno

SyncFS* SyncFS::Instance() {
    if(_instance == NULL) {
        _instance = new SyncFS();
    }
    return _instance;
}

void SyncFS::setRootDir(const char *path) {
}

int SyncFS::Getattr(const char *path, struct stat *statbuf) {
    return 0;
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
    return 0;
}
int SyncFS::Read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {
    return 0;
}
int SyncFS::Write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {
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
    return 0;
}
int SyncFS::Readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fileInfo) {
    return 0;
}
int SyncFS::Releasedir(const char *path, struct fuse_file_info *fileInfo) {
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
