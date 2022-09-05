#include "pch.h"
#include "lua_executor.h"
#include "connection_handler.h"
#include <fstream>

namespace serv_helpers
{

    connection_handler::connection_handler(
        const std::string& code_path,
        const std::string& params)
        :code_path_(code_path)
        , params_(params)
    {
    }

    response_t connection_handler::create_response(unsigned int request_version)
    {
        lua::lua_executor executor;
        auto result = executor.run_code(code_path_, params_);

        response_t response;
        response.version(request_version);
        response.keep_alive();
        response.result(http::status::ok);
        response.set(http::field::server, "OCE-HTTP");
        response.set(http::field::content_type, "application/json");
        response.body().append(result);

        return std::move(response);
    }

} // namespace serv_helpers


