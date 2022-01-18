#ifndef HEILER_H
#define HEILER_H
// Autor: Prof. DI Christian Czaker
#include "Bauer.h"

class Heiler : public Bauer
{
protected:
	char showShield; // used as BOOL 0/1
	
public:
	Heiler();
	void Magic();
	void Show();
	void Attack();
	int BeAttacked();
    
	void ShowStart();
};

#endif
