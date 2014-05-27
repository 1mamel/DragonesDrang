#include <iostream>
#include <string>
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <conio.h>
#include <mmsystem.h>
#include <time.h>

using namespace std;

class timer {
private:
	unsigned long begTime;
public:
	void start() {
		begTime = clock();
	}

	unsigned long elapsedTime() {
		return ((unsigned long) clock() - begTime) / CLOCKS_PER_SEC;
	}

	unsigned long elapsedTimeDziesietny() {
		return ((unsigned long) clock() - begTime) / 100;
	}

	bool isTimeout(unsigned long seconds) {
		return seconds >= elapsedTime();
	}
};

class szablonPostaci
{
public:
	int opoznienieTekstu;
	int sila;
	int inteligencja;
	int zrecznosc;
	int budowa;
	int poziom;
	int doswiadczenie;
	int punktyDoRozdania;
	int maksymalneDoswiadczenie; 
	int zloto;
	int hp;
	int mp;
	int maxhp;
	int hppot;
	int mppot;
	int wybranyPoziom;
	int maxmp;
	int posiadanePrzedmioty[200];
	int posiadaneCzary[100];

	void resetujWartosci()
	{
		opoznienieTekstu=1000;
		sila=10;
		inteligencja=10;
		zrecznosc=10;
		budowa=10;
		poziom = 1;
		doswiadczenie = 0;
		punktyDoRozdania=0;
		maksymalneDoswiadczenie = 100; 
		zloto = 0;
		hp = 100;
		mp = 10;
		maxhp=100;
		hppot=5;
		mppot=5;
		wybranyPoziom = 0;
		maxmp=10;
		for (int i = 0; i<201;i++){
			posiadanePrzedmioty[i] = 0;}
		for (int j = 0; j<101;j++){
			posiadaneCzary[j] = 0;}
	}
	szablonPostaci();
};

szablonPostaci::szablonPostaci()
{
	opoznienieTekstu=1000;
	sila=10;
	inteligencja=10;
	zrecznosc=10;
	budowa=10;
	poziom = 1;
	doswiadczenie = 0;
	punktyDoRozdania=0;
	maksymalneDoswiadczenie = 100; 
	zloto = 0;
	hp = 100;
	mp = 10;
	maxhp=100;
	hppot=5;
	mppot=5;
	wybranyPoziom = 0;
	maxmp=10;
	for (int i = 0; i<201;i++){
		posiadanePrzedmioty[i] = 0;}
	for (int j = 0; j<101;j++){
		posiadaneCzary[j] = 0;}
}

class Gra 
{
public:
	char sciezka[100];
	int r[81][40];
	int sciana[81][40];
	int trudnoscPoziomu;
	int otwarteskrzynki;
	int iloscpotworow;
	int iloscskrzynek;
	int zapamietaj;
	int wygrana;
	int autozapis;
	int opusc;
	int wktora;
	int zdobyteZloto;
	int zabitepotwory;
	int ilestam;
	int wyszedlem;
	int zdobyteDoswiadczenie;
	double szybkoscPotwora,szybkoscGracza;
	int rodzajAnimacji;
	string nazwaitemu;
	string nazwaCzaru;
	ofstream plik;
	ifstream zplik;
	HANDLE hInput, hOutput;
	int rodzajPotwora,potdmgmax,potdmgmin,hpPotwora,potgold,typAtaku;
	int p1,p2,p3,p4;
	int rodzajMagii;
	bool czyZasiegowy;
	int crit;
	int wartoscPrzedmiotu;
	int wartoscCzaru;
	int obrona;
	int atak;
	int iZrecznosc;
	int iInteligencja;
	int iSila;
	int kosztMany;
	double przelicznik;
	int tempexp;
	int litera;
	int uzytyCzar;
	bool wykonanoRuch;
	char jaka;
	unsigned int gdzie;
	bool stanDefensywnyGracza,stanDefensywnyPotwora;
	int	turaPrzyspieszeniaGracza,turaSpowolnieniaGracza,turaPrzyspieszeniaPotwora,turaSpowolnieniaPotwora;

	string potw;
	int x;
	int respawnX;
	int y;
	int respawnY;
	int wybranyRuchGracza,wybranyRuchPotwora;
	int maksymalneHpPotwora;
	double timerPotwora, timerGracza, varSpowolnieniaPotwora,varPrzyspieszeniaPotwora,varAtakuPotwora,varObronyPotwora,varSpowolnieniaGracza,varPrzyspieszeniaGracza,varAtakuGracza,varObronyGracza;
	int czyTrafienieKrytyczne,dmg;
	char nick[100];
	int uzylhp;
	int uzylmp;
	int wybor;           
	string tempTekst1;
	string tempTekst2;
	string tempTekst3;
	unsigned char lewo;
	unsigned char prawo;
	unsigned char gora;
	unsigned char dol;
	unsigned char black;
	unsigned char white;
	unsigned char scianka;
	unsigned char wyjscie;
	unsigned char wejscie;
	unsigned char zycie;
	unsigned char krzyz;
	unsigned char doswiadczenie;
	unsigned char lewy_gorny;
	unsigned char lewy_dolny;
	unsigned char prawy_gorny;
	unsigned char prawy_dolny;
	unsigned char srodkowy;
	unsigned char poziomy_gorny;
	unsigned char poziomy_dolny;
	unsigned char pionowy_prawy;
	unsigned char pionowy_lewy;
	unsigned char skrzynka;
	unsigned char drzwi;
	unsigned char pionowa;
	unsigned char pozioma;
	szablonPostaci postac;	

	void inicjalizujZmienne()
	{
		for (int i = 0; i < 81; i++){
			for (int j = 0; j < 40; j++)
			{
				r[i][j] = 0;
				sciana[i][j] = 0;
			}
		}
		trudnoscPoziomu = 0;
		otwarteskrzynki=0;
		iloscpotworow=0;
		iloscskrzynek=0;
		zapamietaj = -1;
		wygrana = 1;
		autozapis=0;
		opusc =1;
		wktora = 4;
		for (int i = 0; i < 100; i++){
			sciezka[i] = NULL;
			nick[i] = NULL;
		}
	}
	void inicjalizujCzcionke()
	{
		lewo = 17;
		prawo = 16;
		gora = 30;
		dol = 31;
		black = 1;
		white = 2;
		scianka = 219;
		wyjscie = 176;
		wejscie = 177;
		zycie = 3;
		krzyz = 197;
		doswiadczenie = 21;
		lewy_gorny = 201;
		lewy_dolny = 200;
		prawy_gorny = 187;
		prawy_dolny = 188;
		srodkowy = 206;
		poziomy_gorny = 202;
		poziomy_dolny = 203;
		pionowy_prawy = 204;
		pionowy_lewy = 185;
		skrzynka = 127;
		drzwi = 19;
		pionowa = 186;
		pozioma = 205;
	}

	int zliczDef()
	{
		int defik=0;
		for (int i=1;i<200;i++){
			items(i);
			if (postac.posiadanePrzedmioty[i]==2)
				defik=defik + obrona; 
		}
		return defik;
	}

	int zliczDmg()
	{
		int damag=0;
		for (int i=1;i<200;i++){
			items(i);
			if (postac.posiadanePrzedmioty[i]==2)
				damag=atak;
		}
		return damag;
	}

	int zliczZrecznosc()
	{
		int dZrecznosc=0;
		for (int i=1;i<200;i++){
			items(i);
			if (postac.posiadanePrzedmioty[i]==2)
				dZrecznosc=dZrecznosc+iZrecznosc; 
		}
		return dZrecznosc;
	}

	int zliczSile()
	{
		int dSila=0;
		for (int i=1;i<200;i++){
			items(i);
			if (postac.posiadanePrzedmioty[i]==2)
				dSila=dSila+iSila; 
		}
		return dSila;
	}

	int zliczInteligencje()
	{
		int dInteligencja=0;
		for (int i=1;i<200;i++){
			items(i);
			if (postac.posiadanePrzedmioty[i]==2)
				dInteligencja=dInteligencja+iInteligencja; 
		}
		return dInteligencja;
	}

	void ramka(int ileDodatkowo = 0)
	{
		if (ileDodatkowo%2 == -1) ileDodatkowo++; //nauczylismy sie liczyc :D
		gotoxy(16,13-ileDodatkowo/2); cout << lewy_gorny; for (int i = 0; i<47;i++) cout << pozioma; cout << prawy_gorny;
		for (int i = 0; i<10+ileDodatkowo;i++){
			gotoxy(16,14+i-ileDodatkowo/2); cout << pionowa; for (int j = 0; j<47;j++) cout << " "; cout << pionowa;
		}
		gotoxy(16,24+ileDodatkowo/2); cout << lewy_dolny; for (int i = 0; i<47;i++) cout << pozioma; cout << prawy_dolny;   
	}

	void ramkaWyboru(string pytanie, string dluzszyTekst)
	{
		int i = 0;
		int j = 0;
		string tempDluzszyTekst = dluzszyTekst;
		while(true)
		{
			string::size_type pos = tempDluzszyTekst.find('|');
			if (pos == 4294967295) 
			{
				ileTekstu=i;
				break;
			}
			tablicaTekstu[i] = tempDluzszyTekst.substr(0, pos);
			tempDluzszyTekst = tempDluzszyTekst.substr(tempDluzszyTekst.find('|') + 1);
			i++;
		}
		for (int i = 0; i < 30; i++)
			tablicaTekstu[i] = "puste";
		string::size_type pos;
		while(true)
		{
			if (pytanie.length() > 50)
				pos = pytanie.find(' ',40);
			else
			{
				tablicaTekstu[j] = pytanie;
				break;
			}
			tablicaTekstu[j] = pytanie.substr(0, pos);
			pytanie = pytanie.substr(pos);
			j++;
		}
		int z = (int(i+j))/2 +1;
		i=i+j-7;
		ramka(i);
		for (int g = 0; g < 30; g++){
			if (tablicaTekstu[g]== "puste")
				break;
			gotoxy(39-(tablicaTekstu[g].length())/2 +1,18+g-z);
			cout << tablicaTekstu[g];
		}
		menuWyboru(39,20+j-z,dluzszyTekst);
	}

	void ramkaInformacji(string informacja)
	{
		FlushConsoleInputBuffer(hInput);    
		int j = 0;
		for (int i = 0; i < 30; i++)
			tablicaTekstu[i] = "puste";
		string::size_type pos;
		while(true)
		{
			if (informacja.length() > 50)
				pos = informacja.find(' ',40);
			else
			{
				tablicaTekstu[j] = informacja;
				break;
			}
			tablicaTekstu[j] = informacja.substr(0, pos);
			informacja = informacja.substr(pos);
			j++;
		}
		ramka(j-7);

		for (int g = 0; g < 30; g++){
			if (tablicaTekstu[g]== "puste")
				break;
			gotoxy(39-(tablicaTekstu[g].length())/2 +1,18+g +j/2);
			cout << tablicaTekstu[g];
		}

		gotoxy(19,20+j+j/2 -1);
		cout << "Nacisnij dowolny klawisz by kontynuowac...";
		_getch();
	}

	void menuWyboru(int xWyswietlania, int yWyswietlania, string dluzszyTekst, bool czyWysrodkowac = true)
	{
		FlushConsoleInputBuffer(hInput);    
		int dlugosc;
		for (int i = 0; i < 30; i++)
			tablicaTekstu[i] = "puste";
		unsigned int gdzie, ileTekstu;
		int przyKtorym = 1;
		int i = 0;
		while(true)
		{
			string::size_type pos = dluzszyTekst.find('|');
			if (pos == 4294967295) {
				ileTekstu=i;
				break;
			}
			tablicaTekstu[i] = dluzszyTekst.substr(0, pos);
			dluzszyTekst = dluzszyTekst.substr(dluzszyTekst.find('|') + 1);
			i++;
		}
		while (true)
		{
			for (int i = 0; i < 30; i++)
			{
				if (tablicaTekstu[i]== "puste")
					break;
				if (czyWysrodkowac == true)
					dlugosc = tablicaTekstu[i].length()/2;
				else
					dlugosc=0;
				gotoxy(xWyswietlania-dlugosc, yWyswietlania+i);
				if (przyKtorym==i+1)
					cout << "*";
				else
					cout << " ";
				cout << tablicaTekstu[i];
				if (przyKtorym==i+1)
					cout << "*";
				else
					cout << " ";
			}
			FlushConsoleInputBuffer(hInput);    
			gdzie=_getch();
			if ((gdzie==224))
				gdzie=_getch();
			mciSendString("stop sounds/skrot.wav ",NULL,1,NULL);
			mciSendString("play sounds/skrot.wav ",NULL,1,NULL);
			if (gdzie==72){
				przyKtorym=przyKtorym-1;
				if (przyKtorym==0)
					przyKtorym = ileTekstu;
			}
			if (gdzie==80){
				przyKtorym=przyKtorym+1;
				if (przyKtorym==ileTekstu+1)
					przyKtorym = 1;
			}
			if (gdzie==13 || gdzie==120)
			{
				wybor = przyKtorym;
				FlushConsoleInputBuffer(hInput);    
				return;
			}
		}
	}

	/*void ramkabig() //raczej nie bedzie uzyta
	{
	gotoxy(0,0);cout << lewy_gorny;for (int i = 0; i<81;i++) cout << poziomy_dolny;
	gotoxy(81,0);cout << prawy_gorny;
	gotoxy(0,39);cout << lewy_dolny;for (int i = 0; i<81;i++) cout << poziomy_gorny;
	gotoxy(81,39);cout << prawy_dolny;
	for (int i = 0; i<38;i++)
	{
	gotoxy(0,1+i);cout<< pionowy_prawy; 
	gotoxy(81,1+i);cout<< pionowy_lewy;     
	}
	gotoxy(1,1);cout << srodkowy;for (int i = 0; i<79;i++) cout << poziomy_gorny;
	gotoxy(80,1);cout << srodkowy;
	gotoxy(1,38);cout << srodkowy;for (int i = 0; i<79;i++) cout << poziomy_dolny;
	gotoxy(81,39);cout << prawy_dolny;
	}*/

	void mikstury()
	{
		uzylmp=0;
		uzylhp=0;
		ramkaWyboru("Zawartosc sakiewki:",(string("Mikstura zdrowia: ") + to_string(postac.hppot) + string("|Mikstura many: ") + to_string(postac.mppot) + string("|Powrot|")));
		if (wybor == 1){
			if (postac.hppot <1) 
				ramkaInformacji("Masz za malo mikstur zdrowia:");
			else
			{
				postac.hp= postac.hp + 50 ;
				if (postac.hp> postac.maxhp) postac.hp =postac.maxhp;
				uzylhp = 1;
				postac.hppot=postac.hppot-1;
				ramkaInformacji("Uleczyles sie za 50 hp," + string("Posiadasz teraz ") + to_string(postac.hp) + string("hp."));
			}
		}
		if (wybor == 2){
			if (postac.mppot <1) 
				ramkaInformacji("Masz za malo mikstur many");
			else{
				postac.mp=postac.mp+5;
				if (postac.mp>postac.maxmp) postac.mp = postac.maxmp;
				ramkaInformacji("Ilosc aktualnie posiadanych punktow many wzrosla do " + to_string(postac.mp));
				uzylmp=1;
				postac.mppot=postac.mppot-1;
			}
		}
	}   

