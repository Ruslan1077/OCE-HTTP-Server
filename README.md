# OCE-HTTP-Server
##### Basic information
- http server for running Lua scripts
- version: 0.0.8 (alpha test)

##### Used libraries
- boost (server implementation)
- nlohmann-json: https://github.com/nlohmann/json (server configuration)
- lua-wrapper: https://github.com/ahupowerdns/luawrapper (simple to use Lua wrapper for c++)

##### How to build
- Open the project with MVS (2019 or higher).
- Configure the build for Release and x64 (for x64 platform) or Win32 (for x86 platform).
- Rebuild the **http_server** project.

Once all dependencies have been downloaded, the project is built. The compiled server is placed in:<br>
...\OCE-HTTP-Server\OCE-HTTP-Server\bin\ [platform] \Release<br>
[platform] - means x64 or Win32.

##### How to configure & run
Config example
```json
{
  "server_ip": "127.0.0.1",
  "server_port": 80,
  "script_folder": "server_scripts\lua"
}
```
To configure the server, just edit config.json in the root folder of the server. The following parameters are required to run the server:
- server_ip -> static ip of the server machine (if you run it on remote machine) or 127.0.0.1 (if you run it on local machine).
- server_port -> I use 80.
- script_folder -> the folder with the server scripts to run.
> NOTE: For now the configuration file has to be added manually. In future versions, if the configuration file is missing, it will be generated automatically with default settings.

After configuring the server run .exe file
