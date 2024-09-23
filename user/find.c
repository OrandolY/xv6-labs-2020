#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

/*
    将路径格式化为文件名
*/
char* fmt_name(char *path){
    static char buf[DIRSIZ+1];
    char *p;

    //Find first character after last slash
    for(p = path+strlen(path); p >= path && *p != '/'; p--);
    p++;
    memmove(buf, p, strlen(p) + 1);
    return buf;
}

/*
    系统文件名与要查找的文件名，若一致，打印系统文件完整路径
*/