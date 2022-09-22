#pragma once
#include "pch.h"

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

namespace
{
    using json_t = nlohmann::json;

    bool custom_config_exist(const std::string& path)
    {
        std::ifstream config_file(path);
        return config_file.good();
    }

    void create_default_config(const std::string& path)
    {
        std::string default_config = "{ \"server_ip\": \"127.0.0.1\", \"server_port\": 80, \"script_folder\": \"\" }";
        std::ofstream file(path);
        
        if (!file.is_open())
        {
            throw std::exception("Can't create default config.");
        }

        file << default_config;
        file.close();
    }

    json_t get_json(const std::string& path)
    {
        if (path.empty())
            throw std::runtime_error(__FUNCTION__ " path not found");

        std::ifstream file(path);
        if (!file.is_open())
        {
            std::stringstream ss;
            ss << __FUNCTION__ << "cannot open file. path is: " << path;
            throw std::runtime_error(ss.str());
        }

        
        json_t output_json = json_t::parse(file);

        file.close();
        return std::move(output_json);
    }

} // namespace


namespace config
{
    enum class id
    {
        server_ip = 0,
        server_port,
        script_folder,
        ids_count
    };

    std::vector<std::string> options = {
        "server_ip",
        "server_port",
        "script_folder"
    };

    class storage
    {
    public:
        storage(const std::string& path)
        {
            if (!custom_config_exist(path))
            {
                create_default_config(path);
            }

            json_config_ = get_json(path);
        }

        template<typename out_option_t>
        out_option_t get_option_by_id(id id)
        {
            int id_int = static_cast<int>(id);
            return json_config_[options[id_int]].get<out_option_t>();
        }

    private:
        json_t json_config_;
    };

} // namespace config