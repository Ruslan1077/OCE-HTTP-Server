#include "pch.h"
#include "http_server.h"

namespace serv
{

    http_server::http_server(
        net::io_context& ioc,
        const net::ip::address& address,
        unsigned short& port)
        : acceptor_(ioc, {address, port})
        , socket_(ioc)
        , started_(false)
    {
    }

    http_server::~http_server()
    {
    }

    void http_server::start()
    {
        started_ = true;
        accept();
    }

    void http_server::stop()
    {
        started_ = false;
    }

    void http_server::accept()
    {
        auto accept_cb = [this](beast::error_code ec)
        {
            if (!ec)
            {
                if (!started_)
                    return;

                auto connection = std::make_shared<serv_helpers::http_connection>(
                    std::move(socket_));

                connection->start();
            }

            accept();
        };

        acceptor_.async_accept(socket_, accept_cb);
    }

} // namespace serv