#pragma once

#include "pch.h"
#include "http_connection.h"

namespace serv
{
    namespace beast = boost::beast;
    namespace http = beast::http;
    namespace net = boost::asio;


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