	void usewyjscie(){
		wyszedlem = 2; 
		ramka();
		gotoxy(32,14);
		cout << "  Ukonczyles Lochy"<<endl;
		gotoxy(31,15);
		cout << "Lochowe statystyki: ";
		gotoxy(37,16);
		zolty();    cout << "$"; szary(); cout << " - ";
		cout << zdobyteZloto;
		gotoxy(37,17);
		cout << doswiadczenie<< " - " << zdobyteDoswiadczenie ;
		gotoxy(37,18);
		cout << white<< " - " << zabitepotwory<<"/"<<iloscpotworow ;
		gotoxy(37,19);    cout << skrzynka<<" - " << otwarteskrzynki<<"/"<<iloscskrzynek;
		cout << endl;
		gotoxy(19,21);
		system("pause");  
		system("CLS");
	}

	void usewejscie()
	{
		wyszedlem = 3; 
		ramka();
		gotoxy(32,14);
		cout << "Uciekles z lochow"<<endl;
		gotoxy(31,15);
		cout << "Lochowe statystyki: ";
		gotoxy(37,16);
		zolty();    cout << "$"; szary(); cout << " - ";
		cout << zdobyteZloto;
		gotoxy(37,17);
		cout << doswiadczenie<< " - " << zdobyteDoswiadczenie ;
		gotoxy(37,18);
		cout << white<< " - " << zabitepotwory<<"/"<<iloscpotworow ;
		gotoxy(37,19);    cout << skrzynka<<" - " << otwarteskrzynki<<"/"<<iloscskrzynek;
		cout << endl;
		gotoxy(19,21);
		system("pause");  
		system("CLS");
	}

	void wylaczMuzyke()
	{
		mciSendString("stop sounds/miasto.mp3 ",NULL,1,NULL);
		mciSendString("stop sounds/tawerna.wav ",NULL,1,NULL);
		mciSendString("stop sounds/walka.mp3 ",NULL,1,NULL);
		mciSendString("stop sounds/alchemik.wav ",NULL,1,NULL);
		mciSendString("stop sounds/kowal.wav ",NULL,1,NULL);
		mciSendString("stop sounds/ruins.wav ",NULL,1,NULL);
	}

	void menu()
	{  
		mciSendString("stop sounds/tawerna.wav ",NULL,1,NULL);
		mciSendString("stop sounds/walka.mp3 ",NULL,1,NULL);
		mciSendString("stop sounds/alchemik.wav ",NULL,1,NULL);
		mciSendString("stop sounds/kowal.wav ",NULL,1,NULL);
		mciSendString("stop sounds/ruins.wav ",NULL,1,NULL);
		tempexp=postac.doswiadczenie;
		for (int i = 0; i<41;i++){
			for (int j = 0; j<81;j++){
				r[j][i]=0;}}
		fstream plik;
		system("cls");
		pokaz();
		mciSendString("play sounds/miasto.mp3 ",NULL,1,NULL);
		ramkaWyboru("Co chcesz zrobic?","Wyrusz...|Karczma|Kowal i ekwipunek|Mag|Alchemik|Zobacz statystyki postaci|Lista Posiadanych przedmiotow|Sakiewka|Opcje|Zapisz stan gry|");
		switch (wybor)
		{
		case 1:	ramkaWyboru("Gdzie chcialbys wyruszyc?", "Ayleid (latwy)|Dasek Moor (normalny)|Lochy cmentarza (normalny++)|Sancre Tor (trudny)|Yuzaszkowo (trudny)|Krypta Pacmana (chaos)|Leze smoka (BOSS)|Powrot|");
			if (wybor !=8) level(wybor); else return;labirynt(); break;
		case 2: karczma(); break;
		case 3: kowal(); break;
		case 4: mag(); break;
		case 5: alchemik(); break;
		case 6: staty(); break;
		case 7: ekwipunek(); break;
		case 8: mikstury(); break;
		case 9: opcje(); break;
		case 10: save(); break;
		}
	}

	void odswiezEkranWalki(bool podczasRuchu = false)
	{
		zmienKolor(8);
		gotoxy(5,14);
		for (int i = 0; i < 71; i++) cout << pozioma;
		gotoxy(5,17);
		for (int i = 0; i < 71; i++) cout << pozioma;
		gotoxy(4,15); cout << pionowa;
		for (int i = 0; i < 71; i++)
		{
			if (i>=50)zmienKolor(4);
			cout << char(219);
		}
		zmienKolor(8);
		cout << pionowa;
		gotoxy(4,16);  cout << pionowa;
		for (int i = 0; i < 71; i++)
		{
			if (i>=50)zmienKolor(4);
			cout << char(219);
		}
		zmienKolor(8);
		cout << pionowa;
		if (timerGracza >=50) zmienKolor(64+15);
		else zmienKolor(128+15);
		gotoxy(int(5+timerGracza),15); cout << prawo; szary();
		if (timerPotwora >=50) zmienKolor(64+15);
		else zmienKolor(128+15);
		gotoxy(int(5+timerPotwora),16); cout << white; szary();
		gotoxy(30,3);
		cout << "     ";
		gotoxy(30,3);
		czerwony();cout<< postac.hp;szary();cout << "/";czerwony();cout << postac.maxhp;szary(); cout<< " ";
		gotoxy(31,4);cout << "     ";
		gotoxy(31,4);
		niebieski();cout << postac.mp ;szary();cout << "/" ;niebieski();cout << postac.maxmp;szary();
		gotoxy(45,3);cout << "     ";gotoxy(45,3);czerwony();cout << hpPotwora;szary();cout << "/";czerwony();cout << maksymalneHpPotwora;szary();
		if (podczasRuchu == false)
		{
			gotoxy(33,8); cout << " ";
			gotoxy(33,8); if (turaSpowolnieniaGracza > 0)cout << char(174);
			gotoxy(33,9); cout << " ";
			gotoxy(33,9); if (turaPrzyspieszeniaGracza > 0)cout << char(175);
			gotoxy(47,8); cout << " ";
			gotoxy(47,8); if (turaSpowolnieniaPotwora > 0)cout << char(174);
			gotoxy(47,9); cout << " ";
			gotoxy(47,9); if (turaPrzyspieszeniaPotwora > 0)cout << char(175);
			gotoxy(33,10);cout << prawo;
			if (stanDefensywnyGracza == true) cout << char(233);
			gotoxy(46,10);
			if (stanDefensywnyPotwora == true) cout << char(233);
			gotoxy(47,10);
			if (rodzajPotwora == 2) czerwony(); //TODO: dokonczyc
			cout << white;
			szary();
		}
	}

	void ramkaAtaku(bool czyPotwor)
	{
		if (czyPotwor == true)
			tempTekst1 = "Zaatakowales " + potw + string("a!");
		else
			tempTekst1 = "Zostales zaatakowany przez " + potw + string("a!");
		tempTekst2 = " Potwor " + potw + string(" jest poziomu ");
		if (rodzajPotwora==1) tempTekst2 += "slabego.";
		else if (rodzajPotwora==2) tempTekst2 += "normalnego.";
		else if (rodzajPotwora==3) tempTekst2 += "mocnego.";
		else if (rodzajPotwora==4) tempTekst2 += "Legendarnego!";
		ramkaInformacji(tempTekst1 + tempTekst2);
	}

	void podejscieGracza()
	{
		for (int i = 0; i<13;i++)
		{
			gotoxy(33+i,8); cout << " ";
			gotoxy(34+i,8); if (turaSpowolnieniaGracza > 0)cout << char(174);
			gotoxy(33+i,9); cout << " ";
			gotoxy(34+i,9); if (turaPrzyspieszeniaGracza > 0)cout << char(175);
			gotoxy(33+i,10);cout << " ";
			gotoxy(34+i,10);cout << prawo;
			Sleep(50);
		}  
	}

	void odejscieGracza()
	{
		for (int i = 0; i<13;i++)
		{
			gotoxy(46-i,8); cout << " ";
			gotoxy(45-i,8); if (turaSpowolnieniaGracza > 0)cout << char(174);
			gotoxy(46-i,9); cout << " ";
			gotoxy(45-i,9); if (turaPrzyspieszeniaGracza > 0)cout << char(175);
			gotoxy(46-i,10);cout << " ";
			gotoxy(45-i,10);cout << lewo;
			Sleep(50);
		}
		gotoxy(33,10);cout << prawo;
	}


	void podejsciePotwora()
	{
		for(int i=0;i<13;i++)
		{
			gotoxy(47-i,8); cout << " ";
			gotoxy(46-i,8); if (turaSpowolnieniaPotwora > 0)cout << char(174);
			gotoxy(47-i,9); cout << " ";
			gotoxy(46-i,9); if (turaPrzyspieszeniaPotwora > 0)cout << char(175);
			gotoxy(47-i,10);cout<<" ";
			gotoxy(46-i,10);cout<<white;
			Sleep(50);
		}
	}

	void odejsciePotwora()
	{
		for(int i=0;i<13;i++)
		{
			gotoxy(34+i,8); cout << " ";
			gotoxy(35+i,8); if (turaSpowolnieniaPotwora > 0)cout << char(174);
			gotoxy(34+i,9); cout << " ";
			gotoxy(35+i,9); if (turaPrzyspieszeniaPotwora > 0)cout << char(175);
			gotoxy(34+i,10);cout<<" ";
			gotoxy(35+i,10);cout<<white;
			Sleep(50);
		}
	}
	void wyswietlNadWrogiem(int zmianaWartosci,int czyKrytyk, int jakiKolor)
	{
		zmienKolor(jakiKolor);
		gotoxy(46,9);cout <<-zmianaWartosci;if(czyKrytyk == 1) cout << " KRYTYCZNE!";Sleep(150);
		gotoxy(46,9);cout << "                            ";
		gotoxy(46,8);cout <<-zmianaWartosci;if(czyKrytyk == 1) cout << " KRYTYCZNE!";Sleep(150);
		gotoxy(46,8);cout << "                            ";
		gotoxy(46,7);cout <<-zmianaWartosci;if(czyKrytyk == 1) cout << " KRYTYCZNE!";Sleep(150);
		gotoxy(46,7);cout << "                            ";
		gotoxy(46,6);cout <<-zmianaWartosci;if(czyKrytyk == 1) cout << " KRYTYCZNE!";Sleep(150);
		gotoxy(46,6);cout << "                   ";
		szary();
	}

	void wyswietlNadGraczem(int zmianaWartosci,int czyKrytyk, int jakiKolor)
	{
		zmienKolor(jakiKolor);
		gotoxy(32,9);cout <<-zmianaWartosci;if(czyKrytyk == 1) cout << " KRYTYCZNE!";Sleep(150);
		gotoxy(32,9);cout << "                            ";
		gotoxy(32,8);cout <<-zmianaWartosci;if(czyKrytyk == 1) cout << " KRYTYCZNE!";Sleep(150);
		gotoxy(32,8);cout << "                            ";
		gotoxy(32,7);cout <<-zmianaWartosci;if(czyKrytyk == 1) cout << " KRYTYCZNE!";Sleep(150);
		gotoxy(32,7);cout << "                            ";
		gotoxy(32,6);cout <<-zmianaWartosci;if(czyKrytyk == 1) cout << " KRYTYCZNE!";Sleep(150);
		gotoxy(32,6);cout << "                   ";
		szary();
	}

	void odtworzDzwiek(string listaDzwiekow)
	{
		for (int i = 0; i < 30; i++)
			tablicaTekstu[i] = "puste";
		unsigned int ileTekstu;

		int przyKtorym = 1;
		int i = 0;
		while(true)
		{
			string::size_type pos = listaDzwiekow.find('|');
			if (pos == 4294967295) {
				ileTekstu=i;
				break;
			}
			tablicaTekstu[i] = listaDzwiekow.substr(0, pos);
			listaDzwiekow = listaDzwiekow.substr(listaDzwiekow.find('|') + 1);
			i++;
		}
		int losowaLiczba = (rand() % (ileTekstu));

		tempTekst1 = "play sounds/" + tablicaTekstu[losowaLiczba] + string(" ");
		mciSendString((LPCSTR)tempTekst1.c_str(),NULL,1,NULL);
	}

	void poslijPociskDlugi(char jakiZnaczek, int jakiKolor)
	{
		for (int i = 1; i<13;i++)
		{
			zmienKolor(jakiKolor);
			gotoxy(33+i,10);cout << " ";
			gotoxy(34+i,10);cout << jakiZnaczek;
			gotoxy(35+i,10);cout << jakiZnaczek;
			gotoxy(36+i,10);cout << jakiZnaczek;
			Sleep(50);
			szary();
		}  
		gotoxy(34+12,10); cout << "   ";
	}

	void poslijPociskDlugiWybuchowy(char jakiZnaczek, char jakiZnaczek2, int jakiKolor, int kolorWybuchu)
	{
		for (int i = 1; i<11;i++)
		{
			zmienKolor(jakiKolor);
			gotoxy(33+i,10);cout << " ";
			gotoxy(34+i,10);cout << jakiZnaczek;
			gotoxy(35+i,10);cout << jakiZnaczek;
			gotoxy(36+i,10);cout << jakiZnaczek;
			Sleep(50);
			szary();
		}  
		gotoxy(34+10,10); cout << "   ";
		zmienKolor(kolorWybuchu);
		gotoxy(48,9);cout<<jakiZnaczek2;
		gotoxy(46,11);cout<<jakiZnaczek2;
		gotoxy(46,9);cout<<jakiZnaczek2;
		gotoxy(48,11);cout<<jakiZnaczek2;
		Sleep(150);
		gotoxy(49,8);cout<<jakiZnaczek2;
		gotoxy(47,12);cout<<jakiZnaczek2;
		gotoxy(47,8);cout<<jakiZnaczek2;
		gotoxy(49,12);cout<<jakiZnaczek2;
		gotoxy(45,8);cout<<jakiZnaczek2;
		gotoxy(45,12);cout<<jakiZnaczek2;
		gotoxy(49,10);cout<<jakiZnaczek2;
		gotoxy(45,10);cout<<jakiZnaczek2;
		Sleep(150);
		gotoxy(48,9);cout<<" ";
		gotoxy(46,11);cout<<" ";
		gotoxy(46,9);cout<<" ";
		gotoxy(48,11);cout<<" ";
		gotoxy(49,8);cout<<" ";
		gotoxy(47,12);cout<<" ";
		gotoxy(47,8);cout<<" ";
		gotoxy(49,12);cout<<" ";
		gotoxy(45,8);cout<<" ";
		gotoxy(45,12);cout<<" ";
		gotoxy(49,10);cout<<" ";
		gotoxy(45,10);cout<<" ";
	}

	void poslijPocisk(int jakiZnaczek, int jakiKolor)
	{
		for (int i = 1; i<13;i++)
		{
			zmienKolor(jakiKolor);
			gotoxy(33+i,10);cout << " ";
			gotoxy(34+i,10);cout << char(jakiZnaczek);
			Sleep(50);
			szary();
		}  
		gotoxy(34+12,10); cout << " ";
	}

	void poslijPociskWGracza(int jakiZnaczek, int jakiKolor)
	{
		for (int i = 1; i<13;i++)
		{
			zmienKolor(jakiKolor);
			gotoxy(47-i,10);cout << " ";
			gotoxy(46-i,10);cout << char(jakiZnaczek);
			Sleep(50);
			szary();
		}  
		gotoxy(47-13,10);cout << " ";
	}


	void atakNormalnyGracza()
	{
		odswiezEkranWalki();
		dmg = int((rand() % 7)*0.1*(postac.sila+zliczSile()) + postac.sila+zliczDmg()+zliczSile());
		podejscieGracza();
		if ( ((rand() % 99)+1)< crit)
		{
			czyTrafienieKrytyczne = 1;
			dmg=int(dmg*1.5);
		}
		else
			czyTrafienieKrytyczne = 0;
		if (stanDefensywnyPotwora == true) dmg=dmg/2;
		hpPotwora= hpPotwora-dmg;
		wybranyRuchGracza = 0;
		if (timerPotwora>=50) timerPotwora -= 50;
		timerGracza = 0;
		odswiezEkranWalki(true);
		if (czyTrafienieKrytyczne==1)
			odtworzDzwiek("krytyk.wav|krytyk2.mp3|krytyk3.mp3|");
		else
			odtworzDzwiek("hit1.wav|hit2.wav|hit3.wav|hit4.wav|hit5.mp3|");
		wyswietlNadWrogiem(dmg,czyTrafienieKrytyczne,3);
		odejscieGracza();
		odswiezEkranWalki();
	}

