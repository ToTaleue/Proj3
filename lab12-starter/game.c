#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定义游戏状态枚举
typedef enum {
  STATE_MENU,
  STATE_PLAYING,
  STATE_GAME_OVER
} GameState;

// 定义游戏数据结构
typedef struct {
  int score;
  int bird_y;
  int pipe_x;
  int pipe_gap_y;
} GameData;

// 声明状态函数
void menu_enter(GameData *data);
void menu_update(GameData *data);
void menu_render(GameData *data);

void playing_enter(GameData *data);
void playing_update(GameData *data);
void playing_render(GameData *data);

void game_over_enter(GameData *data);
void game_over_update(GameData *data);
void game_over_render(GameData *data);

// 定义状态对象
typedef struct {
  void (*enter)(GameData *);
  void (*update)(GameData *);
  void (*render)(GameData *);
} State;

State menu_state = {
  menu_enter,
  menu_update,
  menu_render
};

State playing_state = {
  playing_enter,
  playing_update,
  playing_render
};

State game_over_state = {
  game_over_enter,
  game_over_update,
  game_over_render
};

// 定义状态机结构体
typedef struct {
  State *current_state;
  State *states[3];
  GameData data;
} StateMachine;

// 状态机初始化
void state_machine_init(StateMachine *state_machine) {
  state_machine->current_state = NULL;
  state_machine->states[STATE_MENU] = &menu_state;
  state_machine->states[STATE_PLAYING] = &playing_state;
  state_machine->states[STATE_GAME_OVER] = &game_over_state;
  state_machine->data.score = 0;
  state_machine->data.bird_y = 0;
  state_machine->data.pipe_x = 0;
  state_machine->data.pipe_gap_y = 0;
}

// 状态机切换状态
void state_machine_change_state(StateMachine *state_machine, GameState state_id) {
  if (state_machine->current_state) {
    // 退出当前状态
    // state_machine->current_state->exit();
  }
  state_machine->current_state = state_machine->states[state_id];
  state_machine->current_state->enter(&state_machine->data);
}

// 状态机更新
void state_machine_update(StateMachine *state_machine) {
  if (state_machine->current_state) {
    state_machine->current_state->update(&state_machine->data);
  }
}

// 状态机渲染
void state_machine_render(StateMachine *state_machine) {
  if (state_machine->current_state) {
    state_machine->current_state->render(&state_machine->data);
  }
}

// 实现菜单状态的函数
void menu_enter(GameData *data) {
  printf("进入菜单状态\n");
}

void menu_update(GameData *data) {
  // 处理菜单状态的更新逻辑
  // ...

  // 按下空格键开始游戏
  if (getchar() == ' ') {
    state_machine_change_state(&state_machine, STATE_PLAYING);
  }
}

void menu_render(GameData *data) {
  printf("渲染菜单界面\n");
}

// 实现游戏状态的函数
void playing_enter(GameData *data) {
  printf("进入游戏状态\n");
  data->score = 0;
  data->bird_y = 0;
  data->pipe_x = 0;
  data->pipe_gap_y = 0;
}

void playing_update(GameData *data) {
  // 处理游戏状态的更新逻辑
  // ...

  // 模拟游戏结束条件
  if (data->score >= 10) {
    state_machine_change_state(&state_machine, STATE_GAME_OVER);
  }
}

void playing_render(GameData *data) {
  printf("渲染游戏界面\n");
  printf("分数: %d\n", data->score);
}

// 实现游戏结束状态的函数
void game_over_enter(GameData *data) {
  printf("进入游戏结束状态\n");
}

void game_over_update(GameData *data) {
  // 处理游戏结束状态的更新逻辑
  // ...

  // 按下空格键重新开始游戏
  if (getchar() == ' ') {
    state_machine_change_state(&state_machine, STATE_PLAYING);
  }
}

void game_over_render(GameData *data) {
  printf("渲染游戏结束界面\n");
  printf("最终得分: %d\n", data->score);
}

// 主函数
int main() {
  StateMachine state_machine;
  state_machine_init(&state_machine);

  state_machine_change_state(&state_machine, STATE_MENU);

  while (1) {
    state_machine_update(&state_machine);
    state_machine_render(&state_machine);
  }

  return 0;
}