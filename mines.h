#ifndef MINES_H
#define MINES_H

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <time.h>
#include <stdint.h>

#define WINDOW_WIDTH        800
#define WINDOW_HEIGHT       800
#define SIDES               8
#define TOTAL_BOMBS         10

typedef enum {
    LOADING,
    RUNNING,
    WIN,
    LOSS
} game_status;

typedef struct {
    game_status status;
    int8_t field[SIDES][SIDES];
    int8_t clicked[SIDES][SIDES];
} game_state;

void print_field(int8_t field[][SIDES]);
void draw_field(game_state * game_ptr);
void init_game(game_state * game_ptr);
void open_all_zeros(game_state * game_ptr, int8_t row, int8_t col);
void check_game_status(game_state * game_ptr);
#endif