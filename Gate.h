#include <iostream>
#include <curses.h>
#include <cstdlib>
#include "Drawable.h"

class Gate : public Drawable 
{
public:
    Gate(int y, int x){
        this->x = x;
        this->y = y;
        this->icon = 'G';
    }
};

