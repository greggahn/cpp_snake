#include <iostream>
#include <ncursesw/curses.h>
//#include <ncurses.h>
#include <clocale> // unicode
#include <cstdlib>
#include <vector>
#include <thread>
#include <locale.h>
#include <panel.h>
using namespace std;

int Item_Max = 3, Item_print_delay = 3, Item_change_delay = 5;
int startCounter =1;
//Header files
#include "map.h"
#include "Poison.h"
#include "Growth.h"
#include "Gate.h"
#include "Functions.h"

int Gate::score = 0; 
int Poison::score = 0; 
int Growth::score = 0;
int Item::total = 0;
Gate gate;
//main---------------------------------------------------------------------------
// ignore OK
int main(void){
  setlocale(LC_ALL, ""); // use unidcode
  // init game //
  initscr();//ncurses TUI 모드 사용 시작 y:25,x:80 window 생성
  resize_term(40, 85);//terminal y:40,x:85

   // init color //
  start_color();
  init_color(COLOR_WHITE, 1000, 1000, 1000);  // init white
  init_color(COLOR_BLACK, 0, 0, 0);             // init black
  init_color(COLOR_YELLOW, 500, 500, 500);    // init gray
  // init color pair match // 팔레트 , 폰트색 , 폰트배경색
  init_pair(1, COLOR_WHITE, COLOR_WHITE);     // 0 : Blank
  init_pair(2, COLOR_YELLOW, COLOR_YELLOW);   // 1 : Wall
  init_pair(3, COLOR_BLACK, COLOR_BLACK);     // 2 : Immune Wall
  init_pair(4, COLOR_CYAN, COLOR_CYAN);       // 3 : Snake Head
  init_pair(5, COLOR_BLUE, COLOR_BLUE);       // 4 : Snake Body
  init_pair(6, COLOR_GREEN, COLOR_GREEN);     // 5 : Growth Item
  init_pair(7, COLOR_RED, COLOR_RED);         // 6 : Poison Item
  init_pair(8, COLOR_MAGENTA, COLOR_MAGENTA); // 7 : Gate
 
  WINDOW *win0 = newwin(40, 85, 0, 0);//글씨
  wborder(win0,'|', '|', '-', '-', '+', '+', '+', '+');
  mvwprintw(win0,3, 25, "C++ Programming - Section 3 - Group 8");
  mvwprintw(win0,4, 33, "snake game project");
  mvwprintw(win0,6, 33, "20222222 AN HYEON JONG");
  mvwprintw(win0,7, 33, "20222222 KIM HYE WON");
  mvwprintw(win0,8, 33, "20222222 OH JU YEOP");
  mvwprintw(win0,9, 33, "20192062 PARK JEONG BIN");
  // init score, mission //
  mvwprintw(win0,13, 57, "|------ S C O R E ------|");
  mvwprintw(win0,26, 57, "|---- M I S S I O N ----|");
 //window (row,col,y,x);
  WINDOW *win1 = newwin(25, 50, 13, 3);//게임화면
  WINDOW *win2 = newwin(11, 25, 14, 57);//score
  WINDOW *win3 = newwin(11, 25, 27, 57);//mission
  wborder(win2, '|', '|', '-', '-', '+', '+', '+', '+');
  wborder(win3, '|', '|', '-', '-', '+', '+', '+', '+');
  refresh();
  // start window //
  WINDOW *win4 = newwin(38, 83, 1, 1);
  PANEL* win4P = new_panel(win4);
  wborder(win4,'|', '|', '-', '-', '+', '+', '+', '+');
  mvwprintw(win4, 3, 12, "     _______..__   __.      ___       __  ___  _______ ");
  mvwprintw(win4, 4, 12, "    /       ||  \\ |  |     /   \\     |  |/  / |   ____|");
  mvwprintw(win4, 5, 12, "   |   (----`|   \\|  |    /  ^  \\    |  '  /  |  |__   ");
  mvwprintw(win4, 6, 12, "    \\   \\    |  . `  |   /  /_\\  \\   |    <   |   __|  ");
  mvwprintw(win4, 7, 12, ".----)   |   |  |\\   |  /  _____  \\  |  .  \\  |  |____ ");
  mvwprintw(win4, 8, 12, "|_______/    |__| \\__| /__/     \\__\\ |__|\\__\\ |_______|");
  mvwprintw(win4, 9, 12,  "     _______      ___      .___  ___.  _______ ");
  mvwprintw(win4, 10, 14, "  /  _____|    /   \\     |   \\/   | |   ____|");
  mvwprintw(win4, 11, 14, " |  |  __     /  ^  \\    |  \\  /  | |  |__");
  mvwprintw(win4, 12, 14, " |  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|");
  mvwprintw(win4, 13, 14, " |  |__| |  /  _____  \\  |  |  |  | |  |____  ");
  mvwprintw(win4, 14, 14, "  \\______| /__/     \\__\\ |__|  |__| |_______|");
  mvwprintw(win4, 30, 25, "PRESS ANY KEY TO START");
 
  update_panels();
  doupdate();
  getch();
  hide_panel(win4P);
  //
  wrefresh(win0);
  wrefresh(win1);
  wrefresh(win2);
  wrefresh(win3);
  
  //난수 생성
  srand((unsigned int)time(NULL));


//map
int count = 0;
while(true){
  show_item();
  if(Poison::score % 3 == 1) gate.show();
  if(gate.invisible == false and Poison::score % 3 == 2){
    pair<int, int> output = gate.enter(gate.get_col(), gate.get_row());
    gate.remove();
  }
  if(count  == 7){ count = 0; }
  count ++ ;
  for(int i=0; i<25; i++) {
    for(int j=0; j<25; j++) {
      int k = map[stage][i][j] + 1;
      wattron(win1, COLOR_PAIR(k));
      mvwprintw(win1, i, j*2, "%d", map[stage][i][j]);
      mvwprintw(win1, i, j*2 + 1, "%d", map[stage][i][j]);
      wattroff(win1, COLOR_PAIR(k));
    }
  }
  
  // score print //
  mvwprintw(win2, 2, 8, "B: %d / %d", cur_len[stage], max_len[stage]);//현재길이//max길이
  mvwprintw(win2, 4, 8, "+:   %d", gItem_num[stage]);//growth
  mvwprintw(win2, 6, 8, "-:   %d", pItem_num[stage]);//poison
  mvwprintw(win2, 8, 8, "G:   %d", gate_num[stage]);//gate
  // mission check //
  if(max_len[stage] >= len_goal[stage]) len_check[stage] = 'v';//victory
  if(gItem_num[stage] >= gItem_goal[stage]) gItem_check[stage] = 'v';
  if(pItem_num[stage] >= pItem_goal[stage]) pItem_check[stage] = 'v';
  if(gate_num[stage] >= gate_goal[stage]) gate_check[stage] = 'v';
  // mission print //
  mvwprintw(win3, 2, 8, "B: %d (%c)", len_goal[stage], len_check[stage]);
  mvwprintw(win3, 4, 8, "+: %d (%c)", gItem_goal[stage], gItem_check[stage]);
  mvwprintw(win3, 6, 8, "-: %d (%c)", pItem_goal[stage], pItem_check[stage]);
  mvwprintw(win3, 8, 8, "G: %d (%c)", gate_goal[stage], gate_check[stage]);
 
  // refresh windows //
  wrefresh(win1);
  wrefresh(win2);
  wrefresh(win3);
 
  curs_set(0); // 커서 안보이게
  if(len_check[stage]=='v' && gItem_check[stage]=='v'
     && pItem_check[stage]=='v' && gate_check[stage]=='v')
  {
    stage++;
    if(stage == 4) stage=0;
  }
  this_thread::sleep_for(2000ms);
}
delwin(win0);
delwin(win1);
delwin(win2);
delwin(win3);
endwin();
return 0;
}