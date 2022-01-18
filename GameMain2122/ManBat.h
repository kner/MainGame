#ifndef MANBAT_H
#define MANBAT_H
// Autor: Prof. DI Christian Czaker
#include "Bauer.h"

class ManBat : public Bauer
{
protected:
	int armor;
	char bodyC7, bodyC8;
public:
	ManBat()
	{
		strcpy(autorName, "Prof. Czaker");
		strcpy(heroName, "ManBat");

		life       = MAX_LIFE/3;
		damage     = STD_DAMAGE;
		armor      = 0;
		range      = 5;
		move       = MAX_MOVE;
		
		height     = 15;
		width      = 11;
		bodyCol    = LIGHTRED;
		headCol    = MAGENTA;
		handCol    = WHITE;
		weaponCol  = RED;     // blutige Z�hne in DoAttack()
		bodyC      = '|';
		bodyC7     = '/';
		bodyC8     = '\\';
		weaponC    = 'V';
		armorC     = 'O';
	}

  	void SetLeft2Right( char  right )
	{
		Bauer::SetLeft2Right( right );
		bodyC7 = side=='l' ? '/' : '\\';
		bodyC8 = side!='l' ? '/' : '\\';
	}
	void ClearHead(int dx)
	{
		char saveBodyC   = bodyC;
		char saveBodyC7  = bodyC7;
		char saveBodyC8  = bodyC8;
		char saveArmorC  = armorC;
		char saveWeaponC = weaponC;
		
		bodyC = bodyC7 = bodyC8 = armorC = weaponC = ' ';
	
		ShowHead(dx);
		
		bodyC   = saveBodyC;
		bodyC7  = saveBodyC7;
		bodyC8  = saveBodyC8;
		armorC  = saveArmorC;
		weaponC = saveWeaponC;
	}
	void ShowHead(int dx)
	{
		int x = this->x-dx;
		
		setcolor(headCol);
		Kreis(x,   height+5,    5,    bodyC);	// Kopf
		Linie(x-5, height+7,  0, +5,  bodyC);	// Ohren
		Linie(x-2, height+9, -2, +2,  bodyC7);	// Ohren
		Linie(x+5, height+7,  0, +5,  bodyC);	// Ohren
		Linie(x+2, height+9, +2, +2,  bodyC8);	// Ohren
		
		setcolor(WHITE);
		Draw( x+1, height+7,          armorC);	// Augen
		Draw( x-3, height+7,          armorC);	// Augen
		Draw( x+0, height+3,          weaponC);	// Z�hne
		Draw( x-2, height+3,          weaponC);	// Z�hne
	}
	void Show() { ShowMan(); }
	
