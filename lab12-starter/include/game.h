#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "lcd/lcd.h"


typedef enum {
  STATE_WELCOME,
  STATE_MENU,
  STATE_PLAYING,
} GameState;


// 因为是单向的，所以可以用union，不用进行存储
typedef union {
  struct {
    /* data */
    u16 delay;
  } welcome;
  struct {
    /* data */
    u16 choice;
  } menu;
  struct {
    u16 score;
    u16 life;
    u16 bird_x;
    u16 bird_y;
    u16 bird_v;
    u16 pipe_x;
    u16 pipe_up_y;
    u16 pipe_down_y;
    u16 pipe_gap_x;
    u16 pipe_gap_y;
  } playing;
} GameData;


void game_init(GameState* state, GameData* data);

void game_update(GameState* state, GameData* data);

void game_render(GameState* state, GameData* data);

void fps_ctrl();

#endif /* GAME_H */
