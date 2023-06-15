//게임 상태 관리와 사용자 입력 관리
#pragma once
#include <curses.h>
#include <time.h>
#include <stdlib.h>
#include "growth_item.h"
#include "Empty.h"
#include "Board.h"
#include "Drawable.h"
#include "Snake.h"

class SnakeGame {
    int stage = 1;  //초기 스테이지 설정
    int cur_len = 4; //초기 스네이크의 길이 설정
    Board board;
    bool game_over; //게임의 상태를 나태내는 bool값
    GrowItem* item_g; //아이템 변수
    Snake snake; //스넹이크(플레이어) 객체

public:
    SnakeGame(int height, int width) {
        board = Board(height, width);
        
        initialize(); //게임 초기화
    }
    ~SnakeGame() { //소멸자
        delete item_g;
    }
    
    void initialize() {
        item_g = NULL;
        board.initialize();
        game_over = false;
        srand(time(NULL));
        snake.setDirection(down); //처음 이동방향은 아래쪽

        handleNextPiece(SnakePiece(1, 1)); //초기 위치는 (1,1), 머리 생성
        handleNextPiece(snake.nexthead()); //꼬리 생성
        handleNextPiece(snake.nexthead()); //꼬리 생성
        handleNextPiece(snake.nexthead()); //꼬리 생성

        if (item_g == NULL) { //**성장 아이템이 없으면 생성하기(아마 특정시간마다 다른 위치로 바뀌게 수정하셔야할 것 같습니다.
            createItem_g(); 
        }
    }

    void processInput() { //사용자 입력 받고 방향 설정
        chtype input = board.getInput();
        switch (input) {
            case 'w':
            case KEY_UP:
                snake.setDirection(up);
                break;
            case 's':
            case KEY_DOWN:
                snake.setDirection(down);
                break;
            case 'd':
            case KEY_RIGHT:
                snake.setDirection(right);
                break;
            case 'a':
            case KEY_LEFT:
                snake.setDirection(left);
                break;
            case 'p': //일시정지키
                board.setTimeout(-1);
                while (board.getInput() != 'p'); //일시정지 해제하려면 다시 p키 누르면 됨.
                board.setTimeout(500);
                break;
        }
    }
    
    void updateState() { //
        handleNextPiece(snake.nexthead()); //스네이크가 일반 맵을 지나는지, 아이템을 먹었는지, 벽과 닿았는지 등등 판단하는 함수
        
        if (item_g == NULL) {
            createItem_g();
        }
    }
    void createItem_g() { //성장 아이템 생성(아이템 생성 조건에 맞게 수정 필요)
        if (item_g == NULL) {
            int y, x;
            board.getEmptyPos(y, x); // 스네이크가 없고 벽도 아닌 좌표 찾기
            item_g = new GrowItem(y, x);
            board.add(*item_g); //맵에 출력하기
        }
    }
    void eatItem_g() { // 성장 아이템을 먹으면
        cur_len++;  //길이 1 증가
        delete item_g;  //아이템 삭제
        item_g = NULL; //상태를 NULL로 만들어 다시 아이템을 생성할 수 있게
    }
    void handleNextPiece(SnakePiece next) {

        if (item_g != NULL)
        {
            switch (board.getCharAt(next.getY(), next.getX()))  //맵에서 스네이크의 머리가 위치한 곳에 있는 char가
            {
            case 'A': //성장아이템인 경우
                eatItem_g();
                break;

            case ' ': //일반적인 맵인 경우
            {
                int emptyRow = snake.tail().getY();
                int emptyCol = snake.tail().getX();
                board.add(Empty(emptyRow, emptyCol));
                snake.dettachPiece();
                break;
            }

            case '1':	// wall에 충돌한 경우와
            case '#':	// 머리에 몸이 닿은 경우 + 현재 방향과 반대되는 방향키가 입력된 경우에 게임 종료
                game_over = true;
                break;
            }
        }
        board.add(next); //맵에 스네이크 출력
        snake.attachPiece(next);
    }

    void redraw() {
        board.refresh(); //맵 새로고침
    }

    bool isOver() {
        return game_over;  //게임 종료 여부 반환
    }
};