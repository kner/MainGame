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
    ManBat();

    void SetLeft2Right(char  right);
    void ClearHead(int dx);
    void ShowHead(int dx);
	void Show();
	
    void ShowMan();
	void ShowWeapon();
    void Clear();
    /***/
    int DoAttack();
    int BeAttacked();
    void Attack();
    void StartHeadAttack();
    void EndHeadAttack();
    void ShowBite();
    void ShowAttack();
    void ShowStart();
	
	void ShowDeath();
};

#endif
