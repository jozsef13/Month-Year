#include "CCalendar.h"

int CCalendar::Aloysius(int an, int& luna, int& zi) 
{
	int g, c, x, e, d, z, n;
	if (an < 1582)
		return 0;
	/// “numarul de aur” in cel de-al 19 ciclu Metonic
	g = an % 19 + 1;
	// secolul
	c = an / 100 + 1;
	/// numarul de ani in care anul bisecta fost neglijat
	x = (3 * c) / 4 - 12;
	/// corectie pentru sincronizare cu orbita lunii
	z = (8 * c + 5) / 25 - 5;
	/// determinarea duminicii
	d = (5 * an / 4) - x - 10;
	/// determinarea aparitiei lunii pline
	e = (11 * g + 20 + zi - x) % 30;
	/// corectie
	if ((e == 25 && g > 11) || (e == 24))
		e++;
	/// determinarea exacta a aparitiei lunii pline
	n = 44 - e;
	/// corectie
	if (n < 21)
		n = n + 30;
	/// stabileste prima duminica dupa luna plina
	n = n + 7 -((d + 7) % 10);
	/// determina luna
	if (n > 31) { /// luna aprilie
		zi = n - 31;
		luna = 4;
	}
	else { /// luna martie
		zi = n;
		luna = 3;
	}
	return 1;
}

CCalendar::CCalendar()
{
	luni[1] = "Ianuarie";
	luni[2] = "Februarie";
	luni[3] = "Martie";
	luni[4] = "Aprilie";
	luni[5] = "Mai";
	luni[6] = "Iunie";
	luni[7] = "Iulie";
	luni[8] = "August";
	luni[9] = "Septembrie";
	luni[10] = "Octombrie";
	luni[11] = "Noiembrie";
	luni[12] = "Decembrie";

	nrZile[1] = 31;
	nrZile[2] = 28;
	nrZile[3] = 31;
	nrZile[4] = 30;
	nrZile[5] = 31;
	nrZile[6] = 30;
	nrZile[7] = 31;
	nrZile[8] = 31;
	nrZile[9] = 30;
	nrZile[10] = 31;
	nrZile[11] = 30;
	nrZile[12] = 31;

	zile[1] = "Sun";
	zile[2] = "Mon";
	zile[3] = "Wed";
	zile[4] = "Tue";
	zile[5] = "Thu";
	zile[6] = "Fri";
	zile[7] = "Sat";

	anulMeu = 0;
	lunaMea = 0;
}

int CCalendar::primaZiDinLuna(int luna, int an)
{
	int ziua = 1;
	int diua = 0;
	int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	an -= luna < 3;
	diua = (an + an / 4 - an / 100 + an / 400 + t[luna - 1] + ziua) % 7;
	return diua;
}

int CCalendar::citireAn()
{
	int an;
	cout << "Anul de inceput al calendarului este anul 1000!" << endl;
	cout << "Durata calendarului este de 3000 de ani!" << endl;
	cout << endl << "Introduceti anul: ";
	cin >> an;
	return an;
}

int CCalendar::citireLuna()
{
	int luna;
	cout << endl << "Introduceti luna: ";
	cin >> luna;
	return luna;
}

