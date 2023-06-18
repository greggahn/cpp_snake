#pragma once
#include <curses.h>
#include <time.h>
#include "Item.h"
#include "Empty.h"
#include "Board.h"
#include "Drawable.h"
#include "Snake.h"
#include "Scoreboard.h"
#include "Missionboard.h"
#include "SnakePic.h"
using namespace std;


class SnakeGame
{
	int stage = 1;
	int cur_len = 4;
	Board board;
	bool game_over;
	bool clear;
	Growth* growth;
	Poison* poison;
    Reverse* reverse;
	Snake snake;
	Gate* gate1;
	Gate* gate2;

	Scoreboard scoreboard;
	Missionboard missionboard;
	SnakePic snakepic;

	// scorboard member
	int growthScore;
	int poisonScore;
    int reverseScore;
	int gateScore;
	int maxLength;


	// mission member
	int trGrowthScore;
	int trPoisonScore;
    int trreverseScore;
	int trGateScore;
	int trLength;

	bool growthclear;
	bool poisonclear;
    bool reberseclear;
	bool gateclear;
	bool lengthclear;

public:
	SnakeGame(int height, int width)
	{
		board = Board(height, width);
		int sb_row = board.getStartRow();
		int sb_col = board.getStartCol();
		scoreboard = Scoreboard(width, sb_row,80);
		missionboard = Missionboard(width, 31, 80);
		snakepic = SnakePic();
		initialize1();	// map1
	}

	~SnakeGame()
	{
		delete growth;
		delete poison;
		delete gate1;
		delete gate2;
	}

	// handleNextPiece()
	void handleNextPiece(SnakePiece next)
	{
		if (growth != NULL)
		{
			switch (board.getCharAt(next.getY(), next.getX()))
			{
			case 'G':
				eatGrowth();
				break;
            case 'R':
				eatReverse(reverse);
				break;

			case 'P':
				eatPoison();
				board.add(Empty(snake.tail().getY(), snake.tail().getX()));
				snake.removePiece();
				break;

			case ' ':
			{
				int emptyRow = snake.tail().getY();
				int emptyCol = snake.tail().getX();
				board.add(Empty(emptyRow, emptyCol));
				snake.removePiece();
				break;
			}

			// gate
			case 'D':
			{
				board.time += snake.prev_pieces.size();	
				gateScore += 100;
				scoreboard.updateGateScore(gateScore);
				if (next.getY() == (*gate1).getY() && next.getX() == (*gate1).getX())
				{
					next = meetGate(gate2);
					int emptyRow = snake.tail().getY();
					int emptyCol = snake.tail().getX();
					board.add(Empty(emptyRow, emptyCol));
					snake.removePiece();
				}

				else if (next.getY() == (*gate2).getY() && next.getX() == (*gate2).getX())
				{
					next = meetGate(gate1);
					int emptyRow = snake.tail().getY();
					int emptyCol = snake.tail().getX();
					board.add(Empty(emptyRow, emptyCol));
					snake.removePiece();
				}

				break;
			}

			case '1':	
			case '#':
				game_over = true;
				break;
			}
		}
		
		board.time -= 1;
		board.add(next);
		snake.addPiece(next);
		scoreboard.updateLength(snake.prev_pieces.size());
	}

    void createReverse()
	{
		int y, x;
		board.getEmptyPos(y, x);
		reverse = new Reverse(y, x);
		board.add(*growth);
	}

	SnakePiece take_Reverse(Reverse* r)
	{
		int tempPosX = (*r).getX();
		int tempPosY = (*r).getY();
        
		Direction direction = snake.getDirection();
        if(direction == go_down){
            snake.setDirection(go_up);
        }
        else if(direction == go_up){
            snake.setDirection(go_down);
        }
        else if(direction == go_left){
            snake.setDirection(go_right);
        }
        else if(direction == go_right){
            snake.setDirection(go_left);
        }
		return SnakePiece(tempPosX, tempPosY);
	}
	void eatReverse(Reverse* r)
	{
		take_Reverse(r);
		delete reverse;
		reverse = NULL;
		reverseScore += 100;
		scoreboard.updateReverseScore(reverseScore);
	}

