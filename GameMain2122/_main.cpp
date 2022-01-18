#include <iostream>
#include <conio.h>
// nur zum Testen:
// Schriftgröße anpassen und
// Konsolen Fenster => Größe 161 x 50 einstellen
#include "Bauer.h"
#include "Heiler.h"
#include "Krieger.h"
#include "ManBat.h"

// CZAKER SAGT #include "Hero.h" // for each Hero

#define STRING_LEN 80

using namespace std;

char zeile[WIDTH+1];

char* InitZeile(char zeichen)
{
	int i;
	for(i=0; i<WIDTH; i++)
	{
		zeile[i] = zeichen;
	}
	zeile[WIDTH] = 0;
	
	return zeile;
}

void AusgabeWaehleKrieger();
void AusgabeWaehleFarbe();

int main(int argc, char *argv[])
{
	char  taste;
	int   i, index, wahl, spieler, anzahlFarben=15;
	short farbe, alteFarbe;
	
	short farben[15] = { LIGHTBLUE,  BLUE,  MAGENTA, LIGHTMAGENTA,
                         LIGHTRED,   RED,   CYAN,    LIGHTCYAN,
                         LIGHTGREEN, GREEN, BROWN,   YELLOW,
                         WHITE,      LIGHTGRAY,      DARKGRAY };
			   
    //BEGIN **+******************************
    //BEGIN ** Spielfeld-Groesse festlegen **
    //BEGIN *********************************
    char setConsole[STRING_LEN];
    sprintf(  setConsole, 
              "mode con cols=%d lines=%d",
              WIDTH+1, BOTTOM+MENU);
    system( setConsole );
    gotoxy(0,0);
    cout << InitZeile(' ');
    gotoxy(0,1);
    cout << InitZeile(' ');
    //END **+******************************
    //END ** Spielfeld-Groesse festlegen **
    //END *********************************
    
    //CZAKER+-SAGT-++-CZAKER-SAGT-+-CZAKER-SAGT-+-CZAKER-SAGT--+CZAKER
    //CZAKER|                                                  |CZAKER
    //CZAKER|  die ANZAHL aller KRIEGER in "anzahl" speichern  |CZAKER
    //CZAKER|                                                  |CZAKER
    //CZAKER+-SAGT-++-CZAKER-SAGT-+-CZAKER-SAGT-+-CZAKER-SAGT--+CZAKER
    int anzahl = 4;
    //CZAKER-SAGT-ENDE
    //CZAKER-SAGT-ENDE

	Bauer* x[2];	// 0..Links / 1..Rechts
    Bauer* alle[anzahl];
    
    do  // while("Nochmal (j/n)" => 'j')
	{

        //BEGIN **+******************
        //BEGIN ** Spieler Auswahl **
        //BEGIN **********************
		wahl=0;
        for(spieler=0; spieler<2; spieler++)
        {
    	    //CZAKER+-SAGT---CZAKER-SAGT---CZAKER-SAGT---CZAKER-SAGT-+CZAKER
            //CZAKER|                                                |CZAKER
            //CZAKER|   hier ALLE KRIEGER im Vektor "alle" anlegen   |CZAKER
            //CZAKER|                                                |CZAKER
            //CZAKER+-SAGT---CZAKER-SAGT---CZAKER-SAGT---CZAKER-SAGT-+CZAKER
			
			alle[anzahl-4] = new Bauer();
            alle[anzahl-3] = new Heiler();
            alle[anzahl-2] = new Krieger();
			alle[anzahl-1] = new ManBat();
			//CZAKER-SAGT-ENDE
            //CZAKER-SAGT-ENDE
    		
    		AusgabeWaehleKrieger();
    	    
    	    gotoxy(MIDDLE-7,1);
    	    cout << " 'n'<-   ->'m'";
    	    gotoxy(MIDDLE-7,3);
    	    cout << "Select  'Enter'";
    	    Circle(MIDDLE,(BOTTOM+MENU+TOP)/2,(BOTTOM+MENU-TOP)/2, '?');
    	    
    		do
    		{
    		    for(i=-2; i<=2; i++)
    		    {
    		    	index=wahl+i;
    		    	if( index<0       ) continue;
    		    	if( index>=anzahl ) continue;
    				alle[index]->SetLeft2Right(i<=0?'l':'r');
    				switch(i)
    				{
    					case  0: alle[index]->SetX(      0    ); break;
    					case -1:
    					case +1: alle[index]->SetX( MIDDLE/2  ); break;
    					case -2:
    					case +2: alle[index]->SetX((MIDDLE*3)/4); break;			
    				}
					setcolor(WHITE);
    		    	alle[index]->ShowName();
    		    }
    			
    			taste = getch(); // Select Krieger
    			
    		    for(i=-2; i<=2; i++)
    		    {
    		    	index=wahl+i;
    		    	if( index<0       ) continue;
    		    	if( index>=anzahl ) continue;
    		    	alle[index]->ClearName();
    			}
    			if( (taste=='m'||taste=='M'||taste==RIGHT_KEY) && wahl<anzahl-1 )
    			{
    				wahl++;
    			}
    			if( (taste=='n'||taste=='N'||taste==LEFT_KEY)  && wahl>0        )
    			{
    				wahl--;
    			}
    		}
    		while(taste!=ENTER_KEY);
    		
    		// Lösche alle nicht verwendete Heros
    		for(i=0; i<anzahl; i++)
    			if(i != wahl)
    				delete(alle[i]);
    				
    		// CLEAR Kreis der KRIEGER Auswahl
    	    Circle(MIDDLE,(BOTTOM+MENU+TOP)/2,(BOTTOM+MENU-TOP)/2, ' ');
    	    
    		x[spieler] = alle[wahl];
    		//for(i=0; i<anzahl; i++) if(i!=wahl) delete alle[i];
    	
    		x[spieler]->SetX(DISTANCE_2_CENTER);
    		x[spieler]->SetLeft2Right(spieler?'r':'l');
    		
    	    //COLOR *********************
    	    //COLOR ** Spieler Auswahl **
    	    //COLOR *********************
    	    farbe=0;
            
            AusgabeWaehleFarbe();
            
    	    gotoxy(MIDDLE-7,1);
    	    cout << " 'n'<-   ->'m'";
    	    gotoxy(MIDDLE-7,3);
    	    cout << "Select   ^ 'j' ";
    	    gotoxy(MIDDLE-7,5);
    	    cout << " Done   'Enter'";

    		x[spieler]->Show();

    	    for(i=0;i<3;i++)
    	    {
                gotoxy(MIDDLE-4,BOTTOM/2);
                switch(i)
    			{
					case 0: cout << "H E A D"; break;
					case 1: cout << "B O D Y"; break;
					case 2: cout << "Arm & Bein"; break;
                }

    			do
    			{
    				taste=getch();
    				
    				if( taste==ENTER_KEY ) break;
    	
    				if( (taste=='m'||taste=='M'||taste==RIGHT_KEY) )
    				{
    					farbe=(farbe+1)%anzahlFarben;
    				}
    				if( (taste=='n'||taste=='N'||taste==LEFT_KEY)  )
    				{
    					farbe=(farbe+anzahlFarben-1)%anzahlFarben;
    				}
    				
    				switch(i)
    				{
    					case 0: x[spieler]->SetColorHead(farben[farbe]); break;
    					case 1: x[spieler]->SetColorBody(farben[farbe]); break;
    					case 2: x[spieler]->SetColorHand(farben[farbe]);
    					        x[spieler]->SetColorLeg (farben[farbe]); break;
    				}
    				x[spieler]->Show();
    			}
    			while(   taste!='j' && taste!=DOWN_KEY 
                      && taste!='J' && taste!=UP_KEY  );

                gotoxy(MIDDLE-4,BOTTOM/2);
                cout << "             ";
    			
    			if( taste==ENTER_KEY ) break;
    		}
    		x[spieler]->Clear();
    	    gotoxy(MIDDLE-7,1);
    	    cout << "               ";
    	    gotoxy(MIDDLE-7,3);
    	    cout << "               ";
    	    gotoxy(MIDDLE-7,5);
    	    cout << "               ";
    	}	// END for(spieler)
    	
        for(i=0; i<10;i++) // CLEAR MENU
        {
        	gotoxy(0,i);
    		cout << InitZeile(' ');
        }
        //END **+******************
        //END ** Spieler Auswahl **
        //END **********************
	    
		x[0]->Vs(x[1]);
	    x[1]->Vs(x[0]);
	    x[0]->ShowLife();
	    x[0]->ShowStart();
	    x[1]->ShowLife();
		x[1]->ShowStart();
		x[0]->Show();
	    x[1]->Show(); 
				

	    //BEGIN **+********
	    //BEGIN ** FIGHT **
	    //BEGIN ***********
		gotoxy(0,BOTTOM+1);
		setcolor(GREEN);
		cout << InitZeile('=');	
		
		gotoxy(10,BOTTOM+4);
		cout << "      Angriff ... a"
			 << "      Magie ... m"
			 << "      Rueckwaerts ... r"
			 << "      Vorwaerts ... v"
			 << "              EXIT ... x";
			 
		gotoxy(10,BOTTOM+5);
		cout << "                  a"
			 << "                s"
			 << "                    - d"
			 << "                  + f";
			 
		i = 1;
		do
		{
			setcolor(WHITE);
	        gotoxy(MIDDLE/2+i*MIDDLE-5,BOTTOM+2);
	        cout << "              ";
	        i++;
	        i=i%2;
	        gotoxy(MIDDLE/2+i*MIDDLE-5,BOTTOM+2);
	        cout << "Aktion: ";
	        taste = getche();
	        switch(taste)
	        {
	            case 'a':
				case 'A': x[i]->Attack(); break;
	            case 's':
	            case 'm':
				case 'M': x[i]->Magic(); break;
	            case 'f':
	            case 'v':
				case 'V': x[i]->Move(+100); break;
	            case 'd':
	            case 'r':
				case 'R': x[i]->Move(-100); break;
				case '+': x[i]->Move(1); break;
				case '-': x[i]->Move(-1); break;
	        }
	    }
	    
	    while( taste != 'x'        && 
		       x[0]->GetLife() > 0 && 
			   x[1]->GetLife() > 0 );
	
	    //END **+********
	    //END ** FIGHT **
	    //END ***********
		
		setcolor(YELLOW);
		
	    gotoxy(MIDDLE/2+i*MIDDLE-5,BOTTOM+2);
	    cout << "              ";
	    
		x[0]->ShowDeath();
		x[1]->ShowDeath();
		
		setcolor(WHITE);
		
		// Unentschieden
		if( x[0]->GetLife() > 0 && x[1]->GetLife() > 0 )
		{
			gotoxy(MIDDLE-10,BOTTOM+2);
			setcolor(YELLOW);
			cout << "U N E N T S C H I E D E N";
		}
		else if( x[0]->GetLife() > 0 ) // 0 wins
		{
			x[0]->ShowVictory();
			gotoxy(MIDDLE/2-8,BOTTOM+2);
			cout << "L E F T      W I N S";
		}
		else if( x[1]->GetLife() > 0 ) // 1 wins
		{
			x[1]->ShowVictory();
			gotoxy(MIDDLE+MIDDLE/2-8,BOTTOM+2);
			cout << "R I G H T     W I N S";
		}
		else	// both are dead
		{
			gotoxy(MIDDLE-20,BOTTOM+2);
			setcolor(RED);
			cout << "N O    W I N N E R  -  A L L    D E A D";
		}
		setcolor(WHITE);
		gotoxy(MIDDLE-5,BOTTOM+6);
		cout << "Nochmal (j/n): ";
		//fflush(stdin);
		do
		{
		  taste = getche();
        }
        while( taste !='j' && taste!='n' && taste !='J' && taste!='N' );
        
		x[0]->Clear();
		x[1]->Clear();
		x[0]->ClearDeath();
		x[1]->ClearDeath();
		delete x[0];
		delete x[1];
    
	    for(i=0; i<=BOTTOM;i++) // CLEAR OLD GAME-MENU
	    {
	    	gotoxy(0,BOTTOM+i);
			cout << InitZeile(' ');
	    }
	}
	while(taste=='j' || taste=='J');
	setcolor(WHITE);
	return 0;
}

