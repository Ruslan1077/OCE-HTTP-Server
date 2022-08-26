#include "http_consts.h"
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

namespace serv
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
        /*
        * REQUEST-PROCESSOR
        * 
        * response_.version(request_.version());
        * response_.keep_alive();
        * 
        * check request_.method()
        * if GET
        *    response_.result(http::status::ok);
        *    response_.set(http::field::server, "OCE-HTTP");
        *    returns OK-status
        *        and
        *    create_response();
        * 
        * 
        * if !GET
        *   response_.result(http::status::bad_request);
        *   response_.set(http::field::content_type, "text/plain");
        * 
        *   beast::ostream(response_.body())
        *       << "Invalid request-method: "
        *       << std::string(request_.method_string())
        *       << ".\r\n";
        * 
        *   returns BAD-REQUEST-status (mb throw)
        */

        response_.version(request_.version());
        response_.keep_alive();

        switch (request_.method())
        {
        case http::verb::get:
            response_.result(http::status::ok);
            response_.set(http::field::server, "OCE-HTTP");
            create_response();
            break;


        default:
            response_.result(http::status::bad_request);
            response_.set(http::field::content_type, "text/plain");

            beast::ostream(response_.body())
                << "Invalid request-method: "
                << std::string(request_.method_string())
                << ".\r\n";
            break;
        }

        write_response();
    }

    void http_connection::create_response()
    {
        /*
        * RESPONSE-CREATOR
        * 
        * depending on target, creates responce
        * mb call from REQUEST-PROCESSOR
        */

        /*
            EXAMPLE

            << func() <- returns std::string

            if (request_.target() == "/count")
            {
                response_.set(http::field::content_type, "text/html");
                beast::ostream(response_.body()) << utils::get_count_html();
            }
            else if (request_.target() == "/time")
            {
                response_.set(http::field::content_type, "text/html");
                beast::ostream(response_.body()) << utils::get_time_html();
            }
            else
            {
                response_.result(http::status::not_found);
                response_.set(http::field::content_type, "text/plain");
                beast::ostream(response_.body()) << "File not found\r\n";
            }
        */


        if (request_.target() == "/count")
        {
            response_.set(http::field::content_type, "text/html");
            beast::ostream(response_.body()) << utils::get_count_html();
        }
        else if (request_.target() == "/time")
        {
            response_.set(http::field::content_type, "text/html");
            beast::ostream(response_.body()) << utils::get_time_html();
        }
        else
        {
            response_.result(http::status::not_found);
            response_.set(http::field::content_type, "text/plain");
            beast::ostream(response_.body()) << "File not found\r\n";
        }
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

} // namespace serv