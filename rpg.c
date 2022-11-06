#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <conio.h>
#include <wchar.h>
#include "rpg.h"

//プレイ時間に関するグローバルな型・変数
time_t start_time, end_time;
int play_time;

int main(void){
  int load, input;   //input:プレイヤーの入力
  Player player;
  Player player2;
  Player player3;
  Items items = {0};

  Area1 area1 = {1,1,1,1,1,0};

  //boss_count = １ならばボス扱い
  //boss_count = 2ならば強制戦闘
  //enemy_skillが0以外なら敵はスキルを使用
  //enemy_id = 1,2,3,4 通常攻撃のみ
  //enemy_id = 100 POISON
  //enemy_id = 101 回復:LV1

  //enemy_id = 0 通常攻撃のみ
  // name hp, maxhp, mp, maxmp, atk, magic, str, agi, luk, lv, exp, gold, badstatus, physical_attack, gun_attack, fire, ice, elec, wave, almighty, death, expel, poison, palyze, charm, close, stone, panic, sleep, curse, boss_count, enemy_id
  Enemy slime = {"スライム", 10, 10, 0, 0, 2, 1, 1, 1, 1, 1, 5, 15, 0, 150, 100, 200, 100, 100, 100, 100, 100, 200, 100, 100, 100, 100, 100, 100, 100, 100, 0, 1};
  Enemy kobalt = {"コボルト", 20, 20, 0, 0, 2, 1, 2, 1, 1, 2, 10, 20, 0, 80, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 0, 2};
  //boss
  Enemy goblin = {"ゴブリン", 65, 65, 0, 0, 3, 1, 2, 2, 1, 3, 25, 30, 0, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 1, 3};
  Enemy zombiedog = {"ゾンビドッグ", 50, 50, 0, 0, 2, 1, 1, 5, 1, 3, 25, 15, 0, 100, 100, 200, 200, 100, 100, 100, 100, 200, 100, 100, 100, 100, 100, 100, 100, 100, 0, 4};
  Enemy ghoul = {"グール", 30, 50, 10, 10, 1, 1, 1, 1, 1, 2, 30, 50, 0, 100, 100, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 0, 5};
  Enemy pixie = {"ピクシー", 55, 55, 15, 15, 1, 3, 1, 5, 5, 3, 25, 40, 0, 100, 150, 100, 100, 50, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 0, 101};
  Enemy angel = {"エンジェル", 108, 108, 30, 30, 2, 5, 3, 5, 2, 4, 50, 100, 0, 100, 100, 100, 100, 150, 100, 100, 200, 100, 100, 100, 100, 100, 100, 100, 100, 100, 1, 101};

  srand((unsigned int)time(NULL));

  P_skill player_skill;
  P_skill player_skill2;
  P_skill player_skill3;

  do{
    printf("MAIN MENU\n");
    printf("1:<<<Load Game>>>\n");
    printf("2:<<<New Game>>>\n");
    printf("1か2を入力してください(ゲームを起動しない場合はcを入力してください)\n");
    input = _getch();
    if ( input == '1' ){
      load = 1;
      save_load(&player, &player2, &player3, &player_skill, &player_skill2, &player_skill3, &items, load);
      start_time = time(NULL);
    }
    else if ( input == '2' ){
      //new gameでは、player.stage_clearは0
      //prologue();
      start_time = time(NULL);
      printf("start_time:%d\n", start_time);
      game_start(&player, &player2, &player3);
      load = 0;
      game_story1(&player, &player2, &player3, &player_skill, &player_skill2, &player_skill3, &items, &area1, &slime, &kobalt, &goblin);
      save_load(&player, &player2, &player3, &player_skill, &player_skill2, &player_skill3, &items, load);
    }
    else if ( input == '' ){
      printf("強制終了\n");
      exit(EXIT_FAILURE);
    }
    else if ( input == 'c' ){
      printf("ゲームを終了します・・・\n");
      exit(EXIT_SUCCESS);
    }
  }while ( input != '1' && input != '2');

  load = 0;
  if ( player.stage_clear == 1 ){
    game_story2(&player, &player2, &player3, &player_skill, &player_skill2, &player_skill3, &items);
    save_load(&player, &player2, &player3, &player_skill, &player_skill2, &player_skill3, &items, load);
  }
  else if ( player.stage_clear == 2 ){
    printf("Wait・・・\n");
  }

  return 0;
}