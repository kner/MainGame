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
	Krieger()
	{
		strcpy(autorName, "Prof. Czaker");
		strcpy(heroName, "Krieger");

		life       = MAX_LIFE;
		damage     = STD_DAMAGE;
		armor      = STD_DAMAGE/4;
		range      = 14;
		mana       = MAX_MANA/10*3;
		move       = MAX_MOVE/2+1;
		block      = 0;

		bodyCol    = LIGHTGRAY;
		headCol    = WHITE;
		handCol    = WHITE;
	}
  /**/
	void ShowMan()
	{
		setcolor(headCol);
		Kreis(x,   height+4,    3,    bodyC);	// Kopf
		Linie(x-4, height+5, +8, -1,  armorC);	// Helm
		Linie(x-4, height+5, +4, +3,  armorC);	// Helm
		Linie(x+4, height+4, -3, +3,  armorC);	// Helm
		
        setcolor(bodyCol);
		Linie(x+1, leg+1, +1, leg-2, armorC);	// Ruecken
		Linie(x+2, leg+1, +1, leg-2, armorC);	// Ruecken
		Linie(x-1, leg+1, -1, leg-2, armorC);	// Brust
		Linie(x-2, leg+1, -1, leg-2, armorC);	// Brust
		Linie(x-1, leg,   -1, -1,    bodyC);	// Rock
		Linie(x+1, leg,   +1, -1,    bodyC);	// Rock
		Linie(x-1, leg+1, +2,  0,    bodyC);	// Guertel
		Linie(x-2, height, +4,  0,    armorC);	// Schulter
		
		setcolor(legCol);
    	Linie(x, leg,     +step, -leg,  bodyC); // Bein 1
		Linie(x, leg,     -step, -leg,  bodyC); // Bein 2
		
		setcolor(handCol);
		Linie(x, height-1,       0,  -hand, bodyC); // Oberarm
		Linie(x, height-1-hand, -hand,   0, bodyC); // Unterarm
    }
    
	void ShowBlocking()
	{
		setcolor(headCol);
		Kreis(x,   height+4-hand,    3,    bodyC);	// Kopf
		Linie(x-4, height+5-hand, +8, -1,  armorC);	// Helm
		Linie(x-4, height+5-hand, +4, +3,  armorC);	// Helm
		Linie(x+4, height+4-hand, -3, +3,  armorC);	// Helm
		
        setcolor(bodyCol);
		Linie(x+1, leg+1-hand, +1, leg-2, armorC);	// Ruecken
		Linie(x+2, leg+1-hand, +1, leg-2, armorC);	// Ruecken
		Linie(x-1, leg+1-hand, -1, leg-2, armorC);	// Brust
		Linie(x-2, leg+1-hand, -1, leg-2, armorC);	// Brust
		Linie(x-1, leg-hand,   -1, -1,    bodyC);	// Rock
		Linie(x+1, leg-hand,   +1, -1,    bodyC);	// Rock
		Linie(x-1, leg+1-hand, +2,  0,    bodyC);	// Guertel
		Linie(x-2, height-hand, +4,  0,    armorC);	// Schulter
		
		setcolor(legCol);
    	Linie(x,      0,     0,     hand,  bodyC); // Bein 1
    	Linie(x,      0,     hand,  0,     bodyC); // Bein 1
		Linie(x,      hand,  -hand, 0,     bodyC); // Bein 2
		Linie(x-hand, hand,  0,     -hand, bodyC); // Bein 2
		
		setcolor(handCol);
		Linie(x, height-1-hand,   -3, -hand, bodyC); // Oberarm
		Linie(x-3, height-1-hand*2, -hand, hand, bodyC); // Unterarm
		
		setcolor(weaponCol);
		Linie(x-hand-3, height-1-hand, 2, range/2, weaponC);

    }	// END Blocking()
    
    /***/
    int BeAttacked()
    {
    	int damage = enemy->DoAttack();
    	
    	if( damage < armor )
		{
			ShowLife();
			return 0;
		}
    	
    	damage -= armor;
    	life -= damage;
    	ShowLife();
    	return damage;
    }
    
    void ShowBlock()
    {
    	Clear();
    	x += 3;
    	ShowBlocking();
    	width += 3;
    }
    
    void ClearBlock()
    {
        char saveBody   = bodyC;
        char saveWeapon = weaponC;
        char saveArmor  = armorC;
        bodyC   = ' ';
        weaponC = ' ';  
        armorC  = ' ';
        ShowBlocking();
        bodyC   = saveBody;
      	weaponC = saveWeapon;
		armorC  = saveArmor;
		 
		x -= 3; 
    	Show();
    	width -= 3;
    }
    
    void ShowStart()
	{
		Show();
		ShowAttack();
		Clear();
		x=-x;
		SetLeft2Right(side=='l'?'r':'l');
		Show();
		ShowAttack();
		Clear();
		x=-x;
		SetLeft2Right(side=='l'?'r':'l');
		Show();
		ShowAttack();
		Show();
		Sleep(500);
	}
};

#endif