	void uzycieCzaru()
	{
		wybranyRuchGracza = 0;
		if (rodzajMagii == 1)
			czarOfensywny();
		else
			czarDefensywny();
		return;
	}

	bool sprawdzMane(int ileMany){
		if(postac.mp < ileMany)
		{
			ramkaInformacji("Niestety masz za malo punktow many. Ilosc many wymagana dla " + nazwaCzaru + " wynosi: " + to_string(ileMany));
			system("cls");
			odswiezEkranWalki();
			return false;
		}
		wykonanoRuch = true;
		wybranyRuchGracza = 3;
		return true;
	}

	void wyborRuchuPotwora()
	{
		int losowaLiczba;

		if (timerGracza >55)
		{
			losowaLiczba = rand() % 100;
			if (losowaLiczba > 40)
			{
				stanDefensywnyPotwora = true;
				timerPotwora = 0;
				odswiezEkranWalki();
				odtworzDzwiek("shield.wav|");
				return;
			}
		}
		else
		{
			losowaLiczba = rand() % 100;
			if (losowaLiczba > 60)
			{
				if (losowaLiczba>80 && turaSpowolnieniaGracza == 0)
				{
					wybranyRuchPotwora = 2;
					varAtakuPotwora = 0.5;
				}
				else if ( turaPrzyspieszeniaPotwora == 0)
				{
					wybranyRuchPotwora = 3;
					varAtakuPotwora = 0.4;
				}
				else
				{
					wybranyRuchPotwora = 1;
					varAtakuPotwora = 0.7; 
				}
			}
			else
			{
				wybranyRuchPotwora = 1;
				varAtakuPotwora = 0.7; 
			}
		}
	}

	void ruchPotwora()
	{
		stanDefensywnyPotwora = false;
		if (wybranyRuchPotwora == 1) //zwykly atak
		{
			int pdmg;
			odswiezEkranWalki();
			pdmg = potdmgmin+(rand()%7) -zliczDef();
			if (pdmg<0) pdmg = 0;
			if (stanDefensywnyGracza == true) pdmg = int(pdmg/2);
			postac.hp=postac.hp-pdmg;
			if (czyZasiegowy == false)
				podejsciePotwora();
			else
				poslijPociskWGracza(5,12);
			odswiezEkranWalki(true);
			odtworzDzwiek("punch1.mp3|punch2.mp3|punch3.mp3|punch4.mp3|punch5.mp3|punch6.mp3|");
			wyswietlNadGraczem(pdmg,0,12);
			if(timerGracza>=50)timerGracza -= 50;
			if (czyZasiegowy == false)
				odejsciePotwora();
			wybranyRuchGracza = 0;
		}
		else if (wybranyRuchPotwora == 2) //spowolnienie
		{
			turaSpowolnieniaGracza = 3;
			poslijPociskWGracza(175,10);
			odtworzDzwiek("spowolnienie.wav|");
			odswiezEkranWalki();
		}
		else if (wybranyRuchPotwora == 3) //przyspieszenie
		{
			turaPrzyspieszeniaPotwora=3;
			odtworzDzwiek("przyspieszenie.mp3|");
			odswiezEkranWalki();
		}
		odswiezEkranWalki();
		wybranyRuchPotwora = 0;
	}

	void sprawdzCzyPotworZyje()
	{
		if (hpPotwora < 1)
		{
			for (int i=0;i<5;i++)
			{
				gotoxy(47,10);
				cout << " ";
				Sleep(100);
				gotoxy(47,10);
				cout << white;
				Sleep(100);
			}
			gotoxy(47,10);
			cout << " ";
			ramkaInformacji("Wygrales! " + potw + string(" nie zyje!"));
			int potexp = int(maksymalneHpPotwora+0.5*(rand()%20));
			potgold = potgold+(rand()%20);
			ramkaInformacji("Otrzymujesz " + to_string(potexp) + string(" punktow doswiadczenia! Otrzymales ") + to_string (potgold) + string(" sztuk zlota"));
			zdobyteDoswiadczenie=zdobyteDoswiadczenie+potexp;
			postac.doswiadczenie=postac.doswiadczenie+potexp;
			zabitepotwory++;
			postac.zloto=postac.zloto+potgold;
			zdobyteZloto=zdobyteZloto+potgold;
		}
	}

	void wyborRuchuGracza()
	{
		wykonanoRuch = false;
		while (wykonanoRuch == false)
		{
			gotoxy(10,30);
			cout << "Twoj ruch?";
			menuWyboru(10,31,"Atak|Obrona|Magia|Mikstury|",false);
			if (wybor == 1){
				wykonanoRuch = true;
				wybranyRuchGracza = 1;
				varAtakuGracza = 0.7;
			}
			else if (wybor == 2)
			{
				stanDefensywnyGracza = true;
				wykonanoRuch = true;
				wybranyRuchGracza = 0;
				timerGracza = 0;
				odswiezEkranWalki();
				odtworzDzwiek("shield.wav|");
			}
			else if (wybor == 3)
			{
				wybranyRuchGracza = 3;
				string tmp="";
				for (int i = 1; i <= 100; i++)
				{
					magic(i);
					if(postac.posiadaneCzary[i]==1)
						tmp+=nazwaCzaru + "|";
				}
				tmp += "Powrot|";
				ramkaWyboru("Spellbook:", tmp);
				system("cls");
				odswiezEkranWalki();
				if (tablicaTekstu[wybor-1] != "Powrot")
				{
					for (int i = 1; i <= 100; i++)
					{
						magic(i);
						if (tablicaTekstu[wybor-1] == nazwaCzaru)
						{
							uzytyCzar = i;
							break;
						}
					}
					sprawdzMane(kosztMany);
				}
			}
			else if (wybor == 4)//uzycie potionow jest natychmiastowe
			{
				ramkaWyboru("Zawartosc sakiewki:",(string("Mikstura zdrowia: ") + to_string(postac.hppot) + string("|Mikstura many: ") + to_string(postac.mppot) + string("|Powrot|")));
				if (wybor == 1){
					if (postac.hppot <1) 
						ramkaInformacji("Masz za malo mikstur zdrowia:");
					else
					{
						postac.hp= postac.hp + 50 ;
						if (postac.hp> postac.maxhp) postac.hp =postac.maxhp;
						postac.hppot=postac.hppot-1;
						system("cls");
						odswiezEkranWalki();
						wykonanoRuch = true;
						wybranyRuchGracza =0;
						timerGracza = 0;
						mciSendString("play sounds/heal.mp3 ",NULL,1,NULL);
						wyswietlNadGraczem(-50,0,2);
					}
				}
				if (wybor == 2){
					if (postac.mppot <1) 
						ramkaInformacji("Masz za malo mikstur many");
					else{
						postac.mp=postac.mp+10;
						if (postac.mp>postac.maxmp) postac.mp = postac.maxmp;
						postac.mppot=postac.mppot-1;
						system("cls");
						wybranyRuchGracza =0;
						timerGracza = 0;
						odswiezEkranWalki();
						wykonanoRuch = true;
						wyswietlNadGraczem(-10,0,9);
					}
				}
				else
				{
					system("cls");
					odswiezEkranWalki();
				}
			}
		}
		for (int i = 0; i < 5; i++)
		{
			gotoxy(10,30+i);
			cout << "           ";
		}
	}

	void walka(bool czyPotworZaatakowal)
	{
		FlushConsoleInputBuffer(hInput);    
		wylaczMuzyke();
		odtworzDzwiek("walka.mp3|");
		//mciSendString("play sounds/walka.mp3 ",NULL,1,NULL);
		potwor();
		ramkaAtaku(czyPotworZaatakowal);
		maksymalneHpPotwora=hpPotwora;
		system("cls");
		timerPotwora= 0, timerGracza = 0;
		if (czyPotworZaatakowal==false)
			timerPotwora = 50;
		else
			timerGracza = 50;
		turaPrzyspieszeniaGracza = 0;
		turaPrzyspieszeniaPotwora = 0;
		turaSpowolnieniaGracza = 0;
		turaSpowolnieniaPotwora = 0;
		wybranyRuchGracza = 0;
		wybranyRuchPotwora = 0;
		odswiezEkranWalki();
		szybkoscGracza = 1+ 0.015 * postac.zrecznosc;
		wybranyRuchGracza = 0;
		stanDefensywnyGracza = false;
		stanDefensywnyPotwora = false;
		while (hpPotwora>0 && postac.hp>0) //petla walki
		{
			FlushConsoleInputBuffer(hInput);    
			odswiezEkranWalki(true);
			if (timerGracza >= 50)
			{
				if (wybranyRuchGracza == 0)
					wyborRuchuGracza(); 
				if (timerGracza == 70)
				{
					if (turaPrzyspieszeniaGracza>0)
						turaPrzyspieszeniaGracza--;
					if (turaSpowolnieniaGracza>0)
						turaSpowolnieniaGracza--;
					stanDefensywnyGracza = false;
					if (wybranyRuchGracza == 1)
						atakNormalnyGracza();
					else if (wybranyRuchGracza == 3)
						uzycieCzaru();
					timerGracza = 0;
				}
			}
			if (timerPotwora >= 50)
			{
				if (wybranyRuchPotwora == 0)
					wyborRuchuPotwora(); 
				if (timerPotwora >= 70) 
				{
					ruchPotwora(); 
					if (turaPrzyspieszeniaPotwora>0)
						turaPrzyspieszeniaPotwora--;
					if (turaSpowolnieniaPotwora>0)
						turaSpowolnieniaPotwora--;
					stanDefensywnyPotwora = false;
					timerPotwora = 0;
				}
			}
			if (postac.hp<1)
			{
				gameover();
				return;
			}
			sprawdzCzyPotworZyje();
			Sleep(50);
			//
			// do wybalansowania
			if (wybranyRuchGracza == 0) varAtakuGracza = 1; 
			if (wybranyRuchPotwora == 0 || timerPotwora<50) varAtakuPotwora = 1; 
			if (turaSpowolnieniaGracza > 0) varSpowolnieniaGracza = 0.7;
			else varSpowolnieniaGracza = 1;
			if (turaSpowolnieniaPotwora > 0) varSpowolnieniaPotwora = 0.7;
			else varSpowolnieniaPotwora = 1;
			if (turaPrzyspieszeniaGracza > 0) varPrzyspieszeniaGracza = 1.3;
			else varPrzyspieszeniaGracza = 1;
			if (turaPrzyspieszeniaPotwora > 0) varPrzyspieszeniaPotwora = 1.3;
			else varPrzyspieszeniaPotwora = 1;
			if (stanDefensywnyGracza == true) varObronyGracza = 1.2;
			else varObronyGracza = 1;
			if (stanDefensywnyPotwora == true) varObronyPotwora = 1.2;
			else varObronyPotwora = 1;
			//
			//
			timerPotwora+=szybkoscPotwora*varSpowolnieniaPotwora*varPrzyspieszeniaPotwora*varAtakuPotwora*varObronyPotwora;
			timerGracza +=szybkoscGracza *varSpowolnieniaGracza *varPrzyspieszeniaGracza *varAtakuGracza *varObronyGracza;
			/*gotoxy(30,30); cout << "    ";
			gotoxy(30,30); cout << szybkoscGracza *varSpowolnieniaGracza *varPrzyspieszeniaGracza *varAtakuGracza *varObronyGracza;
			gotoxy(30,31); cout << "    ";
			gotoxy(30,31); cout << timerGracza;
			gotoxy(70,30); cout << "    ";
			gotoxy(70,30); cout << szybkoscPotwora*varSpowolnieniaPotwora*varPrzyspieszeniaPotwora*varAtakuPotwora*varObronyPotwora;
			gotoxy(70,31); cout << "    ";
			gotoxy(70,31); cout << timerPotwora;*/
			//debugger do balansu predkosci :d
			//
			if (timerPotwora>70)timerPotwora = 70;
			if (timerGracza>70) timerGracza  = 70;
		}
		while (postac.doswiadczenie>postac.maksymalneDoswiadczenie)       
			postac.poziom=postac.poziom+ lvlup();
		wylaczMuzyke();
		wygrana = 1;
		system("CLS");
		return;
	}

	string potwor()
	{
		int k = rand() % 6;
		if (rodzajPotwora==1){
			if (k==0) {potw = "Szczur"; hpPotwora = 25; potdmgmin = 5;potgold=15;szybkoscPotwora=1.2;czyZasiegowy = false;}
			else if (k==1) {potw = "Pajak"; hpPotwora = 30; potdmgmin = 6;potgold=25;szybkoscPotwora=1.1;czyZasiegowy = true; typAtaku = 5;}
			else if (k==2) {potw = "Nietoperz"; hpPotwora = 45; potdmgmin = 7;potgold=45;szybkoscPotwora=1.3;czyZasiegowy = false;}
			else if (k==3) {potw = "Ognik"; hpPotwora = 50; potdmgmin = 8;potgold=65;szybkoscPotwora=1.05;czyZasiegowy = true;}
			else if (k==4) {potw = "Skunks"; hpPotwora = 55; potdmgmin = 9;potgold=65;szybkoscPotwora=1.08;czyZasiegowy = false;}
			else if (k==5) {potw = "Lis"; hpPotwora = 60; potdmgmin = 10;potgold=65;szybkoscPotwora=1.25;czyZasiegowy = false;}
		}
		if (rodzajPotwora==2){
			if (k==0) {potw = "Szkielet"; hpPotwora = 180; potdmgmin = 20;potgold=150;szybkoscPotwora=0.8;czyZasiegowy = false;}
			else if (k==1) {potw = "Goblin"; hpPotwora = 200; potdmgmin = 21;potgold=175;szybkoscPotwora=0.9;czyZasiegowy = false;}
			else if (k==2) {potw = "Szaman"; hpPotwora = 220; potdmgmin = 22;potgold=200;szybkoscPotwora=1.15;czyZasiegowy = true; typAtaku = 4;}
			else if (k==3) {potw = "Troll"; hpPotwora = 240; potdmgmin = 23;potgold=220;szybkoscPotwora=0.7;czyZasiegowy = true; typAtaku = 7;}
			else if (k==4) {potw = "Elf"; hpPotwora = 260; potdmgmin = 24;potgold=220;szybkoscPotwora=1.4;czyZasiegowy = true; typAtaku = 15;}
			else if (k==5) {potw = "Minotaur"; hpPotwora = 280; potdmgmin = 25;potgold=220;szybkoscPotwora=1.05;czyZasiegowy = false;}
		}
		if (rodzajPotwora==3){
			if (k==0) {potw = "Wampir"; hpPotwora = 400; potdmgmin = 35;potgold=280;szybkoscPotwora=1;czyZasiegowy = false;}
			else if (k==1) {potw = "Duch"; hpPotwora = 420; potdmgmin = 36;potgold=300;szybkoscPotwora=1;czyZasiegowy = false;}
			else if (k==2) {potw = "Ogr"; hpPotwora = 440; potdmgmin = 37;potgold=320;szybkoscPotwora=1;czyZasiegowy = true; typAtaku = 22;}
			else if (k==3) {potw = "Wilkolak"; hpPotwora = 460; potdmgmin = 38;potgold=340;szybkoscPotwora=1;czyZasiegowy = false;}
			else if (k==4) {potw = "Dzin"; hpPotwora = 480; potdmgmin = 39;potgold=340;szybkoscPotwora=1;czyZasiegowy = true; typAtaku = 8;}
			else if (k==5) {potw = "Golem"; hpPotwora = 500; potdmgmin = 40;potgold=340;szybkoscPotwora=1;czyZasiegowy = false;}
		}
		if (rodzajPotwora==4){
			if (postac.wybranyPoziom == 1){potw = "Szczurolak"; hpPotwora = 200; potdmgmin = 15;potgold=200;szybkoscPotwora=1.1;czyZasiegowy = false;}
			else if (postac.wybranyPoziom == 2){potw = "Spiderpig"; hpPotwora = 400; potdmgmin = 35;potgold=800;szybkoscPotwora=1.15;czyZasiegowy = true; typAtaku = 5;}
			else if (postac.wybranyPoziom == 3){potw = "Gigant"; hpPotwora = 600; potdmgmin = 40;potgold=1600;szybkoscPotwora=1.2;czyZasiegowy = false;}
			else if (postac.wybranyPoziom == 4){potw = "Cyklop"; hpPotwora = 800; potdmgmin = 45;potgold=2000;szybkoscPotwora=1.25;czyZasiegowy = false;}
			else if (postac.wybranyPoziom == 5){potw = "Yuseg z Yuzaszkowa"; hpPotwora = 1000; potdmgmin = 50;potgold=3000;szybkoscPotwora=1.3;czyZasiegowy = true; typAtaku = 22;}
			else if (postac.wybranyPoziom == 6){potw = "Behemot"; hpPotwora = 1500; potdmgmin = 55;potgold=4000;szybkoscPotwora=1;czyZasiegowy = true; typAtaku = 30;}
			else if (postac.wybranyPoziom == 7){potw = "Smok"; hpPotwora = 5000; potdmgmin = 80;potgold=10000;szybkoscPotwora=1;czyZasiegowy = true; typAtaku = 3;}
		}
		return potw;
	}

