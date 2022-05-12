#include <iostream>

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#define ASIO_STANDALONE
int main()
{
	asio::error_code ec;

	// create context variable
	asio::io_context context;

	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("127.0.0.1", ec), 3306);

	asio::ip::tcp::socket sc(context);

	sc.connect(endpoint, ec);

	if (!ec)
	{
		std::cout << "Polaczono!" << std::endl;
	}
	else
	{
		std::cout << "Polaczenie z adresem nie udane:\n" << ec.message() << std::endl;
	}

	if (sc.is_open())
	{
		std::string buff = "Witaj Swiecie z komputera glownego!\n";
		sc.write_some(asio::buffer(buff.data(), buff.size()), ec);
		
	}
}

