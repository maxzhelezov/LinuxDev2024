#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

int read_file(FILE *fp, char ***strings){
    int nlen = 0, c = 0, i, nchars;
    size_t n;
    char *temp = NULL;
    while ((c = getc(fp)) != EOF){
        if (c == '\n')
            nlen++;
    }
    
    *strings = calloc(nlen, sizeof(char*));
    
    rewind(fp);
    for (i = 0; i < nlen; i++){
        nchars = getline(&temp, &n, fp);
        /* remove trailing \n */
        temp[nchars - 1] = 0;
        (*strings)[i] = temp;
        temp = NULL;
        n = 0;
    }

    return nlen;
}

int get_int_len(int c){
    int n = 0;
    while (c != 0){
        n++;
        c = c / 10;
    }
    return n;
}

int main(int argc, char *argv[]){
    WINDOW *win;
    int c = 0, maxy, maxx, wmaxx, wmaxy, dx = 3, nlen = 0, idx_file, idx_win,
        cur_line = 0, i, offset_pos=0, max_int_len;
    FILE *fp;
    char **strings;

    if (argc != 2){
        fprintf(stderr, "Specify file as the second argument\n");
        return 1;
    }

    if ((fp = fopen(argv[1], "r")) == NULL){
        fprintf(stderr, "Cannot open file\n");
        return 1;
    }

    nlen = read_file(fp, &strings);
    fclose(fp);

    initscr();
    noecho();
    cbreak();
    printw("File: %s, lines: %d", argv[1], nlen);
    refresh();

    getmaxyx(stdscr, maxy, maxx);
    win = newwin(maxy - 2*dx, maxx-2*dx, dx, dx);
    getmaxyx(win, wmaxy, wmaxx);
    keypad(stdscr, TRUE);
    scrollok(win, TRUE);

    do {
        switch (c){
            case ' ':
                cur_line++;
                break;
            case KEY_LEFT:
                offset_pos--;
                break;
            case KEY_RIGHT:
                offset_pos++;
                break;
            case KEY_DOWN:
                cur_line++;
                break;
            case KEY_UP:
                cur_line--;
                break;
            case KEY_NPAGE:
                cur_line += wmaxy - 2;
                break;
            case KEY_PPAGE:
                cur_line -= wmaxy - 2;
                break;
            case 0:
                break;
        }
        if (cur_line < 0)
            cur_line = 0;
        if (offset_pos < 0)
            offset_pos = 0;

        werase(win);
        box(win, 0, 0);
        
        /* getting size of positions that possible last line number will take */
        max_int_len = get_int_len(cur_line + wmaxy - 2);
        for (idx_file = cur_line, idx_win = 0;
                (idx_win < wmaxy - 2) && (idx_file < nlen); idx_file++, idx_win++)
            mvwprintw(win, idx_win + 1, 1, "%d: %.*s", idx_file + 1,
                    wmaxx - 4 - max_int_len, &(strings[idx_file])[offset_pos]);
        wrefresh(win);
    } while ((c = getch()) != 27);

    for (i = 0; i < nlen; i++){
        free(strings[i]);
    }
    free(strings);
    
    endwin();
    return 0;
}
