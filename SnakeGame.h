//���� ���� ������ ����� �Է� ����
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
    int stage = 1;  //�ʱ� �������� ����
    int cur_len = 4; //�ʱ� ������ũ�� ���� ����
    Board board;
    bool game_over; //������ ���¸� ���³��� bool��
    GrowItem* item_g; //������ ����
    Snake snake; //������ũ(�÷��̾�) ��ü

public:
    SnakeGame(int height, int width) {
        board = Board(height, width);
        
        initialize(); //���� �ʱ�ȭ
    }
    ~SnakeGame() { //�Ҹ���
        delete item_g;
    }
    
    void initialize() {
        item_g = NULL;
        board.initialize();
        game_over = false;
        srand(time(NULL));
        snake.setDirection(down); //ó�� �̵������� �Ʒ���

        handleNextPiece(SnakePiece(1, 1)); //�ʱ� ��ġ�� (1,1), �Ӹ� ����
        handleNextPiece(snake.nexthead()); //���� ����
        handleNextPiece(snake.nexthead()); //���� ����
        handleNextPiece(snake.nexthead()); //���� ����

        if (item_g == NULL) { //**���� �������� ������ �����ϱ�(�Ƹ� Ư���ð����� �ٸ� ��ġ�� �ٲ�� �����ϼž��� �� �����ϴ�.
            createItem_g(); 
        }
    }

    void processInput() { //����� �Է� �ް� ���� ����
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
            case 'p': //�Ͻ�����Ű
                board.setTimeout(-1);
                while (board.getInput() != 'p'); //�Ͻ����� �����Ϸ��� �ٽ� pŰ ������ ��.
                board.setTimeout(500);
                break;
        }
    }
    
    void updateState() { //
        handleNextPiece(snake.nexthead()); //������ũ�� �Ϲ� ���� ��������, �������� �Ծ�����, ���� ��Ҵ��� ��� �Ǵ��ϴ� �Լ�
        
        if (item_g == NULL) {
            createItem_g();
        }
    }
    void createItem_g() { //���� ������ ����(������ ���� ���ǿ� �°� ���� �ʿ�)
        if (item_g == NULL) {
            int y, x;
            board.getEmptyPos(y, x); // ������ũ�� ���� ���� �ƴ� ��ǥ ã��
            item_g = new GrowItem(y, x);
            board.add(*item_g); //�ʿ� ����ϱ�
        }
    }
    void eatItem_g() { // ���� �������� ������
        cur_len++;  //���� 1 ����
        delete item_g;  //������ ����
        item_g = NULL; //���¸� NULL�� ����� �ٽ� �������� ������ �� �ְ�
    }
    void handleNextPiece(SnakePiece next) {

        if (item_g != NULL)
        {
            switch (board.getCharAt(next.getY(), next.getX()))  //�ʿ��� ������ũ�� �Ӹ��� ��ġ�� ���� �ִ� char��
            {
            case 'A': //����������� ���
                eatItem_g();
                break;

            case ' ': //�Ϲ����� ���� ���
            {
                int emptyRow = snake.tail().getY();
                int emptyCol = snake.tail().getX();
                board.add(Empty(emptyRow, emptyCol));
                snake.dettachPiece();
                break;
            }

            case '1':	// wall�� �浹�� ����
            case '#':	// �Ӹ��� ���� ���� ��� + ���� ����� �ݴ�Ǵ� ����Ű�� �Էµ� ��쿡 ���� ����
                game_over = true;
                break;
            }
        }
        board.add(next); //�ʿ� ������ũ ���
        snake.attachPiece(next);
    }

    void redraw() {
        board.refresh(); //�� ���ΰ�ħ
    }

    bool isOver() {
        return game_over;  //���� ���� ���� ��ȯ
    }
};