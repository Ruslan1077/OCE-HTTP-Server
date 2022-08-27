#pragma once

#include <fstream>
#include <nlohmann/json.hpp>

namespace config
{
    enum class option
    {
        id_server_ip = 0,
        id_server_port,
        id_scripts_folder,
        id_opt_count
    };


    class json_wrapper
    {
        using json_t = nlohmann::json;

    public:
        json_wrapper(const std::string& config_path);
        ~json_wrapper();

    public:
        bool load_configuration();
        std::string get_option_by_id();

    private:
        std::string config_path_;
        json_t config_;
    };

} // namespace config