	void ShowMan()
	{
		ShowHead(0);
		
		setcolor(handCol);
		Linie(x-3, hand, step, -hand, bodyC); // Bein
		Draw( x-3+step-1, 0, bodyC7);
		Draw( x-3+step-2, 0, bodyC8);
		Linie(x+3, hand, step, -hand, bodyC); // Bein
		Draw( x+3+step-1, 0, bodyC7);
		Draw( x+3+step-2, 0, bodyC8);
		setcolor(bodyCol);
		Kreis(x+6, leg, 5, bodyC7);	// Fl�gel angelegt
		Kreis(x-6, leg, 5, bodyC8);	// Fl�gel angelegt
	}
	void ShowWeapon() {}
	void Clear()
    {
        char saveBodyC7 = bodyC7;
        char saveBodyC8 = bodyC8;
        bodyC7 = ' ';
        bodyC8 = ' ';
        Bauer::Clear();
        bodyC7 = saveBodyC7;
        bodyC8 = saveBodyC8;
	}
    /***/
    int DoAttack()
    {
    	if( x+enemy->x > enemy->width+width+range+2) // +2= Z�hne
			return 0;
		
    	life += (damage+1)/2;
    	
    	StartHeadAttack();
    	setcolor(weaponCol);
        ShowBite();
    	Sleep(300);
    	ShowBite();
    	EndHeadAttack();
    	ShowLife();
    	return damage;
    }
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
    void Attack()
    {
    	Move(20);
    	Bauer::Attack();
    	Move(-8);
    }
    void StartHeadAttack()
    {
    	ClearHead(0);
    	int i;
    	for(i=1; i<range+width; i++)
    	{
    		ShowHead(i);
    		Sleep(10);
    		ClearHead(i);
    	}
    	Sleep(10);
    	ShowHead(range+width);
    }
    void EndHeadAttack()
    {
    	Sleep(200);
    	ClearHead(range+width);
    }
    void ShowBite()
    {
        // Z�hne ausfahren und wieder einfahren
    	Sleep(200);
		Draw( x-range-width,   height+2, weaponC);	// Z�hne
		Draw( x-range-width-2, height+2, weaponC);	// Z�hne
    	Sleep(200);
		Draw( x-range-width,   height+1, weaponC);	// Z�hne
		Draw( x-range-width-2, height+1, weaponC);	// Z�hne
    	Sleep(200);
		Draw( x-range-width,   height+0, weaponC);	// Z�hne
		Draw( x-range-width-2, height+0, weaponC);	// Z�hne
    	Sleep(10);
		Draw( x-range-width,   height+0, ' ');	// Z�hne l�schen
		Draw( x-range-width-2, height+0, ' ');	// Z�hne l�schen
    	Sleep(10);
		Draw( x-range-width,   height+1, ' ');	// Z�hne l�schen
		Draw( x-range-width-2, height+1, ' ');	// Z�hne l�schen
    	Sleep(10);
		Draw( x-range-width,   height+2, ' ');	// Z�hne l�schen
		Draw( x-range-width-2, height+2, ' ');	// Z�hne l�schen
    }
    void ShowAttack()
    {
    	StartHeadAttack();    	
    	ShowBite();
        EndHeadAttack();
    	Show();
    }
    void ShowStart()
	{
        char fluegel[4] = { bodyC7, '-', bodyC8 };
        int step=0; // Fl�gelstellung -1 / 0 / +1
        int xx, yy, len=2;
        
        Clear();
        
        for(xx=MIDDLE-5; xx>=x; xx--)
        {
            step = (step+2)%3-1;
            yy=(step-1)*2 + height;
            
            setcolor(bodyCol);
            Linie(xx-1, yy, -len, len*step, fluegel[-step+1]);
            Linie(xx+1, yy, +len, len*step, fluegel[+step+1]);
            setcolor(headCol);
            Draw( xx,   yy, 'O');
            Sleep(100);
            Linie(xx-1, yy, -len, len*step, ' ');
            Linie(xx+1, yy, +len, len*step, ' ');
            Draw( xx,   yy, ' ');
        }
        xx=x;
        yy=height;

        for(len=2; len<7; len++)
        {
            step = (step+2)%3-1;
            
            setcolor(bodyCol);
            Linie(xx-1, yy, -len, len*step, fluegel[-step+1]);
            Linie(xx+1, yy, +len, len*step, fluegel[+step+1]);
            setcolor(headCol);
            Draw( xx,   yy, 'O');
            Sleep(300);
            Linie(xx-1, yy, -len, len*step, ' ');
            Linie(xx+1, yy, +len, len*step, ' ');
            Draw( xx,   yy, ' ');
        }
        ShowHead(0);
        Sleep(400);
		ClearHead(0);
		
		x=-x;
		SetLeft2Right(side=='l'?'r':'l');
		
        ShowHead(0);
        Sleep(400);
		ClearHead(0);
        
		x=-x;
		SetLeft2Right(side=='l'?'r':'l');
		
        ShowHead(0);
        Sleep(400);
		ClearHead(0);
        Show();
		Sleep(500);
	}
	
	void ShowDeath()
	{
        if( life > 0 ) return;
        
        char fluegel[4] = { bodyC7, '-', bodyC8 };
        int step=0; // Fl�gelstellung -1 / 0 / +1
        int xx, yy, len=2;
        
        Bauer::ShowDeath();
        Bauer::ClearDeath();
        ManBat::Clear();
        
        
        for(xx=x; xx<MIDDLE+5; xx++)
        {
            step = (step+2)%3-1;
            yy=(step-1)*2 + height;
            
            setcolor(bodyCol);
            Linie(xx-1, yy, -len, len*step, fluegel[-step+1]);
            Linie(xx+1, yy, +len, len*step, fluegel[+step+1]);
            setcolor(headCol);
            Draw( xx,   yy, 'O');
            Sleep(100);
            Linie(xx-1, yy, -len, len*step, ' ');
            Linie(xx+1, yy, +len, len*step, ' ');
            Draw( xx,   yy, ' ');
        }
    }
};

#endif
