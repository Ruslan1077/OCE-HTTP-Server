#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "LuaContext.hpp"


namespace lua
{
    namespace
    {

        const char* params_variable_name = "api_params";
        const char* result_variable_name = "api_result";

    } // namespace


    class lua_executor
    {
    public:
        std::string run_code(
            const std::string& path,
            const std::string& params)
        {
            if (path.empty())
                return std::string("path not found.");

            std::string code_result;
            try
            {
                std::ifstream script(path);
                ctx.writeVariable(params_variable_name, params);
                ctx.executeCode(script);
                code_result = ctx.readVariable<std::string>(result_variable_name);
            }
            catch (const std::exception& ex)
            {
                code_result = ex.what();
            }

            return code_result;
        }

    private:
        LuaContext ctx;
    };

} // namespace lua