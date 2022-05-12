#pragma once

#include "pch.h"


class Haslo
{
public:
	void UstawKategorie();

	// funkcja zwraca 1 gdy zadziala prawidlowo i 0 jesli jest blad
	int UstawHaslo();
	std::string GetHaslo();

	void WypiszHasloiKat();

private:
	std::string m_kategoria, m_haslo;
};

