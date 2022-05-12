#pragma once

#include "pch.h"
#include "slowo.h"


void SprawdzLitere(std::string, std::vector<int>&, unsigned int&, char, int&);

std::string ZmienZdanie(std::string);

void IndeksyPol(std::string zdanie, std::vector<int>& indexyPol);

void WpiszLitere(std::string&, std::vector<int>&);

void PrzygotowanieHasla(Haslo haslo1, int& ustawHasloReturn, std::string& haslo);

void PolaczenieZClientem(asio::basic_socket_acceptor<asio::ip::tcp>& ac, asio::basic_stream_socket<asio::ip::tcp>& sc, const std::string& gracz, asio::error_code ec, int ktoryClient);