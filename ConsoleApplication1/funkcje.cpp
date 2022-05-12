#include "funkcje.h"
#include "slowo.h"

void SprawdzLitere(std::string haslo, std::vector<int>& pozycjeZnakow, unsigned int& znalezioneLitery, char litera, int& hp)
{
	bool literaZnaleziona = false;

	for (int i = 0; i < haslo.size(); i++)
	{
		if (haslo[i] == litera)
		{
			// w ktorym miejscu w hasle zostala znaleziona literka
			pozycjeZnakow.push_back(i);

			// wartosc ascii tej literki
			pozycjeZnakow.push_back((int)litera);
			znalezioneLitery++;

			literaZnaleziona = true;
		}
	}


	if (!literaZnaleziona)
	{
		hp--;
		Beep(1000, 400);
	}
}

// zrobic z tego funkcje tylko do zamiany hasla na te z pustymi polami
std::string ZmienZdanie(std::string haslo)
{

	std::vector<char> zdanie;

	// wypelnianie zdania podlogami (usunalem spacje pomiedzy)
	for (auto x : haslo)
	{
		zdanie.push_back('_');
	}

	for (auto x : zdanie)
	{
		std::cout << x;
	}
	std::cout << '\n';

	std::string zmienioneHaslo(zdanie.data(), zdanie.size());
	return zmienioneHaslo;
}

void WpiszLitere(std::string& zmienioneHaslo, std::vector<int>& pozycjeZnakow)
{
	// zmieniamy zdanie na podstawie pozycji znakow
	for (int i = 0; i < pozycjeZnakow.size(); i += 2)
	{
		zmienioneHaslo[pozycjeZnakow[i]] = static_cast<char>(pozycjeZnakow[i + 1]);
	}

	for (auto x : zmienioneHaslo)
	{
		std::cout << x;
	}
	std::cout << '\n';
}

void IndeksyPol(std::string str, std::vector<int>& indexyPol)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '_')
		{
			indexyPol.push_back(i);
		}
	}
}

void PolaczenieZClientem(asio::basic_socket_acceptor<asio::ip::tcp>& ac, asio::basic_stream_socket<asio::ip::tcp>& sc, const std::string& gracz, asio::error_code ec, int ktoryClient)
{
	ac.accept(sc);

	switch (ktoryClient)
	{
	case 1:
		std::cout << "Polaczono z pierwszym clientem. Oczekiwanie na reszte\n";
		break;
	case 2:
		std::cout << "Polaczono z drugim clientem\n";
		break;
	case 3:
		std::cout << "Polaczono z trzecim clientem\n";
		break;
	case 4:
		std::cout << "Polaczono z czwartym clientem. Rozpoczynamy gre\n";
	default:
		break;
	}

	sc.write_some(asio::buffer(gracz.data(), gracz.size()), ec);
}

void PrzygotowanieHasla(Haslo haslo1, int& ustawHasloReturn, std::string& haslo)
{
	// nie pozwol wyjsc z petli a¿ do momentu wprowadzenia poprawnego has³a
	do
	{
		// ustaw haslo dodaje juz wykrzyknik na koniec
		ustawHasloReturn = haslo1.UstawHaslo();
	} while (!ustawHasloReturn);

	haslo = haslo1.GetHaslo();

	// zamiana liter na lowercase
	std::transform(haslo.begin(), haslo.end(), haslo.begin(),
		[](unsigned char c)
		{ return std::tolower(c); });
}