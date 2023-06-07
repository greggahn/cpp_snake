#include <iostream>
#include <ncurses.h>
#include <panel.h>
using namespace std;

int main() {
        WINDOW *my_wins[3];                                                       
        PANEL  *my_panels[3];                                                     
        int lines = 10, cols = 40, y = 2, x = 4, i;                               
                                                                                  
        initscr();                                                                
        cbreak();                                                                 
        noecho();                                                                 
                                                                                  
        /* Create windows for the panels */                                       
        my_wins[0] = newwin(lines, cols, y, x);                                   
        my_wins[1] = newwin(lines, cols, y + 1, x + 5);                           
        my_wins[2] = newwin(lines, cols, y + 2, x + 10);                          
                                                                                  
        /*                                                                        
         * Create borders around the windows so that you can see the effect       
         * of panels                                                              
         */                                                                       
        for(i = 0; i < 3; ++i)                                                   
                box(my_wins[i], 0, 0);                                            
                                                                                  
        /* Attach a panel to each window */     /* Order is bottom up */          
        my_panels[0] = new_panel(my_wins[0]);   /* Push 0, order: stdscr-0 */     
        my_panels[1] = new_panel(my_wins[1]);   /* Push 1, order: stdscr-0-1 */   
        my_panels[2] = new_panel(my_wins[2]);   /* Push 2, order: stdscr-0-1-2 */ 
                                                                                  
        /* Update the stacking order. 2nd panel will be on top */                 
        update_panels();                                                          
                                                                                  
        /* Show it on the screen */                                               
        doupdate();                                                               
                                                                                  
        getch();                                                                  
        endwin();
    WINDOW* win1;//window pointer
     WINDOW* win2;
     WINDOW* win11;
     PANEL * win1P;
     PANEL * win2P;
//     // char key;
//     // char userName[8];
      initscr();
      resize_term(25,25);
      start_color();
      init_pair(1,COLOR_WHITE,COLOR_RED);
      init_pair(2,COLOR_BLACK,COLOR_GREEN);
      border('*','*','*','*','*','*','*','*');
      mvprintw(1,1,"A DEFAULT WINDOW");
      refresh();
      getch();
      

      win1=newwin(20,20,3,3);//window (row,col,y,x);
      win11=newwin(40,40,4,4);
      win1P = new_panel(win1);
      win1P = new_panel(win11);
      wbkgd(win1,COLOR_PAIR(1));//특정윈도우전체적용
      wattron(win1,COLOR_PAIR(1));//특정윈도우적용
      mvwprintw(win1,1,1,"1 WINDOW");//특정윈도우,y,x,출력
      wborder(win1,'3','3','3','3','3','3','3','3');
     // wrefresh(win1);   
     update_panels();
     doupdate();
      getch();
      
        win2=newwin(5,5,3,3);
        win2P = new_panel(win2);
        wbkgd(win2,COLOR_PAIR(2));//특정윈도우전체적용
        wattron(win2,COLOR_PAIR(2));
        mvwprintw(win2,1,1,"2 WINDOW");//특정윈도우,y,x,출력
        wborder(win2,'3','3','3','3','3','3','3','3');
      //  wrefresh(win2);
        getch();
        doupdate();
        hide_panel(win1P);
        getch();
    //delwin(win2);
    //delwin(win1);
    endwin();
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
    // refresh();
    // getch();
   // endwin();
    
    return 0;
}