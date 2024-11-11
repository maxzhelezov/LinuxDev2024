#include <stdio.h>
#include <aio.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "rhash.h"
#include "config.h"

#ifdef HAVE_LIBREADLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

int main(){
    ssize_t sym_read = 0;
    size_t n;
    int upper = 0, alg = -1, res;
    int algs[] = {RHASH_MD5, RHASH_SHA1, RHASH_TTH};
    char * line = NULL, *arg1, *arg2;
    unsigned char digest[64];
    char output[130];

    rhash_library_init();

    #ifdef HAVE_LIBREADLINE
    while ((line = readline("")) != NULL)
    #endif
    #ifndef HAVE_LIBREADLINE
    while ((sym_read = getline(&line, &n, stdin)) > 0)
    #endif
    {
        #ifndef HAVE_LIBREADLINE
        line[strlen(line) - 1] = '\0';
        #endif

        upper = 0;
        alg = -1;
        arg1 = strtok(line, " ");

        if (arg1 == NULL){
            puts("not enough arguments");
            continue;
        }

        arg2 = strtok(NULL, " ");
        
        if (arg2 == NULL){
            puts("not enough arguments");
            continue;
        }
        
        upper = isupper(arg1[0]);

        for(size_t i = 0; i < strlen(arg1); i++){
            arg1[i] = tolower(arg1[i]);
        }

        if (strcmp(arg1, "md5") == 0)
            alg = 0;
        if (strcmp(arg1, "sha1") == 0)
            alg = 1;
        if (strcmp(arg1, "tth") == 0)
            alg = 2;

        if (alg < 0){
            puts("unknown algorithm");
            continue;
        }
        
        if (arg2[0] == '"'){
            int l = strlen(arg2);
            res = rhash_msg(algs[alg], arg2, strlen(arg2), digest);
        }
        else{
            res = rhash_file(algs[alg], arg2, digest);
        }

        if(res < 0) {
            fprintf(stderr, "LibRHash error: %s\n", strerror(errno));
            continue;
        }

        if (upper)
            rhash_print_bytes(output, digest, rhash_get_digest_size(algs[alg]),(RHPR_HEX | RHPR_UPPERCASE));
        else
            rhash_print_bytes(output, digest, rhash_get_digest_size(algs[alg]),(RHPR_BASE64 | RHPR_UPPERCASE));
        
        puts(output);
        free(line);
    }
    if ((sym_read < 0) & (errno > 0)){
        free(line);
        errx(1, "failed to read line: %s", strerror(errno));
    }
}