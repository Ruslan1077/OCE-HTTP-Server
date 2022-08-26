#pragma once

#include "stdafx.h"
#include "http_connection.h"

namespace serv
{

    class http_server
    {
        using tcp = net::ip::tcp;

    public:
        explicit http_server(
            net::io_context& ioc,
            const net::ip::address& address,
            unsigned short& port);
        
        ~http_server();

    public:
        void start();
        void stop();

    private:
        void accept();

    private:
        tcp::acceptor acceptor_;
        tcp::socket socket_;
        bool started_;
    };

} // namespace serv