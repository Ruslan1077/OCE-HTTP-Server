#include <iostream>
#include "http_server.h"
#include "config.h"

int main()
{
    using tcp = serv::net::ip::tcp;

    try
    {
        config::storage cfg("config.json");

        auto folder = cfg.get_option_by_id<std::string>(config::id::script_folder);
        auto ip     = cfg.get_option_by_id<std::string>(config::id::server_ip);
        auto port   = cfg.get_option_by_id<unsigned short>(config::id::server_port);

        serv::net::io_context ioc{ 1 };

        serv::http_server server(
            ioc,
            serv::net::ip::make_address(ip),
            port);

        server.set_script_folder(folder);
        server.start();
        ioc.run();
    }
    catch (const std::exception& ex)
    {
        std::cerr << "ERROR: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

}