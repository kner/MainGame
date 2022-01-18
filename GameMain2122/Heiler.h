#ifndef HEILER_H
#define HEILER_H
// Autor: Prof. DI Christian Czaker
#include "Bauer.h"

class Heiler : public Bauer
{
protected:
	char showShield; // used as BOOL 0/1
	
public:
	Heiler()
	{
		strcpy(autorName, "Prof. Czaker");
		strcpy(heroName, "Heiler");

		life       = 16;
		mana       = MAX_MANA/2;
		damage     = STD_DAMAGE/2;
		range      = 20;
		shield     = (MAX_LIFE*2)/3;
		showShield =  1;
		weaponC    = '#';
		armorC     = '.';
		move       = MAX_MOVE/2+2;
		bodyCol    = LIGHTMAGENTA;
		headCol    = YELLOW;
		handCol    = LIGHTBLUE;
		legCol     = MAGENTA;
		weaponCol  = LIGHTCYAN;
		width      = SHIELD_RAD;
	}
    void Magic()
    {
    	if(mana<MAX_MANA/4) return;	// Mana to low
    	
    	mana-=MAX_MANA/4;
    	life += (MAX_LIFE*2)/3;
    	ShowLife();
    }
    void Show()
    {
    	// show shield
    	if(shield>0 && showShield)
    	{
	    	setcolor(WHITE);
	    	Kreis(x,height-hand/2-1,SHIELD_RAD,armorC);
	    }
	    else if(showShield)
	    {
	    	Kreis(x,height-hand/2-1,SHIELD_RAD,' ');
	    	showShield = 0;
	    }
	    
    	Bauer::Show();
    	
    	// show TOEs
		setcolor(legCol);
    	Draw(x+step-1, 0, bodyC); // Bein 1
		Draw(x-step-1, 0, bodyC); // Bein 2
    	
    }
    void Attack()
    {
    	Bauer::Attack();
    	Show();
    }
    int BeAttacked()
    {
    	int damage = enemy->DoAttack();
    	if(shield)
    	{
    		if(damage<shield)
    		{
    			shield -= damage;
    			ShowLife();
    			return 0;
    		}
    		width  = hand; // With shield the width = SHIELD_RAD!!!
    		damage -= shield;
    		shield = 0;
    	}
    	
    	life -= damage;
    	ShowLife();
    	return damage;
    }
    
    void ShowStart()
	{
		int   saveShield  = shield;
		int   endPosition = x;
		int   saveMove    = move;
		int   saveRange   = range;
		char  saveWeapenC = weaponC;
		short saveColor   = weaponCol;
		
		Clear();
		showShield = 0;		// remove shield
		shield  = 0;
		move    = WIDTH;	// remove the moveLimit
		weaponC = ' ';		// show no weapon, just walk
		x       = MIDDLE-width;	// set x to max (border)
		
		
		ShowLife();				// don't show shield value
		Move(x-endPosition);	// walk to normal position
		move    = saveMove;		// reset moveLimit
		
		
		// animate Weapon
		weaponC   = '|';
		weaponCol = WHITE;
		for(range=5;range<saveRange/3;range++)
		{
			Show();		// Show Hero with little Weapon
			Sleep(30);
		}
		weaponC   = '+';
		weaponCol = LIGHTGRAY;
		for(;range<(saveRange*2)/3;range++)
		{
			Show();		// Show Hero with medium Weapon
			Sleep(30);
		}
		weaponC   = saveWeapenC;	// reset weapon
		weaponCol = saveColor;
		for(;range<saveRange;range++)
		{
			Show();		// Show Hero with normal Weapon
			Sleep(30);
		}
		Sleep(500);
		
		// Animate Create Shield
		for(int shieldRad=1; shieldRad<=SHIELD_RAD; shieldRad++)
		{
			shield = (saveShield*shieldRad)/SHIELD_RAD;
			Show();
			ShowLife();
			setcolor(WHITE);
		    Kreis(x,height-hand/2-1,shieldRad,armorC);
			Sleep(100);
			Kreis(x,height-hand/2-1,shieldRad,' ');
		}
		showShield = 1;
		shield     = saveShield;
		Show();			// Show Hero with Weapon & Shield
		ShowLife();		// Show Life & Shield
		Sleep(500);
	}
};

#endif
