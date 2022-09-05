#pragma once

#include "pch.h"


namespace serv_helpers
{

    class http_connection : 
        public std::enable_shared_from_this<http_connection>
    {
        using tcp = net::ip::tcp;
        using request_t = http::request<http::string_body>;
        using response_t = http::response<http::string_body>;

    public:
        explicit http_connection(tcp::socket socket);
        ~http_connection() = default;

        void start();

    private:
        void read_request();
        void process_request();
        void write_response();
        void check_dedline();

    private:
        tcp::socket socket_;
        beast::flat_buffer buffer_;
        net::steady_timer dedline_;
        request_t request_;
        response_t response_;
    };

} // namespace serv_helpers