
// Autor: Prof. DI Christian Czaker

#include <string.h>
#include "gotoxy.h"
#include "Bauer.h"
// Czaker
using namespace std;

	Bauer::Bauer()
	{
		x = MIDDLE - DISTANCE_2_CENTER;
		Init();
	}   
	Bauer::Bauer(int x0)
	{
		x = x0;
		Init();
	}
	void Bauer::Init()
	{
		strcpy(autorName, "Prof. Czaker");
		strcpy(heroName, "Bauer");

		firstClearName  = 1;
		side       = 'l';
		bodyC      = 'B';
		weaponC    = 'W';
		armorC     = '#';
		step       =  2;
		
		height     = 20;  // Hoehe bis Schulter
        leg        = 10;  // Huefthoehe = Beinlaenge
        hand       =  5;  // Unterarm- / Oberarm-Laenge
        width      =  hand;  // Range of getting damaged
				
		life       = MAX_LIFE/2;
		mana       =  1;
		shield     =  0;
		damage     = STD_DAMAGE;
		range      = 30;
		move       = MAX_MOVE;
		
		bodyCol    = LIGHTGREEN;
		headCol    = BROWN;
		handCol    = LIGHTBLUE;
		legCol     = BLUE;
		weaponCol  = YELLOW;
	}
	void Bauer::Vs(Bauer* other) { enemy=other; }
	
	void Bauer::SetLeft2Right( char  right ) { side      = right; }

	void Bauer::SetCharBody(   char  body  ) { bodyC     = body; }
	void Bauer::SetColorBody(  short color ) { bodyCol   = color; }
	void Bauer::SetColorHead(  short color ) { headCol   = color; }
	void Bauer::SetColorHand(  short color ) { handCol   = color; }
	void Bauer::SetColorLeg(   short color ) { legCol    = color; }
	void Bauer::SetColorWeapon(short color ) { weaponCol = color; }
	int  Bauer::GetX() { return x; }
	
	void Bauer::SetX(int x0)
	{
		if(x0<0) x0=0;
		if(x0>MIDDLE-5) x0=MIDDLE-5;
		x = x0;
	}
	int  Bauer::GetLife() { return life; }
	char Bauer::GetBody() { return bodyC; }
		
	void Bauer::Move(int wohin)
    {
    	// move = speed = range of movement
        if(wohin > +move) wohin = +move;
        if(wohin < -move) wohin = -move;
        
        // positiv wohin => ZUR MITTE
        for(int i=0; i<wohin; i++)
        {
            if( x<=-MIDDLE+width ) break;
            if( x + enemy->x <= MIN_DISTANCE
			    + width + enemy->width ) break;
            Clear();
            x--;                // Move Fighter
            step = (step+1)%3;
            Show();
            Sleep(SLEEP_MOVE);
        }
        // negativ wohin => NACH AUSSEN
        for(int i=0; i>wohin; i--)
        {
            if( x >= MIDDLE-width ) break;
            Clear();
            x++;                // Move Fighter
            step = (step+1)%3;
            Show();
            Sleep(SLEEP_MOVE);
        }
        Clear();
        step = 2;
        Show();
        enemy->Show();
    }
    
	void Bauer::ShowLife()
	{
		int i;
		short x,y;
		char zeile[WIDTH+1];
		for(i=0; i<WIDTH;i++) zeile[i]=' ';
		zeile[WIDTH]=0;
		if(side == 'l')
		{
			y=1;
			x=1;
		}
		else
		{
			y=2;
			x=MIDDLE;
		}
		gotoxy(0,y);
		cout << zeile;	// Clear Life
		gotoxy(0,y+2);
		cout << zeile;	// Clear Mana
		
		if( life > 15)     setcolor(GREEN);
		else if( life > 7) setcolor(YELLOW);
		else               setcolor(RED);
		gotoxy(x,y);
		if( life <= 0 )
		{
			cout << "+ DU BIST TOT +";
		}	
		else
		{
			// LIFE
			for(i=0;i<life;i++) zeile[i]='#';
			zeile[life]=0;
			cout << "Life: "<<zeile;
			// SHIELD
			setcolor(WHITE);
			for(i=0;i<shield;i++) zeile[i]='#';
			zeile[shield]=0;
			cout << zeile;
		}
		
		setcolor(LIGHTCYAN);
		for(i=0;i<mana;i++) zeile[i]='#';
		zeile[mana]=0;
		gotoxy(x,y+2);
		cout << "Mana: "<<zeile;
	}
	void Bauer::ShowName() // Nur f�r "W�hle Krieger"
	{
		Text(x,-2,heroName);
		Text(x,-3,"by");
		Text(x,-4,autorName);
		Show();
	}
	void Bauer::ClearName() // Nur f�r "W�hle Krieger"
	{
		if(firstClearName)	// nur beim ersten Aufruf!!!
		{
			firstClearName=0;	// dann nie wieder
			
			for(int i=0; i<80; i++)
			{
				if( heroName[i]  ) heroClear[i]  = ' ';
				else               heroClear[i]  = 0;
				if( autorName[i] ) autorClear[i] = ' ';
				else               autorClear[i] = 0;
			}
		}
		Text(x,-2,heroClear);
		Text(x,-3,"  ");
		Text(x,-4,autorClear);
		Clear();
	}
	void Bauer::Show()
	{
        ShowMan();
        ShowWeapon();
    }
    void Bauer::Clear()
    {
        char saveBody   = bodyC;
        char saveWeapon = weaponC;
        char saveArmor  = armorC;
        bodyC   = ' ';
        weaponC = ' ';  
        armorC  = ' ';
        Show();
        bodyC   = saveBody;
      	weaponC = saveWeapon;
		armorC  = saveArmor;   
    }
	void Bauer::ShowMan()
	{
		setcolor(headCol);
		Kreis(x,   height+4,    3,   bodyC);    // Kopf
		
        setcolor(bodyCol);
		Linie(x+1, leg+1, +1, leg-2, bodyC);    // Ruecken
		Linie(x-1, leg+1, -1, leg-2, bodyC);    // Brust
		Linie(x-1, leg,   -1, -1,    bodyC);    // Rock
		Linie(x+1, leg,   +1, -1,    bodyC);    // Rock
		Linie(x-1, leg+1, +2,  0,    bodyC);    // Guertel
		Linie(x-2, height, +4,  0,    bodyC);    // Schulter
		
		setcolor(legCol);
    	Linie(x, leg,     +step, -leg,  bodyC); // Bein 1
		Linie(x, leg,     -step, -leg,  bodyC); // Bein 2
		
		setcolor(handCol);
		Linie(x, height-1,       0,  -hand, bodyC); // Oberarm
		Linie(x, height-1-hand, -hand,   0, bodyC); // Unterarm
    }
    void Bauer::ShowWeapon()
    {	// Ausgangspunkt=Ende Hand
		ShowWeapon( 0, range, weaponC);
	}
    void Bauer::ShowWeapon(int dx, int dy, char zeichen)
    {
		setcolor(weaponCol);
		// Waffe: dx 1:1  /  dy 1:2 verzerrt !!!
		Linie(x-hand, height-1-hand, dx, dy/2, zeichen);
	}
		
	void Bauer::Attack()
	{
        enemy->ShowBlock();
        ShowAttack();
        enemy->BeAttacked();
        enemy->ClearBlock();
        enemy->Show();
    }
    
	void Bauer::ShowBlock()
	{
        // No Block implemented => do nothing
    }
	void Bauer::ClearBlock()
	{
        // No Block implemented => do nothing
    }
    
	void Bauer::ShowAttack()
	{
        int dx, dy;
		setcolor(weaponCol);
		
		for( dx=0,dy=range; dx<=dy;  )
		{
            ShowWeapon( -dx,  dy, ' ');
            dx++;
			if(dx*dx+dy*dy > range*range+1) dy--;
			ShowWeapon( -dx,  dy, weaponC);
			Sleep(40);
        }
		for( ; dy>0; )
		{
            ShowWeapon( -dx,  dy, ' ');
            dy--;
			if(dx*dx+dy*dy < range*range) dx++;
			ShowWeapon( -dx,  dy, weaponC);
			Sleep(20);
        }
        Sleep(200);
        ShowWeapon( -dx,  dy, ' ');
        ShowWeapon();
    }
    
    int Bauer::BeAttacked()
    {
    	int damage = enemy->DoAttack();
    	life -= damage;
    	ShowLife();
    	return damage;
    }
    
    int Bauer::DoAttack()
    {
    	if( x+enemy->x > enemy->width+hand+range)
			return 0;
    	return damage;
    }
    
    void Bauer::Magic()
	{
        ShowMagic();
        enemy->BeMagicAttacked();
        enemy->Show();
	}
	
    void Bauer::ShowMagic()
	{
		// No MAGIC => do nothing
	}
    
    int Bauer::BeMagicAttacked()
	{
		int damage = enemy->DoMagicAttack();
    	life -= damage;
    	ShowLife();
    	return damage;    	
	}
	
    int Bauer::DoMagicAttack()
	{
		// No MAGIC => no damage
		return 0;
	}
	
    void Bauer::ShowDeath()
    {
    	if( life > 0) return;  // still alive
    	
    	int yy = (height+leg)/2; // average height
    	char saveBody  = bodyC;
    	char saveArmor = armorC;
    	setcolor(RED);
    	Linie(x-3,yy,7,0,'+');
    	Sleep(200);
    	Linie(x-4,yy+2,9,-4,'+');
    	Sleep(200);
    	Linie(x-5,yy-4,11,+8,'+');
    	Sleep(500);
    	Linie(x-3,yy,7,0,'.');
    	Linie(x-4,yy+2,9,-4,'.');
    	Linie(x-5,yy-4,11,+8,'.');
    	bodyC  = ' ';
    	armorC = ' ';
    	Show();
    	Sleep(200);
    	bodyC  = saveBody;
    	armorC = saveArmor;
    	Show();
    	Sleep(200);
    	bodyC   = ' ';
    	weaponC = ' ';
    	armorC  = ' ';
    	Show();
    }
    
    void Bauer::ClearDeath()
    {
    	Linie(x-3,(height+leg)/2,7,0,' ');
    	Linie(x-4,(height+leg)/2+2,9,-4,' ');
    	Linie(x-5,(height+leg)/2-4,11,+8,' ');
    }
    
	void Bauer::ShowStart()   {}
	
    void Bauer::ShowVictory() {}
    
    void Bauer::Kreis(int x0, int y0, int radius, char zeichen)
	{
		int dx, dy;
		for( dx=0,dy=radius; dx<=dy; dx++ )
		{
			if(dx*dx+dy*dy > radius*radius+1) dy--;
			Draw(x0+dx,y0+dy,zeichen);
			Draw(x0+dx,y0-dy,zeichen);
			Draw(x0-dx,y0+dy,zeichen);
			Draw(x0-dx,y0-dy,zeichen);
			Draw(x0+dy,y0+dx,zeichen);
			Draw(x0+dy,y0-dx,zeichen);
			Draw(x0-dy,y0+dx,zeichen);
			Draw(x0-dy,y0-dx,zeichen);
		}
	}
	void Bauer::Linie(int x0, int y0, int dx, int dy, char zeichen)
	{
		int i,x,y;
		if( dx==0 && dy==0 )
		{
			Draw(x0,y0,zeichen);
			return;
		}
		if( dx*dx >= dy*dy ) // |dx| >= |dy|
		{
			if( dx < 0 )
			{
				x0 += dx;   y0 += dy;
				dx = -dx;   dy = -dy;
			}
			for(i=0; i<=dx; i++)
			{
                x = x0+i;
                y = int(round(y0+(i*dy*1.0)/dx));
				Draw(x, y, zeichen);
            }
		}
		else // |dy| > |dx|
		{
			if( dy < 0 )
			{
				x0 += dx;   y0 += dy;
				dx = -dx;   dy = -dy;
			}
			for(i=0; i<=dy; i++)
			{
                x = int(round(x0+(i*dx*1.0)/dy));
                y = y0+i;
				Draw(x, y, zeichen);
            }
		}
	}
	
	void Bauer::Draw(int x, int y, char zeichen)
	{
		short xx,yy;
		if(side == 'l') xx = (short)(MIDDLE - x);
		else            xx = (short)(MIDDLE + x);
		yy = (short)(BOTTOM - y);
		if(xx<0)      return;
		if(xx>=WIDTH) return;
		if(yy<=TOP)   return;
		if(yy>BOTTOM) return;
		gotoxy(xx,yy);
		cout << zeichen;
	}

	void Bauer::Text(int x, int y, const char* text )
	{
		size_t len = strlen(text);
		
		short xx,yy;
		if(side == 'l') xx = (short)(MIDDLE - x-len/2);
		else            xx = (short)(MIDDLE + x-len/2);
		yy = (short)(BOTTOM - y);
		gotoxy(xx,yy);
		cout << text;
	}
	
