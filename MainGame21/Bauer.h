#ifndef BAUER_H
#define BAUER_H
// Autor: Prof. DI Christian Czaker

#include <string.h>
#include "gotoxy.h"

#define DISTANCE_2_CENTER 30
#define MAX_MOVE          20
#define MIN_DISTANCE       2
#define MAX_LIFE          50
#define MAX_MANA          50
#define SLEEP_MOVE       100
#define STD_DAMAGE        10
#define SHIELD_RAD        11

// Czaker
using namespace std;

class Bauer
{
public:
    Bauer* enemy;
	int   x;		// Distance to Center // 0 = Middle
	char  side;		// Player is left (side='l') or right (side='r')
	int   height;	// From Ground to Shoulder
	int   width;	// From Center to front End of Body => (get damage)
	int   hand;		// length of the Hand
	int   leg;		// length of the Legs
	int   step;		// position of Feet while walking
	int   range;	// Make damage range = range of weapon animation
	int   life;		// Life-points >0 .. ok <=0 .. DEAD
	int   mana;		// Magical resource
	int   damage;	// make damage amount
	int   move;		// distance of one round
	int   shield;	// Shield-Points (absorb damage)
	char  bodyC, weaponC, armorC;	// Charakter to show ...
	short bodyCol, headCol, handCol, legCol, weaponCol; // Colors
	
	char  autorName[80],heroName[80],autorClear[80],heroClear[80];
	char  firstClearName;
		
public:
	Bauer();
	Bauer(int x0);
	void Init();
	void Vs(Bauer* other);
	
	virtual void SetLeft2Right(char  right);

	void SetCharBody(char  body);
	void SetColorBody(short color);
	void SetColorHead(short color);
	void SetColorHand(short color);
	void SetColorLeg(short color);
	void SetColorWeapon(short color);
	int  GetX();
	
	void SetX(int x0 = DISTANCE_2_CENTER);
	int  GetLife();
	char GetBody();
		
	virtual void Move(int wohin);
    
	virtual void ShowLife();
	virtual void ShowName();
	virtual void ClearName();
	virtual void Show();
	virtual void Clear();
	virtual void ShowMan();
	virtual void ShowWeapon();
	virtual void ShowWeapon(int dx, int dy, char zeichen);
		
	
	virtual void ShowBlock();
	virtual void ClearBlock();
    
	virtual void Attack();
	virtual void ShowAttack();
	virtual int BeAttacked();
	virtual int DoAttack();
    
	virtual void Magic();
	virtual void ShowMagic();
	virtual int BeMagicAttacked();
	virtual int DoMagicAttack();
	
	virtual void ShowDeath();
	virtual void ClearDeath();
    
	virtual void ShowStart();
	virtual void ShowVictory();
    
	void Kreis(int x0, int y0, int radius, char zeichen);
	virtual void Linie(int x0, int y0, int dx, int dy, char zeichen);
	void Draw(int x, int y, char zeichen);
	void Text(int x, int y, const char* text);
	
};	// END class Bauer

#endif