	void pokaz()
	{
		crit=int(sqrt(postac.zrecznosc+zliczZrecznosc())*4);
		gotoxy(0,0);bialy();cout << doswiadczenie;szary();cout << " - ";bialy(); cout << postac.doswiadczenie<<"/"<<postac.maksymalneDoswiadczenie;szary();cout << "(";bialy();cout << postac.poziom;szary();cout<<")";
		gotoxy(0,1);czerwony();cout << zycie;szary();cout << " - " ;czerwony();cout << postac.hp;szary();cout << "/";czerwony();cout <<postac.maxhp;
		gotoxy(0,2);niebieski();cout << krzyz;szary();cout << " - " ;niebieski();cout << postac.mp;szary();cout<<"/";niebieski();cout<<postac.maxmp;
		gotoxy(70,0);zolty();cout << "$";szary();cout << " - " ;zolty();cout << postac.zloto;
		gotoxy(70,1);czerwony();cout << zycie; cout<< " pot";szary();cout << " - " ;czerwony();cout << postac.hppot;
		gotoxy(70,2);niebieski();cout << krzyz; cout<< " pot";szary();cout << " - " ;niebieski();cout << postac.mppot;
		szary();
		gotoxy(0,3);
		cout<< "obrona: ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout <<zliczDef() ;
		szary();
		gotoxy(70,3);
		cout << "Dmg: ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		cout << postac.sila+zliczDmg()+zliczSile();
		szary();
		cout << "-";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		cout  << 6*0.1*postac.sila + postac.sila+zliczDmg()+zliczSile();
		szary();
		gotoxy(0,5);
	}

	int lvlup()
	{
		if (postac.doswiadczenie > postac.maksymalneDoswiadczenie-1)
		{
			wylaczMuzyke();
			Sleep(100);
			mciSendString("play sounds/levelUP.wav ",NULL,1,NULL);
			ramkaInformacji("GRATULACJE! Awansowales na poziom: " + to_string(postac.poziom+1) + " HP: " + to_string(postac.maxhp) + string("->") + to_string(int(postac.maxhp+postac.budowa*1.2)) + string("   MP: " )+ to_string(postac.maxmp) + string("->") + to_string(int(postac.maxmp*1.4)));
			postac.doswiadczenie = postac.doswiadczenie-postac.maksymalneDoswiadczenie;
			postac.maksymalneDoswiadczenie=int(postac.maksymalneDoswiadczenie*1.4);
			postac.maxhp=int(postac.maxhp+postac.budowa*1.2);
			postac.maxmp=int(postac.maxmp*1.4);
			postac.mp=postac.maxmp;
			postac.hp=postac.maxhp;
			postac.punktyDoRozdania=5;
			while (postac.punktyDoRozdania>0){
				ramkaWyboru("Punkty do rozdania: "+to_string(postac.punktyDoRozdania),"Sila: "+to_string(postac.sila)+string("|Zrecznosc: ")+to_string(postac.zrecznosc) +string("|Budowa: ")+to_string(postac.budowa)+string("|Inteligencja: ")+to_string(postac.inteligencja) + string("|"));
				if (wybor == 1)
					postac.sila=postac.sila+1;
				else if (wybor == 2)
					postac.zrecznosc=postac.zrecznosc+1;
				else if (wybor == 3)
					postac.budowa=postac.budowa+1;
				else if (wybor == 4)
					postac.inteligencja=postac.inteligencja+1;
				postac.punktyDoRozdania=postac.punktyDoRozdania-1;
			}
			return 1;
		}
		else 
		{
			return 0;
		};
	}

	void alchemik()
	{
		wylaczMuzyke();
		Sleep(100);
		mciSendString("play sounds/alchemik.wav ",NULL,1,NULL);
		int ilosc = -1;
		int ilepot=0;
		ramkaWyboru("Witaj w mym sklepie. Co chcialbys kupic?","Mikstura zdrowia - 250 szt zlota|Mikstura Many - 200 szt zlota|Powrot|");
		if(wybor== 2 || wybor == 1)
		{
			int przycisk=0;
			while(przycisk!=13){
				ramka();
				gotoxy(20,16);
				cout << "Podaj ilosc: < " << ilepot << " >   Cena: ";
				if (wybor==1) 
					cout << ilepot*250 << "   "; 
				else 
					cout << ilepot*200 << "   ";
				przycisk=_getch();
				if (przycisk!=13)
					przycisk=_getch();
				if (przycisk==75) 
				{
					ilepot=ilepot-1; 
					if (ilepot==-1) ilepot=0;
				}
				if (przycisk==77) 
					ilepot=ilepot+1;
				ilosc=ilepot;
			}
			if(wybor == 3) 
			{
				ramkaInformacji("Dowidzenia...");
				return;
			}
			if (ilosc==0) {
				ramkaInformacji("Czyli nic nie wybrales... Dlaczego zawracasz niepotrzebnie dupe?");
				return;
			}
			if (wybor == 1)
			{
				if ((250*ilosc)>postac.zloto) 
					ramkaInformacji("Nie masz przy sobie " + to_string(250*ilosc) + string(" sztuk zlota"));
				else
				{
					mciSendString("play sounds/potion.wav ",NULL,1,NULL);
					postac.zloto = postac.zloto -(250*ilosc); 
					postac.hppot = postac.hppot+ilosc; 
					ramkaInformacji("Kupiles " +to_string(ilosc) + string(" mikstur zdrowia za sume ") + to_string(250*ilosc) + string("sztuk zlota.") + "Posiadasz teraz " +to_string(postac.hppot) + string(" mikstur zdrowia i ")+ to_string(postac.zloto) + string(" sztuk zlota")); 
				}
				return;
			}
			if (wybor == 2)
			{
				if ((200*ilosc)>postac.zloto) 
					ramkaInformacji("Nie masz przy sobie " + to_string(250*ilosc) + string(" sztuk zlota"));
				else
				{
					mciSendString("play sounds/potion.wav ",NULL,1,NULL);
					postac.zloto = postac.zloto -(200*ilosc); 
					postac.mppot = postac.mppot+ilosc; 
					ramkaInformacji("Kupiles " +to_string(ilosc) + string(" mikstur many za sume ") + to_string(200*ilosc) + string("sztuk zlota.") +"Posiadasz teraz " +to_string(postac.mppot) + string(" mikstur many i ")+ to_string(postac.zloto) + string(" sztuk zlota")); 
				}
				return;
			}
		}
		wylaczMuzyke();
	}

	void karczma()
	{
		wylaczMuzyke();
		Sleep(100);
		mciSendString("play sounds/tawerna.wav ",NULL,1,NULL);
		ramkaWyboru("Witaj w mej karczmie, co podac?","Wynajmij pokoj...|Wlasnie wychodzilem...|");
		if (wybor == 1)
		{
			ramkaWyboru("Wybierz pokoj:","Obskurny - 100szt zlota|Czysty - 500szt zlota|Eksklusywny - 1500szt zlota|Powrot...|");
			if (wybor == 1)
			{
				if (postac.zloto>99) 
				{
					postac.zloto=postac.zloto-100; 
					if ((rand() % 10)<3) 
						ramkaInformacji("Niestety po ledwo przespanej nocy nie czujesz by sen ci w czymkolwiek pomogl");
					else 
					{
						postac.hp = postac.maxhp; 
						ramkaInformacji("Po ciezkim snie, budzisz sie wypoczety");
					}
				}
				else
					ramkaInformacji("Nawet na obskurny pokoj cie nie stac? Co za lachodra");
			}
			else if (wybor == 2)
			{
				if (postac.zloto>499) 
				{
					postac.zloto=postac.zloto-500; 
					postac.hp=postac.maxhp; 
					ramkaInformacji("Noc w luksusach zrobila swoje, jestes wypoczety");
				} 
				else 
					ramkaInformacji("Nie stac cie na te luksusy zebraku...");
			}
			else if (true)
			{
				if (postac.zloto>1499) 
				{
					postac.zloto=postac.zloto-1500; 
					postac.hp=postac.maxhp; 
					if ((rand() % 10)<5)
					{
						postac.doswiadczenie=int(postac.doswiadczenie+0.1*postac.maksymalneDoswiadczenie); 
						ramkaInformacji("Po wyspanej nocy czujesz sie jak bog! Zdobywasz " + to_string(postac.maksymalneDoswiadczenie*0.1) + string(" punktow doswiadczenia"));   
					}
					else 
						ramkaInformacji("Po wyspanej nocy w niebianskich warunkach czujesz sie niezwykle orzezwiony."); 
				} 
				else 
					ramkaInformacji("Za wysokie progi na twoje nogi biedaku... Prosze wyjdz i nie wracaj");
			}
		} 
		wylaczMuzyke();
	}

	void staty()
	{
		system("cls");
		cout << "Poziom: " << postac.poziom <<"\nDoswiadczenie: "<< postac.doswiadczenie << "/" << postac.maksymalneDoswiadczenie<< "\nHP: " << postac.hp << "/" << postac.maxhp<< "\nMP: " << postac.mp << "/" << postac.maxmp<< "\n\nSila: "<<postac.sila<<" + "<<zliczSile()<<"\nZrecznosc: "<<postac.zrecznosc <<" + "<<zliczZrecznosc()<<"\nBudowa: " <<postac.budowa << "\nInteligencja: " << postac.inteligencja<<" + "<<zliczInteligencje()<<endl<<endl;
		cout << "Szansa na krytyczny cios: " << crit << "%\n\n";
		cout << "Sila wplywa na ilosc zadawanych obrazen\nZrecznosc wplywa na szanse krytycznego trafienia\nBudowa wplywa na ilosc maksymalnego hp po zdobyciu poziomu\nInteligencja wplywa na moc czarow\n\n";
		system("PAUSE");    
	}

	void save()
	{     
		system("cls");                                 
		ofstream plik;               
		plik.open(sciezka,ios::out);
		plik << nick << endl << postac.poziom << endl << postac.doswiadczenie << endl << postac.maksymalneDoswiadczenie  << endl << postac.hp << endl << postac.maxhp << endl << postac.mp << endl << postac.maxmp << endl << postac.sila << endl << postac.inteligencja << endl << postac.zrecznosc << endl << postac.budowa  << endl << postac.zloto << endl << postac.hppot << endl << postac.mppot << endl << postac.opoznienieTekstu<< endl<<autozapis;
		for (int i=1;i<200;i++)
			plik << endl << postac.posiadanePrzedmioty[i];
		for (int j=1;j<100;j++)
			plik << endl << postac.posiadaneCzary[j];
		plik.close();
		ramkaInformacji("Pomyslnie zapisano stan gry.");
	}

	void opcje()
	{
		ramkaWyboru("Opcje","Predkosc wczytywania tekstu podczas walki|Autozapis|Powrot|");
		if (wybor == 1)
		{
			ramkaWyboru("Predkosc wczytywania tekstu","0 sekund|1 sekunda|2 sekundy|Powrot|");
			if (wybor == 1)
				postac.opoznienieTekstu =0;
			else if (wybor == 2)
				postac.opoznienieTekstu = 1000;
			else if (wybor == 3)
				postac.opoznienieTekstu = 2000;
			ramkaInformacji("Predkosc wczytywania tekstu: " + to_string(postac.opoznienieTekstu/1000) + string(" sekund."));
		}
		else if (wybor == 2)
		{
			ramkaWyboru("Wlaczyc Autozapis?","Tak|Nie|Powrot|");
			if (wybor == 1)
			{
				ramkaInformacji ("Autozapis zostal wlaczony");
				autozapis=1;
			}
			else if (wybor == 2)
			{
				ramkaInformacji ("Autozapis zostal wylaczony");
				autozapis=0;
			}
		}
	}   

	string tablicaTekstu[30];
	unsigned int ileTekstu;

	//Helm od 1
	//Zbroja od 20
	//Buty od 40
	//Spodnie od 60
	//Rekawice od 80
	//Tarcze od 100
	//Bronie od 120