	void deleteReverse()
	{
		board.add(Drawable(reverse->getY(), reverse->getX(), ' '));
		delete reverse;
		reverse = NULL;
	}


	// eatGrowth()
	void createGrowth()
	{
		int y, x;
		board.getEmptyPos(y, x);
		growth = new Growth(y, x);
		board.add(*growth);
	}

	void eatGrowth()
	{
		cur_len++;
		delete growth;
		growth = NULL;
		growthScore += 100;
		scoreboard.updateGrowthScore(growthScore);
	}

	void deleteGrowth()
	{
		board.add(Drawable(growth->getY(), growth->getX(), ' '));
		delete growth;
		growth = NULL;
	}

	void createPoison()
	{
		int y, x;
		board.getEmptyPos(y, x);
		poison = new Poison(y, x);
		board.add(*poison);
	}

	void eatPoison()
	{
		cur_len--;
		poisonScore += 100;
		delete poison;
		poison = NULL;
		board.add(Empty(snake.head().getY(), snake.head().getX()));
		snake.removeBackPiece();
		scoreboard.updatePoisonScore(poisonScore);
	}

	void deletePoison()
	{
		board.add(Drawable(poison->getY(), poison->getX(), ' '));
		delete poison;
		poison = NULL;
	}

	// createGate()
	

	void createGate()
	{
		int y, x;
		board.getRandom(y, x);
		gate1 = new Gate(y, x);
		board.add(*gate1);

		board.getRandom(y, x);
		gate2 = new Gate(y, x);
		board.add(*gate2);
	}

	void deleteGate()
	{
		// ���� gate ��ǥ�� ���� 1�� ����
		board.add(Drawable((*gate1).getY(), (*gate1).getX(), '1'));
		board.add(Drawable((*gate2).getY(), (*gate2).getX(), '1'));

		delete gate1;
		delete gate2;
		gate1 = NULL;
		gate2 = NULL;
	}

	SnakePiece meetGate(Gate* g)
	{
		int tempPosX = (*g).getX();
		int tempPosY = (*g).getY();

		bool possiblego_left = false;
		bool possiblego_right = false;
		bool possiblego_up = false;
		bool possiblego_down = false;

		Direction direction = snake.getDirection();

		if (board.getCharAt(tempPosY + 1, tempPosX) == ' ')
		{
			possiblego_down = true;
		}
		if (board.getCharAt(tempPosY, tempPosX + 1) == ' ')
		{
			possiblego_right = true;
		}
		if (board.getCharAt(tempPosY - 1, tempPosX) == ' ')
		{
			possiblego_up = true;
		}
		if (board.getCharAt(tempPosY, tempPosX - 1) == ' ')
		{
			possiblego_left = true;
		}

		if (direction == go_up)
		{
			if (possiblego_up)
			{
				tempPosY -= 1;
			}
			else if (possiblego_left)
			{
				tempPosX -= 1;
				snake.setDirection(go_left);
			}
			else if (possiblego_right)
			{
				tempPosX += 1;
				snake.setDirection(go_right);
			}
			else if (possiblego_down)
			{
				tempPosY += 1;
				snake.setDirection(go_down);
			}
		}
		else if (direction == go_down)
		{
			if (possiblego_down)
			{
				tempPosY += 1;
			}
			else if (possiblego_right)
			{
				tempPosX += 1;
				snake.setDirection(go_right);
				snake.setDirection(go_right);
			}
			else if (possiblego_left)
			{
				tempPosX -= 1;
				snake.setDirection(go_left);
			}
			else if (possiblego_up)
			{
				tempPosY -= 1;
				snake.setDirection(go_up);
			}
		}
		else if (direction == go_left)
		{
			if (possiblego_left)
			{
				tempPosX -= 1;
			}
			else if (possiblego_down)
			{
				tempPosY += 1;
				snake.setDirection(go_down);
			}
			else if (possiblego_up)
			{
				tempPosY -= 1;
				snake.setDirection(go_up);
			}
			else if (possiblego_right)
			{
				tempPosX += 1;
				snake.setDirection(go_right);
			}
		}
		else if (direction == go_right)
		{
			if (possiblego_right)
			{
				tempPosX += 1;
			}
			else if (possiblego_up)
			{
				tempPosY -= 1;
				snake.setDirection(go_up);
			}
			else if (possiblego_down)
			{
				tempPosY += 1;
				snake.setDirection(go_down);
			}
			else if (possiblego_left)
			{
				tempPosX -= 1;
				snake.setDirection(go_left);
			}
		}

		return SnakePiece(tempPosY, tempPosX);
	}

