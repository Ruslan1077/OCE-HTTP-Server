#ifndef PCH_H
#define PCH_H

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

namespace serv_helpers
{
    namespace beast = boost::beast;
    namespace http = beast::http;
    namespace net = boost::asio;
}

#endif //PCH_H
