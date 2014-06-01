#include <iostream>
#include <cstdio>
#include <fstream>
#include <cctype>
using namespace std;
char a = 178;

int main()
{    
     system("MODE 82,41");
     for (int i = 0; i<41;i++){
for (int j = 0; j<81;j++){
cout << a;
}
cout << endl;
}

     int c;
char wiersz[257];
ifstream we("odczyt2.txt");
int b= 0;
ofstream zapis ("zapis2.txt");
int usuwamy=0;
/*
for (int i = 0; i<41;i++){
for (int j = 0; j<41;j++){
    if (i<10)
    zapis << "sciana[ "<<i<<"]["<<j<<"]=0;";
    else
zapis << "sciana["<<i<<"]["<<j<<"]=0;";

}
zapis << endl;
}
*/
for (int i = 0; i<41;i++){
for (int j = 0; j<41;j++){
zapis << 0;
}
zapis << endl;
}

system("pause");

return 0;  
}


