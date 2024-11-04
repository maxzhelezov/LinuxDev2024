#include <unistd.h>
#include <dlfcn.h>
#include <string.h>
#include <errno.h>

typedef int (*unlink_type)(const char *);

int unlink(const char *pathname){
    unlink_type real_unlink = (unlink_type)(dlsym(RTLD_NEXT, "unlink"));
    char *res = strstr(pathname, "PROTECT");
    if (res == NULL)
        return real_unlink(pathname);
    errno = 38;   
    return -1;
}
