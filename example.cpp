// #include <iostream>
// #include <ncurses.h>
// using namespace std;

// int main() {
//     WINDOW* win1;//window pointer
//     WINDOW* win2;
//     // char key;
//     // char userName[8];
//       initscr();
//       resize_term(25,25);
//       start_color();
//       init_pair(1,COLOR_WHITE,COLOR_RED);
//       init_pair(2,COLOR_BLACK,COLOR_GREEN);
//       border('*','*','*','*','*','*','*','*');
//       mvprintw(1,1,"A DEFAULT WINDOW");
//       refresh();
//       getch();

//       win1=newwin(20,20,3,3);//window (row,col,y,x);
//       wbkgd(win1,COLOR_PAIR(1));//특정윈도우전체적용
//       wattron(win1,COLOR_PAIR(1));//특정윈도우적용
//       mvwprintw(win1,1,1,"1 WINDOW");//특정윈도우,y,x,출력
//       wborder(win1,'3','3','3','3','3','3','3','3');
//       wrefresh(win1);
// getch();
//       win2=newwin(5,5,3,3);
//       wbkgd(win2,COLOR_PAIR(2));//특정윈도우전체적용
//       wattron(win2,COLOR_PAIR(2));
//       mvwprintw(win2,1,1,"2 WINDOW");//특정윈도우,y,x,출력
//       wborder(win2,'3','3','3','3','3','3','3','3');
//       wrefresh(win2);
//     getch();
//     delwin(win2);
//     delwin(win1);
//     endwin();
//     //  keypad(stdscr,TRUE);//특수키입력
//     //  //stdscr - default window 포인터
//     //  curs_set(1);//커서설정0,1,2
//     //  //noecho();//입력값 안보이게
//     //  printw("NAME: ");
//     //  scanw("%s",userName);
//     //  printw("키입력시 화면삭제");
//     //  refresh();
//     // getch();
//     // clear();
//     // start_color();
//     // init_pair(1,COLOR_BLUE,COLOR_YELLOW);//1번팔레트,글자색,바탕색
//     // init_pair(2,COLOR_RED,COLOR_GREEN);

//     // bkgd('-');//한attribute으로 윈도우전체적용
//     // attron(COLOR_PAIR(1));//사용할attribute지정
//     // mvprintw(1,1,"c++ programming");
//     // mvprintw(1,50,"Computer");
//     // attroff(COLOR_PAIR(1));

//     // attron(COLOR_PAIR(2));
//     // border('1','2','3','4','5','6','7','8');//경계선
// 	// attroff(COLOR_PAIR(2));
//     // refresh();
//     // getch();
//     // endwin();
    
//     return 0;
// }