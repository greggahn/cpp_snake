//Gate---------------------------------------------------------------------------

class Gate{
  pair<int,int> A = make_pair(0,0); pair<int,int> B = make_pair(0,0);
public:
  static int score;
  int get_col(){ return A.first ; };
  int get_row(){ return A.second ; };
  bool invisible = true;

  void set_to_map(int y, int x, int v){
    map[stage][y][x] = v;
    A.first = y; A.second = x;//A(y,x)
    //움직임 / 맵 /아이템 / 게이트
    int yb, xb;
    do{
      yb = rand() % 25;
      xb = rand() % 25;
    }while( check_map(yb, xb) or (yb == y or xb == x) );

    map[stage][yb][xb] = v;
    B.first = yb; B.second = xb;
  };

  bool check_map(int y, int x){
    if(map[stage][y][x] == 1) return false;
    return true;
  };

  void show(){
    if(invisible){
      int y, x;
      do{
        y = rand() % 25;
        x = rand() % 25;
      }while(check_map(y, x));

      set_to_map(y,x,7);
      invisible = false;
    }
  };

  pair<int, int> enter(int y, int x){
    if(A.first == y and A.second == x) return B;
    if(B.first == y and B.second == x) return A;
    pair<int, int> Err(-1,-1);
    gate_num[stage]++; // change score
    return Err;
  };

  void remove(){
    map[stage][A.first][A.second] = 1;
    map[stage][B.first][B.second] = 1;
    A.first = 0 ; A.second = 0;
    B.first = 0 ; B.second = 0;
    score++;

    invisible = true;
  };
};
