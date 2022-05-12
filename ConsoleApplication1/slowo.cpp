
#include "slowo.h"


#pragma region Has³o

void Haslo::UstawKategorie()
{
	std::cout << "Wpisz kategorie swojego slowa\n";
	std::cin >> this->Haslo::m_kategoria;
}

int Haslo::UstawHaslo()
{
	// wyczysc haslo przed wpisywaniem go
	Haslo::m_haslo.clear();

	std::cout << "Wpisz swoje haslo\n";
	std::cin >> this->Haslo::m_haslo;

	// dodanie wykrzyknika na koniec hasla
	// potrzebne do dzia³ania programu po stronie hosta
	this->Haslo::m_haslo.push_back('!');

	// find space in m_haslo
	if (this->Haslo::m_haslo.find(' ') != std::string::npos)
	{
		std::cout << "Haslo nie moze zawierac spacji\n";
		return 0;
	}

	return 1;

}

void Haslo::WypiszHasloiKat()
{
	std::cout << this->m_haslo << '\n' << this->m_kategoria << '\n';
}

std::string Haslo::GetHaslo()
{
	return this->m_haslo;
}

#pragma endregion 
