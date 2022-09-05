#include "pch.h"
#include "http_consts.h"
#include "connection_handler.h"
#include "http_connection.h"

// STUFF FOR TEST
//===============================================================================
namespace server_state
{
    std::size_t request_count()
    {
        static std::size_t count = 0;
        return ++count;
    }

    std::time_t now()
    {
        return std::time(0);
    }
}

namespace utils
{
    std::string get_count_html()
    {
        std::stringstream ss;
        ss << "<html>"
            << "<head><title>Request count</title></head>"
            << "<body>"
            << "<h1>Request count</h1>"
            << "<p>There have been " << server_state::request_count() << " requests so far.</p>"
            << "</body>"
            << "</html>";

        return ss.str();
    }

    std::string get_time_html()
    {
        std::stringstream ss;
        ss << "<html>"
            << "<head><title>Current time</title></head>"
            << "<body>"
            << "<h1>Current time is:</h1>"
            << "<p>There have been " << server_state::now() << " since the epoch.</p>"
            << "</body>"
            << "</html>";

        return ss.str();
    }
}

//===============================================================================

namespace serv_helpers
{

    http_connection::http_connection(tcp::socket socket)
        : socket_(std::move(socket))
        , buffer_(consts::buffer_body_size)
        , dedline_(
            socket_.get_executor(),
            std::chrono::seconds(consts::dedline_s))
    {
    }

    void http_connection::start()
    {
        read_request();
        check_dedline();
    }

    void http_connection::read_request()
    {
        auto self = shared_from_this();

        auto read_cb = [self](
            beast::error_code ec,
            size_t bytes_transferred)
        {
            boost::ignore_unused(bytes_transferred);
            if (!ec)
            {
                self->process_request();
            }
        };

        http::async_read(
            socket_,
            buffer_,
            request_,
            std::move(read_cb));
    }

    void http_connection::process_request()
    {
        auto method = request_.method();

        if (method != http::verb::get)
        {
            response_.result(http::status::bad_request);
            response_.set(http::field::content_type, "text/plain");

            std::stringstream ss;
            ss  << "Invalid request-method: "
                << request_.method_string()
                << ".\r\n";
            response_.body().append(ss.str());

            write_response();
            return;
        }

        auto target = request_.target();
        std::string path( // need to add path for code dir
            target.begin() + 1, // remove '/' in target
            target.end());

        std::string params = request_.body();
        if (params.empty())
            params = "Empty body.";

        connection_handler handler(path, params);
        response_ = handler.create_response(request_.version());
        write_response();
    }

    void http_connection::write_response()
    {
        auto self = shared_from_this();

        auto write_cb = [self](
            beast::error_code ec,
            size_t /*bytes_written*/)
        {
            if (!ec)
            {
                self->socket_.shutdown(tcp::socket::shutdown_send, ec);
                self->dedline_.cancel();
            }
        };

        response_.content_length(response_.body().size());
        http::async_write(
            socket_,
            response_,
            std::move(write_cb));
    }

    void http_connection::check_dedline()
    {
        auto self = shared_from_this();

        auto wait_cb = [self](beast::error_code ec)
        {
            if (!ec)
            {
                self->socket_.close(ec);
            }
        };

        dedline_.async_wait(std::move(wait_cb));
    }

} // namespace serv_helpers