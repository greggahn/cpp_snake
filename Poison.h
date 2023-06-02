#include "Item.h"

class Poison:public Item{
public:
  static int score;
  int get_score() { return score; };

  bool check_map(int y, int x){
    if(map[stage][y][x] == 0) return false;
    return true;
  }

  void show() {
    int y; int x;
    if(make_time == -1){
      do{
        y = rand() % 25;
        x = rand() % 25;
      }while(check_map(y, x));

      set_to_map(y, x, 6, 2);
    }
    else if(time(NULL) >= make_time + Item_change_delay){

      do{
        y = rand() % 25;
        x = rand() % 25;
      }while(check_map(y, x));

      set_to_map(y, x, 6);
    }
  };

  void eat(){
    set_to_map(col, row, 0);
    Poison::score ++;

    // score change
    pItem_num[stage]++;
    cur_len[stage]--;
  };

};
