#pragma once

#include "stdafx.h"


namespace serv
{
    namespace beast = boost::beast;
    namespace http  = beast::http;
    namespace net   = boost::asio;

    class http_connection : 
        public std::enable_shared_from_this<http_connection>
    {
        using tcp = net::ip::tcp;

    public:
        explicit http_connection(tcp::socket socket);
        ~http_connection() = default;

        void start();

    private:
        void read_request();
        void process_request();
        void create_response();
        void write_response();
        void check_dedline();

    private:
        tcp::socket socket_;
        beast::flat_buffer buffer_;
        net::steady_timer dedline_;
        http::request<http::dynamic_body> request_;
        http::response<http::dynamic_body> response_;
    };

} // namespace serv