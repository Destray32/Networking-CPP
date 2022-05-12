#pragma once

#define PORT 8001

namespace networking
{
	asio::error_code ec;

	// tutaj ustawienie servera zeby nasluchiwal xD
	asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), PORT);

	asio::io_service ios;

	asio::ip::tcp::acceptor acceptor(ios, ep);

	// pierwszy gracz ustawiajacy haslo
	asio::ip::tcp::socket sock(ios);

	// reszta graczy
	asio::ip::tcp::socket sock2(ios);
	asio::ip::tcp::socket sock3(ios);
	asio::ip::tcp::socket sock4(ios);
}