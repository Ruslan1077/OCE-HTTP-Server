# OCE-HTTP-Server
##### Basic information
- http server for running Lua scripts
- version: 0.1.10 (beta test)

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

##### Pre-compiled server
You can use pre-compiled server that placed in
- Win_http_compiled\x64\ - for x64
- Win_http_compiled\x32\ - for Win32
> NOTE: pdb folder contains all .pdb files for debugging

##### How to configure & run
Config example
```json
{
  "server_ip": "127.0.0.1",
  "server_port": 80,
  "script_folder": ""
}
```
To configure the server, just edit config.json in the root folder of the server. The following parameters are required to run the server:
- server_ip -> static ip of the server machine (if you run it on remote machine) or 127.0.0.1 (if you run it on local machine).
- server_port -> I use 80.
- script_folder -> the folder with the server scripts to run.
> NOTE: if the configuration file is missing, it will be generated automatically with default settings (config example).

##### How to use
`Coming soon`

##### Before release 1.2.x we need to finish
- [x] Add POST request processing.
- [x] Add documentation/diagrams etc.
- [x] Add configuration option for scripts folder.
- [x] Add default config generation.
- [ ] Add "How to use" section in documentation.
- [ ] Add unsecure endpoint host/exec/.
- [ ] Refactor code.

##### Future plans on release 1.3.x
- [ ] Add server command line.
