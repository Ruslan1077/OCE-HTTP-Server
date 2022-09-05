#pragma once
#include "pch.h"
#include <string>

namespace serv_helpers
{
    using response_t = http::response<http::string_body>;

    class connection_handler
    {
    public:
        connection_handler(
            const std::string& code_path,
            const std::string& params);

        response_t create_response(unsigned int request_version);

    private:
        std::string code_path_;
        std::string params_;
    };

} // namespace serv_helpers