void AusgabeWaehleKrieger()
{
    	    setcolor(WHITE);
    	    
    	    gotoxy(20,0); cout << " W      W    a  e    h       l";
    	    gotoxy(20,1); cout << " W      W    e  a    h       l";
    	    gotoxy(20,2); cout << " W  WW  W            h       l";
    	    gotoxy(20,3); cout << " W  WW  W    aea e   h hh    l    eee";
    	    gotoxy(20,4); cout << " W W  W W   e   ae   hh  h   l   e   e";
    	    gotoxy(20,5); cout << " WW    WW   a    e   h    h  l   eeee";
    	    gotoxy(20,6); cout << " WW    WW   e   ae   h    h  l   e";
    	    gotoxy(20,7); cout << " W      W    aea e   h    h   ll  eeee";
    
    	    gotoxy(99,0); cout << " K     K           i       ";
    	    gotoxy(99,1); cout << " K    K            i       ";
    	    gotoxy(99,2); cout << " K   K                     ";
    	    gotoxy(99,3); cout << " K  K     r rrr   iii   eee    ggg g   eee   r rrr";
    	    gotoxy(99,4); cout << " K KK     rr   r   i   e   e  g   gg  e   e  rr   r";
    	    gotoxy(99,5); cout << " KK  K    r        i   eeee   g    g  eeee   r";
    	    gotoxy(99,6); cout << " K    K   r        i   e      g   gg  e      r";
    	    gotoxy(99,7); cout << " K     K  r       iii   eeee   ggg g   eeee  r";
    	    gotoxy(99,8); cout << "                                 g";
    	    gotoxy(99,9); cout << "                            ggggg";
}

