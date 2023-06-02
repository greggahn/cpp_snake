//Functions--------------------------------------------------------------------

int eat(int y, int x){
  int temp; int result = map[stage][y][x];
  for (int i = 0; i < Items.size(); i++) {
      if (Items[i]->get_col() == y && Items[i]->get_row() == x) { temp = i; break; };
  }
  if(ItemType[temp] == 6){
    ((Poison *)Items[temp])->eat();
    result = 6;
  }else if(ItemType[temp] == 5){
    ((Growth *)Items[temp])->eat();
    result = 5;
  }
  delete Items[temp];
  Items.erase(Items.begin()+temp);
  ItemType.erase(ItemType.begin()+temp);
  Item::total --;

  cur_len[stage] = 3 + Growth::score - Poison::score;
  return result;
}

void show_item(){
  //현재시간>현재시간+3 ( 3틱마다 )
  if(time(NULL) > Item_time_counter + Item_print_delay){
    if(Item::total < Item_Max){//아이템 2개이하면
      if(rand()%2 == 0){//랜덤값이 2배수면
        Items.push_back(new Poison());
        ItemType.push_back(6);
      }else{
        Items.push_back(new Growth());
        ItemType.push_back(5);
      }
      Item::total++;
    }
    Item_time_counter = time(NULL);
  }

  for(int i = 0 ; i < Items.size(); i++){
    if(ItemType[i] == 6){//poison 이면
      ((Poison *)Items[i])->show();
    }else if(ItemType[i] == 5){//growth 이면
      ((Growth *)Items[i])->show();
    }
  }
}

void delete_item(){
  for(int i = 0 ; i < 25 ; i++){
    for(int j = 0 ; j < 25 ; j++){
      if(map[stage][i][j] == 5 || map[stage][i][j] == 6) {
        map[stage][i][j] = 0 ;
      }
    }
  }
  for(int temp = 0 ; temp < Items.size() ; temp++){
    delete Items[temp];
  }
  Item::total = 0;
  Items.clear();
  ItemType.clear();
  
}

void reset_score(){
  Gate::score = 0;
  Poison::score = 0;
  Growth::score = 0;
  cout<< "score reset" << endl;
}
