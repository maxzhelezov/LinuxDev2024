#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

// DWall - destructable wall (edges)
// IWall - indestructable wall
typedef enum wall_type {None = 0, Room, DWall, IWall, Empty} tile;
// visualization for each wall type
char sym_vis[] = {'-', '.', '#', '#', '.'};

tile** init_lab(int num_rooms) {
    int i, j, lab_size = num_rooms * 2 + 1;
    tile **lab = malloc(lab_size * sizeof(tile*));
    for(i = 0; i < lab_size; i++) {
        lab[i] = malloc(lab_size * sizeof(tile));
        for(j = 0; j < lab_size; j++) {
            if (((j % 2 == 0) && (i % 2 == 0)) || (i == 0) ||
                    (i == 2 * num_rooms) || (j == 0) || (j == 2 * num_rooms)) {
                lab[i][j] = IWall;
                continue;
            }
            if ((j % 2 == 1) && (i % 2 == 1)) {
                lab[i][j] = Room;
                continue;
            }
            lab[i][j] = DWall;
        }
    }
    return lab;
}


int direction_x[] = {0, 1, -1,  0};
int direction_y[] = {1, 0,  0, -1};
void generate_lab_rec(tile **lab, int num_rooms, int **visited, int room_i, int room_j) {
    int i, x = 1, y = 1, direction, lab_i = room_i * 2 + 1, lab_j = room_j * 2 + 1;
    int visited_directions[] = {0, 0, 0, 0};
    if (visited[room_i][room_j]) {
        return;
    }
    visited[room_i][room_j] = 1;
    for(i = 0; i < 4; i++) {
        while (visited_directions[direction = rand() % 4] != 0) {};
        visited_directions[direction] = 1;
        x = direction_x[direction];
        y = direction_y[direction];
        switch (lab[lab_i + x][lab_j + y]) {
        case Empty:
            continue;
        case DWall:
            if ((room_i + x >= 0) && (room_j + y >= 0) &&
                    (room_i + x < num_rooms) && (room_j + y < num_rooms)) {
                if (visited[room_i + x][room_j + y])
                    continue;
                else {
                    lab[lab_i + x][lab_j + y] = Empty;
                    generate_lab_rec(lab, num_rooms, visited, room_i+x, room_j+y);
                }
            }
            continue;
        default:
            continue;
        }
    }
}

void generate_lab(tile **lab, int num_rooms) {
    int start_room_i, start_room_j, i;
    start_room_i = rand() % num_rooms;
    start_room_j = rand() % num_rooms;
    int **visited = calloc(num_rooms, sizeof(int*));
    for(i = 0; i < num_rooms; i++)
        visited[i] = calloc(num_rooms, sizeof(int));
    generate_lab_rec(lab, num_rooms, visited, start_room_i, start_room_j);
    for(i = 0; i < num_rooms; i++)
        free(visited[i]);
    free(visited);

}

void print_lab(tile **lab, int num_rooms) {
    int i, j, lab_size = num_rooms * 2 + 1;
    char *buf = malloc((lab_size + 1) * sizeof(char));
    for(i = 0; i < lab_size; i++) {
        for(j = 0; j < lab_size; j++) {
            buf[j] = sym_vis[lab[i][j]];
        }
        buf[j] = '\0';
        puts(buf);
    }
    free(buf);
}

void deinit_lab(tile **lab, int num_rooms) {
    int i, lab_size = num_rooms * 2 + 1;
    for(i = 0; i < lab_size; i++)
        free(lab[i]);
    free(lab);
}

int main(int argc, char *argv[]) {
    if (argc != 4){
        errx(-1, "Неверное число параметров - %d, требуется 3", argc - 1);
    }
    char *c;
    int num_rooms;
    unsigned int seed;
    long num;

    num = strtol(argv[1], &c, 10);
    if (errno != 0 || *c != '\0' || num > UINT_MAX || num < 0) {
        errx(-1, "Первый аргумент не uint");
    }
    seed = num;

    if (strlen(argv[2]) != 2){
        errx(-1, "Неверное количество символов второго аргумента - %ld, требуется 2", strlen(argv[2]));
    }
    sym_vis[1] = argv[2][0];
    sym_vis[4] = argv[2][0];
    sym_vis[2] = argv[2][1];
    sym_vis[3] = argv[2][1];
    
    num = strtol(argv[3], &c, 10);
    if (errno != 0 || *c != '\0' || num > INT_MAX || num < INT_MIN) {
        errx(-1, "Третий аргумент не число");
    }
    num_rooms = num;

    srand(seed);
    tile **lab = init_lab(num_rooms);
    generate_lab(lab, num_rooms);
    print_lab(lab, num_rooms);
    deinit_lab(lab, num_rooms);
    return 0;
}