void AusgabeWaehleFarbe()
{
            setcolor(YELLOW);
            
    	    gotoxy(20,0); cout << " W      W    a  e    h       l";
    	    gotoxy(20,1); cout << " W      W    e  a    h       l";
    	    gotoxy(20,2); cout << " W  WW  W            h       l";
    	    gotoxy(20,3); cout << " W  WW  W    aea e   h hh    l    eee";
    	    gotoxy(20,4); cout << " W W  W W   e   ae   hh  h   l   e   e";
    	    gotoxy(20,5); cout << " WW    WW   a    e   h    h  l   eeee";
    	    gotoxy(20,6); cout << " WW    WW   e   ae   h    h  l   e";
    	    gotoxy(20,7); cout << " W      W    aea e   h    h   ll  eeee";
    
    	    gotoxy(99,0); cout << " FFFFFFF                 b";
    	    gotoxy(99,1); cout << " F                       b";
    	    gotoxy(99,2); cout << " F                       b";
    	    gotoxy(99,3); cout << " F        aaa a  r rrr   b bbb    eee              ";
    	    gotoxy(99,4); cout << " FFFFFF  a   aa  rr   r  bb   b  e   e             ";
    	    gotoxy(99,5); cout << " F       a    a  r       b    b  eeee              ";
    	    gotoxy(99,6); cout << " F       a   aa  r       bb   b  e                 ";
    	    gotoxy(99,7); cout << " F        aaa a  r       b bbb    eeee             ";
    	    gotoxy(99,8); cout << "                                                   ";
    	    gotoxy(99,9); cout << "                                                   ";
}

