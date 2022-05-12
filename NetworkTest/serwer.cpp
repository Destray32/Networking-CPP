#include <iostream>
#include <vector>

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#define PORT 8001

#define ASIO_STANDALONE
int main()
{
	std::string zdanieWyjsiowe;

	// tutaj ustawienie servera zeby nasluchiwal xD
	asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), PORT);

	asio::io_service ios;

	asio::ip::tcp::acceptor acceptor(ios, ep);
	acceptor.listen();

	asio::ip::tcp::socket sock(ios);
	acceptor.accept(sock);

	asio::streambuf buff(50);
	// czyli z tego co mysle to wszystko co sie odbiera, wysyla jest w SOCKECIE
	// tutaj pozniej jest jedna funkcja ktora odczytuje co siedzi w sockecie
	asio::read_until(sock, buff, '!');

	// przeksztaclenie na input  a potem wyslanie zdania do zmiennej string
	std::istream is(&buff);

	is >> zdanieWyjsiowe;
	std::cout << zdanieWyjsiowe;
}



