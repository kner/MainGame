#ifndef KRIEGER_H
#define KRIEGER_H
// Autor: Prof. DI Christian Czaker
#include "Bauer.h"

class Krieger : public Bauer
{
protected:
	int  armor;		// reduces the damage Heros gets
	char block;		// is blocking active?
public:
	Krieger();
  /**/
	void ShowMan();
    
    void ShowBlocking();
    
    /***/
    int BeAttacked();
    
    void ShowBlock();
    
	void ClearBlock();
    
    void ShowStart();
};

#endif
