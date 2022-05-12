#include "pch.h"
#include "slowo.h"
#include "funkcje.h"

#define RESET_FLAGI flaga = false

int main()
{
#pragma region Zmienne

	// wartosci do gry
	int hp = 5;
	int dlugoscHasla = 0;
	unsigned int znalezioneLitery = 0;

	bool flaga = false;
	bool czyClient = false;
	bool czyHost = false;
	int ustawHasloReturn = 0;

	char litera;
	std::string haslo;
	std::string hasloDoWyswietlenia;

#pragma endregion


#pragma region Wskazniki

	unsigned int* znalezioneLitery_p = &znalezioneLitery;
	int* hp_p = &hp;

#pragma endregion


#pragma region Kontenery
	std::vector<int> indexyZnalezionychLiter;
	std::vector<int> indeksyPol;
	std::vector<char> uzyteLitery;
#pragma endregion Kontenery


#pragma region INICJACJA

	// inicjacja klasy z hasłem ( to powinien wykonywać host i przesłać do clienta dane)
	Haslo haslo1;

	// nie pozwol wyjsc z petli aż do momentu wprowadzenia poprawnego hasła
	do
	{
		ustawHasloReturn = haslo1.UstawHaslo();
	} while (!ustawHasloReturn);

	dlugoscHasla = haslo1.GetHaslo().size();
	haslo = haslo1.GetHaslo();

	hasloDoWyswietlenia = ZmienZdanie(haslo);
	IndeksyPol(hasloDoWyswietlenia, indeksyPol);

#pragma endregion INICJACJA

#pragma region MAIN LOOP

	// main loop gry klienta
	while (znalezioneLitery < dlugoscHasla && hp > 0)
	{
		// reset flagi (flaga = false)
		RESET_FLAGI;

		std::cout << "Akutalna ilosc zyc: " << hp << '\n';
		std::cout << "Podaj litere\n";
		std::cin >> litera;

		// zapisywanie uzytych juz liter
		for (char x : uzyteLitery)
		{
			if (x == litera)
			{
				std::cout << "Ta litera byla juz wpisana!\n";
				flaga = true;
			}
		}

		// przerwij dalsze wykonywanie pętli jeśli wpisana została ta sama litera
		if (flaga)
		{
			continue;
		}
		uzyteLitery.push_back(litera);
		SprawdzLitere(haslo, indexyZnalezionychLiter, *znalezioneLitery_p, litera, *hp_p);
		system("cls");
		WpiszLitere(hasloDoWyswietlenia, indexyZnalezionychLiter);
	}

#pragma endregion MAIN LOOP
}


