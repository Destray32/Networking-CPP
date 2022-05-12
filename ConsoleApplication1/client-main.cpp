#include "pch.h"
#include "slowo.h"
#include "funkcje.h"

#define RESET_FLAGI flaga = false
#define PORT 8001

namespace networking
{
	asio::error_code ec;

	asio::io_context context;

	asio::ip::tcp::socket sc(context);

	asio::streambuf buff(1000);
	asio::streambuf buff_koduKolejki(100);
}

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
#pragma endregion


	std::string kodMultiplayer;

	// kod gracza
	char kod;

	// kod do kolejki
	char kod2;
	bool czyWiecejNizJeden = false;
	
	std::string ip;
	std::cout << "Podaj lokalny adres IP gracza, z ktorym chcesz sie polaczyc\n";
	std::cin >> ip;

	asio::ip::tcp::endpoint endpoint(asio::ip::make_address(ip, networking::ec), PORT);

	networking::sc.connect(endpoint, networking::ec);
	
	std::cout << "Oczekiwanie na reszte graczy\n";

	// wyciagniecie od hosta kodu oznaczajacego, czy jest to pierwszy gracz czy drugi itd.
	asio::read_until(networking::sc, networking::buff, '0');
	std::istream is_pierwszy(&networking::buff);
	is_pierwszy >> kodMultiplayer;
	kod = kodMultiplayer[0];

	// czyszczenie bufora
	networking::buff.consume(kodMultiplayer.size());





#pragma region INICJACJA

	// Pobieranie hasla od servera
	asio::read_until(networking::sc, networking::buff, '!');

	// stream z odebranym haslem od hosta
	std::istream is(&networking::buff);

	// wprowadzenie odebranego hasla do zmiennej string
	is >> haslo;


	// wyrownanie hasla tak zeby bylo bez wykrzyknika
	haslo.pop_back();
	dlugoscHasla = haslo.size();

	// TODO: 
	// pospinaæ co sie da w funkcje zeby by³o przejrzyscie

	hasloDoWyswietlenia = ZmienZdanie(haslo);
	IndeksyPol(hasloDoWyswietlenia, indeksyPol);

#pragma endregion INICJACJA

#pragma region MAIN LOOP

	// main loop gry klienta
	while (znalezioneLitery < dlugoscHasla && hp > 0)
	{
		std::string kodKolejki;

		// reset flagi (flaga = false)
		RESET_FLAGI;

		std::cout << "Akutalna ilosc zyc: " << hp << '\n';

		std::cout << "Oczekiwanie na swoja kolej\n";

		// odczytywanie od hosta aby sprawdzic czy jest akutalnie twoja kolej
		asio::read_until(networking::sc, networking::buff_koduKolejki, '0');
		std::istream is_drugi(&networking::buff_koduKolejki);

		is_drugi >> kodKolejki;
		kod2 = kodKolejki[0];

		// sprawdzanie kodu ktory dostales na poczatku z kodem ktory wlasnie wyslal host
		if (kod == kod2)
		{
			std::cout << "Podaj litere:\n";
			std::cin >> litera;
			// wyslanie literki do hosta
			networking::sc.write_some(asio::buffer(&litera, 1));
		}
		else
		{
			networking::sc.read_some(asio::buffer(&litera, 1));
		}

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
#endif // _WIN32 || WIN32

		WpiszLitere(hasloDoWyswietlenia, indexyZnalezionychLiter);
	}
	std::cout << "Koniec!\n";

#ifdef _WIN32
		system("pause");
#endif

#pragma endregion MAIN LOOP
}


