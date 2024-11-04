#include "stdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "fcntl.h"
#include "err.h"
#include "errno.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

#define BUF_SIZE 65536

enum errors {EWRONGARGUMENTCOUNT=1, EINFILEOPEN, EOUTFILEOPEN, ETMPFILEOPENERR,
    EREADFILE, EWRITEFILE, ERENAME, ECLOSE, EUNLINK};

int main(int argc, char *argv[]){
    int fdin, fdtemp;
    ssize_t bytes_read, bytes_written;
    char buf[BUF_SIZE];
    char tmpname[] = "/tmp/tempfile-XXXXXX";

    if (argc != 3)
        errx(EWRONGARGUMENTCOUNT, "Wrong amount of arguments - provide infile and outfile");

    if ((fdin = open(argv[1], O_RDONLY)) == -1){
        errx(EINFILEOPEN, "failed to open infile %s: %s", argv[1], strerror(errno));
    }
    
    if ((fdtemp = mkstemp(tmpname)) == -1){
        close(fdin);
        errx(ETMPFILEOPENERR, "failed to create tempfile name: %s", strerror(errno));
    }

    while ((bytes_read = read(fdin, &buf, BUF_SIZE))){
        if (bytes_read == -1){
            close(fdin);
            close(fdtemp);
            unlink(tmpname);
            errx(EREADFILE, "failed to read infile %s: %s", argv[1], strerror(errno));
        }

        if ((bytes_written = write(fdtemp, &buf, bytes_read)) == -1){
            close(fdin);
            close(fdtemp);
            unlink(tmpname);
            errx(EWRITEFILE, "failed to write to tempfile: %s", strerror(errno));
        }
    }

    if ((close(fdin) == -1)){
        close(fdtemp);
        unlink(tmpname);
        errx(ECLOSE, "failed to close file %s: %s", argv[1], strerror(errno));

    }

    if ((rename(tmpname, argv[2]) == -1)){
        close(fdtemp);
        unlink(tmpname);
        errx(ERENAME, "failed to rename tempfile to outfile: %s", strerror(errno));
    }

    if ((close(fdtemp) == -1)){
        errx(ECLOSE, "failed to close tempfile: %s", strerror(errno));
    }

    if ((unlink(argv[1]) == -1)){
        errx(EUNLINK, "failed to delete infile %s: %s", argv[1], strerror(errno));
    }

    return 0;
}