void CCalendar::afisareLunaAn()
{
	int m = 1, lunaPaste = 1, ziuaPaste = 1;
	anulMeu = citireAn();
	lunaMea = citireLuna();
	if (lunaMea <= 12 && anulMeu <= 3000 && anulMeu >= 1000)
	{
		cout << "Ati ales luna: " << luni[lunaMea] << " si anul: " << anulMeu << endl;
	}
	else
	{
		cout << "Anul sau luna au fost alese gresit!";
		return;
	}
	cout << endl;
	//verificam an bisect
	if ((anulMeu % 4 == 0 && anulMeu % 100 != 0) || (anulMeu % 400 == 0))
	{
		nrZile[2] = 29;
	}

	int stanga = (35 - luni[lunaMea].size()) / 2;
	for (int x = 0; x < stanga; x++)
	{
		cout << " ";
	}
	cout << luni[lunaMea] << "  " << anulMeu << endl;
	for (int i = 1; i <= 7; i++)
	{
		cout << setw(5) << zile[i] << setw(2) <<" ";
	}
	cout << endl;
	
	int zileAfisate = 0;
	for (int j = 1; j <= nrZile[lunaMea]; j++)
	{
		if (j == 1)
		{
			int d = primaZiDinLuna(lunaMea, anulMeu);
			if (d == 0)
			{
				duminica[m] = d;
				m++;
			}
			for (int spatii = 0; spatii < d; spatii++)
			{
				cout << setw(5) << " " << setw(2) << " " ;
				zileAfisate++;
			}
		}

		cout << setw(5) << j << setw(2) << " ";
		zileAfisate++;
		if (zileAfisate % 7 == 0)
		{
			cout << endl;
			zileAfisate = 0;
		}

		if (zileAfisate % 7 == 1)
		{
			duminica[m] = j;
			m++;
		}
	}

	cout << endl;
	cout << endl << "Duminicile din luna " << luni[lunaMea] << " anul " << anulMeu << " sunt: ";
	for (int i = 1; i < m; i++)
	{
		cout << duminica[i] << " ";
	}

	if (lunaMea == 1)
	{
		cout << endl << "Zilele de 1 si 2 ale acestei luni sunt zile de sarbatoare - Anul Nou!";
	}

	if (lunaMea == 12)
	{
		cout << endl << "Ziua de 1 a acestei luni este zi de sarbatoare - Ziua Nationala a Romaniei!" << endl;
		cout << "Zilele de 24 si 25 ale acestei luni sunt zile de sarbatoare - Craciunul!";
	}

	if (lunaMea == 3 || lunaMea == 4 || lunaMea == 5)
	{
		if (Aloysius(anulMeu, lunaPaste, ziuaPaste) == 1)
		{
			cout << endl;
			cout << "Zilele de " << ziuaPaste << " si " << ziuaPaste + 1 << " sunt zile de sarbatoare - Pastele!";
		}
	}
	

	anulMeu++;
	m = 1;

	cout << endl << endl;
	if ((anulMeu % 4 == 0 && anulMeu % 100 != 0) || (anulMeu % 400 == 0))
	{
		nrZile[2] = 29;
	}

	stanga = (35 - luni[lunaMea].size()) / 2;
	for (int x = 0; x < stanga; x++)
	{
		cout << " ";
	}
	cout << luni[lunaMea] << "  " << anulMeu << endl;
	for (int i = 1; i <= 7; i++)
	{
		cout << setw(5) << zile[i] << setw(2) << " ";
	}
	cout << endl;

	zileAfisate = 0;
	for (int j = 1; j <= nrZile[lunaMea]; j++)
	{
		if (j == 1)
		{
			int d = primaZiDinLuna(lunaMea, anulMeu);
			if (d == 0)
			{
				duminica[m] = d;
				m++;
			}
			for (int spatii = 0; spatii < d; spatii++)
			{
				cout << setw(5) << " " << setw(2) << " ";
				zileAfisate++;
			}
		}

		cout << setw(5) << j << setw(2) << " ";
		zileAfisate++;
		if (zileAfisate % 7 == 0)
		{
			cout << endl;
			zileAfisate = 0;
		}

		if (zileAfisate % 7 == 1)
		{
			duminica[m] = j;
			m++;
		}
	}

	cout << endl;
	cout << endl << "Duminicile din luna " << luni[lunaMea] << " anul " << anulMeu << " sunt: ";
	for (int i = 1; i < m; i++)
	{
		cout << duminica[i] << " ";
	}

	if (lunaMea == 1)
	{
		cout << endl << "Zilele de 1 si 2 ale acestei luni sunt zile de sarbatoare - Anul Nou!";
	}

	if (lunaMea == 12)
	{
		cout << endl << "Ziua de 1 a acestei luni este zi de sarbatoare - Ziua Nationala a Romaniei!" << endl;
		cout << "Zilele de 24 si 25 ale acestei luni sunt zile de sarbatoare - Craciunul!";
	}

	if (lunaMea == 3 || lunaMea == 4 || lunaMea == 5)
	{
		if (Aloysius(anulMeu, lunaPaste, ziuaPaste) == 1)
		{
			cout << endl;
			cout << "Zilele de " << ziuaPaste << " si " << ziuaPaste + 1 << " sunt zile de sarbatoare - Pastele!";
		}
	}

	cout << endl;

}
