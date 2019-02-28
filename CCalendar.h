#ifndef CCALENDAR_H
#define CCALENDAR_H
#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
using namespace std;

class CCalendar
{
public:
	CCalendar();
	int citireAn();
	int citireLuna();
	void afisareLunaAn();
	
private:
	int nrZile[13];
	string luni[13];
	string zile[8];
	int anulMeu;
	int lunaMea;
	int primaZiDinLuna(int luna, int an);
	int lunimeRand = 35;
	int duminica[8];
	int Aloysius(int an, int& luna, int& zi);
};


#endif // !CCALENDAR_H