#include "stdio.h"
#include "stdlib.h"
#include "err.h"
#include "limits.h"

typedef struct {
    int start;
    int stop;
    int step;
    int count;
} range;

void argparse(int argc, char *argv[], int *start, int *stop, int *step){
    int num, errno=0;
    char *endptr;

    *start = 0;
    *step = 1;

    if ((argc >=2) && (argc <= 4)){
        num = strtol(argv[1], &endptr, 10);
        if ((errno != 0) || (endptr == argv[1]))
            errx(1, "Первый параметр - не число"); 
        *stop = num;
        
        if (argc == 2)
            return;
        
        *start = num;
        
        num = strtol(argv[2], &endptr, 10);
        if ((errno != 0) || (endptr == argv[2]))
            errx(1, "Второй параметр - не число"); 
        *stop = num;

        if (argc == 3)
            return;

        num = strtol(argv[3], &endptr, 10);
        if ((errno != 0) || (endptr == argv[3]))
            errx(1, "Третий параметр - не число"); 
        *step = num;
        return;
    }

    if (argc != 1){
        puts("Неверное количество аргументов");
    }

    puts("Программа - генератор арифметической прогрессии");
    puts("Один параметр N для последовательности [0, 1, … N-1]");
    puts("Два параметра M и N для последовательности [M, M+1, … N-1]");
    puts("Три параметра M, N и S для последовательности [M, M+S, M+2S, … N-1]"); 
    exit(0);
}

void range_init(range* iter){
    iter -> count = iter -> start;
}

int range_run(range *iter){
    return iter -> count < iter -> stop;
}

void range_next(range* iter){
    iter -> count += iter -> step;
}

int range_get(range *iter){
    return iter -> count;
}

int main(int argc, char *argv[]){
    range I;
    argparse(argc, argv, &I.start, &I.stop, &I.step);
    for(range_init(&I); range_run(&I); range_next(&I))
        printf("%d\n", range_get(&I));
    return 0;
}
