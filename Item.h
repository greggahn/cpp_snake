#pragma once
#include <curses.h>
#include "Drawable.h"

class Growth : public Drawable
{
public:
	Growth(int y, int x)
	{
		this->y = y;
		this->x = x;
		this->icon = 'G';
	}
};

class Poison : public Drawable
{
public:
	Poison(int y, int x)
	{
		this->y = y;
		this->x = x;
		this->icon = 'P';
	}
};

class Reverse : public Drawable
{
public:
	Reverse(int y, int x)
	{
		this->y = y;
		this->x = x;
		this->icon = 'R';
	}
};

class Gate : public Drawable
{
public:
	Gate(){

	}
	Gate(int y, int x)
	{
		this->y = y;
		this->x = x;
		this->icon = 'D';
	}
	 bool operator ==(const Gate g){
        return (this->x == g.x) && (this->y == g.y);
	}
};
