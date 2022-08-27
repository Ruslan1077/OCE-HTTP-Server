#include <iostream>
#include "http_server.h"


int main()
{
    using tcp = serv::net::ip::tcp;

    try
    {
        const auto address = serv::net::ip::make_address("127.0.0.1");
        auto port = static_cast<unsigned short>(std::atoi("80"));

        serv::net::io_context ioc{ 1 };

        serv::http_server server(ioc, address, port);
        server.start();

        ioc.run();
    }
    catch (const std::exception& ex)
    {
        std::cerr << "ERROR: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

}