	void items(int id) 
	{
		//1def=120g, 1dmg=140g, 1agi=110g, 1int=130g, 1str=140g TODO:Nowe itemy.
		if(id==1){nazwaitemu = "Skorzany kaptur"; obrona = 1; atak=0; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 120;}
		else if(id==2){nazwaitemu = "Kolczy czepiec"; obrona = 2; atak=0; iZrecznosc=1; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 350;}
		else if(id==3){nazwaitemu = "Zelazny helm"; obrona = 5; atak=0; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 600;}
		else if(id==4){nazwaitemu = "Stalowy helm"; obrona = 5; atak=0; iZrecznosc=0; iInteligencja=0; iSila=2; wartoscPrzedmiotu = 880;}
		else if(id==5){nazwaitemu = "Szklany helm"; obrona = 4; atak=0; iZrecznosc=0; iInteligencja=5; iSila=0; wartoscPrzedmiotu = 1130;}
		else if(id==6){nazwaitemu = "Krasnoludzki szturmak"; obrona = 8; atak=0; iZrecznosc=3; iInteligencja=0; iSila=3; wartoscPrzedmiotu = 1710;}
		else if(id==20){nazwaitemu = "Skorzana zbroja"; obrona = 5; atak=0; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 600;}
		else if(id==21){nazwaitemu = "Kolczuga"; obrona = 7; atak=0; iZrecznosc=2; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 1060;}
		else if(id==22){nazwaitemu = "Zelazna zbroja"; obrona = 10; atak=0; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 1200;}
		else if(id==23){nazwaitemu = "Stalowa zbroja"; obrona = 9; atak=0; iZrecznosc=0; iInteligencja=0; iSila=4; wartoscPrzedmiotu = 1640;}
		else if(id==24){nazwaitemu = "Szklana zbroja"; obrona = 8; atak=0; iZrecznosc=0; iInteligencja=6; iSila=0; wartoscPrzedmiotu = 1740;}
		else if(id==25){nazwaitemu = "Krasnoludzka zbroja"; obrona = 12; atak=0; iZrecznosc=3; iInteligencja=0; iSila=5; wartoscPrzedmiotu = 2470;}
		else if(id==40){nazwaitemu = "Skorzane buty"; obrona = 2; atak=0; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 240;}
		else if(id==41){nazwaitemu = "Kolcze buty"; obrona = 3; atak=0; iZrecznosc=1; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 470;}
		else if(id==42){nazwaitemu = "Zelazne buty"; obrona = 6; atak=0; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 720;}
		else if(id==43){nazwaitemu = "Stalowe buty"; obrona = 4; atak=0; iZrecznosc=0; iInteligencja=0; iSila=4; wartoscPrzedmiotu = 1040;}
		else if(id==44){nazwaitemu = "Szklane buty"; obrona = 4; atak=0; iZrecznosc=0; iInteligencja=5; iSila=0; wartoscPrzedmiotu = 1130;}
		else if(id==45){nazwaitemu = "Krasnoludzkie buty"; obrona = 10; atak=0; iZrecznosc=1; iInteligencja=0; iSila=2; wartoscPrzedmiotu = 1590;}
		else if(id==60){nazwaitemu = "Skorzane spodnie"; obrona = 3; atak=0; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 360;}
		else if(id==61){nazwaitemu = "Kolcze spodnie"; obrona = 4; atak=0; iZrecznosc=2; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 700;}
		else if(id==62){nazwaitemu = "Zelazne nagolenniki"; obrona = 9; atak=0; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 1080;}
		else if(id==63){nazwaitemu = "Stalowe nagolenniki"; obrona = 7; atak=0; iZrecznosc=0; iInteligencja=0; iSila=5; wartoscPrzedmiotu = 1540;}
		else if(id==64){nazwaitemu = "Szklane nagolenniki"; obrona = 7; atak=0; iZrecznosc=0; iInteligencja=8; iSila=0; wartoscPrzedmiotu = 1880;}
		else if(id==65){nazwaitemu = "Krasnoludzkie nagolenniki"; obrona = 12; atak=0; iZrecznosc=2; iInteligencja=0; iSila=3; wartoscPrzedmiotu = 2080;}
		else if(id==80){nazwaitemu = "Skorzane rekawice"; obrona = 1; atak=0; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 120;}
		else if(id==81){nazwaitemu = "Kolcze rekawice"; obrona = 1; atak=0; iZrecznosc=1; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 230;}
		else if(id==82){nazwaitemu = "Zelazne rekawice"; obrona = 5; atak=0; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 600;}
		else if(id==83){nazwaitemu = "Stalowe rekawice"; obrona = 4; atak=0; iZrecznosc=0; iInteligencja=0; iSila=3; wartoscPrzedmiotu = 900;}
		else if(id==84){nazwaitemu = "Szklane rekawice"; obrona = 5; atak=0; iZrecznosc=0; iInteligencja=4; iSila=0; wartoscPrzedmiotu = 1120;}
		else if(id==85){nazwaitemu = "Krasnoludzkie rekawice"; obrona = 7; atak=0; iZrecznosc=1; iInteligencja=0; iSila=3; wartoscPrzedmiotu = 1370;}
		else if(id==100){nazwaitemu = "Zbite deski"; obrona = 5; atak=0; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 600;}
		else if(id==101){nazwaitemu = "Drewniana tarcza"; obrona = 10; atak=0; iZrecznosc=0; iInteligencja=0; iSila=1; wartoscPrzedmiotu = 1200;}
		else if(id==102){nazwaitemu = "Zelazna tarcza"; obrona = 15; atak=0; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 1800;}
		else if(id==103){nazwaitemu = "Walerianska tarcza"; obrona = 20; atak=0; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 2400;}
		else if(id==104){nazwaitemu = "Tarcza z lusek smoka"; obrona = 20; atak=0; iZrecznosc=0; iInteligencja=5; iSila=0; wartoscPrzedmiotu = 3050;}
		else if(id==120){nazwaitemu = "Zardzewialy zelazny sztylet"; obrona = 0; atak=2; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 280;}
		else if(id==121){nazwaitemu = "Zelazny sztylet"; obrona = 0; atak=5; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 700;}
		else if(id==122){nazwaitemu = "Stalowy sztylet"; obrona = 0; atak=7; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 940;}
		else if(id==123){nazwaitemu = "Zelazny krotki miecz"; obrona = 0; atak=10; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 1200;}
		else if(id==124){nazwaitemu = "Walerianski krotki miecz"; obrona = 0; atak=11; iZrecznosc=2; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 1540;}
		else if(id==125){nazwaitemu = "Stalowy krotki miecz"; obrona = 0; atak=15; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 1800;}
		else if(id==140){nazwaitemu = "Zelazny dlugi miecz"; obrona = 0; atak=16; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 1920;}
		else if(id==141){nazwaitemu = "Stalowy dlugi miecz"; obrona = 0; atak=20; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 2400;}
		else if(id==142){nazwaitemu = "Zelazny topor"; obrona = 0; atak=20; iZrecznosc=0; iInteligencja=0; iSila=3; wartoscPrzedmiotu = 2820;}
		else if(id==143){nazwaitemu = "Walerianski mlot bojowy"; obrona = 0; atak=23; iZrecznosc=3; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 3150;}
		else if(id==144){nazwaitemu = "Stalowy wielki miecz dwureczny"; obrona = 0; atak=28; iZrecznosc=0; iInteligencja=0; iSila=0; wartoscPrzedmiotu = 3520;}
		else if(id==145){nazwaitemu = "Demoniczny miecz zaglady"; obrona = 3; atak=30; iZrecznosc=4; iInteligencja=3; iSila=4; wartoscPrzedmiotu =5210;}
		else if(id==146){nazwaitemu = "Miecz ostatnie Dranga"; obrona = -10; atak=50; iZrecznosc=0; iInteligencja=0; iSila=10; wartoscPrzedmiotu =10210;}
	}

	void magic(int id)
	{
		if(id==1){nazwaCzaru = "Ognisty Podmuch"; kosztMany = 8; wartoscCzaru = 100; przelicznik=1.2; rodzajAnimacji=1; p1=12; p2=12; p3=0; p4=0; rodzajMagii = 1; varAtakuGracza = varAtakuGracza = 0.7;}
		else if(id==2){nazwaCzaru = "Swietlisty Grom"; kosztMany = 12; wartoscCzaru = 500; przelicznik=2; rodzajAnimacji=3; p1=126; p2=158; p3=14; p4=12; rodzajMagii = 1; varAtakuGracza = 0.6;}
		else if(id==52){nazwaCzaru = "Spowolnienie"; kosztMany = 4; wartoscCzaru = 1000; przelicznik=0; rodzajAnimacji=1; p1=174; p2=0; p3=10; p4=0; rodzajMagii = 2; varAtakuGracza = 0.5;}
		else if(id==50){nazwaCzaru = "Przyspieszenie"; kosztMany = 5; wartoscCzaru = 200; przelicznik=0; rodzajAnimacji=0; p1=0; p2=0; p3=0; p4=0; rodzajMagii = 2; varAtakuGracza = 0.5;}
		else if(id==51){nazwaCzaru = "Lekkie Uzdrowienie"; kosztMany = 5; wartoscCzaru = 100; przelicznik=1.5; rodzajAnimacji=0; p1=0; p2=0; p3=0; p4=0; rodzajMagii = 2;varAtakuGracza = 0.8;}
	}

	void czarDefensywny()
	{
		if(uzytyCzar == 51)
		{
			postac.mp-=kosztMany;
			postac.hp+=int((postac.inteligencja+zliczInteligencje())*przelicznik);
			if (postac.hp> postac.maxhp) postac.hp =postac.maxhp;
			mciSendString("play sounds/heal.mp3 ",NULL,1,NULL);
			wyswietlNadGraczem(-int((postac.inteligencja+zliczInteligencje())*przelicznik),0,2);
		}
		else if (uzytyCzar == 50)
		{
			postac.mp-=kosztMany;
			turaPrzyspieszeniaGracza = 3;
			odtworzDzwiek("przyspieszenie.mp3|");
		}
		else if (uzytyCzar = 52)
		{
			postac.mp-=kosztMany;
			turaSpowolnieniaPotwora = 3;
			poslijPocisk(174,10);
			odtworzDzwiek("spowolnienie.wav|");

		}
		odswiezEkranWalki();
		timerGracza = 0;

	}

	void czarOfensywny()
	{
		postac.mp-=kosztMany;
		czyTrafienieKrytyczne = 0;
		dmg = int((rand() % 7)*0.1*postac.inteligencja + (postac.inteligencja+zliczInteligencje())*przelicznik);
		odswiezEkranWalki();
		if (czyTrafienieKrytyczne==1)
			odtworzDzwiek("thunder3.wav|"); 
		else
			odtworzDzwiek("thunder1.wav|thunder2.wav|");
		if(rodzajAnimacji==1)
			poslijPocisk(p1,p2);
		else if(rodzajAnimacji==2)
			poslijPociskDlugi(p1,p2);
		else if(rodzajAnimacji==3)
			poslijPociskDlugiWybuchowy(p1,p2,p3,p4);
		if ( ((rand() % 99)+1)< crit)
		{
			czyTrafienieKrytyczne = 1;
			dmg=int(dmg*1.5);
		}
		else
			czyTrafienieKrytyczne = 0;
		timerGracza = 0;
		if (timerPotwora>=50) timerPotwora -= 50;
		if(stanDefensywnyPotwora == true) dmg=dmg/2;
		hpPotwora= hpPotwora-dmg;
		odswiezEkranWalki(true);
		wyswietlNadWrogiem(dmg,czyTrafienieKrytyczne,12);
	}

	void pokazitem(int czyPrzedmiotPosiadany)
	{
		cout << nazwaitemu << " || Wartosc: " << wartoscPrzedmiotu;
		if (czyPrzedmiotPosiadany == 1) cout << " (Posiadasz)\n";
		if (czyPrzedmiotPosiadany  == 2 ) cout <<" (Nosisz)\n";
		if (czyPrzedmiotPosiadany == 0 ) cout << endl;
		cout<< "\t";
		if(obrona!=0 && atak!=0)
			cout << "Obrona: "<<obrona <<" || Atak: "<<atak;
		else if(obrona!=0)
			cout << "Obrona: "<<obrona;
		else if(atak!=0)
			cout << "Atak: " <<atak;
		if(iSila>0)
			cout << " || Sila: " <<iSila;
		if(iZrecznosc>0)
			cout << " || Zrecznosc: " <<iZrecznosc;
		if(iInteligencja>0)
			cout << " || Inteligencja: " <<iInteligencja;
		cout <<endl;
	}

	string wyswietlItem(int idItemu)
	{
		string ciagZnakow;
		items(idItemu);
		if(obrona>atak)
			ciagZnakow = nazwaitemu +string(" # ") + to_string(obrona) + string(" # Wartosc: ") + to_string (wartoscPrzedmiotu);
		else
			ciagZnakow = nazwaitemu +string(" # ") + to_string(atak) + string(" # Wartosc: ") + to_string (wartoscPrzedmiotu);
		if (postac.posiadanePrzedmioty[idItemu] == 1) ciagZnakow= ciagZnakow + " (Posiadasz)";
		if (postac.posiadanePrzedmioty[idItemu] == 2 ) ciagZnakow= ciagZnakow + " (Nosisz)";
		return ciagZnakow;
	}

	string wyswietlCzar(int idCzaru)
	{
		string ciagZnakow;
		magic(idCzaru);
		ciagZnakow = nazwaCzaru + string(" # Wartosc: ") + to_string (wartoscCzaru);
		if (postac.posiadaneCzary[idCzaru] == 1) ciagZnakow= ciagZnakow + " (Posiadasz)";
		return ciagZnakow;
	}

	void ekwipunek()
	{
		system("cls");
		int ilezlota = 0;
		cout << "Zawartosc twojego ekwipunku:\n";
		int bylo1= 0,bylo2= 0,bylo3= 0,bylo4= 0,bylo5= 0,bylo6 = 0,bylo7=0,bylo8=0;
		for (int i =1;i<200;i++){
			items(i);
			if (postac.posiadanePrzedmioty[i]==1 || postac.posiadanePrzedmioty[i]==2)
			{
				if (i>=0 && i<20 && bylo1==0) {bialy();cout << "\nHelmy:\n";szary(); bylo1=1;}
				if (i>=20 && i<40 && bylo2==0) {bialy();cout << "\nZbroje:\n";szary(); bylo2 =1;}
				if (i>=40 && i<60 && bylo3==0) {bialy();cout << "\nButy:\n";szary(); bylo3 =1;}
				if (i>=60 && i<80 && bylo4==0) {bialy();cout << "\nSpodnie:\n";szary(); bylo4 =1;}
				if (i>=80 && i<100 && bylo5==0) {bialy();cout << "\nRekawice:\n";szary(); bylo5 =1;}
				if (i>=100 && i<120 && bylo6==0) {bialy();cout << "\nTarcze:\n";szary(); bylo6 =1;}
				if (i>=120 && i<140 && bylo7==0) {bialy();cout << "\nBronie jednoreczne:\n";szary(); bylo7 =1;}
				if (i>=140 && i<200 && bylo8==0) {bialy();cout << "\nBronie dwureczne:\n";szary(); bylo8 =1;}
				pokazitem(postac.posiadanePrzedmioty[i]);
				ilezlota = ilezlota+ wartoscPrzedmiotu;
			}
		}
		cout << endl<<endl << "Wartosc twojego ekwipunku: " << ilezlota << " sztuk zlota";
		cout << endl << endl;
		system("pause");
	}

