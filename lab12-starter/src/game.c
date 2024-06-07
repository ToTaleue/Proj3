#include "game.h"
#include "assembly/example.h"
#include "lcd/lcd.h"
#include "utils.h"


static u8 number_length(u16 num) {
  u8 length = 0;
  while (num != 0) {
    num /= 10;
    length++;
  }
  return length;
}


// 这个是RISC-V的界面，我不太理解是不是要写在这里？
static void welcome_input_handle(GameData* data) {
  // 理论有交互点击，之后才进入下一个界面
  ;
}

static void menu_input_handle(GameData* data) {
  ;

}



static void playing_input_handle(GameData* data) {
  ;
}


static void welcome_render(GameData* data) {


  draw();
  delay_1ms(data->welcome.delay);


}

static void menu_render(GameData* data) {




}

static void playing_render(GameData* data) {
  LCD_ShowString(5, 20, (u8*)"Score", WHITE);
  LCD_ShowString(5, 40, (u8*)"Life", WHITE);
  LCD_ShowNum(60, 20, data->playing.score, number_length(data->playing.score), WHITE);
  LCD_ShowNum(60, 40, data->playing.life, number_length(data->playing.life), WHITE);
  LCD_DrawRectangle(5, 45, 75, 155, WHITE);



}


void game_init(GameState* state, GameData* data) {
  *state = STATE_WELCOME;
  data->welcome.delay = 2000;

}

void game_update(GameState* state, GameData* data) {
  switch (*state) {
  case STATE_WELCOME:
    welcome_input_handle(data);
    break;
  case STATE_MENU:
    menu_input_handle(data);
    break;
  case STATE_PLAYING:
    playing_input_handle(data);
    break;
  default:
    break;
  }
}

void game_render(GameState* state, GameData* data) {
  switch (*state) {
  case STATE_WELCOME:
    welcome_render(data);
    *state = STATE_PLAYING;
    break;
  case STATE_MENU:
    menu_render(data);
    break;
  case STATE_PLAYING:
    playing_render(data);
    break;
  default:
    break;
  }
}

void fps_ctrl() {}