    //  SnakePiece meetGate(Gate*g) // 게이트에서 나올때 방향 설정
    // {
    //     Gate exit;

    //     if (g == gate1)    // 출구가 gate2
    //     {
    //         exit = *gate2;
    //     }
    //     else                // 출구가 gate1
    //     {
    //         exit = *gate1;
    //     }

    //     Direction dir = snake.getDirection();

    //     int row = exit.getY();
    //     int col = exit.getX();
        

    //     if (exit.getY() == 0) // 상단 벽
    //     {
    //         dir = go_down;
    //     }
    //     else if (exit.getY() == 29) // 하단 벽
    //     {
    //         dir = go_up;
    //     }
    //     else if (exit.getX() == 0) // 좌측 벽
    //     {
    //         dir = go_right;
    //     }
    //     else if (exit.getX() == 29) // 우측 벽
    //     {
    //         dir = go_left;
    //     }
    //     else // 가운데에 있는 벽
    //     {
    //         Direction entryDir = snake.getDirection();

    //         // 진입 방향과 일치하는 방향이 우선
    //         if (entryDir == go_up || entryDir == go_down)
    //         {
    //             if (col - 1 != '1')
    //             {
    //                 dir = go_left;
    //             }
    //             else if (col + 1 != '1')
    //             {
    //                 dir = go_right;
    //             }
    //             else if (entryDir == go_up && row + 1 != '1')
    //             {
    //                 dir = go_down;
    //             }
    //             else if (entryDir == go_down && row - 1 != '1')
    //             {
    //                 dir = go_up;
    //             }
    //             else
    //             {
    //                 // 진입 방향의 시계방향으로 회전
    //                 if (entryDir == go_up)
    //                 {
    //                     dir = go_right;
    //                 }
    //                 else
    //                 {
    //                     dir = go_left;
    //                 }
    //             }
    //         }
    //         else // entryDir == left || entryDir == right
    //         {
    //             if (row-1 != '1')
    //             {
    //                 dir = go_up;
    //             }
    //             else if (row + 1 != '1')
    //             {
    //                 dir = go_down;
    //             }
    //             else if (entryDir == go_left && col + 1 != '1')
    //             {
    //                 dir = go_right;
    //             }
    //             else if (entryDir == go_right && col - 1 != '1')
    //             {
    //                 dir = go_left;
    //             }
    //             else
    //             {
    //                 // 진입 방향의 역시계방향으로 회전
    //                 if (entryDir == go_left)
    //                 {
    //                     dir = go_down;
    //                 }
    //                 else
    //                 {
    //                     dir = go_up;
    //                 }
    //             }
    //         }
    //     }

    //     snake.setDirection(dir);

    //     switch (dir)
    //     {
    //         case go_down:
    //             col++;
    //             break;

    //         case go_up:
    //             col--;
    //             break;

    //         case go_left:
    //             row--;
    //             break;

    //         case go_right:
    //             row++;
    //             break;
    //     }
    //     return SnakePiece(row, col);
    // };

	void initialize1()
	{
		deque<SnakePiece> empty;
		swap(snake.prev_pieces, empty);
		cur_len = 4;
		growth = NULL;
		poison = NULL;
		gate1 = NULL;
		gate2 = NULL;
		board.displayMap1();
		growthScore = 0;
		poisonScore = 0;
        reverseScore = 0;
		maxLength = 30;
		gateScore = 0;
		trGrowthScore = 300; trreverseScore = 100; trPoisonScore = 100; trGateScore = 100, trLength = 5;
		scoreboard.initialize(maxLength);
		missionboard.initialize(trGrowthScore, trPoisonScore, trGateScore, trreverseScore,trLength);
		snakepic.initialize();

		game_over = false;
		srand(time(NULL));

		snake.setDirection(go_down);

		handleNextPiece(SnakePiece(1, 1));
		handleNextPiece(snake.nexthead());
		handleNextPiece(snake.nexthead());
		snake.setDirection(go_right);
		handleNextPiece(snake.nexthead());
		scoreboard.updateLength(snake.prev_pieces.size());

		// create Growth
		if (growth == NULL)
		{
			createGrowth();
		}

		if (poison == NULL)
		{
			createPoison();
		}

		// create gate
		if (gate1 == NULL || gate2 == NULL)
		{
			createGate();
		}
	}

