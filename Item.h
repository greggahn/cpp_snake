#ifndef __Item__
#define __Item__

//Item-------------------------------------------------------------------------------

class Item{
protected:
  time_t make_time = -1;
  int col = 0;
  int row = 0;
public:
  static int total;
  ~Item() { cout<< "item removed" << endl;};
  void set_to_map(int y, int x, int v , int z = 0){
    map[stage][y][x] = v; map[stage][col][row] = z;
    time_initialize();
    col = y; row = x;
  };
  void time_initialize() {make_time = time(NULL);};

  int get_col(){ return col; };
  int get_row(){ return row; };
  virtual void show(){ };
  virtual void eat(){ };
};

vector<Item *> Items; 
vector<int> ItemType;
time_t Item_time_counter = time(NULL);


#endif
