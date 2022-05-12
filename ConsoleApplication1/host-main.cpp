#include "pch.h"
#include "slowo.h"
#include "funkcje.h"
#include "namespaces.h"

#define RESET_FLAGI flaga = false

HBITMAP bitmap;

int main()
{
#pragma region Zmienne

	int iloscGraczy = 0;

	// wartosci do gry
	int hp = 5;
	int dlugoscHasla = 0;
	int iterator = 0;
	unsigned int znalezioneLitery = 0;

	bool flaga = false;
	int ustawHasloReturn = 0;

	char litera;
	std::string haslo;
	std::string gracz1, gracz2, gracz3, gracz4;
	std::string hasloDoWyswietlenia;

#pragma endregion


#pragma region Wskazniki

	unsigned int* znalezioneLitery_p = &znalezioneLitery;
	int* hp_p = &hp;

	// wkazniki na sockety
	asio::ip::tcp::socket* sockety_p[4] = { &networking::sock, &networking::sock2, &networking::sock3, &networking::sock4 };

	// make pointer array of gracz1 etc.
	std::string* gracz[4] = { &gracz1, &gracz2, &gracz3, &gracz4 };

#pragma endregion


#pragma region Kontenery
	std::vector<int> indexyZnalezionychLiter;
	std::vector<int> indeksyPol;
	std::vector<char> uzyteLitery;
#pragma endregion


#pragma region Polaczenie

	gracz1 = "10";
	gracz2 = "20";
	gracz3 = "30";
	gracz4 = "40";
	
	//wybierz na ile graczy zrobic lobby
	std::cout << "Wpisz ilosc graczy z ktorymi chcesz sie polaczyæ\n";
	std::cin >> iloscGraczy;
	system("cls");

	std::cout << "Oczekiwanie na polaczenie z clientem!\n";

	// ustawienie acceptora na nasluch
	networking::acceptor.listen();
	
	// polaczenie z clientami
	for (int i = 0; i < iloscGraczy; i++)
	{
		PolaczenieZClientem(networking::acceptor, *sockety_p[i], *gracz[i], networking::ec, i);
	}

	
#pragma endregion 


#pragma region Odebranie danych


	// inicjacja klasy z has³em
	Haslo haslo1;

	PrzygotowanieHasla(haslo1, ustawHasloReturn, haslo);

	// wylsanie ustawionego hasla z wykrzyknikiem
	if (networking::sock.is_open() && networking::sock2.is_open() && networking::sock3.is_open() && networking::sock4.is_open())
	{
		for (int i = 0; i < iloscGraczy; i++)
		{
			sockety_p[i]->write_some(asio::buffer(haslo.data(), haslo.size()), networking::ec);
		}
	}

	if (networking::ec)
	{
		std::cout << "Wystapil blad: " << networking::ec << std::endl;
	}


	// usunac wykrzyknik z konca hasla po wyslaniu Z WYKRZYKNIKIEM do clientow
	haslo.pop_back();
	dlugoscHasla = haslo.size();

	hasloDoWyswietlenia = ZmienZdanie(haslo);
	IndeksyPol(hasloDoWyswietlenia, indeksyPol);

#pragma endregion Odebranie danych


#pragma region MAIN LOOP

	// main loop gry klienta
	while (znalezioneLitery < dlugoscHasla && hp > 0)
	{
		if (iterator == 4)
		{
			iterator = 0;
		}
		// reset flagi (flaga = false)
		RESET_FLAGI;

		std::cout << "Akutalna ilosc zyc: " << hp << '\n';

		char l;

		// daj znac ktory klient ma wpisac literke

		for (int i = 0; i < iloscGraczy; i++)
		{
			sockety_p[i]->write_some(asio::buffer(gracz[iterator]->data(), gracz[iterator]->size()), networking::ec);
		}

		// odczytaj literke od klienta ktory ma swoja kolej
		sockety_p[iterator]->read_some(asio::buffer(&l, 1));

		//wyslij te literke do reszty graczy
		for (int i = 0; iloscGraczy < 4; i++)
		{
			// pomiñ wysy³adnie do gracza od ktorego wlasnie dostales literke
			if (i == iterator)
			{
				continue;
			}
			sockety_p[i]->write_some(asio::buffer(&l, 1));
		}

		// przejscie do nastêpnego socketu w tablicy wkaŸników
		iterator++;

		litera = l;
		
		// zapisywanie uzytych juz liter
		for (char x : uzyteLitery)
		{
			if (x == litera)
			{
				std::cout << "Ta litera byla juz wpisana!\n";
				flaga = true;
			}
		}

		// przerwij dalsze wykonywanie pêtli jeœli wpisana zosta³a ta sama litera
		if (flaga)
		{
			continue;
		}
		uzyteLitery.push_back(litera);
		SprawdzLitere(haslo, indexyZnalezionychLiter, *znalezioneLitery_p, litera, *hp_p);

#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif // _WIN32

		WpiszLitere(hasloDoWyswietlenia, indexyZnalezionychLiter);
	}

	std::cout << "Koniec!" << std::endl;

#ifdef _WIN32
	system("pause");
#endif // _WIN32

	// wylaczenie funkcji hosta
	networking::sock.close();
	networking::ios.stop();

#pragma endregion MAIN LOOP
}