	void initialize2()
	{
		deque<SnakePiece> empty;
		swap(snake.prev_pieces, empty);
		cur_len = 4;
		trGrowthScore = 500; trPoisonScore = 300; trreverseScore = 100; trGateScore = 300, trLength = 5;
		growth = NULL;
		poison = NULL;
		gate1 = NULL;
		gate2 = NULL;
		board.displayMap2();
		growthScore = 0;
		poisonScore = 0;
		maxLength = 30;
		gateScore = 0;
		scoreboard.initialize(maxLength);
		missionboard.initialize(trGrowthScore, trPoisonScore, trGateScore, trreverseScore,trLength);
		snakepic.initialize();

		game_over = false;
		srand(time(NULL));

		snake.setDirection(go_down);

		handleNextPiece(SnakePiece(1, 1));
		handleNextPiece(snake.nexthead());
		handleNextPiece(snake.nexthead());
		snake.setDirection(go_right);
		handleNextPiece(snake.nexthead());
		scoreboard.updateLength(snake.prev_pieces.size());

		// create Growth
		if (growth == NULL)
		{
			createGrowth();
		}

		if (poison == NULL)
		{
			createPoison();
		}

		// create gate
		if (gate1 == NULL || gate2 == NULL)
		{
			createGate();
		}
	}

	void initialize3()
	{
		deque<SnakePiece> empty;
		swap(snake.prev_pieces, empty);
		cur_len = 4;
		trGrowthScore = 1000; trPoisonScore = 500;trreverseScore = 100; trGateScore = 500, trLength = 8;
		growth = NULL;
		poison = NULL;
		gate1 = NULL;
		gate2 = NULL;
		board.displayMap3();
		growthScore = 0;
		poisonScore = 0;
		maxLength = 30;
		gateScore = 0;
		scoreboard.initialize(maxLength);
		missionboard.initialize(trGrowthScore, trPoisonScore, trGateScore, trreverseScore,trLength);
		snakepic.initialize();

		game_over = false;
		srand(time(NULL));

		snake.setDirection(go_down);

		handleNextPiece(SnakePiece(1, 1));
		handleNextPiece(snake.nexthead());
		handleNextPiece(snake.nexthead());
		snake.setDirection(go_right);
		handleNextPiece(snake.nexthead());
		scoreboard.updateLength(snake.prev_pieces.size());

		// create Growth
		if (growth == NULL)
		{
			createGrowth();
		}

		if (poison == NULL)
		{
			createPoison();
		}

		// create gate
		if (gate1 == NULL || gate2 == NULL)
		{
			createGate();
		}
	}

	void initialize4()
	{
		deque<SnakePiece> empty;
		swap(snake.prev_pieces, empty);
		cur_len = 4;
		trGrowthScore = 2000; trPoisonScore = 1000;trreverseScore = 100; trGateScore = 1000, trLength = 15;
		growth = NULL;
		poison = NULL;
		gate1 = NULL;
		gate2 = NULL;
		board.displayMap4();
		growthScore = 0;
		poisonScore = 0;
		maxLength = 30;
		gateScore = 0;
		scoreboard.initialize(maxLength);
		missionboard.initialize(trGrowthScore, trPoisonScore, trGateScore, trreverseScore,trLength);
		snakepic.initialize();

		game_over = false;
		srand(time(NULL));

		snake.setDirection(go_down);

		handleNextPiece(SnakePiece(1, 1));
		handleNextPiece(snake.nexthead());
		handleNextPiece(snake.nexthead());
		snake.setDirection(go_right);
		handleNextPiece(snake.nexthead());
		scoreboard.updateLength(snake.prev_pieces.size());

		// create Growth
		if (growth == NULL)
		{
			createGrowth();
		}

		if (poison == NULL)
		{
			createPoison();
		}

		// create gate
		if (gate1 == NULL || gate2 == NULL)
		{
			createGate();
		}
	}