	void wybory(int ktoryPrzedmiot)
	{     
		items(ktoryPrzedmiot);
		system("cls");
		if (postac.posiadanePrzedmioty[ktoryPrzedmiot] ==1 || postac.posiadanePrzedmioty[ktoryPrzedmiot]==2)
		{
			ramkaWyboru("Co chcialbys zrobic z " + nazwaitemu + string("?"),"Sprzedac za " + to_string(int(wartoscPrzedmiotu/1.2)) + string(" sztuk zlota|Ubrac|Powrot...|"));
			if (wybor == 1)
			{
				postac.posiadanePrzedmioty[ktoryPrzedmiot]=0; 
				postac.zloto = int(postac.zloto+wartoscPrzedmiotu/1.2);
				mciSendString("play sounds/goldu.wav ",NULL,1,NULL);
				ramkaInformacji("Sprzedales " + nazwaitemu +string(" za ") + to_string(int(wartoscPrzedmiotu/1.2)) +string(" sztuk zlota"));
			}
			else if (wybor == 2)
			{
				mciSendString("play sounds/cloth.wav ",NULL,1,NULL);
				if (ktoryPrzedmiot<20)for (int i=1;i<20;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
				if (ktoryPrzedmiot>=20 && ktoryPrzedmiot<40)for (int i=20;i<40;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
				if (ktoryPrzedmiot>=40 && ktoryPrzedmiot<60)for (int i=40;i<60;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
				if (ktoryPrzedmiot>=60 && ktoryPrzedmiot<80) for (int i=60;i<80;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
				if (ktoryPrzedmiot>=80 && ktoryPrzedmiot<100)for (int i=80;i<100;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
				if (ktoryPrzedmiot>=100 && ktoryPrzedmiot<120){
					for (int i=100;i<120;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
					for (int i=140;i<200;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}}
				if (ktoryPrzedmiot>=120 && ktoryPrzedmiot<140){
					for (int i=120;i<140;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
					for (int i=140;i<200;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}}
				if (ktoryPrzedmiot>=140 && ktoryPrzedmiot<200){
					for (int i=140;i<200;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
					for (int i=100;i<120;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
					for (int i=120;i<140;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}}
				postac.posiadanePrzedmioty[ktoryPrzedmiot]=2;
			}
			else
				return;
		}
		else
		{
			ramkaWyboru("Co chcialbys zrobic z " + nazwaitemu + string("?"),"Kupic za " + to_string(int(wartoscPrzedmiotu)) + string(" sztuk zlota|Powrot...|"));
			if (wybor == 1)
			{
				if (postac.zloto >= wartoscPrzedmiotu){
					mciSendString("play sounds/goldd.wav ",NULL,1,NULL);
					postac.posiadanePrzedmioty[ktoryPrzedmiot]=1; 
					ramkaInformacji("Kupiles " + nazwaitemu +string(" za ") + to_string(int(wartoscPrzedmiotu)) +string(" sztuk zlota."));
					postac.zloto = postac.zloto-wartoscPrzedmiotu;
					ramkaWyboru("Czy chcesz ubrac przedmiot " + nazwaitemu + string("?"),"Tak|Nie|");
					if(wybor==1)
					{
						if (ktoryPrzedmiot<20)for (int i=1;i<20;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
						if (ktoryPrzedmiot>=20 && ktoryPrzedmiot<40)for (int i=20;i<40;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
						if (ktoryPrzedmiot>=40 && ktoryPrzedmiot<60)for (int i=40;i<60;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
						if (ktoryPrzedmiot>=60 && ktoryPrzedmiot<80) for (int i=60;i<80;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
						if (ktoryPrzedmiot>=80 && ktoryPrzedmiot<100)for (int i=80;i<100;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
						if (ktoryPrzedmiot>=100 && ktoryPrzedmiot<120){
							for (int i=100;i<120;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
							for (int i=140;i<200;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}}
						if (ktoryPrzedmiot>=120 && ktoryPrzedmiot<140){
							for (int i=120;i<140;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
							for (int i=140;i<200;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}}
						if (ktoryPrzedmiot>=140 && ktoryPrzedmiot<200){
							for (int i=140;i<200;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
							for (int i=100;i<120;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
							for (int i=120;i<140;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}}
						postac.posiadanePrzedmioty[ktoryPrzedmiot]=2; 
						mciSendString("play sounds/cloth.wav ",NULL,1,NULL);
					}
				}
				else
				{
					ramkaInformacji("Nie posiadasz " + to_string(wartoscPrzedmiotu) + string(" sztuk zlota."));
					return;
				}
			}
		}
	}

	void wyborCzaru(int ktoryCzar)
	{     
		magic(ktoryCzar);
		system("cls");
		if (postac.posiadaneCzary[ktoryCzar] ==1)
		{
			ramkaInformacji("Juz posiadasz ten czar.");
		}
		else
		{
			ramkaWyboru("Co chcialbys zrobic z " + nazwaCzaru + string("?"),"Kupic za " + to_string(int(wartoscCzaru)) + string(" sztuk zlota|Powrot...|"));
			if (wybor == 1)
			{
				if (postac.zloto >= wartoscCzaru){
					mciSendString("play sounds/goldd.wav ",NULL,1,NULL);
					postac.posiadaneCzary[ktoryCzar]=1; 
					ramkaInformacji("Kupiles " + nazwaCzaru +string(" za ") + to_string(int(wartoscCzaru)) +string(" sztuk zlota."));
					postac.zloto = postac.zloto-wartoscCzaru;
				}
				else
				{
					ramkaInformacji("Nie posiadasz " + to_string(wartoscCzaru) + string(" sztuk zlota."));
					return;
				}
			}
		}
	}

	//Helm od 1
	//Zbroja od 20
	//Buty od 40
	//Spodnie od 60
	//Rekawice od 80
	//Bronie od 100

	void kowal()
	{
		wylaczMuzyke();
		Sleep(100);
		int typ;
		mciSendString("play sounds/kowal.wav ",NULL,1,NULL);
		while(true)
		{
			ramkaWyboru("Co chcialbys zobaczyc?","Helmy|Zbroje|Buty|Spodnie|Rekawice|Tarcze|Bron jednoreczna|Bron dwureczna|Powrot...|");
			switch (wybor)
			{
			case 1:typ = 0; break;
			case 2:typ = 19;break;
			case 3:typ = 39;break;
			case 4:typ = 59;break;
			case 5:typ = 79;break;
			case 6:typ = 99;break;
			case 7:typ = 119;break;
			case 8:typ = 139;break;
			case 9:ramkaInformacji("Wyszedles...");return;break;
			}
			int tempInt = 1;
			tempTekst2 = "";
			tempTekst1 = "lol";
			while (true) 
			{
				wyswietlItem(tempInt+typ);
				if (tempTekst1 != nazwaitemu)
					tempTekst2 += wyswietlItem(tempInt+typ) + string("|");
				else
					break;
				tempTekst1 = nazwaitemu;
				tempInt++;
			}
			tempTekst2 +=  string("Powrot...|");
			ramkaWyboru("Co wybierasz?", tempTekst2);
			if (wybor != tempInt)
				wybory(wybor+typ);
			system("cls");
			pokaz();
		}
		wylaczMuzyke();
	}

	void mag()
	{
		wylaczMuzyke();
		Sleep(100);
		int typ;
		mciSendString("play sounds/alchemik.wav ",NULL,1,NULL);
		while(true)
		{
			ramkaWyboru("Witaj mlodziencze. Jaka magia Cie interesuje?","Ofensywna|Defensywna|Powrot|");
			switch (wybor)
			{
			case 1:
				typ=0;
				break;
			case 2:
				typ=49;
				break;
			case 3:
				ramkaInformacji("Zegnaj...");return;break;
			}
			int tempInt = 1;
			tempTekst2 = "";
			tempTekst1 = "lol";
			while (true) 
			{
				wyswietlCzar(tempInt+typ);
				if (tempTekst1 != nazwaCzaru)
					tempTekst2 += wyswietlCzar(tempInt+typ) + string("|");
				else
					break;
				tempTekst1 = nazwaCzaru;
				tempInt++;
			}
			tempTekst2 +=  string("Powrot...|");
			ramkaWyboru("Co wybierasz?", tempTekst2);
			if (wybor != tempInt)
				wyborCzaru(wybor+typ);
			system("cls");
			pokaz();
		}
		wylaczMuzyke();
	}

	void niebieski()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	}
	void bialy()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	void czerwony()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	}
	void zmienKolor(int jakiKolor)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), jakiKolor);
		//0   BLACK
		//1   BLUE
		//2   GREEN
		//3   CYAN
		//4   RED
		//5   MAGENTA
		//6   BROWN
		//7   LIGHTGRAY
		//8   DARKGRAY
		//9   LIGHTBLUE
		//10  LIGHTGREEN
		//11  LIGHTCYAN
		//12  LIGHTRED
		//13  LIGHTMAGENTA
		//14  YELLOW
		//15  WHITE
		//ustawianie tla = dodac ilosc szesnastek do koloru
	}
	void zolty()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);    
	}
	void szary()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	void czarny()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	}

	/*
	int klasa(int id)
	{
	if(id==1){nazwaklasy = "Rycerz"; }         //za kazdy lvl dodatkowe 2 obrona
	if(id==2){nazwaklasy = "Czarodziej"; obrona = 2;  wartoscPrzedmiotu = 220;} //za kazdy lvl dodatkowa mana
	if(id==3){nazwaklasy = "Lotrzyk"; obrona = 4;  wartoscPrzedmiotu = 420;}    //za kazdy lvl dodatkowy kryt
	if(id==4){nazwaklasy = "Barbarzynca"; obrona = 6;  wartoscPrzedmiotu = 620;}//za kazdy lvl dodatkowy dmg(?)
	}*/

	void gotoxy( int column, int line )
	{
		COORD coord;
		coord.X = column;
		coord.Y = line;
		SetConsoleCursorPosition(
			GetStdHandle( STD_OUTPUT_HANDLE ),
			coord
			);
	}

	int wherex()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD                      result;
		if (!GetConsoleScreenBufferInfo(
			GetStdHandle( STD_OUTPUT_HANDLE ),
			&csbi
			))
			return -1;
		return result.X;
	}

	int wherey()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD                      result;
		if (!GetConsoleScreenBufferInfo(
			GetStdHandle( STD_OUTPUT_HANDLE ),
			&csbi
			))
			return -1;
		return result.Y;
	}

	void logo()
	{
		ifstream wczytajpoziom;
		wczytajpoziom.open("poziomy/logo.txt",ios::in);
		for (int i=0;i<40;i++)
			for (int j=0;j<81;j++){
				wczytajpoziom >>sciana[j][i];}
			wczytajpoziom.close();
	}

	void level(int ktoryPoziom)
	{
		ifstream wczytajpoziom;
		tempTekst1 = "poziomy/poziom " + to_string(ktoryPoziom) + string(".txt");
		wczytajpoziom.open(tempTekst1,ios::in);
		for (int i=0;i<40;i++)
			for (int j=0;j<81;j++){
				wczytajpoziom >>sciana[j][i];}
			wczytajpoziom >> x;
			wczytajpoziom >> y;
			wczytajpoziom.close();
			postac.wybranyPoziom= ktoryPoziom;
			trudnoscPoziomu = ktoryPoziom;
	}

	int randus;
	//void krok()
	//{
	//	/*if (randus==0)mciSendString("stop sounds/krok1.wav ",NULL,1,NULL);
	//	if (randus==1)mciSendString("stop sounds/krok2.wav ",NULL,1,NULL);
	//	if (randus==2)mciSendString("stop sounds/krok3.wav ",NULL,1,NULL);
	//	if (randus==3)mciSendString("stop sounds/krok4.wav ",NULL,1,NULL);*/
	//	randus = (rand() % 3);
	//	if (randus==0)mciSendString("play sounds/krok1.wav ",NULL,1,NULL);
	//	if (randus==1)mciSendString("play sounds/krok2.wav ",NULL,1,NULL);
	//	if (randus==2)mciSendString("play sounds/krok3.wav ",NULL,1,NULL);
	//	if (randus==3)mciSendString("play sounds/krok4.wav ",NULL,1,NULL);
	//}

	void usedrzwi()
	{
		int randus = (rand() % 1);
		if (randus==0)mciSendString("play sounds/drzwi1.wav ",NULL,1,NULL);
		if (randus==1)mciSendString("play sounds/drzwi2.wav ",NULL,1,NULL);
		if (wktora==1){gotoxy(x-1,y);sciana[x-1][y]= 0; cout << " ";}
		if (wktora==2){gotoxy(x+1,y);sciana[x+1][y]= 0; cout << " ";}
		if (wktora==3){gotoxy(x,y-1);sciana[x][y-1]= 0; cout << " ";}
		if (wktora==4){gotoxy(x,y+1);sciana[x][y+1]= 0; cout << " ";}
	}

	void usePotwor(int jaki,bool potworZaatakowal)
	{
		rodzajPotwora=jaki;
		if (potworZaatakowal == false)
		{
			if (wktora==1){sciana[x-1][y]= 0;}
			if (wktora==2){sciana[x+1][y]= 0;}
			if (wktora==3){sciana[x][y-1]= 0;}
			if (wktora==4){sciana[x][y+1]= 0;}
			walka(true);
		}
		else
			walka(false);
	}

	void useskrzynka()
	{
		int ilosczlota;
		otwarteskrzynki++;
		odtworzDzwiek("skrzynka1.wav|skrzynka2.wav|");
		if (postac.wybranyPoziom == 1) ilosczlota = (rand() % 20)+20;
		else if (postac.wybranyPoziom == 2) ilosczlota = (rand() % 30)+50;
		else if (postac.wybranyPoziom == 3) ilosczlota = (rand() % 100)+100;
		else if (postac.wybranyPoziom > 3) ilosczlota = (rand() % 100)+300;
		postac.zloto+=ilosczlota;
		if (wktora==1)sciana[x-1][y]= 0;
		else if (wktora==2)sciana[x+1][y]= 0;
		else if (wktora==3)sciana[x][y-1]= 0;
		else if (wktora==4)sciana[x][y+1]= 0;
		ramkaInformacji("Otrzymales " + to_string(ilosczlota) + string(" szt zlota.") +". Posiadasz teraz " + to_string(postac.zloto) + string(" szt zlota."));
		system("cls");
		wygrana = 1;
	};

	void resetEdytora()
	{
		for (int i=0;i<81;i++)
			for (int j=0;j<40;j++)
			{   
				if (sciana[i][j]==0){gotoxy(i,j);cout << " ";};
				if (sciana[i][j]==1){gotoxy(i,j);cout << scianka;};
				if (sciana[i][j]==2) {gotoxy(i,j);cout << white;};
				if (sciana[i][j]==3){gotoxy(i,j);czerwony();cout << white;szary();};
				if (sciana[i][j]==4) {gotoxy(i,j);cout << wyjscie;};
				if (sciana[i][j]==5) {gotoxy(i,j);cout << wejscie;};
				if (sciana[i][j]==6){gotoxy(i,j);cout << skrzynka;};
				if (sciana[i][j]==7) {gotoxy(i,j);cout << drzwi;};
				if (sciana[i][j]==8){gotoxy(i,j);cout << black;};
				if (sciana[i][j]==9){gotoxy(i,j);zolty();cout << black;szary();};
			}
			gotoxy(81,0);
			cout << "1";
			gotoxy(81,1);
			cout << scianka;
			gotoxy(81,3);
			cout << "2";
			gotoxy(81,4);
			cout << white;
			gotoxy(81,6);
			cout << "3";
			gotoxy(81,7);
			czerwony();cout << white;szary();
			gotoxy(81,9);
			cout << "4";
			gotoxy(81,10);
			cout << wyjscie;
			gotoxy(81,12);
			cout << "5";
			gotoxy(81,13);
			cout << wejscie;
			gotoxy(81,15);
			cout << "6";
			gotoxy(81,16);
			cout << skrzynka;
			gotoxy(81,18);
			cout << "7";
			gotoxy(81,19);
			cout << drzwi;
			gotoxy(81,21);
			cout << "8";
			gotoxy(81,22);
			cout << black;
			gotoxy(81,24);
			cout << "9";
			gotoxy(81,25);zolty();
			cout << black;szary();
			gotoxy(0,40);
			cout <<"Lshift-przyspieszenie, q-wymazywanie, s-zapis, r-reset, g-ustaw respawn ESC-wyjdz";
	}

	void range() // kwintesencja zawzietosci ludzkiej: krzywa wieza ifow
	{
		for (int i = 0; i<41;i++)
			for (int j = 0; j<81;j++)
				r[j][i]=0;
		if(x>2)r[x-3][y-6]=5;if(x>1)r[x-2][y-6]=5;if(x>0)r[x-1][y-6]=5;r[x][y-6]=5;r[x+1][y-6]=5;r[x+2][y-6]=5;r[x+3][y-6]=5;    
		if(x>3)r[x-4][y-5]=5;if(x>2)r[x-3][y-5]=1;if(x>1)r[x-2][y-5]=1;if(x>0)r[x-1][y-5]=1;r[x][y-5]=1;r[x+1][y-5]=1;r[x+2][y-5]=1;r[x+3][y-5]=1;r[x+4][y-5]=5;
		if(x>4)r[x-5][y-4]=5;if(x>3)r[x-4][y-4]=1;if(x>2)r[x-3][y-4]=3;if(x>1)r[x-2][y-4]=3;if(x>0)r[x-1][y-4]=3;r[x][y-4]=3;r[x+1][y-4]=3;r[x+2][y-4]=3;r[x+3][y-4]=3;r[x+4][y-4]=1;r[x+5][y-4]=5;
		if(x>5)r[x-6][y-3]=5;if(x>4)r[x-5][y-3]=1;if(x>3)r[x-4][y-3]=3;if(x>2)r[x-3][y-3]=2;if(x>1)r[x-2][y-3]=2;if(x>0)r[x-1][y-3]=2;r[x][y-3]=2;r[x+1][y-3]=2;r[x+2][y-3]=2;r[x+3][y-3]=2;r[x+4][y-3]=3;r[x+5][y-3]=1;r[x+6][y-3]=5;
		if(x>6)r[x-7][y-2]=5;if(x>5)r[x-6][y-2]=1;if(x>4)r[x-5][y-2]=3;if(x>3)r[x-4][y-2]=2;if(x>2)r[x-3][y-2]=2;if(x>1)r[x-2][y-2]=2;if(x>0)r[x-1][y-2]=2;r[x][y-2]=2;r[x+1][y-2]=2;r[x+2][y-2]=2;r[x+3][y-2]=2;r[x+4][y-2]=2;r[x+5][y-2]=3;r[x+6][y-2]=1;r[x+7][y-2]=5;
		if(x>7)r[x-8][y-1]=5;if(x>6)r[x-7][y-1]=1;if(x>5)r[x-6][y-1]=3;if(x>4)r[x-5][y-1]=2;if(x>3)r[x-4][y-1]=2;if(x>2)r[x-3][y-1]=2;if(x>1)r[x-2][y-1]=2;if(x>0)r[x-1][y-1]=2;r[x][y-1]=2;r[x+1][y-1]=2;r[x+2][y-1]=2;r[x+3][y-1]=2;r[x+4][y-1]=2;r[x+5][y-1]=2;r[x+6][y-1]=3;r[x+7][y-1]=1;r[x+8][y-1]=5;
		if(x>7)r[x-8][y]=5;if(x>6)r[x-7][y]=1;if(x>5)r[x-6][y]=3;if(x>4)r[x-5][y]=2;if(x>3)r[x-4][y]=2;if(x>2)r[x-3][y]=2;if(x>1)r[x-2][y]=2;if(x>0)r[x-1][y]=2;r[x][y]=2;r[x+1][y]=2;r[x+2][y]=2;r[x+3][y]=2;r[x+4][y]=2;r[x+5][y]=2;r[x+6][y]=3;r[x+7][y]=1;r[x+8][y]=5;
		if(x>7)r[x-8][y+1]=5;if(x>6)r[x-7][y+1]=1;if(x>5)r[x-6][y+1]=3;if(x>4)r[x-5][y+1]=2;if(x>3)r[x-4][y+1]=2;if(x>2)r[x-3][y+1]=2;if(x>1)r[x-2][y+1]=2;if(x>0)r[x-1][y+1]=2;r[x][y+1]=2;r[x+1][y+1]=2;r[x+2][y+1]=2;r[x+3][y+1]=2;r[x+4][y+1]=2;r[x+5][y+1]=2;r[x+6][y+1]=3;r[x+7][y+1]=1;r[x+8][y+1]=5;
		if(x>6)r[x-7][y+2]=5;if(x>5)r[x-6][y+2]=1;if(x>4)r[x-5][y+2]=3;if(x>3)r[x-4][y+2]=2;if(x>2)r[x-3][y+2]=2;if(x>1)r[x-2][y+2]=2;if(x>0)r[x-1][y+2]=2;r[x][y+2]=2;r[x+1][y+2]=2;r[x+2][y+2]=2;r[x+3][y+2]=2;r[x+4][y+2]=2;r[x+5][y+2]=3;r[x+6][y+2]=1;r[x+7][y+2]=5;
		if(x>5)r[x-6][y+3]=5;if(x>4)r[x-5][y+3]=1;if(x>3)r[x-4][y+3]=3;if(x>2)r[x-3][y+3]=2;if(x>1)r[x-2][y+3]=2;if(x>0)r[x-1][y+3]=2;r[x][y+3]=2;r[x+1][y+3]=2;r[x+2][y+3]=2;r[x+3][y+3]=2;r[x+4][y+3]=3;r[x+5][y+3]=1;r[x+6][y+3]=5;
		if(x>4)r[x-5][y+4]=5;if(x>3)r[x-4][y+4]=1;if(x>2)r[x-3][y+4]=3;if(x>1)r[x-2][y+4]=3;if(x>0)r[x-1][y+4]=3;r[x][y+4]=3;r[x+1][y+4]=3;r[x+2][y+4]=3;r[x+3][y+4]=3;r[x+4][y+4]=1;r[x+5][y+4]=5;
		if(x>3)r[x-4][y+5]=5;if(x>2)r[x-3][y+5]=1;if(x>1)r[x-2][y+5]=1;if(x>0)r[x-1][y+5]=1;r[x][y+5]=1;r[x+1][y+5]=1;r[x+2][y+5]=1;r[x+3][y+5]=1;r[x+4][y+5]=5;
		if(x>2)r[x-3][y+6]=5;if(x>1)r[x-2][y+6]=5;if(x>0)r[x-1][y+6]=5;r[x][y+6]=5;r[x+1][y+6]=5;r[x+2][y+6]=5;r[x+3][y+6]=5;
	}

	void zielony(){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	}

	void wczytnick(int ktoryTekst)
	{
		sciezka[0]= 's';
		sciezka[1]= 'a';
		sciezka[2]= 'v';
		sciezka[3]= 'e';
		sciezka[4]= '\\';
		ilestam = -1;
		sprawdz(ktoryTekst);
		zapamietaj = 0;
		for (int g = 5; g<ilestam+5;g++) {sciezka[g]=nick[zapamietaj];zapamietaj++;};
		sciezka[zapamietaj+5] = '.';
		sciezka[zapamietaj+6] = 's';
		sciezka[zapamietaj+7] = 'a';
		sciezka[zapamietaj+8] = 'v';
	}

	void sprawdz(int ktoryTekst)
	{
		litera = 1;
		ilestam++;
		while (litera != 13){
			system("CLS");
			ramka();
			gotoxy(18,14);
			if (ktoryTekst ==1)
				cout << "  Podaj nick do stworzenia nowego zapisu:";
			else
				cout << "      Podaj nick do wczytania zapisu:";
			gotoxy(39-ilestam/2,16);
			for (int b = 0; b<ilestam;b++)
				cout << nick[b];
			litera=_getch();
			mciSendString("stop sounds/skrot.wav ",NULL,1,NULL);
			mciSendString("play sounds/skrot.wav ",NULL,1,NULL);
			if (litera == 97) jaka = 'a';
			if (litera == 98) jaka = 'b';
			if (litera == 99) jaka = 'c';
			if (litera == 100) jaka = 'd';
			if (litera == 101) jaka = 'e';
			if (litera == 102) jaka = 'f';
			if (litera == 103) jaka = 'g';
			if (litera == 104) jaka = 'h';
			if (litera == 105) jaka = 'i';
			if (litera == 106) jaka = 'j';
			if (litera == 107) jaka = 'k';
			if (litera == 108) jaka = 'l';
			if (litera == 109) jaka = 'm';
			if (litera == 110) jaka = 'n';
			if (litera == 111) jaka = 'o';
			if (litera == 112) jaka = 'p';
			if (litera == 113) jaka = 'q';
			if (litera == 114) jaka = 'r';
			if (litera == 115) jaka = 's';
			if (litera == 116) jaka = 't';
			if (litera == 117) jaka = 'u';
			if (litera == 118) jaka = 'v';
			if (litera == 119) jaka = 'w';
			if (litera == 120) jaka = 'x';
			if (litera == 121) jaka = 'y';
			if (litera == 122) jaka = 'z';
			if (litera == 65) jaka = 'A';
			if (litera == 66) jaka = 'B';
			if (litera == 67) jaka = 'C';
			if (litera == 68) jaka = 'D';
			if (litera == 69) jaka = 'E';
			if (litera == 70) jaka = 'F';
			if (litera == 71) jaka = 'G';
			if (litera == 72) jaka = 'H';
			if (litera == 73) jaka = 'I';
			if (litera == 74) jaka = 'J';
			if (litera == 75) jaka = 'K';
			if (litera == 76) jaka = 'L';
			if (litera == 77) jaka = 'M';
			if (litera == 78) jaka = 'N';
			if (litera == 79) jaka = 'O';
			if (litera == 80) jaka = 'P';
			if (litera == 81) jaka = 'Q';
			if (litera == 82) jaka = 'R';
			if (litera == 83) jaka = 'S';
			if (litera == 84) jaka = 'T';
			if (litera == 85) jaka = 'U';
			if (litera == 86) jaka = 'V';
			if (litera == 87) jaka = 'W';
			if (litera == 88) jaka = 'X';
			if (litera == 89) jaka = 'Y';
			if (litera == 90) jaka = 'Z';
			if (litera == 32) jaka = ' ';
			if (litera == 48) jaka = '0';
			if (litera == 49) jaka = '1';
			if (litera == 50) jaka = '2';
			if (litera == 51) jaka = '3';
			if (litera == 52) jaka = '4';
			if (litera == 53) jaka = '5';
			if (litera == 54) jaka = '6';
			if (litera == 55) jaka = '7';
			if (litera == 56) jaka = '8';
			if (litera == 57) jaka = '9';
			if (litera == 58) jaka = ';';
			if (litera == 41) jaka = ')';
			if (litera == 40) jaka = '(';
			if (litera == 94) jaka = '^';
			if (litera == 43) jaka = '+';
			if (litera == 37) jaka = '%';
			if (litera == 64) jaka = '@';
			if (litera == 46) jaka = '.';
			if (litera == 44) jaka = ',';
			if (litera == 61) jaka = '=';
			if (litera == 95) jaka = '_';
			if (litera == 33) jaka = '!';
			if (litera == 45) jaka = '-';
			if (litera == 63) jaka = '?';
			if (litera == 32) jaka = ' ';
			if ((litera != 13) && (litera !=8)){
				nick[ilestam] = jaka;
				cout << jaka;
				ilestam++;
			}
			if (litera == 8) {
				if (ilestam>zapamietaj+1) { nick[ilestam] = ' ';ilestam--;}}
		}
	}

	void zmienPozycje(int jakiPotwor, int numerPotwora,int i,int j)
	{
		int gdzie =(rand() % 4);
		if (gdzie == 0){
			if ((x==i-1)&&(y==j)){usePotwor(jakiPotwor,true);sciana[i][j]=0;}else
				if (sciana[i-1][j]==0){
					gotoxy(i,j);cout << " ";
					if(r[i][j]!=0){gotoxy(i-1,j);cout << white;}
					sciana[i][j]=0;sciana[i-1][j]=numerPotwora;
				}}
		if (gdzie == 1){
			if ((x==i+1)&&(y==j)){usePotwor(jakiPotwor,true);sciana[i][j]=0;}else
				if (sciana[i+1][j]==0){
					gotoxy(i,j);cout << " ";
					if(r[i][j]!=0){gotoxy(i+1,j);cout << white;}
					sciana[i][j]=0;sciana[i+1][j]=numerPotwora;
				}}
		if (gdzie == 2){              
			if ((x==i)&&(y==j-1)){usePotwor(jakiPotwor,true);sciana[i][j]=0;}else                   
				if (sciana[i][j-1]==0){
					gotoxy(i,j);cout << " ";
					if(r[i][j]!=0){gotoxy(i,j-1);cout << white;}
					sciana[i][j]=0;sciana[i][j-1]=numerPotwora;
				}}
		if (gdzie == 3){                 
			if ((x==i)&&(y==j+1)){usePotwor(jakiPotwor,true);sciana[i][j]=0;}else                
				if (sciana[i][j+1]==0){
					gotoxy(i,j);cout << " ";
					if(r[i][j]!=0){gotoxy(i,j+1);cout << white;}
					sciana[i][j]=0;sciana[i][j+1]=numerPotwora;}
		}
	}

	void tura()
	{
		for (int j = 0; j<41;j++){
			for (int i = 0; i<81;i++){
				if (sciana[i][j] == 2)
					zmienPozycje(1,2,i,j);
				else if (sciana[i][j] == 3)
					zmienPozycje(2,3,i,j);
				else if (sciana[i][j] == 8)
					zmienPozycje(3,8,i,j);
			}
		}
	}           

	void zapiszMape()
	{
		ofstream plik;  
		tempTekst1 = "poziomy/poziom " + to_string(postac.wybranyPoziom) + string(".txt");
		plik.open(tempTekst1,ios::in);
		for (int i=0;i<40;i++)
			for (int j=0;j<81;j++)
				plik << sciana[j][i]<<endl;
		plik << respawnX<<endl;
		plik << respawnY<<endl;
		plik.close();
		ramkaInformacji("Pomyslnie zapisano stan mapy");
	}

	void edytor ()
	{
		int b=0;
		/*if(!wczytajpoziom1) {
		cout << "ERROR";
		system("pause");
		return 1;
		}*/
		level(wybor);
		respawnX = x;
		respawnY = y;
		resetEdytora();
		while(1>0){
			if (GetAsyncKeyState(VK_LSHIFT))
			{
				Sleep(100);
			}
			else
				Sleep(300);
			if (GetAsyncKeyState(VK_LEFT))
			{
				if (x>0){
					gotoxy(x,y);
					if (sciana[x][y]==0){cout << " ";};
					if (sciana[x][y]==1){cout << scianka;};
					if (sciana[x][y]==2) {cout << white;};
					if (sciana[x][y]==3){czerwony();cout << white;szary();};
					if (sciana[x][y]==4) {cout << wyjscie;};
					if (sciana[x][y]==5) {cout << wejscie;};
					if (sciana[x][y]==6){cout << skrzynka;};
					if (sciana[x][y]==7) {cout << drzwi;};
					if (sciana[x][y]==8){cout << black;};
					if (sciana[x][y]==9){zolty();cout << black;szary();};
					x--;
					b=0;
				}
			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				if (x==80){}
				else{

					gotoxy(x,y);
					if (sciana[x][y]==0){cout << " ";};
					if (sciana[x][y]==1){cout << scianka;};
					if (sciana[x][y]==2) {cout << white;};
					if (sciana[x][y]==3){czerwony();cout << white;szary();};
					if (sciana[x][y]==4) {cout << wyjscie;};
					if (sciana[x][y]==5) {cout << wejscie;};
					if (sciana[x][y]==6){cout << skrzynka;};
					if (sciana[x][y]==7) {cout << drzwi;};
					if (sciana[x][y]==8){cout << black;};
					if (sciana[x][y]==9){zolty();cout << black;szary();};
					x++;
					b=0;
				}
			}
			if (GetAsyncKeyState(VK_UP))
			{
				if (y>0)
				{
					gotoxy(x,y);
					if (sciana[x][y]==0){cout << " ";};
					if (sciana[x][y]==1){cout << scianka;};
					if (sciana[x][y]==2) {cout << white;};
					if (sciana[x][y]==3){czerwony();cout << white;szary();};
					if (sciana[x][y]==4) {cout << wyjscie;};
					if (sciana[x][y]==5) {cout << wejscie;};
					if (sciana[x][y]==6){cout << skrzynka;};
					if (sciana[x][y]==7) {cout << drzwi;};
					if (sciana[x][y]==8){cout << black;};
					if (sciana[x][y]==9){zolty();cout << black;szary();};
					y--;
					b=0;
				}
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (y==39){}
				else
				{
					gotoxy(x,y);
					if (sciana[x][y]==0){cout << " ";};
					if (sciana[x][y]==1){cout << scianka;};
					if (sciana[x][y]==2) {cout << white;};
					if (sciana[x][y]==3){czerwony();cout << white;szary();};
					if (sciana[x][y]==4) {cout << wyjscie;};
					if (sciana[x][y]==5) {cout << wejscie;};
					if (sciana[x][y]==6){cout << skrzynka;};
					if (sciana[x][y]==7) {cout << drzwi;};
					if (sciana[x][y]==8){cout << black;};
					if (sciana[x][y]==9){zolty();cout << black;szary();};
					y++; 
					b=0;
				}
			}
			if (GetAsyncKeyState('Q')){sciana[x][y] = 0;}
			if (GetAsyncKeyState('1')){sciana[x][y] = 1;}
			if (GetAsyncKeyState('2')){sciana[x][y] = 2;}
			if (GetAsyncKeyState('3')){sciana[x][y] = 3;}
			if (GetAsyncKeyState('4')){sciana[x][y] = 4;}
			if (GetAsyncKeyState('5')){sciana[x][y] = 5;}
			if (GetAsyncKeyState('6')){sciana[x][y] = 6;}
			if (GetAsyncKeyState('7')){sciana[x][y] = 7;}
			if (GetAsyncKeyState('8')){sciana[x][y] = 8;}
			if (GetAsyncKeyState('9')){sciana[x][y] = 9;}
			if (GetAsyncKeyState('G')){
				ramkaInformacji("Pomyslnie ustawilem respawn na: " +to_string(x) + string(",") + to_string(y) + string("!"));
				respawnX = x;
				respawnY = y;
				system("cls");
				resetEdytora();
			}
			if (GetAsyncKeyState('R')){
				ramkaWyboru("Czy napewno chcesz przeladowac?","Tak|Nie|");
				if (wybor ==1){
					level(postac.wybranyPoziom);
					ramkaInformacji("Pomyslnie zresetowano stan mapy");
				}
				system("cls");
				resetEdytora();
			}
			if (GetAsyncKeyState(VK_ESCAPE)){                                         
				ramkaWyboru("Czy napewno chcesz wyjsc?","Tak|Nie|");
				if (wybor ==1){
					ramkaWyboru("Czy chcesz zapisac przed wyjsciem?","Tak|Nie|");
					if (wybor ==1){
						zapiszMape();
						return;
					}
					else 
					{
						system("cls");
						return;
					}
				}
				else
				{
					system("cls");
					resetEdytora();
				}
			}
			if (GetAsyncKeyState('S')){
				ramkaWyboru("Czy napewno chcesz zapisac?","Tak|Nie|");
				if (wybor ==1)
					zapiszMape();
				system("cls");
				resetEdytora();
			}
			gotoxy(x,y);
			if (b==0)
				cout << "O";
			if (b==1){
				gotoxy(x,y);
				if (sciana[x][y]==0){cout << " ";};
				if (sciana[x][y]==1){cout << scianka;};
				if (sciana[x][y]==2) {cout << white;};
				if (sciana[x][y]==3){czerwony();cout << white;szary();};
				if (sciana[x][y]==4) {cout << wyjscie;};
				if (sciana[x][y]==5) {cout << wejscie;};
				if (sciana[x][y]==6){cout << skrzynka;};
				if (sciana[x][y]==7) {cout << drzwi;};
				if (sciana[x][y]==8){cout << black;};
				if (sciana[x][y]==9){zolty();cout << black;szary();};
			}
			b++;
			if (b==2)b=0;
		}
	}

	void glowne()
	{
		while(true)
		{
			mciSendString("stop sounds/death.mp3 ",NULL,1,NULL);
			int p=0;
			SetConsoleTitle( "Menu glowne");
			mciSendString("play sounds/intro.MID ",NULL,1,NULL);
			postac.posiadanePrzedmioty[120] = 2;
			postac.posiadaneCzary[51] = 1;
			system("cls");
			logo();
			for (int i=0;i<81;i++)
				for (int j=0;j<40;j++)
				{   
					if (sciana[i][j]==0){gotoxy(i,j);cout << " ";};
					if (sciana[i][j]==1){gotoxy(i,j);cout << scianka;};
					if (sciana[i][j]==2){gotoxy(i,j);cout << white;};
					if (sciana[i][j]==3){gotoxy(i,j);czerwony();cout << white;szary();};
					if (sciana[i][j]==4){gotoxy(i,j);cout << wyjscie;};
					if (sciana[i][j]==5){gotoxy(i,j);cout << wejscie;};
					if (sciana[i][j]==6){gotoxy(i,j);cout << skrzynka;};
					if (sciana[i][j]==7){gotoxy(i,j);cout << drzwi;};
					if (sciana[i][j]==8){gotoxy(i,j);cout << black;};
					if (sciana[i][j]==9){gotoxy(i,j);zolty();cout << black;szary();};
				}
				gotoxy(68,40);
				cout << "ver. beta 0.5";
				gotoxy(10,20);
				cout << "Witaj w menu glownym!";
				menuWyboru(18,22,"Nowa gra|Wczytaj gre|Edytor mapy|");
				if (wybor == 1)
				{
					while (p==0){
						wczytnick(1);
						if (nick[0] == NULL) {postac.hp = 0;ramkaInformacji("Podano nieprawidlowa nazwe zapisu"); return;}
						plik.open(sciezka,ios::in |ios::out);
						if(plik.is_open())
						{
							ramkaWyboru("Czy napewno chcialbys nadpisac swoja poprzednia gre?","Tak|Nie|");
							if (wybor == 1)
							{
								p=1;
								ofstream plik;                
								plik.open(sciezka,ios::out);
								plik << nick << endl << postac.poziom << endl << postac.doswiadczenie << endl << postac.maksymalneDoswiadczenie << endl << postac.hp << endl << postac.maxhp << endl << postac.mp << endl << postac.maxmp << endl << postac.sila << endl << postac.inteligencja << endl << postac.zrecznosc << endl << postac.budowa  << endl << postac.zloto << endl << postac.hppot << endl << postac.mppot << endl << postac.opoznienieTekstu << endl << autozapis;
								for (int i=1;i<200;i++)
									plik << endl << postac.posiadanePrzedmioty[i];
								for (int j=1;j<100;j++)
									plik << endl << postac.posiadaneCzary[j];
								plik.close();
								ramkaInformacji("Nadpisalem gre gracza:" +string(nick));
							}
							else
								p=0;
						}
						else
						{
							ofstream plik;      
							plik.open(sciezka,ios::out);
							plik << nick << endl << postac.poziom << endl << postac.doswiadczenie << endl << postac.maksymalneDoswiadczenie  << endl << postac.hp << endl << postac.maxhp << endl << postac.mp << endl << postac.maxmp << endl << postac.sila << endl << postac.inteligencja << endl << postac.zrecznosc << endl << postac.budowa  << endl << postac.zloto << endl << postac.hppot << endl << postac.mppot << endl << postac.opoznienieTekstu << endl << autozapis;
							for (int i=1;i<200;i++)
								plik << endl << postac.posiadanePrzedmioty[i];
							for (int j=1;j<100;j++)
								plik << endl << postac.posiadaneCzary[j];
							plik.close();
							p=1;
							ramkaInformacji("Stworzylem nowy plik postaci pod nazwa:" +string(nick));
						}
					}
					mciSendString("stop sounds/intro.MID ",NULL,1,NULL);
					SetConsoleTitle( nick );
					return;
				}
				else if (wybor == 2)
				{
					system("cls");
					wczytnick(2);
					zplik.open(sciezka,ios::in);
					zplik>>nick >>postac.poziom >>postac.doswiadczenie >>postac.maksymalneDoswiadczenie  >>postac.hp >>postac.maxhp >>postac.mp >>postac.maxmp >>postac.sila >>postac.inteligencja >>postac.zrecznosc >>postac.budowa  >>postac.zloto >>postac.hppot >>postac.mppot >>postac.opoznienieTekstu>>autozapis;
					for (int i=1;i<200;i++)
						zplik>>postac.posiadanePrzedmioty[i];
					for (int j=1;j<100;j++)
						zplik>>postac.posiadaneCzary[j];
					opusc = 0;
					zplik.close();
					mciSendString("stop sounds/intro.MID ",NULL,1,NULL);
					if (nick[0] == NULL) {postac.hp = 0;ramkaInformacji("Podano nieprawidlowa nazwe zapisu"); return;}
					SetConsoleTitle( nick );
					return;
				}
				else
				{
					ramkaWyboru("Wybierz poziom do zaladowania:","Poziom 1|Poziom 2|Poziom 3|Poziom 4|Poziom 5|Poziom 6|Poziom 7|Powrot|");
					if (wybor == 8) { postac.hp = 0; return;}
					edytor();
				}
		}
	}

	void reset()
	{
		range();
		for (int i=0;i<81;i++)
			for (int j=0;j<40;j++)
			{
				if (r[i][j]==5) {gotoxy(i,j);  cout << " ";}
				if (sciana[i][j]==1)
				{
					if (r[i][j]==1) { gotoxy(i,j); cout << wyjscie;};
					if (r[i][j]==3) { gotoxy(i,j); cout << wejscie;};
					if (r[i][j]==2) { gotoxy(i,j); cout << scianka;};      
				}
				if (sciana[i][j]==2) if((r[i][j]==1)||(r[i][j]==2)||(r[i][j]==3)) {gotoxy(i,j);cout << white;};
				if (sciana[i][j]==3) if((r[i][j]==1)||(r[i][j]==2)||(r[i][j]==3)){gotoxy(i,j);czerwony();cout << white;szary();};
				if (sciana[i][j]==4) if((r[i][j]==1)||(r[i][j]==2)||(r[i][j]==3)){gotoxy(i,j);cout << wyjscie;};
				if (sciana[i][j]==5) if((r[i][j]==1)||(r[i][j]==2)||(r[i][j]==3)){gotoxy(i,j);cout << wejscie;};
				if (sciana[i][j]==6) if((r[i][j]==1)||(r[i][j]==2)||(r[i][j]==3)){gotoxy(i,j);cout << skrzynka;};
				if (sciana[i][j]==7) if((r[i][j]==1)||(r[i][j]==2)||(r[i][j]==3)){gotoxy(i,j);cout << drzwi;};
				if (sciana[i][j]==8) if((r[i][j]==1)||(r[i][j]==2)||(r[i][j]==3)){gotoxy(i,j);cout << black;};
				if (sciana[i][j]==9) if((r[i][j]==1)||(r[i][j]==2)||(r[i][j]==3)){gotoxy(i,j);zolty();cout << black;szary();};
			}
	}

	void gameover()
	{
		wylaczMuzyke();
		mciSendString("play sounds/death.mp3 ",NULL,1,NULL);
		ramkaInformacji("Twoja postac nie zyje. Przegrales");
	}

	void sprawdzAkcjeIUzyj(int numerAkcji)
	{
		if (numerAkcji==7) usedrzwi();
		if (numerAkcji==2) usePotwor(1,false);
		if (numerAkcji==4) usewyjscie();
		if (numerAkcji==5) usewejscie();
		if (numerAkcji==6) useskrzynka();
		if (numerAkcji==3) usePotwor(2,false);
		if (numerAkcji==8) usePotwor(3,false);
		if (numerAkcji==9) usePotwor(4,false);
	}

	void labirynt()
	{
		system("cls");
		reset();
		postac.doswiadczenie=tempexp;
		iloscpotworow=0;
		int opozniaczTuryPotwora = 0;
		for (int i=0;i<81;i++)
			for (int j=0;j<40;j++)
			{
				if (sciana[i][j]==2) iloscpotworow++;
				if (sciana[i][j]==3) iloscpotworow++;
				if (sciana[i][j]==7) iloscskrzynek++;
			}
			zdobyteZloto=0;
			zdobyteDoswiadczenie=0;
			zabitepotwory=0;
			otwarteskrzynki=0;
			rodzajPotwora=0;
			wyszedlem =0;
			while (wyszedlem==0)
			{
				if (postac.hp<1) return;
				if (wygrana ==1)
				{
					reset();
					wygrana =0;
					wylaczMuzyke();
					Sleep(100);
					mciSendString("play sounds/ruins.wav ",NULL,1,NULL);
				}
				if (GetAsyncKeyState(VK_LEFT))
				{
					wktora = 1;
					if (sciana[x-1][y]==0)
					{
						odtworzDzwiek("krok1.wav|krok2.wav|krok3.wav|krok4.wav|");
						if (x>0)
							x--;
						reset();
						gotoxy(x+1,y);
						cout << " ";
					}
				}
				if (GetAsyncKeyState(VK_RIGHT))
				{
					wktora = 2;
					if (sciana[x+1][y]==0)
					{
						odtworzDzwiek("krok1.wav|krok2.wav|krok3.wav|krok4.wav|");
						x++;
						reset();
						gotoxy(x-1,y);
						cout << " ";
					}
				}
				if (GetAsyncKeyState(VK_UP))
				{
					wktora = 3;
					if (sciana[x][y-1]==0)
					{
						odtworzDzwiek("krok1.wav|krok2.wav|krok3.wav|krok4.wav|");
						if (y>0)
							y--;
						reset();
						gotoxy(x,y+1);
						cout << " ";
					}
				}
				if (GetAsyncKeyState(VK_DOWN))
				{
					wktora = 4;
					if (sciana[x][y+1]==0)
					{ 
						odtworzDzwiek("krok1.wav|krok2.wav|krok3.wav|krok4.wav|");
						y++;
						reset();
						gotoxy(x,y-1);
						cout << " ";
					}
				}
				if (GetAsyncKeyState('X'))
				{
					if (wktora==1)
						sprawdzAkcjeIUzyj(sciana[x-1][y]);
					else if (wktora==2)
						sprawdzAkcjeIUzyj(sciana[x+1][y]);
					else if (wktora==3)
						sprawdzAkcjeIUzyj(sciana[x][y-1]);
					else if (wktora==4)
						sprawdzAkcjeIUzyj(sciana[x][y+1]);
				}
				if (GetAsyncKeyState('Z'))
				{
					mikstury();
					system("CLS");
					reset();
				}
				gotoxy(x,y);
				if (wktora==1) cout << lewo;
				if (wktora==2) cout << prawo;
				if (wktora==3) cout << gora;
				if (wktora==4) cout << dol;
				if (postac.hp<1) return;
				pokaz();
				szary();
				gotoxy(0,39);
				cout << "Klawisze: x - akcja, z - sakiewka, strzalki - chodzenie";
				gotoxy(0,40);
				cout << skrzynka << " - skrzynia, "<< white << " - potwor, "; 
				czerwony();
				cout<<white;
				szary();
				cout << " - lepszy potwor, "<< wyjscie << " - wyjscie, " << wejscie << " - wejscie, " << drzwi << " - drzwi.";
				Sleep(50);
				if (opozniaczTuryPotwora == 4) //spowolnienie chodzenia potworow
				{
					opozniaczTuryPotwora = 0;
					tura();
				}
				opozniaczTuryPotwora++;
			}
			rodzajPotwora=0;
			wygrana = 1;
			if ((autozapis==1)&&(postac.hp>1)) save();
			return;
	}
	Gra();
};

Gra::Gra()
{
	SetConsoleTitle( "Menu glowne");
	system("MODE 82,41");
	inicjalizujCzcionke();
	inicjalizujZmienne();
	postac.resetujWartosci();
	HANDLE  hConsole;
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	srand ( (unsigned int)time(NULL) );  
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (true){
		//while (true) // while do szybkich testow
		//{
		//  string dlugistring;
		//for (int i = 0; i < 100; i++) dlugistring += (to_string(i) + string(" "));
		//	ramkaWyboru(dlugistring,"tak|nie|");
		//	cin.get();
		//}
		glowne();
		while (postac.hp>0)
			menu();
		inicjalizujZmienne();
		postac.resetujWartosci();
	}
}

int main()
{
	Gra rozgrywka;
	return 0; 
}
