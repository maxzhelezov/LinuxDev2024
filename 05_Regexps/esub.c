#include "stdio.h"
#include "err.h"
#include "regex.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#define MAXGR 10

int main(int argc, char *argv[]){
    int errcode, matches_size, bagnum, start, end;
    size_t errsize, subsize, i, j, substr_filledsize;
    char *errstr = NULL, *substr_filled, prevc=0, curc= 0, *str, *regstr, *substr, *str_filled;
    regex_t regex;
    regmatch_t bags[MAXGR];

    if (argc != 4){
        errx(-1, "Неверное число параметров - %d, требуется 3 regexep substituion string", argc - 1);
    }
    regstr = argv[1];
    substr = argv[2];
    str = argv[3];
    
    errcode = regcomp(&regex, regstr, REG_EXTENDED);
    if (errcode){
        errsize = regerror(errcode, &regex, NULL, 0);
        errstr = malloc(errsize * sizeof(char));
        regerror(errcode, &regex, errstr, errsize);
        errx(-1, "%s", errstr);
    }

    if (regexec(&regex, argv[3], MAXGR, bags, 0) == REG_NOMATCH){
        /* No match, return string as it is */
        puts(argv[3]);
        return 0;
    }
    /* regexec matched something */
    subsize = strlen(substr);
    start = bags[0].rm_so;
    end = bags[0].rm_eo;
    matches_size = end - start;
    substr_filled = malloc((subsize + matches_size) * sizeof(char));

    /* prepare substring by filling references in it */
    for (i = 0, j = 0; i < subsize; i++, j++){
        curc = substr[i];
        if (i != 0 && prevc == '\\'){
            if (isdigit(curc)){
                bagnum = atoi(&curc);
                int s = bags[bagnum].rm_so, e = bags[bagnum].rm_eo;
                if (s == -1)
                    errx(-1, "Нет такого кармана \\%d", bagnum);
                strncpy(substr_filled + j - 1, str + s, e - s);
                j += e - s - 2;
            }
            if (curc == '\\'){
                /* skip this \ */
                j -= 1;
                curc = 0;
            }
            if (curc != '\\' && !isdigit(curc))
                errx(-1, "После \\ ожидался номр кармана, либо \\");
        }
        else
            substr_filled[j] = curc;
        prevc = curc;
    }
    substr_filled[j] = 0;
    substr_filledsize = j;

    str_filled = malloc((strlen(str) + substr_filledsize) * sizeof(char));
    memcpy(str_filled, str, start); 
    memcpy(str_filled + start, substr_filled, substr_filledsize); 
    memcpy(str_filled + substr_filledsize + start, str + end, strlen(str) - end); 

    puts(str_filled);

    free(str_filled);
    free(substr_filled);
    regfree(&regex);
    return 0;
}
