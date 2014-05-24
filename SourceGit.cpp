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
	int szybkoscPotwora,szybkoscGracza;
	string nazwaitemu;
	ofstream plik;
	ifstream zplik;
	HANDLE hInput, hOutput;
	int rodzajPotwora,potdmgmax,potdmgmin,hpPotwora,potgold,typAtaku;
	bool czyZasiegowy;
	int crit;
	int czyPrzedmiotPosiadany;
	int wartoscPrzedmiotu;
	int obrona;
	int tempexp;
	int litera;
	bool wykonanoRuch;
	char jaka;
	unsigned int gdzie;
	string potw;
	int x;
	int respawnX;
	int y;
	int respawnY;
	int ktoryRuch;
	int maksymalneHpPotwora;
	int timerPotwora, timerGracza;
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
	int zliczdef()
	{
		int defik=0;
		for (int i=1;i<100;i++){
			items(i);
			if (postac.posiadanePrzedmioty[i]==2)
				defik=defik + obrona; 
		}
		return defik;
	}

	int zliczdmg()
	{
		int defik=0;
		for (int i=100;i<200;i++){
			items(i);
			if (postac.posiadanePrzedmioty[i]==2)
				defik=obrona;
		}
		return defik;
	}

	void ramka(int ileDodatkowo = 0)
	{
		ileDodatkowo = 5; // porzucamy to bo nie umiemy matematyki
		gotoxy(17,13-ileDodatkowo/2); cout << lewy_gorny; for (int i = 0; i<45;i++) cout << pozioma; cout << prawy_gorny;
		for (int i = 0; i<10+ileDodatkowo;i++){
			gotoxy(17,14+i-ileDodatkowo/2); cout << pionowa; for (int j = 0; j<45;j++) cout << " "; cout << pionowa;
		}
		gotoxy(17,24+ileDodatkowo/2); cout << lewy_dolny; for (int i = 0; i<45;i++) cout << pozioma; cout << prawy_dolny;   
	}

	void ramkaWyboru(string pytanie, string dluzszyTekst, string pytanie2 ="")
	{
		int i = 0;
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

		i=i-7;
		ramka(i);
		gotoxy(39-(pytanie.length())/2 +1,14-i/2);
		cout << pytanie;
		gotoxy(39-(pytanie2.length())/2 +1,15-i/2);
		cout << pytanie2;
		menuWyboru(39,16-i/2,dluzszyTekst);
	}

	void ramkaInformacji(string informacja, string informacja2 = "")
	{
		FlushConsoleInputBuffer(hInput);    
		ramka();
		gotoxy(39-(informacja.length())/2 +1,15);
		cout << informacja;
		gotoxy(39-(informacja2.length())/2 +1,16);
		cout << informacja2;
		gotoxy(19,20);
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

	void pas()
	{
		uzylmp=0;
		uzylhp=0;
		ramkaWyboru("Zawartosc pasa:",(string("Mikstura zdrowia: ") + to_string(postac.hppot) + string("|Mikstura many: ") + to_string(postac.mppot) + string("|Powrot|")));
		if (wybor == 1){
			if (postac.hppot <1) 
				ramkaInformacji("Masz za malo mikstur zdrowia:");
			else
			{
				postac.hp= postac.hp + 50 ;
				if (postac.hp> postac.maxhp) postac.hp =postac.maxhp;
				uzylhp = 1;
				postac.hppot=postac.hppot-1;
				ramkaInformacji("Uleczyles sie za 50 hp,",string("Posiadasz teraz ") + to_string(postac.hp) + string("hp."));
			}
		}
		if (wybor == 2){
			if (postac.mppot <1) 
				ramkaInformacji("Masz za malo mikstur many");
			else{
				postac.mp=postac.mp+5;
				if (postac.mp>postac.maxmp) postac.mp = postac.maxmp;
				ramkaInformacji("Ilosc aktualnie posiadanych punktow many","wzrosla do " + to_string(postac.mp));
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
	};

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
	};

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
		ramkaWyboru("Co chcesz zrobic?","Wyrusz...|Karczma|Kowal i ekwipunek|Alchemik|Zobacz statystyki postaci|Zapisz stan gry|Opcje|Lista Posiadanych przedmiotow|");
		if (wybor == 1)
		{
			ramkaWyboru("Gdzie chcialbys wyruszyc?", "Ayleid (latwy)|Dasek Moor (normalny)|Lochy cmentarza (normalny++)|Krypta Pacmana (chaos)|Sancre Tor (trudny)|Leze smoka (BOSS)|Powrot|");
			if (wybor !=8)
				level(wybor);
			else 
				return;
			labirynt();
		}
		else if (wybor == 2)
			karczma();
		else if (wybor == 3)
			kowal();
		else if (wybor == 4)
			alchemik();
		else if (wybor ==5 )
			staty();
		else if (wybor == 6)
			save();
		else if (wybor == 7)
			opcje();
		else if (wybor == 8)
			ekwipunek();
	}
	void odswiezEkranWalki(bool podczasRuchu = false)
	{
		gotoxy(3,15); cout << " ";
		for (int i = 0; i < 71; i++)
		{
			if (i>=50)zmienKolor(12);
			cout << char(219);
			szary();
		}
		cout << "    ";
		gotoxy(3,16);  cout << " ";
		for (int i = 0; i < 71; i++)
		{
			if (i>=50)zmienKolor(12);
			cout << char(219);
			szary();
		}
		cout << "    ";

		gotoxy(4+timerGracza,15); cout << prawo;
		gotoxy(4+timerPotwora,16); cout << white;

		gotoxy(30,3);
		cout << "     ";
		gotoxy(30,3);
		czerwony();cout<< postac.hp;szary();cout << "/";czerwony();cout << postac.maxhp;szary();
		gotoxy(31,4);cout << "     ";
		gotoxy(31,4);
		niebieski();cout << postac.mp ;szary();cout << "/" ;niebieski();cout << postac.maxmp;szary();
		gotoxy(45,3);cout << "     ";gotoxy(45,3);czerwony();cout << hpPotwora;szary();cout << "/";czerwony();cout << maksymalneHpPotwora;szary();
		if (podczasRuchu == false)
		{
			gotoxy(33,10);cout << prawo;
			if (rodzajPotwora == 2) czerwony(); //TODO: dokonczyc
			gotoxy(47,10);cout << white;
			szary();
		}
	}

	void ramkaAtaku(bool czyPotwor)
	{
		if (czyPotwor == true)
			tempTekst1 = "Zaatakowales " + potw + string("a!");
		else
			tempTekst1 = "Zostales zaatakowany przez " + potw + string("a!");
		tempTekst2 = "Potwor " + potw + string(" jest poziomu ");
		if (rodzajPotwora==1) tempTekst2 += "slabego.";
		else if (rodzajPotwora==2) tempTekst2 += "normalnego.";
		else if (rodzajPotwora==3) tempTekst2 += "mocnego.";
		else if (rodzajPotwora==4) tempTekst2 += "Legendarnego!";
		ramkaInformacji(tempTekst1,tempTekst2);
	}

	void podejdzDoWroga()
	{
		for (int i = 0; i<13;i++)
		{
			gotoxy(33+i,10);cout << " ";
			gotoxy(34+i,10);cout << prawo;
			Sleep(50);
		}  
	}
	void odejdzOdWroga()
	{
		for (int i = 0; i<13;i++)
		{
			gotoxy(46-i,10);cout << " ";
			gotoxy(45-i,10);cout << lewo;
			Sleep(50);
		}
		gotoxy(33,10);cout << prawo;
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
	void odtworzLosowyDzwiek(string listaDzwiekow)
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
	void poslijPocisk(char jakiZnaczek, int jakiKolor)
	{
		for (int i = 1; i<13;i++)
		{
			zmienKolor(jakiKolor);
			gotoxy(33+i,10);cout << " ";
			gotoxy(34+i,10);cout << jakiZnaczek;
			Sleep(50);
			szary();
		}  
		gotoxy(34+12,10); cout << " ";
	}
	void poslijPociskWGracza(char jakiZnaczek, int jakiKolor)
	{
		for (int i = 1; i<13;i++)
		{
			zmienKolor(jakiKolor);
			gotoxy(47-i,10);cout << " ";
			gotoxy(46-i,10);cout << jakiZnaczek;
			Sleep(50);
			szary();
		}  
		gotoxy(47-13,10);cout << " ";
	}
	void podejscieWroga()
	{
		for(int i=0;i<13;i++)
		{
			gotoxy(47-i,10);cout<<" ";
			gotoxy(46-i,10);cout<<white;
			Sleep(50);
		}
	}

	void odejscieWroga()
	{
		for(int i=0;i<13;i++)
		{
			gotoxy(34+i,10);cout<<" ";
			gotoxy(35+i,10);cout<<white;
			Sleep(50);
		}
	}
	void atakNormalnyGracza()
	{
		odswiezEkranWalki();
		dmg = int((rand() % 7)*0.1*postac.sila + postac.sila+zliczdmg());
		podejdzDoWroga();
		if ( ((rand() % 99)+1)< crit)
		{
			czyTrafienieKrytyczne = 1;
			dmg=int(dmg*1.5);
		}
		else
			czyTrafienieKrytyczne = 0;
		hpPotwora= hpPotwora-dmg;
		odswiezEkranWalki(true);
		if (czyTrafienieKrytyczne==1)
			odtworzLosowyDzwiek("krytyk.wav|krytyk2.mp3|krytyk3.mp3|");
		else
			odtworzLosowyDzwiek("hit1.wav|hit2.wav|hit3.wav|hit4.wav|hit5.mp3|");
		wyswietlNadWrogiem(dmg,czyTrafienieKrytyczne,3);
		odejdzOdWroga();
	}

	void uzycieCzaru()
	{
		if (wybor == 1)//uleczenie
		{
			postac.hp= postac.hp + int(postac.inteligencja*1.5) ;
			if (postac.hp> postac.maxhp) postac.hp =postac.maxhp;
			postac.mp=postac.mp-5;
			mciSendString("play sounds/heal.mp3 ",NULL,1,NULL);
			wyswietlNadGraczem(-50,0,2);
		}
		else if (wybor == 2)//ognisty podmuch
		{
			postac.mp-=5;
			czyTrafienieKrytyczne = 0;
			dmg = int((rand() % 7)*0.1*postac.inteligencja + postac.inteligencja*2);
			odswiezEkranWalki();
			poslijPocisk(12,12);
			if ( ((rand() % 99)+1)< crit)
			{
				czyTrafienieKrytyczne = 1;
				dmg=int(dmg*1.5);
			}
			else
				czyTrafienieKrytyczne = 0;
			hpPotwora= hpPotwora-dmg;
			odswiezEkranWalki(true);
			if (czyTrafienieKrytyczne==1)
				odtworzLosowyDzwiek("krytyk.wav|krytyk2.mp3|krytyk3.mp3|"); //TODO: zmienic na odglosy czarow
			else
				odtworzLosowyDzwiek("hit1.wav|hit2.wav|hit3.wav|hit4.wav|hit5.mp3|");//TODO: zmienic na odglosy czarow
			wyswietlNadWrogiem(dmg,czyTrafienieKrytyczne,12);
		}

	}
	void ruchGracza()
	{
		while (wykonanoRuch == false)
		{
			gotoxy(10,30);
			cout << "Twoj ruch?";
			menuWyboru(10,31,"Atakuj|Magia|Pas|",false);

			if (wybor == 1){
				wykonanoRuch = true;
				ktoryRuch = 1;
			}
			else if (wybor == 2)
			{
				ktoryRuch = 2;
				ramkaWyboru("Spellbook:", "Uzdrowienie za " + to_string(int(postac.inteligencja*1.5)) +string(" hp - 5 many|Ognisty Podmuch - 5 many|Powrot|"));
				system("cls");
				odswiezEkranWalki();
				if (wybor == 1)
					if(postac.mp <5)
					{
						ramkaInformacji("Niestety masz za malo punktow many");
						system("cls");
						odswiezEkranWalki();
					}
					else
					{
						wykonanoRuch = true;
						ktoryRuch = 2;
					}
				else if (wybor == 2)
				{
					if(postac.mp <5)
					{
						ramkaInformacji("Niestety masz za malo punktow many");
						system("cls");
						odswiezEkranWalki();
					}
					else
					{
						wykonanoRuch = true;
						ktoryRuch = 2;
					}
				}
			}
			else if (wybor == 3)//uzycie potionow jest natychmiastowe
			{
				pas();
				system("cls");
				odswiezEkranWalki();
				if (uzylhp==1){
					system("cls");
					odswiezEkranWalki();
					wykonanoRuch = true;
					ktoryRuch =0;
					timerGracza = 0;
					mciSendString("play sounds/heal.mp3 ",NULL,1,NULL);
					wyswietlNadGraczem(-50,0,2);
				}
				if (uzylmp==1){
					system("cls");
					ktoryRuch =0;
					timerGracza = 0;
					odswiezEkranWalki();
					wykonanoRuch = true;
					wyswietlNadGraczem(-10,0,9);
				}
			}
		}
		for (int i = 0; i < 5; i++)
		{
			gotoxy(10,30+i);
			cout << "           ";
		}

	}
	void ruchPotwora()
	{
		if (hpPotwora >0){
			int pdmg;
			odswiezEkranWalki();
			pdmg = potdmgmin+(rand()%7) -zliczdef();
			if (pdmg<0) pdmg = 0;
			postac.hp=postac.hp-pdmg;
			if (czyZasiegowy == false)
				podejscieWroga();
			else
				poslijPociskWGracza(5,12);
			odswiezEkranWalki(true);
			odtworzLosowyDzwiek("punch1.mp3|punch2.mp3|punch3.mp3|punch4.mp3|punch5.mp3|punch6.mp3|");
			wyswietlNadGraczem(pdmg,0,12);
			if (czyZasiegowy == false)
				odejscieWroga();
		}
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
			ramkaInformacji("Otrzymujesz " + to_string(potexp) + string(" punktow doswiadczenia!"),"Otrzymales " + to_string (potgold) + string(" sztuk zlota"));
			zdobyteDoswiadczenie=zdobyteDoswiadczenie+potexp;
			postac.doswiadczenie=postac.doswiadczenie+potexp;
			potgold = potgold+(rand()%20);
			zabitepotwory++;
			postac.zloto=postac.zloto+potgold;
			zdobyteZloto=zdobyteZloto+potgold;
		}
	}

	void walka(bool czyPotworZaatakowal)
	{
		FlushConsoleInputBuffer(hInput);    
		wylaczMuzyke();
		mciSendString("play sounds/walka.mp3 ",NULL,1,NULL);
		potwor();
		ramkaAtaku(czyPotworZaatakowal);
		maksymalneHpPotwora=hpPotwora;
		system("cls");
		timerPotwora= 0, timerGracza = 0;
		if (czyPotworZaatakowal==false)
			timerPotwora = 50;
		else
			timerGracza = 50;
		odswiezEkranWalki();
		szybkoscGracza = 2;
		ktoryRuch = 0;
		while (hpPotwora>0 && postac.hp>0)
		{
			FlushConsoleInputBuffer(hInput);    
			wykonanoRuch = false;
			odswiezEkranWalki(true);
			if (timerGracza >= 50)
			{
				if (ktoryRuch == 0)
					ruchGracza(); //RUCH GRACZA
				if (timerGracza >= 70)
				{
					if (ktoryRuch == 1)
					{
						atakNormalnyGracza();
						ktoryRuch = 0;
						if (timerPotwora>=50) timerPotwora -= 35;
						timerGracza = 0;
					}
					else if (ktoryRuch == 2)
					{
						uzycieCzaru();
						ktoryRuch = 0;
						if (timerPotwora>=50) timerPotwora -= 35;
						timerGracza = 0;
					}
				}
			}
			if (timerPotwora >= 50)
			{
				szybkoscPotwora=1;
				if (timerPotwora >= 70) 
				{
					ruchPotwora(); 
					ktoryRuch = 0;
					if (timerGracza>=50) timerGracza -= 25;
					timerPotwora = 0;
					szybkoscPotwora=2; //TODO: powrot do poprzedniej wartosci
				}
			}
			else
			{
				szybkoscPotwora=2;
			}
			if (postac.hp<1)
			{
				gameover();
				return;
			}
			sprawdzCzyPotworZyje();
			Sleep(100);
			timerPotwora+=szybkoscPotwora;
			if (timerPotwora>70)
				timerPotwora = 70;
			timerGracza+=szybkoscGracza;
			if (timerGracza>70)
				timerGracza = 70;
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
			if (k==0) {potw = "Szczur"; hpPotwora = 25; potdmgmin = 5;potgold=15;szybkoscPotwora=2;czyZasiegowy = false;}
			if (k==1) {potw = "Pajak"; hpPotwora = 30; potdmgmin = 6;potgold=25;szybkoscPotwora=2;czyZasiegowy = true; typAtaku = 5;}
			if (k==2) {potw = "Nietoperz"; hpPotwora = 45; potdmgmin = 7;potgold=45;szybkoscPotwora=2;czyZasiegowy = false;}
			if (k==3) {potw = "Ognik"; hpPotwora = 50; potdmgmin = 8;potgold=65;szybkoscPotwora=2;czyZasiegowy = true;}
			if (k==4) {potw = "Skunks"; hpPotwora = 55; potdmgmin = 9;potgold=65;szybkoscPotwora=2;czyZasiegowy = false;}
			if (k==5) {potw = "Lis"; hpPotwora = 60; potdmgmin = 10;potgold=65;szybkoscPotwora=2;czyZasiegowy = false;}
		}
		if (rodzajPotwora==2){
			if (k==0) {potw = "Szkielet"; hpPotwora = 180; potdmgmin = 20;potgold=150;szybkoscPotwora=2;czyZasiegowy = false;}
			if (k==1) {potw = "Goblin"; hpPotwora = 200; potdmgmin = 21;potgold=175;szybkoscPotwora=2;czyZasiegowy = false;}
			if (k==2) {potw = "Szaman"; hpPotwora = 220; potdmgmin = 22;potgold=200;szybkoscPotwora=2;czyZasiegowy = true; typAtaku = 4;}
			if (k==3) {potw = "Troll"; hpPotwora = 240; potdmgmin = 23;potgold=220;szybkoscPotwora=2;czyZasiegowy = true; typAtaku = 7;}
			if (k==4) {potw = "Elf"; hpPotwora = 260; potdmgmin = 24;potgold=220;szybkoscPotwora=2;czyZasiegowy = true; typAtaku = 15;}
			if (k==5) {potw = "Minotaur"; hpPotwora = 280; potdmgmin = 25;potgold=220;szybkoscPotwora=2;czyZasiegowy = false;}
		}
		if (rodzajPotwora==3){
			if (k==0) {potw = "Wampir"; hpPotwora = 400; potdmgmin = 35;potgold=280;szybkoscPotwora=2;czyZasiegowy = false;}
			if (k==1) {potw = "Duch"; hpPotwora = 420; potdmgmin = 36;potgold=300;szybkoscPotwora=2;czyZasiegowy = false;}
			if (k==2) {potw = "Ogr"; hpPotwora = 440; potdmgmin = 37;potgold=320;szybkoscPotwora=2;czyZasiegowy = true; typAtaku = 22;}
			if (k==3) {potw = "Wilkolak"; hpPotwora = 460; potdmgmin = 38;potgold=340;szybkoscPotwora=2;czyZasiegowy = false;}
			if (k==4) {potw = "Dzin"; hpPotwora = 480; potdmgmin = 39;potgold=340;szybkoscPotwora=2;czyZasiegowy = true; typAtaku = 8;}
			if (k==5) {potw = "Golem"; hpPotwora = 500; potdmgmin = 40;potgold=340;szybkoscPotwora=2;czyZasiegowy = false;}
		}
		if (rodzajPotwora==4){
			if (k==0) {potw = "Smok"; hpPotwora = 5000; potdmgmin = 80;potgold=5000;szybkoscPotwora=2;czyZasiegowy = true; typAtaku = 3;}
			else
			{potw = "Smok"; hpPotwora = 5000; potdmgmin = 80;potgold=5000;}
		}
		return potw;


	}

	void pokaz()
	{
		crit=int(sqrt(postac.zrecznosc)*4);
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
		cout <<zliczdef() ;
		szary();
		gotoxy(70,3);
		cout << "Dmg: ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		cout << postac.sila+zliczdmg();
		szary();
		cout << "-";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		cout  << 6*0.1*postac.sila + postac.sila+zliczdmg();
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
			ramkaInformacji("GRATULACJE! Awansowales na poziom: " + to_string(postac.poziom+1),"hp: " + to_string(postac.maxhp) + string("->") + to_string(postac.maxhp+postac.budowa*1.2) + string("   mp: " )+ to_string(postac.maxmp) + string("->") + to_string(postac.maxmp*1.4));
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
				ramkaInformacji("Czyli nic nie wybrales... ","Dlaczego zawracasz niepotrzebnie dupe?");
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
					ramkaInformacji("Kupiles " +to_string(ilosc) + string(" mikstur zdrowia za sume ") + to_string(250*ilosc) + string("sztuk zlota."),"Posiadasz teraz " +to_string(postac.hppot) + string(" mikstur zdrowia i ")+ to_string(postac.zloto) + string(" sztuk zlota")); 
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
					ramkaInformacji("Kupiles " +to_string(ilosc) + string(" mikstur many za sume ") + to_string(200*ilosc) + string("sztuk zlota."),"Posiadasz teraz " +to_string(postac.mppot) + string(" mikstur many i ")+ to_string(postac.zloto) + string(" sztuk zlota")); 
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
						ramkaInformacji("Niestety po ledwo przespanej nocy nie","czujesz by sen ci w czymkolwiek pomogl");
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
						ramkaInformacji("Po wyspanej nocy czujesz sie jak bog!","Zdobywasz " + to_string(postac.maksymalneDoswiadczenie*0.1) + string(" punktow doswiadczenia"));   
					}
					else 
						ramkaInformacji("Po wyspanej nocy w niebianskich warunkach","czujesz sie niezwykle orzezwiony."); 
				} 
				else 
					ramkaInformacji("Za wysokie progi na twoje nogi biedaku...","prosze wyjdz i nie wracaj");
			}

		} 
		wylaczMuzyke();
	}

	void staty()
	{
		system("cls");
		cout << "Poziom: " << postac.poziom <<"\nDoswiadczenie: "<< postac.doswiadczenie << "/" << postac.maksymalneDoswiadczenie<< "\nHP: " << postac.hp << "/" << postac.maxhp<< "\nMP: " << postac.mp << "/" << postac.maxmp<< "\n\nSila: "<<postac.sila<<"\nZrecznosc: "<<postac.zrecznosc<<"\nBudowa: " <<postac.budowa << "\nInteligencja: " << postac.inteligencja<<endl<<endl;
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
	//Bronie od 100

	void items(int id) 
	{
		if(id==1){nazwaitemu = "Skorzany kaptur"; obrona = 1; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 120;}
		if(id==2){nazwaitemu = "Kolczy czepiec"; obrona = 2; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 220;}
		if(id==3){nazwaitemu = "Zelazny helm"; obrona = 4; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 420;}
		if(id==4){nazwaitemu = "Stalowy helm"; obrona = 6; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 620;}
		if(id==5){nazwaitemu = "Szklany helm"; obrona = 8; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 860;}
		if(id==6){nazwaitemu = "Krasnoludzki szturmak"; obrona = 11; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 1200;}
		if(id==20){nazwaitemu = "Skorzana zbroja"; obrona = 5; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 500;}
		if(id==21){nazwaitemu = "Kolczuga"; obrona = 7; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 620;}
		if(id==22){nazwaitemu = "Zelazna zbroja"; obrona = 9; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 840;}
		if(id==23){nazwaitemu = "Stalowa zbroja"; obrona = 11; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 1200;}
		if(id==24){nazwaitemu = "Szklana zbroja"; obrona = 13; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 1500;}
		if(id==25){nazwaitemu = "Krasnoludzka zbroja"; obrona = 15; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 2000;}
		if(id==40){nazwaitemu = "Skorzane buty"; obrona = 2; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 240;}
		if(id==41){nazwaitemu = "Kolcze buty"; obrona = 3; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 370;}
		if(id==42){nazwaitemu = "Zelazne buty"; obrona = 4; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 500;}
		if(id==43){nazwaitemu = "Stalowe buty"; obrona = 6; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 715;}
		if(id==44){nazwaitemu = "Szklane buty"; obrona = 8; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 900;}
		if(id==45){nazwaitemu = "Krasnoludzkie buty"; obrona = 11; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 1200;}
		if(id==60){nazwaitemu = "Skorzane spodnie"; obrona = 3; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 300;}
		if(id==61){nazwaitemu = "Kolcze spodnie"; obrona = 5; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 450;}
		if(id==62){nazwaitemu = "Zelazne nagolenniki"; obrona = 7; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 600;}
		if(id==63){nazwaitemu = "Stalowe nagolenniki"; obrona = 9; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 700;}
		if(id==64){nazwaitemu = "Szklane nagolenniki"; obrona = 11; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 700;}
		if(id==65){nazwaitemu = "Krasnoludzkie nagolenniki"; obrona = 14; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 1600;}
		if(id==80){nazwaitemu = "Skorzane rekawice"; obrona = 1; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 100;}
		if(id==81){nazwaitemu = "Kolcze rekawice"; obrona = 2; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 200;}
		if(id==82){nazwaitemu = "Zelazne rekawice"; obrona = 3; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 340;}
		if(id==83){nazwaitemu = "Stalowe rekawice"; obrona = 4; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 550;}
		if(id==84){nazwaitemu = "Szklane rekawice"; obrona = 6; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 800;}
		if(id==85){nazwaitemu = "Krasnoludzkie rekawice"; obrona = 8; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 1100;}
		if(id==100){nazwaitemu = "Zardzewialy zelazny sztylet"; obrona = 2; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 100;}
		if(id==101){nazwaitemu = "Zelazny sztylet"; obrona = 5; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 400;}
		if(id==102){nazwaitemu = "Stalowy sztylet"; obrona = 10; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 800;}
		if(id==103){nazwaitemu = "Zelazny krotki miecz"; obrona = 15; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 1600;}
		if(id==104){nazwaitemu = "Walerianski krotki miecz"; obrona = 20; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 2500;}
		if(id==105){nazwaitemu = "Stalowy krotki miecz"; obrona = 25; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 3200;}
	}

	void pokazitem()
	{
		cout << nazwaitemu << "|| "<<obrona<< " || Wartosc: " << wartoscPrzedmiotu;
		if (czyPrzedmiotPosiadany == 1) cout << " (Posiadasz)\n";
		if (czyPrzedmiotPosiadany  == 2 ) cout <<" (Nosisz)\n";
		if (czyPrzedmiotPosiadany == 0 ) cout << endl;
	}
	string wyswietlItem(int idItemu)
	{
		string ciagZnakow;
		items(idItemu);
		ciagZnakow = nazwaitemu +string(" # ") + to_string(obrona) + string(" # Wartosc: ") + to_string (wartoscPrzedmiotu);
		if (czyPrzedmiotPosiadany == 1) ciagZnakow= ciagZnakow + " (Posiadasz)";
		if (czyPrzedmiotPosiadany == 2 ) ciagZnakow= ciagZnakow + " (Nosisz)";
		return ciagZnakow;
	}

	void ekwipunek()
	{
		system("cls");
		int ilezlota = 0;
		cout << "Zawartosc twojego ekwipunku:\n";
		int bylo1= 0,bylo2= 0,bylo3= 0,bylo4= 0,bylo5= 0,bylo6 = 0;
		for (int i =1;i<200;i++){
			items(i);
			if (postac.posiadanePrzedmioty[i]==1 || postac.posiadanePrzedmioty[i]==2)
			{
				if (i>0 && i<20 && bylo1==0) {bialy();cout << "\nHelmy:\n";szary(); bylo1=1;}
				if (i>19 && i<40 && bylo2==0) {bialy();cout << "\nZbroje:\n";szary(); bylo2 =1;}
				if (i>39 && i<60 && bylo3==0) {bialy();cout << "\nButy:\n";szary(); bylo3 =1;}
				if (i>59 && i<80 && bylo4==0) {bialy();cout << "\nSpodnie:\n";szary(); bylo4 =1;}
				if (i>79 && i<100 && bylo5==0) {bialy();cout << "\nRekawice:\n";szary(); bylo5 =1;}
				if (i>99 && i<200 && bylo6==0) {bialy();cout << "\nBronie:\n";szary(); bylo6 =1;}
				pokazitem();
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
		pokaz();
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
				if (ktoryPrzedmiot>19 && ktoryPrzedmiot<40)for (int i=20;i<40;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
				if (ktoryPrzedmiot>39 && ktoryPrzedmiot<60)for (int i=40;i<60;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
				if (ktoryPrzedmiot>59 && ktoryPrzedmiot<80) for (int i=60;i<80;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
				if (ktoryPrzedmiot>79 && ktoryPrzedmiot<100)for (int i=80;i<100;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
				if (ktoryPrzedmiot>99 && ktoryPrzedmiot<200)for (int i=100;i<200;i++){if (postac.posiadanePrzedmioty[i]==2) postac.posiadanePrzedmioty[i]=1;}
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
				if (postac.zloto > wartoscPrzedmiotu-1){
					postac.posiadanePrzedmioty[ktoryPrzedmiot]=2; 
					postac.zloto = postac.zloto-wartoscPrzedmiotu;
					mciSendString("play sounds/goldd.wav ",NULL,1,NULL);
					ramkaInformacji("Kupiles " + nazwaitemu +string(" za ") + to_string(int(wartoscPrzedmiotu)) +string(" sztuk zlota."));

				}
				else
				{
					ramkaInformacji("Nie posiadasz " + to_string(wartoscPrzedmiotu) + string(" sztuk zlota."));
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
			ramkaWyboru("Co chcialbys zobaczyc?","Helmy|Zbroje|Buty|Spodnie|Rekawice|Bron|Powrot...|");
			if (wybor == 1)
				typ = 0;
			else if (wybor == 2)
				typ = 19;
			else if (wybor == 3)
				typ = 39;
			else if (wybor == 4)
				typ = 59;
			else if (wybor == 5)
				typ = 79;
			else if (wybor == 6)
				typ = 99;
			if (wybor == 7) 
			{
				ramkaInformacji("Kowal: \"Bywaj!...\"","Wyszedles...");
				return;
			}
			int tempInt = 1;
			tempTekst2 = "";
			tempTekst1 = "lol";
			while (true)
			{
				if (tempTekst1 != wyswietlItem(tempInt+typ))
					tempTekst2 += wyswietlItem(tempInt+typ) + string("|");
				else
					break;
				tempTekst1 = wyswietlItem(tempInt+typ);
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
	if(id==2){nazwaklasy = "Czarodziej"; obrona = 2; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 220;} //za kazdy lvl dodatkowa mana
	if(id==3){nazwaklasy = "Lotrzyk"; obrona = 4; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 420;}    //za kazdy lvl dodatkowy kryt
	if(id==4){nazwaklasy = "Barbarzynca"; obrona = 6; czyPrzedmiotPosiadany = postac.posiadanePrzedmioty[id]; wartoscPrzedmiotu = 620;}//za kazdy lvl dodatkowy dmg(?)
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
	void krok()
	{
		/*if (randus==0)mciSendString("stop sounds/krok1.wav ",NULL,1,NULL);
		if (randus==1)mciSendString("stop sounds/krok2.wav ",NULL,1,NULL);
		if (randus==2)mciSendString("stop sounds/krok3.wav ",NULL,1,NULL);
		if (randus==3)mciSendString("stop sounds/krok4.wav ",NULL,1,NULL);*/
		randus = (rand() % 3);

		if (randus==0)mciSendString("play sounds/krok1.wav ",NULL,1,NULL);
		if (randus==1)mciSendString("play sounds/krok2.wav ",NULL,1,NULL);
		if (randus==2)mciSendString("play sounds/krok3.wav ",NULL,1,NULL);
		if (randus==3)mciSendString("play sounds/krok4.wav ",NULL,1,NULL);
	}

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
		int randus = (rand() % 1);
		if (randus==0)mciSendString("play sounds/skrzynka1.wav ",NULL,1,NULL);
		if (randus==1)mciSendString("play sounds/skrzynka2.wav ",NULL,1,NULL);
		if (trudnoscPoziomu == 1) {ilosczlota = (rand() % 20)+20;zdobyteZloto=zdobyteZloto+ilosczlota;}
		if (trudnoscPoziomu == 2) {ilosczlota = (rand() % 100)+500;zdobyteZloto=zdobyteZloto+ilosczlota;}
		if (trudnoscPoziomu == 3) {ilosczlota = (rand() % 100)+1000;zdobyteZloto=zdobyteZloto+ilosczlota;}
		if (trudnoscPoziomu == 4) {ilosczlota = (rand() % 100)+2000;zdobyteZloto=zdobyteZloto+ilosczlota;}
		if (wktora==1){gotoxy(x-1,y);sciana[x-1][y]= 0; cout << " ";}
		if (wktora==2){gotoxy(x+1,y);sciana[x+1][y]= 0; cout << " ";}
		if (wktora==3){gotoxy(x,y-1);sciana[x][y-1]= 0; cout << " ";}
		if (wktora==4){gotoxy(x,y+1);sciana[x][y+1]= 0; cout << " ";}
		ramkaInformacji("Otrzymales " + to_string(ilosczlota) + string(" szt zlota."), "Posiadasz teraz " + to_string(postac.zloto) + string(" szt zlota."));
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
				if (y>0){

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
			postac.posiadanePrzedmioty[100] = 2;
			system("cls");
			logo();
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
							ramkaWyboru("Czy napewno chcialbys nadpisac ","Tak|Nie|","swoja poprzednia gre?");
							if (wybor == 1)
							{
								p=1;
								ofstream plik;                
								plik.open(sciezka,ios::out);
								plik << nick << endl << postac.poziom << endl << postac.doswiadczenie << endl << postac.maksymalneDoswiadczenie << endl << postac.hp << endl << postac.maxhp << endl << postac.mp << endl << postac.maxmp << endl << postac.sila << endl << postac.inteligencja << endl << postac.zrecznosc << endl << postac.budowa  << endl << postac.zloto << endl << postac.hppot << endl << postac.mppot << endl << postac.opoznienieTekstu << endl << autozapis;
								for (int i=1;i<200;i++)
									plik << endl << postac.posiadanePrzedmioty[i];
								plik.close();
								ramkaInformacji("Nadpisalem gre gracza:",string(nick));
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
							plik.close();
							p=1;
							ramkaInformacji("Stworzylem nowy plik postaci pod nazwa:",string(nick));
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
		ramkaInformacji("Twoja postac nie zyje.","Przegrales");
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
				if (wygrana ==1){
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
						krok();
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
						krok();
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
						krok();
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
						krok();
						y++;
						reset();
						gotoxy(x,y-1);
						cout << " ";
					}
				}

				if (GetAsyncKeyState('X'))
				{
					if (wktora==1)
					{
						if (sciana[x-1][y]==7) usedrzwi();
						if (sciana[x-1][y]==2) usePotwor(1,false);
						if (sciana[x-1][y]==4) usewyjscie();
						if (sciana[x-1][y]==5) usewejscie();
						if (sciana[x-1][y]==6) useskrzynka();
						if (sciana[x-1][y]==3) usePotwor(2,false);
						if (sciana[x-1][y]==8) usePotwor(3,false);
						if (sciana[x-1][y]==9) usePotwor(4,false);
					}
					if (wktora==2)
					{
						if (sciana[x+1][y]==7) usedrzwi();
						if (sciana[x+1][y]==2) usePotwor(1,false);
						if (sciana[x+1][y]==4) usewyjscie();
						if (sciana[x+1][y]==5) usewejscie();
						if (sciana[x+1][y]==6) useskrzynka();
						if (sciana[x+1][y]==3) usePotwor(2,false);
						if (sciana[x+1][y]==8) usePotwor(3,false);
						if (sciana[x+1][y]==9) usePotwor(4,false);
					}
					if (wktora==3)
					{
						if (sciana[x][y-1]==7) usedrzwi();
						if (sciana[x][y-1]==2) usePotwor(1,false);
						if (sciana[x][y-1]==4) usewyjscie();
						if (sciana[x][y-1]==5) usewejscie();
						if (sciana[x][y-1]==6) useskrzynka();
						if (sciana[x][y-1]==3) usePotwor(2,false);
						if (sciana[x][y-1]==8) usePotwor(3,false);
						if (sciana[x][y-1]==9) usePotwor(4,false);
					}
					if (wktora==4)
					{
						if (sciana[x][y+1]==7) usedrzwi();
						if (sciana[x][y+1]==2) usePotwor(1,false);
						if (sciana[x][y+1]==4) usewyjscie();
						if (sciana[x][y+1]==5) usewejscie();
						if (sciana[x][y+1]==6) useskrzynka();
						if (sciana[x][y+1]==3) usePotwor(2,false);
						if (sciana[x][y+1]==8) usePotwor(3,false);
						if (sciana[x][y+1]==9) usePotwor(4,false);
					}
				}
				if (GetAsyncKeyState('Z'))
				{
					pas();
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
				cout << "Klawisze: x - akcja, z - pas, strzalki - chodzenie";
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
		//				odtworzLosowyDzwiek("hit1.wav|hit2.wav|hit3.wav|hit4.wav|hit5.mp3|");
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

