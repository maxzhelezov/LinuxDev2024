#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <libintl.h>
#include <locale.h>
#include <wchar.h>
#include "config.h"

#define _(STRING) gettext(STRING)

int main(){\
    int left = 1, right = 100, middle, ret_code;
    wchar_t wanswer[2] = {'\0', '\0'};
    char answer[10];
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALE_PATH);
    textdomain(PACKAGE);
    printf(_("Pick a number between 1 and 100\n"));
    
    for(;;){
        middle = (right - left) / 2 + left;
        printf(_("Is number bigger %d, y/n?\n"), middle);
        ret_code = wscanf(L" %lc", &wanswer[0]);
        if (ret_code == EOF){
            exit(0);
        }
        if (ret_code == 0){
            printf(_("Repeat your answer\n"));
            continue;
        }
        if (ret_code == 1){
            wcstombs(answer, wanswer, 10);
            if (!strcmp(answer, _("y"))){
                left = middle;
                if ((right - left) == 1){
                    printf(_("Your number is %d\n"), right);
                    exit(0);
                }
                continue;
            }
            if (!strcmp(answer, _("n"))){
                right = middle;
                if ((right - left) == 1){
                    printf(_("Your number is %d\n"), middle);
                    exit(0);
                }
                continue;
            }
            printf(_("Repeat your answer\n"));
            for (;;){
                ret_code = wscanf(L"%lc", &wanswer[0]);
                if (wanswer[0] == L'\n')
                    break;
            }
        }

    }
}