	void allClearInitializer() {
		growthScore = -100; poisonScore = -100; gateScore = -100; trLength = 999999;
		board.clear(); scoreboard.clear(); missionboard.clear(); snakepic.clear();
		board.wdelwin(); scoreboard.wdelwin(); missionboard.wdelwin(); snakepic.wdelwin();
		
		
		initscr();
		resize_term(26, 100);
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_CYAN);
		border('*', '*', '*', '*', '*', '*', '*', '*');
		
		refresh();

		WINDOW* win1;
		win1 = newwin(13, 51, 6, 24);
		wbkgd(win1, COLOR_PAIR(1));
		wattron(win1, COLOR_PAIR(1));
		wborder(win1, '+', '+', '+', '+', '+', '+', '+', '+');
		mvwprintw(win1, 6, 22, "Clear!!");
		wrefresh(win1);
		getch();
		delwin(win1);
		endwin();
	}

	void processInput()
	{
		chtype input = board.getInput();

		switch (input)
		{
		case KEY_UP:
		case 'w':
			if (snake.getDirection() != go_down)
				snake.setDirection(go_up);
			else
				game_over = true;
			break;

		case KEY_DOWN:
		case 's':
			if (snake.getDirection() != go_up)
				snake.setDirection(go_down);

			else
				game_over = true;
			break;

		case KEY_LEFT:
		case 'a':
			if (snake.getDirection() != go_right)
				snake.setDirection(go_left);
			else
				game_over = true;
			break;

		case KEY_RIGHT:
		case 'd':
			if (snake.getDirection() != go_left)
				snake.setDirection(go_right);
			else
				game_over = true;
			break;

		case 'p':	// pause
			board.setTimeout(-1);
			while (board.getInput() != 'p')
				;
			board.setTimeout(300);
			break;

		default:
			break;
		}
	}

	void updateState()
	{
		handleNextPiece(snake.nexthead());

		if (board.time == 0)
		{
			deleteGrowth();
			deletePoison();
			deleteGate();
			board.time = 50;
		}

		if (growth == NULL)
		{
			createGrowth();
		}

		if (poison == NULL)
		{
			createPoison();
		}

		if (gate1 == NULL || gate2 == NULL)
		{
			createGate();
		}
		if (growthScore >= trGrowthScore) { 
			growthclear = true; 
			missionboard.growthScoreCheck();
			snakepic.drawPart1();
		}
		else {
			growthclear = false;
			missionboard.growthScoreUnCheck();
		}
		if (poisonScore >= trPoisonScore) { 
			poisonclear = true; 
			missionboard.poisonScoreCheck();
		}
		else {
			poisonclear = false;
			missionboard.poisonScoreUnCheck();
		}

		if (gateScore >= trGateScore) {
			gateclear = true;
			missionboard.poisonScoreCheck();
		}
		else {
			poisonclear = false;
			missionboard.gateScoreUnCheck();
		}

		if (cur_len >= trLength) {
			lengthclear = true;
			missionboard.lengthCheck();
		}
		else {
			poisonclear = false;
			missionboard.poisonScoreUnCheck();
		}

		if (growthclear && poisonclear && gateclear && lengthclear)
			clear = true;

		if (clear == true && stage == 1) {
			stage++;
			clear = false;
			initialize2();
		}

		if (clear == true && stage == 2) {
			stage++;
			clear = false;
			initialize3();
		}

		if (clear == true && stage == 3) {
			stage++;
			clear = false;
			initialize4();
		}
		if (clear == true && stage == 4) {
			allClearInitializer();
		}

		if (cur_len < 3)
		{
			game_over = true;
		}
	}

	void redraw()
	{
		board.refresh();
		scoreboard.refresh();
	}

	bool isOver()
	{
		return game_over;
	}

	bool isClear() {
		return clear;
	}

	int getMaxLength() { return maxLength; }


};





