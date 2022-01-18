/*********************************************
  gotoxy   ... Positionieren des Cursors
  setcolor ... Einstellen der Farbe
*********************************************/
#ifndef GOTOXY_H
#define GOTOXY_H 1

#include <conio.h>
#include <dos.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <cstring>

#define umlauta       132
#define umlautu       129
#define umlauto       148
#define S_ARROW_UP    24
#define S_ARROW_DOWN  25
#define S_ARROW_RIGHT 26 
#define S_ARROW_LEFT  27
#define ARROW_LEFT    17
#define ARROW_RIGHT   16
#define ARROW_DOWN    31
#define ARROW_UP      30
#define HOT_S         225
#define BLACK         0x00
#define BLUE          0x01
#define GREEN         0x02
#define CYAN          0x03
#define RED           0x04
#define MAGENTA       0x05
#define BROWN         0x06
#define LIGHTGRAY     0x07
#define DARKGRAY      0x08
#define LIGHTBLUE     0x09
#define LIGHTGREEN    0x0A
#define LIGHTCYAN     0x0B
#define LIGHTRED      0x0C
#define LIGHTMAGENTA  0x0D
#define YELLOW        0x0E
#define WHITE         0x0F

#define LEFT_KEY      75
#define RIGHT_KEY     77
#define UP_KEY        72
#define DOWN_KEY      80

#define ENTER_KEY     0x0D

int clrscr();

void gotoxy( short x, short y );

void setcolor( unsigned short color = 0x0F ); // default Color is WHITE


int clrscr()
{
    HANDLE hndl = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo( hndl, &csbi );
    DWORD written;
    DWORD N = csbi.dwSize.X * csbi.dwCursorPosition.Y +
    csbi.dwCursorPosition.X + 1;
    N=2000;
    COORD curhome = { 0, 0 };
    
    FillConsoleOutputCharacter( hndl, ' ', N, curhome, &written );
    csbi.srWindow.Bottom -= csbi.srWindow.Top;
    csbi.srWindow.Top = 0;
    SetConsoleWindowInfo( hndl, TRUE, &csbi.srWindow );
    SetConsoleCursorPosition( hndl, curhome );
    
    return 0;
}

void gotoxy( short x, short y )
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x, y };
    hConsoleOutput = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleCursorPosition( hConsoleOutput, Cursor_an_Pos );
}

void setcolor( unsigned short color )
{
    HANDLE hCon = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( hCon, color );
}

#endif
